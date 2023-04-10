#pragma once
#include "ComboRender.h"
#include "Player.h"

namespace ActionGame
{
	/*
	* @brief	コンボ描画クラスにオブザーバーの値を渡す
	*/
	class CComboPresenter
	{
	public:
		/*
		* @brief	コンボ数描画にオブザーバーの値を渡す
		* @param	player プレイヤーのポインタ
		* @param	view	コンボ描画のポインタ
		*/
		static void Present(const PlayerPtr& player, const ComboRenderPtr& view);
	};

}
