#include	"JsonObjectCreator.h"


using namespace Sample;


class JsonObjectCreator
{
	/**
	 * @brief		�R���X�g���N�^
	 */
	JsonObjectCreator()
	{

	}
	/**
	 * @brief		JSon�t�@�C������̐���
	 */
	static std::vector<ObjectPtr> Create(const std::string& name) {
		std::ifstream ifs(name);
		if (ifs.fail())
		{
			return std::vector<ObjectPtr>();
		}
		nlohmann::json os = nlohmann::json::parse(ifs);
		return Create(os);
	}
	/**
	 * @brief		����
	 */
	static std::vector<ObjectPtr> Create(nlohmann::json& os) {
		std::vector<ObjectPtr>	Objects;
		for (auto& object : os)
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
			obj = std::make_shared<CDivisionObject>(pos, size, Vector3(0, 0, 0));
			Objects.push_back(obj);
		}
		return Objects;
	}
};

