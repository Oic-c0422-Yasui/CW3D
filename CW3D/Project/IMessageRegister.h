#pragma once

#include "MessageDefine.h"
#include <functional>

namespace Messenger
{
    /*
    * @brief    メッセージを受け取った際の処理を登録するインタフェース
    */
    class IRegister
    {
    public:
        virtual ~IRegister() = default;

        /*
        * @brief    メッセージを受け取った際の処理を追加
        * @param    message　メッセージの種類
        * @param    func    処理内容の関数
        */
        virtual void Regist(GameMessageType message, const std::function<void()>& func) = 0;

        /*
        * @brief    メッセージを受け取った際の処理を削除
        */
        virtual void Delete(GameMessageType message) = 0;
    };
}