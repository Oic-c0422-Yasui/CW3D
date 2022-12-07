#pragma once
#include	<memory>

namespace ActionGame
{

	class IScene
	{
	public:

		virtual ~IScene() = default;
		/*
		* @brief		�ǂݍ���
		*/
		virtual bool Load() = 0;
		/*
		* @brief		������
		*/
		virtual void Initialize() = 0;
		/*
		* @brief		�X�V
		*/
		virtual void Update() = 0;
		/*
		* @brief		�`��
		*/
		virtual void Render() = 0;
		/*
		* @brief		�f�o�b�O�`��
		*/
		virtual void RenderDebug() = 0;
		/*
		* @brief		�QD�`��
		*/
		virtual void Render2D() = 0;
		/*
		* @brief		�QD�f�o�b�O�`��
		*/
		virtual void Render2DDebug() = 0;
		/*
		* @brief		���
		*/
		virtual void Release() = 0;
	};

	using ScenePtr = std::shared_ptr<IScene>;

}


