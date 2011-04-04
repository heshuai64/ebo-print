#include "stdafx.h"
#include "Print.h"

HINSTANCE hlib;

mBPLA_SetSaveFile		 BPLA_SetSaveFile			     = NULL;
mBPLA_GetVersion   		 BPLA_GetVersion			     = NULL;
mBPLA_OpenCom   		 BPLA_OpenCom				     = NULL;
mBPLA_OpenComEx   		 BPLA_OpenComEx				     = NULL;
mBPLA_CloseCom			 BPLA_CloseCom				     = NULL;
mBPLA_OpenLpt  			 BPLA_OpenLpt				     = NULL;
mBPLA_CloseLpt   		 BPLA_CloseLpt				     = NULL;
mBPLA_OpenUsb			 BPLA_OpenUsb					 = NULL;
mBPLA_OpenUsbByID  		 BPLA_OpenUsbByID				 = NULL;
mBPLA_CloseUsb   		 BPLA_CloseUsb					 = NULL;
mBPLA_SetTimeOut         BPLA_SetTimeOut				 = NULL;
mBPLA_OpenPrinterDriver	 BPLA_OpenPrinterDriver			 = NULL;
mBPLA_ClosePrinterDriver BPLA_ClosePrinterDriver		 = NULL;
mBPLA_StartDoc   		 BPLA_StartDoc					 = NULL;
mBPLA_EndDoc             BPLA_EndDoc					 = NULL;
mBPLA_SendCommand  		 BPLA_SendCommand				 = NULL;
mBPLA_ReceiveInfo  		 BPLA_ReceiveInfo				 = NULL;
mBPLA_SendFile			 BPLA_SendFile					 = NULL;
mBPLA_ReceiveFile		 BPLA_ReceiveFile				 = NULL;
mBPLA_DownloadImage		 BPLA_DownloadImage				 = NULL;
mBPLA_DownloadFont		 BPLA_DownloadFont				 = NULL;
mBPLA_DownErase			 BPLA_DownErase					 = NULL;
mBPLA_DownEraseAll		 BPLA_DownEraseAll				 = NULL;
mBPLA_Set				 BPLA_Set						 = NULL;
mBPLA_SetSensor			 BPLA_SetSensor					 = NULL;
mBPLA_SetPaperLength	 BPLA_SetPaperLength			 = NULL;
mBPLA_SetEnd			 BPLA_SetEnd					 = NULL;
mBPLA_ForBack			 BPLA_ForBack					 = NULL;
mBPLA_Reset				 BPLA_Reset						 = NULL;
mBPLA_StartArea			 BPLA_StartArea					 = NULL;
mBPLA_SetMirror			 BPLA_SetMirror					 = NULL;
mBPLA_Print				 BPLA_Print						 = NULL;
mBPLA_SaveLabel			 BPLA_SaveLabel					 = NULL;
mBPLA_PrintSaveLabel	 BPLA_PrintSaveLabel			 = NULL;
mBPLA_SetCopy			 BPLA_SetCopy					 = NULL;
mBPLA_SetAllMirror		 BPLA_SetAllMirror				 = NULL;
mBPLA_SetAllRotate		 BPLA_SetAllRotate				 = NULL;
mBPLA_PrintLine			 BPLA_PrintLine					 = NULL;
mBPLA_PrintBox			 BPLA_PrintBox					 = NULL;
mBPLA_PrintCircle		 BPLA_PrintCircle				 = NULL;
mBPLA_LoadImage			 BPLA_LoadImage					 = NULL;
mBPLA_PrintImage		 BPLA_PrintImage				 = NULL;
mBPLA_PrintText			 BPLA_PrintText					 = NULL;
mBPLA_PrintOut			 BPLA_PrintOut					 = NULL;
mBPLA_PrintTruetype		 BPLA_PrintTruetype				 = NULL;
mBPLA_PrintTruetypeEx	 BPLA_PrintTruetypeEx			 = NULL;
mBPLA_PrintMixText		 BPLA_PrintMixText				 = NULL;
mBPLA_PrintMixTextEx	 BPLA_PrintMixTextEx			 = NULL;
mBPLA_PrintBarcode		 BPLA_PrintBarcode				 = NULL;
mBPLA_PrintPDF			 BPLA_PrintPDF					 = NULL;
mBPLA_PrintMaxi			 BPLA_PrintMaxi					 = NULL;
mBPLA_CheckCom			 BPLA_CheckCom					 = NULL;
mBPLA_CheckStatus		 BPLA_CheckStatus				 = NULL;
mBPLA_CheckCut			 BPLA_CheckCut					 = NULL;

BOOL LoadDll()
{
   hlib = LoadLibrary("bpladll.dll");

   BPLA_SetSaveFile = (mBPLA_SetSaveFile) GetProcAddress(hlib,"BPLA_SetSaveFile");
   if(BPLA_SetSaveFile == NULL)
   {
	   AfxMessageBox("BPLA_SetSaveFile Funcation Error!");
	   return FALSE;
   }

   BPLA_GetVersion = (mBPLA_GetVersion) GetProcAddress(hlib,"BPLA_GetVersion");
   if(BPLA_GetVersion == NULL)
   {
	   AfxMessageBox("BPLA_GetVersion Funcation Error!");
	   return FALSE;
   }

   BPLA_OpenCom = (mBPLA_OpenCom) GetProcAddress(hlib,"BPLA_OpenCom");
   if(BPLA_OpenCom == NULL)
   {
	   AfxMessageBox("BPLA_OpenCom Funcation Error!");
	   return FALSE;
   }

   BPLA_OpenComEx = (mBPLA_OpenComEx) GetProcAddress(hlib,"BPLA_OpenComEx");
   if(BPLA_OpenComEx == NULL)
   {
	   AfxMessageBox("BPLA_OpenComEx Funcation Error!");
	   return FALSE;
   }

   BPLA_CloseCom = (mBPLA_CloseCom) GetProcAddress(hlib,"BPLA_CloseCom");
   if(BPLA_CloseCom == NULL)
   {
	   AfxMessageBox("BPLA_CloseCom Funcation Error!");
	   return FALSE;
   }

   BPLA_OpenLpt = (mBPLA_OpenLpt) GetProcAddress(hlib,"BPLA_OpenLpt");
   if(BPLA_OpenLpt == NULL)
   {
	   AfxMessageBox("BPLA_OpenLpt Funcation Error!");
	   return FALSE;
   }

   BPLA_CloseLpt = (mBPLA_CloseLpt) GetProcAddress(hlib,"BPLA_CloseLpt");
   if(BPLA_CloseLpt == NULL)
   {
	   AfxMessageBox("BPLA_CloseLpt Funcation Error!");
	   return FALSE;
   }

   BPLA_OpenUsb = (mBPLA_OpenUsb) GetProcAddress(hlib,"BPLA_OpenUsb");
   if(BPLA_OpenUsb == NULL)
   {
	   AfxMessageBox("BPLA_OpenUsb Funcation Error!");
	   return FALSE;
   }

   BPLA_OpenUsbByID = (mBPLA_OpenUsbByID) GetProcAddress(hlib,"BPLA_OpenUsbByID");
   if(BPLA_OpenUsbByID == NULL)
   {
	   AfxMessageBox("BPLA_OpenUsbByID Funcation Error!");
	   return FALSE;
   }

   BPLA_CloseUsb = (mBPLA_CloseUsb) GetProcAddress(hlib,"BPLA_CloseUsb");
   if(BPLA_CloseUsb == NULL)
   {
	   AfxMessageBox("BPLA_CloseUsb Funcation Error!");
	   return FALSE;
   }

   BPLA_SetTimeOut = (mBPLA_SetTimeOut) GetProcAddress(hlib,"BPLA_SetTimeOut");
   if(BPLA_SetTimeOut == NULL)
   {
	   AfxMessageBox("BPLA_SetTimeOut Funcation Error!");
	   return FALSE;
   }

   BPLA_OpenPrinterDriver = (mBPLA_OpenPrinterDriver) GetProcAddress(hlib,"BPLA_OpenPrinterDriver");
   if(BPLA_OpenPrinterDriver == NULL)
   {
	   AfxMessageBox("BPLA_OpenPrinterDriver Funcation Error!");
	   return FALSE;
   }

   BPLA_ClosePrinterDriver = (mBPLA_ClosePrinterDriver) GetProcAddress(hlib,"BPLA_ClosePrinterDriver");
   if(BPLA_ClosePrinterDriver == NULL)
   {
	   AfxMessageBox("BPLA_ClosePrinterDriver Funcation Error!");
	   return FALSE;
   }

   BPLA_StartDoc = (mBPLA_StartDoc) GetProcAddress(hlib,"BPLA_StartDoc");
   if(BPLA_StartDoc == NULL)
   {
	   AfxMessageBox("BPLA_StartDoc Funcation Error!");
	   return FALSE;
   }

   BPLA_EndDoc = (mBPLA_EndDoc) GetProcAddress(hlib,"BPLA_EndDoc");
   if(BPLA_EndDoc == NULL)
   {
	   AfxMessageBox("BPLA_EndDoc Funcation Error!");
	   return FALSE;
   }

   BPLA_SendCommand = (mBPLA_SendCommand) GetProcAddress(hlib,"BPLA_SendCommand");
   if(BPLA_SendCommand == NULL)
   {
	   AfxMessageBox("BPLA_SendCommand Funcation Error!");
	   return FALSE;
   }

   BPLA_ReceiveInfo = (mBPLA_ReceiveInfo) GetProcAddress(hlib,"BPLA_ReceiveInfo");
   if(BPLA_ReceiveInfo == NULL)
   {
	   AfxMessageBox("BPLA_ReceiveInfo Funcation Error!");
	   return FALSE;
   }

   BPLA_SendFile = (mBPLA_SendFile) GetProcAddress(hlib,"BPLA_SendFile");
   if(BPLA_SendFile == NULL)
   {
	   AfxMessageBox("BPLA_SendFile Funcation Error!");
	   return FALSE;
   }

   BPLA_ReceiveFile = (mBPLA_ReceiveFile) GetProcAddress(hlib,"BPLA_ReceiveFile");
   if(BPLA_ReceiveFile == NULL)
   {
	   AfxMessageBox("BPLA_ReceiveFile Funcation Error!");
	   return FALSE;
   }

   BPLA_DownloadImage = (mBPLA_DownloadImage) GetProcAddress(hlib,"BPLA_DownloadImage");
   if(BPLA_DownloadImage == NULL)
   {
	   AfxMessageBox("BPLA_DownloadImage Funcation Error!");
	   return FALSE;
   }


   BPLA_DownloadFont = (mBPLA_DownloadFont) GetProcAddress(hlib,"BPLA_DownloadFont");
   if(BPLA_DownloadFont == NULL)
   {
	   AfxMessageBox("BPLA_DownloadFont Funcation Error!");
	   return FALSE;
   }

   BPLA_DownErase = (mBPLA_DownErase) GetProcAddress(hlib,"BPLA_DownErase");
   if(BPLA_DownErase == NULL)
   {
	   AfxMessageBox("BPLA_DownErase Funcation Error!");
	   return FALSE;
   }

   BPLA_DownEraseAll = (mBPLA_DownEraseAll) GetProcAddress(hlib,"BPLA_DownEraseAll");
   if(BPLA_DownEraseAll == NULL)
   {
	   AfxMessageBox("BPLA_DownEraseAll Funcation Error!");
	   return FALSE;
   }

   BPLA_Set = (mBPLA_Set) GetProcAddress(hlib,"BPLA_Set");
   if(BPLA_Set == NULL)
   {
	   AfxMessageBox("BPLA_Set Funcation Error!");
	   return FALSE;
   }

   BPLA_SetSensor = (mBPLA_SetSensor) GetProcAddress(hlib,"BPLA_SetSensor");
   if(BPLA_SetSensor == NULL)
   {
	   AfxMessageBox("BPLA_SetSensor Funcation Error!");
	   return FALSE;
   }

   BPLA_SetPaperLength = (mBPLA_SetPaperLength) GetProcAddress(hlib,"BPLA_SetPaperLength");
   if(BPLA_SetPaperLength == NULL)
   {
	   AfxMessageBox("BPLA_SetPaperLength Funcation Error!");
	   return FALSE;
   }


   BPLA_SetEnd = (mBPLA_SetEnd) GetProcAddress(hlib,"BPLA_SetEnd");
   if(BPLA_SetEnd == NULL)
   {
	   AfxMessageBox("BPLA_SetEnd Funcation Error!");
	   return FALSE;
   }

   BPLA_ForBack = (mBPLA_ForBack) GetProcAddress(hlib,"BPLA_ForBack");
   if(BPLA_ForBack == NULL)
   {
	   AfxMessageBox("BPLA_ForBack Funcation Error!");
	   return FALSE;
   }

   BPLA_Reset = (mBPLA_Reset) GetProcAddress(hlib,"BPLA_Reset");
   if(BPLA_Reset == NULL)
   {
	   AfxMessageBox("BPLA_Reset Funcation Error!");
	   return FALSE;
   }

   BPLA_StartArea = (mBPLA_StartArea) GetProcAddress(hlib,"BPLA_StartArea");
   if(BPLA_StartArea == NULL)
   {
	   AfxMessageBox("BPLA_StartArea Funcation Error!");
	   return FALSE;
   }

   BPLA_SetMirror = (mBPLA_SetMirror) GetProcAddress(hlib,"BPLA_SetMirror");
   if(BPLA_SetMirror == NULL)
   {
	   AfxMessageBox("BPLA_SetMirror Funcation Error!");
	   return FALSE;
   }

   BPLA_Print = (mBPLA_Print) GetProcAddress(hlib,"BPLA_Print");
   if(BPLA_Print == NULL)
   {
	   AfxMessageBox("BPLA_Print Funcation Error!");
	   return FALSE;
   }

   BPLA_SaveLabel = (mBPLA_SaveLabel) GetProcAddress(hlib,"BPLA_SaveLabel");
   if(BPLA_SaveLabel == NULL)
   {
	   AfxMessageBox("BPLA_SaveLabel Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintSaveLabel = (mBPLA_PrintSaveLabel) GetProcAddress(hlib,"BPLA_PrintSaveLabel");
   if(BPLA_PrintSaveLabel == NULL)
   {
	   AfxMessageBox("BPLA_PrintSaveLabel Funcation Error!");
	   return FALSE;
   }

   BPLA_SetCopy = (mBPLA_SetCopy) GetProcAddress(hlib,"BPLA_SetCopy");
   if(BPLA_SetCopy == NULL)
   {
	   AfxMessageBox("BPLA_SetCopy Funcation Error!");
	   return FALSE;
   }

   BPLA_SetAllMirror = (mBPLA_SetAllMirror) GetProcAddress(hlib,"BPLA_SetAllMirror");
   if(BPLA_SetAllMirror == NULL)
   {
	   AfxMessageBox("BPLA_SetAllMirror Funcation Error!");
	   return FALSE;
   }

   BPLA_SetAllRotate = (mBPLA_SetAllRotate) GetProcAddress(hlib,"BPLA_SetAllRotate");
   if(BPLA_SetAllRotate == NULL)
   {
	   AfxMessageBox("BPLA_SetAllRotate Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintLine = (mBPLA_PrintLine) GetProcAddress(hlib,"BPLA_PrintLine");
   if(BPLA_PrintLine == NULL)
   {
	   AfxMessageBox("BPLA_PrintLine Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintBox = (mBPLA_PrintBox) GetProcAddress(hlib,"BPLA_PrintBox");
   if(BPLA_PrintBox == NULL)
   {
	   AfxMessageBox("BPLA_PrintBox Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintCircle = (mBPLA_PrintCircle) GetProcAddress(hlib,"BPLA_PrintCircle");
   if(BPLA_PrintCircle == NULL)
   {
	   AfxMessageBox("BPLA_PrintCircle Funcation Error!");
	   return FALSE;
   }

   BPLA_LoadImage = (mBPLA_LoadImage) GetProcAddress(hlib,"BPLA_LoadImage");
   if(BPLA_LoadImage == NULL)
   {
	   AfxMessageBox("BPLA_LoadImage Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintImage = (mBPLA_PrintImage) GetProcAddress(hlib,"BPLA_PrintImage");
   if(BPLA_PrintImage == NULL)
   {
	   AfxMessageBox("BPLA_PrintImage Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintText = (mBPLA_PrintText) GetProcAddress(hlib,"BPLA_PrintText");
   if(BPLA_PrintText == NULL)
   {
	   AfxMessageBox("BPLA_PrintText Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintOut = (mBPLA_PrintOut) GetProcAddress(hlib,"BPLA_PrintOut");
   if(BPLA_PrintOut == NULL)
   {
	   AfxMessageBox("BPLA_PrintOut Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintMixText = (mBPLA_PrintMixText) GetProcAddress(hlib,"BPLA_PrintMixText");
   if(BPLA_PrintMixText == NULL)
   {
	   AfxMessageBox("BPLA_PrintMixText Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintMixTextEx = (mBPLA_PrintMixTextEx) GetProcAddress(hlib,"BPLA_PrintMixTextEx");
   if(BPLA_PrintMixTextEx == NULL)
   {
	   AfxMessageBox("BPLA_PrintMixTextEx Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintTruetype = (mBPLA_PrintTruetype) GetProcAddress(hlib,"BPLA_PrintTruetype");
   if(BPLA_PrintTruetype == NULL)
   {
	   AfxMessageBox("BPLA_PrintTruetype Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintTruetypeEx = (mBPLA_PrintTruetypeEx) GetProcAddress(hlib,"BPLA_PrintTruetypeEx");
   if(BPLA_PrintTruetypeEx == NULL)
   {
	   AfxMessageBox("BPLA_PrintTruetypeEx Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintBarcode = (mBPLA_PrintBarcode) GetProcAddress(hlib,"BPLA_PrintBarcode");
   if(BPLA_PrintBarcode == NULL)
   {
	   AfxMessageBox("BPLA_PrintBarcode Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintPDF = (mBPLA_PrintPDF) GetProcAddress(hlib,"BPLA_PrintPDF");
   if(BPLA_PrintPDF == NULL)
   {
	   AfxMessageBox("BPLA_PrintPDF Funcation Error!");
	   return FALSE;
   }

   BPLA_PrintMaxi = (mBPLA_PrintMaxi) GetProcAddress(hlib,"BPLA_PrintMaxi");
   if(BPLA_PrintMaxi == NULL)
   {
	   AfxMessageBox("BPLA_PrintMaxi Funcation Error!");
	   return FALSE;
   }

   BPLA_CheckCom = (mBPLA_CheckCom) GetProcAddress(hlib,"BPLA_CheckCom");
   if(BPLA_CheckCom == NULL)
   {
	   AfxMessageBox("BPLA_CheckCom Funcation Error!");
	   return FALSE;
   }

   BPLA_CheckStatus = (mBPLA_CheckStatus) GetProcAddress(hlib,"BPLA_CheckStatus");
   if(BPLA_CheckStatus == NULL)
   {
	   AfxMessageBox("BPLA_CheckStatus Funcation Error!");
	   return FALSE;
   }

   BPLA_CheckCut = (mBPLA_CheckCut) GetProcAddress(hlib,"BPLA_CheckCut");
   if(BPLA_CheckCut == NULL)
   {
	   AfxMessageBox("BPLA_CheckCut Funcation Error!");
	   return FALSE;
   }

   return TRUE;
}

BOOL UnLoadDll()
{
	return FreeLibrary(hlib);	 
}