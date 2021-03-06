#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <WiFiUdp.h>

IPAddress timeServer(94, 228, 220, 14); // time-a.timefreq.bldrdoc.gov
const int timeZone = 1;     // Central European Time
WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

int output_1_state = 0;
int output_2_state = 0;
int output_3_state = 0;

#define CHANNEL1_PIN 6
#define CHANNEL2_PIN 7
#define CHANNEL3_PIN 8

int SetChannel1State(String state);

void setup() {
  // put your setup code here, to run once:
  pinMode(CHANNEL1_PIN, OUTPUT);
  digitalWrite(CHANNEL1_PIN, LOW);
  pinMode(CHANNEL2_PIN, OUTPUT);
  digitalWrite(CHANNEL2_PIN, LOW);
  pinMode(CHANNEL3_PIN, OUTPUT);
  digitalWrite(CHANNEL3_PIN, LOW);
  
  Particle.function("ch1_state", SetChannel1State);
  Particle.function("ch2_state", SetChannel2State);
  Particle.function("ch3_state", SetChannel3State);
  
  Udp.begin(localPort);
  setSyncProvider(getNtpTime);
  Particle.publish("init_complete");

  while(timeStatus() == timeNotSet) {
    Particle.process();
    delay(10);
  }

  setTime(hour(),minute(),second(),day(),month(),year());
  
  //Alarm.alarmRepeat(07,00,00, Channel1On);
  //Alarm.alarmRepeat(17,00,00, Channel1Off);
  
}

int SetChannel1State(String state) {
  if(state == "true") Channel1On();
  else Channel1Off();
  return 1;
}

int SetChannel2State(String state) {
  if(state == "true") Channel2On();
  else Channel2Off();
  return 1;
}

int SetChannel3State(String state) {
  if(state == "true") Channel3On();
  else Channel3Off();
  return 1;
}

void loop() {
  Particle.process();
  Alarm.delay(50); 
}

void Channel1On(){
  output_1_state = 1;
  Particle.publish("ch1", "on");
  digitalWrite(CHANNEL1_PIN, HIGH);  
}

void Channel1Off(){
  output_1_state = 0;
  Particle.publish("ch1", "off");
  digitalWrite(CHANNEL1_PIN, LOW);           
}

void Channel2On(){
  output_2_state = 1;
  Particle.publish("ch2", "on");
  digitalWrite(CHANNEL2_PIN, HIGH);  
}

void Channel2Off(){
  output_2_state = 0;
  Particle.publish("ch2", "off");
  digitalWrite(CHANNEL2_PIN, LOW);           
}

void Channel3On(){
  output_3_state = 1;
  Particle.publish("ch3", "on");
  digitalWrite(CHANNEL3_PIN, HIGH);  
}

void Channel3Off(){
  output_3_state = 0;
  Particle.publish("ch3", "off");
  digitalWrite(CHANNEL3_PIN, LOW);           
}


const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

