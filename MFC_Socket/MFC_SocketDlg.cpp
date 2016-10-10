
// MFC_SocketDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFC_Socket.h"
#include "MFC_SocketDlg.h"
#include "afxdialogex.h"
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
struct THREAD_SERVER
{
	bool  Continue;
	HWND hWnd;
}Thread_Server;
bool m_exit;
// CMFC_SocketDlg 對話方塊



CMFC_SocketDlg::CMFC_SocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_SocketDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_SocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_SocketDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_startServer, &CMFC_SocketDlg::OnBnClickedButtonstartserver)
	ON_BN_CLICKED(IDC_BUTTON_clientSend, &CMFC_SocketDlg::OnBnClickedButtonclientsend)
END_MESSAGE_MAP()


// CMFC_SocketDlg 訊息處理常式

BOOL CMFC_SocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO:  在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}


void CMFC_SocketDlg::OnBnClickedButtonstartserver()
{
	Thread_Server.hWnd = m_hWnd;
	Thread_Server.Continue = TRUE;
	m_pThread = AfxBeginThread(ThreadServerFun, (LPVOID)&Thread_Server);
	UpdateData();
}
UINT CMFC_SocketDlg::ThreadServerFun(LPVOID lParam)
{
	THREAD_SERVER * Thread_Server = (THREAD_SERVER *)lParam;
	CMFC_SocketDlg * hWnd = (CMFC_SocketDlg *)CWnd::FromHandle((HWND)Thread_Server->hWnd);


	while (1)
	{
		if (!AfxSocketInit())
			AfxMessageBox(L"Failed to Initialize Sockets");

		m_exit = false;
		//creat two socket
		CSocket aSocket, serverSocket;
		if (!aSocket.Socket())
			AfxMessageBox(L"Create Faild");

		BOOL bOptVal = TRUE;
		int bOptLen = sizeof(BOOL);

		aSocket.SetSockOpt(SO_REUSEADDR, (void *)&bOptVal, bOptLen, SOL_SOCKET);

		CString strServerPort;
		hWnd->GetDlgItemText(IDC_EDIT_serverPort, strServerPort);
		int nServerPort = _ttoi(strServerPort);
		if (!aSocket.Bind(nServerPort))
			AfxMessageBox(L"Bind Faild");
		if (!aSocket.Listen(10))
			AfxMessageBox(L"Listen Faild");


		hWnd->GetDlgItem(IDC_EDIT_serverBuf)->SetWindowText(L"server on.  Port: " + strServerPort);

		while (!m_exit)
		{
			if (!aSocket.Accept(serverSocket))
			{
				continue;
			}
			else
			{
				char szRecvMsg[256] = { 0 };
				serverSocket.Receive(szRecvMsg, 256);

				CString strRecvMsg;
				strRecvMsg = szRecvMsg;
				
				CString report;

				report = (L"This is server. Your text is : ");
				CString ClientIP;
				UINT ClientPort;
				serverSocket.GetPeerName(ClientIP, ClientPort);
				report = report + strRecvMsg + L"   from:" + ClientIP;
				hWnd->GetDlgItem(IDC_EDIT_serverBuf)->SetWindowText(ClientIP + L" : "+strRecvMsg);

				char c_report[100];
				USES_CONVERSION;
				strcpy_s(c_report, T2A(report));
				serverSocket.Send(c_report, sizeof(c_report));
				serverSocket.Close();
				//m_exit = true;
			}

		}

		aSocket.Close();
		serverSocket.Close();

	}
	AfxMessageBox(L"sever close");


	//-----end thread-----
	Thread_Server->Continue = false;
	::PostMessage(hWnd->m_hWnd, (WM_USER + 1), 0, 0);
	return(0);
}

void CMFC_SocketDlg::OnBnClickedButtonclientsend()
{
	AfxSocketInit();
	CSocket aSocket;
	CString strIP;
	CString strPort;
	char resp[20];

	if (!aSocket.Create())
	{
		AfxMessageBox(L"Creat Faild");
		return;
	}

	GetDlgItemText(IDC_EDIT_serverIP, strIP);
	GetDlgItemText(IDC_EDIT_serverPort, strPort);
	int nPort = _ttoi(strPort);
	if (aSocket.Connect(strIP, nPort))
	{
		char szRecValue[1024] = { 0 };
		CString str_send;
		GetDlgItemText(IDC_EDIT_sendMessage, str_send);
		USES_CONVERSION;
		strcpy_s(resp, T2A(str_send));

		aSocket.Send(resp, sizeof(resp));
		aSocket.Receive((void *)szRecValue, 1024);
		CString temp;
		temp = (szRecValue);
		GetDlgItem(IDC_EDIT_clientBuf)->SetWindowText(temp);
	}
	else
	{
		AfxMessageBox(L"Creat Faild(Connect)");
	}
	aSocket.Close();
}
