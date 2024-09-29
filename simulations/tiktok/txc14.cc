#include "tiktok14_m.h"
#include <omnetpp.h>

using namespace omnetpp;

class Txc14 : public cSimpleModule {
private:
  long numberSent;
  long numberReceived;

protected:
  virtual TikTokMessage14 *generateMessage();
  virtual void forwardMessage(TikTokMessage14 *message);
  virtual void refreshDisplay() const override;

  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc14);

void Txc14::initialize() {
  numberSent = 0;
  numberReceived = 0;
  WATCH(numberSent);
  WATCH(numberReceived);

  if (getIndex() == 0) {
    TikTokMessage14 *message = generateMessage();
    numberSent++;
    scheduleAt(0.0, message);
  }
}

void Txc14::handleMessage(cMessage *message) {
  TikTokMessage14 *tiktokMessage = check_and_cast<TikTokMessage14 *>(message);

  if (tiktokMessage->getDestination() == getIndex()) {
    EV << "Message " << tiktokMessage << " arrived after"
       << tiktokMessage->getHopCount() << " hops.\n";
    numberReceived++;
    delete tiktokMessage;
    bubble("ARRIVED, starting new one!");

    EV << "Generating another message: ";
    TikTokMessage14 *newMessage = generateMessage();
    EV << newMessage << endl;
    forwardMessage(newMessage);
    numberSent++;
  } else {
    forwardMessage(tiktokMessage);
  }
}

TikTokMessage14 *Txc14::generateMessage() {
  int source = getIndex();
  int n = getVectorSize();
  int destination = intuniform(0, n - 2);
  if (destination >= source)
    destination++;

  char messageName[20];
  sprintf(messageName, "tik-%d-to-%d", source, destination);

  TikTokMessage14 *message = new TikTokMessage14(messageName);
  message->setSource(source);
  message->setDestination(destination);
  return message;
}

void Txc14::forwardMessage(TikTokMessage14 *message) {
  message->setHopCount(message->getHopCount() + 1);

  int n = gateSize("gate");
  int k = intuniform(0, n - 1);

  EV << "Forwarding message " << message << " on gate[" << k << "]\n";
  send(message, "gate$o", k);
}

void Txc14::refreshDisplay() const {
  char buffer[40];
  sprintf(buffer, "rcvd: %ld sent: %ld", numberReceived, numberSent);
  getDisplayString().setTagArg("t", 0, buffer);
}
