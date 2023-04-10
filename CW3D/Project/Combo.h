#pragma once
#include "ICombo.h"
#include "Timer.h"
#include "CharaTypeDefine.h"
#include "ReactiveParameter.h"

namespace ActionGame
{
	/*
	* @brief	�R���{�N���X
	*/
	class CCombo : public ICombo
	{
	private:
		CReactiveParameter<uint32_t> count_;
		float resetTime_;
		CTimer timer_;
	public:
		CCombo(float resetTime);

		/*
		* @brief	������
		*/
		void Initialize();
		/*
		* @brief	�X�V
		* @param	type�@�L�����̃^�C�v
		*/
		void Update(CHARA_TYPE type);

		/*
		* @brief	�R���{���擾
		*/
		uint32_t GetCount() const noexcept override;

		/*
		* @brief	�R���{���p�����[�^�擾
		*/
		CReactiveParameter<uint32_t>& GetCountParam() noexcept;

		/*
		* @brief	�R���{���ǉ�
		*/
		void AddCount() noexcept override;
		
	};


}



