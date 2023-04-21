#pragma once
#include "Common.h"

namespace ActionGame
{
	//当たり判定
	using Collider = Mof::CAABB;

	/*
	* @brief	当たり判定用クラス
	*/
	class CCollider
	{
	private:
		Collider collider_;
		Vector3 position_;
		Vector3 size_;
	public:
		CCollider();
		CCollider(Vector3 pos,Vector3 size);
		~CCollider();

		/*
		* @brief	当たり判定取得
		*/
		Collider GetCollider() const noexcept;
		/*
		* @brief	当たり判定座標取得
		*/
		const Vector3& GetPosition() const noexcept;
		/*
		* @brief	当たり判定サイズ取得
		*/
		const Vector3& GetSize() const noexcept;

		/*
		* @brief	当たり判定設定
		*/
		void SetCollider(const Vector3& pos, const Vector3& size) noexcept;
		/*
		* @brief	当たり判定座標設定
		*/
		void SetPosition(const Vector3& pos) noexcept;
		/*
		* @brief	当たり判定サイズ設定
		*/
		void SetSize(const Vector3& size) noexcept;
	};

	using ColliderPtr = std::shared_ptr<CCollider>;
}


