#include <omnetpp.h>
#include <string.h>

using namespace omnetpp;

class Txc3 : public cSimpleModule {
private:
  int counter;

protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc3);

void Txc3::initialize() {
  counter = 10;

  WATCH(counter);

  if (strcmp("tik", getName()) == 0) {
    cMessage *message = new cMessage("tiktokMessage");
    EV << "Sending initial message\n";
    send(message, "out");
  }
}

void Txc3::handleMessage(cMessage *message) {
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
