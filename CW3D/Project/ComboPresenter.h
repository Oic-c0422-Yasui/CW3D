#pragma once
#include "ComboRender.h"
#include "Player.h"

namespace ActionGame
{
	/*
	* @brief	�R���{�`��N���X�ɃI�u�U�[�o�[�̒l��n��
	*/
	class CComboPresenter
	{
	public:
		/*
		* @brief	�R���{���`��ɃI�u�U�[�o�[�̒l��n��
		* @param	player �v���C���[�̃|�C���^
		* @param	view	�R���{�`��̃|�C���^
		*/
		static void Present(const PlayerPtr& player, const ComboRenderPtr& view);
	};

}
