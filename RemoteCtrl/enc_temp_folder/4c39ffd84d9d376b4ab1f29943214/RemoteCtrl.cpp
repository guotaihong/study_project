// RemoteCtrl.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//TODO代表要后续完善的意思

#include "pch.h"
#include "framework.h"
#include "RemoteCtrl.h"
#include "ServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)  
    {
        // 初始化 MFC 并在失败时  显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 在此处为应用程序的行为编写代码。
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {  //进度的可控性 2 连接的方便性3 可行性评估，提高暴露风险
            // TODO: （在此处为应用程序的行为编写代码）要做的事：socket、bind、listen、accept、read、write、close。万年不变，只是linux和windows函数不同
            //套接字初始化（在wid下面需要环境初始化，linux不需要
            //server;
            {
                //CServerSocket local; 
            }
            CServerSocket*pserver=  CServerSocket::getInstance();
            int count= 0;
            if (pserver->InitSocket() == false) {    
                MessageBox(NULL, _T("网络初始化异常，未能成功初始化，请检查网络状态！"), _T("网络初始化失败！"), MB_OK | MB_ICONERROR);
                exit(0);
            }
            //网络初始化正常后 考虑AcceptClient
            while (CServerSocket::getInstance() != NULL) { //一直循环
                if (pserver->AcceptClient() == false) {
                    if (count >= 3) {
                        MessageBox(NULL, _T("多次无法正常接入用户，结束程序！"), _T("接入用户失败！"), MB_OK | MB_ICONERROR);
                   }
                    MessageBox(NULL, _T("正常接入用户，自动重试！"), _T("接入用户失败！"), MB_OK | MB_ICONERROR);  //自动==while
                    count++;
                }
                int ret = pserver->DealCommand();

            }
            // 下面的两句已经整合到一个初始化函数了
            //  WSADATA data;  
            //WSAStartup(MAKEWORD(1, 1), &data);   //TODO 后需要做返回值处理  这两行wdn独有
             
     
            //WSACleanup();//与WSAStartup一对一匹配


        }
    }
    else
    {
        // TODO: 更改错误代码以符合需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

    return nRetCode;
}
