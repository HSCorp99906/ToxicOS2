all:
	nasm -felf64 src/x86_64/kernel/interrupts/syscalls/syscall_dispatcher.S -o obj/sysc_disp.o
	nasm -felf64 src/x86_64/applications/kernelspace/keybindHandler/kbutils.S -o obj/kbutils.o
	nasm -felf64 src/x86_64/kernel/cpu/longMode.S -o obj/lm.o
	nasm -felf64 src/x86_64/kernel/interrupts/interrupt_handlers.S -o obj/asminthandlr.o
	nasm -felf64 src/x86_64/kernel/interrupts/IDT.S -o obj/asmidt.o
	gcc -c -m64 src/x86_64/kernel/kmain.c -mgeneral-regs-only -ffreestanding -fno-pie -fstack-protector -o obj/kmain.o
	gcc -c -m64 src/x86_64/applications/kernelspace/keybindHandler/main.c  -ffreestanding -fno-pie -fstack-protector -o obj/startupShell.o
	gcc -c -m64 src/x86_64/kernel/drivers/impl/IO.c -ffreestanding -fno-pie -fstack-protector -o obj/io.o
	gcc -c -m64 src/x86_64/kernel/drivers/impl/VGA.c -ffreestanding -fno-pie -fstack-protector -o obj/vga.o
	gcc -c -m64 src/x86_64/kernel/util/impl/strings.c -ffreestanding -fno-pie -fstack-protector -o obj/strings.o
	gcc -c -m64 src/x86_64/kernel/drivers/impl/floppy.c -ffreestanding -fno-pie -fstack-protector -o obj/floppy.o
	gcc -c -m64 src/x86_64/kernel/drivers/impl/graphics.c -ffreestanding -fno-pie -fstack-protector -o obj/graphics.o
	gcc -c -m64 src/x86_64/kernel/util/impl/converters.c -ffreestanding -fno-pie -fstack-protector -o obj/conv.o
	gcc -c -m64 src/x86_64/kernel/filesystem/impl/USTAR.c -ffreestanding -fno-pie -fstack-protector -o obj/ustar.o
	gcc -c -m64 src/x86_64/kernel/drivers/impl/mouse.c -ffreestanding -fno-pie -fstack-protector -o obj/mouse.o
	nasm -f elf64 src/x86_64/kernel/kernel.S -o obj/kasm.o
	ld -m elf_x86_64 -T link.ld obj/*.o -o Toxic/boot/kernel.bin
	grub-mkrescue -o ToxicOS.iso Toxic/
	sudo dd bs=4M if=ToxicOS.iso of=/dev/sdb
	rm ToxicOS.iso
	sudo qemu-system-x86_64 -hdb /dev/sdb -d int -D logfile.txt -M smm=off -monitor stdio 
