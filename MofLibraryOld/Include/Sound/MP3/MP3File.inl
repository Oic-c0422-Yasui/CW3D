/*************************************************************************//*!
					
					@file	MP3File.inl
					@brief	MP3ファイルの読み込みとデコードを行うクラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

/*************************************************************************//*!
		@brief			名前設定
		@param[in]		pName			設定する名前
				
		@return			TRUE			正常終了<br>
						それ以外		設定エラー、エラーコードを返す。
*//**************************************************************************/
FORCE_INLINE MofBool CMp3File::SetName(LPCMofChar pName){
	return m_pFile->SetName(pName);
}
/*************************************************************************//*!
		@brief			名前取得
		@param			None

		@return			名前の取得
*//**************************************************************************/
FORCE_INLINE LPString CMp3File::GetName(void){
	return m_pFile->GetName();
}
/*************************************************************************//*!
		@brief			WAVEフォーマット取得
		@param			None

		@return			WAVEフォーマットの取得
*//**************************************************************************/
FORCE_INLINE LPCWAVEFORMATEX CMp3File::GetWaveFormat(void) const {
	return &m_WaveFormat;
}
/*************************************************************************//*!
		@brief			フレームサイズ取得
		@param			None

		@return			フレームサイズの取得
*//**************************************************************************/
FORCE_INLINE MofU32 CMp3File::GetFrameSize(void) const {
	return m_FrameSize;
}
/*************************************************************************//*!
		@brief			フレームサイズ取得
		@param			None

		@return			フレームサイズの取得
*//**************************************************************************/
FORCE_INLINE MofU32 CMp3File::GetFrameDecodeSize(void) const {
	return m_FrameDecodeSize;
}
/*************************************************************************//*!
		@brief			ストリームサイズ取得
		@param			None

		@return			ストリームサイズの取得
*//**************************************************************************/
FORCE_INLINE MofU32 CMp3File::GetStreamSize(void) const {
	return m_StreamSize;
}
/*************************************************************************//*!
		@brief			ストリームサイズ取得
		@param			None

		@return			ストリームサイズの取得
*//**************************************************************************/
FORCE_INLINE MofU32 CMp3File::GetStreamDecodeSize(void) const {
	return m_DecodeSize;
}
/*************************************************************************//*!
		@brief			サイズ取得
		@param			None

		@return			サイズの取得
*//**************************************************************************/
FORCE_INLINE MofU32 CMp3File::GetSize(void) const {
	if(!m_pFile)
	{
		return 0;
	}
	return m_pFile->GetBufferSize();
}

//[EOF]