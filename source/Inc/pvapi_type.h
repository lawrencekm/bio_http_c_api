// Copyright 2021 FUJITSU FRONTECH LIMITED
/*-----------------------------------------------------------------------
 * File   : PvAPI_TYPE.H
 *
 * Update : 2006.02.03 New
 *          2006.02.27 Message change.
 *          2006.04.06 Linux support.
 *          2006.05.18 V11
 *          2006.12.13 V20
 *          2007.04.04 V20-030
 *          2007.12.25 V24-010
 *          2008.01.19 V24-010
 *          2008.01.22 V24-010
 *          2008.02.21 V24-100
 *          2008.04.16 V24-100
 *          2008.12.16 V27-010
 *          2009.03.18 V27-030
 *          2009.08.06 V30-010
 *          2009.08.26 V30-010
 *          2009.09.15 V30-030
 *          2009.10.07 V30-040
 *          2010.09.28 V30-220
 *          2010.10.13 V30-220
 *          2010.10.21 V30-220
 *          2011.05.23 V30-300
 *          2011.06.07 V30-300
 *          2011.06.23 V30-300
 *          2011.08.04 V30-310
 *          2011.09.29 V30-310
 *          2011.12.01 V31-010
 *          2012.01.17 V31-010
 *          2012.01.18 V31-010
 *          2012.01.19 V31-010
 *          2012.01.24 V31-010
 *          2012.01.26 V31-010
 *          2012.02.28 V31-010
 *          2012.03.09 V31-012
 *          2012.03.09 V31-020
 *          2012.04.04 V31-012
 *          2012.04.24 V31-020
 *          2012.09.26 V31-100
 *          2012.11.05 V31-200
 *          2013.01.16 V31-200
 *          2013.02.05 V31-200
 *          2013.02.28 V31-200
 *          2013.06.18 V32-010
 *          2013.07.18 V32-010
 *          2013.12.02 V32-110
 *          2014.05.13 V32-200
 *          2014.10.17 V33-010
 *          2014.10.27 V33-010
 *          2014.12.17 V33-020
 *          2015.10.08 V33-201
 *          2016.02.15 V33-202
 *          2016.03.02 V33-203
 *          2016.06.02 V33-300
 *          2016.06.06 V33-210
 *          2016.10.11 V33-220
 *          2017.04.26 V33-300
 *          2017.06.29 V34-010
 *          2017.10.11 V34-020
 *          2018.01.11 V34-031
 *          2018.03.12 V34-040
 *          2018.04.11 V34-100
 *          2019.09.06 V34-150
 *          2019.11.21 V34-150
 *          2021.03.24 V34-211
 *          2021.12.24 V34-310
 *          2022.02.04 V34-310
 *-----------------------------------------------------------------------
 */

#ifndef _PVAPITYPE_H_
#define _PVAPITYPE_H_


#if defined(_WIN32)
	#ifdef _WIN64
		#define PvAPI_64BIT_OS_TARGET
	#endif
#elif defined(__x86_64__) || defined(__LP64__)
	#define PvAPI_64BIT_OS_TARGET
#endif

/*****************************************************************************
	PvAPI Services API Datatypes
*****************************************************************************/
#ifndef _DWORD_DEFINED
#define _DWORD_DEFINED
typedef	unsigned long					DWORD;
#endif

/***********************************************************
	PvAPI BIR
***********************************************************/
#ifdef PvAPI_64BIT_OS_TARGET
typedef struct pvapi_hrs_bir
{
	BioAPI_BIR_HEADER  Header;
	uint32 BiometricData;
	uint32 Signature;
} PvAPI_BIR, *PvAPI_BIR_PTR;
#else
typedef BioAPI_BIR  PvAPI_BIR, *PvAPI_BIR_PTR;
#endif

/***********************************************************
	PvAPI ErrorInfo
***********************************************************/
typedef struct t_PvAPI_ErrorInfo
{
	uint32 ErrorLevel;
	uint32 ErrorCode;
	uint32 ErrorDetail;
	uint32 ErrorModule;
	uint32 ErrorOptional1;
	uint32 ErrorOptional2;
	uint32 APIInfo[4];
	uint32 ErrorInfo1;
	uint32 ErrorInfo2;
	uint32 ErrorInfo3[4];
}PvAPI_ErrorInfo;


/***********************************************************
	PvAPI VLInfo
***********************************************************/
typedef struct t_PvAPI_VLInfo
{
	uint32 uiVersion;
	uint32 uiLevel;
	uint32 uiSubCounter;
	uint32 uiReserve;
} PvAPI_VLINFO_TBL,  *PvAPI_VLINFO_TBL_PTR;


/***********************************************************
	PvAPI DRInfo
***********************************************************/
typedef struct t_PvAPI_DRInfo
{
	sint32 iFVersion;
	sint32 iFLevel;
	sint8  szDVersion[16];
	uint32 uiCamera;
	uint32 uiReserve;
} PvAPI_DRINFO_TBL,  *PvAPI_DRINFO_TBL_PTR;


/***********************************************************
	PvAPI SensorInfo
***********************************************************/
typedef struct t_PvAPI_SensorInfo
{
	uint32 uiSerialNo;
	sint8  szUnitNo[128];
	uint32 uiSensor;
	void*  lpvReserve2;
} PvAPI_SensorInfo;


/***********************************************************
	PvAPI SensorInfoEx
***********************************************************/
typedef struct t_PvAPI_SensorInfoEx
{
	uint32 uiSerialNo;
	sint8  szUnitNo[128];
	uint32 uiSensor;
	uint32 uiFwVersion;
	uint32 uiFwLevel;
	sint8  szReserve[112];
} PvAPI_SensorInfoEx, *PvAPI_SensorInfoEx_PTR;


/***********************************************************
	PvAPI TemplateInfo
***********************************************************/
typedef struct t_PvAPI_TemplateInfo
{
	uint32 uiVersion;
	uint32 uiSensor;
	uint32 uiGuideMode;
	uint32 uiCompressMode;
	uint32 uiExtractKind;
	uint32 uiIndexKind;
	uint32 uiReserve1;	
	void*  lpvReserve2;
} PvAPI_TemplateInfo;


/***********************************************************
	PvAPI TemplateInfoEx
***********************************************************/
typedef struct t_PvAPI_TemplateInfoEx
{
	uint32 uiVersion;
	uint32 uiSensor;
	uint32 uiGuideMode;
	uint32 uiCompressMode;
	uint32 uiExtractKind;
	uint32 uiIndexKind;
	uint32 uiSensorExtKind;
	uint32 uiM2ExtInfo;
	uint32 uiDataExtInfo;
	uint32 uiGExtendedMode;
	uint32 auiReserve[6];
	uint32 auiMultiDataMode[2];
	sint8  szReserve[440];
}PvAPI_TemplateInfoEx, *PvAPI_TemplateInfoEx_PTR;


/***********************************************************
	PvAPI LBInfo
***********************************************************/
typedef struct t_PvAPI_LBInfo
{
	uint32 uiLibVersion;
	uint32 uiLibLevel;
	uint32 uiLibSubCounter;
	sint8  szDrvVersion[16];
	uint32 uiFwVersion;
	uint32 uiFwLevel;
	uint32 uiSensorKind;
	uint32 uiSensorExtKind;
	uint32 uiSerialNo;
	sint8  szUnitNo[16];
	uint32 uiLoopMode;
	uint32 uiCompressMode;

	uint32 uiDriverKind;
	uint32 uiEdition;

	sint8  szReserve[496];
}  PvAPI_LBINFO,  *PvAPI_LBINFO_PTR;


/***********************************************************
	PvAPI SharedCaptureDataInfo
***********************************************************/
typedef struct t_PvAPI_SharedCaptureDataInfo
{
	uint32 uiSharedMode;
	sint8  szCaptureSharedKey[16];
	uint32 uiReserve;
	sint8  szReserve[8];
}  PvAPI_SharedCaptureDataInfo;



/***********************************************************
	PvAPI Define
***********************************************************/
// PalmVein Biometoric data type.
#define	PvAPI_FACTOR_PALM_VEIN				(0x00010000)

//------------------------------------------
// MaxFRRRequested Matching level.
//------------------------------------------
#define	PvAPI_MATCHING_LEVEL_NORMAL			(0)				//Threshold levels - Standard
#define	PvAPI_MATCHING_LEVEL_HIGHEST		(1)				//Threshold levels - Highest
#define	PvAPI_MATCHING_LEVEL_HIGH			(2)				//Threshold levels - High
#define	PvAPI_MATCHING_LEVEL_LOW			(3)				//Threshold levels - Low
#define	PvAPI_MATCHING_LEVEL_LOWEST			(4)				//Threshold levels - Lowest



//------------------------------------------
// GuiState.
//------------------------------------------
#define PvAPI_APPEND_STREAMING				(0x0008)


//------------------------------------------
// Guide state message provided state.
//------------------------------------------
#define	PvAPI_NOTIFY_CAP_GUID_START			(0x02030000)	//Guide message - Guide start.
#define	PvAPI_NOTIFY_CAP_GUID_BADIMAGE		(0x02030200)	//Guide message - Move your hand away from the sensor.
#define	PvAPI_NOTIFY_CAP_GUID_MOVING		(0x02030203)	//Guide message - Stop moving your hand.
#define	PvAPI_NOTIFY_CAP_GUID_LESSINFO		(0x02030204)	//Guide message - Place your hand correctly.
#define	PvAPI_NOTIFY_CAP_GUID_RIGHT			(0x02030205)	//(Optional) Guide message - Move left.
#define	PvAPI_NOTIFY_CAP_GUID_LEFT			(0x02030206)	//(Optional) Guide message - Move right.
#define	PvAPI_NOTIFY_CAP_GUID_DOWN			(0x02030207)	//(Optional) Guide message - Move backward.
#define	PvAPI_NOTIFY_CAP_GUID_UP			(0x02030208)	//(Optional) Guide message - Move forward.
#define	PvAPI_NOTIFY_CAP_GUID_FAR			(0x02030209)	//Guide message - Bring your hand close.
#define	PvAPI_NOTIFY_CAP_GUID_NEAR			(0x0203020a)	//Guide message - Keep away your hand.
#define	PvAPI_NOTIFY_CAP_GUID_CAPTURING		(0x0203020b)	//Guide message - Now capturing.
#define	PvAPI_NOTIFY_CAP_GUID_LEAN			(0x0203020c)	//(Not Support) Guide message - Your hand has inclined.
#define	PvAPI_NOTIFY_CAP_GUID_PITCH_DOWN	(0x02030210)	//(Optional) Guide message - Your hand has pitched down.
#define	PvAPI_NOTIFY_CAP_GUID_PITCH_UP		(0x02030211)	//(Optional) Guide message - Your hand has pitched up.
#define	PvAPI_NOTIFY_CAP_GUID_ROLL_RIGHT	(0x02030212)	//(Optional) Guide message - Your hand has rolled right.
#define	PvAPI_NOTIFY_CAP_GUID_ROLL_LEFT		(0x02030213)	//(Optional) Guide message - Your hand has rolled left.
#define	PvAPI_NOTIFY_CAP_GUID_YAW_RIGHT		(0x02030214)	//(Optional) Guide message - Your hand has yaw right.
#define	PvAPI_NOTIFY_CAP_GUID_YAW_LEFT		(0x02030215)	//(Optional) Guide message - Your hand has yaw left.
#define	PvAPI_NOTIFY_CAP_GUID_CLOSE_FINGER	(0x02030216)	//(Optional) Guide message - Your fingers are closed.
#define	PvAPI_NOTIFY_CAP_GUID_ADJUST_LIGHT	(0x02030220)	//(Optional) Guide message - Adjust gain and retry.
#define	PvAPI_NOTIFY_CAP_GUID_ADJUST_NG		(0x02030221)	//(Optional) Guide message - Failed adjusting gain.
#define	PvAPI_NOTIFY_CAP_GUID_PHASE_END		(0x02030300)	//Guide message - Guide phase end.

#define	PvAPI_NOTIFY_CAP_GUID_NO_HANDS		(0x02030201)	//(Optional) Guide message - Set your hand.
#define	PvAPI_NOTIFY_CAP_GUID_ROUND			(0x02030217)	//(Optional) Guide message - Extend your hand flatly.

#define	PvAPI_NOTIFY_CAP_GUID_CAPTURE_IMAGE	(0x02030222)	//(Optional) Guide message - Captured image

#define	PvAPI_NOTIFY_CAP_GUID_LIGHT_NORMAL	(0x02030223)	//(Optional) Guide message - The lighting environment is normal
#define	PvAPI_NOTIFY_CAP_GUID_LIGHT_STRONG	(0x02030224)	//(Optional) Guide message - The lighting environment is strong

#define PvAPI_NOTIFY_CAP_GUID_TOO_FAR		(0x02030225)
#define PvAPI_NOTIFY_CAP_GUID_TOO_NEAR		(0x02030226)

#define	PvAPI_NOTIFY_SHUTTER				(0x02040000)
#define	PvAPI_NOTIFY_CAP_GUID_SHUTTER		(0x02040000)
#define	PvAPI_NOTIFY_WAIT_FOR_TRIGGER		(0x02040000)

#define	PvAPI_NOTIFY_API_KIND				(0x03000100)
#define	PvAPI_NOTIFY_API_END				(0x03000200)
#define	PvAPI_NOTIFY_MATCH_RESULT			(0x04000000)
#define	PvAPI_NOTIFY_REGIST_SCORE			(0x05000000)
#define	PvAPI_NOTIFY_CAPTURE_RANGE			(0x06000000)

#define PvAPI_NOTIFY_API_KIND_CAPTURE		(0x01)
#define PvAPI_NOTIFY_API_KIND_VERIFYMATCH	(0x02)
#define PvAPI_NOTIFY_API_KIND_IDENTIFYMATCH	(0x03)
#define PvAPI_NOTIFY_API_KIND_ENROLL		(0x04)
#define PvAPI_NOTIFY_API_KIND_VERIFY		(0x05)
#define PvAPI_NOTIFY_API_KIND_IDENTIFY		(0x06)

#define	PvAPI_NOTIFY_API_END_NORMAL			(0x00)
#define	PvAPI_NOTIFY_API_END_CANCEL			(0x10)
#define	PvAPI_NOTIFY_API_END_ERROR			(0x20)

#define PvAPI_REGIST_SCORE_QUALITY_1		(1)
#define PvAPI_REGIST_SCORE_QUALITY_2		(2)
#define PvAPI_REGIST_SCORE_QUALITY_3		(3)


//------------------------------------------
// SetProfile
//------------------------------------------
// SetProfile flag value.
#define	PvAPI_PROFILE_DISPLAY_KIND				(0x00000001)
#define	PvAPI_PROFILE_SENSOR_DIRECTION			(0x00000002)
#define	PvAPI_PROFILE_GUIDE_TYPE				(0x00000003)
#define	PvAPI_PROFILE_REGIST_DATA_TYPE			(0x00000004)
#define	PvAPI_PROFILE_SENSOR_TYPE				(0x00000005)
#define	PvAPI_PROFILE_REGIST_TEMPERATURE		(0x00000006)
#define	PvAPI_PROFILE_MATCH_TEMPERATURE			(0x00000007)
#define	PvAPI_PROFILE_MATCH_EXTRACT_KIND		(0x00000008)
#define	PvAPI_PROFILE_CARD_INFO					(0x00000009)
#define	PvAPI_PROFILE_CR_INFO					(0x0000000A)
#define	PvAPI_PROFILE_IDENTIFY_MODE				(0x0000000B)
#define	PvAPI_PROFILE_IDENTIFY_TRUNCATION_MODE	(0x0000000C)
#define PvAPI_PROFILE_ENROLL_INDEX_MODE			(0x0000000D)
#define	PvAPI_PROFILE_IMAGE						(0x0000000E)
#define	PvAPI_PROFILE_REGIST_EXTRACT_KIND		(0x0000000F)
#define	PvAPI_PROFILE_TRACE_MESSAGE				(0x00000010)
#define	PvAPI_PROFILE_GUIDE_MODE				(0x00000011)
#define PvAPI_PROFILE_CAPTURE_DATA_MODE			(0x00000013)
#define PvAPI_PROFILE_SCORE_NOTIFICATIONS		(0x00000014)
#define	PvAPI_PROFILE_GETGMODE					(0x00000015)
#define	PvAPI_PROFILE_RI_INFO					(0x00000016)
#define	PvAPI_PROFILE_CAPTURE_TIMES				(0x00000017)
#define	PvAPI_PROFILE_SL_EXTEND_MODE			(0x00000018)
#define PvAPI_PROFILE_CAPTURE_INV_SENSE			(0x0000001A)
#define	PvAPI_PROFILE_EXDATA_MODE				(0x0000001B)
#define	PvAPI_PROFILE_SHARED_CAPTURE_DATA		(0x0000001E)
// reserve										(0x0000001F)
#define	PvAPI_PROFILE_MULTIDATA_MODE			(0x00000020)
#define	PvAPI_PROFILE_MULTIDATA_SL_EXT_MODE		(0x00000021)

// SetProfile display kind dwParam value.
#define	PvAPI_PROFILE_DISPLAY_KIND_APL			(0x00000000)
#define	PvAPI_PROFILE_DISPLAY_KIND_LIB			(0x00000001)

// SetProfile sensor direction dwParam value.
#define	PvAPI_PROFILE_SENSOR_DIRECTION_0		(0x00000000)
#define	PvAPI_PROFILE_SENSOR_DIRECTION_90		(0x00000001)
#define	PvAPI_PROFILE_SENSOR_DIRECTION_180		(0x00000002)
#define	PvAPI_PROFILE_SENSOR_DIRECTION_270		(0x00000003)

// SetProfile guide type dwParam value.
#define	PvAPI_PROFILE_GUIDE_TYPE_NORMAL			(0x00000000)
#define	PvAPI_PROFILE_GUIDE_TYPE_NO_GUITE		(0x00000001)
#define	PvAPI_PROFILE_GUIDE_TYPE_ATM1			(0x00000100)
#define	PvAPI_PROFILE_GUIDE_TYPE_ATM2			(0x00000101)
#define	PvAPI_PROFILE_GUIDE_TYPE_USER1			(0x00000200)
#define	PvAPI_PROFILE_GUIDE_TYPE_USER2			(0x00000201)

// SetProfile regist data type dwParam value.
#define	PvAPI_PROFILE_REGIST_DATA_TYPE_NO_COMPRESS_2	(0x00000001)
#define	PvAPI_PROFILE_REGIST_DATA_TYPE_COMPRESS_2		(0x00000003)

// SetProfile sensor type dwParam value.
#define	PvAPI_PROFILE_SENSOR_TYPE_INI			(0x00000000)
#define	PvAPI_PROFILE_SENSOR_TYPE_AUTO			(0x00000001)
#define	PvAPI_PROFILE_SENSOR_TYPE_NO_SENSOR		(0x00000002)

// SetProfile extract kind dwParam value.
#define	PvAPI_PROFILE_EXTRACT_KIND_1			(0x00000000)
#define	PvAPI_PROFILE_EXTRACT_KIND_2			(0x00000001)
#define	PvAPI_PROFILE_EXTRACT_KIND_3			(0x00000002)

// SetProfile CR type dwParam value.
#define	PvAPI_PROFILE_CR_KIND_2					(0x00000002)
#define	PvAPI_PROFILE_CR_KIND_3					(0x00000003)

// Identify Mode type dwParam value.
#define	PvAPI_PROFILE_IDENTIFY_MODE_OLDCOMPATIBLE	(0x00000000)
#define	PvAPI_PROFILE_IDENTIFY_MODE_INDEX			(0x00000001)
#define	PvAPI_PROFILE_IDENTIFY_MODE_INDEX_2			(0x00000002)

// Not Support
#define	PvAPI_PROFILE_IDENTIFY_TRUNCATION_MODE_NOTHING	(0x00000000)

// SetProfile enroll-index-mode dwParam value.
#define	PvAPI_PROFILE_INDEX_MODE_1				(0x00000001)
#define	PvAPI_PROFILE_INDEX_MODE_2				(0x00000002)

// SetProfile capture-data-mode dwParam value.
#define	PvAPI_PROFILE_CAPTURE_DATA_MODE_0		(0x00000000)
#define	PvAPI_PROFILE_CAPTURE_DATA_MODE_2		(0x00000002)

// SetProfile image type dwParam value.
#define	PvAPI_PROFILE_IMAGE_OFF					(0x00000000)
#define	PvAPI_PROFILE_IMAGE_SILHOUETTE			(0x00000001)


#define	PvAPI_PROFILE_GUIDE_MODE_NO_GUIDE		(0x00000000)
#define	PvAPI_PROFILE_GUIDE_MODE_GUIDE			(0x00000001)

// SetProfile Match-score dwParam value.
#define PvAPI_PROFILE_SCORE_NOTIFICATIONS_OFF		(0x00000000)
#define PvAPI_PROFILE_SCORE_NOTIFICATIONS_ON		(0x00000001)
#define PvAPI_PROFILE_SCORE_NOTIFICATIONS_ON_MODE2	(0x00000002)

// SetProfile SL-Extend-Mode dwParam value.
#define	PvAPI_PROFILE_SL_EXTEND_MODE_OLD		(0x00000000)
#define	PvAPI_PROFILE_SL_EXTEND_MODE_EX1		(0x00000001)

// SetProfile CaptureInvSense dwParam value.
#define PvAPI_PROFILE_CAPTURE_INV_SENSE_OFF		(0x00000000)
#define PvAPI_PROFILE_CAPTURE_INV_SENSE_ON		(0x00000001)

// SetProfile shared capture data dwParam value.
#define PvAPI_PROFILE_SHARED_MODE_OFF			(0x00000000)
#define PvAPI_PROFILE_SHARED_MODE_ON			(0x00000001)

// SetProfile MultiData-Mode dwParam value.
#define PvAPI_PROFILE_MULTIDATA_MODE_0			(0x00000000)
#define PvAPI_PROFILE_MULTIDATA_MODE_1			(0x00000001)

// SetProfile MultiData-SL-Ext-Mode dwParam value.
#define PvAPI_PROFILE_MULTIDATA_SL_EXT_MODE_0	(0x00000000)
#define PvAPI_PROFILE_MULTIDATA_SL_EXT_MODE_1	(0x00000001)

//------------------------------------------
// PreSetProfile
//------------------------------------------
// PreSetProfile flag value.
#define	PvAPI_PRE_PROFILE_IDENTIFYSENSOR		(0x00000001)
#define	PvAPI_PRE_PROFILE_SENSOR_AES256			(0x00000002)
#define	PvAPI_PRE_PROFILE_CERTIFY_INFO			(0x00000003)
#define	PvAPI_PRE_PROFILE_SENSOR_CONNECT		(0x00000007)
#define	PvAPI_PRE_PROFILE_SENSOR_EXTEND			(0x00000008)
#define	PvAPI_PRE_PROFILE_CAPTURE_TIMES			(0x00000009)
#define	PvAPI_PRE_PROFILE_CAPTURE_COMPRESS		(0x0000000A)
#define	PvAPI_PRE_PROFILE_BHG_MODE				(0x0000000B)
#define	PvAPI_PRE_PROFILE_CAPTURING_RANGE		(0x0000000C)
#define	PvAPI_PRE_PROFILE_MAX_MATCHTHREAD_NUM	(0x0000000D)
#define	PvAPI_PRE_PROFILE_G_EXTENDED_MODE		(0x0000000E)
#define	PvAPI_PRE_PROFILE_USB_POWER_MODE		(0x0000000F)
// reserve										(0x00000010)
#define	PvAPI_PRE_PROFILE_SLG_EXTENDED_MODE		(0x00000011)

// PreSetProfile sensor connect lpvParamData value.
#define	PvAPI_PRE_PROFILE_SENSOR_CONNECT_0		(0x00000000)
#define	PvAPI_PRE_PROFILE_SENSOR_CONNECT_1		(0x00000001)

// PreSetProfile sensor extend lpvParamData value.
#define	PvAPI_PRE_PROFILE_SENSOR_EXTEND_OFF		(0x00000000)
#define	PvAPI_PRE_PROFILE_SENSOR_EXTEND_ON		(0x00000001)

// PreSetProfile capture compress lpvParamData value.
#define	PvAPI_PRE_PROFILE_CAPTURE_COMPRESS_OFF	(0x00000000)
#define	PvAPI_PRE_PROFILE_CAPTURE_COMPRESS_ON	(0x00000001)

// PreSetProfile BHG use mode lpvParamData value.
#define	PvAPI_PRE_PROFILE_BHG_MODE_OFF			(0x00000000)
#define	PvAPI_PRE_PROFILE_BHG_MODE_ON			(0x00000001)

// PreSetProfile capturing range lpvParamData value.
#define	PvAPI_PRE_PROFILE_CAPTURING_RANGE_NEW	(0x00000000)
#define	PvAPI_PRE_PROFILE_CAPTURING_RANGE_OLD	(0x00000001)
#define	PvAPI_PRE_PROFILE_CAPTURING_RANGE_CHG	(0x00000002)

// PreSetProfile G-Extended-Mode lpvParamData value.
#define	PvAPI_PRE_PROFILE_G_EXTENDED_MODE_OFF	(0x00000000)
#define	PvAPI_PRE_PROFILE_G_EXTENDED_MODE_1		(0x00000001)
#define	PvAPI_PRE_PROFILE_G_EXTENDED_MODE_2		(0x00000002)
#define	PvAPI_PRE_PROFILE_G_EXTENDED_MODE_3		(0x00000003)
#define	PvAPI_PRE_PROFILE_G_EXTENDED_MODE_4		(0x00000004)

// PreSetProfile USBHighPowerMode lpvParamData value.
#define	PvAPI_PRE_PROFILE_USB_POWER_MODE_NORMAL	(0x00000000)
#define	PvAPI_PRE_PROFILE_USB_POWER_MODE_HIGH	(0x00000001)

// PreSetProfile SLG-Extended-Mode lpvParamData value.
#define	PvAPI_PRE_PROFILE_SLG_EXTENDED_MODE_OFF	(0x00000000)
#define	PvAPI_PRE_PROFILE_SLG_EXTENDED_MODE_1	(0x00000001)


//------------------------------------------
// Packet
//------------------------------------------
#define	PvAPI_SIZE_PACKET_CRCINFO				(0x00000010)
#define	PvAPI_SIZE_PACKET_VEINBUFFER			(0x00001000)


//------------------------------------------
// Population Type
//------------------------------------------
#define	PvAPI_PRESET_ARRAY_TYPE					(3)
#define	PvAPI_PRESET_ARRAY_ADD					(4)
#define	PvAPI_PRESET_ARRAY_DEL					(5)


//------------------------------------------
// GetTemplateInfo Type
//------------------------------------------
#define	PvAPI_INFO_SENSOR_TYPE_1				(0x00000000)
#define	PvAPI_INFO_SENSOR_TYPE_2				(0x00000001)
#define	PvAPI_INFO_SENSOR_TYPE_3				(0x00000002)
#define	PvAPI_INFO_SENSOR_TYPE_4				(0x00000003)
#define	PvAPI_INFO_SENSOR_TYPE_8				(0x00000007)
#define	PvAPI_INFO_SENSOR_TYPE_9				(0x00000008)
#define	PvAPI_INFO_SENSOR_TYPE_A				(0x00000009)
#define	PvAPI_INFO_SENSOR_TYPE_B				(0x0000000A)
#define	PvAPI_INFO_SENSOR_TYPE_C				(0x0000000B)
#define	PvAPI_INFO_SENSOR_TYPE_D				(0x0000000C)

// SetProfile enroll-index-mode dwParam value.
#define	PvAPI_PROFILE_INDEX_MODE_0				(0x00000000)
//#define	PvAPI_PROFILE_INDEX_MODE_1			(0x00000001)
//#define	PvAPI_PROFILE_INDEX_MODE_2			(0x00000002)
#define	PvAPI_INFO_INDEX_MODE_0					(0x00000000)
#define	PvAPI_INFO_INDEX_MODE_1					(0x00000001)
#define	PvAPI_INFO_INDEX_MODE_2					(0x00000002)
#define	PvAPI_INFO_INDEX_MODE_5					(0x00000005)
#define	PvAPI_INFO_INDEX_MODE_10				(0x0000000A)
#define	PvAPI_INFO_INDEX_MODE_11				(0x0000000B)

#define	PvAPI_INFO_M2_EXTEND_OFF				(0x00000000)
#define	PvAPI_INFO_M2_EXTEND_ON					(0x00000001)

#define	PvAPI_INFO_G_EXTENDED_MODE_OFF			(0x00000000)
#define	PvAPI_INFO_G_EXTENDED_MODE_1			(0x00000001)
#define	PvAPI_INFO_G_EXTENDED_MODE_2			(0x00000002)
#define	PvAPI_INFO_G_EXTENDED_MODE_3			(0x00000003)
#define	PvAPI_INFO_G_EXTENDED_MODE_4			(0x00000004)

#define	PvAPI_INFO_GUIDE_MODE_NO_GUIDE			(0x00000000)
#define	PvAPI_INFO_GUIDE_MODE_GUIDE				(0x00000001)
#define	PvAPI_INFO_GUIDE_MODE_BHG				(0x00000002)

#define	PvAPI_INFO_MULTI_DATA_G					(0x00000000)
#define	PvAPI_INFO_MULTI_DATA_G_GUIDE			(0x00000010)
#define	PvAPI_INFO_MULTI_DATA_I					(0x00000001)
#define	PvAPI_INFO_MULTI_DATA_I_GUIDE			(0x00000011)
#define	PvAPI_INFO_MULTI_DATA_I_BHG				(0x00000021)
#define	PvAPI_INFO_MULTI_DATA_Iex				(0x00000101)
#define	PvAPI_INFO_MULTI_DATA_I33				(0x00010001)
#define	PvAPI_INFO_MULTI_DATA_I33_GUIDE			(0x00010011)
#define	PvAPI_INFO_MULTI_DATA_R					(0x00020001)
#define	PvAPI_INFO_MULTI_DATA_R_GUIDE			(0x00020011)


//------------------------------------------
// GuiStateCallback Return
//------------------------------------------
#define	PvAPI_WAIT								(16)


//------------------------------------------
// PvAPI_GetConnectSensorInfo MaxNum
//------------------------------------------
#define	PvAPI_GET_SENSOR_INFO_MAX				(8)


//------------------------------------------
// PvAPI_GetLibraryInfo Sensor Extend Mode
//------------------------------------------
#define PvAPI_INFO_SENSOR_MODE_COMPATIBLE		(0x00000000)
#define PvAPI_INFO_SENSOR_MODE_EXTEND			(0x00000001)

// GetLibraryInfo loop-mode dwParam value.
#define PvAPI_INFO_LOOP_MODE_OFF				(0x00000000)
#define PvAPI_INFO_LOOP_MODE_ON					(0x00000001)

// GetLibraryInfo compress-mode dwParam value.
#define PvAPI_INFO_COMPRESS_MODE_OFF			(0x00000000)
#define PvAPI_INFO_COMPRESS_MODE_ON				(0x00000001)

// GetLibraryInfo driver-kind value.
#define PvAPI_INFO_DRIVER_KIND_EXTENDED			(0x00000000)
#define PvAPI_INFO_DRIVER_KIND_CONVENTIONAL		(0x00000001)
#define PvAPI_INFO_DRIVER_KIND_MP				(0x00000002)
#define PvAPI_INFO_DRIVER_KIND_UUD				(0x00000004)

// GetLibraryInfo Edition value.
#define PvAPI_INFO_EDITION_INVALID				(0x00000000)
#define PvAPI_INFO_EDITION_PE					(0x00000002)
#define PvAPI_INFO_EDITION_EE					(0x00000003)
#define PvAPI_INFO_EDITION_F_PE					(0x00010002)
#define PvAPI_INFO_EDITION_F_EE					(0x00010003)



//------------------------------------------
// PvAPI_GetExData Get Extend Data Type
//------------------------------------------
#define PvAPI_EX_DATA_TYPE_0001					(0x00000000)
#define PvAPI_EX_DATA_TYPE_0002					(0x00000001)
#define PvAPI_EX_DATA_TYPE_1001					(0x00001000)
#define PvAPI_EX_DATA_TYPE_1002					(0x00001001)
// INC02789 add START 20220204 N.Ishida
#define PvAPI_EX_DATA_TYPE_3001					(0x00003000)
// INC02789 add END   20220204 N.Ishida

//------------------------------------------
// PvAPI_GetExData Get Extend Data Size
//------------------------------------------
#define PvAPI_EX_DATA_0001_SIZE					(4096)
#define PvAPI_EX_DATA_1001_SIZE					(5242880)
// INC02789 add START 20220204 N.Ishida
#define PvAPI_EX_DATA_3001_SIZE					(4)
// INC02789 add END   20220204 N.Ishida


/*****************************************************************************
	PvAPI Macro
*****************************************************************************/
	static const int							g_PvAPI_EndianCheckCode = 0x00000001;
// Length Return
#define	PvAPI_GET_BIR_Length( BIR, SetLength ) \
	{ \
		if( BIR ) \
		{ \
			if( &((BIR)->Header.Length) != &(SetLength) ) \
			{ \
				if( ((char*)&g_PvAPI_EndianCheckCode)[0] == 0 ) \
				{ \
					(SetLength) =	((((BIR)->Header.Length) >> 24)&0x000000ff) | \
									((((BIR)->Header.Length) >> 8)&0x0000ff00) | \
									((((BIR)->Header.Length) << 8)&0x00ff0000) | \
									((((BIR)->Header.Length) << 24)&0xff000000); \
				} \
				else \
				{ \
					(SetLength) = ((BIR)->Header.Length); \
				} \
			} \
		} \
	}


#endif /* _PVAPITYPE_H_ */
