/*
 * Project IntervalManagerTest
 * Description:
 * Author:
 * Date:
 */

#include <IntervalManager.h>

const int boardLed = D7; // This is the LED that is already on your device.

//---------------------------------------------------------
void setup() {
  Serial.begin(14400);
 
  pinMode(boardLed, OUTPUT);
  digitalWrite(boardLed, LOW);
}

void loop() {
  static IntervalMgr blinkTimer( 5*1000 ) ;
  static IntervalMgr panicTimer( 1*60*1000 ) ;

  if( blinkTimer.isTimeToRun() )  blinkLED( boardLed, 10) ;    //  Blinks every given interval
  if( panicTimer.isTimeToRun() )  checkForDisconnectPanic() ;  //  Keeps track of how often to call the method
}

//---------------------------------------------------------

void blinkLED( int LEDPin, int times ) {
  for( int i=0; i < times; i++) {
    if( i > 0 )
      delay( 300 );
    digitalWrite(LEDPin, HIGH);
    delay( 250 );
    digitalWrite(LEDPin, LOW);
  }
}

void checkForDisconnectPanic() {
  static IntervalMgr disconnectTimer( 3*60*1000 ) ;  // Keeps track of how long we've been in this state

  if (Particle.connected()) {
    digitalWrite(boardLed, LOW);
    disconnectTimer.markAsRun() ;  // we are connected, so reset the timer
  } else {
    digitalWrite(boardLed, HIGH);
    Serial.printlnf("[%s] Particle Cloud is not accessible", Time.timeStr().c_str() );

    if ( disconnectTimer.isTimeToRun() ) {
      blinkLED( boardLed, 12 ) ;
      Serial.printlnf("[%s] Resetting, to regain access to Particle Cloud", Time.timeStr().c_str() );
      Serial.flush() ;
      delay(100);

      // we have been disconnected for too long, so let's reset everything!
      #if Wiring_Wifi
        Wifi.off();
        delay(1000);
      #endif
      System.reset();
    }
  }
}

