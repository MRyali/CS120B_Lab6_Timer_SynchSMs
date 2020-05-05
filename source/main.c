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

enum States{Start, light1, light2, light3, wait1, wait2, wait3, release1, release2, release3} state;
unsigned char tempB = 0x00; //temp for Port B
unsigned char button;

void Tick() {
	switch(state){
		case Start:
			state = light1;
			break;
		case light1: //PB0
			if (button) {
				state = wait1;
			}
			else {
				state = light2;
			}
			break;
		case light2: //PB1
			if (button) {
				state = wait2;
			}
			else {
				state = light3;
			}
			break;
		case light3: //PB2
			if (button) {
				state = wait3;
			}
			else {
				state = light1;
			}
			break;
		case wait1:
			if (!button) {
				state = release1;
			}
			else {
				state = wait1;
			}
			break;
		case wait2:
			if (!button) {
				state = release2;
			}
			else {
				state = wait2;
			}
			break;
		case wait3:
			if (!button) {
				state = release3;
			}
			else {
				state = wait3;
			}
			break;
		case release1:
			if (button) {
				state = light1;
			}
			else {
				state = release1;
			}
			break;
		case release2:
			if (button) {
				state = light1;
			}
			else {
				state = release2;
			}
			break;
		case release3:
			if (button) {
				state = light1;
			}
			else {
				state = release3;
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
		case wait1:
			tempB = 0x01;
			break;
		case wait2:
			tempB = 0x02;
			break;
		case wait3:
			tempB = 0x04;
			break;
		case release1:
			tempB = 0x01;
			break;
		case release2:
			tempB = 0x02;
			break;
		case release3:
			tempB = 0x04;
			break;
		default:
			break;
	
	}
}


int main(void) {
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x00; //output

	TimerSet(300); //1000ms = 1s
	TimerOn();

	state = Start;

	while (1) {
		button = ~PINA & 0x08; //PA0
		Tick();

		PORTB = tempB;

		while(!TimerFlag);
		TimerFlag = 0;
	
   	}
    
    	return 1;
}
