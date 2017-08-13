#include "stdafx.h"
#include "sinstar3_tsf.h"
#include "editsession.h"

#define TIMERID_CHKDEFIME 100


/* static */
HRESULT CBaiduJPTSF::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObj)
{
    CBaiduJPTSF *pCase;
    HRESULT hr;

    if (ppvObj == NULL)
        return E_INVALIDARG;

    *ppvObj = NULL;

    if (NULL != pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    if ((pCase = new CBaiduJPTSF) == NULL)
        return E_OUTOFMEMORY;

    hr = pCase->QueryInterface(riid, ppvObj);

    pCase->Release(); // caller still holds ref if hr == S_OK

    return hr;
}

PCTSTR pszAppList_Use_Cursor[] = 
{
	// IE Series
	_T("iexplore.exe")
};

PCTSTR pszAppList_Use_Ms_Method[] = 
{
	// Adobe Series
	_T("Photoshop.exe"),
	_T("Illustrator.exe"),
	_T("DreamWeaver.exe"),
	_T("Flash.exe"),
	_T("soffice.exe"),
	_T("soffice.bin"),

	// Kingsoft Series
	_T("wps.exe"),	// Kingsoft Writer
	_T("wpp.exe"),	// Kingsoft Presentation
	_T("et.exe")	// Kingsoft SpreadSheet
};


//+---------------------------------------------------------------------------
//
// ctor
//
//----------------------------------------------------------------------------

CBaiduJPTSF::CBaiduJPTSF()
{
	XLOG_FUNCTION;

    DllAddRef();

    //
    // Initialize the thread manager pointer.
    //
    _pThreadMgr = NULL;

    //
    // Initialize the numbers for ThreadMgrEventSink.
    //
    _dwThreadMgrEventSinkCookie = TF_INVALID_COOKIE;
	_dwThreadFocusSinkCookie = TF_INVALID_COOKIE;

    //
    // Initialize the numbers for TextEditSink.
    //
    _pTextEditSinkContext = NULL;
    _dwTextEditSinkCookie = TF_INVALID_COOKIE;
	//
	// for input mode cookie
	//
	_dwThreadInputModeSinkCookie = TF_INVALID_COOKIE;
	_dwThreadKeyboardSinkCookie = TF_INVALID_COOKIE;

    //
    // Initialize the composition object pointer.
    //
    _pComposition = NULL;

    _cRef = 1;

	_dwCookieTextLayoutSink = TF_INVALID_COOKIE;

	m_pBaiduJP3=NULL;

	_bHasFocus=FALSE;

	_bInKeyProc=FALSE;
	_bInEditDocument = FALSE;	
	
	_bUseCursorPos = FALSE;
	_bUseMSMethod = FALSE;

	TCHAR szFileName[MAX_PATH] = _T("");
	GetModuleFileName( NULL, szFileName, ARRAYSIZE( szFileName));

	PCTSTR pszPos = _tcsrchr( szFileName, _T('\\'));
	if ( pszPos != NULL)
	{
		for ( size_t i = 0; i < ARRAYSIZE( pszAppList_Use_Cursor); i++)
		{
			if ( _tcsicmp( pszPos + 1, pszAppList_Use_Cursor[i]) == 0)
			{
				_bUseCursorPos = TRUE;
				break;
			}
		}

		for ( size_t i = 0; i < ARRAYSIZE( pszAppList_Use_Ms_Method); i++)
		{
			if ( _tcsicmp( pszPos + 1, pszAppList_Use_Ms_Method[i]) == 0)
			{
				_bUseMSMethod = TRUE;
				break;
			}
		}
	}

	_bPosSaved = FALSE;
}

//+---------------------------------------------------------------------------
//
// dtor
//
//----------------------------------------------------------------------------

CBaiduJPTSF::~CBaiduJPTSF()
{
	XLOG_FUNCTION;

	Deactivate();
    DllRelease();
}

STDAPI CBaiduJPTSF::Activate(ITfThreadMgr *pThreadMgr, TfClientId tfClientId)
{
	Helper_Trace(L"Activate %x %x", pThreadMgr, tfClientId);

	SHORT sSt=GetKeyState(VK_KANA);
	if(GetKeyState(VK_KANA)&0x01)
	{//自动取消假名输入模式
		INPUT input[2];
		input[0].type=INPUT_KEYBOARD;
		input[0].ki.wVk=VK_KANA;
		input[0].ki.dwFlags=0;
		input[1].type=INPUT_KEYBOARD;
		input[1].ki.wVk=VK_KANA;
		input[1].ki.dwFlags=KEYEVENTF_KEYUP;
		BOOL bRet=SendInput(2,input,sizeof(INPUT));
		_ASSERT(bRet);
	}

	_pThreadMgr = pThreadMgr;
    _pThreadMgr->AddRef();
    _tfClientId = tfClientId;	

	_dwLastLayoutChangeTime = GetTickCount();

    //
    // Initialize ThreadMgrEventSink.
    //
    if (!_InitThreadMgrEventSink())
        goto ExitError;	

    // 
    //  If there is the focus document manager already,
    //  advise the TextEditSink.
    // 
    ITfDocumentMgr *pDocMgrFocus;
    if ((_pThreadMgr->GetFocus(&pDocMgrFocus) == S_OK) &&
        (pDocMgrFocus != NULL))
    {
        _bInEditDocument = _InitTextEditSink(pDocMgrFocus);
        pDocMgrFocus->Release();
    }

	//
    // Initialize KeyEventSink
    //
    if (!_InitKeyEventSink())
        goto ExitError;
	//
	// Initialize display guid atom
	//
	if (!_InitDisplayAttributeGuidAtom())
		goto ExitError;	

	if ( !_InitThreadCompartment())
		goto ExitError;

	CreateMsgListner(g_hInst);

	OnSetThreadFocus();

	if(!_InitBaiduJP3())
 		goto ExitError;

	
	return S_OK;

ExitError:
    Deactivate(); // cleanup any half-finished init
    return E_FAIL;
}

//+---------------------------------------------------------------------------
//
// Deactivate
//
//----------------------------------------------------------------------------

STDAPI CBaiduJPTSF::Deactivate()
{
	Helper_Trace(_T("Deactivate"));
	//确保输入过程结束
	if(_IsComposing())
	{
		BD_VERIFY(_pThreadMgr);
		ITfContext *pCtx=(ITfContext *)GetImeContext();
		if(pCtx) 
			EndComposition(pCtx);
		else if(m_pBaiduJP3)
			m_pBaiduJP3->OnCompositionTerminated();
		ReleaseImeContext(pCtx);
	}
	if (_pThreadMgr)
	{
		_InitTextEditSink(NULL);
		_UninitThreadCompartment();
		_UninitThreadMgrEventSink();
		_UninitKeyEventSink();
	}

    if (_pThreadMgr != NULL)
    {
		OnKillThreadFocus();
		DestroyMsgListner();
		_UninitBaiduJP3();
		_pThreadMgr->Release();
		_pThreadMgr = NULL;
	}

    _tfClientId = TF_CLIENTID_NULL;
	_bInEditDocument = FALSE;
	_bPosSaved = FALSE;

    return S_OK;
}

STDMETHODIMP CBaiduJPTSF::OnLayoutChange(ITfContext *pContext, TfLayoutCode lcode, ITfContextView *pContextView)
{
	Helper_Trace(_T("OnLayoutChange _pComposition=%08X"),_pComposition);
	switch (lcode)
	{
	case TF_LC_CHANGE:
		_bGetLayoutChangeMsg=TRUE;
		if (IsCompositing())
		{
			CEditSessionGetTextExtent *pEditSession;

			if ((pEditSession = new CEditSessionGetTextExtent(this, pContext, pContextView)) != NULL)
			{
				HRESULT hr;
				HRESULT hrSession;
				//由于这个接口可能是延时定时器触发的，因此不能使用TF_ES_SYNC标志来同步执行
				hr = pContext->RequestEditSession(_GetClientId(), pEditSession, TF_ES_ASYNCDONTCARE | TF_ES_READ, &hrSession);
				pEditSession->Release();
			}
		}

		// 处理完之后，设置一个时间标记
		_dwLastLayoutChangeTime = GetTickCount();

		break;

	case TF_LC_DESTROY:
		{
			Helper_Trace(_T("LayoutChange:Destroy"));
		}
		break;

	case TF_LC_CREATE:
		{
			Helper_Trace(_T("LayoutChange:Create"));
		}
		break;

	default:
		break;
	}

	return S_OK;
}

STDMETHODIMP CBaiduJPTSF::Show(	HWND hwndParent,LANGID langid,REFGUID rguidProfile)
{
	CBaiduIMEModule::GetInstance().BaiduJP3_OpenConfig(hwndParent);
	return S_OK;
}

STDMETHODIMP CBaiduJPTSF::GetDisplayName(BSTR* pbstrName)
{
	*pbstrName=SysAllocString(L"BAIDUTYPE");
	return S_OK;
}


BOOL CBaiduJPTSF::IsCompositing()
{
	return _IsComposing();
}


HRESULT CBaiduJPTSF::_AdviseTextLayoutSink(ITfContext *pContext)
{
	HRESULT hr;
	ITfSource *pSource = NULL;

	hr = E_FAIL;

	if (FAILED(pContext->QueryInterface(IID_ITfSource, (void **)&pSource)))
		goto Exit;

	if (FAILED(pSource->AdviseSink(IID_ITfTextLayoutSink, (ITfTextLayoutSink *)this, &_dwCookieTextLayoutSink)))
		goto Exit;

	hr = S_OK;

Exit:
	if (pSource != NULL)
		pSource->Release();
	return hr;
}

HRESULT CBaiduJPTSF::_UnadviseTextLayoutSink(ITfContext *pContext)
{
	HRESULT hr;
	ITfSource *pSource = NULL;

	hr = E_FAIL;
	if(_dwCookieTextLayoutSink==TF_INVALID_COOKIE) goto Exit;

	if (FAILED(pContext->QueryInterface(IID_ITfSource, (void **)&pSource)))
		goto Exit;

	if (FAILED(pSource->UnadviseSink(_dwCookieTextLayoutSink)))
		goto Exit;

	hr = S_OK;

Exit:
	if (pSource != NULL)
		pSource->Release();
	return hr;
}

void CBaiduJPTSF::StartComposition(LPVOID pImeContext)
{
	//TSF输入法中不需要实现该接口，而是在开始输入后的editsession中来开启一次输入过程
}


void CBaiduJPTSF::EndComposition(LPVOID pImeContext)
{
	_EndComposition((ITfContext*)pImeContext);
}


void CBaiduJPTSF::ReplaceSelCompositionW(LPVOID pImeContext,int nLeft,int nRight,WCHAR* wszComp,int nLen)
{
	_ChangeComposition((ITfContext*)pImeContext,nLeft,nRight,wszComp,nLen);
}

void CBaiduJPTSF::UpdateResultAndCompositionStringW(LPVOID lpImeContext,WCHAR *wszResultStr,int nResStrLen,WCHAR *wszCompStr,int nCompStrLen)
{
	_UpdateResultAndCompositionStringW((ITfContext*)lpImeContext,wszResultStr,nResStrLen,wszCompStr,nCompStrLen);
}

int  CBaiduJPTSF::MoveCaretPos(LPVOID lpImeContext,int nPos,BOOL bSet)
{
	return _MoveCaretPos((ITfContext*)lpImeContext,nPos,bSet);
}


LPVOID CBaiduJPTSF::GetImeContext()
{

	if(!_pThreadMgr) return NULL;
	HRESULT         hr;

	if(IsCompositing())
	{
		ITfRange *pRange;
		ITfContext *pContext;
		hr=_pComposition->GetRange(&pRange);
		if(SUCCEEDED(hr) && pRange)
		{
			hr=pRange->GetContext(&pContext);
			pRange->Release();
			if(SUCCEEDED(hr)&&pContext)	return pContext;
		}
	}else
	{
		ITfDocumentMgr  *pFocusDoc;
		hr = _pThreadMgr->GetFocus(&pFocusDoc);
		if(SUCCEEDED(hr) && pFocusDoc != NULL)
		{
			ITfContext *pContext;
			hr = pFocusDoc->GetTop(&pContext);
			pFocusDoc->Release();
			if(SUCCEEDED(hr))
			{
				return pContext;
			}
		}
	}
	return NULL;
}

BOOL   CBaiduJPTSF::ReleaseImeContext(LPVOID lpImeContext)
{
	if(!lpImeContext) return FALSE;
	ITfContext *pContext=(ITfContext*)lpImeContext;
	try
	{
		pContext->Release();
	}
	catch (...)
	{
		
	}
	return TRUE;
}

BOOL CBaiduJPTSF::GetLanguageBarItemMgr(ITfLangBarItemMgr **ppLangBarMgr,GUID *pclsidTIP)
{
	if(!_pThreadMgr) return NULL;
	*pclsidTIP=c_clsidBaidujpTSF;
	return SUCCEEDED(_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr,(void **)ppLangBarMgr));
}

BOOL CBaiduJPTSF::_InitDisplayAttributeGuidAtom()
{
	ITfCategoryMgr *pCategoryMgr;
	HRESULT hr;

	if (CoCreateInstance(CLSID_TF_CategoryMgr,
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_ITfCategoryMgr, 
		(void**)&pCategoryMgr) != S_OK)
	{
		return FALSE;
	}

	// register the display attribute for input text.
	hr = pCategoryMgr->RegisterGUID(c_guidDisplayAttributeInput, &_gaDisplayAttributeInput);
	// register the display attribute for the converted text.
	hr = pCategoryMgr->RegisterGUID(c_guidDisplayAttributeConverted, &_gaDisplayAttributeConverted);
	// register the display attribute for the target converted text.
	hr = pCategoryMgr->RegisterGUID(c_guidDisplayAttributeTargetConverted, &_gaDisplayAttributeTargetConverted);

	pCategoryMgr->Release();

	return (hr == S_OK);
}

BOOL CBaiduJPTSF::_InitBaiduJP3()
{
	m_pBaiduJP3=CBaiduIMEModule::GetInstance().BaiduJP3_Create(this,g_hInst);
	if(!m_pBaiduJP3) return FALSE;
 	m_pBaiduJP3->OnIMESelect(_bHasFocus);
 	m_pBaiduJP3->OnSetFocus(_bHasFocus && _bInEditDocument);
 	OnChange(GUID_COMPARTMENT_KEYBOARD_OPENCLOSE);
 	OnChange(GUID_COMPARTMENT_KEYBOARD_INPUTMODE_CONVERSION);
	return TRUE;
}

BOOL CBaiduJPTSF::_UninitBaiduJP3()
{
	if(m_pBaiduJP3)
	{
		m_pBaiduJP3->OnIMESelect(FALSE);
		CBaiduIMEModule::GetInstance().BaiduJP3_Delete(m_pBaiduJP3);
		m_pBaiduJP3=NULL;
	}
	return TRUE;
}

LRESULT CBaiduJPTSF::MsgListnerWndProc(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static UINT s_MsgUpdate=0;

	if(uMsg==WM_CREATE)
	{
// 		if(!s_MsgUpdate) s_MsgUpdate=::RegisterWindowMessage(MSG_UPDATE_BAIDUJP3);
// 		CImeUtil::Comm_ChangeWindowMessageFilter(m_hWnd,s_MsgUpdate,TRUE);
		SetTimer(m_hWnd,TIMERID_CHKDEFIME,2000,NULL);
	}else if(s_MsgUpdate==uMsg)
	{
		if( wParam == 0x7654321 && lParam == 0x1234567)
		{
			//
			// 这里做个测试，模拟一个异常，看看dump发送机制是否正常
			//
			PTSTR pszPos = NULL;
			pszPos[0] = 1;
		}

		if(wParam==0)
		{
			//Helper_Trace(_T("UNINSTALL %08X"),m_pBaiduJP3);
			//if(_EndCompositionEx() && m_pBaiduJP3)
			//{
			//	m_pBaiduJP3->OnCompositionTerminated();
			//}
			//if(m_pBaiduJP3) _UninitBaiduJP3();
			CIMEMan::SwitchToOtherIME();
		}else if(!m_pBaiduJP3)
		{
			Helper_Trace(_T("RELOAD"));
			_InitBaiduJP3();
		}
		return 0;
	}else if(uMsg==WM_TIMER)
	{
		if(wParam==TIMERID_CHKDEFIME)
		{
			// 有focus才做检查，否则在多个app中弹出这个对话框
			if ( _bHasFocus)
			{
				static BOOL bChkDefIME=FALSE;
				if(!bChkDefIME && !IsCompositing())
				{//正在输入过程中不检查
					bChkDefIME=TRUE;
					
					Helper_Trace( _T("bChkDefIME: %d, Thread id: %d"), bChkDefIME, GetCurrentThreadId());

					// 判断是否已经是默认输入法
					BOOL bDefIME=CIMEMan::IsDefaultIme( BAIDU_IME_FILE_NAME, c_clsidBaidujpTSF, c_guidProfile);
					if(!bDefIME && m_pBaiduJP3)	m_pBaiduJP3->CheckDefIME();
				}
				if(bChkDefIME)	KillTimer(m_hWnd,wParam);//防止多个线程的情况下Timer没有被中止
			}
		}
	}
	return __super::MsgListnerWndProc(uMsg,wParam,lParam);
}

void CBaiduJPTSF::UpdateCompAttr(ITfContext *pContext,TfEditCookie ec,ITfRange *pRangeComposition)
{
	//做一个简单的处理，当range为空时baidujp3中的数据可能和TSF中的数据不一致
	BOOL bEmpty=FALSE;
	if(pRangeComposition->IsEmpty(ec,&bEmpty)==S_OK && bEmpty) return;

	pRangeComposition->Collapse(ec,TF_ANCHOR_START);
	int nSegs=m_pBaiduJP3->GetCompositionSegments();
	int nBegin=0;
	for(int i=0;i<nSegs;i++)
	{
		LONG cch=0;
		int nEnd=m_pBaiduJP3->GetCompositionSegmentEnd(i);
		pRangeComposition->ShiftEnd(ec,nEnd-nBegin,&cch,NULL);
		_SetCompositionDisplayAttributes(ec, pContext, pRangeComposition,(TF_DA_ATTR_INFO)m_pBaiduJP3->GetCompositionSegmentAttr(i));
		nBegin=nEnd;
		pRangeComposition->Collapse(ec,TF_ANCHOR_END);
	}
}

//+---------------------------------------------------------------------------
//
// _ClearCompositionDisplayAttributes
//
//----------------------------------------------------------------------------

void CBaiduJPTSF::_ClearCompositionDisplayAttributes(TfEditCookie ec, ITfContext *pContext)
{
	ITfRange *pRangeComposition;
	ITfProperty *pDisplayAttributeProperty;

	if(!pContext) return;
	// get the compositon range.
	if (!_pComposition || _pComposition->GetRange(&pRangeComposition) != S_OK)
		return;

	// get our the display attribute property
	if (pContext->GetProperty(GUID_PROP_ATTRIBUTE, &pDisplayAttributeProperty) == S_OK)
	{
		// clear the value over the range
		pDisplayAttributeProperty->Clear(ec, pRangeComposition);

		pDisplayAttributeProperty->Release();
	}

	pRangeComposition->Release();
}

BOOL CBaiduJPTSF::RegisterIMEHotKey(REFGUID guidHotKey,LPCWSTR pszName,const PRESERVEDKEY *pKey)
{
	ITfKeystrokeMgr *pKeystrokeMgr;
	HRESULT hr;
	const TF_PRESERVEDKEY *pKeyTF=(const TF_PRESERVEDKEY*)pKey;

	if (_pThreadMgr->QueryInterface(IID_ITfKeystrokeMgr, (void **)&pKeystrokeMgr) != S_OK)
		return FALSE;

	hr = pKeystrokeMgr->PreserveKey(_tfClientId, 
		guidHotKey,
		pKeyTF,
		pszName,
		pszName?wcslen(pszName):0);
	pKeystrokeMgr->Release();

	return (hr == S_OK);
}

BOOL CBaiduJPTSF::UnregisterIMEHotKey(REFGUID guidHotKey,const PRESERVEDKEY *pKey)
{
	ITfKeystrokeMgr *pKeystrokeMgr;

	if (_pThreadMgr->QueryInterface(IID_ITfKeystrokeMgr, (void **)&pKeystrokeMgr) != S_OK)
		return FALSE;

	const TF_PRESERVEDKEY *pKeyTF=(const TF_PRESERVEDKEY*)pKey;
	pKeystrokeMgr->UnpreserveKey(guidHotKey, pKeyTF);
	pKeystrokeMgr->Release();
	return TRUE;
}