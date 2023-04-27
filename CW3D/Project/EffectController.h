#pragma once
#include "Effect.h"

#include "Singleton.h"

namespace ActionGame 
{
	/*
	* �G�t�F�N�g����N���X
	*/
	class CEffectController : public Singleton<CEffectController>
	{
		friend class Singleton<CEffectController>;
	private:
		std::vector<EffectPtr> effectArray_;


		CEffectController()
			: Singleton<CEffectController>()
		{
		}
		~CEffectController() override;

	private:
		void Create(const Effekseer::Handle& handle, const Vector3& position, EffectCreateParameter param);
		void Create(const Effekseer::Handle& handle, const Vector3& position, const EffectCreateParameterPtr& param);
	public:

		/*
		* @brief	�G�t�F�N�g�Đ�
		* @param	key �G�t�F�N�g��
		* @param	pos	�G�t�F�N�g���W
		* @param	param	�G�t�F�N�g�쐬�p�����[�^
		*/
		EffectPtr Play(const std::string& key,const Vector3& pos, const EffectCreateParameter& param);

		/*
		* @brief	�G�t�F�N�g�Đ�
		* @param	key �G�t�F�N�g��
		* @param	pos	�G�t�F�N�g���W
		* @param	param	�G�t�F�N�g�쐬�p�����[�^
		*/
		EffectPtr Play(const std::string& key, const Vector3& pos,const EffectCreateParameterPtr& param);

		/*
		* @brief	�X�V
		*/
		void Update();
		/*
		* @brief	�G�t�F�N�g�폜
		*/
		void Delete();
		/*
		* @brief	���ׂẴG�t�F�N�g��j��
		*/
		void Reset();
		
		/*
		* @brief	�G�t�F�N�g�擾
		* @param	id �z��ԍ�
		* @return	�G�t�F�N�g
		*/
		const EffectPtr& GetEffect(size_t id)
		{
			assert(effectArray_[id]);
			return effectArray_[id];
		}

		/*
		* @brief	�G�t�F�N�g��]�ݒ�
		* @param	handle �G�t�F�N�g�n���h��
		* @param	rotate	��]�l
		*/
		void SetRotate(const Effekseer::Handle& handle, const Vector3& rotate);
		/*
		* @brief	�G�t�F�N�g���W�ݒ�
		* @param	handle �G�t�F�N�g�n���h��
		* @param	pos	���W�l
		*/
		void SetPosition(const Effekseer::Handle& handle, const Vector3& pos);
		/*
		* @brief	�G�t�F�N�g�T�C�Y�ݒ�
		* @param	handle �G�t�F�N�g�n���h��
		* @param	scale	�T�C�Y�l
		*/
		void SetScale(const Effekseer::Handle& handle, const Vector3& scale);
		/*
		* @brief	�G�t�F�N�g�F�ݒ�
		* @param	handle �G�t�F�N�g�n���h��
		* @param	color	�F
		*/
		void SetColor(const Effekseer::Handle& handle, const Vector4& color);
		/*
		* @brief	�G�t�F�N�g�ړ��ݒ�
		* @param	handle �G�t�F�N�g�n���h��
		* @param	pos	���W�l
		*/
		void AddPosition(const Effekseer::Handle& handle, const Vector3& pos);
		/*
		* @brief	�G�t�F�N�g�Đ����x�ݒ�
		* @param	handle �G�t�F�N�g�n���h��
		* @param	speed	�Đ����x
		*/
		void SetSpeed(const Effekseer::Handle& handle, float speed);
		/*
		* @brief	�G�t�F�N�g�̃C���X�^���X�����݂��Ă��邩�H
		* @param	handle �G�t�F�N�g�n���h��
		* @return	true	�Ȃ瑶��
		*/
		bool Exists(const Effekseer::Handle& handle);
		/*
		* @brief	�G�t�F�N�g���~����
		* @param	handle �G�t�F�N�g�n���h��
		*/
		void StopEffect(const Effekseer::Handle& handle);

	};
	//�ȈՃA�N�Z�X�p
	#define EffectControllerInstance 	ActionGame::CEffectController::GetInstance()
}



