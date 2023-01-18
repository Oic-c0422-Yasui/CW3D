#pragma once

#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"
#include	"ActorObject.h"
#include	"Observer.h"
#include	"PlayerActionCreator.h"
#include	"PlayerStateCreator.h"
#include	"PlayerSkillCreater.h"
#include	"PlayerParameterCreator.h"

/*
* @brief	�v���C���[
*/
class CPlayer : public ActionGame::ActorObject
{
private:

	//�C���v�b�g�L�[
	ActionGame::InputPtr		m_pInput;

	//�I�u�U�[�o�[�ő�HP
	ActionGame::ParameterHandle< ActionGame::ReactiveParameter<int> > m_MaxHP;

	//�I�u�U�[�o�[�ő�K�E�Z�Q�[�W
	ActionGame::ParameterHandle< ActionGame::ReactiveParameter<float> > m_MaxUltGauge;

	//�A�N�V��������
	ActionGame::PlayerActionCreator m_ActionCreator;
	//��Ԑ���
	ActionGame::PlayerStateCreator m_StateCreator;
	//�X�L������
	ActionGame::PlayerSkillCreator m_SkillCreator;
	//�p�����[�^����
	ActionGame::PlayerParameterCreator m_ParameterCreator;

	//������̓����蔻��T�C�Y
	CVector3 m_EscapeColliderSize;

public:
	CPlayer();
	~CPlayer() override;
	/*
	* @brief	�ǂݍ���
	* @return	true�@�Ȃ�ǂݍ��ݐ���
	*/
	bool Load();
	/*
	* @brief	������
	*/
	void Initialize();
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
	void Damage(const Vector3& direction, const Vector3& power, int damage, BYTE armorBrakeLevel);
	
	/*
	* @brief		�C���v�b�g�L�[�̐ݒ�
	* @param ptr	�C���v�b�g
	*/
	void SetInput(const ActionGame::InputPtr& ptr) noexcept
	{
		m_pInput = ptr;
	}

	/*
	* @brief		HP�̎擾
	* @return HP
	*/
	int GetHP() const noexcept
	{
		return m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	}


	/**
	* @brief		HP�ω��ʒm
	*/
	ActionGame::IObservable<int>& GetHPSubject() { return  m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP); }
	ActionGame::IObservable<int>* GetMaxHPSubject() { return &(m_MaxHP.Get()); }


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
	ActionGame::IObservable<float>* GetMaxUltSubject() { return &(m_MaxUltGauge.Get()); }
	ActionGame::IObservable<float>& GetUltSubject() { return m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE); }

	/*
	* @brief	�X�L���R���g���[���[���擾
	* @return	�X�L���R���g���[���[
	*/
	const ActionGame::SkillControllerPtr& GetSkillController() const noexcept
	{
		return m_Actor->GetSkillController();
	}
	
	/*
	* @brief	�ő�K�E�Z�Q�[�W���擾����
	* @return	�ő�K�E�Z�Q�[�W
	*/
	float GetMaxUltGauge() const noexcept
	{
		return m_MaxUltGauge.Get();
	}

	/*
	* @brief	�����Ԃ��H
	* @return	true�@�Ȃ������
	*/
	bool IsEscape() const
	{
		return m_Actor->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
	}

	/*
	* @brief	���G��Ԃ��H
	* @return	true �Ȃ疳�G���
	*/
	bool IsInvincible() const;

	/*
	* @brief	�����蔻��擾
	* @return	AABB�̓����蔻��
	*/
	const CAABB& GetCollider() override
	{
		m_Collider.Size = m_ColliderSize;
		m_Collider.SetPosition(m_Actor->GetPosition() + m_ColliderOffset);

		return m_Collider;
	}
	
	/*
	* @brief	������̓����蔻��擾
	* @return	AABB�̓����蔻��
	*/
	const CAABB& GetEscapeCollider() noexcept
	{
		m_Collider.Size = m_EscapeColliderSize;
		m_Collider.SetPosition(m_Actor->GetPosition() + m_ColliderOffset);
		return m_Collider;
	}

	/*
	* @brief	�N���A�|�[�Y���J�n����
	*/
	void ClearPose();
};

using PlayerPtr = std::shared_ptr<CPlayer>;