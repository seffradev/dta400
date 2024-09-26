#include <omnetpp.h>
#include <string.h>

using namespace omnetpp;

class Txc2 : public cSimpleModule {
protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc2);

void Txc2::initialize() {
  if (strcmp("tik", getName()) == 0) {
    cMessage *message = new cMessage("tiktokMessage");
    EV << "Sending initial message\n";
    send(message, "out");
  }
}

void Txc2::handleMessage(cMessage *message) {
  EV << "Received message '" << message->getName()
     << "', sending it out again\n";
  send(message, "out");
}
