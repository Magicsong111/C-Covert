/** 
* @file index.cpp
* @brief ����cpp
* @author �����С��
* @date 2023/4/5
* @version beta0.1
* ��g++�����exe��������.
*/
#include<iostream>
#include<windows.h>
#include<commdlg.h>
#include<shlobj.h>
#include<fstream>
#include"resource.h"
using namespace std;
/**
 * ����������
 * @param msg ������ַ���
 * @param line ��������
*/
void error(string msg,int line)
{
    string s="Error!\nIn line "+to_string(line)+"\n"+msg;  //������Ϣ
    MessageBox(NULL,s.c_str(),"Error!",MB_ICONERROR|MB_OK);  //��������
    exit(-1);  //��������
}
/**
 * ����һ����ѡ��ť
 * @param text ��ť��ʾ���ı�
 * @param x ��ť��x����
 * @param y ��ť��y����
 * @param w ��ť�Ŀ�
 * @param h ��ť�ĸ�
 * @param hwnd �����ڵľ��
 * @param idcb ��ť��ʶ��
 * @return ������ť�ľ��,����ʧ��Ϊ��
*/
HWND CreateCheckBox(LPSTR text,int x,int y,int w,int h,HWND hwnd,HMENU idcb)
{
    HWND shwnd=CreateWindow("Button",text,WS_VISIBLE|WS_CHILD|BS_CHECKBOX,x,y,w,h,hwnd,idcb,(HINSTANCE)GetWindowLongPtr(hwnd,GWLP_HINSTANCE),NULL);  //�������
    return shwnd; 
}
/**
 * ����һ����ѡ��ť
 * @param text ��ť��ʾ���ı�
 * @param x ��ť��x����
 * @param y ��ť��y����
 * @param w ��ť�Ŀ�
 * @param h ��ť�ĸ�
 * @param hwnd �����ڵľ��
 * @param idcb ��ť��ʶ��
 * @return ������ť�ľ��,����ʧ��Ϊ��
*/
HWND CreateRadioButton(LPSTR text,int x,int y,int w,int h,HWND hwnd,HMENU idcb)
{
    HWND shwnd=CreateWindow("Button",text,WS_VISIBLE|WS_CHILD|BS_RADIOBUTTON,x,y,w,h,hwnd,idcb,(HINSTANCE)GetWindowLongPtr(hwnd,GWLP_HINSTANCE),NULL);  //�������
    return shwnd;  
}
/**
 * ����һ����ť
 * @param text ��ť��ʾ���ı�
 * @param x ��ť��x����
 * @param y ��ť��y����
 * @param w ��ť�Ŀ�
 * @param h ��ť�ĸ�
 * @param hwnd �����ڵľ��
 * @param idb ��ť��ʶ��
 * @return ������ť�ľ��,����ʧ��Ϊ��
*/
HWND CreateButton(LPSTR text,int x,int y,int w,int h,HWND hwnd,HMENU idb)
{
    HWND shwnd=CreateWindow("Button",text,WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,x,y,w,h,hwnd,idb,(HINSTANCE)GetWindowLongPtr(hwnd,GWLP_HINSTANCE),NULL);
    return shwnd;
}
/**
 * ����һ���ı���
 * @param text �ı����Ĭ���ı�
 * @param x �ı����x����
 * @param y �ı����y����
 * @param w �ı���Ŀ�
 * @param h �ı���ĸ�
 * @param hwnd �����ڵľ��
 * @param idb �ı����ʶ��
 * @return �����ı���ľ��,����ʧ��Ϊ��
*/
HWND CreateEdit(LPSTR text,int x,int y,int w,int h,HWND hwnd,HMENU ide)
{
    HWND shwnd=CreateWindow("Edit",text,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE,x,y,w,h,hwnd,ide,(HINSTANCE)GetWindowLongPtr(hwnd,GWLP_HINSTANCE),NULL);  //�������
    return shwnd;
}
/**
 * ����һ�������ļ�����
 * @param hwnd �����
 * @return �����ļ�·��
*/
string CreateSaveFileDilog(HWND hwnd)
{
    TCHAR szBuffer[MAX_PATH]={0};  //���ݻ�����
    BROWSEINFO bi;   
    ZeroMemory(&bi,sizeof(BROWSEINFO));   //��0�����
    bi.hwndOwner=hwnd;   //�����ھ��
    bi.pszDisplayName=szBuffer;  //�趨������   
    bi.lpszTitle=NULL;  //����
    bi.ulFlags=BIF_RETURNFSANCESTORS;  //����һ���ڵ�   
    LPITEMIDLIST idl=SHBrowseForFolder(&bi);  //��ʾ�Ի���   
    if (idl==NULL)  //�ļ���Ϊ��
        return "";   //�ļ��б� 
    SHGetPathFromIDList(idl,szBuffer);  //�����ʶ���б�ת��Ϊ�ļ�ϵͳ·��
    return string(szBuffer);  
}
/**
 * ����һ�����ļ�����
 * @param filter �ļ�������
 * @param hwnd �����
 * @return �����ļ�·��
*/
string CreateOpenFileDilog(LPSTR filter,HWND hwnd)
{
    OPENFILENAME ofn;  //�ļ�����
    CHAR szFile[255];  //������
    ZeroMemory(&ofn,sizeof(ofn));  //����
    ofn.lStructSize=sizeof(ofn);  //��С
    ofn.hwndOwner=hwnd;  //�����
    ofn.lpstrFile=szFile;  //�ļ�������
    ofn.lpstrFile[0]='\0';  
    ofn.nMaxFile=sizeof(szFile);  //�ļ���С
    ofn.lpstrFilter=filter;  //�ļ�������
    ofn.nFilterIndex=1;  //�ļ���������ʶ
    ofn.lpstrFileTitle=NULL;  //�ļ�����
    ofn.nMaxFileTitle=0;  
    ofn.lpstrInitialDir=NULL;  //��ʼλ��
    ofn.Flags=OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
    if(GetOpenFileName(&ofn))  //��ȡ�ļ����ɹ�?
    {
        return ofn.lpstrFile;  
    }
    return "";  
}
/**
 * ���ڻص�����
 * @param hwnd ���ھ��
 * @param Message �����¼�
 * @param wParam ��Ϣ��Ӧ����
 * @param lParam ��Ϣ��Ӧ����
 * @return ����������Ϣ
 * @remark ʹ�� @c WM_CREATE ��ʼ�����, @c WM_COMMAND ������Ϣ
 * @bug �����µ�ѡ��ťʱ��Ӧ��
*/
LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    /* ��� */
    static HWND b1,b2,b3,b4,b5,b6;
    static HWND e1,e2,e3,e4;
    static HWND cb1,cb2;
    static HWND rb1,rb2;
    static bool i1=false,i2=false,i3=false;
    string FileName;
    fstream file1;
    static string running[4];
    bool exit;
    PAINTSTRUCT ps;
    string temp;
    CHAR buff[255];
    HDC hdc;
    HFONT font;
    /* ��Ϣ��Ӧ */
    switch(Message)
    {
        case WM_CREATE:
            /* ������� */
            e1=CreateEdit((char*)"",80,12,421,26,hwnd,(HMENU)IDE_1);
            b1=CreateButton((char*)"ѡ��",500,12,73,26,hwnd,(HMENU)IDB_1);
            cb1=CreateCheckBox((char*)"ͼ��",10,60,70,26,hwnd,(HMENU)IDCB_1);
            e2=CreateEdit((char*)"",80,60,421,26,hwnd,(HMENU)IDE_2);
            b2=CreateButton((char*)"ѡ��",500,60,73,26,hwnd,(HMENU)IDB_2);
            cb2=CreateCheckBox((char*)"�汾",10,100,70,26,hwnd,(HMENU)IDCB_2);
            e3=CreateEdit((char*)"",80,100,421,26,hwnd,(HMENU)IDE_3);
            b3=CreateButton((char*)"ѡ��",500,100,73,26,hwnd,(HMENU)IDB_3);
            e4=CreateEdit((char*)"",80,150,421,26,hwnd,(HMENU)IDE_4);
            b4=CreateButton((char*)"ѡ��",500,150,73,26,hwnd,(HMENU)IDB_4);
            rb1=CreateRadioButton((char*)"window",145,180,135,40,hwnd,(HMENU)IDRB_1);
            rb2=CreateRadioButton((char*)"cmd",300,180,135,40,hwnd,(HMENU)IDRB_2);
            b5=CreateButton((char*)"ת��",0,225,205,85,hwnd,(HMENU)IDB_5);
            b6=CreateButton((char*)"�鿴�ļ�λ��",400,225,205,85,hwnd,(HMENU)IDB_6);
            SendMessage(rb2,BM_SETCHECK,BST_CHECKED,0);  //��ʼ��rb2
        case WM_PAINT:
            /* �������� */
            hdc=BeginPaint(hwnd,&ps);  //��ʼ����
            TextOut(hdc,10,15,"�����ļ�:",9);  
            TextOut(hdc,10,155,"����ļ�:",9);
            TextOut(hdc,10,190,"ģʽ:",5);
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDB_1:
                    /* ��ť1������ */
                    FileName=CreateOpenFileDilog((char*)"cpp(*.cpp)\0*.cpp\0",hwnd);
                    if(SetWindowText(e1,FileName.c_str())==0)error("ERROR!",199);  
                    return 0;
                case IDCB_1:
                    /* ��ѡ��ť1������ */
                    i1=!i1;
                    //cout<<i<<endl;
                    /* �л�ѡ��ģʽ */
                    if(!i1)
                        SendMessage(cb1,BM_SETCHECK,BST_UNCHECKED,0);
                    else
                        SendMessage(cb1,BM_SETCHECK,BST_CHECKED,0);
                    return 0;
                case IDB_2:
                    /* ��ť2������ */
                    FileName=CreateOpenFileDilog((char*)"ͼ��(*.ico)\0*.ico\0",hwnd);
                    if(SetWindowText(e2,FileName.c_str())==0)error("ERROR!",214);
                    return 0;
                case IDCB_2:
                    /* ��ѡ��ť2������ */
                    i2=!i2;
                    /* �л�ѡ��ģʽ */
                    if(!i2)
                        SendMessage(cb2,BM_SETCHECK,BST_UNCHECKED,0);
                    else
                        SendMessage(cb2,BM_SETCHECK,BST_CHECKED,0);
                    return 0;
                case IDB_3:
                    /* ��ť3������ */
                    FileName=CreateOpenFileDilog((char*)"�汾(*.txt)\0*.txt\0",hwnd);
                    if(SetWindowText(e3,FileName.c_str())==0)error("ERROR!",228);
                    return 0;
                case IDB_4:
                    /* ��ť4������ */
                    FileName=CreateSaveFileDilog(hwnd);
                    if(SetWindowText(e4,FileName.c_str())==0)error("ERROR!",233);
                    return 0;
                case IDRB_1:
                    /* ��ѡ��ť1������ */
                    i3=!i3;
                    if(i3)
                    {
                        SendMessage(rb1,BM_SETCHECK,BST_CHECKED,0);
                        SendMessage(rb2,BM_SETCHECK,BST_UNCHECKED,0);
                    }
                    return 0;
                case IDRB_2:
                    /* ��ѡ��ť2������ */
                    i3=!i3;
                    if(i3)
                    {
                        SendMessage(rb1,BM_SETCHECK,BST_UNCHECKED,0);
                        SendMessage(rb2,BM_SETCHECK,BST_CHECKED,0);
                    }
                    return 0;
                case IDB_5:
                    /* ��ť5������ */
                    /* ��ʼת�� */
                    /* ��ȡ���� */
                    GetWindowText(e1,buff,255);  
                    running[0]=string(buff);
                    GetWindowText(e2,buff,255);
                    running[1]=string(buff);
                    GetWindowText(e3,buff,255);
                    running[2]=string(buff);
                    GetWindowText(e4,buff,255);
                    running[3]=string(buff);
                    if(running[0]=="")
                        error("��������:\n  �������ļ�",288);
                    /* �ļ����� */
                    file1.open("C:\\ProgramData\\data.rc",ios::out|ios::trunc);
                    if(running[1]!=""&&SendMessage(cb1,BM_GETCHECK,0,0)==BST_CHECKED)
                    {
                        CopyFile(running[1].c_str(),"C:\\ProgramData\\1.ico",FALSE);  //�����ļ�
                        file1<<"id ICON "<<'"'<<"1.ico"<<'"'<<endl;  //����rc
                    }
                    if(running[2]!=""&&SendMessage(cb2,BM_GETCHECK,0,0)==BST_CHECKED)
                    {
                        CopyFile(running[2].c_str(),"C:\\ProgramData\\1.txt",FALSE);  //�����ļ�
                        fstream f;
                        /* ��ȡ�ı��ļ���ÿһ�е��ı� */
                        f.open(running[2],ios::in);
                        for(int i=0;i<100;i++)
                        {
                            f.getline(buff,2555);
                            file1<<string(buff)<<endl;
                        }
                    }
                    /* ûѡ���·���� */
                    if(running[3]=="")
                        running[3]="C:";
                    system("windres -i C:\\ProgramData\\data.rc -o C:\\ProgramData\\data.o");  //windres����
                    file1.close();  //�ͷ��ļ��ڴ�
                    //cout<<running[3];
                    temp="g++ \""+running[0]+"\" C:\\ProgramData\\data.o -o \""+running[3]+"\\output.exe\" -leasyx -static -lgdi32 -lcomdlg32 -lComCtl32";  //���в���
                    if(SendMessage(rb1,BM_GETCHECK,0,0)==BST_CHECKED)  //�Ǵ��ڳ���
                        temp+=" -mwindows";  //����ָ��
                    cout<<temp<<endl;
                    system(temp.c_str());  //����ָ��
                    MessageBox(hwnd,"ת�����","���!",MB_OK|MB_ICONINFORMATION);  //��������
                    /* ɾ��������ʱ�ļ� */
                    remove("C:\\ProgramData\\1.ico");
                    remove("C:\\ProgramData\\1.txt");
                    remove("C:\\ProgramData\\data.o");
                    remove("C:\\ProgramData\\data.rc");
                    return 0;
                case IDB_6:
                    /* ��ť6�����£� */
                    temp="start "+running[3];  //���в���
                    system(temp.c_str());  //����
                    return 0;
            }
            break;
        case WM_CLOSE:
            /* ���ڹر�? */
            if(MessageBox(hwnd,"ȷ��Ҫ�˳���?","�˳�",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
                DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:  //������Ϣ
            return DefWindowProc(hwnd,Message,wParam,lParam);
    }
    return 0;
}
/**
 * Win32��������
 * @param hinstance Ӧ�ó���ǰʵ���ľ��
 * @param hPrevlnstance Ӧ�ó������ǰʵ���ľ��
 * @param lpcmdline ָ��Ӧ�ó��������е��ַ�����ָ��
 * @param nCmdShow ָ�����������ʾ
 * @return �˳�����
*/
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hPrevlnstance,LPSTR lpcmdline,int nCmdShow)
{
    WNDCLASSEX wc;  //һ������
    HWND hwnd;  //���ھ��
    MSG msg; //������Ϣ
    memset(&wc,0,sizeof(wc));  //����
    wc.cbSize=sizeof(WNDCLASSEX);  //WNDCLASSEX�Ĵ�С
    wc.lpfnWndProc=WndProc;  //���ڴ�������ָ��
    wc.hInstance=hinstance;  //��ģ���ʵ�����
    wc.hCursor=LoadCursor(NULL,IDC_ARROW);  //���ľ��
    wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);  //������ˢ�ľ��
    wc.lpszClassName="WindowClass"; //ָ�������Ƶ�ָ��
    wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);  //ͼ��ľ��
    wc.hIconSm=LoadIcon(NULL,IDI_APPLICATION);  //�ʹ����������Сͼ��
    if(!RegisterClassEx(&wc))  //ע��ʧ��
        error("Window Registration Failed",346);
    hwnd=CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","CPP COVERT",WS_VISIBLE|WS_OVERLAPPEDWINDOW,DEFAULT_X,DEFAULT_Y,DEFAULT_WIDTH,DEFAULT_HEIGHT,NULL,NULL,hinstance,NULL);  //��������
    if(hwnd==NULL)  //����ʧ��
        error("Window Creation Falied",349);
    /* ��ȡ��Ϣ */
    while(GetMessage(&msg,NULL,0,0)>0)  
    {
        TranslateMessage(&msg);  //��������ת��Ϊ�ַ�(�������)
        DispatchMessage(&msg);  //���䷢�͵�WndProc
    }
    return msg.wParam;
}

