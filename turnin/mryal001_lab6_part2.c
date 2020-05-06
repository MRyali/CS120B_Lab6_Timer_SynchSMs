/*	Author: Mayur Ryali
 *  Partner(s) Name: 
 *	Lab Section:21
 *	Assignment: Lab #6  Exercise #2
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

enum States{Start, light1, light2, light3, wait, release, reset} state;
unsigned char tempB = 0x00; //temp for Port B
unsigned char button; //input from PA0

void Tick() {
	switch(state){
		case Start:
			state = light1;
			break;
		case light1: //PB0
			if (button) {
				state = wait;
			}
			else {
				state = light2;
			}
			break;
		case light2: //PB1
			if (button) {
				state = wait;
			}
			else {
				state = light3;
			}
			break;
		case light3: //PB2
			if (button) {
				state = wait;
			}
			else {
				state = light1;
			}
			break;
		case wait:
			if (!button) {
				state = release;
			}
			else {
				state = wait;
			}
			break;
		case release:
			if (button) {
				state = reset;
			}
			else {
				state = release;
			}
			break;
		case reset: 
			if (!button) {
				state = light1;
			}
			else {
				state = reset;
			}
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
		case wait:
			break;
		case release:
			break;
		case reset:
			break;
		default:
			break;
	
	}
}


int main(void) {
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x00; //output

	TimerSet(300); //300ms = 1s
	TimerOn();

	state = Start;

	while (1) {
		button = ~PINA & 0x08; //PA0
		Tick();

		while(!TimerFlag);
		TimerFlag = 0;

		PORTB = tempB;
   	}
    
    	return 1;
}
