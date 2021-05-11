all: AES-128
	g++ AES-128.cpp -o AES-128 -Og
encrypt:
	make && ./AES-128 plaintext 1
decrypt:
	make && ./AES-128 ciphertext 0
check-en:
	make encrypt && cmp encrypted ciphertext
check-de:
	make decrypt && cmp decrypted plaintext
clean:
	rm -f AES-128 encrypted decrypted