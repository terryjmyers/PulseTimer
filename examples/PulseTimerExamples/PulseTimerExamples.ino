#include <PulseTimer.h>

//PulseTimer Class calls
PulseTimer t1000(1000); //Create a precise 1 second pulse
PulseTimer CurrentIntegrator(501); //create a ~500ms pulse using a close prime number that won't intersect with the other times too often
PulseTimer t100(101); //Create a ~100ms pulse using a close prime number that won't intersect with the other times too often

float HourTimer; //A register to store a timer value in fractional hours
float SecondTimer; //A register to store a timer in seconds
float mAh; //milliAmp Hour register for current integration

void setup() {
	Serial.begin(115200);
}

void loop() {

	//Call some function that reads all of the input pins and does input processing on a regular basis 
	if (t100.pulse()) {
		GetInputs();
	}

	//Perform an integration of an analogRead(), Remember to divide by the "CurrentIntegrator.preset()" to retreive the timer preset in case you ever change the value during the class call.
	if (CurrentIntegrator.pulse()) {
		//value = analogRead(somepin)
		//mAh += value / CurrentIntegrator.preset();
	}

	// Use a pulse timer to directly increment a timer used in your code
	if (t1000.pulse()) {
		HourTimer = HourTimer + 1.0 / 3600.0; //This floating point will increment in fractional hours once a second
		SecondTimer++; //This will increment in whole seconds and can be used as a VERY long timer
		Serial.println("This message will appear every 1000ms on average regardless of how long the loop time is.  This is useful to put in front of debugging serial messages to prevent Serial Monitor flooding");
	}
	//Just for display purposes for this example:
	if (SecondTimer >= 10) {
		Serial.print("SecondTimer has elapsed 10 seconds!  ");
		Serial.print("HourTimer is incrementing: ");
		Serial.println(HourTimer, 3);
		SecondTimer = 0; //Reset the timer
	}

	delay(random(5, 84)); //Delay for some random time for demonstration purposes

						  //Call the tick functions once and only once for each loop through the code
	t1000.tick();
	CurrentIntegrator.tick();
	t100.tick();
}
//=======================================
void GetInputs() {
	//Do some analogRead()'s and some digitalReads()'s
}