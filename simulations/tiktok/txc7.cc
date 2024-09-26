#include <omnetpp.h>
#include <string.h>

using namespace omnetpp;

class Txc7 : public cSimpleModule {
private:
  cMessage *event = nullptr;
  cMessage *tiktokMessage = nullptr;

public:
  virtual ~Txc7();

protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc7);

Txc7::~Txc7() {
  cancelAndDelete(event);
  delete tiktokMessage;
}

void Txc7::initialize() {
  event = new cMessage("event");

  tiktokMessage = nullptr;

  if (strcmp("tik", getName()) == 0) {
    EV << "Scheduling first send to t=5.0s\n";
    tiktokMessage = new cMessage("tiktokMessage");
    scheduleAt(5.0, event);
  }
}

void Txc7::handleMessage(cMessage *message) {
  if (message == event) {
    EV << "Wait period is over, sending back message\n";
    send(tiktokMessage, "out");
    tiktokMessage = nullptr;
  } else if (uniform(0, 1) < 0.1) {
    EV << "\"Losing\" message\n";
    delete message;
  } else {
    simtime_t delay = par("delayTime");
    EV << "Message arrived, starting to wait " << delay << " secs...\n";
    tiktokMessage = message;
    scheduleAt(simTime() + delay, event);
  }
}
