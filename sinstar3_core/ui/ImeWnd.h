#pragma once

namespace SOUI
{

class CImeWnd : public SHostWnd
{
public:
	CImeWnd(LPCTSTR pszLayout);

	HWND Create();
	void Show(BOOL bShow);
protected:

	BOOL OnSetCursor(HWND wnd, UINT nHitTest, UINT message);
	void OnMouseMove(UINT nFlags, CPoint point);

	LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

	BEGIN_MSG_MAP_EX(CImeWnd)
		MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseEvent)
		MSG_WM_SETCURSOR(OnSetCursor)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_ACTIVATE(OnActivate)
		CHAIN_MSG_MAP(SHostWnd)
	END_MSG_MAP()
};

}