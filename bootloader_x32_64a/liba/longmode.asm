bits 16

check_longmode_support:
	mov eax, 0x80000000 ;test if there is extended processor info available
	cpuid
	cmp eax, 0x80000001
	jb .not_supported
	
	mov eax, 0x80000001
	cpuid	;all AMD64 compliant processors have the longmode-capable-bit (bit 29) set in edx
	test edx, (1<<29)
	
	jz .not_supported
	ret
	
	.not_supported:
		xor eax, eax
		ret


enter_longmode:
	mov edi, PAGING_DATA
	mov eax, 10100000b;set the PAE and PGE bit (Physical Address Extention and Page Global Enable)
	mov cr4, eax
	mov edx, edi			;point CR3 at PML4
	mov cr3, edx
	mov ecx, 0xC0000080;read from the EREF MSR (xtended Feature Enable Register Model Specific Reg)
	rdmsr
	or eax, 0x00000100	;set the LME bit (Long Mode Enable)
	wrmsr
	mov ebx, cr0
	or ebx, 0x80000001	;activate long mode by enabling paging and GDT simultaneously
	mov cr0, ebx
	lgdt [GDT.pointer]
	jmp CODE_SEG:kernel ;load code segment with 64 bit segment and flush the instruction cache.
