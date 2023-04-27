#pragma once

#include "MessageDefine.h"
#include "Observable.h"
#include <string>
#include <functional>
#include <memory>

namespace Messenger
{
    using MessageFunc = std::function<void()>;
    using MessageFuncPtr = std::shared_ptr<ActionGame::IObserver<void>>;
    using MessageName = std::string;
    /*
    * @brief    メッセージを受け取った際の処理を登録するインタフェース
    */
    class __declspec(novtable) IRegister
    {
    public:
        virtual ~IRegister() = default;

        /*
        * @brief    メッセージを受け取った際の処理を追加
        * @param    type　メッセージの種類
        * @param    name　メッセージの名前
        * @param    func    処理内容の関数ポインタ
        */
        virtual void Regist(GameMessageType type,const MessageName& name, const MessageFuncPtr& func) = 0;
        /*
        * @brief    メッセージを受け取った際の処理を追加
        * @param    type　メッセージの種類
        * @param    name    メッセージの名前
        * @param    func    処理内容の関数
        * @return   処理内容の関数ポインタ
        */
        virtual MessageFuncPtr Regist(GameMessageType type, const MessageName& name, const MessageFunc& func) = 0;

        /*
        * @brief    メッセージを受け取った際の処理を削除
        * @param    type　   メッセージの種類
        * @param    name    メッセージの名前
        */
        virtual bool Delete(GameMessageType message, const MessageName& name) = 0;
    };
}