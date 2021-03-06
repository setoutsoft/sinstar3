// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "IsSvrProxy.h"
#include "../include/reg.h"
#include "../iscomm/iscomm.h"

//从PE文件加载，注意从文件加载路径位置
#define RES_TYPE 0
//#define SYSRES_TYPE 0
// #define RES_TYPE 0   //PE
// #define RES_TYPE 1   //ZIP
// #define RES_TYPE 2   //7z
// #define RES_TYPE 2   //文件
//去掉多项支持，以免代码显得混乱
#if (RES_TYPE==1)
#include "resprovider-zip\zipresprovider-param.h"
#else 
#if (RES_TYPE==2)
#include "resprovider-7zip\zip7resprovider-param.h"
#endif
#endif
#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif


//定义唯一的一个R,UIRES对象,ROBJ_IN_CPP是resource.h中定义的宏。
ROBJ_IN_CPP

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int /*nCmdShow*/)
{

	int nRet = 0;

	HANDLE hMapData = OpenFileMapping(FILE_MAP_READ, FALSE, NAME_ACK_MAPFILE);
	if (hMapData)
	{
		HWND hPrev = 0;
		LPVOID pData = MapViewOfFile(hMapData, FILE_MAP_READ, 0, 0, 0);
		memcpy(&hPrev, pData, sizeof(HWND));
		UnmapViewOfFile(pData);
		CloseHandle(hMapData);
		if (IsWindow(hPrev))
		{
			return 4;
		}
	}

	TCHAR szDataPath[MAX_PATH];
	CRegKey reg;
	LONG ret = reg.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\SetoutSoft\\sinstar3"), KEY_READ | KEY_WOW64_64KEY);
	if (ret != ERROR_SUCCESS)
	{
		return 1;
	}
	ULONG len = MAX_PATH;
	reg.QueryStringValue(_T("path_svr_data"), szDataPath, &len);
	reg.Close();
	if (GetFileAttributes(szDataPath) == INVALID_FILE_ATTRIBUTES)
	{
		return 2;
	}

	HRESULT hRes = OleInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));

	SComMgr *pComMgr = new SComMgr;
	TCHAR szCurrentDir[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szCurrentDir, sizeof(szCurrentDir));

	LPTSTR lpInsertPos = _tcsrchr(szCurrentDir, _T('\\'));
#ifdef _DEBUG
	_tcscpy(lpInsertPos + 1, _T("..\\isserver3"));
#else
	_tcscpy(lpInsertPos + 1, _T("\0"));
#endif
	SetCurrentDirectory(szCurrentDir);
	{
		BOOL bLoaded = FALSE;
		CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
		CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
		bLoaded = pComMgr->CreateRender_GDI((IObjRef**)&pRenderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [render] failed!"));
		bLoaded = pComMgr->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("imgdecoder"));

		pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
		SApplication *theApp = new SApplication(pRenderFactory, hInstance);
#ifdef _DEBUG
		//选择了仅在Release版本打包资源则系统资源在DEBUG下始终使用DLL加载
		{
			HMODULE hModSysResource = LoadLibrary(SYS_NAMED_RESOURCE);
			if (hModSysResource)
			{
				CAutoRefPtr<IResProvider> sysResProvider;
				CreateResProvider(RES_PE, (IObjRef**)&sysResProvider);
				sysResProvider->Init((WPARAM)hModSysResource, 0);
				theApp->LoadSystemNamedResource(sysResProvider);
				FreeLibrary(hModSysResource);
			}
			else
			{
				SASSERT(0);
			}
		}
#else		
		//从DLL加载系统资源
		{
			HMODULE hModSysResource = LoadLibrary(SYS_NAMED_RESOURCE);
			if (hModSysResource)
			{
				CAutoRefPtr<IResProvider> sysResProvider;
				CreateResProvider(RES_PE, (IObjRef**)&sysResProvider);
				sysResProvider->Init((WPARAM)hModSysResource, 0);
				theApp->LoadSystemNamedResource(sysResProvider);
				FreeLibrary(hModSysResource);
			}
			else
			{
				SASSERT(0);
			}
		}
#endif

		CAutoRefPtr<IResProvider>   pResProvider;

#ifdef _DEBUG		
		//选择了仅在Release版本打包资源则在DEBUG下始终使用文件加载
		{
			CreateResProvider(RES_FILE, (IObjRef**)&pResProvider);
			bLoaded = pResProvider->Init((LPARAM)_T("uires"), 0);
			SASSERT(bLoaded);
		}
#else
		{
			CreateResProvider(RES_PE, (IObjRef**)&pResProvider);
			bLoaded = pResProvider->Init((WPARAM)hInstance, 0);
			SASSERT(bLoaded);
		}
#endif
		theApp->InitXmlNamedID(namedXmlID, ARRAYSIZE(namedXmlID), TRUE);
		theApp->AddResProvider(pResProvider);

		// BLOCK: Run application
		{
			CIsSvrProxy svrProxy(szDataPath);
			svrProxy.Create(_T("sinstar3_server_proxy"), WS_POPUP, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL);
			if (!svrProxy.IsWindow())
			{
				nRet = 3;
			}
			else
			{
				nRet = theApp->Run(svrProxy.m_hWnd);
			}
		}

		delete theApp;
	}

	delete pComMgr;

	OleUninitialize();
	return nRet;
}
