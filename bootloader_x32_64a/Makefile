.PHONY: clean, .force-rebuild
all: bootloader.bin

bootloader.bin: os.asm .force-rebuild
	nasm -fbin os.asm -o os.bin

clean:
	rm *.bin

run:
	qemu-system-x86_64 -drive format=raw,file=os.bin -monitor stdio
	
#https://alamot.github.io/os_stage2/
