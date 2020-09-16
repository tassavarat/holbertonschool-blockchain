#include "hblk_crypto.h"

/**
 * sha256 - compute the hash of a sequence of bytes
 * @s: Sequence of bytes to be hashed
 * @len: Bytes to hash
 * @digest: array to store resulting hash in
 *
 * Return: pointer to digest, NULL on error
 */
uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!s || !digest)
		return (NULL);
	return (SHA256((const unsigned char *)s, len, digest));
}
