#pragma once

namespace SOUI
{
	class CBlurListAdapter;

	class CConfigDlg: public SHostWnd
	{
	public:
		CConfigDlg();
		~CConfigDlg(void);		

	protected:
		void FindAndSetCheck(int id, BOOL bcheck);
		void FindAndSetText(int id, LPCTSTR text);
		void FindAndSetSpin(int id, int nValue);
		void FindAndSetHotKey(int id, DWORD accel);
		void InitPageHabit();
		void InitPageHotKey();
		void InitPageAssociate();
		void InitPageCandidate();
		void InitPageMisc();
		void InitPageAbout();
		void InitPageTTS();

		void InitPinyinBlur(COMFILE & cf, CBlurListAdapter * pBlurAdapter, int iGroup);
		void InitPagePinYin();

		void InitPages();


		LPBYTE InitTtsTokenInfo(LPBYTE pBuf, SComboBox *pCbx);

		void OnClickInputSwitch(int id);
		//回车
		void OnClickEnter(int id);
		//临时拼音
		void OnClickPYTemp(int id);

		void OnClickAlertMode(int id);

		//重码自动上屏
		void OnAutoInput();
		//拼音重码词组优先
		void OnPyPhraseFirst();

		//show op tip
		void OnChkOpTip(EventArgs *e);

		//联想类型
		void OnClickAssMode(int id);
		void OnClickForcast(int id);
		//GBK重码
		void OnClickGBK(int id);
		//出简不出全
		void OnChkFullSkipSimple();
		//词频调整
		void OnClickRateAdjust(int id);

		void OnClickAutoCompPromp();
		void OnClickAutoDot();
		void OnClickAutoSelectCand();
		void OnClickSendInput();
		void OnDisableNumSelCand();
		void OnEnable23Cand();
		void OnHotKeyEvent(EventArgs *pEvt);
		void OnClose();
		void OnWebHeaderNotify(EventArgs *e);

		void OnTtsSpeedChanged(EventArgs *e);
		void OnTtsChPreview();
		void OnTtsEnPreview();

		void OnPyBlurClick(EventArgs *e);
		void OnJPBlurClick(EventArgs *e);
		void OnTtsChTokenChange(EventArgs *e);
		void OnTtsEnTokenChange(EventArgs *e);

		void OnReNotify(EventArgs *e);

		EVENT_MAP_BEGIN()
			EVENT_ID_COMMAND_RANGE(100, 102, OnClickInputSwitch)
			EVENT_ID_COMMAND_RANGE(110, 111, OnClickInputSwitch)
			EVENT_ID_COMMAND_RANGE(120, 122, OnClickPYTemp)
			EVENT_ID_COMMAND(R.id.cand_auto_input, OnAutoInput)
			EVENT_ID_COMMAND(R.id.cand_py_phrase_first, OnPyPhraseFirst)
			EVENT_ID_HANDLER(R.id.chk_show_op_tip,EventCmd::EventID, OnChkOpTip)
			EVENT_ID_COMMAND_RANGE(400, 403, OnClickAssMode)
			EVENT_ID_COMMAND_RANGE(600, 602, OnClickForcast)
			EVENT_ID_COMMAND_RANGE(700, 702, OnClickGBK)
			EVENT_ID_COMMAND(R.id.chk_full_skip_simple, OnChkFullSkipSimple)
			EVENT_ID_COMMAND_RANGE(500, 502, OnClickRateAdjust)
			EVENT_ID_COMMAND_RANGE(R.id.sound_disable,R.id.sound_beep,OnClickAlertMode)
			EVENT_ID_COMMAND(R.id.chk_auto_comp_promp, OnClickAutoCompPromp)
			EVENT_ID_COMMAND(R.id.chk_auto_dot, OnClickAutoDot)
			EVENT_ID_COMMAND(R.id.chk_auto_select_cand, OnClickAutoSelectCand)
			EVENT_ID_COMMAND(R.id.chk_sent_input, OnClickSendInput)
			EVENT_ID_COMMAND(R.id.chk_disable_number_to_select_cand, OnDisableNumSelCand)
			EVENT_ID_COMMAND(R.id.chk_enable_23cand_hotkey, OnEnable23Cand)
			EVENT_ID_COMMAND(R.id.btn_close,OnClose)
			EVENT_HANDLER(EventSetHotKey::EventID, OnHotKeyEvent)
			EVENT_ID_HANDLER(R.id.edit_webmode_header,EventRENotify::EventID,OnWebHeaderNotify)
			EVENT_ID_HANDLER(R.id.slider_tts_speed,EventSliderPos::EventID,OnTtsSpeedChanged)
			EVENT_ID_HANDLER(R.id.cbx_tts_ch_token,EventCBSelChange::EventID,OnTtsChTokenChange)
			EVENT_ID_HANDLER(R.id.cbx_tts_en_token, EventCBSelChange::EventID, OnTtsEnTokenChange)
			EVENT_ID_COMMAND(R.id.btn_tts_ch_preview,OnTtsChPreview)
			EVENT_ID_COMMAND(R.id.btn_tts_en_preview, OnTtsEnPreview)
			EVENT_ID_HANDLER(R.id.chk_py_blur, EventCmd::EventID, OnPyBlurClick)
			EVENT_ID_HANDLER(R.id.chk_jp_zcs, EventCmd::EventID, OnJPBlurClick)
			EVENT_ID_HANDLER(R.id.edit_predict_phrase_maxlength,EventRENotify::EventID,OnReNotify)
			EVENT_ID_HANDLER(R.id.edit_phrase_ast_deepness_max, EventRENotify::EventID, OnReNotify)
			EVENT_ID_HANDLER(R.id.edit_sent_record_max, EventRENotify::EventID, OnReNotify)
			EVENT_MAP_END()


	protected:
		int OnCreate(LPCREATESTRUCT lpCreateStruct);
		void OnDestroy();

		BEGIN_MSG_MAP_EX(CConfigDlg)
			MSG_WM_CREATE(OnCreate)
			MSG_WM_DESTROY(OnDestroy)
			CHAIN_MSG_MAP(SHostWnd)
		END_MSG_MAP()

	};

}