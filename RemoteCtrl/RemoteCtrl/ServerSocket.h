#pragma once
#include "pch.h"
#include "framework.h"  //包含一些网络编程的头文件
class CServerSocket
{
public:
	static CServerSocket* getInstance() {   //这样就可以在RCcpp调用 CServerSocket::getInstance();
		if (m_instance == NULL) {                     //静态函数没有this指针们不能直接访问成员变量m_instance，需要把m_instance也设置成静态
			m_instance = new CServerSocket();
		}
		return m_instance;
	}
	bool InitSocket() {   //初始化集成一个函数
		//socket创建
		SOCKET serv_sock = socket(PF_INET, SOCK_STREAM, 0);
		if (serv_sock == -1) return false;
		//TODO：校验
		sockaddr_in serv_adr, client_adr;
		memset(&serv_adr, 0, sizeof(serv_adr)); //初始化
		serv_adr.sin_family = AF_INET; //
		serv_adr.sin_addr.s_addr = INADDR_ANY; //在所有ip都监听，（any）不能假定都一个单独的ip
		serv_adr.sin_port = htons(9527);   //设置监听端口 
		//绑定
		if (bind(serv_sock, (sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) {
			return false;
		}
		//监听
		if (listen(serv_sock, 1) == -1) {
			return false;
		}
		return true;
	}
	bool AcceptClient() {
		sockaddr_in  client_adr;
		int cli_sz = sizeof(client_adr);

		m_client = accept(m_sock, (sockaddr*)&client_adr, &cli_sz);
		if (m_client == -1) {
			return false;
		}
		return true;
	}
	int DealCommand() {
		if (m_client == -1) return false;
		char buffer[1024] = "";
		while (true) {
			int len = recv(m_client, buffer, sizeof(buffer), 0);
			if (len <= 0) {
				return -1;
			}
		}
	}
	bool Send(const char* pData, int nSize) {
		if (m_client == -1)return false;
		return send(m_client, pData, nSize, 0) > 0;
	}


private:    //把构造和析构设为私有，别人就不能调用了

	SOCKET m_client;
	SOCKET m_sock;
	CServerSocket& operator =(const CServerSocket& ss) {}
	CServerSocket(const CServerSocket& ss) {
		m_sock = ss.m_sock;
		m_client = ss.m_client;
	}
	CServerSocket() {          //构造
		m_sock = INVALID_SOCKET;
		if (InitSockEnv() == FALSE) {
			MessageBox(NULL, _T("无法初始化套接字环境，请检查网络设置！"), _T("初始化错误！"), MB_OK | MB_ICONERROR);
			exit(0);
		}
		m_sock = socket(PF_INET, SOCK_STREAM, 0);
	}
	~CServerSocket() {  //析构
		closesocket(m_sock);
		WSACleanup();
	}
	BOOL InitSockEnv() {      //判断初始化
		WSADATA data;
		if (WSAStartup(MAKEWORD(1, 1), &data) != 0) {
			return FALSE;
		} return TRUE;
	}
	//以下用来保证调用析构
	static void releaseInstance() {
		if (m_instance != NULL) {
			CServerSocket* tmp = m_instance;
			m_instance = NULL;
			delete tmp;
		}
	}
	static CServerSocket* m_instance;
	class CHelper {
	public:
		CHelper() {
			CServerSocket::getInstance();
		}
		~CHelper() {
			CServerSocket::releaseInstance();
		}
	};
	static CHelper m_helper; //是私有的
};
extern CServerSocket server; //声明一个外部变量，这样其他人（引入.h的)就可以用外部变量
