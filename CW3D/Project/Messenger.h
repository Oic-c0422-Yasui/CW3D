#pragma once
#include "IMessenger.h"
#include    <array>

namespace ActionGame
{

    class IReceiver
    {
    private:

    public:
        virtual void Exec(std::any& value) = 0;
    };
    using ReceiverFunc = std::function<void(std::any&)>;
    using ReceiverList = std::vector<ReceiverFunc>;

    class Messenger : public IMessenger
    {
    private:
        std::array<ReceiverList, MessageCount> receiverLists;
    public:
        Messenger();

        void Send(GameMessageType message, std::any& value) override;

        void AddReceiver(GameMessageType message, ReceiverFunc recv)
        {
            receiverLists[message].push_back(recv);
        }
    };
}


