#pragma once
#include "json.hpp"
#include <fstream>
#include <codecvt>

namespace ActionGame
{
	/*
	* @brief	�G�t�F�N�g�ǂݍ��ݗp�N���X
	*/
	class JsonEffectLoader
	{
	public:
		JsonEffectLoader();
		~JsonEffectLoader();
		/**
		* @brief		JSon�t�@�C������̐���
		* @return		true�@�Ȃ琬��
		*/
		bool Load(const std::string& name);
		/**
		 * @brief		����
		 */
		bool Load(nlohmann::json& os);

	};
}



