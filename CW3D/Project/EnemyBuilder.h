#pragma once
#include "Enemy.h"
#include "EnemyBuildParameter.h"

namespace Sample
{
	class EnemyBuilder
	{
	private:
	public:
		virtual const EnemyPtr& Create(const EnemyBuildParameter& param) = 0;
	};

	using EnemyBuilderPtr = std::shared_ptr<EnemyBuilder>;

}


