; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlldemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dlldemo.h"

ClassCount=4
Class1=CDlldemoApp
Class2=CDlldemoDlg

ResourceCount=7
Resource1=IDR_MAINFRAME
Resource2=IDD_FORMVIEW (English (U.S.))
Class3=CDlldemoMenu
Resource3=IDD_SKU_BARCODE
Resource4=IDD_PROPPAGE_SMALL
Resource5=IDD_OLE_PROPPAGE_SMALL (English (U.S.))
Class4=CLoginDlg
Resource6=IDD_DLLDEMO_DIALOG
Resource7=IDR_MENU1

[CLS:CDlldemoApp]
Type=0
HeaderFile=dlldemo.h
ImplementationFile=dlldemo.cpp
Filter=N

[CLS:CDlldemoDlg]
Type=0
HeaderFile=dlldemoDlg.h
ImplementationFile=dlldemoDlg.cpp
Filter=D
LastObject=IDM_LOGIN
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_DLLDEMO_DIALOG]
Type=1
Class=CDlldemoDlg
ControlCount=10
Control1=IDC_BUTTONOPENPORT,button,1342242816
Control2=IDC_CHECK1,button,1342242819
Control3=IDC_BUTTONCLOSEPORT,button,1476460544
Control4=IDC_STATICPRINTSTATUS,static,1342312972
Control5=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242853
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BUTTONPRINTADDRESS,button,1342242816
Control9=IDC_CURRENCY_USER,static,1342312960
Control10=IDC_STATIC,static,1342308352

[MNU:IDR_MENU1]
Type=1
Class=CDlldemoDlg
Command1=IDM_LOGIN
Command2=IDM_SKU_BARCODE
CommandCount=2

[CLS:CDlldemoMenu]
Type=0
HeaderFile=DlldemoMenu.h
ImplementationFile=DlldemoMenu.cpp
BaseClass=CMiniFrameWnd
Filter=T
LastObject=CDlldemoMenu

[DLG:IDD_FORMVIEW (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_OLE_PROPPAGE_SMALL (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CLoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CLoginDlg
VirtualFilter=dWC

[DLG:IDD_PROPPAGE_SMALL]
Type=1
Class=CLoginDlg
ControlCount=6
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631584
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_SKU_BARCODE]
Type=1
Class=?
ControlCount=10
Control1=IDC_SKU,static,1342308352
Control2=IDC_BARCODE_SKU,edit,1350631552
Control3=IDC_SKU_TITLE,static,1342312448
Control4=IDC_SKU_STOCK,static,1342312448
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_GET_SKU_INFO,button,1342242816
Control8=IDC_SKU_BARCODE_PRINT,button,1342242816
Control9=IDC_PRINT_NUM,edit,1350631552
Control10=IDC_STATIC,static,1342308352

