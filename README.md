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

### [1. EC_KEY creation](./crypto/ec_create.c)
Write a function that creates a new EC key pair.
* Prototype: `EC_KEY *ec_create(void);`
* Your function must return a pointer to an `EC_KEY` structure, containing both the public and private keys, or `NULL` upon failure
* Both the private and the public keys must be generated
* You have to use the [secp256k1](https://intranet.hbtn.io/rltoken/d87cG30FDgcZTEdie3RNQQ) elliptic curve to create the new pair (See `EC_CURVE` macro)
```
alex@~/holbertonschool-blockchain/crypto$ cat test/ec_create-main.c
#include <stdlib.h>
#include <stdio.h>

#include "hblk_crypto.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    EC_KEY *key;

    /* Test `ec_create()` */
    key = ec_create();
    if (!key)
    {
        fprintf(stderr, "ec_create() failed\n");
        return (EXIT_FAILURE);
    }
    if (!EC_KEY_check_key(key))
    {
        fprintf(stderr, "Key verification failed\n");
        return (EXIT_FAILURE);
    }

    printf("Successfully created EC key pair\n");

    /* Cleanup */
    EC_KEY_free(key);

    return (EXIT_SUCCESS);
}
alex@~/holbertonschool-blockchain/crypto$ gcc -Wall -Wextra -Werror -pedantic -I. -o ec_create-test test/ec_create-main.c ec_create.c -lssl -lcrypto
alex@~/holbertonschool-blockchain/crypto$ valgrind ./ec_create-test
==17436== Memcheck, a memory error detector
==17436== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==17436== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==17436== Command: ./ec_create-test
==17436==
Successfully created EC key pair
==17436==
==17436== HEAP SUMMARY:
==17436==     in use at exit: 0 bytes in 0 blocks
==17436==   total heap usage: X allocs, X frees, Y bytes allocated
==17436==
==17436== All heap blocks were freed -- no leaks are possible
==17436==
==17436== For counts of detected and suppressed errors, rerun with: -v
==17436== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
alex@~/holbertonschool-blockchain/crypto$
```

### [2. EC_KEY to public key](./crypto/ec_to_pub.c)
Write a function that extracts the public key from an `EC_KEY` opaque structure

* Prototype: `uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]);`, where:
	* `key` is a pointer to the `EC_KEY` structure to retrieve the public key from. If it is `NULL`, your function must do nothing and fail
	* `pub` is the address at which to store the extracted public key (The key shall not be compressed)
* Your function must return a pointer to `pub`
* `NULL` must be returned upon failure, and there should not be any memory leak

NOTE: It is also possible to extract the private key from an EC_KEY structure, but we’re never going to store one’s private key anywhere in the Blockchain. So we don’t really need it.
```
alex@~/holbertonschool-blockchain/crypto$ cat test/ec_to_pub-main.c
#include <stdlib.h>
#include <stdio.h>

#include "hblk_crypto.h"

void _print_hex_buffer(uint8_t const *buf, size_t len);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    EC_KEY *key;
    uint8_t pub[EC_PUB_LEN];
    uint8_t *test_ptr;

    /* Prerequisites */
    key = ec_create();
    if (!key)
    {
        fprintf(stderr, "ec_create() failed\n");
        return (EXIT_FAILURE);
    }
    printf("Successfully created EC key pair\n");

    /* Test `ec_to_pub()` */
    test_ptr = ec_to_pub(key, pub);
    if (!test_ptr)
    {
        fprintf(stderr, "ec_to_pub() failed\n");
        EC_KEY_free(key);
        return (EXIT_FAILURE);
    }
    if (test_ptr != pub)
    {
        fprintf(stderr, "Return value and pointer differ\n");
        EC_KEY_free(key);
        return (EXIT_FAILURE);
    }

    printf("Public key: ");
    _print_hex_buffer(pub, EC_PUB_LEN);
    printf("\n");

    /* Cleanup */
    EC_KEY_free(key);

    return (EXIT_SUCCESS);
}
alex@~/holbertonschool-blockchain/crypto$ gcc -Wall -Wextra -Werror -pedantic -I. -o ec_to_pub-test test/ec_to_pub-main.c provided/_print_hex_buffer.c ec_to_pub.c ec_create.c -lssl -lcrypto
alex@~/holbertonschool-blockchain/crypto$ valgrind ./ec_to_pub-test
==18243== Memcheck, a memory error detector
==18243== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==18243== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==18243== Command: ./ec_to_pub-test
==18243==
Successfully created EC key pair
Public key: 04a6dedb9d6180946b7866fc1a63ceff2aa8012161e0a01c351fb8e408b5863de5a1732497e7f4da0f7ff96e6650a51d0ca64eccd969415f8f53e956aa046991df
==18243==
==18243== HEAP SUMMARY:
==18243==     in use at exit: 0 bytes in 0 blocks
==18243==   total heap usage: X allocs, X frees, Y bytes allocated
==18243==
==18243== All heap blocks were freed -- no leaks are possible
==18243==
==18243== For counts of detected and suppressed errors, rerun with: -v
==18243== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
alex@~/holbertonschool-blockchain/crypto$
```
