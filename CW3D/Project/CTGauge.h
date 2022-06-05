#include	"ICTGauge.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	class CTGauge : public ICTGauge<float>
	{
	protected:
		/** HP */
		float					CT_;
		/** �ő�HP */
		float					maxCT_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CTGauge(float val)
			: CT_(0)
			, maxCT_(val) {
		}

		/**
		 * @brief		CT�ݒ�
		 */
		void Set(const float& v) override {
			if (v <= 0) { CT_ = 0; }
			else if (v >= maxCT_) { CT_ = maxCT_; }
			else { CT_ = v; }
		}

		/**
		 * @brief		CT�擾
		 */
		const float Get() const override {
			return CT_;
		}

		/**
		 * @brief		CT�����擾
		 */
		const float GetPercent() const override {
			return (CT_) / (maxCT_);
		}

		/**
		 * @brief	�ʒm���\�b�h
		 */
		void Notify(float val) override {
			Set(val);
		}
	};

}