#pragma once
#include "Common.h"
#include "SoundDefine.h"

namespace MyClass
{
	using SoundBufferPtr = std::shared_ptr<CSoundBufferBase>;
	
	/*
	* @breif	�T�E���h�f�[�^�p�̍\����
	* @param	type �T�E���h�^�C�v
	* @param	isLoop ���[�v���邩�H
	*/
	struct SoundData
	{
		SOUND_TYPE type;
		bool isLoop;
	};

	/*
	* @brief	�T�E���h�N���X
	*/
	class CSound
	{
	private:
		SoundBufferPtr buffer_;
		SoundData data_;
	public:
		CSound();
		/*
		* @brief	�R���X�g���N�^
		* @param	buffer	�ǂݍ��ݍς݂̃T�E���h�o�b�t�@�̃|�C���^
		* @param	data	�T�E���h�f�[�^
		*/
		CSound(SoundBufferPtr buffer,const SoundData& data);
		~CSound();
		/*
		* @brief	�ǂݍ���
		* @param	fileName	�ǂݍ��ރt�@�C����
		* @param	name	�T�E���h��
		* @param	type	�T�E���h�̃^�C�v
		* @param	isLoop	���[�v���邩�H
		*/
		bool Load(const char* fileName, const SoundData& data);
		/*
		* @brief	�ǂݍ���
		* @param	buffer	�ǂݍ��ݍς݂̃T�E���h�o�b�t�@�̃|�C���^
		* @param	name	�T�E���h��
		* @param	type	�T�E���h�̃^�C�v
		* @param	isLoop	���[�v���邩�H
		*/
		bool Load(SoundBufferPtr buffer, const SoundData& data);

		/*
		* @brief	�Đ�
		* @return	true�@�Ȃ琬��
		*/
		bool Play();
		/*
		* @brief	��~
		* @return	true�@�Ȃ琬��
		*/
		bool Stop();
		/*
		* @brief	�ꎞ��~
		* @return	true�@�Ȃ琬��
		*/
		bool Pause();
		/*
		* @brief	�ĊJ
		* @return	true�@�Ȃ琬��
		*/
		bool Resume();

		/*
		* @brief	���[�v���邩�H
		* @return	true�@�Ȃ烋�[�v
		*/
		bool IsLoop() const noexcept;
		/*
		* @brief	�����Ԏ擾
		* @return	������
		*/
		float GetTime() const noexcept;
		/*
		* @brief	�Đ����Ԏ擾
		* @return	�Đ�����
		*/
		float GetPlayTime() const noexcept;
		/*
		* @brief	���ʎ擾
		* @return	����(0.0~1.0)
		*/
		float GetVolume() const noexcept;
		/*
		* @brief	�s�b�`�擾
		* @return	�s�b�`
		*/
		float GetPitch() const noexcept;

		/*
		* @brief	���[�v�ݒ�
		* @param	isLoop�@���[�v�t���O
		*/
		void SetLoop(bool isLoop) noexcept;
		/*
		* @brief	���ʐݒ�
		* @param	volume�@����(0.0~1.0)
		*/
		void SetVolume(float volume) noexcept;
		/*
		* @brief	�s�b�`�ݒ�
		* @param	pitch�@�s�b�`
		*/
		void SetPitch(float pitch) noexcept;
	};

	using SoundPtr = std::shared_ptr<CSound>;
}



