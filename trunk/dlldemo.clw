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

ResourceCount=6
Resource1=IDR_MAINFRAME
Resource2=IDD_FORMVIEW (English (U.S.))
Class3=CDlldemoMenu
Resource3=IDD_PROPPAGE_SMALL (English (U.S.))
Resource4=IDD_DLLDEMO_DIALOG
Resource5=IDD_OLE_PROPPAGE_SMALL (English (U.S.))
Class4=CLoginDlg
Resource6=IDR_MENU1

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
ControlCount=32
Control1=IDC_RADIO1,button,1342308361
Control2=IDC_RADIO3,button,1342177289
Control3=IDC_RADIO6,button,1342177289
Control4=IDC_RADIO7,button,1342177289
Control5=IDC_COMNAME,combobox,1344340226
Control6=IDC_COMBOBAUDRATE,combobox,1344339971
Control7=IDC_COMBOADDRESS,combobox,1478557699
Control8=IDC_BUTTONOPENPORT,button,1342242816
Control9=IDC_CHECK1,button,1342242819
Control10=IDC_RADIO4,button,1342308361
Control11=IDC_RADIO5,button,1342177289
Control12=IDC_BUTTONPRINT,button,1476460544
Control13=IDC_BUTTONCLOSEPORT,button,1476460544
Control14=IDC_STATICPRINTSTATUS,static,1342312972
Control15=IDC_STATIC,button,1342177543
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,button,1342178055
Control19=IDC_EDIT1,edit,1350637572
Control20=IDC_STATICIMAGE,static,1342177294
Control21=IDC_BUTTONSTATUS,button,1476460544
Control22=IDC_STATIC,static,1342308352
Control23=IDC_DRIVER,edit,1350631552
Control24=IDC_STATIC,button,1342177287
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_TIMEOUT,edit,1350639744
Control28=IDC_STATIC,static,1342308352
Control29=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242853
Control30=IDC_EDIT3,edit,1350631552
Control31=IDC_STATIC,static,1342308352
Control32=IDC_BUTTON1,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=CDlldemoDlg
Command1=IDM_LOGIN
CommandCount=1

[CLS:CDlldemoMenu]
Type=0
HeaderFile=DlldemoMenu.h
ImplementationFile=DlldemoMenu.cpp
BaseClass=CMiniFrameWnd
Filter=T
LastObject=CDlldemoMenu

[DLG:IDD_PROPPAGE_SMALL (English (U.S.))]
Type=1
Class=CLoginDlg
ControlCount=6
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

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

