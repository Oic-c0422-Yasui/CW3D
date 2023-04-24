#pragma once


	/**
 * Singleton�p�e���v���[�g
 */
	template< typename T >
	class Singleton
	{
	private:
		Singleton(const Singleton& obj) = delete;
		Singleton(Singleton&& obj) = delete;

		static T* instance_;

	protected:

		Singleton() { }
		virtual ~Singleton() { }

		/**
		 * �V���O���g���p�̃C���X�^���X�̐���
		 */
		static void Create()
		{

			if (instance_)
			{
				return;
			}
			instance_ = new T();
		}
	public:
		/**
		 * �V���O���g���p�̃A�N�Z�X�|�C���g�̒�`
		 * ���̊֐����ŃC���X�^���X������A�O������Q�Ƃł���
		 */
		static constexpr T& GetInstance()
		{
			if (instance_ == nullptr)
			{
				Create();
			}
			return *instance_;
		}

		/**
		 * �V���O���g���p�̃C���X�^���X�̔j��
		 */
		static void Release()
		{
			//�G���[�m�F
			assert(instance_);

			if (instance_)
			{
				delete instance_;
				instance_ = nullptr;
				return;
			}
		}
	};
	template< typename T > T* Singleton<T>::instance_ = nullptr;

