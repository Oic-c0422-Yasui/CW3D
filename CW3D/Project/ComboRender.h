#pragma once

#include "Common.h"
#include "Quake.h"
#include "Fade.h"

namespace ActionGame
{
	/*
	* @brief�@�R���{�`��
	*/
	class CComboRender
	{
	private:
		uint32_t comboCount_;
		uint32_t prevComboCount_;

		Vector2 position_;

		#define COMBO_MAX 999

		std::shared_ptr<CFont> font_;

		CQuake quake_;
		CFade fade_;
		bool isFade_;
		bool isShow_;
		float showTime_;
		float showEndTime_;

	public:
		CComboRender();
		~CComboRender();
		
		/*
		* @brief	�ǂݍ���
		* @return	true�@�Ȃ琬��
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
		* @brief	���
		*/
		void Release();
		/*
		* @brief	�R���{���ݒ�
		*/
		void SetComboCount(uint32_t count) noexcept;

		/*
		* @brief	�R���{�\�����Ԑݒ�
		*/
		void SetCurrentShowTime(float time) noexcept;

		void SetEndShowTime(float time) noexcept;
	};

	using ComboRenderPtr = std::shared_ptr<CComboRender>;
}


