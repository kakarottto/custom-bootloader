bits 16

disk db 0x80
disk_error_message dw 11
	db 'Disk error!'

DAP:
;disk address package
;offset	size	decription
;	0	1		size of package
;	1	1		always 0
;	2	2		number of sectors to load
;	4	2		16-bit offset of target buffer
;	4	2		16-bit segment of target buffer
;	8	4		lower 32 bits of 48-bit starting LBA
;	12	4		upper 32 bits of 48-bit starting LBA


				db 0x10	;size of package
				db 0	;always 0
.num_sectors: dw 127	;number of sectors to load
.buf_offset:  dw 0x0	;16 bit offset
.buf_segment: dw 0x0	;16 bit segment
.LBA_lower:   dd 0x0	;lower 32 bits of LBA (Logical Block Address)
.LBA_upper:	  dd 0x0	;upper 32 bits of LBA

read_disk16:
	;ax - start sector
	;cx - num of sectors
	;bx - offset
	;dx - segment
	.start:
		cmp cx, 127
		jbe .good_size
		pusha
		mov cx, 127
		call read_disk16
		popa
		add eax, 127
		add dx, 127 * 32
		sub cx, 127
		jmp .start

.good_size:
	mov [DAP.LBA_lower], ax
	mov [DAP.num_sectors], cx
	mov [DAP.buf_offset], bx
	mov [DAP.buf_segment], dx
	mov dl, [disk]
	mov si, DAP
	mov ah, 0x42 ;bios function for reading disk
	int 0x13	 ;bios call
	jc .print_error
	ret

.print_error:
	mov si, disk_error_message
	call print16ln
	jmp $
