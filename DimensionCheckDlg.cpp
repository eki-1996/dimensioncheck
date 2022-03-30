
// DimensionCheckDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "DimensionCheck.h"
#include "DimensionCheckDlg.h"
#include "afxdialogex.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CREATELINE(x,y,handle,handle330)  \
	checkedfile.Write(_T("MTEXT\r\n"), 6); \
	checkedfile.Write(_T("  5\r\n"), 4); \
	checkedfile.Write(handle+_T("\r\n"), handle.GetLength()+1); \
	checkedfile.Write(_T("330\r\n"), 4); \
	checkedfile.Write(handle330+_T("\r\n"), handle330.GetLength()+1); \
	checkedfile.Write(_T("100\r\n"), 4); \
	checkedfile.Write(_T("AcDbEntity\r\n"), 11); \
	checkedfile.Write(_T("  8\r\n"), 4); \
	checkedfile.Write(_T("0\r\n"), 2); \
	checkedfile.Write(_T("100\r\n"), 4); \
	checkedfile.Write(_T("AcDbMText\r\n"), 10); \
	checkedfile.Write(_T(" 10\r\n"), 4); \
	checkedfile.Write(x+_T("\r\n"), x.GetLength()+1); \
	checkedfile.Write(_T(" 20\r\n"), 4); \
	checkedfile.Write(y+_T("\r\n"), y.GetLength()+1); \
	checkedfile.Write(_T(" 30\r\n"), 4); \
	checkedfile.Write(_T("0.0\r\n"), 4); \
	checkedfile.Write(_T(" 40\r\n"), 4); \
	checkedfile.Write(_T("2.5\r\n"), 4); \
	checkedfile.Write(_T(" 41\r\n"), 4); \
	checkedfile.Write(_T("9\r\n"), 2); \
	checkedfile.Write(_T(" 46\r\n"), 4); \
	checkedfile.Write(_T("0.0\r\n"), 4); \
	checkedfile.Write(_T(" 71\r\n"), 4); \
	checkedfile.Write(_T("     1\r\n"), 7); \
	checkedfile.Write(_T(" 72\r\n"), 4); \
	checkedfile.Write(_T("     5\r\n"), 7); \
	checkedfile.Write(_T("  1\r\n"), 4); \
	checkedfile.Write(_T("ERROR\r\n"), 6); \
	checkedfile.Write(_T(" 73\r\n"), 4); \
	checkedfile.Write(_T("     1\r\n"), 7); \
	checkedfile.Write(_T("  0\r\n"), 4); \

#define GETMAXHANDLE \
	if(str==_T("  5")) { \
		dxffile.ReadString(str); \
		checkedfile.Write(str+_T("\r\n"), str.GetLength()+1); \
		if(str.GetLength()>maxhandle.GetLength()) { \
			maxhandle=str; \
		} \
	} \

//CList<CString, CString &> FilePathList;
// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDimensionCheckDlg ダイアログ




CDimensionCheckDlg::CDimensionCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDimensionCheckDlg::IDD, pParent)
	, m_vNafilepath(_T(""))
	, m_vdxffolderpath(_T(""))
	, DiPro(_T(""))
	, NoDiPro(_T(""))
	, NotCoincide(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDimensionCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_vNafilepath);
	DDX_Text(pDX, IDC_EDIT2, m_vdxffolderpath);
	DDX_Text(pDX, IDC_EDIT3, NoDiPro);
	DDX_Text(pDX, IDC_EDIT4, DiPro);
	DDX_Text(pDX, IDC_EDIT5, NotCoincide);
	DDX_Control(pDX, IDC_BUTTON1, Conform);
	DDX_Control(pDX, IDC_BUTTON2, CheckStart);
	DDX_Control(pDX, IDC_BUTTON4, CheckAll);
	DDX_Control(pDX, IDC_BUTTON5, Cancle);
	DDX_Control(pDX, IDC_EDIT1, m_cNafolderpath);
	DDX_Control(pDX, IDC_EDIT2, m_cdxffolderpath);
}

BEGIN_MESSAGE_MAP(CDimensionCheckDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDimensionCheckDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDimensionCheckDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDimensionCheckDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CDimensionCheckDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDimensionCheckDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CDimensionCheckDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CDimensionCheckDlg メッセージ ハンドラー

BOOL CDimensionCheckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	Conform.EnableWindow(TRUE);
	CheckStart.EnableWindow(FALSE);
	CheckAll.EnableWindow(FALSE);
	Cancle.EnableWindow(FALSE);


	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CDimensionCheckDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CDimensionCheckDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CDimensionCheckDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDimensionCheckDlg::OnBnClickedButton1()//確認ボタン
{
	CWnd::UpdateData(TRUE);
	m_cNafolderpath.EnableWindow(FALSE);
	m_cdxffolderpath.EnableWindow(FALSE);
	int nullnum=0;//二種類のパスの入力さてない数
	//名前フォルダのパスが入力状況によってdxfフォルダのパスのすべてのファイルを処理すると名前ファイル内のファイルを処理するを空けて処理する

	//dxfフォルダのパスは必要
	if(m_vdxffolderpath=="") {
		nullnum++;
		CString message=_T("dxfフォルダのパスを入力してください！");
		AfxMessageBox(message);
		m_cNafolderpath.EnableWindow(TRUE);
	    m_cdxffolderpath.EnableWindow(TRUE);
		return;
	}

	//dxfフォルダのパスだけの場合
	if(m_vNafilepath=="") {
		nullnum++;
		CString message=_T("名前フォルダのパスがない場合はdxfフォルダパス下のすべてファイルが寸法チェックの対象になりますが、よろしいでしょうか？");
		AfxMessageBox(message);
		CheckAll.EnableWindow(TRUE);
		Cancle.EnableWindow(TRUE);
		Conform.EnableWindow(FALSE);
		return;
	}
	//両方とも入力された場合
	if(nullnum==0) {
		Conform.EnableWindow(FALSE);
		CheckStart.EnableWindow(TRUE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CDimensionCheckDlg::OnBnClickedButton4()
{
	//FINDFile
	CheckStart.EnableWindow(TRUE);
	CheckAll.EnableWindow(FALSE);
	Cancle.EnableWindow(FALSE);
	// TODO: 在此添加控件通知处理程序代码
}


void CDimensionCheckDlg::OnBnClickedButton5()
{
	m_cNafolderpath.EnableWindow(TRUE);
	m_cdxffolderpath.EnableWindow(TRUE);
	Conform.EnableWindow(TRUE);
	CheckAll.EnableWindow(FALSE);
	Cancle.EnableWindow(FALSE);
	// TODO: 在此添加控件通知处理程序代码
}


void CDimensionCheckDlg::OnBnClickedButton2()
{
	CList<CString, CString &> FilePathList;
	if(GetFilePathList(FilePathList)) {
		DimensionCheck(FilePathList);
	}
	else {
		OnInitDialog();
		return ;
	}
	// TODO: 在此添加控件通知处理程序代码
}

BOOL CDimensionCheckDlg::GetFilePathList(CList<CString, CString &> &FilePath)
{
	if(m_vNafilepath=="") {
		return GetAllFilePathList(FilePath);
	}
	else {
		return GetNaFilePathList(FilePath);
	}
}

BOOL CDimensionCheckDlg::GetAllFilePathList(CList<CString, CString &> &AllFilePath)  //すべてのファイルを対象
{
	 // ファイル検索を開始します。
    CFileFind fileFind;
    BOOL bResult = fileFind.FindFile(m_vdxffolderpath+_T("\\*.dxf"));

    // ファイル検索ができない場合、終了します。
    if (!bResult) return FALSE;
	//CList<CString, CString &> PathList;

    // ファイルが検索できる間繰り返します。
    do {
		// ファイルを検索します。
        // 次のファイル・ディレクトリがない場合、FALSEが返却されます。
        bResult = fileFind.FindNextFile();
        // "."または".."の場合、次を検索します。
        if (fileFind.IsDots()) continue;
    
        // 検索した結果がディレクトリの場合
        //CString msg;
        //CString filePath = fileFind.GetFilePath();
        if (fileFind.IsDirectory()) {
            /*msg.Format(_T("Directory:%s\n"), filePath);
            AfxOutputDebugString(msg);  
            
            // サブディレクトリを検索する場合、再帰呼出しします。
            CPath subDir = filePath;
            // ディレクトリ内のすべてのファイル・ディレクトリを対象とするため
            // ワイルドカード"*"を指定します。
            subDir.Append(_T("*"));
            GetFileList(subDir);
			*/
			continue;
        }
		
        // ファイルの場合
        else {
			AllFilePath.AddTail(fileFind.GetFilePath());
        }
    }
	while (bResult);
	return TRUE;
}

BOOL CDimensionCheckDlg::GetNaFilePathList(CList<CString, CString &> &NaFilePath)  //名前ファイルのファイルだけを対象
{
	//CList<CString, CString &> PathList;
	if (!PathFileExists(m_vNafilepath)) {
		return FALSE;
	}
	CStdioFile namefile;
	if (!namefile.Open(m_vNafilepath, CFile::modeRead)) {
		return FALSE;
	}
	CString strValue = _T("");
	while(namefile.ReadString(strValue)) {
		NaFilePath.AddTail(m_vdxffolderpath+_T("\\")+strValue+_T(".dxf"));
	}
	namefile.Close();
	return TRUE;
}

BOOL CDimensionCheckDlg::DimensionCheck(CList<CString, CString &> &FilePath)
{
	CStdioFile dxffile;
	CStdioFile checkedfile;
	CList<CString, CString &> CheckedFolderPath;
	MakeCheckedFolderPath(FilePath, CheckedFolderPath);
	CString str;
	for(int i=0; i<FilePath.GetCount(); i++) {
		if(!dxffile.Open(FilePath.GetAt(FilePath.FindIndex(i)),CFile::modeRead)) {
			return FALSE;
		}
		if(!checkedfile.Open(CheckedFolderPath.GetAt(CheckedFolderPath.FindIndex(i)), CFile::modeCreate|CFile::modeWrite)) {
			return FALSE;
		}
		CString maxhandle=_T(""), handle330;
		int handleint=0x0;
		CStringArray cstrarray,circle,centerline,wrodimension, notcocircle;   //circle contains center X Y, line contains start point X1 Y1 end point X2 Y2 (!change Z to 0)
		int mark=0,fake=0,notcoincide=0;
		while(!dxffile.ReadString(str)==NULL){
			checkedfile.Write(str+_T("\r\n"), str.GetLength()+1);
			GETMAXHANDLE;
			if(str==_T("ENTITIES")){
				dxffile.ReadString(str);
				checkedfile.Write(str+_T("\r\n"), str.GetLength()+1);
				dxffile.ReadString(str);
				checkedfile.Write(str+_T("\r\n"), str.GetLength()+1);
				while(str!=_T("ENDSEC")){      //while(str!=_T("  0"))
					GETMAXHANDLE;
					if(str==_T("330")) {
						dxffile.ReadString(str);
						checkedfile.Write(str+_T("\r\n"), str.GetLength()+1);
						handle330=str;
					}
					if(str==_T("CIRCLE")){
						mark=1;
						while(str!=_T("  0")){
							dxffile.ReadString(str);
							cstrarray.Add(str);
							//GETMAXHANDLE;
							if(str==_T(" 10")){
								dxffile.ReadString(str);
								circle.Add(str);
								cstrarray.Add(str);
							}
							if(str==_T(" 20")){
								dxffile.ReadString(str);
								circle.Add(str);
								cstrarray.Add(str);
							}
							if(str==_T(" 40")){
								dxffile.ReadString(str);
								circle.Add(str);
								cstrarray.Add(str);
							}
						}
					}
					if(str==_T("LINE")){
						while(str!=_T("  0")){
							dxffile.ReadString(str);
							checkedfile.Write(str+_T("\r\n"), str.GetLength()+1);
							//GETMAXHANDLE;
							if(str==_T("CENTER")) {
								mark=1;
								while(str!=_T("  0")){
									dxffile.ReadString(str);
									cstrarray.Add(str);
									if(str==_T(" 10")){
										dxffile.ReadString(str);
										centerline.Add(str);
										cstrarray.Add(str);
									}
									if(str==_T(" 20")){
										dxffile.ReadString(str);
										centerline.Add(str);
										cstrarray.Add(str);
									}
									if(str==_T(" 11")){
										dxffile.ReadString(str);
										centerline.Add(str);
										cstrarray.Add(str);
									}
									if(str==_T(" 21")){
										dxffile.ReadString(str);
										centerline.Add(str);
										cstrarray.Add(str);
									}
								}
							}
						}
					}
					if(str==_T("DIMENSION")) {
						mark=1;
						CString strx,stry;
						while(str!=_T("  0")) {
							dxffile.ReadString(str);
							cstrarray.Add(str);
							//GETMAXHANDLE;
							if(str==_T(" 11")) {
								dxffile.ReadString(str);
								cstrarray.Add(str);
								strx=str;
							}
							if(str==_T(" 21")) {
								dxffile.ReadString(str);
								cstrarray.Add(str);
								stry=str;
							}
							if(str==_T("  1")) {
								dxffile.ReadString(str);
								if(!CheckFake(&str)) {
									fake++;
									wrodimension.Add(strx);
									wrodimension.Add(stry);
								}
								cstrarray.Add(str);
							}
						}
					}
					if(mark==1) {
						mark=0;
						//cstrarray.RemoveAll();
						for(int i=0; i<cstrarray.GetCount(); i++) {
							checkedfile.Write(cstrarray[i]+_T("\r\n"), cstrarray[i].GetLength()+1);
						}
						cstrarray.RemoveAll();
					}
					dxffile.ReadString(str);
					if(str!=_T("ENDSEC")) {
						checkedfile.Write(str+_T("\r\n"), str.GetLength()+1);
					}
					//if(str==_T("ENDSEC")){
					//	break;
					//}

				}
				TakeOutUnNeCircle(circle,centerline);
				CheckCoincide(circle,centerline,notcocircle)?notcoincide=0:notcoincide=1;
				int index=maxhandle.GetLength()+1;
				handleint=(int)pow(10.0, index);
				if(wrodimension.GetCount()>0) {
					CString str=_T(""), x,y,handle;
					//double x1,x2,y1,y2;
					for(int i=0; i<wrodimension.GetCount()/2; i++) {
						str.Format(_T("%d"), handleint); handle=str;
						str.Format(_T("%d"), _ttoi(wrodimension[(i+1)*2-2])); x=str;
						str.Format(_T("%d"), _ttoi(wrodimension[(i+1)*2-1]));y=str;
						CREATELINE(x, y, handle, handle330);
						handleint++;
						//CREATELINE((str.Format(_T("%d"), _ttoi(wrodimension[(i+1)*2-2])-5)),(str.Format(_T("%d"), _ttoi(wrodimension[(i+1)*2-1])+10)),(str.Format(_T("%d"), _ttoi(wrodimension[(i+1)*2-2])+5)),(str.Format(_T("%d"), _ttoi(wrodimension[(i+1)*2-1])-10)));
						//CREATELINE((str.Format(_T("%d"), _ttoi(wrodimension[(i+1)*2-2])-5)),(str.Format(_T("%d"), _ttoi(wrodimension[(i+1)*2-1])-10)),(str.Format(_T("%d"), _ttoi(wrodimension[(i+1)*2-2])+5)),(str.Format(_T("%d"), _ttoi(wrodimension[(i+1)*2-1])+10)));
					}
				}
				if(notcocircle.GetCount()>0) {
					CString str=_T(""), x,y,handle;
					//double x1,x2,y1,y2;
					for(int i=0; i<notcocircle.GetCount()/2; i++) {
						str.Format(_T("%d"), handleint); handle=str;
						str.Format(_T("%d"), _ttoi(notcocircle[(i+1)*2-2])); x=str;
						str.Format(_T("%d"), _ttoi(notcocircle[(i+1)*2-1]));y=str;
						CREATELINE(x, y, handle, handle330);
						handleint++;
						//CREATELINE((str.Format(_T("%d"), _ttoi(notcocircle[(i+1)*2-2])-5)),(str.Format(_T("%d"), _ttoi(notcocircle[(i+1)*2-1])+10)),(str.Format(_T("%d"), _ttoi(notcocircle[(i+1)*2-2])+5)),(str.Format(_T("%d"), _ttoi(notcocircle[(i+1)*2-1])-10)));
						//CREATELINE((str.Format(_T("%d"), _ttoi(notcocircle[(i+1)*2-2])-5)),(str.Format(_T("%d"), _ttoi(notcocircle[(i+1)*2-1])-10)),(str.Format(_T("%d"), _ttoi(notcocircle[(i+1)*2-2])+5)),(str.Format(_T("%d"), _ttoi(notcocircle[(i+1)*2-1])+10)));
					}
				}
				checkedfile.Write(str+_T("\r\n"), str.GetLength()+1);
			}
		}
		//TakeOutUnNeCircle(circle,centerline);
		//CheckCoincide(circle,centerline)?notcoincide=0:notcoincide=1;
		if(notcoincide==0&&fake==0) {
			NoDiPro=NoDiPro+dxffile.GetFileName()+_T("\t\n");
		}
		if(notcoincide==1) {
			notcoincide=0;
			NotCoincide=NotCoincide+dxffile.GetFileName()+_T("\t\n");
		}
		if(fake>0) {
			fake=0;
			DiPro=DiPro+dxffile.GetFileName()+_T("\t\n");
		}
		CWnd::UpdateData(FALSE);
		CWnd::UpdateWindow();
		cstrarray.RemoveAll();
		circle.RemoveAll();
		centerline.RemoveAll();
		wrodimension.RemoveAll();
		notcocircle.RemoveAll();
		dxffile.Close();
		checkedfile.Close();
	}
	return TRUE;
}

void CDimensionCheckDlg::MakeCheckedFolderPath(CList<CString, CString &> &FilePath, CList<CString, CString &> &CheckedFolderPath)
{
	CString cstr;
	int pos;
	//POSITION pos;
	/*cstr=FilePath.GetHead();
	cstr.MakeReverse();
	pos1=cstr.Find(_T("\\"));
	cstr.MakeReverse();
	cstr.Insert(cstr.GetLength()-pos1, _T("Checked\\"));
	CheckedFolderPath.AddTail(cstr);
	pos=FilePath.GetHeadPosition();
	cstr=FilePath.GetNext(pos);
	for(int i=0; i<FilePath.GetCount()-1; i++) {
		cstr=FilePath.GetNext(pos);
		cstr.MakeReverse();
		pos1=cstr.Find(_T("\\"));
		cstr.MakeReverse();
		cstr.Insert(pos1, _T("Checked\\"));
		CheckedFolderPath.AddTail(cstr);
	}*/
	for(int i=0; i<FilePath.GetCount(); i++) {
		cstr=FilePath.GetAt(FilePath.FindIndex(i));
		cstr.MakeReverse();
		pos=cstr.Find(_T("\\"));
		cstr.MakeReverse();
		cstr.Insert(cstr.GetLength()-pos, _T("Checked\\"));
		CheckedFolderPath.AddTail(cstr);
	}
}

BOOL CDimensionCheckDlg::CheckFake(CString *str)
{
	if(str->Find(_T("<>"))==-1) {
		str->Insert(0, _T("!!!"));
		return FALSE;
	}else {
		return TRUE;
	}
}

void CDimensionCheckDlg::TakeOutUnNeCircle(CStringArray &circle, CStringArray &centerline)
{
	CStringArray delatecircle;
	CString str=_T("");
	for(int i=0; i<(circle.GetCount()/3)&&((circle.GetCount()/3)>0); i++) {
		int count;
		count=0;
		for(int j=0; j<(centerline.GetCount()/4); j++) {
			if(CheckDistance(circle, centerline, i, j)&&CheckFootPointSlope(circle, centerline, i, j)) {
				count++;
			}
		}
		if(count==0) {
			str.Format(_T("%d"), i);
			delatecircle.Add(str);
			//circle.RemoveAt((i+1)*3-1);
			//circle.RemoveAt((i+1)*3-2);
			//circle.RemoveAt((i+1)*3-3);
		}
	}
	if(delatecircle.GetCount()>0) {
		for(int i=delatecircle.GetCount()-1; i>=0; i--) {
			circle.RemoveAt((_ttoi(delatecircle.GetAt(i))+1)*3-1);
			circle.RemoveAt((_ttoi(delatecircle.GetAt(i))+1)*3-2);
			circle.RemoveAt((_ttoi(delatecircle.GetAt(i))+1)*3-3);
		}
	}
}

BOOL CDimensionCheckDlg::CheckCoincide(const CStringArray &circle, const CStringArray &centerline, CStringArray &notcocircle)
{
	double slopeaf, slopebef, x0, x1, x2, y0, y1, y2;
	int level, upright, slopenum, mark=0;
	for(int i=0; i<(circle.GetCount()/3); i++) {
		x0=_ttof(circle[(i+1)*3-3]);
		y0=_ttof(circle[(i+1)*3-2]);
		level=upright=slopenum=0;
		slopeaf=slopebef=0;
		for(int j=0; j<(centerline.GetCount()/4); j++) {
			x1=_ttof(centerline[((j+1)*4)-4]);
			y1=_ttof(centerline[((j+1)*4)-3]);
			x2=_ttof(centerline[((j+1)*4)-2]);
			y2=_ttof(centerline[((j+1)*4)-1]);
			slopeaf=(y2-y0)/(x2-x0);
			if(CheckDistance(circle, centerline, i, j)&&CheckFootPointSlope(circle, centerline, i, j)) {
				if(x0==x1&&x0==x2) {
					upright=1;
					//break;
				}
				if(y0==y1&&y0==y2) {
					level=1;
					//break;
				}
				if(((floor(((y2-y0)/(x2-x0)*1000))/1000)==(floor((y0-y1)/(x0-x1)*1000)/1000))&&(slopeaf!=slopebef)) {
					slopenum++;
				}
				if((upright==1&&level==1)||slopenum>=2) break;
			}
		}
		//if((upright==0||level==0)&&(slopenum<2)) {
		//	return FALSE;
		//}
		if((upright==0||level==0)&&(slopenum<2)) {
			mark++;
			notcocircle.Add(circle[(i+1)*3-3]);
			notcocircle.Add(circle[(i+1)*3-2]);
		}
	}
	if(mark==0) {
		return TRUE;
	} else return FALSE;
}

BOOL CDimensionCheckDlg::CheckDistance( const CStringArray &circle, const CStringArray &centerline, int i, int j)
{
	double A, B, C, x0, y0,d;
	A=_ttof(centerline[((j+1)*4)-1])-_ttof(centerline[((j+1)*4)-3]);
	B=_ttof(centerline[((j+1)*4)-4])-_ttof(centerline[((j+1)*4)-2]);
	C=_ttof(centerline[((j+1)*4)-3])*_ttof(centerline[((j+1)*4)-2])-_ttof(centerline[((j+1)*4)-4])*_ttof(centerline[((j+1)*4)-1]);
	x0=_ttof(circle[(i+1)*3-3]);
	y0=_ttof(circle[(i+1)*3-2]);
	d=_ttoi(circle[(i+1)*3-1]);
	return (((floor(abs(A*x0+B*y0+C)*1000)/1000)/(floor(sqrt(A*A+B*B)*1000)/1000))<d)?TRUE:FALSE;
}

BOOL CDimensionCheckDlg::CheckFootPointSlope( const CStringArray &circle, const CStringArray &centerline, int i, int j)
{
	double A, B, C, x0, y0, x1, y1, x2, y2, xfootp, yfootp;
	x1=_ttof(centerline[((j+1)*4)-4]);
	y1=_ttof(centerline[((j+1)*4)-3]);
	x2=_ttof(centerline[((j+1)*4)-2]);
	y2=_ttof(centerline[((j+1)*4)-1]);
	A=y2-y1;
	B=x1-x2;
	C=y1*x2-x1*y2;
	x0=_ttof(circle[(i+1)*3-3]);
	y0=_ttof(circle[(i+1)*3-2]);
	xfootp=(B*B*x0-A*B*y0-A*C)/(A*A+B*B);
	yfootp=(-A*B*x0+A*A*y0-C*B)/(A*A+B*B);
	if((x1==x2&&x2==x0)&&((y2-y0)*(y0-y1)>0)) return TRUE;
	if((y1==y2&&y2==y0)&&((x2-x0)*(x0-x1)>0)) return TRUE;
	return ((((y2-yfootp)*(yfootp-y1)>0)&&((x2-xfootp)*(xfootp-x1)>0))&&((floor(((y2-yfootp)/(x2-xfootp))*1000)/1000)==(floor(((yfootp-y1)/(xfootp-x1))*1000))/1000))?TRUE:FALSE;
}


void CDimensionCheckDlg::OnBnClickedButton3()
{
	exit(0);
	// TODO: 在此添加控件通知处理程序代码
}


void CDimensionCheckDlg::OnBnClickedButton6()
{
	m_cNafolderpath.EnableWindow(TRUE);
	m_cdxffolderpath.EnableWindow(TRUE);
	NoDiPro=_T("");
	DiPro=_T("");
	NotCoincide=_T("");
	OnInitDialog();
	// TODO: 在此添加控件通知处理程序代码
}
