
// MFC_SocketDlg.h : 標頭檔
//

#pragma once


// CMFC_SocketDlg 對話方塊
class CMFC_SocketDlg : public CDialogEx
{
// 建構
public:
	CMFC_SocketDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_MFC_SOCKET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	CWinThread * m_pThread;
	static UINT ThreadServerFun(LPVOID lParam);

public:
	afx_msg void OnBnClickedButtonstartserver();
	afx_msg void OnBnClickedButtonclientsend();
};
