#pragma once

#include "ActorObject.h"
#include "Singleton.h"



namespace ActionGame
{

	/*
	* �A�N�^�[���Ǘ�����N���X
	*/
	class CActorObjectManager : public Singleton<CActorObjectManager>
	{
		friend class Singleton<CActorObjectManager>;
	private:

		using ActorMap = std::unordered_map<uint32_t, ActorObjectWeakPtr>;
		using ActorMapPtr = std::shared_ptr<ActorMap>;
		
		using TagMap = std::unordered_map<CHARA_TYPE, ActorMapPtr>;

		TagMap tagMap_;

		CActorObjectManager()
			: Singleton<CActorObjectManager>()
			, tagMap_()
		{
		}
	private:
		/*
		* @brief	�^�O���̃A�N�^�[��ǉ�����
		* @param[out]	list �ǉ�����A�N�^�[�̃��X�g
		*/
		void AddActorList(CHARA_TYPE type, ActorObjectWeakListPtr& list);

	public:

		/*
		* @brief	�A�N�^�[��ǉ�����
		* @param	actor �A�N�^�[�|�C���^
		*/
		void Add(const ActorObjectPtr& actor);

		/*
		* @brief	�Q�Ƃ̐؂ꂽ�A�N�^�[���폜����
		*/
		void Delete();

		/*
		* @brief	�A�N�^�[���擾����
		* @param	id	�A�N�^�[�̌ŗLID
		*/
		ActorObjectPtr GetActor(uint32_t id);

		/*
		* @brief	�A�N�^�[���擾����
		* @param	parentType	�L�����^�C�v
		* @param	id		�A�N�^�[�̌ŗLID
		*/
		ActorObjectPtr GetActor(CHARA_TYPE type, uint32_t id) {
			return (*tagMap_[type])[id].lock();
		}

		/*
		* @brief	�^�O���̃A�N�^�[���擾����
		*/
		ActorObjectWeakListPtr GetActors(CHARA_TYPE type);



		/*
		* @brief	�G�΂��Ă���A�N�^�[���擾����i�v���C���[�Ȃ�G�ƃ{�X�A�G�Ȃ�v���C���[���擾�j
		* @return	�����F�A�N�^�[�z��|�C���^
		*			���s�Fnullptr
		*/
		ActorObjectWeakListPtr GetHostilityActors(CHARA_TYPE type);

	};
}
//�ȈՃA�N�Z�X�p
#define ActorObjectManagerInstance 	ActionGame::CActorObjectManager::GetInstance()

