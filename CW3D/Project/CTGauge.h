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
		/** 最大HP */
		float					maxCT_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CTGauge(float val)
			: CT_(0)
			, maxCT_(val) {
		}

		/**
		 * @brief		CT設定
		 */
		void Set(const float& v) override {
			if (v <= 0) { CT_ = 0; }
			else if (v >= maxCT_) { CT_ = maxCT_; }
			else { CT_ = v; }
		}

		/**
		 * @brief		CT取得
		 */
		const float Get() const override {
			return CT_;
		}

		/**
		 * @brief		CT割合取得
		 */
		const float GetPercent() const override {
			return (CT_) / (maxCT_);
		}

		/**
		 * @brief	通知メソッド
		 */
		void Notify(float val) override {
			Set(val);
		}
	};

}