#pragma once

#include "Common.h"
#include <Graphics/SpriteStudio/sstypes.h>

namespace MyClass
{
	/*名称置き換え*/
	//ノーマルマップ用シェーダーポインタ
	using NormalMapPtr = std::shared_ptr<Mof::CShader>;
	//ノーマルマップ用シェーダーバインドポインタ
	using NormalMapBindPtr = std::shared_ptr<Mof::CShaderBindBase>;

	class CNormalMapParameterBase
	{
	protected:
		/*
		* @brief　読み込み（継承先用）
		*/
		bool Load(const std::string& fileName, const NormalMapPtr& shader,
			const NormalMapBindPtr& shaderBind);
		/*
		* @brief　シェーダーにカメラを設定（継承先用）
		*/
		void SetCamera(const NormalMapBindPtr& bind);
	public:
		CNormalMapParameterBase();
		virtual ~CNormalMapParameterBase() = default;

		/*
		* @brief　読み込み
		* @param fileName　シェーダーのファイル名
		* @return true なら成功
		*/
		virtual bool Load(const std::string& fileName) = 0;

		/*
		* @brief　シェーダー取得
		*/
		virtual const NormalMapPtr& GetShader() const noexcept = 0;
		/*
		* @brief　シェーダーバインド取得
		*/
		virtual const NormalMapBindPtr& GetShaderBind() const noexcept = 0;
		/*
		* @brief　シェーダーにカメラを設定
		*/
		virtual void SetCamera() = 0;
	};
}



