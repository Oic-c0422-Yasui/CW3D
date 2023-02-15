#pragma once
#include "IMessenger.h"
#include    <map>
#include "IReceiver.h"

namespace ActionGame
{

    /*
    * @brief    メッセージを送るクラス
    */
    class CMessenger : public IMessenger
    {
    private:
        std::map<int, > m_ReceiverLists;
    public:
        CMessenger();
        
        /*
        * @brief    メッセージを送る
        * @param    message　メッセージの種類
        */
        void Send(GameMessageType message) override;

        /*
        * @brief    メッセージを受け取る相手を追加
        * @param    message　メッセージの種類
        * @param    recv　メッセージの受取人
        */
        void AddReceiver(GameMessageType message, ReceiverPtr recv) override
        {
            m_ReceiverLists[message].push_back(recv);
        }

        /*
        * @brief    メッセージを受け取る相手を削除
        */
        void DeleteReceiver(GameMessageType message) override
        {
            m_ReceiverLists[message].clear();
        }
    };
}


