#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <string>

namespace Task
{
	//タスクの優先順位（数字が低いほど優先される）
	enum class PRIORITY
	{
		EVENT,		//イベントタスク
		MAIN1,		//メインタスク１
		MAIN2,		//メインタスク２
		MAIN3,		//メインタスク３
		COLLISION1,	//衝突タスク１
		COLLISION2,	//衝突タスク２
	};
	//タスク関数
	using Func = std::function<void()>;


	/*
	* @brief	タスク処理を行う
	*/
	class CTask
	{
	private:
		PRIORITY priority_;
		Func task_;
		std::string	name_;
		bool	isEnd_;
	public:
		/*
		* @param	name	タスク名
		* @param	pri		タスク優先順位（数字が低いほど優先順位が高い）
		* @param	func	タスク関数
		*/
		CTask(const std::string& name, PRIORITY pri, const Func& func);
		~CTask();

		/*
		* @brief	タスク実行
		*/
		void Execution();

		/*
		* @brief	優先順位取得
		* @return	優先順位（数字が低いほど優先順位が高い）
		*/
		PRIORITY GetPriority() const noexcept
		{
			return priority_;
		}

		/*
		* @brief	優先順位設定
		* @param	pri	優先順位（数字が低いほど優先順位が高い）
		*/
		void SetPriority(PRIORITY pri) noexcept
		{
			priority_ = pri;
		}

		/*
		* @brief	タスク名取得
		* @return	タスク名
		*/
		const std::string& GetName() const noexcept
		{
			return name_;
		}
		/*
		* @brief	タスクが終了したか？
		* @return	true　なら終了
		*/
		bool IsEnd() const noexcept
		{
			return isEnd_;
		}
		/*
		* @brief	タスクを終了する
		*/
		void End()  noexcept
		{
			isEnd_ = true;
		}

	};
	
	using TaskPtr = std::shared_ptr<CTask>;
	using TaskList = std::vector<TaskPtr>;
}


