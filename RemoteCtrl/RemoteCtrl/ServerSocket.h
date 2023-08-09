#pragma once
#include "pch.h"
#include "framework.h"  //����һЩ�����̵�ͷ�ļ�
class CServerSocket
{
public:
	static CServerSocket* getInstance() {   //�����Ϳ�����RCcpp���� CServerSocket::getInstance();
		if (m_instance == NULL) {                     //��̬����û��thisָ���ǲ���ֱ�ӷ��ʳ�Ա����m_instance����Ҫ��m_instanceҲ���óɾ�̬
			m_instance = new CServerSocket();
		}
		return m_instance;
	}
	bool InitSocket() {   //��ʼ������һ������
		//socket����
		SOCKET serv_sock = socket(PF_INET, SOCK_STREAM, 0);
		if (serv_sock == -1) return false;
		//TODO��У��
		sockaddr_in serv_adr, client_adr;
		memset(&serv_adr, 0, sizeof(serv_adr)); //��ʼ��
		serv_adr.sin_family = AF_INET; //
		serv_adr.sin_addr.s_addr = INADDR_ANY; //������ip����������any�����ܼٶ���һ��������ip
		serv_adr.sin_port = htons(9527);   //���ü����˿� 
		//��
		if (bind(serv_sock, (sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) {
			return false;
		}
		//����
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


private:    //�ѹ����������Ϊ˽�У����˾Ͳ��ܵ�����

	SOCKET m_client;
	SOCKET m_sock;
	CServerSocket& operator =(const CServerSocket& ss) {}
	CServerSocket(const CServerSocket& ss) {
		m_sock = ss.m_sock;
		m_client = ss.m_client;
	}
	CServerSocket() {          //����
		m_sock = INVALID_SOCKET;
		if (InitSockEnv() == FALSE) {
			MessageBox(NULL, _T("�޷���ʼ���׽��ֻ����������������ã�"), _T("��ʼ������"), MB_OK | MB_ICONERROR);
			exit(0);
		}
		m_sock = socket(PF_INET, SOCK_STREAM, 0);
	}
	~CServerSocket() {  //����
		closesocket(m_sock);
		WSACleanup();
	}
	BOOL InitSockEnv() {      //�жϳ�ʼ��
		WSADATA data;
		if (WSAStartup(MAKEWORD(1, 1), &data) != 0) {
			return FALSE;
		} return TRUE;
	}
	//����������֤��������
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
	static CHelper m_helper; //��˽�е�
};
extern CServerSocket server; //����һ���ⲿ���������������ˣ�����.h��)�Ϳ������ⲿ����
