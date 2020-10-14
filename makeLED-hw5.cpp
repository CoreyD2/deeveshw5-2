/** Simple On-board LED flashing program - written in C++ by Derek Molloy
*    simple functional struture for the Exploring BeagleBone book
*
*    This program uses USR LED 3 and can be executed in three ways:
*         makeLED on
*         makeLED off
*         makeLED flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         makeLED status (get the trigger status)
*
* * Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   cout << endl;

   if(argc!=3){
	cout << "Usage is makeLED and one of: " << endl;
        cout << "   blink,on, off, flash or status" << endl;
	cout << " e.g. makeLED flash 0" << endl;
        return 2;
   }

   string cmd(argv[1]);
   int n = stoi(argv[2]);

   cout << "Starting the makeLED-hw5 program" << endl;

   // select whether command is blink, on, off, flash or status
   // Blink
   if(cmd=="blink"){
	int counter = 0;
	cout << "Blinking the LED " << argv[2] << " times" << endl;
	while(counter < n)
	{
	   removeTrigger();
	   writeLED("/brightness","1");
	   sleep(1);
	   writeLED("/brightness","0");
	   sleep(1);
	   counter++;
	}
   }
   //On
   else if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   //Off
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   //flash
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="status"){
	// display the current trigger details
	cout << "Status:" << endl;
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED-hw5 Program" << endl;
   cout << endl;
   return 0;
}
