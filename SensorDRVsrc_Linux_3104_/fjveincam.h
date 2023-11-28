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
 * 2015-02-04 - V31L02
 *	 - first version
 * 2016-11-02 - V31L03
 *	 - supported PalmSecure-F Pro
 *
 */

#ifndef _FJVEINCAM_
#define _FJVEINCAM_

/*----------------------------------------------------------------------*/
/* ioctl																*/
/*----------------------------------------------------------------------*/

#define FJPV_IOCTL_CTRLMSG	0x01
#define FJPV_IOCTL_CHECK	0x02
#define FJPV_IOCTL_INFO		0x03
#define FJPV_IOCTL_CONFIRM	0x04

// Berore V30 Authentication Library use.
#define USB_FJVEINCAMV30_IOCTL_CTRLMSG 	FJPV_IOCTL_CTRLMSG
#define USB_FJVEINCAMV30_IOCTL_CHECK	FJPV_IOCTL_CHECK
#define USB_FJVEINCAMV30_IOCTL_INFO		FJPV_IOCTL_INFO
#define USB_FJVEINCAMV30_IOCTL_CONFIRM 	FJPV_IOCTL_CONFIRM

// V31 Authentication Library or later version use.
#define FJPV_IOCTL_MAGIC	0xB4
#define USB_FJVEINCAM_IOCTL_CTRLMSG 	_IOWR(FJPV_IOCTL_MAGIC, \
		FJPV_IOCTL_CTRLMSG, struct fjveincam_cmsg)
#define USB_FJVEINCAM_IOCTL_CHECK		_IO  (FJPV_IOCTL_MAGIC, \
		FJPV_IOCTL_CHECK)
#define USB_FJVEINCAM_IOCTL_INFO		_IOR (FJPV_IOCTL_MAGIC, \
		FJPV_IOCTL_INFO, struct fjveincam_info)
#define USB_FJVEINCAM_IOCTL_CONFIRM 	_IO  (FJPV_IOCTL_MAGIC, \
		FJPV_IOCTL_CONFIRM)

/* Magic number for Fujitsu Palmsecure sensor driver. */
#define FJPV_MAGIC	0x464A5056

/* for USB_FJVEINCAM_IOCTL_CTRLMSG */

struct fjveincam_cmsg {
	struct {
		unsigned char bRequestType;
		unsigned char bRequest;
		unsigned short wValue;
		unsigned short wIndex;
		unsigned short wLength;
	} req;						/* USB device control request data */
	void *data; 				/* response data area pointer */
};

/* for USB_FJVEINCAM_IOCTL_CHECK */

	/* no structure */

/* for USB_FJVEINCAM_IOCTL_INFO */

struct fjveincam_info {
	int magic;					/* Magic number for indicating
								   Fujitsu Palmsecure sensor driver. */
	int minor;					/* minor number */
	int o_timeout;				/* counter of open time out */
	int r_error;				/* counter of read error */
	int r_lasterr;				/* read last error */
	int w_error;				/* counter of write error */
	int w_lasterr;				/* write last error */
	unsigned char version[8];	/* device driver version string */
};

#endif	/* _FJVEINCAM_ */
