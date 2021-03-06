// MainDlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

class CAboutDlg : public SHostDialog
{
public:
	CAboutDlg();
	~CAboutDlg();

	void OnClose();
protected:
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
	EVENT_MAP_END()
		
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CAboutDlg)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
};
