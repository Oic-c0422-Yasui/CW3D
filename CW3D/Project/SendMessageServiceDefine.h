#pragma once
#include "IMessageSender.h"
#include "ServiceLocator.h"

//���b�Z�[�W���M�p�T�[�r�X
using SendMessageService = CServiceLocator<Messenger::ISender>;