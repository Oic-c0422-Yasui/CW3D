#pragma once
#include "Common.h"
#include	"TemplateSingleton.h"

namespace Sample
{
	//�Ȃɂ��̌^�i�����܂Ō��܂��Ă��Ȃ��j
	template<typename T>
	class ResourceManager
	{
	private:
		//�V�F�A�|�C���^���g���₷���悤�ɖ��O��t����
		using ResourcePtr = std::shared_ptr<T>;
		//�����̂悤�Ȃ���
		std::unordered_map<std::string, ResourcePtr> m_Resources;

		ResourceManager() :
			m_Resources()
		{

		}
	public:

		//���\�[�X��ǉ�����
		void AddResource(const std::string& key, const ResourcePtr& ptr)
		{
			m_Resources[key] = ptr;
		}

		//���\�[�X���폜����
		bool DeleteResource(const std::string& key)
		{
			auto it = m_Resources.find(key);
			if (it != m_Resources.end())
			{
				m_Resources.erase(it);
				return true;
			}
			return false;
		}

		//���\�[�X���擾����
		ResourcePtr& GetResource(const std::string& key)
		{
			return m_Resources[key];
		}

		//�}�l�[�W���[�̃C���X�^���X���擾����
		static ResourceManager& GetInstance()
		{
			static ResourceManager instance;
			return instance;
		}

	};
}
	



