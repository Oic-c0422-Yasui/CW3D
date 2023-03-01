#pragma once

#include	<thread>
#include	<functional>
#include	<atomic>

class ThreadCreator
{
private:
	std::thread thread_;

	using CreateFunc = std::function<bool()>;
	using CompletedFunc = std::function<void()>;
	std::atomic<bool> isComplete_;

public:
	ThreadCreator();
	~ThreadCreator();
	
	/*
	* @brief	�X���b�h���쐬����
	* @param	func	�쐬����֐��ibool�^�j
	*/
	void Create(const CreateFunc& func);
	
	/*
	* @brief	�X���b�h���쐬����
	* @param	createFunc		�쐬����֐��ibool�^�j
	* @param	completedFunc	������Ɏ��s�����֐��ivoid�^�j
	*/
	void Create(const CreateFunc& createFunc,const CompletedFunc& completedFunc);

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

