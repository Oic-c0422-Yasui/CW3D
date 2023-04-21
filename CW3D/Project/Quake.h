#pragma once
#include "Common.h"

namespace ActionGame
{
	/*
	* @brief	�h�炷��
	*/
	enum class QaukeAxis
	{
		X,
		Y,
		XY
	};

	/*
	* @brief	�U���p�����[�^
	*/
	struct QuakeParam
	{
		float power;	//�h�ꕝ
		float frequent;	//�h��Ԋu
		float time;		//�h�ꎞ��
	};
	/*
	* @brief	UI�Ȃǂ�h�炷���߂̃I�t�Z�b�g���쐬����
	*/
	class CQuake
	{
	private:
		Vector2		offset_;
		QuakeParam	param_;
		float		currentTime_;
		bool		isQuake_;
	private:
		/*
		* @brief	�U���l�����߂�
		* @param	power �h�ꕝ
		* @param	frequent �h��Ԋu
		* @param	time �h�ꎞ��
		*/
		void Quake(float power, float frequent, float time) noexcept;
	public:
		CQuake();
		~CQuake();
		/*
		* @brief	������
		* @param	power �h�ꕝ
		* @param	frequent �h��Ԋu
		* @param	time �h�ꎞ��
		*/
		void Initialize(float power, float frequent, float time);
		/*
		* @brief	�h��J�n
		*/
		void StartQuake();
		
		/*
		* @brief	�U���l��K�p����
		* @param	axis �h�炷��
		*/
		void EnableQuake(QaukeAxis axis);

		/*
		* @brief	�h����W�I�t�Z�b�g
		*/
		const Vector2& GetOffset() const noexcept;
	};
}


