#pragma once

#include	<thread>
#include	<functional>

class ThreadCreator
{
private:
	std::thread m_Thread;

	using CreateFunc = std::function<bool()>;
	bool m_CompleteFlg;

public:
	ThreadCreator();
	~ThreadCreator();

	void Create(const CreateFunc& func);

	/*
	* @brief	実行中か
	* @return	true　なら実行中
	*/
	bool IsLoading();

	/*
	* @brief	実行が完了したか
	* @return	true　なら完了
	*/
	bool IsComplete();

};

