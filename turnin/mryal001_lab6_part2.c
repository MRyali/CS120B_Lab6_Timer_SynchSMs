/*	Author: Mayur Ryali
 *  Partner(s) Name:
 *	Lab Section:21
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

// Demo: https://drive.google.com/open?id=1-xi196et4XCCJ5h8Gri7VcV6m_isYfUw


#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum States{Start, light1, light2, light3, light4, wait, release, reset} state;
unsigned char tempB = 0x00; //temp for Port B
unsigned char button; //input from PA0
unsigned char s = 0; //tracks if previous state was reset or not
unsigned char tmp = 1;

void Tick() {
	switch(state){
		case Start:
			state = light1;
			break;
		case light1: //PB0
			if (!button) {
				tmp = 1;
			}
			if (button && s == 0 && tmp == 1) { //previous state was NOT rest
				state = wait;
			}
			else if (button && s == 1) { //previous state WAS reset
				tmp = 0;
				s = 0; //reset tracker
				state = light2;
			}
			else {
				s = 0;
				state = light2;
			}
			break;
		case light2: //PB1
			if (!button) {
				tmp = 1;
			}
			if (button && tmp == 1) {
				state = wait;
			}
			else {
				state = light3;
			}
			break;
		case light3: //PB2
			if (!button) {
				tmp = 1;
			}
			if (button && tmp == 1) {
				state = wait;
			}
			else {
				state = light4;
			}
			break;
		case light4:
			if (!button) {
				tmp = 1;
			}
			if (button && tmp == 1) {
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
		       	tmp = 1;
			s = 1;
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
		case light4:
			tempB = 0x02;
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
		button = ~PINA & 0x01; //PA0
		Tick();

		while(!TimerFlag);
		TimerFlag = 0;

		PORTB = tempB;
   	}

    	return 1;
}
