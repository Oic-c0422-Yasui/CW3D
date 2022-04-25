#include "Test.h"
#include <unordered_map>


//�Ȃɂ��̌^�i�����܂Ō��܂��Ă��Ȃ��j
template<typename T>
class MinResourceManager {
private:

	//�V�F�A�|�C���^���g���₷���悤�ɖ��O��t����
	using ResourcePtr = std::shared_ptr<T>;
	//�����̂悤�Ȃ���
	std::unordered_map<std::string, ResourcePtr> resources;

	MinResourceManager()
		: resources()
	{
	}
public:
	//
	void AddResource(const std::string& key, const ResourcePtr& ptr)
	{
		resources[key] = ptr;
	}

	ResourcePtr& GetResource(const std::string& key)
	{
		return resources[key];
	}

	static MinResourceManager& GetInstance() {
		static MinResourceManager obj;
		return obj;
	}
};


CTest::CTest()
{
}

CTest::~CTest()
{
}

bool CTest::Load()
{
	return false;
}

void CTest::Initialize()
{
	using CTexturePtr = std::shared_ptr<CTexture>;
	CTexturePtr ap = std::make_shared<CTexture>();
	ap->Load("test.png");
	CTexturePtr bp = ap;
	CTexturePtr cp = ap;

	MinResourceManager<CTexture>::GetInstance().AddResource("gori", ap);

	MinResourceManager<CMeshContainer>::GetInstance().AddResource("gori", std::make_shared<CMeshContainer>());
	auto tex = MinResourceManager<CTexture>::GetInstance().GetResource("gori");
	auto mesh = MinResourceManager<CMeshContainer>::GetInstance().GetResource("gori");
	ap.reset();
}

void CTest::Update()
{
}

void CTest::Render()
{
}

void CTest::Release()
{
}
