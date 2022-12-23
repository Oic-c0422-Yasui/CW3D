#pragma once
#include "Common.h"


namespace ActionGame
{
	/*
	* @brief	�m�b�N�o�b�N�̌�����ݒ肷��N���X�̃C���^�t�F�[�X
	*/
	class IKnockBack 
	{
	public:
		virtual Vector3 Get(const CVector3& otherPos) const = 0;
	};
	using KnockBackPtr = std::shared_ptr<IKnockBack>;
}

	



	