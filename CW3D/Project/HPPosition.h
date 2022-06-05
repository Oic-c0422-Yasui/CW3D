#include	"IHPPosition.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	class HPPosition : public IHPPosition<Vector3>
	{
	protected:
		/** �ʒu */
		Vector3				m_Position;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		HPPosition(Vector3 pos)
			: m_Position(pos)
		{
		}

		/**
		 * @brief		���W�ݒ�
		 */
		void Set(const Vector3& pos) override {
			m_Position = pos;
		}

		/**
		 * @brief		���W�擾
		 */
		const Vector3 Get() const override {
			return m_Position;
		}


		/**
		 * @brief	�ʒm���\�b�h
		 */
		void Notify(Vector3 val) override {
			Set(val);
		}
	};

}