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
	* @brief		�ǂݍ���
	*/
	virtual bool Load() = 0;
	/*
	* @brief		������
	*/
	virtual void Initialize() = 0;
	/*
	* @brief		�X�V
	*/
	virtual void Update() = 0;
	/*
	* @brief		�`��
	*/
	virtual void Render() = 0;
	/*
	* @brief		�f�o�b�O�`��
	*/
	virtual void RenderDebug() = 0;
	/*
	* @brief		�QD�`��
	*/
	virtual void Render2D() = 0;
	/*
	* @brief		�QD�f�o�b�O�`��
	*/
	virtual void Render2DDebug() = 0;
	/*
	* @brief		���
	*/
	virtual void Release() = 0;
	int GetNextScene() { return m_NextScene; }
	bool IsEnd() { return m_EndFlg; }
};

using ScenePtr = std::shared_ptr<CSceneBase>;

