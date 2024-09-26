#include <omnetpp.h>
#include <string.h>

using namespace omnetpp;

class Txc4 : public cSimpleModule {
private:
  int counter;

protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc4);

void Txc4::initialize() {
  counter = par("limit");

  if (par("sendMsgOnInit").boolValue() == true) {
    EV << "Sending initial message\n";
    cMessage *message = new cMessage("tiktokMessage");
    send(message, "out");
  }
}

void Txc4::handleMessage(cMessage *message) {
  counter--;
  if (counter == 0) {
    EV << getName() << "'s counter reached zero, deleting message\n";
    delete message;
  } else {
    EV << getName() << "'s counter is " << counter
       << ", sending back message\n";
    send(message, "out");
  }
}