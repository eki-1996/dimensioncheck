
// DimensionCheck.h : PROJECT_NAME ���ץꥱ�`�����Υᥤ�� �إå��` �ե�����Ǥ���
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ˌ����Ƥ��Υե�����򥤥󥯥�`�ɤ���ǰ�� 'stdafx.h' �򥤥󥯥�`�ɤ��Ƥ�������"
#endif

#include "resource.h"		// �ᥤ�� ����ܥ�


// CDimensionCheckApp:
// ���Υ��饹�Όgװ�ˤĤ��Ƥϡ�DimensionCheck.cpp ����դ��Ƥ���������
//

class CDimensionCheckApp : public CWinApp
{
public:
	CDimensionCheckApp();

// ���`�Щ`�饤��
public:
	virtual BOOL InitInstance();

// �gװ

	DECLARE_MESSAGE_MAP()
};

extern CDimensionCheckApp theApp;