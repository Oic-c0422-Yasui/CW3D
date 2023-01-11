#pragma once

#include "Common.h"

namespace ActionGame
{
	class EnemyHPRender
	{
	protected:
		//���݂̕`��HP
		float				m_CurrentHPPercent;
		//���݂̕`��Q�[�W
		float				m_CurrentHPGaugePercent;

		int m_HP;
		int m_MaxHP;

		bool	m_ShowFlg;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		EnemyHPRender();

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~EnemyHPRender() = default;


		/**
		 * @brief		�ǂݍ���
		 */
		virtual bool Load() = 0;
		/**
		 * @brief		������
		 */
		virtual void Initialize() = 0;
		/**
		 * @brief		���Z�b�g
		 */
		virtual void Reset() noexcept = 0;

		/**
		 * @brief		�`��
		 */
		virtual void Render() = 0;


		void SetHP(int hp)
		{
			m_HP = hp;
		}

		void SetMaxHP(int hp)
		{
			m_MaxHP = hp;
		}

		bool IsShow()
		{
			return m_ShowFlg;
		}

		void SetShow(bool isShow)
		{
			m_ShowFlg = isShow;
		}



	};

	using EnemyHPRenderPtr = std::shared_ptr<EnemyHPRender>;
}


