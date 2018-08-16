#pragma once
#include <helper/SAdapterBase.h>
#include "../FindCaller/FindCaller.h"

namespace SOUI
{
	struct TASKINFOEX : TASKINFO
	{
		BOOL bX64;
	};

	class CTaskAdapter : public SMcAdapterBase
	{
	public:
		CTaskAdapter();
		~CTaskAdapter();

		void AddTask(TASKINFO ti, BOOL bX64);
		TASKINFOEX* GetTask(int iTask);
		BOOL DelTask(int iTask);
		void ClearTask();
	protected:
		virtual int getCount();

		virtual void getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate);

		//ɾ��һ�У��ṩ�ⲿ���á�
		void DeleteItem(int iPosition);

		SStringW GetColumnName(int iCol) const;

		bool OnSort(int iCol, SHDSORTFLAG * stFlags, int nCols);

		static int __cdecl SortCmp(void *context, const void * p1, const void * p2);
	protected:
		SArray<TASKINFOEX> m_arrTasks;
	};
}
