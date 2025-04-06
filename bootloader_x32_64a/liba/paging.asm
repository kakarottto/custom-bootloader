bits 16

%define PAGE_PRESENT	(1<<0)
%define PAGE_WRITE	 	(1<<1)
%define CODE_SEG	 	0x0008
%define PAGING_DATA	0x9000


;init GDT
;The Global Descriptor Table (GDT) is a data structure used by x86-family processors    
;(starting with the 80286) in order to define the characteristics of the various memory 
;areas (segments) used during program execution, including the base address, the size,  
;and access privileges like executability and writability.                              

GDT:
	.null:
		dq 0x0000000000000000
	.code:
		dq 0x00209A0000000000	;64 bit code descriptor (exec/read)
	.data:
		dq 0x0000920000000000	;64 bit data descriptor (read/write)
	align 4
		dw 0					;padding to make the address of the GDT aligned on 4-byte boundary
	
	.pointer:
		dw $ - GDT - 1			;16 bit size (limit)
		dd GDT					;32 bit base address of GDT


prepare_paging:
; ES:EDI Should point to a valid page-aligned 16KiB buffer, for the PML4, PDPT, PD and a PT.
; SS:ESP Should point to memory that can be used as a small (1 uint32_t) stack.             
	
	mov edi, PAGING_DATA	;point edi to free space to create the paging structure
	
	;zero out the 16Kib buffer
	push di
	mov ecx, 0x1000
	xor eax, eax
	cld
	rep stosd	;repeat ecx(4096) times storing value of eax, at address es:di
	pop di
	
	;build the Page Map Level 4. es:di points to the PML4 table
	lea eax, [es:di + 0x1000]				;eax = address of the PDPT
	or eax, PAGE_PRESENT | PAGE_WRITE
	mov [es:di], eax
	
	;build the Page Directory Pointer Table
	lea eax, [es:di + 0x2000]				;eax = address of the PD
	or eax, PAGE_PRESENT | PAGE_WRITE
	mov [es:di + 0x1000], eax
	
	;build the Page Directory
	lea eax, [es:di + 0x3000]				;eax = address of the PT
	or eax, PAGE_PRESENT | PAGE_WRITE
	mov [es:di + 0x2000], eax
	
	push di
	lea di, [di + 0x3000]					;di = address of the PT
	mov eax, PAGE_PRESENT | PAGE_WRITE
	
	;build the Page Table
	.loop_PT:
		mov [es:di], eax
		add eax, 0x1000
		add di, 8
		cmp eax, 0x200000	;check if we did all of the 2Mib
		jb .loop_PT
	
	pop di
	ret
