#pragma once

#include "Shot.h"
#include "Singleton.h"
#include "Common.h"


namespace ActionGame
{
	

	class CShotManager : public Singleton<CShotManager>
	{
		friend class Singleton<CShotManager>;
	private:
		std::vector<ShotPtr> shotArray_;

		CShotManager()
			: Singleton<CShotManager>()
			, shotArray_()
		{
		}

	public:
		/*
		* @brief	�e�𐶐�����(����)
		* @param	pos	�������W
		* @param	sphere	���̂̒e
		* @return	�������ꂽ�e
		*/
		ShotPtr Create(const Vector3& pos, const ShotSphere& sphere);
		/*
		* @brief	�e�𐶐�����(��)
		* @param	pos	�������W
		* @param	aabb	���̒e
		* @return	�������ꂽ�e
		*/
		ShotPtr Create(const Vector3& pos, const ShotAABB& aabb);
		/*
		* @brief	�e�𐶐�����(��]���l��������)
		* @param	pos	�������W
		* @param	obb	��]���l���������̒e
		* @return	�������ꂽ�e
		*/
		ShotPtr Create(const Vector3& pos, const ShotOBB& obb);

		/*
		* @brief	��\���̒e���폜����
		*/
		void Delete();

		/*
		* @brief	�e���\���ɂ���
		*/
		void Reset();

		/*
		* @brief	�X�V
		*/
		void Update();
		/*
		* @brief	�`��
		*/
		void Render();


		/*
		* @brief	�e���擾����
		* @param	id �e�̔z��ԍ�
		* @return	�e
		*/
		const ShotPtr& GetShot(size_t id) 
		{
			assert(shotArray_[id]);
			return shotArray_[id]; 
		}

		/*
		* @brief	�e�𐔂��擾����
		* @param	�e�̐�
		*/
		size_t GetShotCount()
		{
			return shotArray_.size();
		}

	};
}
//�ȈՃA�N�Z�X�p
#define ShotManagerInstance 	ActionGame::CShotManager::GetInstance()

