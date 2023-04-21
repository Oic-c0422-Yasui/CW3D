#pragma once

#include "Common.h"

namespace ActionGame
{
	/*
	* @brief�@�R���{�`��
	*/
	class CComboRender
	{
	private:
		uint32_t comboCount_;

		Vector2 position_;

		#define COMBO_MAX 999

		std::shared_ptr<CFont> font_;
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
	};

	using ComboRenderPtr = std::shared_ptr<CComboRender>;
}


