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
		// 姿勢管理クラス
		TransformPtr					transform_;

		// 速度管理クラス 
		VelocityPtr						velocity_;

		// アニメーションクラス 
		AnimationStatePtr				animation_;

		// パラメータ情報クラス
		AnyParameterMapPtr				parameters_;

		// スキル操作クラス
		SkillControllerPtr				skillController_;
		
		//　当たり判定クラス
		ColliderPtr						collider_;

		/**
		 * @brief		姿勢登録
		 */
		void SetTransform(TransformPtr transform) final 
		{ 
			transform_ = transform;
		}

		/**
		 * @brief		姿勢登録
		 */
		void SetVelocity(VelocityPtr velocity) final 
		{ 
			velocity_ = velocity;
		}

		///**
		// * @brief		アニメーション登録
		// */
		void SetAnimation(AnimationStatePtr animation)  
		{ 
			animation_ = animation; 
		}

		/**
		 * @brief		パラメーター情報登録
		 */
		void SetParameterMap(const AnyParameterMapPtr& parameter) final 
		{ 
			parameters_ = parameter; 
		}

		/**
		 * @brief		スキル操作登録
		 */
		void SetSkillController(const SkillControllerPtr & skill) final 
		{ 
			skillController_ = skill; 
		}

		/**
		 * @brief		当たり判定登録
		 */
		void SetCollider(const ColliderPtr& collider) final
		{
			collider_ = collider;
		}

	protected:
		/** privateメンバ取得専用 */
		//姿勢クラス
		TransformPtr Transform() { return transform_; }
		//速度クラス
		VelocityPtr	 Velocity()	 { return velocity_; }
		//アニメーションクラス
		AnimationStatePtr AnimationState() { return animation_; }
		//パラメータ情報クラス
		AnyParameterMapPtr ParameterMap() { return parameters_; }
		//スキル操作クラス
		SkillControllerPtr SkillController() { return skillController_; }
		//当たり判定
		ColliderPtr		Collider() { return collider_; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CAction()
			: transform_()
			, velocity_()
			, animation_()
			, parameters_()
			, skillController_()
			, collider_()
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