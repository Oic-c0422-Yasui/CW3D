#pragma once
#include "IScene.h"

namespace Scene
{
	/*
	* @brief	�V�[�������p�C���^�t�F�[�X
	*/
	class __declspec(novtable) ISceneCreator
	{
	public:
		virtual ~ISceneCreator() = default;
	
		/**
		 * @brief		�V�[������
		 */
		virtual ScenePtr Create() = 0;
	};
	
	/*
	* @brief	�V�[�������p�N���X
	*/
	template < class T >
	class SceneCreator : public ISceneCreator 
	{
	public:
		ScenePtr Create() { return std::make_shared<T>(); }
	};

	using SceneCreatorPtr = std::unique_ptr<ISceneCreator>;
}
