/*!
 * @file uart.ino
 * @brief Control speech synthesis sensor via UART, and synthetise speech
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-11-6
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_SpeechSynthesis_V2
 */
#include "DFRobot_SpeechSynthesis_V2.h"
DFRobot_SpeechSynthesis_UART ss;
/*Use software serial when using UNO or NANO*/
#if ((defined ARDUINO_AVR_UNO) || (defined ARDUINO_AVR_NANO))
    #include <SoftwareSerial.h>
    SoftwareSerial Serial1(2, 3);  //RX, TX
    #define FPSerial Serial1
    
#else
    #define FPSerial Serial1
#endif

void setup(){
  //使用firebeetle-ESP32 时需要见rx,tx映射到D2,D3
  #if (defined ESP32)
     Serial1.begin(115200, SERIAL_8N1, /*rx =*/D2, /*tx =*/D3);
  #else
  Serial1.begin(115200);
  #endif
  ss.begin(Serial1);
  
  //Set voice volume to 5
  //ss.setVolume(5);
  //Set playback speed to 5
  //ss.setSpeed(5);
  //Set tone to 5
  //ss.setTone(5);
  //For English, speak word 
  //ss.setEnglishPron(ss.WORD);
}


void loop() {
  ss.speak(F("She sells seashells by the seashore"));
  ss.speak(F("Hello, I'm Speech Synthesis module"));
  ss.speak(F("a b c d e f g"));

  /*Use text control identifier*/
  //Voice volume identifier 
  //ss.speak(F("[v3]Hello [v8]world"));
  //Word Pronounce mode identifier
  //ss.speak(F("[h1]Hello [h2]world"));
}
