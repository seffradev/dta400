#include <omnetpp.h>
#include <string.h>

using namespace omnetpp;

class Txc6 : public cSimpleModule {
private:
  cMessage *event = nullptr;
  cMessage *tiktokMessage = nullptr;

public:
  virtual ~Txc6();

protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc6);

Txc6::~Txc6() {
  cancelAndDelete(event);
  delete tiktokMessage;
}

void Txc6::initialize() {
  event = new cMessage("event");

  tiktokMessage = nullptr;

  if (strcmp("tik", getName()) == 0) {
    EV << "Scheduling first send to t=5.0s\n";
    tiktokMessage = new cMessage("tiktokMessage");
    scheduleAt(5.0, event);
  }
}

void Txc6::handleMessage(cMessage *message) {
  if (message == event) {
    EV << "Wait period is over, sending back message\n";
    send(tiktokMessage, "out");
    tiktokMessage = nullptr;
  } else {
    EV << "Message arrived, starting to wait 1 sec...\n";
    tiktokMessage = message;
    scheduleAt(simTime() + 1.0, event);
  }
}
