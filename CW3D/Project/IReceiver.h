#pragma once
#include <memory>
#include <vector>
#include <any>
#include <functional>

namespace ActionGame
{
    /*
    * @brief    メッセージを受け取るクラスのインタフェース
    */
    class __declspec(novtable) IReceiver
    {
    private:

    public:
        virtual ~IReceiver() = default;
        virtual void Exection() = 0;
    };
    using ReceiverFunc = std::function<void(std::any&)>;
    using ReceiverPtr = std::shared_ptr<IReceiver>;
    using ReceiverList = std::vector<ReceiverPtr>;
}

