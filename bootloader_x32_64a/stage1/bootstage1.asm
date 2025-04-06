bits 16
org 0x7c00	;bios reads here


stage1_entrypoint:
	jmp 0x000: setup_segments

	setup_segments:
		xor ax, ax
		mov ss, ax
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax

		mov sp, stage1_entrypoint
		cld

		;loading stage 2 from disk into RAM
		mov [disk], dl	;store the disk number
		mov ax, (stage2_start-stage1_start)/512
		mov cx, (kernel_end-stage2_start)/512
		mov bx, stage2_start
		xor dx, dx
		call read_disk16

		mov si, stage1_message
		call print16ln

		jmp stage2_entrypoint

		.halt:
			hlt
			jmp .halt

%include "liba/disk.asm"
%include "liba/print16.asm"

times 510-($-$$) db 0
dw 0xaa55
