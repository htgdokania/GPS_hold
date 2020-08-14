void loop() 
{
  tim=millis()-tim; // this will give us the the time of 1 complete cycle
  
  final1Out=channel1Output;
  final2Out=channel2Output;
  final3Out=map(channel3Output,1200,1856,1000,2000);
  final4Out=channel4Output;

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
    previous_lat=actual_lat;
    previous_lng=actual_lng;
    actual_lat=gps.location.lat();      //These actual values get updated in every 200ms i.e 5hz
    actual_lng=gps.location.lng();
    current_lat=actual_lat;
    current_lng=actual_lng;
    lat_add=0;
    lng_add=0;
  }

/* uncomment this block comment to virtually change gps update rate from 5 hz to 50 hz
  
  else{
    lat_add=(actual_lat- previous_lat)/10;
    lng_add=(actual_lng- previous_lng)/10;
    
  }
  counter=int(20/tim);
  c++;                                    // The value of c updates every tim millsec     //So basically the below if statement satisfies only in every tim*(20/tim)=20 millsec 
  if(c>=counter){       
  current_lat+=lat_add;     // these values update
  current_lng+=lng_add;     // every 20ms ==> 50hz
  c=0;
  }
*/


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
              final4Out+=yaw_change;  
              Ail_change=p_lng*(current_lng-initial_lng) + d_lng*(current_lng-initial_lng);
              Ele_change=p_lat*(current_lat-initial_lat) + d_lat*(current_lat-initial_lat);
              
              final1Out+=Ail_change;
              final2Out+=Ele_change;
              break;
    }
  channel1.writeMicroseconds(final1Out);    
  channel2.writeMicroseconds(final2Out);    
  channel3.writeMicroseconds(final3Out);    
  channel4.writeMicroseconds(final4Out);    
  
}
