#include	"IHPShowFlg.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	class HPShowFlg : public IHPShowFlg<bool>
	{
	protected:
		/** �ʒu */
		bool				m_ShowFlg;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		HPShowFlg(bool isShow)
			: m_ShowFlg(isShow)
		{
		}

		/**
		 * @brief		�\���ݒ�
		 */
		void Set(const bool& isShow) override {
			m_ShowFlg = isShow;
		}

		/**
		 * @brief		�\���擾
		 */
		const bool Get() const override {
			return m_ShowFlg;
		}


		/**
		 * @brief	�ʒm���\�b�h
		 */
		void Notify(bool val) override {
			Set(val);
		}
	};

}