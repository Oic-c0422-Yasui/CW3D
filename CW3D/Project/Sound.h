#pragma once
#include "Common.h"
#include "SoundDefine.h"

namespace MyClass
{
	using SoundBufferPtr = std::shared_ptr<CSoundBufferBase>;
	
	/*
	* @breif	サウンドデータ用の構造体
	* @param	type サウンドタイプ
	* @param	isLoop ループするか？
	*/
	struct SoundData
	{
		SOUND_TYPE type;
		bool isLoop;
	};

	/*
	* @brief	サウンドクラス
	*/
	class CSound
	{
	private:
		SoundBufferPtr buffer_;
		SoundData data_;
	public:
		CSound();
		/*
		* @brief	コンストラクタ
		* @param	buffer	読み込み済みのサウンドバッファのポインタ
		* @param	data	サウンドデータ
		*/
		CSound(SoundBufferPtr buffer,const SoundData& data);
		~CSound();
		/*
		* @brief	読み込み
		* @param	fileName	読み込むファイル名
		* @param	name	サウンド名
		* @param	type	サウンドのタイプ
		* @param	isLoop	ループするか？
		*/
		bool Load(const char* fileName, const SoundData& data);
		/*
		* @brief	読み込み
		* @param	buffer	読み込み済みのサウンドバッファのポインタ
		* @param	name	サウンド名
		* @param	type	サウンドのタイプ
		* @param	isLoop	ループするか？
		*/
		bool Load(SoundBufferPtr buffer, const SoundData& data);

		/*
		* @brief	再生
		* @return	true　なら成功
		*/
		bool Play();
		/*
		* @brief	停止
		* @return	true　なら成功
		*/
		bool Stop();
		/*
		* @brief	一時停止
		* @return	true　なら成功
		*/
		bool Pause();
		/*
		* @brief	再開
		* @return	true　なら成功
		*/
		bool Resume();

		/*
		* @brief	ループするか？
		* @return	true　ならループ
		*/
		bool IsLoop() const noexcept;
		/*
		* @brief	総時間取得
		* @return	総時間
		*/
		float GetTime() const noexcept;
		/*
		* @brief	再生時間取得
		* @return	再生時間
		*/
		float GetPlayTime() const noexcept;
		/*
		* @brief	音量取得
		* @return	音量(0.0~1.0)
		*/
		float GetVolume() const noexcept;
		/*
		* @brief	ピッチ取得
		* @return	ピッチ
		*/
		float GetPitch() const noexcept;

		/*
		* @brief	ループ設定
		* @param	isLoop　ループフラグ
		*/
		void SetLoop(bool isLoop) noexcept;
		/*
		* @brief	音量設定
		* @param	volume　音量(0.0~1.0)
		*/
		void SetVolume(float volume) noexcept;
		/*
		* @brief	ピッチ設定
		* @param	pitch　ピッチ
		*/
		void SetPitch(float pitch) noexcept;
	};

	using SoundPtr = std::shared_ptr<CSound>;
}



