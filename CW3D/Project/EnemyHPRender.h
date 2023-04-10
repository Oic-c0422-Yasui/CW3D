#pragma once

#include "Common.h"

namespace ActionGame
{
	class CEnemyHPRender
	{
	protected:
		//���݂̕`��HP
		float				currentHPPercent_;
		//���݂̕`��Q�[�W
		float				currentHPGaugePercent_;

		int HP_;
		int maxHP_;

		bool	isShow_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CEnemyHPRender();

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~CEnemyHPRender() = default;


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


		virtual void SetHP(int hp)
		{
			HP_ = hp;
		}

		virtual void SetMaxHP(int hp)
		{
			maxHP_ = hp;
		}

		bool IsShow()
		{
			return isShow_;
		}

		void SetShow(bool isShow)
		{
			isShow_ = isShow;
		}

	};

	using EnemyHPRenderPtr = std::shared_ptr<CEnemyHPRender>;
}


