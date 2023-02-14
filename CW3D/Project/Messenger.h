#pragma once
#include "IMessenger.h"
#include    <array>
#include "IReceiver.h"

namespace ActionGame
{

    

    class Messenger : public IMessenger
    {
    private:
        std::array<ReceiverList, MessageCount> receiverLists;
    public:
        Messenger();
        
        /*
        * @brief    メッセージを送る
        */
        void Send(GameMessageType message) override;

        /*
        * @brief    メッセージを受け取る相手を追加
        */
        void AddReceiver(GameMessageType message, ReceiverPtr recv)
        {
            receiverLists[message].push_back(recv);
        }

        /*
        * @brief    メッセージを受け取る相手を削除
        */
        void DeleteReceiver(GameMessageType message)
        {
            receiverLists[message].clear();
        }
    };
}


