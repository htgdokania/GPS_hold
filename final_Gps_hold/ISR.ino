

ISR(PCINT1_vect){

  //First we take the current count value in micro seconds using the micros() function
  current_count = micros();  

  ///////////////////////////////////////Channel 1
  if(PINC & B00000001 )
  {                             //pin A0 - B00000001                                         
    if(last_CH1_state == 0)
    {                                             
      last_CH1_state = 1;                                                  
      counter_1 = current_count;                                               
    }
  }
  else if(last_CH1_state == 1)
  {                                             
    last_CH1_state = 0;                                                    
    channel1Output = current_count - counter_1;                            
  }

  ///////////////////////////////////////Channel 2
  if(PINC & B00000010 )
  {                             //pin A1 - B00000010                                         
    if(last_CH2_state == 0)
    {                                             
      last_CH2_state = 1;                                                  
      counter_2 = current_count;                                               
    }
  }
  else if(last_CH2_state == 1)
  {                                             
    last_CH2_state = 0;                                                    
    channel2Output = current_count - counter_2;                            
  }  

  ///////////////////////////////////////Channel 3
  if(PINC & B00000100 )
  {                             //pin A2 - B00000100                                         
    if(last_CH3_state == 0)
    {                                             
      last_CH3_state = 1;                                                  
      counter_3 = current_count;                                               
    }
  }
  else if(last_CH3_state == 1)
  {                                             
    last_CH3_state = 0;                                                    
    channel3Output = current_count - counter_3;                            
  }

  ///////////////////////////////////////Channel 4
  if(PINC & B00001000 )
  {                             //pin A3 - B00001000                                         
    if(last_CH4_state == 0)
    {                                             
      last_CH4_state = 1;                                                  
      counter_4 = current_count;                                               
    }
  }
  else if(last_CH4_state == 1)
  {                                             
    last_CH4_state = 0;                                                    
    channel4Output = current_count - counter_4;                            
  }
}



ISR(PCINT0_vect){
 
  //First we take the current count value in micro seconds using the micros() function
  current_count = micros();  
  
  ///////////////////////////////////////Channel 5
  if(PINB & B00001000 )
  {                             //pin D11 - B00001000                                         
    if(last_CH5_state == 0)
    {                                             
      last_CH5_state = 1;                                                  
      counter_5 = current_count;                                               
    }
  }
  else if(last_CH5_state == 1)
  {                                             
    last_CH5_state = 0;                                                    
    channel5Output = current_count - counter_5;                            
  }


  ///////////////////////////////////////Channel 6
  if(PINB & B00010000 )
  {                             //pin A5 - B00010000                                         
    if(last_CH6_state == 0)
    {                                             
      last_CH6_state = 1;                                                  
      counter_6 = current_count;                                               
    }
  }
  else if(last_CH6_state == 1)
  {                                             
    last_CH6_state = 0;                                                    
    channel6Output = current_count - counter_6;                            
  }
}
