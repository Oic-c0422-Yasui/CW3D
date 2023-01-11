#pragma once
#include "NormalEnemyHPRender.h"
#include "BossHPRender.h"

namespace ActionGame
{
	class NPCHPRenderManager
	{
	private:
		std::vector<NormalEnemyHPRenderPtr> m_NormalHPRender;
		std::vector<BossHPRenderPtr> m_BossHPRender;

	public:
		NPCHPRenderManager();
		~NPCHPRenderManager();
		/*
		* @brief	�ǂݍ���
		*/
		bool Load();
		/*
		* @brief	������
		*/
		void Initialize();
		/*
		* @brief	�`��
		*/
		void Render();
		/*
		* @brief	�QD�`��
		*/
		void Render2D();
		/*
		* @brief	���
		*/
		void Release();
		/*
		* @brief	���Z�b�g
		*/
		void Reset();

		/*
		* @brief	HP�o�[�̕`�揇������ւ�
		*/
		void Sort();

		/*
		* @brief	HP�o�[�̒ǉ��i�ʏ�HP�j
		*/
		void Add(const NormalEnemyHPRenderPtr& render);
		/*
		* @brief	HP�o�[�̒ǉ��i�{�XHP�j
		*/
		void Add(const BossHPRenderPtr& render);
	};

}


