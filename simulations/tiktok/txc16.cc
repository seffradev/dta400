#include "tiktok16_m.h"
#include <omnetpp.h>

using namespace omnetpp;

class Txc16 : public cSimpleModule {
private:
  simsignal_t arrivalSignal;

protected:
  virtual TikTokMessage16 *generateMessage();
  virtual void forwardMessage(TikTokMessage16 *message);
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc16);

void Txc16::initialize() {
  arrivalSignal = registerSignal("arrival");

  if (getIndex() == 0) {
    TikTokMessage16 *message = generateMessage();
    scheduleAt(0.0, message);
  }
}

void Txc16::handleMessage(cMessage *message) {
  TikTokMessage16 *tiktokMessage = check_and_cast<TikTokMessage16 *>(message);

  if (tiktokMessage->getDestination() == getIndex()) {
    int hopCount = tiktokMessage->getHopCount();
    emit(arrivalSignal, hopCount);

    EV << "Message " << tiktokMessage << " arrived after" << hopCount
       << " hops.\n";

    delete tiktokMessage;

    EV << "Generating another message: ";
    TikTokMessage16 *newMessage = generateMessage();
    EV << newMessage << endl;
    forwardMessage(newMessage);
  } else {
    forwardMessage(tiktokMessage);
  }
}

TikTokMessage16 *Txc16::generateMessage() {
  int source = getIndex();
  int n = getVectorSize();
  int destination = intuniform(0, n - 2);
  if (destination >= source)
    destination++;

  char messageName[20];
  sprintf(messageName, "tik-%d-to-%d", source, destination);

  TikTokMessage16 *message = new TikTokMessage16(messageName);
  message->setSource(source);
  message->setDestination(destination);
  return message;
}

void Txc16::forwardMessage(TikTokMessage16 *message) {
  message->setHopCount(message->getHopCount() + 1);

  int n = gateSize("gate");
  int k = intuniform(0, n - 1);

  EV << "Forwarding message " << message << " on gate[" << k << "]\n";
  send(message, "gate$o", k);
}
