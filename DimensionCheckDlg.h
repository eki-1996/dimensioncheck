
// DimensionCheckDlg.h : �إå��` �ե�����
//

#pragma once
#include "afxwin.h"


// CDimensionCheckDlg ��������
class CDimensionCheckDlg : public CDialogEx
{
// ���󥹥ȥ饯�����
public:
	CDimensionCheckDlg(CWnd* pParent = NULL);	// �˜ʥ��󥹥ȥ饯���`

// �������� �ǩ`��
	enum { IDD = IDD_DIMENSIONCHECK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ���ݩ`��


// �gװ
protected:
	HICON m_hIcon;

	// ���ɤ��줿����å��`����굱���v��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_vNafilepath;
	CString m_vdxffolderpath;
	CString NoDiPro;
	CString DiPro;
	CString NotCoincide;
	afx_msg void OnBnClickedButton1();
	CButton Conform;
	CButton CheckStart;
	CButton CheckAll;
	CButton Cancle;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CEdit m_cNafolderpath;
	CEdit m_cdxffolderpath;
	afx_msg void OnBnClickedButton2();
	BOOL GetFilePathList(CList<CString, CString &> &FilePath);
	BOOL GetAllFilePathList(CList<CString, CString &> &AllFilePath);
	BOOL GetNaFilePathList(CList<CString, CString &> &NaFilePath);
	BOOL DimensionCheck(CList<CString, CString &> &FilePath);
	void MakeCheckedFolderPath(CList<CString, CString &> &FilePath, CList<CString, CString &> &CheckedFolderPath);
	BOOL CheckFake(CString *str);
	void TakeOutUnNeCircle(CStringArray &circle, CStringArray &centerline);
	BOOL CheckCoincide(const CStringArray &circle, const CStringArray &centerline, CStringArray &notcocircle);
	BOOL CheckDistance( const CStringArray &circle, const CStringArray &centerline, int i, int j);
	BOOL CheckFootPointSlope( const CStringArray &circle, const CStringArray &centerline, int i, int j);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
};
