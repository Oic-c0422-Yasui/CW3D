#pragma once
#include "IStateCreator.h"
#include "json.hpp"

namespace ActionGame
{
	class JsonStateCreator : public IStateCreator
	{
	private:
		nlohmann::json data_;
	public:
		JsonStateCreator();

		/*
		* @brief	�t�@�C���ǂݍ���
		* @return	true�@�Ȃ琬��
		*/
		bool Load(const std::string& fileName);
		bool Create(const StateMachinePtr& stateMachine,
			const ActorPtr& actor,
			const Input::InputPtr& input) override;

	};
}


