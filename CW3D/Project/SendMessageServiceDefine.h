#pragma once
#include "IMessageSender.h"
#include "ServiceLocator.h"

//メッセージ送信用サービス
using SendMessageService = CServiceLocator<Messenger::ISender>;