#pragma once
namespace ActionGame {

	/**
	 * @brief		�����蔻��܂Ƃ�
	 */
	class CollisionManager
	{
	public:
		template< typename T1, typename T2 >
		static bool Collision(T1& obj1, T2& obj2) {
			static_assert(false, "Collision Not Found");
			return false;
		}
	};

}