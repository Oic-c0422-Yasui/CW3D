#include "ComboPresenter.h"

void ActionGame::CComboPresenter::Present(const PlayerPtr& player, const ComboRenderPtr& view)
{
	player->GetComboSubject().Subscribe([view](uint32_t combo) { view->SetComboCount(combo); });

	view->SetComboCount(0);
}
