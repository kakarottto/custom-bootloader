#include "types.h"
#include "idt.h"
#include "ports.h"
#include "timer.h"

unsigned int ticks=0;
unsigned int seconds =0;

void PITIRQ0(){
	ticks++;
	if(ticks%20==0)seconds++;
}

void Sleep(int seconds){
	int start = ticks;
	while(ticks< (start+20*seconds));
}

void InitTimer(){
	IRQ_install_handler(0x00,&PITIRQ0);
	u32 div =  1193180 / 100;
	outb(0x43, 0x36);
	outb(0x40, (u8)(div & 0xffff));
	outb(0x40, (u8)((div & 0xffff) & 0xff));
}

void Sleep_ticks(int t){
	int end = t + ticks;
	while(ticks<end);
}

unsigned int get_currtick(){
	return ticks;
}
