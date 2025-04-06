bits 16

stage2_message dw 19
	db "Entering Stage 2..."
longmode_supported_message dw 23
	db "Long mode is supported."
longmode_not_supported_message dw 27
	db "Long mode is not supported?"



stage2_entrypoint:
	mov si, stage2_message
	call print16ln
	
	call check_longmode_support
	test eax, eax
	jz .longmode_not_supported
	mov si, longmode_supported_message
	call print16ln
	
	call enable_a20
	call prepare_paging
	call remap_pic
	call enter_longmode
	hlt
	
.longmode_not_supported:
	mov si, longmode_not_supported_message
	call print16ln
	jmp $

%include "liba/a20.asm"
%include "liba/paging.asm"
%include "liba/pic.asm"
%include "liba/longmode.asm"

