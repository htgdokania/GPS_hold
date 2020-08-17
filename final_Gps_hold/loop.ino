void loop() 
{
  final1Out=channel1Output;
  final2Out=channel2Output;
  final3Out=map(channel3Output,1200,1856,1000,2000);
  final4Out=channel4Output;
 
  
  p_val=map(channel6Output,1100,2000,0,10);
  if(p_val<0)
     p_val=0;
  d_lat=-1*1000000,d_lng=1*1000000; 
  p_lat=1*p_val*1000000,p_lng=-1*p_val*1000000;

  
  while(Serial.available())//While there are characters to come from the GPS
  {
    gps.encode(Serial.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    digitalWrite(4,stat);
    if(stat==0)
      stat=1;
    else
      stat=0;
    //save previous location point first
    previous_lat=current_lat;
    previous_lng=current_lng;
    current_lat=gps.location.lat();      //These actual values get updated in every 200ms i.e 5hz
    current_lng=gps.location.lng();

  }

   switch (int((channel5Output-1000)/300))//covert output of the channel 5 to 0,1,2,3   //Mode change using channel5
    {
      case 0: //normal mode (initial state should always be front facing north)
              //compass value updated till mode changed              
              qmc.read(&x, &y, &z,&azimuth);
              compass_initial=azimuth;  //make sure Front is facing towards north for GPS Hold feature to work
              initial_lat=current_lat;
              initial_lng=current_lng;
              break;
      case 1://yaw hold mode
              //compass value update for direction hold             
              qmc.read(&x, &y, &z,&azimuth);
              compass_current=azimuth;
              yaw_change=p_mag*(compass_current-compass_initial);
              final4Out+=yaw_change;  
              initial_lat=current_lat;
              initial_lng=current_lng;
              break;
     case 2:case 3: //GPS Hold Mode
              //compass value update  for direction hold             
              qmc.read(&x, &y, &z,&azimuth);
              compass_current=azimuth;
              yaw_change=p_mag*(compass_current-compass_initial);
              final4Out+=yaw_change;  

              
              //GPS position based calculations for Aileron and Elevation to control the left/right, front/back motion
              Ail_change=p_lng*(current_lng-initial_lng) + d_lng*(current_lng-previous_lng);
              Ele_change=p_lat*(current_lat-initial_lat) + d_lat*(current_lat-previous_lat);
              limit_val=200;
              //Limit the maximum corrections to limit_val=300, so that the bot does not tilt too much
              if(abs(Ail_change)>limit_val){
               Ail_change=limit_val*(abs(Ail_change)/Ail_change);
               }
              if(abs(Ele_change)>limit_val){
               Ele_change=limit_val*(abs(Ele_change)/Ele_change);
               }

              
              final1Out+=Ail_change;  
              final2Out+=Ele_change;
              break;
    }
  channel1.writeMicroseconds(final1Out);  //Aileron  
  channel2.writeMicroseconds(final2Out);  //Elevation  
  channel3.writeMicroseconds(final3Out);  //Throttle  
  channel4.writeMicroseconds(final4Out);  //Yaw  
  
}
