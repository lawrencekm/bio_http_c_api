// Copyright 2018 FUJITSU FRONTECH LIMITED
/*-----------------------------------------------------------------------
 * File   : PvAPI_ERR.H
 *
 * Update : 2006.02.03
 *          2016.10.11 V33-220
 *          2017.04.19 V33-300
 *          2018.02.02 V34-040
 *-----------------------------------------------------------------------
 */

#ifndef _PVAPIERR_H_
#define _PVAPIERR_H_


/*
  ----------------------------------------------------------
	PvAPI Error Level
  ----------------------------------------------------------
*/
#define PvAPI_ERROR_LEVEL_NORMAL			(0x00000000)
/* Normal */

#define PvAPI_ERROR_LEVEL_CANCEL			(0x00000001)
/* Cancel */

#define PvAPI_ERROR_LEVEL_ERROR				(0x00000002)
/* Error. It is possible to recovery. */

#define PvAPI_ERROR_LEVEL_FAILED			(0x00000003)
/* Error. It is impossible to recovery. */


/*
  ----------------------------------------------------------
	PvAPI Error Factor
  ----------------------------------------------------------
*/
#define PvAPI_ERROR_CODE_DEVICE				(0x00000001)
/* Device error */

#define PvAPI_ERROR_CODE_RESOURCE			(0x00000002)
/* Resource error */

#define PvAPI_ERROR_CODE_USER				(0x00000003)
/* Usage error */

#define PvAPI_ERROR_CODE_OTHER				(0x00000004)
/* Other error */


/*
  ----------------------------------------------------------
	PvAPI Error Detail
  ----------------------------------------------------------
*/
/*
 *  It is possible to recovery.
 */
#define PvAPI_ERROR_DETAIL_TEMPERATURE		(0x02010001)
/* Abnormal temperature */

#define PvAPI_ERROR_DETAIL_DEVICE_OFF		(0x02010002)
/* Device off */

#define PvAPI_ERROR_DETAIL_NO_DEVICE		(0x02010003)
/* No device */

#define PvAPI_ERROR_DETAIL_SENSOR_FUNC		(0x02010007)
/* Sensor not have the function */

#define PvAPI_ERROR_DETAIL_SENSOR_READ		(0x02010008)
/* Sensor read error */

#define PvAPI_ERROR_DETAIL_SENSOR_WRITE		(0x02010009)
/* Sensor write error */

#define PvAPI_ERROR_DETAIL_PARAMETER		(0x02030001)
/* Parameter error */

#define PvAPI_ERROR_DETAIL_SEQUENCE			(0x02030002)
/* Sequence error */

#define PvAPI_ERROR_DETAIL_AUTHENTICATE		(0x02030003)
/* Authentication error */

#define PvAPI_ERROR_DETAIL_UUID				(0x02030004)
/* UUID error */

#define PvAPI_ERROR_DETAIL_HANDLE			(0x02030005)
/* HANDLE error */

#define PvAPI_ERROR_DETAIL_CALLBACK			(0x02030006)
/* Callback function is not set */

#define PvAPI_ERROR_DETAIL_ATTACH_OVER		(0x02030007)
/* Exceeded maximum number */

#define PvAPI_ERROR_DETAIL_MULTIPLE_CALLED	(0x02030008)
/* Multiple called */

#define PvAPI_ERROR_DETAIL_BIR				(0x02030009)
/* Abnormal BIR */

#define PvAPI_ERROR_DETAIL_DATA_ERROR		(0x0203000A)
/* Abnormal data */


#define PvAPI_ERROR_DETAIL_TIMEOUT			(0x02040001)
/* Timeout */

#define PvAPI_ERROR_DETAIL_NOT_CANCELED		(0x02040002)
/* It is impossible to cancel */

#define PvAPI_ERROR_DETAIL_ERROR_INI_FILE	(0x02040003)
/* Environmental setting error */


/*
 *  It is impossible to recover.
 */
#define PvAPI_ERROR_DETAIL_DEVICE_ERROR		(0x03010001)
/* Device error */

#define PvAPI_ERROR_DETAIL_SENSOR_ALARM		(0x03010002)
/* Sensor alarm error */

#define PvAPI_ERROR_DETAIL_SENSOR_AUTH		(0x03010003)
/* Sensor authentication error */


#define PvAPI_ERROR_DETAIL_MALLOC			(0x03020001)
/* Cannot allocate memory */

#define PvAPI_ERROR_DETAIL_RECOURCE_GET		(0x03020002)
/* Cannot get resource */

#define PvAPI_ERROR_DETAIL_RECOURCE_CTRL	(0x03020003)
/* Cannot manipulate resource */


#define PvAPI_ERROR_DETAIL_BAD_AREA			(0x03030001)
/* Memory Area error */

#define PvAPI_ERROR_DETAIL_CALLBACK_ERROR	(0x03030002)
/* Callback function error / Contradiction occured */


#define PvAPI_ERROR_DETAIL_INTERNAL_ERROR	(0x03040001)
/* Internal error */

#define PvAPI_ERROR_DETAIL_FAILED_INI_FILE	(0x03040002)
/* Environmental setting error */


/*
  ----------------------------------------------------------
	PvAPI Error Module
  ----------------------------------------------------------
*/
#define PvAPI_ERROR_MODULE_IF				(0x00000001)
/* Interface part */

#define PvAPI_ERROR_MODULE_LIBRARY			(0x00000002)
/* Authentication library */



#endif /* _PVAPIERR_H_ */
