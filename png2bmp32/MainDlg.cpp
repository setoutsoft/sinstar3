// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
#include <controls.extend/FileHelper.h>

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	return 0;
}

void CMainDlg::OnConvert()
{
	SImageWnd *pImg = FindChildByName2<SImageWnd>(L"img_preview");
	SASSERT(pImg);
	IBitmap *pBmp = pImg->GetImage();
	if (pBmp)
	{
		BITMAPFILEHEADER bmf = { 0 };
		BITMAPINFOHEADER bmi = { 0 };
		bmf.bfType = 0x4D42;//'BM'
		bmf.bfOffBits = sizeof(bmf) + sizeof(bmi);
		bmf.bfSize = bmf.bfOffBits + 4*pBmp->Width()*pBmp->Height();

		bmi.biSize = sizeof(bmi);
		bmi.biBitCount = 32;
		bmi.biCompression = BI_RGB;
		bmi.biWidth = pBmp->Width();
		bmi.biHeight = pBmp->Height();
		bmi.biPlanes = 1;

		SStringT strFileName = FindChildByName(L"edit_path")->GetWindowText();
		strFileName = strFileName.Left(strFileName.GetLength() - 3) + _T("bmp");
		FILE *f = _tfopen(strFileName, _T("wb"));
		if (f)
		{
			fwrite(&bmf, 1, sizeof(bmf), f);
			fwrite(&bmi, 1, sizeof(bmi), f);
			fwrite(pBmp->GetPixelBits(), 4, pBmp->Width()*pBmp->Height(), f);
			fclose(f);
		}
		else
		{
			SMessageBox(m_hWnd, _T("open file to write failed"), _T("error"), MB_OK | MB_ICONSTOP);
		}
	}
	else
	{
		SMessageBox(m_hWnd, _T("no png"), _T("error"), MB_OK | MB_ICONSTOP);
	}
}

void CMainDlg::OnBrowse()
{
	CFileDialogEx openDlg(TRUE, _T("png"), 0, 6, _T("png files(*.png)\0*.png\0All files (*.*)\0*.*\0\0"));
	if (openDlg.DoModal() == IDOK)
	{
		FindChildByName(L"edit_path")->SetWindowText(openDlg.m_szFileName);
		SImageWnd *pImg = FindChildByName2<SImageWnd>(L"img_preview");
		SASSERT(pImg);
		IBitmap *pBmp = SResLoadFromFile::LoadImage(openDlg.m_szFileName);
		if (pBmp)
		{
			pImg->SetImage(pBmp);
			pBmp->Release();
		}
	}
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

