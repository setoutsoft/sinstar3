#pragma once

#include "ImeWnd.h"
namespace SOUI
{
	class CStatusWnd :
		public CImeWnd
	{
	public:
		CStatusWnd(void);
		~CStatusWnd(void);

	protected:
		int OnCreate(LPCREATESTRUCT lpCreateStruct);

		BEGIN_MSG_MAP_EX(CStatusWnd)
			MSG_WM_CREATE(OnCreate)
		END_MSG_MAP()
	};

}