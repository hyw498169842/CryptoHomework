all: RC4
	g++ RC4.cpp -o RC4 -Og
encrypt:
	make && ./RC4 plaintext 1
decrypt:
	make && ./RC4 ciphertext 0
check-en:
	make encrypt && cmp encrypted ciphertext
check-de:
	make decrypt && cmp decrypted plaintext
clean:
	rm -f RC4 keystream encrypted decrypted