all:
	clang *.c -Wno-multichar -I. -o iBoot32Patcher
clean:
	rm -f iBoot32Patcher
