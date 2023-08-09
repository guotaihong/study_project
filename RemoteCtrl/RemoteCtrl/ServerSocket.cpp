#include "pch.h"
#include "ServerSocket.h"

//CServerSocket server;
CServerSocket* CServerSocket::m_instance = NULL;  //把这个置空
CServerSocket::CHelper CServerSocket::m_helper;   //CServerSocket::CHelper是类  CServerSocket::m_helper;是成员变量
CServerSocket* pserver = CServerSocket::getInstance();//
/*这里会调用到serversocket.h里
static CServerSocket* getInstance() {   //这样就可以在RCcpp调用 CServerSocket::getInstance();
		if (m_instance == NULL) {                     //静态函数没有this指针们不能直接访问成员变量m_instance，需要把m_instance也设置成静态
			m_instance = new CServerSocket();
		}
return m_instance;
*/
