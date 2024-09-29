#include "tiktok17_m.h"
#include <omnetpp.h>

using namespace omnetpp;

class Txc17 : public cSimpleModule {
private:
  simsignal_t arrivalSignal;

protected:
  virtual TikTokMessage17 *generateMessage();
  virtual void forwardMessage(TikTokMessage17 *message);
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
};

Define_Module(Txc17);

void Txc17::initialize() {
  arrivalSignal = registerSignal("arrival");

  if (getIndex() == 0) {
    TikTokMessage17 *message = generateMessage();
    scheduleAt(0.0, message);
  }
}

void Txc17::handleMessage(cMessage *message) {
  TikTokMessage17 *tiktokMessage = check_and_cast<TikTokMessage17 *>(message);

  if (tiktokMessage->getDestination() == getIndex()) {
    int hopCount = tiktokMessage->getHopCount();
    emit(arrivalSignal, hopCount);

    if (hasGUI()) {
      char label[50];
      sprintf(label, "last hopCount = %d", hopCount);
      cCanvas *canvas = getParentModule()->getCanvas();
      cTextFigure *textFigure =
          check_and_cast<cTextFigure *>(canvas->getFigure("lasthopcount"));
      textFigure->setText(label);
    }

    EV << "Message " << tiktokMessage << " arrived after" << hopCount
       << " hops.\n";

    delete tiktokMessage;

    EV << "Generating another message: ";
    TikTokMessage17 *newMessage = generateMessage();
    EV << newMessage << endl;
    forwardMessage(newMessage);
  } else {
    forwardMessage(tiktokMessage);
  }
}

TikTokMessage17 *Txc17::generateMessage() {
  int source = getIndex();
  int n = getVectorSize();
  int destination = intuniform(0, n - 2);
  if (destination >= source)
    destination++;

  char messageName[20];
  sprintf(messageName, "tik-%d-to-%d", source, destination);

  TikTokMessage17 *message = new TikTokMessage17(messageName);
  message->setSource(source);
  message->setDestination(destination);
  return message;
}

void Txc17::forwardMessage(TikTokMessage17 *message) {
  message->setHopCount(message->getHopCount() + 1);

  int n = gateSize("gate");
  int k = intuniform(0, n - 1);

  EV << "Forwarding message " << message << " on gate[" << k << "]\n";
  send(message, "gate$o", k);
}
