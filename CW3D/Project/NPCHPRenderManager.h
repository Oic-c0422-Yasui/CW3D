#pragma once
#include "NormalEnemyHPRender.h"
#include "BossHPRender.h"

namespace ActionGame
{
	/*
	* @brief	NPC�p��HP�`��Ǘ��N���X
	*/
	class CNPCHPRenderManager
	{
	private:
		std::vector<NormalEnemyHPRenderPtr> normalHPRender_;
		std::vector<BossHPRenderPtr> bossHPRender_;
		bool isShow_;
	private:
		/* �v���C�x�[�g�֐��@*/
		//UI�\��
		void VisibleUI();
		//UI��\��
		void DisableUI();

	public:
		CNPCHPRenderManager();
		~CNPCHPRenderManager();
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
		* @brief	�ʏ�HP�o�[�̕`�揇������ւ�
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

		/*
		* @brief	���b�Z�[�W��o�^����
		*/
		void RegistSendMessage();
	};

}


