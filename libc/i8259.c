#include <types.h>
#include <i8259.h>

static inline void outb(uint16_t port, uint8_t data)
{
	__asm__ volatile ( "outb %b0, %w1" : : "a"(data), "Nd"(port) : "memory");
}

uint8_t inb(uint16_t port){
	uint8_t result;
	__asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (port) : "memory");
	return result;
}

void outw(uint16_t port, uint16_t data){
	__asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (port) : "memory");
}

uint16_t inw(uint16_t port){
	uint16_t result;
	 __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (port) : "memory");
	 return result;
}

void outl(uint16_t port, uint32_t data){
	__asm__ volatile("outl %0, %1" : : "a"(data), "Nd" (port) : "memory");
}

uint32_t inl(uint16_t port){
	uint32_t result;
	__asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (port) : "memory");
	return result;
}

void io_wait(){
	outb(0x80,0);
}

int interrupts_enabled(){
	unsigned long flags;
	asm volatile("pushf\n pop %0" : "=g"(flags));
	return flags & (1<<9);
}

void PIC_sendEOI(uint8_t irq){
	if(irq >= 8) outb(PIC2_COMMAND,PIC_EOI);
	outb(PIC1_COMMAND,PIC_EOI);
}

void PIC_remap(int off1, int off2){
	uint8_t a1 = inb(PIC1_DATA);
	uint8_t a2 = inb(PIC2_DATA);
	
	//icw2 master pic and slave pic
	//icw3 tells master pic there is slave pic at IRQ2
	//icw3 tells slave pic its cascade mode
	//icw4 have the PICs use 8086 mode
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA,off1);
	io_wait();
	outb(PIC2_DATA,off2);
	io_wait();
	outb(PIC1_DATA, 4);
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();
	
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
	
	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);
}

void pic_disable(){
	outb(PIC1_DATA, 0xff);
	outb(PIC2_DATA, 0xff);
}

//when set, pic is ignored
void IRQ_set_mask(uint8_t irq){
	uint16_t port;
	uint8_t value;
	if(irq<8) port = PIC1_DATA;
	else {
		port = PIC2_DATA;
		irq -=8;
	}
	
	value = inb(port) | (1<<irq);
	outb(port,value);
}

void IRQ_clear_mask(uint8_t irq){
	uint16_t port;
	uint8_t value;
	if(irq < 8) port = PIC1_DATA;
	else{
		port = PIC2_DATA;
		irq -= 8;
	}
	
	value = inb(port) & ~(1<<irq);
	outb(port,value);
}
//OCW3 is command byte sent to the pic to handle interrupt control
	//bit 7: EOI signal
	//bit 6: IRR read
	//bit 5: ISR read
	//bit 4: specific EOI 
	//bit 3 - 0: can be used for soecific modes, depending on pic's master mode and can be with priority
uint16_t pic_get_irq_reg(int ocw3){
	outb(PIC1_COMMAND, ocw3);
	outb(PIC2_COMMAND, ocw3);
	return(inb(PIC2_COMMAND)<<8 | inb(PIC1_COMMAND));
}

uint16_t pic_get_irr(){
	return pic_get_irq_reg(PIC_READ_IRR);
}

uint16_t pic_get_isr(){
	return pic_get_irq_reg(PIC_READ_ISR);
}

//https://pdos.csail.mit.edu/6.828/2005/readings/hardware/8259A.pdf
