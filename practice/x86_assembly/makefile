master.img: boot.bin
	dd if=boot.bin of=master.img bs=512 count=1 conv=notrunc

%.bin: %.asm
	nasm -f bin $< -o $@

.PHONY: bochs
bochs: master.img
	bochs -q -unlock

.PHONY:clean
clean:
	rm -rf *.bin
