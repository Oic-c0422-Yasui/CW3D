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
	* @brief	���s����
	* @return	true�@�Ȃ���s��
	*/
	bool IsLoading();

	/*
	* @brief	���s������������
	* @return	true�@�Ȃ犮��
	*/
	bool IsComplete();

};

