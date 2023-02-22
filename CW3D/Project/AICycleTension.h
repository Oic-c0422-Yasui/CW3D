#pragma once
#include "IAICycle.h"
#include	"Player.h"
#include "ServiceLocator.h"

namespace ActionGame
{
	/**
	 * @brief		�v���C���[�Ƃ̋����ŋٔ��x�Ƃ��Ď������菈��
	 */
    class AICycleTension : public IAICycle
	{
	private:
		//���̃A�N�^�[
		ActorPtr		actor_;

		//�ҋ@����
		int			currentTime_;
	public:
		/**
		 *	@brief		�R���X�g���N�^
		 */
		AICycleTension(ActorPtr actor);

		/**
		 * @brief		�X�V
		 * @return		true�Ȃ�o��
		 */
		bool Update() override;

		/**
		 * @brief		��ԃ��Z�b�g
		 */
		void Reset() override {
			currentTime_ = 0;
		}
	};
}


