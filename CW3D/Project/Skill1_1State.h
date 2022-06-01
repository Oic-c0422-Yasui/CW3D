#pragma once


#include	"State.h"
#include	"Skill1_1Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class Skill1_1State : public State
	{
	private:
		/** 移動アクション */
		Skill1_1ActionPtr			m_SkillAction;
		bool						m_NextInputFlg;
		int							m_FrameTime;
		std::vector<ShotPtr>		m_Shots;
		EffectPtr					m_Effect;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Skill1_1State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<Skill1_1Action>(GetKey());

			m_NextInputFlg = false;
			m_FrameTime = 0;
			if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(false);

			}
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(true);

			}
			m_SkillAction->Start();
			auto attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			attack *= Actor()->GetSkillController()->GetSkill(SKILL_KEY_1)->GetDamage() * 0.01f;
			m_Effect = EffectControllerInstance.Play("Effect3");
			if (Actor()->IsReverse())
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition() , Vector3(-6.0f, 0.7f, 0), Vector3(5.0f, 10.0f, 7.0f), attack, 0.05f, 0));
				EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, MOF_ToRadian(-90), 0.0f));
				EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(-0.8f, -1.5f, 0));

			}
			else
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(6.0f, 0.7f, 0), Vector3(5.0f, 10.0f, 7.0f), attack, 0.05f, 0));
				EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, MOF_ToRadian(90), 0.0f));
				EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(0.8f, -1.5f, 0));
			}
			EffectControllerInstance.SetScale(m_Effect->GetHandle(), Vector3(1.0f, 1.0f, 1.0f));
			EffectControllerInstance.SetSpeed(m_Effect->GetHandle(), 1.8f);

			
			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBack(Vector3(0.5f,0.2f,0));
			}
			
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK1, 0.0f, 0.6f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {

			for (auto& shot : m_Shots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_FrameTime < 55)
				{
					shot->SetCollideFlg(false);


				}
				else if (!shot->GetCollideFlg())
				{
					shot->SetCollideFlg(true);
				}
				if (m_FrameTime > 80)
				{
					if (shot->GetCollideFlg())
					{
						shot->SetCollideFlg(false);
					}
				}

			}
			m_FrameTime++;
			

			

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				if (Actor()->GetTransform()->GetPositionY() > 0)
				{
					ChangeState(STATE_KEY_FALL);
				}
				else
				{
					ChangeState(STATE_KEY_IDLE);
				}
				
			}


		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {


			//対応したスキルのボタンが押されていたらそのスキルのステートに移動
			for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
			{
				if (!Actor()->GetSkillController()->GetSkill(i)->GetCanUseFlg() || Actor()->GetSkillController()->GetSkill(i)->GetState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(Actor()->GetSkillController()->GetSkill(i)->GetButton()))
				{

					Actor()->GetSkillController()->GetSkill(i)->Start();
					//宙に浮いていれば空中発動
					if (Actor()->GetTransform()->GetPositionY() > 0)
					{
						ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetFlyState());
					}
					else
					{
						ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetState());
					}
					break;
				}
			}
		}



		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override {
			m_SkillAction->End();
			for (auto& shot : m_Shots)
			{
				shot->SetShow(false);
				shot.reset();
			}
			m_Shots.clear();
			if (m_Effect != nullptr)
			{
				m_Effect->SetStop(true);
				m_Effect.reset();
			}
			
		}

		/**
		 * @brief		ステート内の接触イベント
		 * @param[in]	type		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		void CollisionEvent(unsigned int type, std::any obj) override {
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override {
			return STATE_KEY_SKILL1_1;
		}
	};

}