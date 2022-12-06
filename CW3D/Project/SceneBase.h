#pragma once
#include	<memory>
#include	<string>

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
	/*
	* @brief		読み込み
	*/
	virtual bool Load() = 0;
	/*
	* @brief		初期化
	*/
	virtual void Initialize() = 0;
	/*
	* @brief		更新
	*/
	virtual void Update() = 0;
	/*
	* @brief		描画
	*/
	virtual void Render() = 0;
	/*
	* @brief		デバッグ描画
	*/
	virtual void RenderDebug() = 0;
	/*
	* @brief		２D描画
	*/
	virtual void Render2D() = 0;
	/*
	* @brief		２Dデバッグ描画
	*/
	virtual void Render2DDebug() = 0;
	/*
	* @brief		解放
	*/
	virtual void Release() = 0;
	int GetNextScene() { return m_NextScene; }
	bool IsEnd() { return m_EndFlg; }
};

using ScenePtr = std::shared_ptr<CSceneBase>;

