/*
PulseTimer
Created by Terry Myers Dec 2016
V0.1

Creates a boolean that is set true for one loop of the code based on a preconfigured time.  The error created by varying loop times is automatically subtracted out.
For example, a 1000ms pulse: When PulseTimer.tick() is called 1002ms has passed since the last pulse, the pulse bit is set and 2ms is subtracted.  The next pulse will be "scheduled" to occur 998 ms later.

This allows precise timing functions to occur code that may have a variable loop time:
1. create very long timers
Create a 1000ms pulse timer.  Each pulse add 1 to an unsigned long integer thereby creating a timer with a resolution of 1 sec but a possible duration of 136years!
2. Place in front of Serial.print debug logic to prevent flooding of the serial monitor
3. Call input and output mapping functions on regular intervals
4. Call integration routines such as integrating a current/power analog input to get Wh or mAH

Use:
Initialze the timer by creating a PulseTimer class and giving it a timer preset value in ms
Place only one call PulseTimer.tick() function in your loop code.  Its expected that the call to tick() will occur only once each loop.
This class has been tested with the rollover of millis()
This class has been tested to be as accurate for timing purposes as the millis() function can be irrespective of the main loops processing time

Limitations:
You cannot create a pulse timer that is shorter than  double your loop time or the bit will be on all of the timer (Nyquist Theorem).

tips:
1. Place all PulseTimer.tick() functions at the bottom of the loop code
2. When using multiple timers to trigger code try using timers with prime number of ms to prevent overlap.
*/

#ifndef PulseTimer_H
#define PulseTimer_H

class PulseTimer {

	public:
		PulseTimer(uint32_t t) { //Class definition, set the pulse timer in ms
			TimerPRE_ = t; //Set the internal timer preset
			millisREM_ = millis(); //Capture the first millis Remember value
		};
		void tick() { //Call this function once, and only once for each loop of the code for each created class
			pulse_ = false; //Reset the pulse each time
			uint32_t millisNOW = millis(); //get the current millis()
			uint32_t elapsed = millisNOW - millisREM_; //Get the elapsed time

			if (elapsed >= TimerPRE_) { //If enough time has elapsed initate the pulse
				pulse_ = true; //Set the pulse bit true for one loop
				uint32_t error = elapsed - TimerPRE_; //Calculate the error that the timer has accumulated
				millisREM_ = millisNOW - error; //Capture the next time stamp and subtract the error
			}
		}
		bool pulse() { return pulse_; }
		uint32_t preset() { return TimerPRE_; }
		void initialize() { millisREM_ = millis(); } //Initialize the timer.  Typically not needed as the Class call does the same but provided here just in case you want to reset this

	private:
		uint32_t millisREM_; //Millis remember register
		uint32_t TimerPRE_; //Internal timer preset.  Set with the PulseTimer class call
		bool pulse_;
};

#endif