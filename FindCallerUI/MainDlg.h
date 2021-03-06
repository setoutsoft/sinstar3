// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TaskAdapter.h"

class CMainDlg : public SHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

protected:
	BOOL StartProcess(LPCTSTR pszFileName);
	void Refresh(BOOL isX64, LPCTSTR pszFileName);
	void ParseRefreshAck(BOOL bX64, const BYTE * pBuf, DWORD dwLen);
	LRESULT SendFCCmd(HWND hRecv,DWORD fcCmd, DWORD dwLen, LPVOID pData);
protected:
	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	BOOL OnCopyData(HWND wnd, PCOPYDATASTRUCT pCopyDataStruct);
	void OnDestroy();
protected:

	void OnRefresh();
	void OnKillTask();
	void OnActivateTask();

	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
		EVENT_ID_COMMAND(R.id.btn_refresh,OnRefresh)
		EVENT_ID_COMMAND(R.id.btn_kill,OnKillTask)
		EVENT_ID_COMMAND(R.id.btn_activate,OnActivateTask)
	EVENT_MAP_END()
		
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		MSG_WM_COPYDATA(OnCopyData)
		MSG_WM_DESTROY(OnDestroy)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
private:
	BOOL			m_bLayoutInited;	

	HWND			m_hWndCallerX86;
	HWND			m_hWndCallerX64;

	CTaskAdapter	*m_taskAdapter;
};
