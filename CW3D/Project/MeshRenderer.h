#pragma once
#include "Common.h"
#include "NormalMapParameter.h"

namespace MyClass
{

	/*名称置き換え*/
	//メッシュポインタ
	using MeshPtr = std::shared_ptr<Mof::CMeshContainer>;
	//マトリクス(4×4)
	using Matrix = Mof::CMatrix44;
	//モーション
	using MotionPtr = Mof::LPMeshMotionController;
	//色(Vector4)
	using Color = Mof::Vector4;

	/*
	* @brief メッシュ描画を行うクラス
	*/
	class CMeshRenderer
	{
	private:
		MeshPtr mesh_;
		NormalMapParameterPtr normalMap_;
		bool isEnableNormalMap_;
	public:
		CMeshRenderer();
		~CMeshRenderer();
		/*
		* @brief	リソースマネージャーから読み込み（既に素材が読み込まれている場合のみ）
		* @param	meshTag　メッシュタグ名
		* @param	meshName メッシュ名
		* @param	shaderName シェーダー名
		* @return	true　なら成功
		*/
		bool Load(const std::string& meshTag,const std::string& meshName, const std::string& shaderName);

		/*
		* @brief メッシュ描画
		* @param mat マトリクス(４×４)
		* @param color 色(Vector4)
		*/
		void Render(const Matrix& mat,const MyClass::Color& color);
		/*
		* @brief モーション適用メッシュ描画
		* @param motion モーション
		* @param color 色(Vector4)
		*/
		void Render(MotionPtr motion, const MyClass::Color& color);

		/*
		* @brief　解放
		*/
		void Release();

		/*
		* @brief モーションコントローラー生成
		*/
		MotionPtr CreateMotionController();
	};
}



