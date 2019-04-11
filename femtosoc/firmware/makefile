# femtosoc firmware 

# path to gcc
TOOLCHAIN_PREFIX = /opt/riscv32i/bin/riscv32-unknown-elf-

counter: counter.S
	$(TOOLCHAIN_PREFIX)gcc -Os -ffreestanding -nostdlib -o counter.elf counter.S 
	$(TOOLCHAIN_PREFIX)objcopy -O binary counter.elf counter.bin
	python3 ../../firmware/makehex.py counter.bin 1024 > counter.mem

femto_fw: main.c femto.lds femto.S
	$(TOOLCHAIN_PREFIX)gcc -march=rv32ic -Wl,-Bstatic,-T,femto.lds,--strip-debug -ffreestanding -nostdlib -o femto_fw.elf femto.S main.c
	$(TOOLCHAIN_PREFIX)objcopy -O binary femto_fw.elf femto_fw.bin
	python3 ../../firmware/makehex.py femto_fw.bin 16384 > femto_fw.mem

.PHONY: clean
clean:
	rm -f femto_fw.elf femto_fw.bin
	rm -f counter.elf counter.bin

