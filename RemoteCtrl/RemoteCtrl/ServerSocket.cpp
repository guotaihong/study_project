#include "pch.h"
#include "ServerSocket.h"

//CServerSocket server;
CServerSocket* CServerSocket::m_instance = NULL;  //������ÿ�
CServerSocket::CHelper CServerSocket::m_helper;   //CServerSocket::CHelper����  CServerSocket::m_helper;�ǳ�Ա����
CServerSocket* pserver = CServerSocket::getInstance();//
/*�������õ�serversocket.h��
static CServerSocket* getInstance() {   //�����Ϳ�����RCcpp���� CServerSocket::getInstance();
		if (m_instance == NULL) {                     //��̬����û��thisָ���ǲ���ֱ�ӷ��ʳ�Ա����m_instance����Ҫ��m_instanceҲ���óɾ�̬
			m_instance = new CServerSocket();
		}
return m_instance;
*/
