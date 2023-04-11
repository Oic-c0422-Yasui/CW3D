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
		NormalMapPtr normalMap_;

	protected:
		bool CreateShaderBind(const NormalMapBindPtr& bind);
		void SetCameraBind(const NormalMapBindPtr& bind);
	public:
		CNormalMapParameterBase();
		virtual ~CNormalMapParameterBase() = default;

		/*
		* @brief　読み込み
		* @param fileName　シェーダーのファイル名
		* @return true なら成功
		*/
		virtual bool Load(const std::string& fileName);

		/*
		* @brief　シェーダー取得
		*/
		virtual const NormalMapPtr& GetShader() const noexcept;
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



