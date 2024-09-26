#include <omnetpp.h>
#include <string.h>

using namespace omnetpp;

class Txc11 : public cSimpleModule {
protected:
  virtual void forwardMessage(cMessage *message);
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc11);

void Txc11::initialize() {
  if (getIndex() == 0) {
    char messageName[20];
    sprintf(messageName, "tik-%d", getIndex());
    cMessage *message = new cMessage(messageName);
    scheduleAt(0.0, message);
  }
}

void Txc11::handleMessage(cMessage *message) {
  if (getIndex() == 5) {
    EV << "Message " << message << " arrived.\n";
    delete message;
  } else {
    forwardMessage(message);
  }
}

void Txc11::forwardMessage(cMessage *message) {
  int n = gateSize("out");
  int k = intuniform(0, n - 1);

  EV << "Forwarding message " << message << " on port out[" << k << "]\n";
  send(message, "out", k);
}
