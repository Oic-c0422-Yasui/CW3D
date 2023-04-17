#pragma once

#include "VectorDirection.h"

namespace MyUtil
{
	/*
	* @brief	�ڕW���͈͓������肷��
	* @param	selfPos		���g�̍��W
	* @param	selfDir		���g�̌���
	* @param	targetPos	�ڕW�̍��W
	* @param	sightAngle	����p�i�x���@�j
	* @param	maxDistance �ő匟�m����
	*/
	bool IsRange(const Vector3& selfPos, const Vector3& selfDir, const Vector3& targetPos,
					float sightAngle,float maxDistance);
	/*
	* @brief	�x�N�g���̂Q��̒��������߂�
	*/
	float LengthSquare(const Vector3& vec);

	/*
	* @brief	�x�N�g���̒��������߂�
	*/
	float Length(const Vector3& vec);

	/*
	* @brief	�x�N�g���̓��ς����߂�
	*/
	float Dot(const Vector3& vec1, const Vector3& vec2);
	/*
	* @brief	�x�N�g���𐳋K������
	*/
	void Normalize(Vector3& outVec);

	/*
	* @brief	�Q�_�̋��������߂�
	*/
	float Distance(const Vector3& vec1, const Vector3& vec2);
	/*
	* @brief	�Q�_�̋��������߂�(�x�N�g�����Q�悵���l)
	* @brief	�����̋����Ɣ�r����ꍇ�͑��̋����̕����Q�悷�邱��
	*/
	float DistanceSquare(const Vector3& vec1, const Vector3& vec2);
	/*
	* @brief	�O���x�N�g�������߂�
	*/
	Vector3 ForwardVector(const Vector3& angle);

}