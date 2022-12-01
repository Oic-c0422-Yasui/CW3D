#pragma once
#include "Common.h"
namespace Sample
{
	/*
	* エフェクトの作成パラーメータ
	*/
	struct EffectCreateParameter
	{
		std::string name;
		Vector3 offset;
		Vector3 scale;
		Vector3 rotate;
		float speed;
	};
	/*
	* @brief	エフェクト再生クラス
	*/
	class Effect
	{
	private:

		Effekseer::EffectRef				m_Effect;
		Effekseer::Handle					m_Handle;
		CVector3							m_Position;
		Vector3								m_Rotation;
		bool								m_StopFlg;
		Vector3								m_Offset;

	public:

		Effect(Effekseer::Handle handle);
		~Effect();

		/*
		* @brief	初期化
		* @param	offset	座標のオフセット
		*/
		void Initialize( const Vector3& offset);

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
			return  m_StopFlg;
		}

		/*
		* @brief	再生停止設定
		* @param	isStop	再生停止可否
		*/
		void SetStop(bool isStop) noexcept
		{
			m_StopFlg = isStop;
		}

		/*
		* @brief	再生ハンドルを取得
		* @return	再生ハンドル
		*/
		Effekseer::Handle GetHandle() const noexcept
		{
			return m_Handle;
		}

		/*
		* @brief	座標オフセットを取得
		* @return	座標オフセット
		*/
		const Vector3& GetOffset() const noexcept
		{
			return m_Offset;
		}
	
	};

	//ポインタ置き換え
	using EffectPtr = std::shared_ptr<Effect>;
}

