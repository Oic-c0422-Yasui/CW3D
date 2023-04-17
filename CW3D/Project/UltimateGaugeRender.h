#pragma once

#include "Common.h"


namespace ActionGame
{
	/**
	 * @brief		�K�E�Z�Q�[�WUI
	 */
	class CUltimateGaugeRender
	{
	private:

		std::shared_ptr<CTexture>			gaugeBar_;
		std::shared_ptr<CTexture>			gaugeFrame_;


		std::shared_ptr<CFont>				font_;

		float								gauge_;
		float								maxGauge_;

		Vector2								offset_;
		Vector2								size_;
		Vector2								position_;

		Vector2								strPosition_;


	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CUltimateGaugeRender();


		/**
		 * @brief		�f�X�g���N�^
		 */
		~CUltimateGaugeRender();

		/**
		 * @brief		�ǂݍ���
		 * @return		true�Ȃ琬��
		 */
		bool Load();
		/**
		 * @brief		�`��
		 */
		void Render();
		/**
		 * @brief		���
		 */
		void Release();


		void SetGauge(float gauge)
		{
			gauge_ = gauge;
		}

		void SetMaxGauge(float gauge)
		{
			maxGauge_ = gauge;
		}

	};

	using UltimateGaugeUIRenderPtr = std::shared_ptr<CUltimateGaugeRender>;
}
