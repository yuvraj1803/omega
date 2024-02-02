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
OBJ += ./build/monitor/irq.o
OBJ += ./build/monitor/exceptions.S.o
OBJ += ./build/monitor/delay.o
OBJ += ./build/monitor/context.o
OBJ += ./build/monitor/context.S.o
OBJ += ./build/monitor/sync.o
OBJ += ./build/monitor/misc.S.o
OBJ += ./build/monitor/bl33_loader.o
OBJ += ./build/mm/mm.o
OBJ += ./build/mm/mm.S.o
OBJ += ./build/mm/paging.S.o
OBJ += ./build/drivers/uart.o
OBJ += ./build/drivers/sd.o
OBJ += ./build/lib/stdio.o
OBJ += ./build/lib/memory.o
OBJ += ./build/lib/string.o
OBJ += ./build/lib/stdlib.o
OBJ += ./build/debug/debug.o
OBJ += ./build/fs/diskio.o
OBJ += ./build/fs/ff.o

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

./build/fs/%.o: ./fs/%.c
	@echo [CC] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/mm/%.S.o: ./mm/%.S
	@echo [CC] $@
	$(CC) $(ASMFLAGS) -c $< -o $@


omega.bin: sdcard $(OBJ)
	$(LD) -T linker.ld -o ./omega.elf $(OBJ_C) $(OBJ)
	$(OBJCOPY) ./omega.elf -O binary ./omega.bin

sdcard:	deltaV
	sudo modprobe nbd max_part=8
	qemu-img create sdcard.img 128m
	sudo qemu-nbd -c /dev/nbd0 --format=raw sdcard.img 
	(echo o; echo n; echo p; echo 1; echo ; echo ;echo w; echo q) | sudo fdisk /dev/nbd0
	@sudo mkfs.fat -F32 /dev/nbd0p1
	mkdir temp || true
	sudo mount -o user /dev/nbd0p1 temp/
	sudo cp ./deltaV/kernel8.img temp/
	sudo cp -r ./deltaV/guests temp/
	sleep 1s
	sudo umount temp/
	rmdir temp/ || true
	@sudo qemu-nbd -d /dev/nbd0
	(echo t; echo c; echo w; echo q) | sudo fdisk sdcard.img


deltaV:
	cd deltaV && OMEGA=1 make

run: omega.bin
	qemu-system-aarch64 -M raspi3b -nographic -serial null -serial mon:stdio -m 1024 -drive file=./sdcard.img,if=sd,format=raw -kernel ./omega.bin

debug: omega.bin
	qemu-system-aarch64 -M raspi3b -nographic -serial null -serial mon:stdio -m 1024 -drive file=./sdcard.img,if=sd,format=raw -kernel ./omega.bin -s -S

gdb: 
	gdb-multiarch -ex "target remote localhost:1234" -ex "add-symbol-file omega.elf" -ex "add-symbol-file ./deltaV/deltaV.elf" -ex "add-symbol-file ./deltaV/guests/deltaOS/deltaOS.elf"

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