bits 16

a20_enabled_message dw 15
	db 'A20 is enabled.'
a20_disabled_message dw 16
	db 'A20 is disabled.' 
a20_trying_bios dw 34
	db 'Trying to enable A20 using BIOS...'
a20_trying_kbd dw 49
	db 'Trying to enable A20 using Keyboard Controller...'
a20_trying_io92 dw 40
	db 'Trying to enable A20 using IO port 92...'

enable_a20:
	call check_a20	;check if its already enabled
	test ax, ax
	jnz .end
	
	mov si, a20_trying_kbd
	call print16ln
	mov si, a20_enable_using_kbd
	
	call check_a20
	test ax, ax
	jnz .end
	
	mov si, a20_trying_io92
	call print16ln
	call a20_enable_using_io92
	
	call check_a20
	test ax, ax
	jnz .end
	.halt:
		hlt
		jmp .halt
	.end:
		ret

check_a20:
	call real_mode_check_a20
	test ax, ax
	jnz .a20_enabled
		mov si, a20_disabled_message
		call print16ln
		ret
	.a20_enabled:
		mov si, a20_enabled_message
		call print16ln
		ret

real_mode_check_a20:
	pushf
	push ds
	push es
	push di
	push si
	cli
	
	xor ax, ax
	mov es, ax
	not ax
	mov ds, ax
	mov di, 0x0500
	mov si, 0x0510
	
	mov dl, byte [es:di]
	push dx
	mov dl, byte [ds:si]
	push dx
	
	mov byte [es:di], 0x00
	mov byte [ds:si], 0xff
	cmp byte [es:di], 0xff
	
	mov ax, 0
	je .a20_disabled
	mov ax, 1	;set ax to tell its enabled
	.a20_disabled:
		pop dx
		mov byte [ds:si], dl
		pop dx
		mov byte [es:di], dl
		
		pop si
		pop di
		pop es
		pop ds
		popf
		sti
		ret
	
;returns ax =0 (failure) or ax=1(success)	
a20_enable_using_kbd:
	cli
	call a20wait
	mov al, 0xad	;disable kbd
	out 0x64, al
	call a20wait
	mov al, 0xd0	;read from input
	out 0x64, al
	call a20wait2
	in al, 0x60
	push eax
	call a20wait
	mov al, 0xd1
	out 0x64, al
	call a20wait
	pop eax
	or al, 2
	out 0x60, al
	call a20wait
	mov al, 0xae	;enable kbd
	out 0x64, al
	call a20wait
	sti
	ret
a20wait:
	in al, 0x64
	test al, 2
	jnz a20wait
	ret

a20wait2:
	in al, 0x64
	test al, 1
	jnz a20wait2
	ret


;Bits of port 92h                                                    
;Bit 0 - setting to 1 causes a fast reset                            
;Bit 1 - 0: disable A20, 1: enable A20                               
;Bit 2 - manufacturer defined                                              
;Bit 3 - power on password bytes. 0: accessible, 1: inaccessible     
;Bits 4-5 - manufacturer defined                                     
;Bits 6-7 - 0b00: HDD activity LED off else on

a20_enable_using_io92:
	in al, 0x92		;read from port 0x92
	test al, 2		;check if second bit is set
	jnz .end
	or al, 2
	and al, 0xfe;make sure bit 0 is 0 cuz it causes fast reset
	out 0x92, al;do it
	.end:
	ret
