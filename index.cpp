/** 
* @file index.cpp
* @brief 美化cpp
* @author 神奇的小宋
* @date 2023/4/5
* @version beta0.1
* 将g++编译的exe进行美化.
*/
#include<iostream>
#include<windows.h>
#include<commdlg.h>
#include<shlobj.h>
#include<fstream>
#include"resource.h"
using namespace std;
/**
 * 错误解决函数
 * @param msg 报错的字符串
 * @param line 报错行数
*/
void error(string msg,int line)
{
    string s="Error!\nIn line "+to_string(line)+"\n"+msg;  //报错消息
    MessageBox(NULL,s.c_str(),"Error!",MB_ICONERROR|MB_OK);  //弹窗报错
    exit(-1);  //结束程序
}
/**
 * 创建一个复选按钮
 * @param text 按钮显示的文本
 * @param x 按钮的x坐标
 * @param y 按钮的y坐标
 * @param w 按钮的宽
 * @param h 按钮的高
 * @param hwnd 父窗口的句柄
 * @param idcb 按钮标识号
 * @return 创建按钮的句柄,创建失败为空
*/
HWND CreateCheckBox(LPSTR text,int x,int y,int w,int h,HWND hwnd,HMENU idcb)
{
    HWND shwnd=CreateWindow("Button",text,WS_VISIBLE|WS_CHILD|BS_CHECKBOX,x,y,w,h,hwnd,idcb,(HINSTANCE)GetWindowLongPtr(hwnd,GWLP_HINSTANCE),NULL);  //生成组件
    return shwnd; 
}
/**
 * 创建一个单选按钮
 * @param text 按钮显示的文本
 * @param x 按钮的x坐标
 * @param y 按钮的y坐标
 * @param w 按钮的宽
 * @param h 按钮的高
 * @param hwnd 父窗口的句柄
 * @param idcb 按钮标识号
 * @return 创建按钮的句柄,创建失败为空
*/
HWND CreateRadioButton(LPSTR text,int x,int y,int w,int h,HWND hwnd,HMENU idcb)
{
    HWND shwnd=CreateWindow("Button",text,WS_VISIBLE|WS_CHILD|BS_RADIOBUTTON,x,y,w,h,hwnd,idcb,(HINSTANCE)GetWindowLongPtr(hwnd,GWLP_HINSTANCE),NULL);  //生成组件
    return shwnd;  
}
/**
 * 创建一个按钮
 * @param text 按钮显示的文本
 * @param x 按钮的x坐标
 * @param y 按钮的y坐标
 * @param w 按钮的宽
 * @param h 按钮的高
 * @param hwnd 父窗口的句柄
 * @param idb 按钮标识号
 * @return 创建按钮的句柄,创建失败为空
*/
HWND CreateButton(LPSTR text,int x,int y,int w,int h,HWND hwnd,HMENU idb)
{
    HWND shwnd=CreateWindow("Button",text,WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,x,y,w,h,hwnd,idb,(HINSTANCE)GetWindowLongPtr(hwnd,GWLP_HINSTANCE),NULL);
    return shwnd;
}
/**
 * 创建一个文本框
 * @param text 文本框的默认文本
 * @param x 文本框的x坐标
 * @param y 文本框的y坐标
 * @param w 文本框的宽
 * @param h 文本框的高
 * @param hwnd 父窗口的句柄
 * @param idb 文本框标识号
 * @return 创建文本框的句柄,创建失败为空
*/
HWND CreateEdit(LPSTR text,int x,int y,int w,int h,HWND hwnd,HMENU ide)
{
    HWND shwnd=CreateWindow("Edit",text,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE,x,y,w,h,hwnd,ide,(HINSTANCE)GetWindowLongPtr(hwnd,GWLP_HINSTANCE),NULL);  //生成组件
    return shwnd;
}
/**
 * 创建一个保存文件窗口
 * @param hwnd 父句柄
 * @return 返回文件路径
*/
string CreateSaveFileDilog(HWND hwnd)
{
    TCHAR szBuffer[MAX_PATH]={0};  //数据缓冲区
    BROWSEINFO bi;   
    ZeroMemory(&bi,sizeof(BROWSEINFO));   //用0来填充
    bi.hwndOwner=hwnd;   //父窗口句柄
    bi.pszDisplayName=szBuffer;  //设定缓冲区   
    bi.lpszTitle=NULL;  //标题
    bi.ulFlags=BIF_RETURNFSANCESTORS;  //返回一个节点   
    LPITEMIDLIST idl=SHBrowseForFolder(&bi);  //显示对话框   
    if (idl==NULL)  //文件名为空
        return "";   //文件列表 
    SHGetPathFromIDList(idl,szBuffer);  //将项标识符列表转换为文件系统路径
    return string(szBuffer);  
}
/**
 * 创建一个打开文件窗口
 * @param filter 文件过滤器
 * @param hwnd 父句柄
 * @return 返回文件路径
*/
string CreateOpenFileDilog(LPSTR filter,HWND hwnd)
{
    OPENFILENAME ofn;  //文件窗口
    CHAR szFile[255];  //缓存区
    ZeroMemory(&ofn,sizeof(ofn));  //归零
    ofn.lStructSize=sizeof(ofn);  //大小
    ofn.hwndOwner=hwnd;  //父句柄
    ofn.lpstrFile=szFile;  //文件缓存区
    ofn.lpstrFile[0]='\0';  
    ofn.nMaxFile=sizeof(szFile);  //文件大小
    ofn.lpstrFilter=filter;  //文件过滤器
    ofn.nFilterIndex=1;  //文件过滤器标识
    ofn.lpstrFileTitle=NULL;  //文件标题
    ofn.nMaxFileTitle=0;  
    ofn.lpstrInitialDir=NULL;  //初始位置
    ofn.Flags=OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
    if(GetOpenFileName(&ofn))  //读取文件名成功?
    {
        return ofn.lpstrFile;  
    }
    return "";  
}
/**
 * 窗口回调函数
 * @param hwnd 窗口句柄
 * @param Message 窗口事件
 * @param wParam 消息响应机制
 * @param lParam 消息响应机制
 * @return 返回其他消息
 * @remark 使用 @c WM_CREATE 初始化组件, @c WM_COMMAND 接受消息
 * @bug 当按下单选按钮时反应慢
*/
LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    /* 组件 */
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
    /* 消息响应 */
    switch(Message)
    {
        case WM_CREATE:
            /* 绘制组件 */
            e1=CreateEdit((char*)"",80,12,421,26,hwnd,(HMENU)IDE_1);
            b1=CreateButton((char*)"选择",500,12,73,26,hwnd,(HMENU)IDB_1);
            cb1=CreateCheckBox((char*)"图标",10,60,70,26,hwnd,(HMENU)IDCB_1);
            e2=CreateEdit((char*)"",80,60,421,26,hwnd,(HMENU)IDE_2);
            b2=CreateButton((char*)"选择",500,60,73,26,hwnd,(HMENU)IDB_2);
            cb2=CreateCheckBox((char*)"版本",10,100,70,26,hwnd,(HMENU)IDCB_2);
            e3=CreateEdit((char*)"",80,100,421,26,hwnd,(HMENU)IDE_3);
            b3=CreateButton((char*)"选择",500,100,73,26,hwnd,(HMENU)IDB_3);
            e4=CreateEdit((char*)"",80,150,421,26,hwnd,(HMENU)IDE_4);
            b4=CreateButton((char*)"选择",500,150,73,26,hwnd,(HMENU)IDB_4);
            rb1=CreateRadioButton((char*)"window",145,180,135,40,hwnd,(HMENU)IDRB_1);
            rb2=CreateRadioButton((char*)"cmd",300,180,135,40,hwnd,(HMENU)IDRB_2);
            b5=CreateButton((char*)"转换",0,225,205,85,hwnd,(HMENU)IDB_5);
            b6=CreateButton((char*)"查看文件位置",400,225,205,85,hwnd,(HMENU)IDB_6);
            SendMessage(rb2,BM_SETCHECK,BST_CHECKED,0);  //初始化rb2
        case WM_PAINT:
            /* 绘制文字 */
            hdc=BeginPaint(hwnd,&ps);  //开始绘制
            TextOut(hdc,10,15,"输入文件:",9);  
            TextOut(hdc,10,155,"输出文件:",9);
            TextOut(hdc,10,190,"模式:",5);
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDB_1:
                    /* 按钮1被按下 */
                    FileName=CreateOpenFileDilog((char*)"cpp(*.cpp)\0*.cpp\0",hwnd);
                    if(SetWindowText(e1,FileName.c_str())==0)error("ERROR!",199);  
                    return 0;
                case IDCB_1:
                    /* 多选按钮1被按下 */
                    i1=!i1;
                    //cout<<i<<endl;
                    /* 切换选择模式 */
                    if(!i1)
                        SendMessage(cb1,BM_SETCHECK,BST_UNCHECKED,0);
                    else
                        SendMessage(cb1,BM_SETCHECK,BST_CHECKED,0);
                    return 0;
                case IDB_2:
                    /* 按钮2被按下 */
                    FileName=CreateOpenFileDilog((char*)"图标(*.ico)\0*.ico\0",hwnd);
                    if(SetWindowText(e2,FileName.c_str())==0)error("ERROR!",214);
                    return 0;
                case IDCB_2:
                    /* 多选按钮2被按下 */
                    i2=!i2;
                    /* 切换选择模式 */
                    if(!i2)
                        SendMessage(cb2,BM_SETCHECK,BST_UNCHECKED,0);
                    else
                        SendMessage(cb2,BM_SETCHECK,BST_CHECKED,0);
                    return 0;
                case IDB_3:
                    /* 按钮3被按下 */
                    FileName=CreateOpenFileDilog((char*)"版本(*.txt)\0*.txt\0",hwnd);
                    if(SetWindowText(e3,FileName.c_str())==0)error("ERROR!",228);
                    return 0;
                case IDB_4:
                    /* 按钮4被按下 */
                    FileName=CreateSaveFileDilog(hwnd);
                    if(SetWindowText(e4,FileName.c_str())==0)error("ERROR!",233);
                    return 0;
                case IDRB_1:
                    /* 单选按钮1被按下 */
                    i3=!i3;
                    if(i3)
                    {
                        SendMessage(rb1,BM_SETCHECK,BST_CHECKED,0);
                        SendMessage(rb2,BM_SETCHECK,BST_UNCHECKED,0);
                    }
                    return 0;
                case IDRB_2:
                    /* 单选按钮2被按下 */
                    i3=!i3;
                    if(i3)
                    {
                        SendMessage(rb1,BM_SETCHECK,BST_UNCHECKED,0);
                        SendMessage(rb2,BM_SETCHECK,BST_CHECKED,0);
                    }
                    return 0;
                case IDB_5:
                    /* 按钮5被按下 */
                    /* 开始转换 */
                    /* 获取文字 */
                    GetWindowText(e1,buff,255);  
                    running[0]=string(buff);
                    GetWindowText(e2,buff,255);
                    running[1]=string(buff);
                    GetWindowText(e3,buff,255);
                    running[2]=string(buff);
                    GetWindowText(e4,buff,255);
                    running[3]=string(buff);
                    if(running[0]=="")
                        error("致命错误:\n  无输入文件",288);
                    /* 文件操作 */
                    file1.open("C:\\ProgramData\\data.rc",ios::out|ios::trunc);
                    if(running[1]!=""&&SendMessage(cb1,BM_GETCHECK,0,0)==BST_CHECKED)
                    {
                        CopyFile(running[1].c_str(),"C:\\ProgramData\\1.ico",FALSE);  //拷贝文件
                        file1<<"id ICON "<<'"'<<"1.ico"<<'"'<<endl;  //加入rc
                    }
                    if(running[2]!=""&&SendMessage(cb2,BM_GETCHECK,0,0)==BST_CHECKED)
                    {
                        CopyFile(running[2].c_str(),"C:\\ProgramData\\1.txt",FALSE);  //拷贝文件
                        fstream f;
                        /* 获取文本文件中每一行的文本 */
                        f.open(running[2],ios::in);
                        for(int i=0;i<100;i++)
                        {
                            f.getline(buff,2555);
                            file1<<string(buff)<<endl;
                        }
                    }
                    /* 没选输出路径？ */
                    if(running[3]=="")
                        running[3]="C:";
                    system("windres -i C:\\ProgramData\\data.rc -o C:\\ProgramData\\data.o");  //windres编译
                    file1.close();  //释放文件内存
                    //cout<<running[3];
                    temp="g++ \""+running[0]+"\" C:\\ProgramData\\data.o -o \""+running[3]+"\\output.exe\" -leasyx -static -lgdi32 -lcomdlg32 -lComCtl32";  //运行参数
                    if(SendMessage(rb1,BM_GETCHECK,0,0)==BST_CHECKED)  //是窗口程序
                        temp+=" -mwindows";  //加入指令
                    cout<<temp<<endl;
                    system(temp.c_str());  //运行指令
                    MessageBox(hwnd,"转换完成","完成!",MB_OK|MB_ICONINFORMATION);  //弹窗提醒
                    /* 删除所有临时文件 */
                    remove("C:\\ProgramData\\1.ico");
                    remove("C:\\ProgramData\\1.txt");
                    remove("C:\\ProgramData\\data.o");
                    remove("C:\\ProgramData\\data.rc");
                    return 0;
                case IDB_6:
                    /* 按钮6被按下？ */
                    temp="start "+running[3];  //运行参数
                    system(temp.c_str());  //运行
                    return 0;
            }
            break;
        case WM_CLOSE:
            /* 窗口关闭? */
            if(MessageBox(hwnd,"确定要退出吗?","退出",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
                DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:  //其他消息
            return DefWindowProc(hwnd,Message,wParam,lParam);
    }
    return 0;
}
/**
 * Win32程序的入口
 * @param hinstance 应用程序当前实例的句柄
 * @param hPrevlnstance 应用程序的先前实例的句柄
 * @param lpcmdline 指向应用程序命令行的字符串的指针
 * @param nCmdShow 指明窗口如何显示
 * @return 退出代码
*/
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hPrevlnstance,LPSTR lpcmdline,int nCmdShow)
{
    WNDCLASSEX wc;  //一个窗口
    HWND hwnd;  //窗口句柄
    MSG msg; //窗口消息
    memset(&wc,0,sizeof(wc));  //归零
    wc.cbSize=sizeof(WNDCLASSEX);  //WNDCLASSEX的大小
    wc.lpfnWndProc=WndProc;  //窗口处理函数的指针
    wc.hInstance=hinstance;  //本模块的实例句柄
    wc.hCursor=LoadCursor(NULL,IDC_ARROW);  //光标的句柄
    wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);  //背景画刷的句柄
    wc.lpszClassName="WindowClass"; //指向类名称的指针
    wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);  //图标的句柄
    wc.hIconSm=LoadIcon(NULL,IDI_APPLICATION);  //和窗口类关联的小图标
    if(!RegisterClassEx(&wc))  //注册失败
        error("Window Registration Failed",346);
    hwnd=CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","CPP COVERT",WS_VISIBLE|WS_OVERLAPPEDWINDOW,DEFAULT_X,DEFAULT_Y,DEFAULT_WIDTH,DEFAULT_HEIGHT,NULL,NULL,hinstance,NULL);  //创建窗口
    if(hwnd==NULL)  //创建失败
        error("Window Creation Falied",349);
    /* 获取消息 */
    while(GetMessage(&msg,NULL,0,0)>0)  
    {
        TranslateMessage(&msg);  //将键代码转换为字符(如果存在)
        DispatchMessage(&msg);  //将其发送到WndProc
    }
    return msg.wParam;
}

