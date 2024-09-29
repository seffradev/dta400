#include <omnetpp.h>
#include "tiktok13_m.h"

using namespace omnetpp;

class Txc13 : public cSimpleModule {
protected:
  virtual TikTokMessage13 *generateMessage();
  virtual void forwardMessage(TikTokMessage13 *message);
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc13);

void Txc13::initialize() {
  if (getIndex() == 0) {
    TikTokMessage13 *message = generateMessage();
    scheduleAt(0.0, message);
  }
}

void Txc13::handleMessage(cMessage *message) {
  TikTokMessage13 *tiktokMessage = check_and_cast<TikTokMessage13 *>(message);

  if (tiktokMessage->getDestination() == getIndex()) {
    EV << "Message " << tiktokMessage << " arrived after"
       << tiktokMessage->getHopCount() << " hops.\n";
    bubble("ARRIVED, starting new one!");
    delete tiktokMessage;

    EV << "Generating another message: ";
    TikTokMessage13 *newMessage = generateMessage();
    EV << newMessage << endl;
    forwardMessage(newMessage);
  } else {
    forwardMessage(tiktokMessage);
  }
}

TikTokMessage13 *Txc13::generateMessage() {
  int source = getIndex();
  int n = getVectorSize();
  int destination = intuniform(0, n - 2);
  if (destination >= source)
    destination++;

  char messageName[20];
  sprintf(messageName, "tik-%d-to-%d", source, destination);

  TikTokMessage13 *message = new TikTokMessage13(messageName);
  message->setSource(source);
  message->setDestination(destination);
  return message;
}

void Txc13::forwardMessage(TikTokMessage13 *message) {
  message->setHopCount(message->getHopCount() + 1);

  int n = gateSize("gate");
  int k = intuniform(0, n - 1);

  EV << "Forwarding message " << message << " on gate[" << k << "]\n";
  send(message, "gate$o", k);
}
