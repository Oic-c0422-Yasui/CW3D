#pragma once


#include	"json.hpp"
#include	"StageBase.h"
#include	"Division.h"
#include	"DivisionObject.h"

namespace Sample {


	class JsonDivisionCreator
	{
	private:
	public:
		/**
		 * @brief		JSonファイルからの生成
		 */
		static DivisionArrayPtr Create(const std::string& name) {
			std::ifstream ifs(name);
			if (ifs.fail())
			{
				return DivisionArrayPtr();
			}
			nlohmann::json os = nlohmann::json::parse(ifs);
			return Create(os);
		}



		/**
		 * @brief		コンストラクタ
		 */
		JsonDivisionCreator()
		{
			
		}

		/**
		 * @brief		生成
		 */
		static DivisionArrayPtr Create(nlohmann::json& os) {
			DivisionArray divArray;
			auto& divisions = os["Divisions"];
			for (auto& division : divisions)
			{
				CDivision::DIVISION_DATA data{};
				auto& enemys = division["Enemys"];
				for (auto& enemy : enemys)
				{
					EnemyPtr ene;
					CVector3 pos;
					enemy["PosX"].get_to(pos.x);
					enemy["PosY"].get_to(pos.y);
					enemy["PosZ"].get_to(pos.z);
					ene = std::make_shared<CEnemy>(pos);
					data.Enemys.push_back(ene);
				}
				data.EnemyCount = data.Enemys.size();

				auto& objects = division["Objects"];
				for (auto& object : objects)
				{
					ObjectPtr obj;
					CVector3 pos;
					CVector3 size;
					object["PosX"].get_to(pos.x);
					object["PosY"].get_to(pos.y);
					object["PosZ"].get_to(pos.z);
					object["SizeX"].get_to(size.x);
					object["SizeY"].get_to(size.y);
					object["SizeZ"].get_to(size.z);
					obj = std::make_shared<CDivisionObject>(pos, size,Vector3(0,0,0));
					data.Objects.push_back(obj);
				}
				data.ObjectCount = data.Objects.size();

				divArray.push_back(std::make_shared<CDivision>(data));
			}
			DivisionArrayPtr result = std::make_shared<DivisionArray>(divArray);
			return result;
		}
	};

}