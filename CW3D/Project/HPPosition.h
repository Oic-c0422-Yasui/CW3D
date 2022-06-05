#include	"IHPPosition.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	class HPPosition : public IHPPosition<Vector3>
	{
	protected:
		/** 位置 */
		Vector3				m_Position;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		HPPosition(Vector3 pos)
			: m_Position(pos)
		{
		}

		/**
		 * @brief		座標設定
		 */
		void Set(const Vector3& pos) override {
			m_Position = pos;
		}

		/**
		 * @brief		座標取得
		 */
		const Vector3 Get() const override {
			return m_Position;
		}


		/**
		 * @brief	通知メソッド
		 */
		void Notify(Vector3 val) override {
			Set(val);
		}
	};

}