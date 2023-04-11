#pragma once

#include "Common.h"

namespace MyClass
{
	//メッシュポインタ
	using MeshPtr = std::shared_ptr<CMeshContainer>;
	//テクスチャポインタ
	using TexturePtr = std::shared_ptr<CTexture>;

	/*
	* @brief	テクスチャとノーマルマップのないマテリアルに仮のテクスチャを付与する
	*/
	class CGiveTextureToMaterial
	{
	private:
		TexturePtr meshTexture_;
		TexturePtr normalMapTexture_;
	public:
		CGiveTextureToMaterial();
		~CGiveTextureToMaterial();
		/*
		* @brief	仮のテクスチャ読み込み
		*/
		bool Load();
		/*
		* @brief 仮のテクスチャを付与する
		* @param mesh　付与する対象のメッシュ
		*/
		void Give(const MeshPtr& mesh);

	};

	using GiveTextureToMaterialPtr = std::shared_ptr<CGiveTextureToMaterial>;
}


