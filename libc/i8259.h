#pragma once
#include <types.h>

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1+1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2+1)

#define ICW1_ICW4 0x01 //icw4 will present
#define ICW1_SINGLE	0x02 //single mode
#define ICW1_INTERVAL4 0x04 //call address interval 4
#define ICW1_LEVEL 0x08 //level triggered mode
#define ICW1_INIT 0x10 //init

#define ICW4_8086 0x01 //8086/88 mode
#define ICW4_AUTO 0x02 //auto EOI
#define ICW4_BUF_SLAVE 0x08 //buffered mode slave
#define ICW4_BUF_MASTER 0x0C //buffered mode master
#define ICW4_SFNM 0x10 //special fully nested mode

#define PIC_EOI 0x20 //end of interrupt
#define PIC_READ_IRR 0x0a
#define PIC_READ_ISR 0x0b



static inline void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);
void outw(uint16_t port, uint16_t data);
uint16_t inw(uint16_t port);
void outl(uint16_t port, uint32_t data);
uint32_t inl(uint16_t port);
void io_wait();
int interrupts_enabled();
void PIC_sendEOI(uint8_t irq);
void PIC_remap(int off1, int off2);
void pic_disable();
void IRQ_set_mask(uint8_t irq);
void IRQ_clear_mask(uint8_t irq);
uint16_t pic_get_irq_reg(int ocw3);
uint16_t pic_get_irr();
uint16_t pic_get_isr();
