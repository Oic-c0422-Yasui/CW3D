#pragma once
#include "IMessageRegister.h"
#include "ServiceLocator.h"

//メッセージ登録用サービス
using RegistMessageService = CServiceLocator<Messenger::IRegister>;