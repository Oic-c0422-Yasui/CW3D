#pragma once
namespace ActionGame {

	/**
	 * @brief		当たり判定まとめ
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