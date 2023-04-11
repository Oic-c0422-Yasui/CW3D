#pragma once
#include "Common.h"

namespace MyClass
{

	/*名称置き換え*/
	//ノーマルマップ用シェーダーポインタ
	using NormalMapSkinnedPtr = std::shared_ptr<Mof::CShader>;
	//ノーマルマップ用シェーダーバインドポインタ
	using NormalMapSkinnedBindPtr = std::shared_ptr<Mof::CShaderBind_BumpMappingSkinned>;


	class CNormalMapSkinnedParameter
	{
	private:
		NormalMapSkinnedPtr normalMap_;
		NormalMapSkinnedBindPtr normalMapBind_;
	public:
		CNormalMapSkinnedParameter();
		~CNormalMapSkinnedParameter();
		/*
		* @brief　読み込み
		* @param fileName　シェーダーのファイル名
		* @return true なら成功
		*/
		bool Load(const std::string& fileName);

		/*
		* @brief　シェーダー取得
		*/
		const NormalMapSkinnedPtr& GetShader();
		/*
		* @brief　シェーダーバインド取得
		*/
		const NormalMapSkinnedBindPtr& GetShaderBind();
		/*
		* @brief　シェーダーにカメラを設定
		*/
		void SetCamera();
	};

	using NormalMapSkinnedParameterPtr = std::shared_ptr<CNormalMapSkinnedParameter>;

}


