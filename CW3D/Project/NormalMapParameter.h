#pragma once
#include "Common.h"
#include "CameraBase.h"

namespace MyClass
{
	/*名称置き換え*/
	//ノーマルマップ用シェーダーポインタ
	using NormalMapPtr = std::shared_ptr<Mof::CShader>;
	//ノーマルマップ用シェーダーバインドポインタ
	using NormalMapBindPtr = std::shared_ptr<Mof::CShaderBind_BumpMapping>;


	class CNormalMapParameter
	{
	private:
		NormalMapPtr normalMap_;
		NormalMapBindPtr normalMapBind_;
	public:
		CNormalMapParameter();
		~CNormalMapParameter();
		/*
		* @brief　読み込み
		* @param fileName　シェーダーのファイル名
		* @return true なら成功
		*/
		bool Load(const std::string& fileName);

		/*
		* @brief　シェーダー取得
		*/
		const NormalMapPtr& GetShader();
		/*
		* @brief　シェーダーバインド取得
		*/
		const NormalMapBindPtr& GetShaderBind();
		/*
		* @brief　シェーダーにカメラを設定
		*/
		void SetCamera();
	};

	using NormalMapParameterPtr = std::shared_ptr<CNormalMapParameter>;
}



