#pragma once
#include "IScene.h"

namespace Scene
{
	/*
	* @brief	シーン生成用インタフェース
	*/
	class __declspec(novtable) ISceneCreator
	{
	public:
		virtual ~ISceneCreator() = default;
	
		/**
		 * @brief		シーン生成
		 */
		virtual ScenePtr Create() = 0;
	};
	
	/*
	* @brief	シーン生成用クラス
	*/
	template < class T >
	class SceneCreator : public ISceneCreator 
	{
	public:
		ScenePtr Create() { return std::make_shared<T>(); }
	};

	using SceneCreatorPtr = std::unique_ptr<ISceneCreator>;
}
