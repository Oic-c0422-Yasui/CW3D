#pragma once
#include "Common.h"
#include	"Singleton.h"


//template<typename T>�Ȃɂ��̌^�i�����܂Ō��܂��Ă��Ȃ��j

///////////////////////////////////////////////////////////////
///			���\�[�X�Ǘ��i�|�C���^�[�j
///////////////////////////////////////////////////////////////

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
	ResourceMap resources_;

	//�^�O�t������
	std::unordered_map<std::string,ResourceMap> resourcesMap_;

	ResourcePtrManager() 
		: Singleton<ResourcePtrManager<T>>()
		, resourcesMap_()
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
		resourcesMap_["default"][key] = resource;
	}

	/*
	* @brief	���\�[�X��ǉ����違�^�O�t��
	* @param	tag			���\�[�X�̃^�O
	* @param	key			���\�[�X�̖��O
	* @param	resource	���\�[�X
	*/
	void AddResource(const std::string& tag, const std::string& key, const ResourcePtr& resource)
	{
		resourcesMap_[tag][key] = resource;
	}

	/*
	* @brief	���\�[�X���폜����
	* @param	key			���\�[�X�̖��O
	*/
	bool DeleteResource(const std::string& key)
	{
		auto& map = resourcesMap_["default"];
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
		auto& map = resourcesMap_[tag];
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
		for (auto& map : resourcesMap_)
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
			return resourcesMap_[tag][key];
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
		for (auto& map : resourcesMap_)
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
		auto& map = resourcesMap_[tag];
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
		auto it = resourcesMap_.find(tag);
		return it != resourcesMap_.end();
	}
};


///////////////////////////////////////////////////////////////
///			���\�[�X�Ǘ��i�ʏ�́j
///////////////////////////////////////////////////////////////

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
	ResourceMap resources_;

	//�^�O�t������
	std::unordered_map<std::string, ResourceMap> resourcesMap_;

	ResourceManager()
		: Singleton<ResourceManager<T>>()
		, resourcesMap_()
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
		resourcesMap_["default"][key] = resource;
	}

	/*
	* @brief	���\�[�X��ǉ����違�^�O�t��
	* @param	tag			���\�[�X�̃^�O
	* @param	key			���\�[�X�̖��O
	* @param	resource	���\�[�X
	*/
	void AddResource(const std::string& tag, const std::string& key, const T& resource)
	{
		resourcesMap_[tag][key] = resource;
	}

	/*
	* @brief	���\�[�X���폜����
	* @param	key			���\�[�X�̖��O
	*/
	bool DeleteResource(const std::string& key)
	{
		auto& map = resourcesMap_["default"];
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
		auto& map = resourcesMap_[tag];
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
		for (auto& map : resourcesMap_)
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
			return resourcesMap_[tag][key];
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
		for (auto& map : resourcesMap_)
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
		auto it = resourcesMap_.find(tag);
		return it != resourcesMap_.end();
	}

};

	



