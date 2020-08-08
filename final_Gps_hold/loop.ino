void loop() 
{
  final1Out=map(channel1Output,1124,1884,1000,2000);
  final2Out=map(channel2Output,1192,1844,1000,2000);
  final3Out=map(channel3Output,1200,1856,1000,2000);
  final4Out=map(channel4Output,1076,1876,1000,2000);
  while(Serial.available())//While there are characters to come from the GPS
  {
    gps.encode(Serial.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    current_lat=gps.location.lat();
    current_lng=gps.location.lng();
    //Serial.print("latitute:");Serial.println(current_lat);
  }
  //Serial.print("mode:");Serial.println(int((channel5Output-1000)/300));
  switch (int((channel5Output-1000)/300))//covert output of the channel 5 to 0,1,2,3
    {
      case 0: //normal mode (initial state should always be front facing north)
              //compass value updated till mode changed              
              qmc.read(&x, &y, &z,&azimuth);
              compass_initial=azimuth;
              initial_lat=current_lat;
              initial_lng=current_lng;
              break;
      case 1://yaw hold mode
              //compass value update              
              qmc.read(&x, &y, &z,&azimuth);
              compass_current=azimuth;
              yaw_change=p_mag*(compass_current-compass_initial);
              final4Out+=yaw_change;  
              initial_lat=current_lat;
              initial_lng=current_lng;
              break;
     case 2:case 3: //GPS Hold Mode
              //compass value update              
              qmc.read(&x, &y, &z,&azimuth);
              compass_current=azimuth;
              yaw_change=p_mag*(compass_current-compass_initial);
              final4Out=channel4Output+yaw_change;  
              Ail_change=p_lng*(current_lng-initial_lng);
              Ele_change=p_lat*(current_lng-initial_lng);
              final1Out+=Ail_change;
              final2Out+=Ele_change;
              break;
    }
  
//  Serial.print("value1:");Serial.print(channel1Output);
//  Serial.print("value2:");Serial.print(channel2Output);
//  Serial.print("value3:");Serial.print(channel3Output);
//  Serial.print("value4:");Serial.println(channel4Output);
  channel1.writeMicroseconds(final1Out);    
  channel2.writeMicroseconds(final2Out);    
  channel3.writeMicroseconds(final3Out);    
  channel4.writeMicroseconds(final4Out);    
  
}
