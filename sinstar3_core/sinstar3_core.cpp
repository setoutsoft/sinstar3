// sinstar3_core.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Sinstar3Impl.h"
#include "../include/autolock.h"
#include "../include/version.h"
#include "../helper/helper.h"
#include "SouiEnv.h"
#include "Minidump.h"
#include "dataCenter/DataCenter.h"

//使用共享内存方式使设置信息在所有输入法进程中共享
#pragma data_seg(".sinstar3")
int				g_nRefCount = 0;	//ref count
#pragma data_seg()


EXTERN_C SINSTAR3_API  ISinstar* Sinstar3_Create(ITextService* pTxtSvr)
{
	CSinstar3Impl*  pRet= new CUnknownImpl<CSinstar3Impl>(pTxtSvr);
	return pRet;
}

EXTERN_C SINSTAR3_API  void Sinstar3_Delete(ISinstar* pSinstar3)
{
	pSinstar3->Release();
}

EXTERN_C SINSTAR3_API HRESULT Sinstar3_CanUnloadNow()
{
	return theModule->GetRefCount()==0;
}

EXTERN_C SINSTAR3_API BOOL Sinstar3_Config(HWND hWnd)
{
	return FALSE;
}


EXTERN_C SINSTAR3_API void Sinstar3_SetHostInfo(HostInfo *pHostInfo)
{
	theModule->SetLogStateListener(pHostInfo->pLogStateListener);
}

CSinstar3Core::CSinstar3Core(HINSTANCE hInst):CModuleRef(hInst),m_pLogStateListener(NULL), m_hMutex(0), m_hSettingFileMap(NULL)
{
	m_hMutex = CreateMutex(NULL, FALSE, SINSTAR3_MUTEX);
	TCHAR szPath[MAX_PATH];
	CRegKey reg;
	LONG ret = reg.Open(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\SetoutSoft\\sinstar3"),KEY_READ|KEY_WOW64_64KEY);
	if(ret == ERROR_SUCCESS)
	{
		ULONG len = MAX_PATH;
		reg.QueryStringValue(_T("path_client"),szPath,&len);
		reg.Close();
	}
	m_strDataPath = szPath;


	m_hSettingFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(CSettingsGlobal), KFileMapName_GlobalSetting);
	if (!m_hSettingFileMap)
	{
		SLOG_ERROR("open file map object for global settings storage failed");
	}
	else
	{
		bool bCreate = GetLastError() != ERROR_ALREADY_EXISTS;
		g_SettingsG = (CSettingsGlobal*)MapViewOfFile(m_hSettingFileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
		if (bCreate)
		{//first create object
			Helper_SetObjectToLowIntegrity(m_hSettingFileMap, SE_KERNEL_OBJECT);//降低内核对象访问权限
			m_strConfigIni = m_strDataPath + _T("\\data\\") + KSettingINI;
			g_SettingsG->Load(m_strConfigIni);
		}
		new CDataCenter(m_strDataPath);
	}
}

CSinstar3Core::~CSinstar3Core()
{
	delete CDataCenter::getSingletonPtr();
	g_nRefCount --;
	CloseHandle(m_hMutex);
}

SOUI::SStringT CSinstar3Core::GetSettingPath() const
{
	return m_strDataPath + _T("\\program\\settings.exe");
}

void CSinstar3Core::OnInit()
{
	CMinidump::Enable();
	new CSouiEnv(GetModule(),GetDataPath());
	if(m_pLogStateListener)
	{
		m_pLogStateListener->OnLogMgrReady(CSouiEnv::getSingleton().theApp()->GetLogManager());
	}
}

void CSinstar3Core::OnFinalRelease()
{
	if(m_pLogStateListener)
	{
		m_pLogStateListener->OnLogMgrFree();
	}
	delete CSouiEnv::getSingletonPtr();
}

void CSinstar3Core::SetLogStateListener(ILogStateListener *pListener)
{
	m_pLogStateListener = pListener;
	if(CSouiEnv::getSingletonPtr())
	{
		m_pLogStateListener->OnLogMgrReady(CSouiEnv::getSingleton().theApp()->GetLogManager());
	}
}
