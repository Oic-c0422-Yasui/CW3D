#pragma once
#include "Effect.h"

#include "Singleton.h"

namespace ActionGame 
{
	/*
	* エフェクト操作クラス
	*/
	class CEffectController : public Singleton<CEffectController>
	{
		friend class Singleton<CEffectController>;
	private:
		std::vector<EffectPtr> m_Effects;


		CEffectController()
			: Singleton<CEffectController>()
		{
		}


		void Create(const Effekseer::Handle& handle,const Vector3& position, EffectCreateParameter param);
	public:

		/*
		* @brief	エフェクト再生
		* @param	key エフェクト名
		* @param	pos	エフェクト座標
		* @param	param	エフェクト作成パラメータ
		*/
		EffectPtr Play(const std::string& key,const Vector3& pos, EffectCreateParameter param);

		/*
		* @brief	更新
		*/
		void Update();
		/*
		* @brief	エフェクト削除
		*/
		void Delete();
		/*
		* @brief	すべてのエフェクトを破棄
		*/
		void Reset();
		
		/*
		* @brief	エフェクト取得
		* @param	id 配列番号
		* @return	エフェクト
		*/
		const EffectPtr& GetEffect(size_t id)
		{
			assert(m_Effects[id]);
			return m_Effects[id];
		}

		/*
		* @brief	エフェクト回転設定
		* @param	handle エフェクトハンドル
		* @param	rotate	回転値
		*/
		void SetRotate(const Effekseer::Handle& handle, const Vector3& rotate);
		/*
		* @brief	エフェクト座標設定
		* @param	handle エフェクトハンドル
		* @param	pos	座標値
		*/
		void SetPosition(const Effekseer::Handle& handle, const Vector3& pos);
		/*
		* @brief	エフェクトサイズ設定
		* @param	handle エフェクトハンドル
		* @param	scale	サイズ値
		*/
		void SetScale(const Effekseer::Handle& handle, const Vector3& scale);
		/*
		* @brief	エフェクト色設定
		* @param	handle エフェクトハンドル
		* @param	color	色
		*/
		void SetColor(const Effekseer::Handle& handle, const Vector4& color);
		/*
		* @brief	エフェクト移動設定
		* @param	handle エフェクトハンドル
		* @param	pos	座標値
		*/
		void AddPosition(const Effekseer::Handle& handle, const Vector3& pos);
		/*
		* @brief	エフェクト再生速度設定
		* @param	handle エフェクトハンドル
		* @param	speed	再生速度
		*/
		void SetSpeed(const Effekseer::Handle& handle, float speed);


	};
	//簡易アクセス用
	#define EffectControllerInstance 	ActionGame::CEffectController::GetInstance()
}



