/*************************************************************************//*!
					
					@file	SoundBufferBase.inl
					@brief	各種サウンドバッファの処理を行う基底クラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

/*************************************************************************//*!
		@brief			ループフラグがONか判定
		@param			None

		@return			TRUE			ループ再生する<br>
						FALSE			ループしない
*//**************************************************************************/
FORCE_INLINE MofBool CSoundBufferBase::IsLoop(void){
	return m_bLoop;
}
/*************************************************************************//*!
		@brief			名前設定
		@param[in]		pName			設定する名前
				
		@return			TRUE			正常終了<br>
						それ以外		設定エラー、エラーコードを返す。
*//**************************************************************************/
FORCE_INLINE MofBool CSoundBufferBase::SetName(LPCMofChar pName){
	return m_Name.SetString(pName);
}
/*************************************************************************//*!
		@brief			ループフラグの設定
		@param[in]		bl			ループフラグ（TRUE:ループする、FALSE:ループしない）
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
FORCE_INLINE MofBool CSoundBufferBase::SetLoop(MofBool bl){
	m_bLoop = bl;
	return TRUE;
}
/*************************************************************************//*!
		@brief			名前取得
		@param			None

		@return			名前の取得
*//**************************************************************************/
FORCE_INLINE LPString CSoundBufferBase::GetName(void){
	return &m_Name;
}
/*************************************************************************//*!
		@brief			再生音量取得
		@param			None
				
		@return			音量(0.0(無音)〜1.0(通常))
*//**************************************************************************/
FORCE_INLINE MofFloat CSoundBufferBase::GetVolume(void) const {
	return m_Volume;
}
/*************************************************************************//*!
		@brief			再生ピッチ取得
		@param			None
				
		@return			ピッチ
*//**************************************************************************/
FORCE_INLINE MofFloat CSoundBufferBase::GetPitch(void) const {
	return m_Pitch;
}
/*************************************************************************//*!
		@brief			音ファイルの時間取得
		@param			None
				
		@return			音ファイルの時間
*//**************************************************************************/
FORCE_INLINE MofFloat CSoundBufferBase::GetTime(void) const {
	return m_Time;
}

//[EOF]