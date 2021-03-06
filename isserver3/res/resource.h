//stamp:0af9587a1a00eb45
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				dlg_about = _T("LAYOUT:dlg_about");
				dlg_keymap = _T("LAYOUT:dlg_keymap");
			}
			const TCHAR * dlg_about;
			const TCHAR * dlg_keymap;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				color = _T("values:color");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
		}values;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
				ICON_LOGO1 = _T("ICON:ICON_LOGO1");
				ICON_LOGO2 = _T("ICON:ICON_LOGO2");
				ICON_LOGO3 = _T("ICON:ICON_LOGO3");
				ICON_LOGO4 = _T("ICON:ICON_LOGO4");
			}
			const TCHAR * ICON_LOGO;
			const TCHAR * ICON_LOGO1;
			const TCHAR * ICON_LOGO2;
			const TCHAR * ICON_LOGO3;
			const TCHAR * ICON_LOGO4;
		}ICON;
		class _smenu{
			public:
			_smenu(){
				menu_context = _T("smenu:menu_context");
			}
			const TCHAR * menu_context;
		}smenu;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"_name_start",65535},
		{L"btn_close",65536},
		{L"img_keymap",65539},
		{L"link_comp_website",65538},
		{L"menu_about",100},
		{L"menu_auto",101},
		{L"menu_exit",102},
		{L"txt_comp_name",65537}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			_name_start = namedXmlID[0].strName;
			btn_close = namedXmlID[1].strName;
			img_keymap = namedXmlID[2].strName;
			link_comp_website = namedXmlID[3].strName;
			menu_about = namedXmlID[4].strName;
			menu_auto = namedXmlID[5].strName;
			menu_exit = namedXmlID[6].strName;
			txt_comp_name = namedXmlID[7].strName;
		}
		 const wchar_t * _name_start;
		 const wchar_t * btn_close;
		 const wchar_t * img_keymap;
		 const wchar_t * link_comp_website;
		 const wchar_t * menu_about;
		 const wchar_t * menu_auto;
		 const wchar_t * menu_exit;
		 const wchar_t * txt_comp_name;
		}name;

		class _id{
		public:
		const static int _name_start	=	65535;
		const static int btn_close	=	65536;
		const static int img_keymap	=	65539;
		const static int link_comp_website	=	65538;
		const static int menu_about	=	100;
		const static int menu_auto	=	101;
		const static int menu_exit	=	102;
		const static int txt_comp_name	=	65537;
		}id;

		class _string{
		public:
		const static int keymap	=	0;
		const static int title	=	1;
		const static int ver	=	2;
		}string;

		class _color{
		public:
		const static int blue	=	0;
		const static int gray	=	1;
		const static int green	=	2;
		const static int red	=	3;
		const static int white	=	4;
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
