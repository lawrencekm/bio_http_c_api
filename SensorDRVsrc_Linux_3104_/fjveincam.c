/*
 * USB PalmSecure Sensor driver
 *
 * Copyright (C) 2015 - 2016 FUJITSU FRONTECH LIMITED
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	version 2 as published by the Free Software Foundation.
 *
 * Notes:
 *
 * History:
 *
 * 2015-03-16 - V31L02
 * 2016-11-02 - V31L03
 * 2018-01-16 - V31L04
 *
 *
 */

#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,11,0)
#include <linux/sched/signal.h>
#else
#include <linux/sched.h>
#endif
#include <linux/usb.h>

#include "fjveincam.h"

/* Version Information */
#define DRIVER_NAME			"fjveincam"
#define DRIVER_AUTHOR		"Fujitsu Frontech Ltd."
#define DRIVER_DESC 		"FUJITSU PalmSecure Sensor driver"
#define DRIVER_VERSION		"V31L04"
#define DRIVER_LICENSE		"GPL v2"

//#define CONFIG_FJVEINCAM_DEBUG
#define errlog(format, arg...) \
		printk(KERN_ERR DRIVER_NAME ": " format "\n", ## arg);
#ifdef CONFIG_FJVEINCAM_DEBUG
#define dbglog(format, arg...) \
		printk(KERN_DEBUG __FILE__":%d %s: " format "\n", \
		__LINE__, __FUNCTION__, ## arg);
#else
#define dbglog(format, arg...)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0)
#define file_inode(file)	(file)->f_dentry->d_inode
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,11,0)
#define CURRENT_TIME		current_time(file_inode(file))
#endif

/* Endpoint direction check macros */
#define IS_EP_BULK(ep) \
		((ep)->bmAttributes == USB_ENDPOINT_XFER_BULK ? 1 : 0)
#define IS_EP_BULK_IN(ep) (IS_EP_BULK(ep) && \
		((ep)->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN)
#define IS_EP_BULK_OUT(ep) (IS_EP_BULK(ep) && \
		((ep)->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT)

/* minor number defines */
#ifdef CONFIG_USB_DYNAMIC_MINORS
#define USB_FJVEINCAM_MINOR_BASE	0
#else
#define USB_FJVEINCAM_MINOR_BASE	160
#endif

/* Waiting time for sensor confirming. */
/* Change this value when the time-out happens
   before the sensor confirming ends. */
#define SENSOR_CONFIRMED_WAIT_TIME	100

/* Read timeouts -- R_NAK_TIMEOUT * R_EXPIRE = Number of seconds */
#define R_NAK_TIMEOUT	5000
#define R_EXPIRE	1

/* Write timeouts */
#define W_NAK_TIMEOUT	5000

/* Ioctl timeouts */
#define C_NAK_TIMEOUT	10000

/* Allocate buffer byte size */
#define IBUF_SIZE	32768
#define OBUF_SIZE	4096
#define CBUF_SIZE	1024

/* Flag of sensor state of use */
#define SENSOR_NOT_CONFIRMED	0	/* Sensor is not used or
									   is in phase of confirming. */
#define SENSOR_CONFIRMED		1	/* Sensor is now used */


/* table of devices that work with this driver */
static struct usb_device_id fjveincam_device_ids [] = {
	{ USB_DEVICE(0x04C5, 0x1084) },
	{ USB_DEVICE(0x04C5, 0x125a) },
	{ USB_DEVICE(0x04C5, 0x1526) },
	{ USB_DEVICE(0x04C5, 0x1527) },
	{ }								/* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, fjveincam_device_ids);


static DEFINE_MUTEX(fjveincam_mutex);	/* Initializes to unlocked */

struct fjveincam_usb_data {
	struct usb_device *udev;
	unsigned char fjveincam_minor;	/* minor number -
									   used in disconnect() */
	char confirmed; 				/* Not zero if the device is used
									   (Not in phase of confirming) */
	int  open_count;				/* count the number of openers */
	char *obuf, *ibuf, *cbuf;		/* transfer buffers */
	char bulk_in_ep;				/* Endpoint assignments */
	char bulk_out_ep;				/* Endpoint assignments */
	wait_queue_head_t wait_q;		/* wait-queue for checking
									   sensors */
	struct mutex io_mutex;			/* lock to prevent concurrent
									   reads or writes */
	int o_timeout;					/* counter of open time out */
	int r_error;					/* counter of read error */
	int r_lasterr;					/* read last error */
	int w_error;					/* counter of write error */
	int w_lasterr;					/* write last error */
};

static struct usb_driver usb_fjveincam_driver;


static int usb_fjveincam_open(
	struct inode *inode, struct file *file)
{

	struct fjveincam_usb_data *fjveincam;
	struct usb_interface *intf;

	int fjveincam_minor;

	int err = 0;
	long wait;

	mutex_lock(&fjveincam_mutex);

	fjveincam_minor = iminor(inode);

	dbglog("minor:%d", fjveincam_minor);

	intf = usb_find_interface(&usb_fjveincam_driver, fjveincam_minor);
	if (!intf) {
		dbglog("minor:%d Unable to access minor data.",
				fjveincam_minor);
		mutex_unlock(&fjveincam_mutex);
		return -ENODEV;
	}

	fjveincam = usb_get_intfdata(intf);
	if ((!fjveincam) || (!fjveincam->udev)) {
		errlog("open(%d): Device not present.",
				fjveincam_minor);
		mutex_unlock(&fjveincam_mutex);
		return -ENODEV;
	}

	mutex_lock(&(fjveincam->io_mutex));

	if (fjveincam->open_count) {
		/* Another process has opened. */
		if (fjveincam->confirmed == SENSOR_CONFIRMED) {
			/* The sensor was confirmed. */
			dbglog("minor:%d Device is already open.",
					fjveincam_minor);
			err = -EBUSY;
			goto out_error;
		}

		mutex_unlock(&(fjveincam->io_mutex));

		/* Wait until the sensor is confirmed or closed,
		   because another process is open. */
		/* Change SENSOR_CONFIRMED_WAIT_TIME value when the time-out
		   happens before the sensor is confirmed. */
		wait = wait_event_interruptible_timeout(fjveincam->wait_q,
				(!fjveincam->open_count) ||
				(fjveincam->confirmed == SENSOR_CONFIRMED),
				SENSOR_CONFIRMED_WAIT_TIME);

		mutex_lock(&(fjveincam->io_mutex));
		if (wait == 0) {
			/* Time-out happens before the sensor is confirmed. */
			dbglog("minor:%d Sensor confirmed Time-out.",
					fjveincam_minor);
			fjveincam->o_timeout++;
			fjveincam->confirmed=SENSOR_CONFIRMED;
			err = -EBUSY;
			goto out_error;
		}
		else if (fjveincam->confirmed==SENSOR_CONFIRMED) {
			/* Another process completed the sensor confirming,
			   and started the use of the sensor. */
			dbglog("minor:%d Device is already open.",
					fjveincam_minor);
			err = -EBUSY;
			goto out_error;
		}
		else if(wait == -ERESTARTSYS) {
			err = -ERESTARTSYS;
			goto out_error;
		}
		/* else {
			// Another process closed the sensor.
		} */
	}

	init_waitqueue_head(&fjveincam->wait_q);
	fjveincam->open_count = 1;
	/* Used by the read and write methods */
	file->private_data = fjveincam;

out_error:
	mutex_unlock(&(fjveincam->io_mutex));

	mutex_unlock(&fjveincam_mutex);

	return err;

}

static int usb_fjveincam_close(
	struct inode *inode, struct file *file)
{
	struct fjveincam_usb_data *fjveincam = file->private_data;

	mutex_lock(&(fjveincam->io_mutex));

	fjveincam->confirmed = SENSOR_NOT_CONFIRMED;

	fjveincam->open_count = 0;

	file->private_data = NULL;

	if (!fjveincam->udev) {
		/* The device was unplugged while open - need to clean up */
		dbglog("minor:%d delayed de-allocating",
				fjveincam->fjveincam_minor);

		mutex_unlock(&(fjveincam->io_mutex));

		kfree(fjveincam->cbuf);
		kfree(fjveincam->ibuf);
		kfree(fjveincam->obuf);
		kfree(fjveincam);

		return 0;
	}

	/* Wake_up the process waiting in open() function. */
	wake_up_interruptible(&fjveincam->wait_q);

	dbglog("minor:%d", fjveincam->fjveincam_minor);

	mutex_unlock(&(fjveincam->io_mutex));

	return 0;
}

static ssize_t usb_fjveincam_read(
		struct file *file, char *buffer, size_t count, loff_t *ppos)
{
	struct fjveincam_usb_data *fjveincam = file->private_data;
	struct usb_device *dev;

	ssize_t bytes_read = 0; /* Overall count of bytes_read */
	ssize_t ret = 0;

	int fjveincam_minor;
	int partial;		/* Number of bytes successfully read */
	int this_read;		/* Max number of bytes to read */
	int result;
	int r_expire = R_EXPIRE;

	char *ibuf;


	mutex_lock(&(fjveincam->io_mutex));

	fjveincam_minor = fjveincam->fjveincam_minor;

	dev = fjveincam->udev;
	if (!dev) {
		/* The device was unplugged before the file was released */
		errlog("read(%d): Device was unplugged.", fjveincam_minor);
		ret = -ENODEV;
		goto out_error;
	}

	ibuf = fjveincam->ibuf;

	/* Update the atime of the device node */
	file_inode(file)->i_atime = CURRENT_TIME;

	while (count > 0) {
		if (signal_pending(current)) {
			dbglog("read(%d): Signal detection.", fjveincam_minor);
			ret = -ERESTARTSYS;
			break;
		}

		this_read = (count >= IBUF_SIZE) ? IBUF_SIZE : count;

		result = usb_bulk_msg(dev,
				usb_rcvbulkpipe(dev, fjveincam->bulk_in_ep),
				ibuf, this_read, &partial, R_NAK_TIMEOUT);
		dbglog("minor:%d result:%d this_read:%d partial:%d count:%ld",
				fjveincam_minor, result, this_read, partial, count);

		fjveincam->r_lasterr = result;
		if (result == -ETIMEDOUT) { /* NAK */
			fjveincam->r_error++;
			if (!partial) { /* No data */
				if (--r_expire <= 0) { /* Give it up */
					dbglog("read(%d): Excessive NAK's received.",
							fjveincam_minor);
					ret = result;
					break;
				} else { /* Keep trying to read data */
					schedule_timeout(R_NAK_TIMEOUT);
					continue;
				}
			} else { /* Timeout w/ some data */
				goto data_recvd;
			}
		}

		if (result == -EPIPE) { /* No hope */
			fjveincam->r_error++;
			if(usb_clear_halt(dev, fjveincam->bulk_in_ep)) {
				errlog("read(%d): "
						"Failure to clear endpoint halt condition.",
						fjveincam_minor);
			}
			ret = result;
			break;
		} else if ((result < 0) && (result != -EREMOTEIO)) {
			fjveincam->r_error++;
			dbglog("read(%d): An error occered: %d.",
					fjveincam_minor, result);
			ret = -EIO;
			break;
		}

data_recvd:

		if (partial) { /* Data returned */
			if (copy_to_user(buffer, ibuf, partial)) {
				errlog("read(%d): Failure to copy_to_user. size:%d.",
						fjveincam_minor, partial);
				ret = -EFAULT;
				break;
			}
			count -= partial; /* Compensate for short reads */
			bytes_read += partial;
			/* Keep tally of what actually was read */
			buffer += partial;
		} else {
			ret = 0;
			break;
		}
	}

out_error:

	dbglog("minor:%d ret:%ld bytes_read:%ld count:%ld",
			fjveincam_minor, ret, bytes_read, count);

	mutex_unlock(&(fjveincam->io_mutex));

	return ret ? ret : bytes_read;
}

static ssize_t usb_fjveincam_write(
		struct file *file, const char *buffer,
		size_t count, loff_t *ppos)
{
	struct fjveincam_usb_data *fjveincam = file->private_data;
	struct usb_device *dev;

	ssize_t bytes_written = 0; /* Overall count of bytes written */
	ssize_t ret = 0;

	int fjveincam_minor;
	int this_write; 	/* Number of bytes to write */
	int partial;		/* Number of bytes successfully written */
	int result = 0;

	char *obuf;

	mutex_lock(&(fjveincam->io_mutex));

	fjveincam_minor = fjveincam->fjveincam_minor;

	dev = fjveincam->udev;
	if (!dev) {
		errlog("write(%d): Device was unplugged.", fjveincam_minor);
		ret = -ENODEV;
		goto out_error;
	}

	obuf = fjveincam->obuf;
	file_inode(file)->i_atime = CURRENT_TIME;

	while (count > 0) {
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}

		this_write = (count >= OBUF_SIZE) ? OBUF_SIZE : count;

		if (copy_from_user(fjveincam->obuf, buffer, this_write)) {
			ret = -EFAULT;
			break;
		}

		result = usb_bulk_msg(dev,
				usb_sndbulkpipe(dev, fjveincam->bulk_out_ep),
				obuf, this_write, &partial, W_NAK_TIMEOUT);
		dbglog("minor:%d result:%d this_write:%d partial:%d",
				fjveincam_minor, result, this_write, partial);

		fjveincam->w_lasterr = result;
		if (result == -ETIMEDOUT) { /* NAK */
			dbglog("write(%d): Excessive NAK's received.",
					fjveincam_minor);
			fjveincam->w_error++;
			ret = result;
			break;
		} else if (result < 0) { /* We should not get any I/O errors */
			dbglog("write(%d): An error occered: %d.",
					fjveincam_minor, result);
			fjveincam->w_error++;
			ret = -EIO;
			break;
		}

		/* Unable to write all contents of obuf */
		if (partial != this_write) {
			fjveincam->w_error++;
			ret = -EIO;
			break;
		}

		if (partial) {	/* Data written */
			buffer += partial;
			count -= partial;
			bytes_written += partial;
		} else {		/* No data written */
			ret = 0;
			break;
		}
	}

out_error:

	mutex_unlock(&(fjveincam->io_mutex));

	return ret ? ret : bytes_written;
}

static long usb_fjveincam_ioctl(
	struct file *file, uint cmd, ulong arg)
{
	struct fjveincam_usb_data *fjveincam = file->private_data;
	struct usb_device *dev;

	int fjveincam_minor;
	int retval = 0;

	mutex_lock(&(fjveincam->io_mutex));

	fjveincam_minor = fjveincam->fjveincam_minor;

	dbglog("minor:%d cmd:%x arg:%p", fjveincam_minor, cmd, (void *)arg);

	if (!fjveincam->udev) {
		errlog("ioctl(%d): Device was unplugged.", fjveincam_minor);
		retval = -ENODEV;
		goto out_error;
	}

	switch (_IOC_NR(cmd))
	{
	  case FJPV_IOCTL_CTRLMSG:
	  {
		struct fjveincam_cmsg user_cmsg;
		struct {
			struct usb_ctrlrequest req;
			unsigned char *data;
		} cmsg;
		int pipe, nb, ret;
		unsigned char *buf = (unsigned char *)fjveincam->cbuf;

		dev = fjveincam->udev;

		if (copy_from_user(&user_cmsg, (void *)arg,
				sizeof(user_cmsg))) {
			retval = -EFAULT;
			break;
		}
		cmsg.req.bRequestType	= user_cmsg.req.bRequestType;
		cmsg.req.bRequest		= user_cmsg.req.bRequest;
		cmsg.req.wValue 		= user_cmsg.req.wValue;
		cmsg.req.wIndex 		= user_cmsg.req.wIndex;
		cmsg.req.wLength		= user_cmsg.req.wLength;
		cmsg.data				= user_cmsg.data;

		nb = cmsg.req.wLength;

		if (nb > CBUF_SIZE) {
			retval = -EINVAL;
			break;
		}

		if ((cmsg.req.bRequestType & USB_ENDPOINT_DIR_MASK) == 0) {
			pipe = usb_sndctrlpipe(dev, 0);
			if (nb > 0 && copy_from_user(buf, cmsg.data, nb)) {
				retval = -EFAULT;
				break;
			}
		} else {
			pipe = usb_rcvctrlpipe(dev, 0);
		}

		ret = usb_control_msg(dev, pipe,
				cmsg.req.bRequest,
				cmsg.req.bRequestType,
				cmsg.req.wValue,
				cmsg.req.wIndex,
				buf, nb, C_NAK_TIMEOUT);

		dbglog("minor:%d request result:%d "
				"cmd[%02X:%04X:%04X:%04X] rsp[%02X:%02X:%02X:%02X]",
				fjveincam_minor, ret, cmsg.req.bRequest,
				cmsg.req.wValue, cmsg.req.wIndex, cmsg.req.wLength,
				buf[0], buf[1], buf[2], buf[3]);

		if (ret < 0) {
			errlog("ioctl(%d): An error occered: %d.",
					fjveincam_minor, ret);
			retval = -EIO;
			break;
		}

		if (nb < ret) {
			ret = nb;
		}
		if (nb > 0 && (cmsg.req.bRequestType & USB_ENDPOINT_DIR_MASK) &&
				copy_to_user(cmsg.data, buf, ret)) {
			retval = -EFAULT;
		}

		break;
	  }

	  case FJPV_IOCTL_CHECK:
		/* nop */
		break;

	  /* Notification of the end of sensor confirming. */
	  case FJPV_IOCTL_CONFIRM:
	  {
		/* Sensor confirming was completed,
		   and started the use of the sensor. */
		fjveincam->confirmed = SENSOR_CONFIRMED;
		/* Wake_up the process waiting in open() function. */
		wake_up_interruptible(&fjveincam->wait_q);
		dbglog("minor:%d Sensor was checked.", fjveincam_minor);
		break;
	  }

	  case FJPV_IOCTL_INFO:
	  {
		struct fjveincam_info info;

		/* Magic number for indicating
		   Fujitsu Palmsecure sensor driver. */
		info.magic		= FJPV_MAGIC;
		info.minor		= fjveincam_minor;
		info.o_timeout	= fjveincam->o_timeout;
		info.r_error	= fjveincam->r_error;
		info.r_lasterr	= fjveincam->r_lasterr;
		info.w_error	= fjveincam->w_error;
		info.w_lasterr	= fjveincam->w_lasterr;
		strncpy((char*)info.version, DRIVER_VERSION,
				sizeof(info.version));
		if (copy_to_user((void *)arg, &info, sizeof(info)))
			retval = -EFAULT;

		break;
	  }

	  default:
		dbglog("minor:%d invalid request code:%x",
				fjveincam_minor, cmd);
		retval = -ENOIOCTLCMD;
		break;
	}

out_error:

	mutex_unlock(&(fjveincam->io_mutex));

	dbglog("minor:%d ret=%d", fjveincam_minor, retval);

	return retval;
}

static struct file_operations usb_fjveincam_fops = {
	.owner			= THIS_MODULE,
	.read			= usb_fjveincam_read,
	.write			= usb_fjveincam_write,
	.unlocked_ioctl	= usb_fjveincam_ioctl,
	.open			= usb_fjveincam_open,
	.release		= usb_fjveincam_close,
};

static struct usb_class_driver fjveincam_class = {
	.name			= "usb/fjveincam%d",
	.fops			= &usb_fjveincam_fops,
	.minor_base		= USB_FJVEINCAM_MINOR_BASE,
};

static int usb_fjveincam_probe(
		struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct fjveincam_usb_data *fjveincam;
	struct usb_host_interface *interface;
	struct usb_endpoint_descriptor *endpoint;

	int ep_cnt;
	int retval;

	char have_bulk_in, have_bulk_out;
	char name[20];

	dbglog("vendor id 0x%x, device id 0x%x, portnum:%d",
			 dev->descriptor.idVendor, dev->descriptor.idProduct,
			 dev->portnum);

	/*
	 * After this point we can be a little noisy about what
	 * we are trying to configure.
	 */

	if (dev->descriptor.bNumConfigurations != 1) {
		dbglog("Only one device configuration is supported.");
		return -ENODEV;
	}

	/*
	 * Start checking for two bulk endpoints.
	 */

	interface = &intf->altsetting[0];

	dbglog("Number of Endpoints:%d",
			(int) interface->desc.bNumEndpoints);

	if (interface->desc.bNumEndpoints != 2) {
		dbglog("Only two endpoints supported.");
		return -EIO;
	}

	ep_cnt = have_bulk_in = have_bulk_out = 0;

	while (ep_cnt < interface->desc.bNumEndpoints) {
		endpoint = &interface->endpoint[ep_cnt].desc;

		if (!have_bulk_in && IS_EP_BULK_IN(endpoint)) {
			ep_cnt++;
			have_bulk_in = endpoint->bEndpointAddress &
					USB_ENDPOINT_NUMBER_MASK;
			dbglog("bulk_in_ep:%d", have_bulk_in);
			continue;
		}

		if (!have_bulk_out && IS_EP_BULK_OUT(endpoint)) {
			ep_cnt++;
			have_bulk_out = endpoint->bEndpointAddress &
					USB_ENDPOINT_NUMBER_MASK;
			dbglog("bulk_out_ep:%d", have_bulk_out);
			continue;
		}

		dbglog("Detected endpoint is not bulk endpoint.");
		/* Shouldn't ever get here unless we have something weird */
		return -EIO;
	}

	/*
	 * Perform a quick check to make sure that everything worked as it
	 * should have.
	 */

	if (!have_bulk_in || !have_bulk_out) {
		dbglog("Bulk endpoints of both in and out is required.");
		return -EIO;
	}

	/*
	 * Determine a minor number and initialize the structure
	 * associated with it.
	 */
	if (!(fjveincam = kzalloc(sizeof (struct fjveincam_usb_data),
			GFP_KERNEL))) {
		errlog("probe(port-%d): Not enough memory "
				"for the minor data.", dev->portnum);
		return -ENOMEM;
	}
	mutex_init(&(fjveincam->io_mutex)); /* Initializes to unlocked */

	/* Ok, now initialize all the relevant values */
	if (!(fjveincam->obuf = (char *)kmalloc(OBUF_SIZE, GFP_KERNEL))) {
		errlog("probe(port-%d): Not enough memory "
				"for the output buffer.", dev->portnum);
		kfree(fjveincam);
		return -ENOMEM;
	}

	if (!(fjveincam->ibuf = (char *)kmalloc(IBUF_SIZE, GFP_KERNEL))) {
		errlog("probe(port-%d): Not enough memory "
				"for the input buffer.", dev->portnum);
		kfree(fjveincam->obuf);
		kfree(fjveincam);
		return -ENOMEM;
	}

	if (!(fjveincam->cbuf = (char *)kmalloc(CBUF_SIZE, GFP_KERNEL))) {
		errlog("probe(port-%d): Not enough memory "
				"for the control buffer.", dev->portnum);
		kfree(fjveincam->obuf);
		kfree(fjveincam->ibuf);
		kfree(fjveincam);
		return -ENOMEM;
	}

	usb_get_dev(dev);
	fjveincam->bulk_in_ep	= have_bulk_in;
	fjveincam->bulk_out_ep	= have_bulk_out;
	fjveincam->udev			= dev;
	fjveincam->open_count	= 0;
	fjveincam->confirmed	= SENSOR_NOT_CONFIRMED;

	usb_set_intfdata(intf, fjveincam);

	retval = usb_register_dev(intf, &fjveincam_class);
	if (retval) {
		errlog("probe(port-%d): Not able to get a minor "
				"for this device.", dev->portnum);
		usb_set_intfdata(intf, NULL);
		kfree(fjveincam->cbuf);
		kfree(fjveincam->ibuf);
		kfree(fjveincam->obuf);
		kfree(fjveincam);
		return -ENOMEM;
	}

	dbglog("Allocated minor:%d", intf->minor);
	fjveincam->fjveincam_minor = intf->minor;

	snprintf(name, sizeof(name), fjveincam_class.name,
			intf->minor - fjveincam_class.minor_base);
	dev_info(&intf->dev,
			"USB PalmVeinCam device now attached to %s\n", name);

	return 0;
}

static void usb_fjveincam_disconnect(
		struct usb_interface *interface)
{
	struct fjveincam_usb_data *fjveincam = usb_get_intfdata(interface);
	int fjveincam_minor = interface->minor;

	usb_set_intfdata(interface, NULL);

	/* give back our minor */
	usb_deregister_dev (interface, &fjveincam_class);

	/* If there is a process in open(), wait for return. */
	mutex_lock(&fjveincam_mutex);
	mutex_lock(&(fjveincam->io_mutex));

	dev_info(&interface->dev,
			"USB PalmVeinCam #%d now disconnected\n",
			(fjveincam_minor - fjveincam_class.minor_base));

	usb_driver_release_interface(&usb_fjveincam_driver,
			fjveincam->udev->actconfig->interface[0]);

	if (fjveincam->open_count) {
		/* The device is still open - cleanup must be delayed */
		dbglog("minor:%d The device was unplugged while open",
				fjveincam_minor);
		fjveincam->udev = 0;
		mutex_unlock(&(fjveincam->io_mutex));
		mutex_unlock(&fjveincam_mutex);
		return;
	}

	dbglog("minor:%d De-allocating", fjveincam_minor);

	kfree(fjveincam->cbuf);
	kfree(fjveincam->ibuf);
	kfree(fjveincam->obuf);
	mutex_unlock(&(fjveincam->io_mutex));
	kfree(fjveincam);
	mutex_unlock(&fjveincam_mutex);
}

static struct usb_driver usb_fjveincam_driver = {
	.name			= DRIVER_NAME,
	.probe			= usb_fjveincam_probe,
	.disconnect		= usb_fjveincam_disconnect,
	.id_table		= fjveincam_device_ids,
	.no_dynamic_id	= 1
};

static int __init usb_fjveincam_init(void)
{
	int result;

	/* register this driver with the USB subsystem */
	result = usb_register(&usb_fjveincam_driver);
	if (result)
		errlog("usb_register failed. Error number %d", result);

	dbglog("register driver");
	return result;
}

static void __exit usb_fjveincam_exit(void)
{
	/* deregister this driver with the USB subsystem */
	usb_deregister(&usb_fjveincam_driver);
	dbglog("remove driver");
}

module_init(usb_fjveincam_init);
module_exit(usb_fjveincam_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE(DRIVER_LICENSE);
