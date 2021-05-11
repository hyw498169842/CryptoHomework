all: SHA-3-256
	g++ SHA-3-256.cpp -o SHA-3-256 -Og
encrypt:
	make && ./SHA-3-256 plaintext
check-en:
	make encrypt && cmp encrypted hashtext
clean:
	rm -f SHA-3-256 encrypted
