#pragma once

//singleton!
class SSVLongTime_Class 
{
  private:
    SSVLongTime_Class() = default; // Make constructor private
    
    uint32_t lastMillis=0;
    uint32_t overloadCnt=0;

  public:
    static SSVLongTime_Class &getInstance(); // Accessor for singleton instance
    SSVLongTime_Class(const SSVLongTime_Class &) = delete; // no copying
    SSVLongTime_Class &operator=(const SSVLongTime_Class&) = delete;

    void process();
    uint32_t getUpTimeSec();
	uint64_t millis64();
};

extern SSVLongTime_Class &SSVLongTime;

SSVLongTime_Class &SSVLongTime = SSVLongTime.getInstance();

SSVLongTime_Class &SSVLongTime_Class::getInstance() 
{
  static SSVLongTime_Class instance;
  return instance;
}

void SSVLongTime_Class::process()
{
  uint32_t newMillis = millis();  //millis(); //for speedup of overload for testing - micros();
  if (newMillis < lastMillis) overloadCnt++;
  lastMillis = newMillis;
}

uint32_t SSVLongTime_Class::getUpTimeSec() 
{
  //max uint32_t: 0x0FFFFFFFF=4294967295 
  //for millis(): 4294967.295; //for micros():4294.967295
  //use uint32_t for speed. For millis() approx. inaccuracy is 1 sec per 150 days. For micros() approx. inaccuracy is 1 sec per 38 hours.
  const uint32_t multiplier = 4294967; 
  //for millis(): 1000;        //for micros(): 1000000;
  const uint32_t divisor = 1000;   
  process();
  return (uint32_t) (lastMillis/divisor + multiplier*overloadCnt);
}

uint64_t SSVLongTime_Class::millis64()
{
  process();
  return (uint64_t) overloadCnt << 32 | lastMillis;
}


//-----------  NOT A CLASS FUNCTION, so may be used out of class ---------
String Sec_To_Age_Str(uint32_t Sec)
{
 String age_str="";
 long days=0;
 long hours=0;
 long mins=0;
 long secs=0;
 secs = Sec; 
 mins=secs/60; //convert seconds to minutes
 hours=mins/60; //convert minutes to hours
 days=hours/24; //convert hours to days
 secs=secs-(mins*60); //subtract the coverted seconds to minutes in order to display 59 secs max 
 mins=mins-(hours*60); //subtract the coverted minutes to hours in order to display 59 minutes max
 hours=hours-(days*24); //subtract the coverted hours to days in order to display 23 hours max
 //Display results
 if (days>0) // days will displayed only if value is greater than zero
 {
   age_str += String(days) + "d ";
 }
 if (hours<10) age_str += "0" + String(hours) + "h:"; else age_str += String(hours) + "h:";
 if (mins<10)  age_str += "0" + String(mins)  + "m:"; else age_str += String(mins)  + "m:";
 if (secs<10)  age_str += "0" + String(secs)  + "s";  else age_str += String(secs)  + "s";
 return age_str;
}