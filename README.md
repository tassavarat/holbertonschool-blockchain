# holbertonschool-blockchain

## Learning Objectives
* How a Blockchain is considered “unbreakable”
* What is a hash algorithm
* What SHA stands for
* How hash algorithms apply to Blockchains
* What is asymmetric cryptography
* How asymmetric cryptography applies to cryptocurrencies
* What ECC stands for
* What ECDSA stands for
* What a digital signature is
* How digital signatures apply to cryptocurrencies

## Requirements
* Allowed editors: `vi`, `vim`, `emacs`
* All your files will be compiled on Ubuntu 14.04 LTS
* Your C programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall` `-Werror` `-Wextra,` `-pedantic` and the linker flags `-lssl` and `-lcrypto`
* All your files should end with a new line
* A README.md file, at the root of the folder of the project, is mandatory
* Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
* The prototypes of all your functions should be included in your header file called `crypto/hblk_crypto.h`
* All your header files should be include guarded

## Dependencies
For this project, you will need to Install the [OpenSSL](https://intranet.hbtn.io/rltoken/puTInVoDzWmv4k4TZ6Tx9A) library (if not already installed).

At the end of this project, the structure of your repository should look like this (you may have additional files):
```
holbertonschool-blockchain
├── crypto
│   ├── ec_create.c
│   ├── ec_from_pub.c
│   ├── ec_load.c
│   ├── ec_save.c
│   ├── ec_sign.c
│   ├── ec_to_pub.c
│   ├── ec_verify.c
│   ├── hblk_crypto.h
│   ├── libhblk_crypto.a
│   ├── Makefile
│   ├── provided
│   │   └── _print_hex_buffer.c
│   ├── sha256.c
│   └── test
│       ├── ec_create-main.c
│       ├── ec_from_pub-main.c
│       ├── ec_load-main.c
│       ├── ec_save-main.c
│       ├── ec_sign-main.c
│       ├── ec_to_pub-main.c
│       ├── ec_verify-main.c
│       └── sha256-main.c
└── README.md
```

---

### [0. SHA256](./crypto/sha256.c)
Write a function that computes the hash of a sequence of bytes
* Prototype: `uint8_t *sha256(int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH]);`, where
	* `s` is the sequence of bytes to be hashed
	* `len` is the number of bytes to hash in s
* The resulting hash must be stored in `digest`
* Your function must return a pointer to `digest`
* If `digest` happens to be `NULL`, your function must do nothing and return NULL
* You are not allowed to allocate memory dynamically
```
alex@~/holbertonschool-blockchain/crypto$ cat test/sha256-main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hblk_crypto.h"

void _print_hex_buffer(uint8_t const *buf, size_t len);

/**
 * main - Entry point
 *
 * @ac: Arguments counter
 * @av: Arguments vector
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int ac, char **av)
{
    uint8_t hash[SHA256_DIGEST_LENGTH];
    uint8_t *test_ptr;

    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s arg\n", av[0]);
        return (EXIT_FAILURE);
    }

    /* Test `sha256()` */
    test_ptr = sha256((int8_t *)av[1], strlen(av[1]), hash);
    if (!test_ptr)
    {
        fprintf(stderr, "sha256() failed\n");
        return (EXIT_FAILURE);
    }
    if (test_ptr != hash)
    {
        fprintf(stderr, "Return value and pointer differ\n");
        return (EXIT_FAILURE);
    }

    printf("\"%s\" hash is: ", av[1]);
    _print_hex_buffer(hash, SHA256_DIGEST_LENGTH);
    printf("\n");

    return (EXIT_SUCCESS);
}
alex@~/holbertonschool-blockchain/crypto$ gcc -Wall -Wextra -Werror -pedantic -I. -o sha256-test test/sha256-main.c provided/_print_hex_buffer.c sha256.c -lssl -lcrypto
alex@~/holbertonschool-blockchain/crypto$ ./sha256-test Holberton
77c4925c01e8d9f79c8a6a61685c6b3182be10f2fa553de915f3733ee19c0204
alex@~/holbertonschool-blockchain/crypto$ ./sha256-test "Holberton School"
2a05534c3fd942dc5e5ab0a968433b747b2188d526feffdb5a6406f15bf4861c
alex@~/holbertonschool-blockchain/crypto$
```
