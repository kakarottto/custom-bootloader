bits 16

newline dw 2
	db 13,10 ; \r\n

stage1_message dw 17
	db 'Stage 1 finished.'



print16:
	push ax
	push cx
	push si
	mov cx, word [si]	;first 16 bits = the number of characters in the string
	add si, 2
	.string_loop:		;print all the characters in the string
		lodsb
		mov ah, 0eh
		int 0x10
	loop .string_loop, cx
	pop si
	pop cx
	pop ax
	ret


print16ln:
	push si
	call print16
	mov si, newline
	call print16
	pop si
	ret


