INC = ./include
LIB = ./lib/include
TOOLCHAIN=@aarch64-linux-gnu-
CC = 		$(TOOLCHAIN)gcc
AS = 		$(TOOLCHAIN)as
LD = 		$(TOOLCHAIN)ld
OBJCOPY = 	$(TOOLCHAIN)objcopy
OBJDUMP = 	$(TOOLCHAIN)objdump

CFLAGS = -g -ffreestanding -nostdlib -nostartfiles -Wall -I$(INC) -I$(LIB)
ASMFLAGS = -g -I$(INC)

.PHONY: all deltaV
all: deltaV omega.bin

OBJ += ./build/boot/boot.S.o
OBJ += ./build/monitor/monitor_main.o
OBJ += ./build/monitor/irq.S.o
OBJ += ./build/mm/mm.o
OBJ += ./build/mm/mm.S.o
OBJ += ./build/mm/paging.S.o
OBJ += ./build/drivers/uart.o
OBJ += ./build/lib/stdio.o
OBJ += ./build/lib/memory.o
OBJ += ./build/lib/string.o
OBJ += ./build/lib/stdlib.o
OBJ += ./build/debug/debug.o


./build/boot/%.S.o: ./boot/%.S
	@echo [CC] $@
	$(CC) $(ASMFLAGS) -c $< -o $@


./build/monitor/%.S.o: ./monitor/%.S
	@echo [CC] $@
	$(CC) $(ASMFLAGS) -c $< -o $@

./build/monitor/%.o: ./monitor/%.c
	@echo [CC] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/drivers/%.o: ./drivers/%.c
	@echo [CC] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/mm/%.o: ./mm/%.c
	@echo [CC] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/lib/%.o: ./lib/src/%.c
	@echo [CC] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/debug/%.o: ./debug/%.c
	@echo [CC] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/mm/%.S.o: ./mm/%.S
	@echo [CC] $@
	$(CC) $(ASMFLAGS) -c $< -o $@


omega.bin: $(OBJ)
	$(LD) -T linker.ld -o ./omega.elf $(OBJ_C) $(OBJ)
	$(OBJCOPY) ./omega.elf -O binary ./omega.bin

deltaV:
	cd deltaV && make

run: omega.bin
	qemu-system-aarch64 -M raspi3b -nographic -serial null -serial mon:stdio -m 1024 -kernel ./omega.bin

debug: omega.bin
	qemu-system-aarch64 -M raspi3b -nographic -serial null -serial mon:stdio -m 1024 -kernel ./omega.bin -s -S

gdb: omega.bin
	gdb-multiarch -ex "target remote localhost:1234" -ex "add-symbol-file omega.elf"

list: omega.bin
	aarch64-linux-gnu-objdump -D omega.elf > omega.list

clean:
	cd deltaV && make clean
	rm -f *.elf
	rm -f *.img
	rm -f *.bin
	find ./build -name '*.o' -delete 
	find ./build -name '*.d' -delete
	rm -f *.list