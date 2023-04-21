#pragma once
#include "Common.h"

namespace ActionGame
{
	//�����蔻��
	using Collider = Mof::CAABB;

	/*
	* @brief	�����蔻��p�N���X
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
		* @brief	�����蔻��擾
		*/
		Collider GetCollider() const noexcept;
		/*
		* @brief	�����蔻����W�擾
		*/
		const Vector3& GetPosition() const noexcept;
		/*
		* @brief	�����蔻��T�C�Y�擾
		*/
		const Vector3& GetSize() const noexcept;

		/*
		* @brief	�����蔻��ݒ�
		*/
		void SetCollider(const Vector3& pos, const Vector3& size) noexcept;
		/*
		* @brief	�����蔻����W�ݒ�
		*/
		void SetPosition(const Vector3& pos) noexcept;
		/*
		* @brief	�����蔻��T�C�Y�ݒ�
		*/
		void SetSize(const Vector3& size) noexcept;
	};

	using ColliderPtr = std::shared_ptr<CCollider>;
}


