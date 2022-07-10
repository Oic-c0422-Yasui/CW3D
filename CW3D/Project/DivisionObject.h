#pragma once
#include "Object.h"
#include "EffectController.h"

namespace Sample
{
	class CDivisionObject : public CObject
	{
	private:

		const Sample::EffectCreateParameter param = { "ClosedEffect", Vector3(0, 0.5f, -8) , Vector3(0.3f, 0.5f, 0.3f), Vector3(MOF_ToRadian(90), 0.0f, 0.0f),1.0f };
		EffectPtr m_pEffect;
	public:
		CDivisionObject(const Vector3& pos, const Vector3& size, const Vector3& offset);
		~CDivisionObject() override;
		bool Load() override;
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Release() override;

	};
	using DivisionObjectPtr = std::shared_ptr<CDivisionObject>;
}
