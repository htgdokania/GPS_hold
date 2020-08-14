void setup() 
{
  Serial.begin(9600); //Initiially GPS starts at 9600 baud rate
  delay(250);

  //Disable GPGSV messages by. using the ublox protocol.
  uint8_t Disable_GPGSV[11] = {0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x03, 0x00, 0xFD, 0x15};
  Serial.write(Disable_GPGSV, 11);
  delay(350);   //A small delay is added to give the GPS some time to respond @ 9600bps.
  //Set the refresh rate to 5Hz by using the ublox protocol.
  uint8_t Set_to_5Hz[14] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xC8, 0x00, 0x01, 0x00, 0x01, 0x00, 0xDE, 0x6A};
  Serial.write(Set_to_5Hz, 14);
  delay(350);   //A small delay is added to give the GPS some time to respond @ 9600bps.
  //Set the baud rate to 57.6kbps by using the ublox protocol.
  uint8_t Set_to_57kbps[28] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00,
                               0x00, 0xE1, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE2, 0xE1
                              };
  Serial.write(Set_to_57kbps, 28);
  delay(200);

  Serial.begin(57600);
  delay(200);
  


  
  pinMode(4,OUTPUT); // indicator LED for GPS 
  digitalWrite(4,0 );

  //for SOftware interrupts port C
  PCICR |= (1 << PCIE1);    //enable PCMSK0 scan                                                              
  PCMSK1 |= (1 << PCINT8);  //Set pin A0 trigger an interrupt on state change.                                   
  PCMSK1 |= (1 << PCINT9);  //Set pin A1 trigger an interrupt on state change.                                              
  PCMSK1 |= (1 << PCINT10);  //Set pin A2 trigger an interrupt on state change.                                               
  PCMSK1 |= (1 << PCINT11);  //Set pin A3 trigger an interrupt on state change.                                               
  //for SOftware interrupts port B
  PCICR |= (1 << PCIE0);    //enable PCMSK0 scan
  PCMSK0 |= (1 << PCINT3);  //Set pin D11 trigger an interrupt on state change.                                                                                                          
  PCMSK0 |= (1 << PCINT4);  //Set pin D12 trigger an interrupt on state change.                                               
 
  Wire.begin();
  qmc.init();

  //Aileron
  channel1.attach(5);
  channel1.writeMicroseconds(1500);
  //Elevation
  channel2.attach(6);
  channel2.writeMicroseconds(1500);
  //Throttle 
  channel3.attach(9);
  channel3.writeMicroseconds(1000);
  //yaw 
  channel4.attach(10);
  channel4.writeMicroseconds(1500);//initial yaw value is 1500 i.e at centre
  
}
