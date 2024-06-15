all:
	clang *.c -Wno-multichar -Wno-int-conversion -I. -o iBoot32Patcher
clean:
	rm -f iBoot32Patcher
