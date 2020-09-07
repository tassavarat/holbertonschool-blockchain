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
	EVP_MD_CTX *mdctx;
	unsigned int md_len;

	if (!s || !len || !digest)
		return (NULL);
	mdctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(mdctx, EVP_get_digestbyname("SHA256"), NULL);
	EVP_DigestUpdate(mdctx, s, len);
	EVP_DigestFinal_ex(mdctx, digest, &md_len);
	EVP_MD_CTX_free(mdctx);
	return (digest);
}
