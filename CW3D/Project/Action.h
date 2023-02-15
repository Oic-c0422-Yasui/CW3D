#pragma once

#include	"IAction.h"
#include	"AnimationDefine.h"
#include	"StateDefine.h"

namespace ActionGame {

	
	/**
	 * @brief		アクション基底クラス
	 */
	class CAction : public IAction
	{
	private:
		/* 姿勢クラス */
		TransformPtr					m_Transform;

		/* 速度クラス */
		VelocityPtr						m_Velocity;

		/* アニメーションクラス */
		AnimationStatePtr				m_Animation;

		/* パラメーター情報クラス */
		AnyParameterMapPtr				m_Parameters;

		/* スキル操作クラス */
		SkillControllerPtr				m_SkillController;
		

		/**
		 * @brief		姿勢登録
		 */
		void SetTransform(TransformPtr t) final { m_Transform = t; }

		/**
		 * @brief		姿勢登録
		 */
		void SetVelocity(VelocityPtr v) final { m_Velocity = v; }

		///**
		// * @brief		アニメーション登録
		// */
		void SetAnimation(AnimationStatePtr a)  { m_Animation = a; }

		/**
		 * @brief		パラメーター情報登録
		 */
		void SetParameterMap(const AnyParameterMapPtr& a) final { m_Parameters = a; }

		/**
		 * @brief		スキル操作登録
		 */
		void SetSkillController(const SkillControllerPtr & a) final { m_SkillController = a; }

	protected:
		/** privateメンバ取得専用 */
		TransformPtr Transform() { return m_Transform; }
		VelocityPtr	 Velocity()	 { return m_Velocity; }
		AnimationStatePtr AnimationState() { return m_Animation; }
		AnyParameterMapPtr ParameterMap() { return m_Parameters; }
		SkillControllerPtr SkillController() { return m_SkillController; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CAction()
			: m_Transform()
			, m_Velocity()
			, m_Animation()
			, m_Parameters()
			, m_SkillController()
		{
		}

		/**
		 * @brief		新規アクションの生成
		 * @return		生成したアクション
		 */
		template < typename T, typename... _Args >
		static std::shared_ptr< T > Create(_Args&& ... args) {
			if (!std::is_base_of<CAction, T >::value)
			{
				return std::shared_ptr<T>();
			}
			auto re = std::make_shared<T>(args...);
			return re;
		}
	};

}