//Print.h

#define SOH  0x01
#define STX  0x02
#define ESC  0x1b 
#define XON	 0X11
#define XOFF 0X13
#define CR   0X0D
#define LF	 0X0A
#define FF   0X0C

#define BPLA_OK             1000     //һ������
#define BPLA_COMERROR       1001     //ͨѶ�����δ���Ӵ�ӡ��
#define BPLA_PARAERROR      1002     //��������
#define BPLA_FILEOPENERROR  1003     //�ļ��򿪴���
#define BPLA_FILEREADERROR  1004     //�ļ�������
#define BPLA_FILEWRITEERROR 1005     //�ļ�д����
#define BPLA_FILEERROR      1006     //�ļ�����Ҫ��
#define BPLA_NUMBEROVER     1007     //ָ���Ľ�����Ϣ��������
#define BPLA_IMAGETYPEERROR 1008     //ͼ���ļ���ʽ����ȷ 

BOOL  LoadDll();

//***************���Ժ���
typedef int (__stdcall *mBPLA_SetSaveFile)(bool,char*,bool);	//��ָ��浽�ļ�
typedef int (__stdcall *mBPLA_GetVersion)();					//��ȡ�汾

//***************�˿ڿ���
typedef int (__stdcall *mBPLA_OpenCom)(char*,int,int);			//�����ô���
typedef int (__stdcall *mBPLA_OpenComEx)(char*,int,int,int);	//�����ô���,�����
typedef int (__stdcall *mBPLA_CloseCom)();						//�رմ���
typedef int (__stdcall *mBPLA_OpenLpt)(int, int);				//�򿪲���
typedef int (__stdcall *mBPLA_CloseLpt)();						//�رղ���
typedef int (__stdcall *mBPLA_OpenUsb)();						//��USB��
typedef int (__stdcall *mBPLA_OpenUsbByID)(int);				//ͨ���ڲ�ID�Ŵ�USB��
typedef int (__stdcall *mBPLA_CloseUsb)();						//�ر�USB��
typedef int (__stdcall *mBPLA_SetTimeOut)(int);					//���ö˿ڳ�ʱ

//***************�����շ�
typedef int (__stdcall *mBPLA_SendCommand)(char*,int);           //����ָ��
typedef int (__stdcall *mBPLA_ReceiveInfo)(int,char*,int*,int);  //����ָ��
typedef int (__stdcall *mBPLA_SendFile)(char*);                  //����ָ���ļ�
typedef int (__stdcall *mBPLA_ReceiveFile)(int,char*, int*,int); //����ָ��ļ�

//***************��������
typedef int (__stdcall *mBPLA_OpenPrinterDriver)(char* );		 //����������
typedef int (__stdcall *mBPLA_ClosePrinterDriver)();             //�ر���������
typedef int (__stdcall *mBPLA_StartDoc)();                       //������ӡ��ҵ
typedef int (__stdcall *mBPLA_EndDoc)();                         //�رմ�ӡ��ҵ

//***************�豸����
typedef int (__stdcall *mBPLA_DownloadImage)(char*,int,int,char*);   //����ͼ��
typedef int (__stdcall *mBPLA_DownloadFont)(char*,int,int,int,int,int,int,int,int,char*);//��������
typedef int (__stdcall *mBPLA_DownErase)(int,int,char*);             //ɾ��ָ�����ļ�
typedef int (__stdcall *mBPLA_DownEraseAll)(int);                    //ɾ��ָ��ģ���е�ȫ���ļ�
typedef int (__stdcall *mBPLA_Reset)();                              //��λ��ӡ��
typedef int (__stdcall *mBPLA_ForBack)(int,int);                     //��/�˱�ǩ
typedef int (__stdcall *mBPLA_Set)(int,int,int);                     //��ֽ��ʽ��ֽ�����͡�����ģʽ
typedef int (__stdcall *mBPLA_SetSensor)(int);                       //ѡ�񴫸���
typedef int (__stdcall *mBPLA_SetPaperLength)(int,int);              //����ֽ����
typedef int (__stdcall *mBPLA_SetEnd)(int);	                         //���ô�ӡֹͣλ��

//***************��ǩ��ʽ
typedef int (__stdcall *mBPLA_StartArea)(int,int,int,int,int,int,int,int);//�����ǩģʽ
typedef int (__stdcall *mBPLA_SetMirror)();                               //��������Ч
//typedef int (__stdcall *mBPLA_SetZero)();
typedef int (__stdcall *mBPLA_SetCopy)(int pieces,int gap);               //������
typedef int (__stdcall *mBPLA_SetAllRotate)(int);                         //���巭ת
typedef int (__stdcall *mBPLA_SetAllMirror)();                            //���徵��  
typedef int (__stdcall *mBPLA_PrintSaveLabel)(int);                       //��ӡ�Ѿ�����ı�ǩ����֧������������
typedef int (__stdcall *mBPLA_Print)(int,int,int);                        //��ӡ��ǩ
typedef int (__stdcall *mBPLA_SaveLabel)();                               //�����ǩ����ӡ  

//***************��������
//ͼ�δ�ӡ
typedef int (__stdcall *mBPLA_PrintLine)(int,int,int,int,int);        //ֱ��
typedef int (__stdcall *mBPLA_PrintBox)(int,int,int,int,int,int,int); //����
typedef int (__stdcall *mBPLA_PrintCircle)(int,int,int,int,int);      //Բ

//ͼ���ӡ
typedef int (__stdcall *mBPLA_LoadImage)(char*,int,int,int,int,int);  //�����Ѿ����ص�ͼ��
typedef int (__stdcall *mBPLA_PrintImage)(char*,int,int,int);         //ֱ������ͼ�󵽴�ӡλ��

//���ִ�ӡ
typedef int (__stdcall *mBPLA_PrintText)(char*,int,int,int,int,int,int,char*,int,int);//�ڲ�����0-8��000-007��P06-P18
typedef int (__stdcall *mBPLA_PrintOut)(char*,int,int,int,char*,int,int,char*,int,int);//�Ѿ����ص��ⲿ�����ӡ
typedef int (__stdcall *mBPLA_PrintTruetype)(char*,int,int,char*,int,int);//��ӡTRUETYPE����
typedef int (__stdcall *mBPLA_PrintTruetypeEx)(char*,int,int,char*,int,int,int);//��ӡTRUETYPE���壬����ѡ��������ת��������з���
//��Ӣ�Ļ��Ŵ�ӡ
typedef int (__stdcall *mBPLA_PrintMixText)(char*,int,int,int,int, int,char*,int,int, int,int,char*,int,int);
//��Ӣ�Ļ��Ŵ�ӡ��ָ���ʽ��
typedef int (__stdcall *mBPLA_PrintMixTextEx)(char*,int,int,int,int, char*,char*,int,int,char*,int,int);

//�����ӡ
//һά����
typedef int (__stdcall *mBPLA_PrintBarcode)(char*,int,int,int,int,int,int,int,char*);
//PDF417��
typedef int (__stdcall *mBPLA_PrintPDF)(char*,int,int,int,int,int,int,int,int,int,int,int,int,char*);
//MAXICODE��
typedef int (__stdcall *mBPLA_PrintMaxi)(char*,int,int,char*);

//***************��ѯ
typedef int (__stdcall *mBPLA_CheckCom)();  //���Դ���
typedef int (__stdcall *mBPLA_CheckStatus)(char*,char*,char*,char*,char*,char*,char*,char*);//����״̬
typedef int (__stdcall *mBPLA_CheckCut)();  //�����е�
