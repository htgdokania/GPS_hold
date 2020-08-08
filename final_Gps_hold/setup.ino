void setup() 
{
  Serial.begin(9600);
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
  //Throttle output pin
  channel3.attach(9);
  channel3.writeMicroseconds(1000);
  //yaw output pin
  channel4.attach(10);
  channel4.writeMicroseconds(1500);//initial yaw value is 1500 i.e at centre
  
}
