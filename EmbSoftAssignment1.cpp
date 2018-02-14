//Assignment 1 Embedded Software

//Digital inputs sw1 and sw2
//sw1 enables/disables stream of pulses
//sw2 switches between normal mode and modified waveform cycle

//Digital outputs sigA and sigB
//variables a-d represent blocks of time and were determined through student personalisation

//n is a variable used to keep track of the number of pulses created per block
//the value of n is changed based on whether normal or modified waveform mode is selected


#include "mbed.h"
#include "MCP23017.h" // include 16-bit parallel I/O header file
#include "WattBob_TextLCD.h" // include 2*16 character display header file

//setting up lcd
#define BACK_LIGHT_ON(INTERFACE) INTERFACE->write_bit(1,BL_BIT)
#define BACK_LIGHT_OFF(INTERFACE) INTERFACE->write_bit(0,BL_BIT)

MCP23017 *par_port; // pointer to 16-bit parallel I/O object
WattBob_TextLCD *lcd; // pointer to 2*16 chacater LCD object

//digital inputs
DigitalIn sw1(p5);
DigitalIn sw2(p6);

//digital outputs
DigitalOut sigA(p29);
DigitalOut sigB(p30);

//variables assigned through student personalisation
int a = 400;          //us
int b = 1200;         //us
int c = 10;             //us
int d = 3500;         //us

int main() {
    //setting up lcd
    par_port = new MCP23017(p9, p10, 0x40);         // initialise 16-bit I/O chip
    lcd = new WattBob_TextLCD(par_port);            // initialise 2*26 char display
    par_port->write_bit(1,BL_BIT);                  // turn LCD backlight ON
    
    lcd->cls();                                     // clear display
    lcd->locate(0,0);                               // set cursor to location (0,0) - top left corner
    lcd->printf("Emb Soft Task 1");                 // print string
    lcd->locate(1,0);                               // set cursor to location (1,0) - bottom left corner
    lcd->printf("Amy Douglas");                     // print string
    
    while(1) {                                      //constant loop
        if (sw1 == 0){                              //if input switch 1 set to 0
            int n;                                  //n represents number of pulses in block
            if (sw2 == 1){                          //if switch 2 is set to "modified waveform cycle"
                n = c - 3;                          //alter number of pulses for modified waveform
            }
            else if (sw2 == 0){                     //if switch 2 is set to normal mode
                n = c;                              //set number of pulses to default value
            }
            sigB = 1;                               //set output B high
            wait_us(50);                            //keep signal high for 50us
            sigB = 0;                               //set output B low
            for (int x=0;x<n;x++){                  //for the number of pulses required
                int timeHigh = (a + (x*50));        //calculate the time the pulse should be high for
                sigA = 1;                           //set output A high
                wait_us(timeHigh);                  //wait calculated time
                sigA = 0;                           //set output A low
                wait_us(b);                         //wait for time specified between individual pulses
            }
            wait_us(d);                                //wait for time specified at the end of each cycle
        }
    }
    
    
}

