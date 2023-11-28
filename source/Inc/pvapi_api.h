// Copyright 2020 FUJITSU FRONTECH LIMITED
/*-----------------------------------------------------------------------
 * File   : PvAPI_API.H
 *
 * Date   : 2006.02.03
 *
 * Update : 2008.01.08 V24
 *          2008.07.03 V25-010
 *          2008.11.19 V27-010
 *          2011.05.23 V30-300
 *          2012.04.24 V31-020
 *          2017.10.20 V34-030
 *          2020.04.23 V34-151
 *-----------------------------------------------------------------------
 */

#ifndef _PvAPIAPI_H
#define _PvAPIAPI_H

/* API Functions */
#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************/
/*** PvAPI Service Functions *********************************************/
/*************************************************************************/

BioAPI_RETURN BioAPI PvAPI_ApAuthenticate(
						uint8 *Key );

void BioAPI PvAPI_GetErrorInfo(
						PvAPI_ErrorInfo *pErrorInfo );

BioAPI_RETURN BioAPI PvAPI_Sense(
						BioAPI_HANDLE ModuleHandle,
						uint32 Timeout,
						uint32 Interval,
						uint32 CheckRetryInterval,
						uint32 CheckRetryCount );

BioAPI_RETURN BioAPI PvAPI_Cancel(
						BioAPI_HANDLE ModuleHandle,
						PvAPI_ErrorInfo *pErrorInfo );

BioAPI_RETURN BioAPI PvAPI_CreateHandleFromBiometricData(
						BioAPI_HANDLE ModuleHandle,
						const void *Data,
						sint32 DataSize,
						BioAPI_BIR_HANDLE_PTR NewTemplate );

#ifdef PvAPI_64BIT_OS_TARGET
BioAPI_RETURN BioAPI PvAPI_SetProfile(
						BioAPI_HANDLE ModuleHandle,
						uint64 dwFlag,
						uint64 dwParam1,
						uint64 dwParam2,
						uint64 dwReserve );
#else
BioAPI_RETURN BioAPI PvAPI_SetProfile(
						BioAPI_HANDLE ModuleHandle,
						DWORD dwFlag,
						DWORD dwParam1,
						DWORD dwParam2,
						DWORD dwReserve );
#endif

BioAPI_RETURN BioAPI PvAPI_GetFileVersion(
						PvAPI_VLINFO_TBL_PTR lptVLInfo,
						PvAPI_DRINFO_TBL_PTR lptDRInfo );

BioAPI_RETURN BioAPI PvAPI_PreSetProfile(
						uint32 uiFlag,
						void* lpvParamData,
						uint32 uiParamDataSize,
						void* lpvReserve );

BioAPI_RETURN BioAPI PvAPI_MatchStatus(
						BioAPI_HANDLE ModuleHandle,
						uint32 uiFlag,
						void* lpvParamData,
						uint32 uiParamDataSize,
						void* lpvReserve );

BioAPI_RETURN BioAPI PvAPI_CreateVeinPacket(
						void* 	lpvVeinData,
						uint32 	uiVeinDataSize,
						void* 	lpvVeinPacket,
						uint32*	lpuiVeinPacketSize );

BioAPI_RETURN BioAPI PvAPI_GetVeinDataFromPacket(
						void* 	lpvVeinPacket,
						uint32 	uiVeinPacketSize,
						void* 	lpvVeinData,
						uint32*	lpuiVeinDataSize );

BioAPI_RETURN BioAPI PvAPI_PresetIdentifyPopulation(
						BioAPI_HANDLE	ModuleHandle,
						const BioAPI_IDENTIFY_POPULATION*	Population	);

BioAPI_RETURN BioAPI PvAPI_GetTemplateInfo(
						BioAPI_HANDLE				ModuleHandle,
						const BioAPI_INPUT_BIR*		StoredTemplate,
						PvAPI_TemplateInfo*			TemplateInfo	);

BioAPI_RETURN BioAPI PvAPI_GetConnectSensorInfo(
						uint32* lpuiSensorNum,
						PvAPI_SensorInfo* lptSensorInfo );

BioAPI_RETURN BioAPI PvAPI_GetLibraryInfo(
						PvAPI_LBINFO_PTR		lptLBInfo );

BioAPI_RETURN BioAPI PvAPI_GetTemplateInfoEx(
						BioAPI_HANDLE				ModuleHandle,
						const BioAPI_INPUT_BIR*		StoredTemplate,
						PvAPI_TemplateInfoEx*		TemplateInfo );

BioAPI_RETURN BioAPI PvAPI_GetConnectSensorInfoEx(
						uint32* lpuiSensorNum,
						PvAPI_SensorInfoEx* lptSensorInfo );

BioAPI_RETURN BioAPI PvAPI_GetExData(
						BioAPI_HANDLE				ModuleHandle,
						uint32						uiExDataType,
						BioAPI_DATA*				ptExData );

BioAPI_RETURN BioAPI PvAPI_DataHandler(
						BioAPI_HANDLE				ModuleHandle,
						uint32						uiFlag,
						BioAPI_DATA*				ptData );

BioAPI_RETURN BioAPI PvAPI_F3BC4AndInit(
						sint8 *Path );

/*************************************************************************/


#ifdef __cplusplus
}
#endif

#endif /* _PvAPIAPI_H */
