/*	Author: Mayur Ryali
 *  Partner(s) Name: 
 *	Lab Section:21
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

// Demo: 

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum States{Start, light1, light2, light3} state;
unsigned char tempB = 0x00; //temp for Port B


void Tick() {
	switch(state){
		case Start:
			state = light1;
			break;
		case light1: //PB0
			state = light2;
			break;
		case light2: //PB1
			state = light3;
			break;
		case light3: //PB2
			state = light1;
			break;
		default:
			state = Start;
			break;
	
	}

	switch(state) {
		case Start:
			break;
		case light1: //PB0
			tempB = 0x01;
			break;
		case light2: //PB1
			tempB = 0x02;
			break;
		case light3: //PB2
			tempB = 0x04;
			break;
		default:
			break;
	
	}
}


int main(void) {
    DDRB = 0xFF; PORTB = 0x00; //output

    TimerSet(1000); //1000ms = 1s
    TimerOn();

    state = Start;

    while (1) {
	Tick();

	PORTB = tempB;

	while(!TimerFlag);
	TimerFlag = 0;
    }
    
    return 1;
}
