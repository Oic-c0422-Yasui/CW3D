#pragma once

#include "VectorDirection.h"

namespace MyUtil
{
	/*
	* @brief	目標が範囲内か判定する
	* @param	selfPos		自身の座標
	* @param	selfDir		自身の向き
	* @param	targetPos	目標の座標
	* @param	sightAngle	視野角（度数法）
	* @param	maxDistance 最大検知距離
	*/
	bool IsRange(const Vector3& selfPos, const Vector3& selfDir, const Vector3& targetPos,
					float sightAngle,float maxDistance);
	/*
	* @brief	ベクトルの２乗の長さを求める
	*/
	float LengthSquare(const Vector3& vec);

	/*
	* @brief	ベクトルの長さを求める
	*/
	float Length(const Vector3& vec);

	/*
	* @brief	ベクトルの内積を求める
	*/
	float Dot(const Vector3& vec1, const Vector3& vec2);
	/*
	* @brief	ベクトルを正規化する
	*/
	void Normalize(Vector3& outVec);

	/*
	* @brief	２点の距離を求める
	*/
	float Distance(const Vector3& vec1, const Vector3& vec2);
	/*
	* @brief	２点の距離を求める(ベクトルを２乗した値)
	* @brief	※他の距離と比較する場合は他の距離の方を２乗すること
	*/
	float DistanceSquare(const Vector3& vec1, const Vector3& vec2);
	/*
	* @brief	前方ベクトルを求める
	*/
	Vector3 ForwardVector(const Vector3& angle);

}