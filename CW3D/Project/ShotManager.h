#pragma once

#include "Shot.h"
#include "Singleton.h"
#include "Common.h"


namespace Sample
{
	

	class CShotManager : public Singleton<CShotManager>
	{
		friend class Singleton<CShotManager>;
	private:
		std::vector<ShotPtr> m_Shots;

		CShotManager()
			: Singleton<CShotManager>()
			, m_Shots()
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
		* @brief	�e�𐶐�����(�l�p)
		* @param	pos	�������W
		* @param	aabb	�l�p�̒e
		* @return	�������ꂽ�e
		*/
		ShotPtr Create(const Vector3& pos, const ShotAABB& aabb);

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
			assert(m_Shots[id]);
			return m_Shots[id]; 
		}

		/*
		* @brief	�e�𐔂��擾����
		* @param	�e�̐�
		*/
		size_t GetShotCount()
		{
			return m_Shots.size();
		}

	};
}
//�ȈՃA�N�Z�X�p
#define ShotManagerInstance 	Sample::CShotManager::GetInstance()

