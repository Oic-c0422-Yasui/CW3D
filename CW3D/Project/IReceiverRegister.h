#pragma once
#include "IReceiver.h"
#include "MessageDefine.h"

namespace ActionGame
{


    /*
    * @brief    メッセージの受取人を登録するクラスのインタフェース
    */
    class IReceiverRegister
    {
    public:
        virtual ~IReceiverRegister() = default;

        /*
        * @brief    メッセージを受け取る相手を追加
        * @param    message　メッセージの種類
        * @param    recv    メッセージの受取人
        */
        virtual void AddReceiver(GameMessageType message, ReceiverPtr recv) = 0;

        /*
        * @brief    メッセージを受け取る相手を削除
        */
        virtual void DeleteReceiver(GameMessageType message) = 0;
    };
}