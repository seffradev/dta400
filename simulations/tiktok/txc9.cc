#include <omnetpp.h>
#include <string.h>

using namespace omnetpp;

class Tik9 : public cSimpleModule {
private:
  simtime_t timeout;
  cMessage *timeoutEvent = nullptr;
  int sequence;
  cMessage *message = nullptr;

public:
  virtual ~Tik9();

protected:
  virtual cMessage *generateNewMessage();
  virtual void sendCopyOf(cMessage *message);
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Tik9);

Tik9::~Tik9() {
  cancelAndDelete(timeoutEvent);
  delete message;
}

void Tik9::initialize() {
  sequence = 0;
  timeout = 1.0;
  timeoutEvent = new cMessage("timeoutEvent");

  EV << "Sending initial message\n";
  message = generateNewMessage();
  sendCopyOf(message);
  scheduleAt(simTime() + timeout, timeoutEvent);
}

void Tik9::handleMessage(cMessage *incomingMessage) {
  if (message == timeoutEvent) {
    EV << "Timeout expired, resending message and restarting timer\n";
    sendCopyOf(message);
    scheduleAt(simTime() + timeout, timeoutEvent);
  } else {
    EV << "Received: " << incomingMessage->getName() << "\n";
    delete incomingMessage;

    EV << "Timer cancelled.\n";
    cancelEvent(timeoutEvent);
    delete message;

    message = generateNewMessage();
    sendCopyOf(message);
    scheduleAt(simTime() + timeout, timeoutEvent);
  }
}

cMessage *Tik9::generateNewMessage() {
  char messageName[20];
  sprintf(messageName, "tik-%d", ++sequence);
  cMessage *newMessage = new cMessage(messageName);
  return newMessage;
}

void Tik9::sendCopyOf(cMessage *messageToCopy) {
  cMessage *copy = (cMessage *)messageToCopy->dup();
  send(copy, "out");
}

class Tok9 : public cSimpleModule {
protected:
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Tok9);

void Tok9::handleMessage(cMessage *message) {
  if (uniform(0, 1) < 0.1) {
    EV << "\"Losing\" message.\n";
    bubble("message lost");
  } else {
    EV << message << " received, sending back an acknowledgement.\n";
    send(new cMessage("ack"), "out");
  }

  delete message;
}
