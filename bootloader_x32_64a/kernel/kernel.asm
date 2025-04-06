 bits 64
 
 %define DATA_SEG 0x0010
 %define VRAM 0xB8000
 
 kernel:
 	mov ax, DATA_SEG
 	mov ds, ax
 	mov es, ax
 	mov fs, ax
 	mov gs, ax
 	mov ss, ax
 	
 	;test 
 	mov rax, 0x69696969
 	;kernel continues here
 	
 	
 	;kernel end
	.halt: 
		hlt
		jmp .halt
