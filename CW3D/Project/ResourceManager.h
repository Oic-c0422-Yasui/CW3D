#pragma once
#include "Common.h"
#include	"Singleton.h"


//template<typename T>なにかの型（入れるまで決まっていない）

///////////////////////////////////////////////////////////////
///			リソース管理（ポインター）
///////////////////////////////////////////////////////////////

/*
* @brief	リソースを管理する(ポインター)
*/
template<typename T>
class ResourcePtrManager : public Singleton<ResourcePtrManager<T>>
{
	friend class Singleton<ResourcePtrManager<T>>;
private:
	//シェアポインタを使いやすいように名前を付ける
	using ResourcePtr = std::shared_ptr<T>;

	//辞書のようなもの
	using ResourceMap = std::unordered_map<std::string, ResourcePtr>;
	ResourceMap resources_;

	//タグ付き辞書
	std::unordered_map<std::string,ResourceMap> resourcesMap_;

	ResourcePtrManager() 
		: Singleton<ResourcePtrManager<T>>()
		, resourcesMap_()
	{

	}
public:

	/*
	* @brief	リソースを追加する
	* @param	key			リソースの名前
	* @param	resource	リソース
	*/
	void AddResource(const std::string& key, const ResourcePtr& resource)
	{
		resourcesMap_["default"][key] = resource;
	}

	/*
	* @brief	リソースを追加する＆タグ付け
	* @param	tag			リソースのタグ
	* @param	key			リソースの名前
	* @param	resource	リソース
	*/
	void AddResource(const std::string& tag, const std::string& key, const ResourcePtr& resource)
	{
		resourcesMap_[tag][key] = resource;
	}

	/*
	* @brief	リソースを削除する
	* @param	key			リソースの名前
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
	* @brief	タグ内のリソースを削除する
	* @param	tag			リソースのタグ
	* @param	key			リソースの名前
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
	* @brief	リソースを取得する
	* @param	key			リソースの名前
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
	* @brief	タグ内のリソースを取得する
	* @param	tag			リソースのタグ
	* @param	key			リソースの名前
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
	* @brief	リソースが存在するか？
	* @param	key			リソースの名前
	* @return	true なら存在する
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
	* @brief	タグ内のリソースが存在するか？
	* @param	tag			リソースのタグ
	* @param	key			リソースの名前
	* @return	true なら存在する
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
	* @brief	タグが存在するか？
	* @param	tag			リソースのタグ
	* @return	true なら存在する
	*/
	bool IsContainTag(const std::string& tag)
	{
		auto it = resourcesMap_.find(tag);
		return it != resourcesMap_.end();
	}
};


///////////////////////////////////////////////////////////////
///			リソース管理（通常の）
///////////////////////////////////////////////////////////////

/*
* @brief	リソースを管理する
*/
template<typename T>
class ResourceManager : public Singleton<ResourceManager<T>>
{
	friend class Singleton<ResourceManager<T>>;
private:
	//辞書のようなもの
	using ResourceMap = std::unordered_map<std::string, T>;
	ResourceMap resources_;

	//タグ付き辞書
	std::unordered_map<std::string, ResourceMap> resourcesMap_;

	ResourceManager()
		: Singleton<ResourceManager<T>>()
		, resourcesMap_()
	{

	}
public:

	/*
	* @brief	リソースを追加する
	* @param	key			リソースの名前
	* @param	resource	リソース
	*/
	void AddResource(const std::string& key, const T& resource)
	{
		resourcesMap_["default"][key] = resource;
	}

	/*
	* @brief	リソースを追加する＆タグ付け
	* @param	tag			リソースのタグ
	* @param	key			リソースの名前
	* @param	resource	リソース
	*/
	void AddResource(const std::string& tag, const std::string& key, const T& resource)
	{
		resourcesMap_[tag][key] = resource;
	}

	/*
	* @brief	リソースを削除する
	* @param	key			リソースの名前
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
	* @brief	タグ内のリソースを削除する
	* @param	tag			リソースのタグ
	* @param	key			リソースの名前
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
	* @brief	リソースを取得する
	* @param	key			リソースの名前
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
	* @brief	タグ内のリソースを取得する
	* @param	tag			リソースのタグ
	* @param	key			リソースの名前
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
	* @brief	リソースが存在するか？
	* @param	key			リソースの名前
	* @return	true なら存在する
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
	* @brief	タグが存在するか？
	* @param	tag			リソースのタグ
	* @return	true なら存在する
	*/
	bool IsContainTag(const std::string& tag)
	{
		auto it = resourcesMap_.find(tag);
		return it != resourcesMap_.end();
	}

};

	



