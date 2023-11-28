/* =========================================================================
 *  Sample Source for C Language Professional Edition
 * =========================================================================
 *
 *	All Rights Reserved, Copyright(c) FUJITSU FRONTECH LIMITED 2021
 *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>

#include "./Inc/bioapi_type.h"
#include "./Inc/bioapi_api.h"
#include "./Inc/bioapi_err.h"

#include "./Inc/pvapi_type.h"
#include "./Inc/pvapi_api.h"
#include "./Inc/pvapi_err.h"

#define  MAX_ENROLLDATA_SIZE		(1024*16)
#define  MAX_CAPTUREDATA_SIZE		(1024*80)




#define  APPLICATION_KEY 		"T02BUj0uaqquBpKu"
#define  ENROLL_FILENAME		"BIRData.dat"
#define  CAPTURE_FILENAME		"BIRCapData.dat"
#define  SILHOUETTE_FILENAME	"silhouette.bmp"

void disp_ErrorInfo(PvAPI_ErrorInfo *ErrInfo);
BioAPI_RETURN BioAPI GuiState_for_BioAPICallBack( void * GuiStateCallbackCtx,
											   BioAPI_GUI_STATE GuiState,
											   BioAPI_GUI_RESPONSE Response,
											   BioAPI_GUI_MESSAGE Message,
											   BioAPI_GUI_PROGRESS	Progress,
											   BioAPI_GUI_BITMAP_PTR SampleBuffer );

/* -------------------------------------------------------------------------
 *	main
 * ---------------------------------------------------------------------- */
int main(int argc, char **argv)
{
	FILE *fp;
	size_t datasize;

	BioAPI_RETURN		ret;
	BioAPI_HANDLE		mModuleHandle = 0;		// BioAPI_ModuleAttach handle
	BioAPI_BIR_HANDLE	NewBIRHandle = 0;		// BioAPI_Enroll/BioAPI_Capture
	PvAPI_BIR_PTR		pBIR = NULL;			// BioAPI_GetBIRFromHandle

	BioAPI_GUI_MESSAGE	mPreMessage = 0;		// BioAPI_SetGUICallbacks
	PvAPI_ErrorInfo		ErrorInfo;				// PvAPI_GetErrorInfo

	unsigned char		ucEnrolledBIR[MAX_ENROLLDATA_SIZE];
	unsigned char		ucCapturedBIR[MAX_CAPTUREDATA_SIZE];

	const BioAPI_UUID uuid[16] = {0xE1, 0x9A, 0x69, 0x01, 0xB8, 0xC2, 0x49, 0x80, 0x87, 0x7E, 0x11, 0xD4, 0xD8, 0xF1, 0xBE, 0x79};

	memset(ucEnrolledBIR, 0, sizeof(ucEnrolledBIR));
	memset(ucCapturedBIR, 0, sizeof(ucCapturedBIR));
	
		/* -------------------------------------------------------------------------
		 *	Phase: Initialize
		 * ---------------------------------------------------------------------- */
		printf("--\n");
		printf("PvAPI_ApAuthenticate\n");
		ret = PvAPI_ApAuthenticate((uint8*)APPLICATION_KEY);

		if ( ret != BioAPI_OK ) {
			PvAPI_GetErrorInfo(&ErrorInfo);
			if ( ErrorInfo.ErrorDetail == 0x02030003 ) {
				if ( ErrorInfo.ErrorInfo3[0] == 0x4c430000 ) {
					printf("\nError: License Error\n");
				} else {
					printf("\nError: APPLICATION_KEY Error(maybe)\n");
				}
			} else {
				disp_ErrorInfo(&ErrorInfo);
			}
			return 1;
		}

		// -----------------------------------------------------------------
		printf("--\n");
		printf("BioAPI_ModuleLoad\n");
		ret = BioAPI_ModuleLoad(uuid,		/* const BioAPI_UUID *				*/
							0,				/* uint32							*/
							NULL,			/* BioAPI_ModuleEventHandler(unuse)	*/
							NULL			/* void*(unuse)						*/
							);

		if ( ret != BioAPI_OK ) {
			PvAPI_GetErrorInfo(&ErrorInfo);
			disp_ErrorInfo(&ErrorInfo);
			return 1;
		}

		// -----------------------------------------------------------------
		printf("--\n");
		printf("BioAPI_ModuleAttach\n");
		ret = BioAPI_ModuleAttach(uuid,		/* const BioAPI_UUID *				*/ 
							  NULL,			/* const BioAPI_VERSION(unuse)		*/
							  NULL,			/* const BioAPI_MEMORY_FUNCS(unuse)	*/
							  0,			/* BioAPI_DEVICE_ID(unuse)			*/
							  0,			/* uint32(unuse)					*/
							  0,			/* uint32(unuse)					*/
							  0,			/* uint32(unuse)					*/
							  NULL,			/* BioAPI_FUNC_NAME_ADDR(unuse)		*/
							  0,			/* uint32(unuse)					*/
							  NULL,			/* const void *	(unuse)				*/
							  &mModuleHandle /* BioAPI_HANDLE_PTR				*/
							  );
		
		if ( ret != BioAPI_OK ) {
			goto error;
		}

		// -----------------------------------------------------------------
		printf("--\n");
		printf("BioAPI_SetGUICallbacks\n");
		ret = BioAPI_SetGUICallbacks(mModuleHandle,				/* BioAPI_HANDLE						*/
								 NULL,							/* BioAPI_GUI_STREAMING_CALLBACK(unuse)	*/
								 NULL,							/* void *(unuse)						*/
								 (BioAPI_GUI_STATE_CALLBACK)GuiState_for_BioAPICallBack,	/* BioAPI_GUI_STATE_CALLBACK			*/
								 &mPreMessage					/* void *								*/
								 );
		if ( ret != BioAPI_OK ) {
			goto error;
		}

		/* -------------------------------------------------------------------------
		 *	Phase: Enroll
		 * ---------------------------------------------------------------------- */
		if ( (fp = fopen(ENROLL_FILENAME, "rb")) != NULL ) {
			fread(ucEnrolledBIR, sizeof(unsigned char), sizeof(ucEnrolledBIR), fp);
			fclose(fp);
		} else {
			printf("--\n");
			printf("BioAPI_Enroll\n");
			mPreMessage = 0;
			ret = BioAPI_Enroll(mModuleHandle,			/* BioAPI_HANDLE				*/
								BioAPI_PURPOSE_VERIFY,  /* BioAPI_BIR_PURPOSE			*/
								NULL,					/* BioAPI_INPUT_BIR *(unuse)	*/
								&NewBIRHandle,			/* BioAPI_BIR_HANDLE_PTR		*/
								NULL,					/* BioAPI_DATA *(unuse)			*/
								0,						/* sint32						*/
								NULL					/* BioAPI_BIR_HANDLE_PTR(unuse) */
								);

			if ( ret != BioAPI_OK ) {
				goto error;
			}
			printf(" BioAPI_Enroll done.\n");

			// -----------------------------------------------------------------
			printf("--\n");
			printf("BioAPI_GetBIRFromHandle\n");
			ret = BioAPI_GetBIRFromHandle(mModuleHandle,		/* BioAPI_HANDLE		*/
									  NewBIRHandle,				/* BioAPI_BIR_HANDLE	*/
									  (BioAPI_BIR_PTR*)&pBIR	/* BioAPI_BIR_PTR *		*/
									  );

			if ( ret != BioAPI_OK ) {
				goto error;
			}

			datasize = (size_t)pBIR->Header.Length + 8;
			
			if ( datasize > MAX_ENROLLDATA_SIZE ) {
				printf("Error: Enroll data size error.\n");
				goto error;
			}

			memcpy(ucEnrolledBIR, (unsigned char*)pBIR, datasize);
			((PvAPI_BIR_PTR)ucEnrolledBIR)->BiometricData = 0;

			// -----------------------------------------------------------------
			printf("--\n");
			printf("BioAPI_FreeBIRHandle\n");
			ret = BioAPI_FreeBIRHandle(mModuleHandle,		/* BioAPI_HANDLE		*/
									 NewBIRHandle			/* BioAPI_BIR_HANDLE	*/
									 );

			if ( ret != BioAPI_OK ) {
				goto error;
			}

			// -----------------------------------------------------------------
			printf("--\n");

			fp = fopen(ENROLL_FILENAME, "wb");
			if ( fp != NULL ) {
				fwrite(ucEnrolledBIR, sizeof(unsigned char), datasize, fp);
				fclose(fp);
				printf(" FILE: %s (DataSize=%d)\n", ENROLL_FILENAME, datasize);
			}
		}

		/* -------------------------------------------------------------------------
		 *	Phase: Verify(Standalone)
		 * ---------------------------------------------------------------------- */
		{
			BioAPI_FRR			MaxFRRRequested = PvAPI_MATCHING_LEVEL_NORMAL;
			BioAPI_BOOL			Result = BioAPI_FALSE;
			BioAPI_BOOL			FARPrecedence = BioAPI_FALSE;
			BioAPI_FAR			FARAchieved = 0;
			BioAPI_INPUT_BIR	enrollInputBIR;

			printf("--\n");	
			printf("BioAPI_Verify\n");

			((PvAPI_BIR_PTR)ucEnrolledBIR)->BiometricData = 0;
			enrollInputBIR.Form = BioAPI_FULLBIR_INPUT;
			enrollInputBIR.InputBIR.BIR = (BioAPI_BIR_PTR)ucEnrolledBIR;

			mPreMessage = 0;
			ret = BioAPI_Verify(mModuleHandle,		/* BioAPI_HANDLE				*/
								NULL,				/* const BioAPI_FAR(unuse)		*/
								&MaxFRRRequested,	/* const BioAPI_FRR				*/
								&FARPrecedence,		/* const BioAPI_BOOL			*/
								&enrollInputBIR,	/* const BioAPI_INPUT_BIR*		*/
								NULL,				/* BioAPI_BIR_HANDLE_PTR(unuse)	*/
								&Result,			/* BioAPI_BOOL					*/
								&FARAchieved,		/* BioAPI_FAR_PTR				*/
								NULL,				/* BioAPI_FRR_PTR(unuse)		*/
								NULL,				/* BioAPI_DATA_PTR(unuse)		*/
								0,					/* sint32						*/
								NULL				/* BioAPI_BIR_HANDLE_PTR(unuse)	*/
								);

			if ( ret != BioAPI_OK ) {
				goto error;
			}
			
			printf("--\nBioAPI_Verify Result: %s\n",
					(Result==BioAPI_FALSE) ? "Auth-NG" : "Auth-OK");
		}
		
		/* -------------------------------------------------------------------------
		 *	Phase: Capture+VerifyMatch(CL/SV)
		 * ---------------------------------------------------------------------- */
		printf("--\n");	
		printf("BioAPI_Capture\n");
		
		mPreMessage = 0;
		ret = BioAPI_Capture(mModuleHandle,				/* BioAPI_HANDLE				*/
							BioAPI_PURPOSE_VERIFY,		/* BioAPI_BIR_PURPOSE			*/
							&NewBIRHandle,				/* BioAPI_BIR_HANDLE_PTR		*/
							0,							/* sint32						*/
							NULL						/* BioAPI_BIR_HANDLE_PTR(unuse)	*/
							);
		
		if ( ret != BioAPI_OK ) {
			goto error;
		}
		
		printf(" Capture done.\n");

		// -----------------------------------------------------------------
		printf("--\n");
		printf("BioAPI_GetBIRFromHandle\n");
		ret = BioAPI_GetBIRFromHandle(mModuleHandle,		/* BioAPI_HANDLE		*/
								  NewBIRHandle,				/* BioAPI_BIR_HANDLE	*/
								  (BioAPI_BIR_PTR*)&pBIR	/* BioAPI_BIR_PTR *		*/
								  );

		if ( ret != BioAPI_OK ) {
			goto error;
		}

		datasize = (size_t)pBIR->Header.Length + 8;
		
		if ( datasize > MAX_CAPTUREDATA_SIZE ) {
			printf("Error: Capture data size error.\n");
			goto error;
		}
		memcpy(ucCapturedBIR, (unsigned char*)pBIR, datasize);
		((PvAPI_BIR_PTR)ucCapturedBIR)->BiometricData = 0;

		// -----------------------------------------------------------------
		printf("--\n");
		printf("BioAPI_FreeBIRHandle\n");
		ret = BioAPI_FreeBIRHandle(mModuleHandle,		/* BioAPI_HANDLE		*/
								 NewBIRHandle			/* BioAPI_BIR_HANDLE	*/
								 );

		if ( ret != BioAPI_OK ) {
			goto error;
		}
		
		// -----------------------------------------------------------------
		printf("--\n");

		fp = fopen(CAPTURE_FILENAME, "wb");
		if ( fp != NULL ) {
			fwrite(ucCapturedBIR, sizeof(unsigned char), datasize, fp);
			fclose(fp);
			printf(" FILE: %s (DataSize=%d)\n", CAPTURE_FILENAME, datasize);
		}

		// -----------------------------------------------------------------
		{
			BioAPI_FRR			MaxFRRRequested = PvAPI_MATCHING_LEVEL_NORMAL;
			BioAPI_BOOL			Result = BioAPI_FALSE;
			BioAPI_BOOL			FARPrecedence = BioAPI_FALSE;
			BioAPI_FAR			FARAchieved = 0;
			BioAPI_INPUT_BIR	enrollInputBIR;
			BioAPI_INPUT_BIR	captureInputBIR;

			printf("--\n");
			printf("BioAPI_VerifyMatch\n");
			
			((PvAPI_BIR_PTR)ucEnrolledBIR)->BiometricData = 0;
			enrollInputBIR.Form = BioAPI_FULLBIR_INPUT;
			enrollInputBIR.InputBIR.BIR = (BioAPI_BIR_PTR)ucEnrolledBIR;

			((PvAPI_BIR_PTR)ucCapturedBIR)->BiometricData = 0;
			captureInputBIR.Form = BioAPI_FULLBIR_INPUT;
			captureInputBIR.InputBIR.BIR = (BioAPI_BIR_PTR)ucCapturedBIR;
			
			mPreMessage = 0;
			ret = BioAPI_VerifyMatch(mModuleHandle,			/* BioAPI_HANDLE				*/
									 NULL,					/* const BioAPI_FAR *(unuse)	*/
									 &MaxFRRRequested,		/* const BioAPI_FRR	*			*/
									 &FARPrecedence,		/* const BioAPI_BOOL *			*/
									 &captureInputBIR,		/* const BioAPI_INPUT_BIR *		*/
									 &enrollInputBIR,		/* const BioAPI_INPUT_BIR *		*/
									 NULL,					/* BioAPI_BIR_HANDLE *(unuse)	*/
									 &Result,				/* BioAPI_BOOL *				*/
									 &FARAchieved,			/* BioAPI_FAR_PTR				*/
									 NULL,					/* BioAPI_FRR_PTR(unuse)		*/
									 NULL					/* BioAPI_DATA_PTR *(unuse)		*/
									 );

			if ( ret != BioAPI_OK ) {
				goto error;
			}
			
			printf("--\nBioAPI_VerifyMatch Result: %s\n",
					(Result==BioAPI_FALSE) ? "Auth-NG" : "Auth-OK");

		}
		
		/* -------------------------------------------------------------------------
		 *	Phase: Terminate
		 * ---------------------------------------------------------------------- */
		printf("--\n");	
		printf("BioAPI_ModuleDetach\n");
		ret = BioAPI_ModuleDetach(mModuleHandle);	/* BioAPI_HANDLE	*/

		// -----------------------------------------------------------------
		printf("--\n");	
		printf("BioAPI_ModuleUnload\n");
		ret = BioAPI_ModuleUnload(uuid,				/* const BioAPI_UUID *			*/
								  NULL,				/* BioAPI_ModuleEvevtHandler	*/
								  NULL				/* void	*						*/
								  );
		
	// -----------------------------------------------------------------
	return 0;

 error:;
	PvAPI_GetErrorInfo(&ErrorInfo);
	disp_ErrorInfo(&ErrorInfo);
	if ( mModuleHandle != 0 ) {
		ret = BioAPI_ModuleDetach(mModuleHandle);
	}
	ret = BioAPI_ModuleUnload(uuid, NULL, NULL);
	return 1;
}

/* -------------------------------------------------------------------------
 *	Callback Message
 * ---------------------------------------------------------------------- */
void disp_message( BioAPI_GUI_MESSAGE Message )
{
	switch(Message){
	case PvAPI_NOTIFY_CAP_GUID_BADIMAGE: // 0x02030200
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_BADIMAGE\n");
		printf(" Move your hand away from the sensor.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_NO_HANDS: // 0x02030201
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS\n");
		printf(" Place your hand.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_MOVING: // 0x02030203
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING\n");
		printf(" Stop moving your hand.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_LESSINFO: // 0x02030204
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO\n");
		printf(" Unclench your hand and place correctly.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_RIGHT: // 0x02030205
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_RIGHT\n");
		printf(" Move your hand to the left.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_LEFT: // 0x02030206
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_LEFT\n");
		printf(" Move your hand to the right.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_DOWN: // 0x02030207
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_DOWN\n");
		printf(" Move your hand away from you.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_UP: // 0x02030208
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_UP\n");
		printf(" Move your hand towards you.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_FAR: // 0x02030209
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_FAR\n");
		printf(" Bring your hand closer.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_NEAR: // 0x0203020A
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_NEAR\n");
		printf(" Move your hand higher.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_CAPTURING: // 0x0203020B
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING\n");
		printf(" Now capturing.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_PITCH_DOWN: // 0x02030210
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_PITCH_DOWN\n");
		printf(" Lay your hand flat.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_PITCH_UP: // 0x02030211
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_PITCH_UP\n");
		printf(" Lay your hand flat.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_ROLL_RIGHT: // 0x02030212
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_ROLL_RIGHT\n");
		printf(" Lay your hand flat.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_ROLL_LEFT: // 0x02030213
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_ROLL_LEFT\n");
		printf(" Lay your hand flat.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_YAW_RIGHT: // 0x02030214
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_YAW_RIGHT\n");
		printf(" Place your hand parallel to the sensor.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_YAW_LEFT: // 0x02030215
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_YAW_LEFT\n");
		printf(" Place your hand parallel to the sensor.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_CLOSE_FINGER: // 0x02030216 (V24)
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_CLOSE_FINGER\n");
		printf(" Unclench your hand and place correctly.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_ROUND: // 0x02030217
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_ROUND\n");
		printf(" Lay your hand flat.\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_ADJUST_LIGHT: // 0x02030220
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_ADJUST_LIGHT\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_ADJUST_NG: // 0x02030221
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_ADJUST_NG\n");
		break;
	case PvAPI_NOTIFY_CAP_GUID_PHASE_END: // 0x02030300
		printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_PHASE_END\n");
		printf(" Now authenticating.\n");
		break;
	// -------------------------------------------------------------------------
	case (PvAPI_NOTIFY_API_KIND + PvAPI_NOTIFY_API_KIND_CAPTURE): // 0x03000101
		printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_API_KIND_CAPTURE\n");
		break;
	case (PvAPI_NOTIFY_API_KIND + PvAPI_NOTIFY_API_KIND_VERIFYMATCH): // 0x03000102
		printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_API_KIND_VERIFYMATCH\n");
		break;
	case (PvAPI_NOTIFY_API_KIND + PvAPI_NOTIFY_API_KIND_IDENTIFYMATCH): // 0x03000103
		printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_API_KIND_IDENTIFYMATCH\n");
		break;
	case (PvAPI_NOTIFY_API_KIND + PvAPI_NOTIFY_API_KIND_ENROLL): // 0x03000104
		printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_API_KIND_ENROLL\n");
		break;
	case (PvAPI_NOTIFY_API_KIND + PvAPI_NOTIFY_API_KIND_VERIFY): // 0x03000105
		printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_API_KIND_VERIFY\n");
		break;
	case (PvAPI_NOTIFY_API_KIND + PvAPI_NOTIFY_API_KIND_IDENTIFY): // 0x03000106
		printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_API_KIND_IDENTIFY\n");
		break;
	case (PvAPI_NOTIFY_API_END + PvAPI_NOTIFY_API_END_NORMAL): // 0x03000200
		printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_API_END_NORMAL\n");
		break;
	case (PvAPI_NOTIFY_API_END + PvAPI_NOTIFY_API_END_CANCEL): // 0x03000210
		printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_API_END_CANCEL\n");
		break;
	case (PvAPI_NOTIFY_API_END + PvAPI_NOTIFY_API_END_ERROR): // 0x03000220
		printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_API_END_ERROR\n");
		break;
	case (PvAPI_NOTIFY_CAP_GUID_CAPTURE_IMAGE): // 0x02030222
		printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_CAP_GUID_CAPTURE_IMAGE\n");
		break;
	case PvAPI_NOTIFY_WAIT_FOR_TRIGGER: // 0x02040000
		printf("-MessageCB: [optional] PvAPI_NOTIFY_WAIT_FOR_TRIGGER\n");
		break;
	case (PvAPI_NOTIFY_REGIST_SCORE + PvAPI_REGIST_SCORE_QUALITY_1): // 0x05000001
		printf("-MessageCB: [optional] PvAPI_REGIST_SCORE_QUALITY_1(Good)\n");
		break;
	case (PvAPI_NOTIFY_REGIST_SCORE + PvAPI_REGIST_SCORE_QUALITY_2): // 0x05000002
		printf("-MessageCB: [optional] PvAPI_REGIST_SCORE_QUALITY_2\n");
		break;
	case (PvAPI_NOTIFY_REGIST_SCORE + PvAPI_REGIST_SCORE_QUALITY_3): // 0x05000003
		printf("-MessageCB: [optional] PvAPI_REGIST_SCORE_QUALITY_3\n");
		break;
	default:
		if ( (0xFF000000 & Message) == PvAPI_NOTIFY_MATCH_RESULT ) { // 0x04XXXXXX
			int iResult;
			iResult = 0x00FFFFFF & Message;
			printf("-MessageCB(GUI): [optional] PvAPI_NOTIFY_MATCH_RESULT");
			if ( iResult == 0 ) {
				printf("(Auth-NG)\n");
			} else {
				printf("(Auth-OK[%d])\n", iResult);
			}
			break;
		}

		if ( (0xFFFFFF00 & Message) == PvAPI_NOTIFY_CAP_GUID_START ) { // 0x020300MN
			printf("-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x%08X]\n", Message);
			printf(" Capturing Start. (%d/%d)\n", (Message & 0x000F), ((Message >> 4) & 0x000F));
			break;
		}

		printf("-Unknown message [0x%08X]\n", Message);
		break;

	}
	
	return;
}

/* -------------------------------------------------------------------------
 *	Callback Function
 * ---------------------------------------------------------------------- */

BioAPI_RETURN BioAPI GuiState_for_BioAPICallBack( void * GuiStateCallbackCtx,
											   BioAPI_GUI_STATE GuiState,
											   BioAPI_GUI_RESPONSE Response,
											   BioAPI_GUI_MESSAGE Message,
											   BioAPI_GUI_PROGRESS	Progress,
											   BioAPI_GUI_BITMAP_PTR SampleBuffer )
{
	BioAPI_GUI_MESSAGE		*PreMessage;

	PreMessage = (BioAPI_GUI_MESSAGE*)GuiStateCallbackCtx;

	if ( GuiState & BioAPI_SAMPLE_AVAILABLE ) {
		printf("-MessageCB: State: Silhouette\n");
		{
			BioAPI_DATA_PTR pbmp;
			FILE *fp;
			
			pbmp = SampleBuffer->Bitmap;
			fp = fopen(SILHOUETTE_FILENAME, "wb");
			if ( fp != NULL ) {
				fwrite((unsigned char*)pbmp->Data, sizeof(unsigned char), (size_t)pbmp->Length, fp);
				fclose(fp);
			}
		}
	}

	if ( GuiState & BioAPI_MESSAGE_PROVIDED ) {
		if ( *PreMessage != Message ) {
			disp_message(Message);
		}
		*PreMessage = Message;
	}

	return BioAPI_OK; // only "BioAPI_OK"
}


/* -------------------------------------------------------------------------
 *	Error Function
 * ---------------------------------------------------------------------- */
void disp_ErrorInfo(PvAPI_ErrorInfo *ErrInfo)
{
	if ( (ErrInfo->ErrorLevel == PvAPI_ERROR_LEVEL_NORMAL) ||
	     (ErrInfo->ErrorLevel == PvAPI_ERROR_LEVEL_CANCEL) )
	{
	 return;
	}
	
	printf(" ErrorLevel  = 0x%02X\n", ErrInfo->ErrorLevel);
	printf(" ErrorCode   = 0x%02X\n", ErrInfo->ErrorCode);
	printf(" ErrorDetail = 0x%08X\n", ErrInfo->ErrorDetail);
	printf(" ErrorInfo1 = 0x%08X\n", ErrInfo->ErrorInfo1);
	printf(" ErrorInfo2 = 0x%08X\n", ErrInfo->ErrorInfo2);
	printf(" ErrorInfo3[0] = 0x%08X\n", ErrInfo->ErrorInfo3[0]);
	printf(" ErrorInfo3[1] = 0x%08X\n", ErrInfo->ErrorInfo3[1]);
	printf(" ErrorInfo3[2] = 0x%08X\n", ErrInfo->ErrorInfo3[2]);
	printf(" ErrorInfo3[3] = 0x%08X\n", ErrInfo->ErrorInfo3[3]);

	return;
}
