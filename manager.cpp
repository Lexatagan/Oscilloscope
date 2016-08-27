#include "manager.h"

Manager::Manager(QObject *parent) : QObject(parent)
{
  processor = new Processor;
  shiftA = 2048;
  shiftB = 2048;
  gainA = 0;
  gainB = 0;
}

void Manager::receiveRaw(ushort *raw, USBCommunicator::TDataStructure structure)
{
  uint i;
  if (structure == USBCommunicator::Single){
    for (i = 0; i < CHANNEL_SAMPLE_VOLUME; i++){
      *(channelABuffer + i) = *(raw + i);
    }
  }
  else{
    processor->deserialize(raw, CHANNEL_SAMPLE_VOLUME, channelABuffer, channelBBuffer);
  }
  processor->scaleRaw(channelABuffer, CHANNEL_SAMPLE_VOLUME, channelABuffer, shiftA, gainA);
  emit scaledReady(channelABuffer, CHANNEL_SAMPLE_VOLUME, DisplayWidget::channelA);
  if (structure == USBCommunicator::Dual){
    processor->scaleRaw(channelBBuffer, CHANNEL_SAMPLE_VOLUME, channelBBuffer, shiftB, gainB);
    emit scaledReady(channelBBuffer, CHANNEL_SAMPLE_VOLUME, DisplayWidget::channelB);
  }
}

void Manager::setShift(int shift, DisplayWidget::TChannel channel)
{
  if (channel == DisplayWidget::channelA){
    shiftA = shift;
  }
  else{
    shiftB = shift;
  }
}

void Manager::setGain(int gain, DisplayWidget::TChannel channel)
{
  if (channel == DisplayWidget::channelA){
    gainA = gain;
  }
  else{
    gainB = gain;
  }
}
