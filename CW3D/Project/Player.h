#pragma once

#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"
#include	"ActorObject.h"
#include	"Observer.h"
#include	"PlayerActionCreator.h"
#include	"PlayerStateCreator.h"
#include	"PlayerSkillCreator.h"
#include	"PlayerParameterCreator.h"
#include	"EffectController.h"
#include	"Combo.h"

namespace ActionGame
{

	#define COMBO_SHOW_TIME 5.0f

	/*
	* @brief	�v���C���[
	*/
	class CPlayer : public ActionGame::CActorObject
	{
	private:

		//�C���v�b�g�L�[
		Input::InputPtr		input_;

		//�I�u�U�[�o�[�ő�HP
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<int> > maxHP_;

		//�I�u�U�[�o�[�ő�K�E�Z�Q�[�W
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<float> > maxUltGauge_;

		//�A�N�V��������
		ActionGame::PlayerActionCreator actionCreator_;
		//��Ԑ���
		ActionGame::PlayerStateCreator stateCreator_;
		//�X�L������
		ActionGame::PlayerSkillCreator skillCreator_;
		//�p�����[�^����
		ActionGame::PlayerParameterCreator parameterCreator_;

		//������̓����蔻��T�C�Y
		CVector3 escapeColliderSize_;

		//�R���{
		std::shared_ptr<CCombo>	combo_;

	public:
		CPlayer();
		~CPlayer() override;
		/*
		* @brief	�ǂݍ���
		* @return	true�@�Ȃ�ǂݍ��ݐ���
		*/
		bool Load() override;
		/*
		* @brief	������
		*/
		void Initialize() override;
		/*
		* @brief	�X�V
		*/
		void Update() override;
		/*
		* @brief	�`��
		*/
		void Render() override;
		/*
		* @brief	�QD�f�o�b�O�`��
		*/
		void RenderDebug2D();
		/*
		* @brief	���
		*/
		void Release()override;
		
		/*
		* @brief		�_���[�W����
		* @param direction	�m�b�N�o�b�N�̕���
		* @param power	�m�b�N�o�b�N�̗�
		* @param damage �_���[�W��
		* @param armorBrakeLevel �A�[�}�[�j�󃌃x��
		*/
		void Damage(const Vector3& direction,
					const Vector3& power,
					int damage,
					BYTE armorBrakeLevel);

		/*
		* @brief		�_���[�W����(�G�t�F�N�g�𔭐�������)
		* @param direction	�m�b�N�o�b�N�̕���
		* @param power	�m�b�N�o�b�N�̗�
		* @param damage �_���[�W��
		* @param armorBrakeLevel �A�[�}�[�j�󃌃x��
		* @param effect	�_���[�W�G�t�F�N�g
		*/
		void Damage(const Vector3& direction,
					const Vector3& power,
					int damage,
					BYTE armorBrakeLevel,
					const EffectCreateParameterPtr& effect);

		/*
		* @brief		�C���v�b�g�L�[�̐ݒ�
		* @param ptr	�C���v�b�g
		*/
		void SetInput(const Input::InputPtr& input) noexcept
		{
			input_ = input;
		}

		/*
		* @brief		HP�̎擾
		* @return HP
		*/
		int GetHP() const noexcept
		{
			return actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
		}


		/*
		* @brief		HP�ω��ʒm
		*/
		ActionGame::IObservable<int>& GetHPSubject() 
		{ 
			return  actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP); 
		}
		ActionGame::IObservable<int>* GetMaxHPSubject() { return &(maxHP_.Get()); }

		
		/*
		* @brief		�R���{���ʒm
		*/
		ActionGame::IObservable<uint32_t>& GetComboSubject()
		{
			return combo_->GetCountParam();
		}

		/*
		* @brief		�R���{�\�����Ԓʒm
		*/
		ActionGame::IObservable<float>& GetComboTimeSubject()
		{
			return combo_->GetTimeSubject();
		}

		/*
		* @brief		�X�L���擾
		* @param id	�z��ԍ�
		* @return �X�L��
		*/
		const ActionGame::SKillPtr& GetSkill(int id) const noexcept {
			return GetSkillController()->GetSkill(id);
		}


		/*
		* @brief		�A�b�v�L���X�g�����X�L���擾
		* @param id	�z��ԍ�
		* @return �X�L��
		*/
		template< typename T >
		const std::shared_ptr<T> GetCastSkill(int id) const noexcept {
			auto& skill = GetSkillController()->GetSkill(id);
			auto& castSkill = std::dynamic_pointer_cast<T>(skill);
			assert(castSkill);
			return  castSkill;
		}
		//�K�E�Z�Q�[�W
		ActionGame::IObservable<float>* GetMaxUltSubject() { return &(maxUltGauge_.Get()); }
		ActionGame::IObservable<float>& GetUltSubject() { return actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE); }

		/*
		* @brief	�X�L���R���g���[���[���擾
		* @return	�X�L���R���g���[���[
		*/
		const ActionGame::SkillControllerPtr& GetSkillController() const noexcept
		{
			return actor_->GetSkillController();
		}

		/*
		* @brief	�ő�K�E�Z�Q�[�W���擾����
		* @return	�ő�K�E�Z�Q�[�W
		*/
		float GetMaxUltGauge() const noexcept
		{
			return maxUltGauge_.Get();
		}

		/*
		* @brief	�����Ԃ��H
		* @return	true�@�Ȃ������
		*/
		bool IsEscape() const
		{
			return actor_->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
		}

		/*
		* @brief	���G��Ԃ��H
		* @return	true �Ȃ疳�G���
		*/
		bool IsInvincible() const;


		/*
		* @brief	������̓����蔻��擾
		* @return	AABB�̓����蔻��
		*/
		CAABB GetEscapeCollider() noexcept
		{
			CAABB collider(actor_->GetPosition() + colliderOffset_, escapeColliderSize_);
			return collider;
		}

		/*
		* @brief	�N���A�|�[�Y���J�n����
		*/
		void ClearPose();
	};

	using PlayerPtr = std::shared_ptr<CPlayer>;
}

