/*************************************************************************//*!
					
					@file	ImageReader.h
					@brief	PSD内部画像保存用クラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__IMAGEREADER__H__

#define		__IMAGEREADER__H__

//INCLUDE
#include	"../../Common/DynamicArray.h"

namespace Mof {
	
	/*******************************//*!
	@brief	画像ファイルデータ保存構造体

			画像ファイルデータ保存構造体。

	@author	CDW
	*//********************************/
	typedef struct MOFLIBRARY_API tag_MOFIMAGEDATA {
		CString				Name;					//!<ファイル名
		MofU8*				pData;					//!<画像データ
		MofU32				Size;					//!<画像サイズ
		
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		tag_MOFIMAGEDATA() :
		Name() ,
		pData(NULL) ,
		Size(0) {
		}
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピーイメージ

				@return			None
		*//**************************************************************************/
		tag_MOFIMAGEDATA(const tag_MOFIMAGEDATA& pObj) :
		Name(pObj.Name) ,
		pData(NULL) ,
		Size(pObj.Size) {
			pData = (LPMofU8)MOF_ALLOCATOR(Size,"CImageReader");
			memcpy(pData,pObj.pData,Size);
		}
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~tag_MOFIMAGEDATA(){
			Name.SetString(NULL);
			MOF_SAFE_FREE(pData,"CImageReader Release");
		}
	}MOFIMAGEDATA,*LPMOFIMAGEDATA;
	typedef CDynamicArray< LPMOFIMAGEDATA > CImageDataArray,*LPImageDataArray;
	
	/*******************************//*!
	@brief	PSD内部画像クラス

			PSD内部画像クラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CImageReader : public IMofNamedObject {
	protected:
		/*******************//*!
		元ファイル名
		*//********************/
		CString						m_Name;
		/*******************//*!
		画像データ配列
		*//********************/
		CImageDataArray				m_ImageData;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CImageReader();
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピーイメージ

				@return			None
		*//**************************************************************************/
		CImageReader(const CImageReader& pObj);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CImageReader();

		/*************************************************************************//*!
				@brief			ファイルの読み込み
				@param[in]		pName		ファイル名
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Load(LPCMofChar pName) = 0;

		/*************************************************************************//*!
				@brief			解放
				@param[in]		pData			解放追加データ

				@return			TRUE			正常終了<br>
								それ以外		解放エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool Release(LPMofVoid pData = NULL);
		
		//----------------------------------------------------------------------------
		////Set
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			名前設定
				@param[in]		pName			設定する名前
				
				@return			TRUE			正常終了<br>
								それ以外		設定エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool SetName(LPCMofChar pName);

		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			名前取得
				@param			None

				@return			名前の取得
		*//**************************************************************************/
		virtual LPString GetName(void);
		/*************************************************************************//*!
				@brief			イメージ配列取得
				@param			None

				@return			イメージ配列
		*//**************************************************************************/
		LPImageDataArray GetImage(void);
		/*************************************************************************//*!
				@brief			イメージ名取得
				@param[in]		Index			配列内番号

				@return			イメージ名
		*//**************************************************************************/
		LPString GetImageName(MofS32 Index);
		/*************************************************************************//*!
				@brief			イメージデータ取得
				@param[in]		Index			配列内番号

				@return			イメージデータ
		*//**************************************************************************/
		MofU8* GetImageData(MofS32 Index);
		/*************************************************************************//*!
				@brief			イメージデータサイズ取得
				@param[in]		Index			配列内番号

				@return			イメージデータサイズ
		*//**************************************************************************/
		MofU32 GetImageDataSize(MofS32 Index);
		/*************************************************************************//*!
				@brief			イメージデータ配列数取得
				@param			None

				@return			イメージデータ配列数
		*//**************************************************************************/
		MofU32 GetImageCount(void) const;
		
		//クラス基本定義
		MOF_LIBRARYCLASS_NOTEQUAL(CImageReader,MOF_IMAGEREADERCLASS_ID);
	};

	//TYPEDEF
	typedef CImageReader* LPImageReader;

	//INLINE INCLUDE
	#include	"ImageReader.inl"

}

#endif		//__IMAGEREADER__H__

//[EOF]