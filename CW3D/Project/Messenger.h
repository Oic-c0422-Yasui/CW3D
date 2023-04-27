#pragma once
#include "IMessenger.h"
#include <map>
#include <cassert>
#include "Subject.h"

namespace Messenger
{
    using ObserveMessage = std::unordered_map<std::string, ActionGame::CSubject<void>>;
    using ObserveMessageMap = std::unordered_map<int, ObserveMessage>;

    /*
    * @brief    メッセージを送るクラス
    */
    class CMessenger : public IMessenger
    {
    private:
        ObserveMessageMap observeMap_;
    public:
        CMessenger();
        ~CMessenger() override;
        
        /*
        * @brief    メッセージを送る
        * @param    message　メッセージの種類
        */
        bool Send(GameMessageType message) override;

        /*
         * @brief    メッセージを受け取った際の処理を追加
         * @param    message　メッセージの種類
         * @param    func    処理内容の関数ポインタ
         */
        void Regist(GameMessageType type, const MessageName& name,const MessageFuncPtr& func) override;

        /*
         * @brief    メッセージを受け取った際の処理を追加
         * @param    message　メッセージの種類
         * @param    func    処理内容の関数
         */
        MessageFuncPtr Regist(GameMessageType type, const MessageName& name, const MessageFunc& func) override;
        

        /*
        * @brief    メッセージを受け取る相手を削除
        */
        bool Delete(GameMessageType type, const MessageName& name) override;

        /*
       * @brief    メッセージを受け取る相手を削除
       */
        bool Delete();
    };
}


