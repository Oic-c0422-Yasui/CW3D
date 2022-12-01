#pragma once

#include	<thread>
#include	<functional>

class ThreadCreator
{
private:
	std::thread m_Thread;

	using CreateFunc = std::function<bool()>;
	using CompletedFunc = std::function<void()>;
	bool m_CompleteFlg;

public:
	ThreadCreator();
	~ThreadCreator();
	
	/*
	* @brief	スレッドを作成する
	* @param	func	作成する関数（bool型）
	*/
	void Create(const CreateFunc& func);
	
	/*
	* @brief	スレッドを作成する
	* @param	createFunc		作成する関数（bool型）
	* @param	completedFunc	完了後に実行される関数（void型）
	*/
	void Create(const CreateFunc& createFunc,const CompletedFunc& completedFunc);

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

