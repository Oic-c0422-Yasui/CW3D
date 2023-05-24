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
		* @brief	ファイル読み込み
		* @return	true　なら成功
		*/
		bool Load(const std::string& fileName);
		bool Create(const StateMachinePtr& stateMachine,
			const ActorPtr& actor,
			const Input::InputPtr& input) override;

	};
}


