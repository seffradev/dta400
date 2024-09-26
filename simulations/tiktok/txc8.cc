#include <omnetpp.h>
#include <string.h>

using namespace omnetpp;

class Tik8 : public cSimpleModule {
private:
  simtime_t timeout;
  cMessage *timeoutEvent = nullptr;

public:
  virtual ~Tik8();

protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Tik8);

Tik8::~Tik8() { cancelAndDelete(timeoutEvent); }

void Tik8::initialize() {
  timeout = 1.0;
  timeoutEvent = new cMessage("timeoutEvent");

  EV << "Sending initial message\n";
  cMessage *message = new cMessage("tiktokMessage");
  send(message, "out");
  scheduleAt(simTime() + timeout, timeoutEvent);
}

void Tik8::handleMessage(cMessage *message) {
  if (message == timeoutEvent) {
    EV << "Timeout expired, resending message and restarting timer\n";
    cMessage *newMessage = new cMessage("tiktokMessage");
    send(newMessage, "out");
    scheduleAt(simTime() + timeout, timeoutEvent);
  } else {
    EV << "Timer cancelled.\n";
    cancelEvent(timeoutEvent);
    delete message;

    cMessage *newMessage = new cMessage("tiktokMessage");
    send(newMessage, "out");
    scheduleAt(simTime() + timeout, timeoutEvent);
  }
}

class Tok8 : public cSimpleModule {
protected:
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Tok8);

void Tok8::handleMessage(cMessage *message) {
  if (uniform(0, 1) < 0.1) {
    EV << "\"Losing\" message.\n";
    bubble("message lost");
    delete message;
  } else {
    EV << "Sending back same message as acknowledgement.\n";
    send(message, "out");
  }
}
