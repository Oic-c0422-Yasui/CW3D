#pragma once
#include "Common.h"
#include	"Singleton.h"

namespace Sample
{
	//�Ȃɂ��̌^�i�����܂Ō��܂��Ă��Ȃ��j
	template<typename T>
	class ResourceManager : public Singleton<ResourceManager<T>>
	{
		friend class Singleton<ResourceManager<T>>;
	private:
		//�V�F�A�|�C���^���g���₷���悤�ɖ��O��t����
		using ResourcePtr = std::shared_ptr<T>;
		//�����̂悤�Ȃ���
		std::unordered_map<std::string, ResourcePtr> m_Resources;

		std::unordered_map<std::string, T> m_ResourcesT;

		ResourceManager() :
			Singleton<ResourceManager<T>>(),
			m_Resources(),
			m_ResourcesT()
		{

		}
	public:

		//���\�[�X��ǉ�����
		void AddResource(const std::string& key, const ResourcePtr& ptr)
		{
			m_Resources[key] = ptr;
		}

		//���\�[�X��ǉ�����
		void AddResourceT(const std::string& key, const T& ptr)
		{
			m_ResourcesT[key] = ptr;
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

		//���\�[�X���폜����
		bool DeleteResourceT(const std::string& key)
		{
			auto it = m_ResourcesT.find(key);
			if (it != m_ResourcesT.end())
			{
				m_ResourcesT.erase(it);
				return true;
			}
			return false;
		}

		//���\�[�X���擾����
		ResourcePtr& GetResource(const std::string& key)
		{
			return m_Resources[key];
		}

		T& GetResourceT(const std::string& key)
		{
			return m_ResourcesT[key];
		}

		////�}�l�[�W���[�̃C���X�^���X���擾����
		//static ResourceManager& GetInstance()
		//{
		//	static ResourceManager instance;
		//	return instance;
		//}

	};
}
	



