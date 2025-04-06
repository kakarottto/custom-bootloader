bits 16
;The Programmable Interrupt Controller (PIC) is one of the most important chips in the x86. 
;Its function is to manage hardware interrupts and send them to the appropriate system interrupts. This 
;allows the system to respond to devices without the need for polling them all the time. In protected 
;mode and long mode, the Interrupt Requests (IRQs) 0-15 are in conflict with the CPU exceptions which 
;reserve the first 32 positions (0-31 or 0x00-0x1F). Thus, prior to switching to the long mode, we have 
;to change the PIC's offsets (a.k.a. remapping the PIC) so that IRQs use non-reserved vectors

PIC1_COMMAND    equ 0x20 ;Command port of 1st PIC
PIC1_DATA       equ 0x21 ;Data port of 1st PIC
PIC2_COMMAND    equ 0xA0 ;Command port of 2nd PIC
PIC2_DATA       equ 0xA1 ;Data port of 2nd PIC
PIC_EOI         equ 0x20 ;EOI (End of interrupt) command

ICW1_ICW4       equ 0x01 ;Initialization Command Word 4 is needed
ICW1_SINGLE     equ 0x02 ;Single mode (0: Cascade mode)
ICW1_INTERVAL4  equ 0x04 ;Call address interval 4 (0: 8)
ICW1_LEVEL      equ 0x08 ;Level triggered mode (0: Edge mode)
ICW1_INIT       equ 0x10 ;Initialization - required!

ICW4_8086       equ 0x01 ;8086/88 mode (0: MCS-80/85 mode)
ICW4_AUTO_EOI   equ 0x02 ;Auto End Of Interrupt (0: Normal EOI)
ICW4_BUF_SLAVE  equ 0x08 ;Buffered mode/slave
ICW4_BUF_MASTER equ 0x0C ;Buffered mode/master
ICW4_SFNM       equ 0x10 ;Special Fully Nested Mode

remap_pic:
; IRQs 0..15 -> INT 0x20..0x2F (30..47). For that
; 1st PIC's offset to 0x20 (32) and the 2nd's to 0x28 (40).

	push ax
	
	;disable IRQ
	mov al, 0xff
	out PIC1_DATA, al
	out PIC2_DATA, al
	nop
	nop
	
	;remap PIC
	mov al, ICW1_INIT | ICW1_ICW4 ;ICW1: Send initialization command (= 0x11) to both PICs 
	out PIC1_COMMAND, al    
	out PIC2_COMMAND, al     
	mov al, 0x20		;ICW2: set vector offset of 1st PIC to 0x20 (i.e. IRQ0 => INT 32) 
	out PIC1_DATA, al
	mov al, 0x28		;ICW2: set vector offset of 2nd PIC to 0x28 (i.e. IRQ8 => INT 40)    
	out PIC2_DATA, al
	mov al, 4			;ICW3: tell 1st PIC that there is a 2nd PIC at IRQ2
	out PIC1_DATA, al       
	mov al, 2          ;ICW3: tell 2nd PIC its cascade identity 
	out PIC2_DATA, al        
	mov al, ICW4_8086  ;ICW4: set mode to 8086/88 mode
	out PIC1_DATA, al
	out PIC2_DATA, al

	mov al, 0xff		;mask all interrupts(untill set proper IDT)
	out PIC1_DATA, al
	out PIC2_DATA, al
	
	pop ax
	ret
