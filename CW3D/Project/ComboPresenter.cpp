#include "ComboPresenter.h"

void ActionGame::CComboPresenter::Present(const PlayerPtr& player, const ComboRenderPtr& view)
{
	player->GetComboSubject().Subscribe([view](uint32_t combo) { view->SetComboCount(combo); });
	player->GetComboTimeSubject().Subscribe([view](float time) { view->SetCurrentShowTime(time); });
	auto func = [view](float time) { view->SetCurrentShowTime(time); };
	view->SetComboCount(0);
	view->SetCurrentShowTime(0.0f);
	view->SetEndShowTime(COMBO_SHOW_TIME);
}
