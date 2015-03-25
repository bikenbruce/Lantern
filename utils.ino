
//=====================================
int RTC_init(){ 
  pinMode(cs,OUTPUT); // chip selec
  // start the SPI library:
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); 
  SPI.setDataMode(SPI_MODE1); // both mode 1 & 3 should work 
  //set control register 
  digitalWrite(cs, LOW);  
  SPI.transfer(0x8E);
  SPI.transfer(0x60); //60= disable Osciallator and Battery SQ wave @1hz, temp compensation, Alarms disabled
  digitalWrite(cs, HIGH);
  delay(10);
}

//=====================================
int SetTimeDate(int d, int mo, int y, int h, int mi, int s){ 
  int TimeDate [7]={s,mi,h,0,d,mo,y};
  for(int i=0; i<=6;i++){
    if(i==3) i++;
    int b= TimeDate[i]/10;
    int a= TimeDate[i]-b*10;
    if(i==2){
      if (b==2) b=B00000010;
      else if (b==1) b=B00000001;
    }	
    TimeDate[i]= a+(b<<4);
    
    digitalWrite(cs, LOW);
    SPI.transfer(i+0x80); 
    SPI.transfer(TimeDate[i]);        
    digitalWrite(cs, HIGH);
  }
}

//=====================================
String ReadTimeDate(){
  String temp;
  int TimeDate [7]; //second,minute,hour,null,day,month,year		
  for(int i=0; i<=6;i++){
    if(i==3) i++;
    digitalWrite(cs, LOW);
    SPI.transfer(i+0x00); 
    unsigned int n = SPI.transfer(0x00);
    digitalWrite(cs, HIGH);
    int a=n & B00001111;    
    if(i==2){	
      int b=(n & B00110000)>>4; //24 hour mode
      if(b==B00000010) b=20;        
      else if(b==B00000001) b=10;
      TimeDate[i]=a+b;
    }
    else if(i==4){
      int b=(n & B00110000)>>4;
      TimeDate[i]=a+b*10;
    }
    else if(i==5){
      int b=(n & B00010000)>>4;
      TimeDate[i]=a+b*10;
    }
    else if(i==6){
      int b=(n & B11110000)>>4;
      TimeDate[i]=a+b*10;
    }
    else{
      int b=(n & B01110000)>>4;
      TimeDate[i]=a+b*10;
    }
  }
  temp.concat(TimeDate[4]);
  temp.concat("/");
  temp.concat(TimeDate[5]);
  temp.concat("/");
  temp.concat(TimeDate[6]);
  temp.concat(" ") ;
  temp.concat(TimeDate[2]);
  temp.concat(":") ;
  temp.concat(TimeDate[1]);
  temp.concat(":") ;
  temp.concat(TimeDate[0]);
  return(temp);
}


int getIRKey() {
  int data[12];
  int i;

  while(pulseIn(irPin, LOW) < start_bit); //Wait for a start bit
  
  for(i = 0 ; i < 11 ; i++)
    data[i] = pulseIn(irPin, LOW); //Start measuring bits, I only want low pulses
  
  for(i = 0 ; i < 11 ; i++) //Parse them
  {	    
    if(data[i] > bin_1) //is it a 1?
      data[i] = 1;
    else if(data[i] > bin_0) //is it a 0?
      data[i] = 0;
    else
      return -1; //Flag the data as invalid; I don't know what it is! Return -1 on invalid data
  }

  int result = 0;
  for(i = 0 ; i < 11 ; i++) //Convert data bits to integer
    if(data[i] == 1) result |= (1<<i);

  return result; //Return key number
} 


 

