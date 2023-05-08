#include "GravityUtilities.h"

void MyUtil::SetGravityScale(const ActionGame::VelocityPtr& velocity, ActionGame::GravityScale gravity)
{
	SetGravityScale(velocity,gravity,0,0);
}

void MyUtil::SetGravityScale(const ActionGame::VelocityPtr& velocity, ActionGame::GravityScale gravity, BYTE armor, BYTE armorBrake)
{
	if (!gravity.isEnable) return;
	if (armor > armorBrake) return;

	velocity->SetGravityScale(gravity.startScale, gravity.endScale, gravity.time);

}