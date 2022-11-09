#pragma once
#include "Common.h"
#include	"Singleton.h"

namespace Sample
{
	//�Ȃɂ��̌^�i�����܂Ō��܂��Ă��Ȃ��j
	template<typename T>
	class ResourcePtrManager : public Singleton<ResourcePtrManager<T>>
	{
		friend class Singleton<ResourcePtrManager<T>>;
	private:
		//�V�F�A�|�C���^���g���₷���悤�ɖ��O��t����
		using ResourcePtr = std::shared_ptr<T>;

		//�����̂悤�Ȃ���
		using ResourceMap = std::unordered_map<std::string, ResourcePtr>;
		ResourceMap m_Resources;

		//�^�O�t������
		std::unordered_map<std::string,ResourceMap> m_ResourcesMap;

		ResourcePtrManager() 
			: Singleton<ResourcePtrManager<T>>()
			, m_ResourcesMap()
		{

		}
	public:

		//���\�[�X��ǉ�����
		void AddResource(const std::string& key, const ResourcePtr& resource)
		{
			m_ResourcesMap["default"][key] = resource;
		}
		//���\�[�X��ǉ����違�^�O�t��
		void AddResource(const std::string& tag, const std::string& key, const ResourcePtr& resource)
		{
			m_ResourcesMap[tag][key] = resource;
		}

		//���\�[�X���폜����
		bool DeleteResource(const std::string& key)
		{
			auto& map = m_ResourcesMap["default"];
			auto it = map.find(key);
			if (it != map.end())
			{
				map.erase(it);
				return true;
			}
			return false;
		}

		//�^�O���̃��\�[�X���폜����
		bool DeleteResouce(const std::string& tag, const std::string& key)
		{
			auto& map = m_ResourcesMap[tag];
			auto it = map.find(key);
			if (it != map.end())
			{
				map.erase(it);
				return true;
			}
			return false;
		}

		//���\�[�X���擾����
		ResourcePtr& GetResource(const std::string& key)
		{
			for (auto& map : m_ResourcesMap)
			{
				auto it = map.second.find(key);
				if (it != map.second.end())
				{
					return map.second[key];
				}
			}
			return nullptr;
		}
		//�^�O���̃��\�[�X���擾����
		const ResourcePtr& GetResource(const std::string& tag, const std::string& key)
		{
			if (IsContainTag(tag))
			{
				return m_ResourcesMap[tag][key];
			}
			return nullptr;
		}

		//���\�[�X�����݂��邩�H
		bool IsContainResource(const std::string& key)
		{
			for (auto& map : m_ResourcesMap)
			{
				auto it = map.find(key);
				if (it != map.end())
				{
					return true;
				}
			}
			return false;
		}
		//���\�[�X�����݂��邩�H
		bool IsContainResource(const std::string& tag,const std::string& key)
		{
			for (auto& map : m_ResourcesMap[tag])
			{
				auto it = map.find(key);
				if (it != map.end())
				{
					return true;
				}
			}
			return false;
		}

		//�^�O�����݂��邩�H
		bool IsContainTag(const std::string& tag)
		{
			auto it = m_ResourcesMap.find(tag);
			return it != m_ResourcesMap.end();
		}
	};

	//�Ȃɂ��̌^�i�����܂Ō��܂��Ă��Ȃ��j
	template<typename T>
	class ResourceManager : public Singleton<ResourceManager<T>>
	{
		friend class Singleton<ResourceManager<T>>;
	private:
		//�����̂悤�Ȃ���
		using ResourceMap = std::unordered_map<std::string, T>;
		ResourceMap m_Resources;

		//�^�O�t������
		std::unordered_map<std::string, ResourceMap> m_ResourcesMap;

		ResourceManager()
			: Singleton<ResourceManager<T>>()
			, m_ResourcesMap()
		{

		}
	public:
		//���\�[�X��ǉ�����
		void AddResource(const std::string& key, const T& resource)
		{
			m_ResourcesMap["default"][key] = resource;
		}
		//���\�[�X��ǉ����違�^�O�t��
		void AddResource(const std::string& tag, const std::string& key, const T& resource)
		{
			m_ResourcesMap[tag][key] = resource;
		}

		//���\�[�X���폜����
		bool DeleteResource(const std::string& key)
		{
			auto& map = m_ResourcesMap["default"];
			auto it = map.find(key);
			if (it != map.end())
			{
				map.erase(it);
				return true;
			}
			return false;
		}

		//�^�O���̃��\�[�X���폜����
		bool DeleteResouce(const std::string& tag, const std::string& key)
		{
			auto& map = m_ResourcesMap[tag];
			auto it = map.find(key);
			if (it != map.end())
			{
				map.erase(it);
				return true;
			}
			return false;
		}

		//���\�[�X���擾����
		const T& GetResource(const std::string& key)
		{
			for (auto& map : m_ResourcesMap)
			{
				auto it = map.second.find(key);
				if (it != map.second.end())
				{
					return map.second[key];
				}
			}
			return nullptr;
		}
		//���\�[�X���擾����
		const T& GetResource(const std::string& tag, const std::string& key)
		{
			if (IsContainTag(tag))
			{
				return m_ResourcesMap[tag][key];
			}
			return nullptr;
		}

		//���\�[�X�����݂��邩�H
		bool IsContainResource(const std::string& key)
		{
			for (auto& map : m_ResourcesMap)
			{
				auto it = map.second.find(key);
				if (it != map.second.end())
				{
					return true;
				}
			}
			return false;
		}

		//�^�O�����݂��邩�H
		bool IsContainTag(const std::string& tag)
		{
			auto it = m_ResourcesMap.find(tag);
			return it != m_ResourcesMap.end();
		}
	
	};
}
	



