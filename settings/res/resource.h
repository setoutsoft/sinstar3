//stamp:0750de39e25eec99
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
				dlg_config = _T("LAYOUT:dlg_config");
			}
			const TCHAR * dlg_config;
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
		class _img{
			public:
			_img(){
				SYS_SCROLLBAR = _T("img:SYS_SCROLLBAR");
			}
			const TCHAR * SYS_SCROLLBAR;
		}img;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
			}
			const TCHAR * ICON_LOGO;
		}ICON;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"_name_start",65535},
		{L"ass_mode_english_prompt",402},
		{L"ass_mode_none",400},
		{L"ass_mode_phrase",401},
		{L"ass_mode_phrase_prompt",403},
		{L"btn_close",2},
		{L"btn_down",65559},
		{L"btn_tts_ch_preview",65571},
		{L"btn_tts_en_preview",65573},
		{L"btn_up",65558},
		{L"cand_auto_input",65538},
		{L"cand_py_phrase_first",65539},
		{L"cbx_tts_ch_token",65570},
		{L"cbx_tts_en_token",65572},
		{L"chk_auto_comp_promp",65553},
		{L"chk_auto_dot",65551},
		{L"chk_auto_select_cand",65552},
		{L"chk_disable_number_to_select_cand",65566},
		{L"chk_enable_23cand_hotkey",65563},
		{L"chk_full_skip_simple",65569},
		{L"chk_jp_zcs",65580},
		{L"chk_py_blur",65579},
		{L"chk_sent_input",65554},
		{L"chk_show_op_tip",65540},
		{L"edit_phrase_ast_deepness_max",65560},
		{L"edit_predict_phrase_maxlength",65556},
		{L"edit_sent_record_max",65562},
		{L"edit_webmode_header",65555},
		{L"enter_for_clear",110},
		{L"enter_for_input",111},
		{L"forcast_always",601},
		{L"forcast_disable",600},
		{L"forcast_no_cand",602},
		{L"gbk_show_as_gb",702},
		{L"gbk_show_manual",701},
		{L"gbk_show_only",700},
		{L"hk_2_cand",65564},
		{L"hk_3_cand",65565},
		{L"hk_bihua_heng",900},
		{L"hk_bihua_na",903},
		{L"hk_bihua_pie",902},
		{L"hk_bihua_shu",901},
		{L"hk_bihua_wild",905},
		{L"hk_bihua_zhe",904},
		{L"hk_filter_gbk",65548},
		{L"hk_input_en",65547},
		{L"hk_make_phrase",65543},
		{L"hk_record",65550},
		{L"hk_show_comp",65545},
		{L"hk_show_statusbar",65546},
		{L"hk_show_table",65544},
		{L"hk_switch_py",65541},
		{L"hk_to_sentmode",65537},
		{L"hk_to_umode",65542},
		{L"hk_tts",65549},
		{L"hk_turn_next",65568},
		{L"hk_turn_prev",65567},
		{L"ime_switch_disabled",102},
		{L"ime_switch_left_shift",100},
		{L"ime_switch_right_shift",101},
		{L"key_to_sentmode",65536},
		{L"lv_blur",65576},
		{L"py_switch_disabled",122},
		{L"py_switch_left_ctrl",120},
		{L"py_switch_right_ctrl",121},
		{L"rate_adjust_auto",501},
		{L"rate_adjust_disable",500},
		{L"rate_adjust_fast",502},
		{L"slider_tts_speed",65574},
		{L"sound_beep",802},
		{L"sound_disable",800},
		{L"sound_wave",801},
		{L"spin_phrase_ast_deepness_max",65561},
		{L"spin_predict_phrase_maxlength",65557},
		{L"txt_blur_group",65577},
		{L"txt_blur_info",65578},
		{L"txt_build_time",65583},
		{L"txt_svr_ver",65582},
		{L"txt_tts_speed",65575},
		{L"txt_ver",65581}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			_name_start = namedXmlID[0].strName;
			ass_mode_english_prompt = namedXmlID[1].strName;
			ass_mode_none = namedXmlID[2].strName;
			ass_mode_phrase = namedXmlID[3].strName;
			ass_mode_phrase_prompt = namedXmlID[4].strName;
			btn_close = namedXmlID[5].strName;
			btn_down = namedXmlID[6].strName;
			btn_tts_ch_preview = namedXmlID[7].strName;
			btn_tts_en_preview = namedXmlID[8].strName;
			btn_up = namedXmlID[9].strName;
			cand_auto_input = namedXmlID[10].strName;
			cand_py_phrase_first = namedXmlID[11].strName;
			cbx_tts_ch_token = namedXmlID[12].strName;
			cbx_tts_en_token = namedXmlID[13].strName;
			chk_auto_comp_promp = namedXmlID[14].strName;
			chk_auto_dot = namedXmlID[15].strName;
			chk_auto_select_cand = namedXmlID[16].strName;
			chk_disable_number_to_select_cand = namedXmlID[17].strName;
			chk_enable_23cand_hotkey = namedXmlID[18].strName;
			chk_full_skip_simple = namedXmlID[19].strName;
			chk_jp_zcs = namedXmlID[20].strName;
			chk_py_blur = namedXmlID[21].strName;
			chk_sent_input = namedXmlID[22].strName;
			chk_show_op_tip = namedXmlID[23].strName;
			edit_phrase_ast_deepness_max = namedXmlID[24].strName;
			edit_predict_phrase_maxlength = namedXmlID[25].strName;
			edit_sent_record_max = namedXmlID[26].strName;
			edit_webmode_header = namedXmlID[27].strName;
			enter_for_clear = namedXmlID[28].strName;
			enter_for_input = namedXmlID[29].strName;
			forcast_always = namedXmlID[30].strName;
			forcast_disable = namedXmlID[31].strName;
			forcast_no_cand = namedXmlID[32].strName;
			gbk_show_as_gb = namedXmlID[33].strName;
			gbk_show_manual = namedXmlID[34].strName;
			gbk_show_only = namedXmlID[35].strName;
			hk_2_cand = namedXmlID[36].strName;
			hk_3_cand = namedXmlID[37].strName;
			hk_bihua_heng = namedXmlID[38].strName;
			hk_bihua_na = namedXmlID[39].strName;
			hk_bihua_pie = namedXmlID[40].strName;
			hk_bihua_shu = namedXmlID[41].strName;
			hk_bihua_wild = namedXmlID[42].strName;
			hk_bihua_zhe = namedXmlID[43].strName;
			hk_filter_gbk = namedXmlID[44].strName;
			hk_input_en = namedXmlID[45].strName;
			hk_make_phrase = namedXmlID[46].strName;
			hk_record = namedXmlID[47].strName;
			hk_show_comp = namedXmlID[48].strName;
			hk_show_statusbar = namedXmlID[49].strName;
			hk_show_table = namedXmlID[50].strName;
			hk_switch_py = namedXmlID[51].strName;
			hk_to_sentmode = namedXmlID[52].strName;
			hk_to_umode = namedXmlID[53].strName;
			hk_tts = namedXmlID[54].strName;
			hk_turn_next = namedXmlID[55].strName;
			hk_turn_prev = namedXmlID[56].strName;
			ime_switch_disabled = namedXmlID[57].strName;
			ime_switch_left_shift = namedXmlID[58].strName;
			ime_switch_right_shift = namedXmlID[59].strName;
			key_to_sentmode = namedXmlID[60].strName;
			lv_blur = namedXmlID[61].strName;
			py_switch_disabled = namedXmlID[62].strName;
			py_switch_left_ctrl = namedXmlID[63].strName;
			py_switch_right_ctrl = namedXmlID[64].strName;
			rate_adjust_auto = namedXmlID[65].strName;
			rate_adjust_disable = namedXmlID[66].strName;
			rate_adjust_fast = namedXmlID[67].strName;
			slider_tts_speed = namedXmlID[68].strName;
			sound_beep = namedXmlID[69].strName;
			sound_disable = namedXmlID[70].strName;
			sound_wave = namedXmlID[71].strName;
			spin_phrase_ast_deepness_max = namedXmlID[72].strName;
			spin_predict_phrase_maxlength = namedXmlID[73].strName;
			txt_blur_group = namedXmlID[74].strName;
			txt_blur_info = namedXmlID[75].strName;
			txt_build_time = namedXmlID[76].strName;
			txt_svr_ver = namedXmlID[77].strName;
			txt_tts_speed = namedXmlID[78].strName;
			txt_ver = namedXmlID[79].strName;
		}
		 const wchar_t * _name_start;
		 const wchar_t * ass_mode_english_prompt;
		 const wchar_t * ass_mode_none;
		 const wchar_t * ass_mode_phrase;
		 const wchar_t * ass_mode_phrase_prompt;
		 const wchar_t * btn_close;
		 const wchar_t * btn_down;
		 const wchar_t * btn_tts_ch_preview;
		 const wchar_t * btn_tts_en_preview;
		 const wchar_t * btn_up;
		 const wchar_t * cand_auto_input;
		 const wchar_t * cand_py_phrase_first;
		 const wchar_t * cbx_tts_ch_token;
		 const wchar_t * cbx_tts_en_token;
		 const wchar_t * chk_auto_comp_promp;
		 const wchar_t * chk_auto_dot;
		 const wchar_t * chk_auto_select_cand;
		 const wchar_t * chk_disable_number_to_select_cand;
		 const wchar_t * chk_enable_23cand_hotkey;
		 const wchar_t * chk_full_skip_simple;
		 const wchar_t * chk_jp_zcs;
		 const wchar_t * chk_py_blur;
		 const wchar_t * chk_sent_input;
		 const wchar_t * chk_show_op_tip;
		 const wchar_t * edit_phrase_ast_deepness_max;
		 const wchar_t * edit_predict_phrase_maxlength;
		 const wchar_t * edit_sent_record_max;
		 const wchar_t * edit_webmode_header;
		 const wchar_t * enter_for_clear;
		 const wchar_t * enter_for_input;
		 const wchar_t * forcast_always;
		 const wchar_t * forcast_disable;
		 const wchar_t * forcast_no_cand;
		 const wchar_t * gbk_show_as_gb;
		 const wchar_t * gbk_show_manual;
		 const wchar_t * gbk_show_only;
		 const wchar_t * hk_2_cand;
		 const wchar_t * hk_3_cand;
		 const wchar_t * hk_bihua_heng;
		 const wchar_t * hk_bihua_na;
		 const wchar_t * hk_bihua_pie;
		 const wchar_t * hk_bihua_shu;
		 const wchar_t * hk_bihua_wild;
		 const wchar_t * hk_bihua_zhe;
		 const wchar_t * hk_filter_gbk;
		 const wchar_t * hk_input_en;
		 const wchar_t * hk_make_phrase;
		 const wchar_t * hk_record;
		 const wchar_t * hk_show_comp;
		 const wchar_t * hk_show_statusbar;
		 const wchar_t * hk_show_table;
		 const wchar_t * hk_switch_py;
		 const wchar_t * hk_to_sentmode;
		 const wchar_t * hk_to_umode;
		 const wchar_t * hk_tts;
		 const wchar_t * hk_turn_next;
		 const wchar_t * hk_turn_prev;
		 const wchar_t * ime_switch_disabled;
		 const wchar_t * ime_switch_left_shift;
		 const wchar_t * ime_switch_right_shift;
		 const wchar_t * key_to_sentmode;
		 const wchar_t * lv_blur;
		 const wchar_t * py_switch_disabled;
		 const wchar_t * py_switch_left_ctrl;
		 const wchar_t * py_switch_right_ctrl;
		 const wchar_t * rate_adjust_auto;
		 const wchar_t * rate_adjust_disable;
		 const wchar_t * rate_adjust_fast;
		 const wchar_t * slider_tts_speed;
		 const wchar_t * sound_beep;
		 const wchar_t * sound_disable;
		 const wchar_t * sound_wave;
		 const wchar_t * spin_phrase_ast_deepness_max;
		 const wchar_t * spin_predict_phrase_maxlength;
		 const wchar_t * txt_blur_group;
		 const wchar_t * txt_blur_info;
		 const wchar_t * txt_build_time;
		 const wchar_t * txt_svr_ver;
		 const wchar_t * txt_tts_speed;
		 const wchar_t * txt_ver;
		}name;

		class _id{
		public:
		const static int _name_start	=	65535;
		const static int ass_mode_english_prompt	=	402;
		const static int ass_mode_none	=	400;
		const static int ass_mode_phrase	=	401;
		const static int ass_mode_phrase_prompt	=	403;
		const static int btn_close	=	2;
		const static int btn_down	=	65559;
		const static int btn_tts_ch_preview	=	65571;
		const static int btn_tts_en_preview	=	65573;
		const static int btn_up	=	65558;
		const static int cand_auto_input	=	65538;
		const static int cand_py_phrase_first	=	65539;
		const static int cbx_tts_ch_token	=	65570;
		const static int cbx_tts_en_token	=	65572;
		const static int chk_auto_comp_promp	=	65553;
		const static int chk_auto_dot	=	65551;
		const static int chk_auto_select_cand	=	65552;
		const static int chk_disable_number_to_select_cand	=	65566;
		const static int chk_enable_23cand_hotkey	=	65563;
		const static int chk_full_skip_simple	=	65569;
		const static int chk_jp_zcs	=	65580;
		const static int chk_py_blur	=	65579;
		const static int chk_sent_input	=	65554;
		const static int chk_show_op_tip	=	65540;
		const static int edit_phrase_ast_deepness_max	=	65560;
		const static int edit_predict_phrase_maxlength	=	65556;
		const static int edit_sent_record_max	=	65562;
		const static int edit_webmode_header	=	65555;
		const static int enter_for_clear	=	110;
		const static int enter_for_input	=	111;
		const static int forcast_always	=	601;
		const static int forcast_disable	=	600;
		const static int forcast_no_cand	=	602;
		const static int gbk_show_as_gb	=	702;
		const static int gbk_show_manual	=	701;
		const static int gbk_show_only	=	700;
		const static int hk_2_cand	=	65564;
		const static int hk_3_cand	=	65565;
		const static int hk_bihua_heng	=	900;
		const static int hk_bihua_na	=	903;
		const static int hk_bihua_pie	=	902;
		const static int hk_bihua_shu	=	901;
		const static int hk_bihua_wild	=	905;
		const static int hk_bihua_zhe	=	904;
		const static int hk_filter_gbk	=	65548;
		const static int hk_input_en	=	65547;
		const static int hk_make_phrase	=	65543;
		const static int hk_record	=	65550;
		const static int hk_show_comp	=	65545;
		const static int hk_show_statusbar	=	65546;
		const static int hk_show_table	=	65544;
		const static int hk_switch_py	=	65541;
		const static int hk_to_sentmode	=	65537;
		const static int hk_to_umode	=	65542;
		const static int hk_tts	=	65549;
		const static int hk_turn_next	=	65568;
		const static int hk_turn_prev	=	65567;
		const static int ime_switch_disabled	=	102;
		const static int ime_switch_left_shift	=	100;
		const static int ime_switch_right_shift	=	101;
		const static int key_to_sentmode	=	65536;
		const static int lv_blur	=	65576;
		const static int py_switch_disabled	=	122;
		const static int py_switch_left_ctrl	=	120;
		const static int py_switch_right_ctrl	=	121;
		const static int rate_adjust_auto	=	501;
		const static int rate_adjust_disable	=	500;
		const static int rate_adjust_fast	=	502;
		const static int slider_tts_speed	=	65574;
		const static int sound_beep	=	802;
		const static int sound_disable	=	800;
		const static int sound_wave	=	801;
		const static int spin_phrase_ast_deepness_max	=	65561;
		const static int spin_predict_phrase_maxlength	=	65557;
		const static int txt_blur_group	=	65577;
		const static int txt_blur_info	=	65578;
		const static int txt_build_time	=	65583;
		const static int txt_svr_ver	=	65582;
		const static int txt_tts_speed	=	65575;
		const static int txt_ver	=	65581;
		}id;

		class _string{
		public:
		const static int btn_close	=	0;
		const static int cfg_about	=	1;
		const static int cfg_about_title	=	2;
		const static int cfg_associate	=	3;
		const static int cfg_candidate	=	4;
		const static int cfg_habit	=	5;
		const static int cfg_hotkey	=	6;
		const static int cfg_misc	=	7;
		const static int cfg_pinyin	=	8;
		const static int cfg_tts	=	9;
		const static int title_config	=	10;
		}string;

		class _color{
		public:
		const static int blue	=	0;
		const static int configborder	=	1;
		const static int gray	=	2;
		const static int green	=	3;
		const static int red	=	4;
		const static int tabnavbk	=	5;
		const static int white	=	6;
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
