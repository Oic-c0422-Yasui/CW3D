#pragma once
class CSceneBase
{
protected:
	bool		m_EndFlg;
	int			m_NextScene;
public:
	CSceneBase() :
		m_EndFlg(false),
		m_NextScene(0)
	{

	}
	virtual ~CSceneBase() = default;
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void RenderDebug() = 0;
	virtual void Render2D() = 0;
	virtual void Render2DDebug() = 0;
	virtual void Release() = 0;
	int GetNextScene() { return m_NextScene; }
	bool IsEnd() { return m_EndFlg; }
};

