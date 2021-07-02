#include "DFRobot_SpeechSynthesis_V2.h"
/*!
   @file DFRobot_SpeechSynthesis_V2.cpp
   @brief Implementation of DFRobot_SpeechSynthesis class
   @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2020-08-17
   @get from https://www.dfrobot.com
   @https://github.com/DFRobot/DFRobot_SpeechSynthesis_V2
*/

DFRobot_SpeechSynthesis::DFRobot_SpeechSynthesis(){

}

void DFRobot_SpeechSynthesis::setVolume(uint8_t voc){
  String str="[v3]";
  if(voc > 9) voc = 9;
  str[2] = 48 + voc;
  speak(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setSpeed(uint8_t speed)
{
  String str="[s5]";
  if(speed > 9) speed = 9;
  str[2] = 48 + speed;
  speak(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setTone(uint8_t tone){
  String str="[t5]";
  if(tone > 9) tone = 9;
  str[2] = 48 + tone;
  speak(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setEnglishPron(eENpron_t pron)
{
  String str;
  if(pron == ALPHABET) {
     str="[h1]";
  }else if(pron ==WORD){
     str="[h2]";
  }
  speak(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setDigitalPron(eDigitalPron_t pron){
  String str;
  if(pron == NUMBER) {
     str="[n1]";
  }else if(pron ==NUMERIC){
     str="[n2]";
  }else if(pron == AUTOJUDGED){
     str="[n0]";
  }
  speak(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setSpeechStyle(eSpeechStyle_t style){
  String str;
  if(style == CATON) {
     str="[f0]";
  }else if(style ==SMOOTH){
     str="[f1]";
  }
  speak(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::enablePINYIN(bool enable){
  String str;
  if(enable == true) {
     str="[i1]";
  }else if(enable ==false){
     str="[i0]";
  }
  speak(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setLanguage(eLanguage_t style){
  String str;
  if(style == CHINESEL) {
     str="[g1]";
  }else if(style ==ENGLISHL){
     str="[g2]";
  }else if(style == AUTOJUDGEL){
     str="[g0]";
  }
  speak(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setZeroPron(eZeroPron_t pron){
  String str;
  if(pron == ZREO) {
     str="[o0]";
  }else if(pron ==OU){
     str="[o1]";
  }
  speak(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setOnePron(eOnePron_t pron){
  String str;
  if(pron == YAO) {
     str="[y0]";
  }else if(pron ==CHONE){
     str="[y1]";
  }
  speak(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setNamePron(eNamePron_t pron){
  String str;
  if(pron == NAME) {
     str="[r1]";
  }else if(pron ==AUTOJUDGEDN){
     str="[r0]";
  }
  speak(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::enableRhythm(bool enable){
  String str;
  if(enable == true) {
     str="[z1]";
  }else if(enable ==false){
     str="[z0]";
  }
  speak(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::reset(){
  speak("[d]");
}

void DFRobot_SpeechSynthesis::speak(String word){

  uint16_t _len = word.length();
  uint8_t sendData[5] = {0xfd,(_len + 2) >> 8,(_len + 2) & 0xff,0x01,0x04};
  
  sendCommand(sendData,5);
  for(uint16_t i = 0 ;i< _len;i++){
      uint8_t utf8 = word[i];
      sendCommand(&utf8,1);
  }
}
void DFRobot_SpeechSynthesis::wait(){
	
while(readACK()!=0x41)//等待语音合成完成
  {}
  

while(1)//等待语音播放完成
  {
   delay(20);
   uint8_t check[4]={0xFD,0x00,0x01,0x21};
   sendCommand(check,4);
   delay(20);
   if(readACK() == 0x4f) break;
  } 
  /*
readACK();
readACK();
readACK();
readACK();

*/

}

void DFRobot_SpeechSynthesis::speak(const __FlashStringHelper *data) {
  uint16_t _len;
  uint8_t * _data = (uint8_t *)data;
  while(pgm_read_byte(_data+_len) !=0){
    _len++;
  }
  uint8_t sendData[5] = {0xfd,(_len + 2) >> 8,(_len + 2) & 0xff,0x01,0x04};
  sendCommand(sendData,5);
  for(uint16_t i = 0 ;i< _len;i++){
      uint8_t utf8 = pgm_read_byte(_data + i);
      sendCommand(&utf8,1);
  }
  wait();
}

void DFRobot_SpeechSynthesis::speak(const void *data)
{
  uint8_t * _data = (uint8_t *)data;
  uint16_t _len = strlen((char*)_data);
  uint8_t sendData[5] = {0xfd,(_len + 2) >> 8,(_len + 2) & 0xff,0x01,0x04};

  sendCommand(sendData,_data,_len);
  wait();
}
void DFRobot_SpeechSynthesis::stopSynthesis(){
  sendPack(STOP_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::pauseSynthesis(){
  sendPack(PAUSE_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::recoverSynthesis(){
  sendPack(RECOVER_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::sleep(){
  sendPack(ENTERSAVEELETRI);
}
void DFRobot_SpeechSynthesis::wakeup(){
  sendPack(WAKEUP);
}
void DFRobot_SpeechSynthesis::sendPack(uint8_t cmd,uint8_t* data,uint16_t len)
{
  
  uint16_t length = 0;
  uint8_t head[5] = {0};
  head[0] = 0xfd;
  switch(cmd){
    case START_SYNTHESIS:{
      length = 2 + len;
      head[1]= length >> 8;
      head[2]= length & 0xff;
      head[3]= START_SYNTHESIS;
      head[4]= 0x04;
      sendCommand(head,data,len);
   } break;
   case START_SYNTHESIS1:{
      length = 2 + len;
      head[1]= length >> 8;
      head[2]= length & 0xff;
      head[3]= START_SYNTHESIS;
      head[4]= 0x04;
      sendCommand(head,data,len);
   }
   break;
   default :{
      length = 1;
      head[1]= length >> 8;
      head[2]= length & 0xff;
      head[3]= cmd;
      sendCommand(head,4);
   }
   break;
  }
}
DFRobot_SpeechSynthesis_I2C::DFRobot_SpeechSynthesis_I2C(TwoWire *pWire, uint8_t address){
  _pWire = pWire;
  _deviceAddr = address;
}


bool DFRobot_SpeechSynthesis_I2C::begin()
{
uint8_t ack = 0;


    _pWire->begin();
    //_pWire->setClock(100000);
    uint8_t init = 0xAA;
    sendCommand(&init,1);
	
	/*
	 Serial.println("1");
    delay(50);
    speakElish("[n1]");
	Serial.println("2");
    setVolume(1); 
	Serial.println("3");
    setSpeed(5); 
	Serial.println("4");
    setTone(5);  
	Serial.println("5");
    setSoundType(FEMALE1);
	Serial.println("6");
    setEnglishPron(WORD);
	Serial.println("7");
	Serial.println("7.1");
    speak(F("She sells seashells by the seashore"));
    speak(F("Hello, I'm Speech Synthesis module"));
    speak(F("a b c d e f g"));
	*/
	return true;
}
uint8_t DFRobot_SpeechSynthesis_I2C::sendCommand(uint8_t *head,uint8_t *data,uint16_t length)
{
	 uint16_t lenTemp = 0;
  Serial.println(length);
  _pWire->beginTransmission(_deviceAddr);
  for(uint8_t i =0;i<5;i++){
     _pWire->write(head[i]);
  }
  _pWire->endTransmission();
  
  
  while(length){
     if(length > 28){
        lenTemp =28;
     } else {
        lenTemp = length;
    }

     _pWire->beginTransmission(_deviceAddr);
     for(uint8_t i =0;i<lenTemp;i++){
      _pWire->write(data[i]);
	  DBG(data[i]);
     }
     if( _pWire->endTransmission() != 0 ) {
         DBG("ERR_DATA_BUS");
         return ERR_DATA_BUS;
     }
     length -= lenTemp;
     data += lenTemp;
  }
#ifdef ENABLE_DBG
  Serial.println();
  for(uint8_t i =0;i<5;i++){
   Serial.print(head[i],HEX);
   Serial.print(" ");
  }
  for(uint8_t i =0;i<length;i++){
   Serial.print(data[i],HEX);
   Serial.print(" ");
  }
  Serial.println();
#endif
  // if( _pWire->endTransmission() != 0 ) {
      // DBG("ERR_DATA_BUS");
      // return ERR_DATA_BUS;
  // }


  return ERR_OK;
}

uint8_t DFRobot_SpeechSynthesis_I2C::sendCommand(uint8_t *data,uint8_t length)
{
  _pWire->beginTransmission(_deviceAddr);
  for(uint8_t i =0;i<length;i++){
     _pWire->write(data[i]);
     delayMicroseconds(150);
  }
  if( _pWire->endTransmission() != 0 ) {
      DBG("ERR_DATA_BUS");
      return ERR_DATA_BUS;
  }


  return ERR_OK;
}
uint8_t DFRobot_SpeechSynthesis_I2C::readACK(){

  uint8_t data = 0;
   _pWire->requestFrom(_deviceAddr, 1);
   delay(10);
  if(_pWire->available()) {
     data = _pWire->read();
    }
   return data;
}

DFRobot_SpeechSynthesis_UART::DFRobot_SpeechSynthesis_UART(){


}

bool DFRobot_SpeechSynthesis_UART::begin(Stream &s){
   _s = &s;
   if(_s == NULL){
    return false;
   } else {
   // speakElish("[n1]");
    setVolume(5); 
    setSpeed(5); 
    setTone(5);  
    //setSoundType(FEMALE1);
    setEnglishPron(WORD);
    return true;
   }
   
}
uint8_t DFRobot_SpeechSynthesis_UART::sendCommand(uint8_t *head,uint8_t *data,uint16_t length)
{
   while (_s->available()) {
     _s->read();
    }


  for(uint8_t i =0;i<5;i++){
     _s->write(head[i]);
  }
  for(uint16_t i =0;i<length;i++){
   _s->write(data[i]);
  }
#ifdef ENABLE_DBG
  Serial.println();
  for(uint8_t i =0;i<5;i++){
   Serial.print(head[i],HEX);
   Serial.print(" ");
  }
  for(uint8_t i =0;i<length;i++){
   Serial.print(data[i],HEX);
   Serial.print(" ");
  }
  Serial.println();
#endif
  return ERR_OK;
}

uint8_t DFRobot_SpeechSynthesis_UART::sendCommand(uint8_t *data,uint8_t length)
{
  for(uint8_t i =0;i<length;i++){
   _s->write(data[i]);
  }
  return ERR_OK;
}
uint8_t DFRobot_SpeechSynthesis_UART::readACK(){

  uint8_t data = 0;
  delay(10);
  //DBG(data,HEX);
  if(_s->available()) {
     data = _s->read();
     DBG(data,HEX);
  }
  DBG(data,HEX);
  return data;

}
