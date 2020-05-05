/*	Author: Mayur Ryali
 *  Partner(s) Name:
 *	Lab Section: 21
 *	Assignment: Lab #6 Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

 // Demo: https://drive.google.com/open?id=1-H2FFMoAWYfxVfR9-F5Kz63ZMj1wJPfE
 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum States {Start, Init, Inc, Dec, Zero, Wait} state;

unsigned char tempB; //temp for PORTB
unsigned char button0; //PA0
unsigned char button1; //PA1

void Tick() {
	switch(state) {
		case Start:
			state = Init;
			break;
		case Init:
			if (button0 && !button1) { //check if PA0 is 1
				state = Inc;
			}
			else if (!button0 && button1) { //check if PA1 is 1
				state = Dec;
			}
			else if (button0 && button1) { //check if both are pressed
				state = Zero;
			}
			else { //wait for button push
				state = Init;
			}
			break;
		case Inc:
			if (button0 && button1) {//check if both pressed
				state = Zero;
			}
			else { //wait for new action
				state = Wait;
			}
			break;
		case Dec:
			if (button0 && button1) {//check if both pressed
				state = Zero;
			}
			else { //wait for new action
				state = Wait;
			}
			break;
		case Zero: //check which button is pushed during zero state
			if (button0 && !button1) {
				state = Inc;
			}
			else if (!button0 && button1) {
				state = Dec;
			}
			else if (!button0 && !button1) {
				state = Init;
			}
			else {
				state = Zero;
			}
			break;
		case Wait: //wait for new action
			if (!button0 && !button1) {
				state = Init;
			}
			else if (button0 && button1) {
				state = Zero;
			}
			else {
				state = Wait;
			}
			break;
		default:
			state = Start;
			break;
	}

	switch(state) {
		case Start:
			break;
		case Init:
			break;
		case Inc: //increase while temp is below 9
			if (tempB < 9) {
				tempB = tempB + 1;
			}
			break;
		case Dec: //decrease while temp is greater than 0
			if (tempB > 0) {
				tempB = tempB - 1;
			}
			break;
		case Zero: //set to zero
			tempB = 0;
			break;
		case Wait:
			break;
		default:
			break;
	}
}



int main(void) {
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x00; //output

	TimerSet(100); //100ms
	TimerOn();

	state = Start;
	tempB = 0x07; //initially start with 7

    	while (1) {
		button0 = ~PINA & 0x01; //PA0, negated to account for pull-up mode
		button1 = ~PINA & 0x02; //PA1, negated for pull-up mode
		
		Tick();

		while(!TimerFlag);
		TimerFlag = 0;

		PORTB = tempB;
    	}
    	return 1;
}