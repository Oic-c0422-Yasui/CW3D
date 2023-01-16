#include "AICycleTension.h"
#include "TimeScaleController.h"

bool ActionGame::AICycleTension::Update()
{
	//�v���C���[�擾
	const auto& player = ServiceLocator< CPlayer >::GetService();
	const auto& transform = m_Actor->GetTransform();
	//��������C���^�[�o���Z�o
	float sx = player->GetPosition().x - transform->GetPosition().x;
	float sz = player->GetPosition().z - transform->GetPosition().z;
	float d = sqrt(sx * sx + sz * sz);
	int interval = (int)((d - 30.0f) / 20.0f);
	interval = interval <= 0 ? 1 : interval;
	m_CurrentTime += 1;
	if (m_CurrentTime > interval)
	{
		m_CurrentTime -= interval;
		return true;
	}
	return false;
}
