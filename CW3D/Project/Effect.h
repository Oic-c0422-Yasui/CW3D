#pragma once
#include "Common.h"
#include "CharaTypeDefine.h"
namespace ActionGame
{
	/*
	* @brief エフェクトの作成パラーメータ
	* @param	name	エフェクト名
	* @param	offset	座標オフセット
	* @param	scale	大きさ
	* @param	rotate	回転値
	* @param	speed	速度
	* @param	type	キャラのタイプ
	*/
	struct EffectCreateParameter
	{
		std::string name;	
		Vector3 offset;
		Vector3 scale;
		Vector3 rotate;
		float speed;
		CHARA_TYPE type;
	};
	using EffectCreateParameterPtr = std::shared_ptr<EffectCreateParameter>;

	/*
	* @brief	エフェクト再生クラス
	*/
	class CEffect
	{
	private:
		Effekseer::Handle					handle_;
		bool								isStop_;
		Vector3								offset_;
		float								speed_;
		CHARA_TYPE							type_;
	public:

		CEffect(Effekseer::Handle handle);
		~CEffect();

		/*
		* @brief	初期化
		* @param	offset	座標のオフセット
		*/
		void Initialize( const Vector3& offset,float speed,CHARA_TYPE type);

		/*
		* @brief	更新
		*/
		void Update();

		/*
		* @brief	再生が停止されているか？
		* @return	true　なら停止されている
		*/
		bool IsStop() const noexcept
		{
			return  isStop_;
		}

		/*
		* @brief	再生停止設定
		* @param	isStop	再生停止可否
		*/
		void SetStop(bool isStop) noexcept
		{
			isStop_ = isStop;
		}

		/*
		* @brief	再生ハンドルを取得
		* @return	再生ハンドル
		*/
		Effekseer::Handle GetHandle() const noexcept
		{
			return handle_;
		}

		/*
		* @brief	座標オフセットを取得
		* @return	座標オフセット
		*/
		const Vector3& GetOffset() const noexcept
		{
			return offset_;
		}

		float GetSpeed() const noexcept
		{
			return speed_;
		}
	
	};

	//ポインタ置き換え
	using EffectPtr = std::shared_ptr<CEffect>;
}

