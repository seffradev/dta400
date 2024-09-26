#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc1 : public cSimpleModule {
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc1);

void Txc1::initialize() {
    if (strcmp("tik", getName()) == 0) {
        cMessage *message = new cMessage("tiktokMessage");
        send(message, "out");
    }
}

void Txc1::handleMessage(cMessage *message) {
    send(message, "out");
}
