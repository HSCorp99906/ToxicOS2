all:
	nasm -felf32 src/x86_64/kernel/memory/GDT.S -o obj/asmgdt.o
	nasm -felf32 src/x86_64/kernel/interrupts/syscalls/syscall_dispatcher.S -o obj/sysc_disp.o
	nasm -felf32 src/x86_64/applications/kernelspace/keybindHandler/kbutils.S -o obj/kbutils.o
	gcc -c -m32 src/x86_64/kernel/kmain.c -mgeneral-regs-only -ffreestanding -fno-pie -fstack-protector -o obj/kmain.o
	gcc -c -m32 src/x86_64/applications/kernelspace/keybindHandler/main.c  -ffreestanding -fno-pie -fstack-protector -o obj/startupShell.o
	gcc -c -m32 src/x86_64/kernel/drivers/impl/IO.c -ffreestanding -fno-pie -fstack-protector -o obj/io.o
	gcc -c -m32 src/x86_64/kernel/drivers/impl/VGA.c -ffreestanding -fno-pie -fstack-protector -o obj/vga.o
	gcc -c -m32 src/x86_64/kernel/util/impl/strings.c -ffreestanding -fno-pie -fstack-protector -o obj/strings.o
	gcc -c -m32 src/x86_64/kernel/drivers/impl/floppy.c -ffreestanding -fno-pie -fstack-protector -o obj/floppy.o
	nasm -f elf32 src/x86_64/kernel/kernel.S -o obj/kasm.o
	i686-elf-ld -m elf_i386 -T link.ld obj/*.o -o Toxic/boot/kernel.bin
	grub-mkrescue -o ToxicOS.iso Toxic/
	sudo dd bs=4M if=ToxicOS.iso of=/dev/sdb
	rm ToxicOS.iso
	sudo qemu-system-x86_64 -hdb /dev/sdb -monitor stdio 
