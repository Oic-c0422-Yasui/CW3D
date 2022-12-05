#pragma once
#include "Object.h"
#include "EffectController.h"

namespace ActionGame
{
	class CDivisionObject : public CObject
	{
	private:

		const ActionGame::EffectCreateParameter param = { "ClosedEffect", Vector3(0, 0.5f, -8) , Vector3(0.3f, 0.5f, 0.3f), Vector3(MOF_ToRadian(90), 0.0f, 0.0f),1.0f };
		EffectPtr m_pEffect;
	public:
		CDivisionObject(const Vector3& pos, const Vector3& size, const Vector3& offset);
		~CDivisionObject() override;
		bool Load();
		void Initialize() override;
		void Update();
		void Render();
		void Release();

	};
	using DivisionObjectPtr = std::shared_ptr<CDivisionObject>;
}

