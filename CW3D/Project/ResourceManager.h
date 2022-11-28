#pragma once
#include "Common.h"
#include	"Singleton.h"

namespace Sample
{
	//template<typename T>�Ȃɂ��̌^�i�����܂Ō��܂��Ă��Ȃ��j

	/*
	* @brief	���\�[�X���Ǘ�����(�|�C���^�[)
	*/
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

		/*
		* @brief	���\�[�X��ǉ�����
		* @param	key			���\�[�X�̖��O
		* @param	resource	���\�[�X
		*/
		void AddResource(const std::string& key, const ResourcePtr& resource)
		{
			m_ResourcesMap["default"][key] = resource;
		}

		/*
		* @brief	���\�[�X��ǉ����違�^�O�t��
		* @param	tag			���\�[�X�̃^�O
		* @param	key			���\�[�X�̖��O
		* @param	resource	���\�[�X
		*/
		void AddResource(const std::string& tag, const std::string& key, const ResourcePtr& resource)
		{
			m_ResourcesMap[tag][key] = resource;
		}

		/*
		* @brief	���\�[�X���폜����
		* @param	key			���\�[�X�̖��O
		*/
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

		/*
		* @brief	�^�O���̃��\�[�X���폜����
		* @param	tag			���\�[�X�̃^�O
		* @param	key			���\�[�X�̖��O
		*/
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

		/*
		* @brief	���\�[�X���擾����
		* @param	key			���\�[�X�̖��O
		*/
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

		/*
		* @brief	�^�O���̃��\�[�X���擾����
		* @param	tag			���\�[�X�̃^�O
		* @param	key			���\�[�X�̖��O
		*/
		const ResourcePtr& GetResource(const std::string& tag, const std::string& key)
		{
			if (IsContainTag(tag))
			{
				return m_ResourcesMap[tag][key];
			}
			return nullptr;
		}

		/*
		* @brief	���\�[�X�����݂��邩�H
		* @param	key			���\�[�X�̖��O
		* @return	true �Ȃ瑶�݂���
		*/
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

		/*
		* @brief	�^�O���̃��\�[�X�����݂��邩�H
		* @param	tag			���\�[�X�̃^�O
		* @param	key			���\�[�X�̖��O
		* @return	true �Ȃ瑶�݂���
		*/
		bool IsContainResource(const std::string& tag,const std::string& key)
		{
			auto& map = m_ResourcesMap[tag];
			auto it = map.find(key);
			if (it != map.end())
			{
				return true;
			}
			return false;
		}

		/*
		* @brief	�^�O�����݂��邩�H
		* @param	tag			���\�[�X�̃^�O
		* @return	true �Ȃ瑶�݂���
		*/
		bool IsContainTag(const std::string& tag)
		{
			auto it = m_ResourcesMap.find(tag);
			return it != m_ResourcesMap.end();
		}
	};

	/*
	* @brief	���\�[�X���Ǘ�����
	*/
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

		/*
		* @brief	���\�[�X��ǉ�����
		* @param	key			���\�[�X�̖��O
		* @param	resource	���\�[�X
		*/
		void AddResource(const std::string& key, const T& resource)
		{
			m_ResourcesMap["default"][key] = resource;
		}

		/*
		* @brief	���\�[�X��ǉ����違�^�O�t��
		* @param	tag			���\�[�X�̃^�O
		* @param	key			���\�[�X�̖��O
		* @param	resource	���\�[�X
		*/
		void AddResource(const std::string& tag, const std::string& key, const T& resource)
		{
			m_ResourcesMap[tag][key] = resource;
		}

		/*
		* @brief	���\�[�X���폜����
		* @param	key			���\�[�X�̖��O
		*/
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

		/*
		* @brief	�^�O���̃��\�[�X���폜����
		* @param	tag			���\�[�X�̃^�O
		* @param	key			���\�[�X�̖��O
		*/
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

		/*
		* @brief	���\�[�X���擾����
		* @param	key			���\�[�X�̖��O
		*/
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

		/*
		* @brief	�^�O���̃��\�[�X���擾����
		* @param	tag			���\�[�X�̃^�O
		* @param	key			���\�[�X�̖��O
		*/
		const T& GetResource(const std::string& tag, const std::string& key)
		{
			if (IsContainTag(tag))
			{
				return m_ResourcesMap[tag][key];
			}
			return nullptr;
		}

		/*
		* @brief	���\�[�X�����݂��邩�H
		* @param	key			���\�[�X�̖��O
		* @return	true �Ȃ瑶�݂���
		*/
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

		/*
		* @brief	�^�O�����݂��邩�H
		* @param	tag			���\�[�X�̃^�O
		* @return	true �Ȃ瑶�݂���
		*/
		bool IsContainTag(const std::string& tag)
		{
			auto it = m_ResourcesMap.find(tag);
			return it != m_ResourcesMap.end();
		}
	
	};
}
	



