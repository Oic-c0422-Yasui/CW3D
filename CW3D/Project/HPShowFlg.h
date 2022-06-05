#include	"IHPShowFlg.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	class HPShowFlg : public IHPShowFlg<bool>
	{
	protected:
		/** 位置 */
		bool				m_ShowFlg;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		HPShowFlg(bool isShow)
			: m_ShowFlg(isShow)
		{
		}

		/**
		 * @brief		表示設定
		 */
		void Set(const bool& isShow) override {
			m_ShowFlg = isShow;
		}

		/**
		 * @brief		表示取得
		 */
		const bool Get() const override {
			return m_ShowFlg;
		}


		/**
		 * @brief	通知メソッド
		 */
		void Notify(bool val) override {
			Set(val);
		}
	};

}