/*************************************************************************//*!
					
					@file	DX11Texture.inl
					@brief	DirectX11テクスチャ基底クラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

/*************************************************************************//*!
		@brief			テクスチャ取得
		@param			None

		@return			テクスチャ
*//**************************************************************************/
FORCE_INLINE MofTextureHandle CDX11Texture::GetTextureHandle(void) {
	return m_pTexture;
}

//[EOF]