# AES-128
## 编译方式
直接在目录下输入 `make` 即可，默认使用 `-Og` 优化选项。
## 运行方式
``` bash
./AES-128 [file name] [encrypt flag]
```
`file name` 为待加密或解密的二进制文件，`encrypt flag` 为 0 时表示解密，否则表示加密。

加密结果默认保存为二进制文件 `encrypted`， 解密结果默认保存为二进制文件 `decrypted` 。

目录下提供了一对明密文 `plaintext` 和 `ciphertext`，可用于检查加解密的正确性。
## 其他 make 选项
``` makefile
make encrypt # make && ./AES-128 plaintext 1, 加密 plaintext 文件
make decrypt # make && ./AES-128 ciphertext 0, 解密 ciphertext 文件
make check-en # make encrypt && cmp encrypted ciphertext, 检查加密正确性
make check-de # make decrypt && cmp decrypted plaintext, 检查解密正确性
make clean
```

# RC4
## 编译方式
直接在目录下输入 `make` 即可，默认使用 `-Og` 优化选项。
## 运行方式
``` bash
./RC4 [file name] [encrypt flag]
```
`file name` 和 `encrypt flag` 的含义同上，加解密结果的保存方式也同上。

除 `plaintext` 和 `ciphertext` 外，目录下还提供了初始密钥 `key` ，可用于检查加解密的正确性。
## 其他 make 选项
``` makefile
make encrypt # make && ./RC4 plaintext 1, 加密 plaintext 文件
make decrypt # make && ./RC4 ciphertext 0, 解密 ciphertext 文件
make check-en # make encrypt && cmp encrypted ciphertext, 检查加密正确性
make check-de # make decrypt && cmp decrypted plaintext, 检查解密正确性
make clean
```

# SHA-3-256
## 编译方式
直接在目录下输入 `make` 即可，默认使用 `-Og` 优化选项。
## 运行方式
``` bash
./SHA-3-256 [file name]
```
`file name` 为待散列的二进制文件，散列结果默认保存为二进制文件 `encrypted` 。

目录下提供了 `plaintext` 和对应的散列值 `hashtext`，可用于检查算法的正确性。
## 其他 make 选项
``` makefile
make encrypt # make && ./SHA-3-256 plaintext, 散列 plaintext 文件
make check-en # make encrypt && cmp encrypted hashtext, 检查散列正确性
make clean
```
