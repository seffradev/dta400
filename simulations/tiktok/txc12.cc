#include <omnetpp.h>
#include <string.h>

using namespace omnetpp;

class Txc12 : public cSimpleModule {
protected:
  virtual void forwardMessage(cMessage *message);
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc12);

void Txc12::initialize() {
  if (getIndex() == 0) {
    char messageName[20];
    sprintf(messageName, "tik-%d", getIndex());
    cMessage *message = new cMessage(messageName);
    scheduleAt(0.0, message);
  }
}

void Txc12::handleMessage(cMessage *message) {
  if (getIndex() == 3) {
    EV << "Message " << message << " arrived.\n";
    delete message;
  } else {
    forwardMessage(message);
  }
}

void Txc12::forwardMessage(cMessage *message) {
  int n = gateSize("gate");
  int k = intuniform(0, n - 1);

  EV << "Forwarding message " << message << " on gate[" << k << "]\n";
  send(message, "gate$o", k);
}
