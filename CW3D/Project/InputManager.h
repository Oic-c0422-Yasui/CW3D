#pragma once

#include	"Input.h"
#include	"Singleton.h"

namespace ActionGame {

	/**
	 * @brief		�C���v�b�g�}�l�[�W���[
	 */
	class InputManager : public Singleton<InputManager>
	{
		friend class Singleton<InputManager>;
	private:
		/** ���̓��X�g */
		InputList			inputList_;
		/**
		 * @brief		�R���X�g���N�^
		 */
		InputManager()
			: Singleton<InputManager>()
			, inputList_()
		{ }
	public:

		/**
		 * @brief		�V�K���͔F���̒ǉ�
		 */
		template< class T >
		std::shared_ptr<T> AddInput() {
			auto add = std::make_shared<T>();
			inputList_.push_back(add);
			return add;
		}

		/**
		 * @brief		�V�K���͔F���̒ǉ�
		 */
		template < typename T, typename... _Types >
		std::shared_ptr<T> AddInput(_Types&& ... _Args) {
			auto add = std::make_shared<T>(_Args...);
			inputList_.push_back(add);
			return add;
		}


		
		/**
		 * @brief		�X�V
		 */
		void Update()
		{
			for (auto& input : inputList_) { input->Update(); }
		}

		/**
		 * @brief		���͂̎擾
		 */
		InputPtr& GetInput(int id) { return inputList_[id]; }

	};
}
//�ȈՃA�N�Z�X�p
#define InputManagerInstance	ActionGame::InputManager::GetInstance()