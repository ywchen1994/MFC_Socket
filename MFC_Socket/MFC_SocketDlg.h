
// MFC_SocketDlg.h : ���Y��
//

#pragma once


// CMFC_SocketDlg ��ܤ��
class CMFC_SocketDlg : public CDialogEx
{
// �غc
public:
	CMFC_SocketDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_MFC_SOCKET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	CWinThread * m_pThread;
	static UINT ThreadServerFun(LPVOID lParam);

public:
	afx_msg void OnBnClickedButtonstartserver();
	afx_msg void OnBnClickedButtonclientsend();
};
