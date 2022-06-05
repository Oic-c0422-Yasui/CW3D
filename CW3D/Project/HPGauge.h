#include	"IHPGauge.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	class HPGauge : public IHPGauge<int>
	{
	protected:
		/** HP */
		int					HP_;
		/** �ő�HP */
		int					maxHP_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		HPGauge(int val)
			: HP_(val)
			, maxHP_(val) {
		}

		/**
		 * @brief		HP�ݒ�
		 */
		void Set(const int& v) override {
			if (v <= 0) { HP_ = 0; }
			else if (v >= maxHP_) { HP_ = maxHP_; }
			else { HP_ = v; }
		}

		/**
		 * @brief		HP�擾
		 */
		const int Get() const override {
			return HP_;
		}

		/**
		 * @brief		HP�����擾
		 */
		const float GetPercent() const override {
			return static_cast<float>(HP_) / static_cast<float>(maxHP_);
		}

		/**
		 * @brief	�ʒm���\�b�h
		 */
		void Notify(int val) override {
			Set(val);
		}
	};

}