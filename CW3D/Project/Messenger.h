#pragma once
#include "IMessenger.h"
#include    <map>
#include    <cassert>
#include "Subject.h"

namespace Messenger
{

    /*
    * @brief    メッセージを送るクラス
    */
    class CMessenger : public IMessenger
    {
    private:
        std::map<int, ActionGame::CSubject<void>> observeMap_;
    public:
        CMessenger();
        
        /*
        * @brief    メッセージを送る
        * @param    message　メッセージの種類
        */
        void Send(GameMessageType message) const override;

        /*
         * @brief    メッセージを受け取った際の処理を追加
         * @param    message　メッセージの種類
         * @param    func    処理内容の関数
         */
        void Regist(GameMessageType message, const std::function<void>& func) override;
        

        /*
        * @brief    メッセージを受け取る相手を削除
        */
        void Delete(GameMessageType message) override;
    };
}


