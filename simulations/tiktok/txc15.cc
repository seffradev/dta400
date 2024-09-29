#include "tiktok15_m.h"
#include <omnetpp.h>

using namespace omnetpp;

class Txc15 : public cSimpleModule {
private:
  long numberSent;
  long numberReceived;
  cHistogram hopCountStats;
  cOutVector hopCountVector;

protected:
  virtual TikTokMessage15 *generateMessage();
  virtual void forwardMessage(TikTokMessage15 *message);
  virtual void initialize() override;
  virtual void handleMessage(cMessage *message) override;
  virtual void finish() override;
};

Define_Module(Txc15);

void Txc15::initialize() {
  numberSent = 0;
  numberReceived = 0;
  WATCH(numberSent);
  WATCH(numberReceived);

  hopCountStats.setName("hopCountStats");
  hopCountVector.setName("hopCount");

  if (getIndex() == 0) {
    TikTokMessage15 *message = generateMessage();
    numberSent++;
    scheduleAt(0.0, message);
  }
}

void Txc15::handleMessage(cMessage *message) {
  TikTokMessage15 *tiktokMessage = check_and_cast<TikTokMessage15 *>(message);

  if (tiktokMessage->getDestination() == getIndex()) {
    int hopCount = tiktokMessage->getHopCount();

    EV << "Message " << tiktokMessage << " arrived after" << hopCount
       << " hops.\n";

    numberReceived++;
    hopCountVector.record(hopCount);
    hopCountStats.collect(hopCount);

    delete tiktokMessage;

    EV << "Generating another message: ";
    TikTokMessage15 *newMessage = generateMessage();
    EV << newMessage << endl;
    forwardMessage(newMessage);
    numberSent++;
  } else {
    forwardMessage(tiktokMessage);
  }
}

TikTokMessage15 *Txc15::generateMessage() {
  int source = getIndex();
  int n = getVectorSize();
  int destination = intuniform(0, n - 2);
  if (destination >= source)
    destination++;

  char messageName[20];
  sprintf(messageName, "tik-%d-to-%d", source, destination);

  TikTokMessage15 *message = new TikTokMessage15(messageName);
  message->setSource(source);
  message->setDestination(destination);
  return message;
}

void Txc15::forwardMessage(TikTokMessage15 *message) {
  message->setHopCount(message->getHopCount() + 1);

  int n = gateSize("gate");
  int k = intuniform(0, n - 1);

  EV << "Forwarding message " << message << " on gate[" << k << "]\n";
  send(message, "gate$o", k);
}

void Txc15::finish() {
  EV << "Sent: " << numberSent << endl;
  EV << "Received: " << numberReceived << endl;
  EV << "Hop count, min: " << hopCountStats.getMin() << endl;
  EV << "Hop count, max: " << hopCountStats.getMax() << endl;
  EV << "Hop count, mean: " << hopCountStats.getMean() << endl;
  EV << "Hop count, stddev: " << hopCountStats.getStddev() << endl;

  recordScalar("#sent", numberSent);
  recordScalar("#received", numberReceived);

  hopCountStats.recordAs("hop count");
}
