CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb -gdwarf-2 -g
CFLAGS += -MD
CFLAGS += -mcmodel=medany
# CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
CFLAGS += -fno-common -nostdlib
CFLAGS += -fno-builtin-strncpy -fno-builtin-strncmp -fno-builtin-strlen -fno-builtin-memset
CFLAGS += -fno-builtin-memmove -fno-builtin-memcmp -fno-builtin-log -fno-builtin-bzero
CFLAGS += -fno-builtin-strchr -fno-builtin-exit -fno-builtin-malloc -fno-builtin-putc
CFLAGS += -fno-builtin-free
CFLAGS += -fno-builtin-memcpy -Wno-main
CFLAGS += -fno-builtin-printf -fno-builtin-fprintf -fno-builtin-vprintf
CFLAGS += -I.

QEMUOPTS = -machine virt -bios none -kernel kernel -m 128M -nographic -smp 4
QEMUOPTS += -serial mon:stdio 
#QEMUOPTS += -S -gdb tcp::1234
compile:
	riscv64-unknown-elf-gcc $(CFLAGS) start.c -c
	riscv64-unknown-elf-gcc $(CFLAGS) handler.c -c
	riscv64-unknown-elf-gcc $(CFLAGS) console.c -c
	riscv64-unknown-elf-gcc $(CFLAGS) main.c -c
	riscv64-unknown-elf-objdump -S start.o > start.asm
objectify:
	riscv64-unknown-elf-as -g entry.s -o entry.o 
	riscv64-unknown-elf-as -g cpu_utils.s -o cpu_utils.o 
	riscv64-unknown-elf-objdump -S entry.o > entry.asm
link: compile objectify
	riscv64-unknown-elf-ld -g -z max-page-size=4096 -T kernel.ld -o kernel entry.o start.o main.o cpu_utils.o handler.o console.o
	riscv64-unknown-elf-objdump -S kernel > kernel.asm

qemu:
	qemu-system-riscv64 $(QEMUOPTS)

dbg:
	gdb kernel
clean:
	-rm *.o
	-rm *.d
	-rm *.asm
	-rm *.sym
	-rm kernel
