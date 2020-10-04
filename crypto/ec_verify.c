#include "hblk_crypto.h"

/**
 * ec_verify - verify the signature of a given set of bytes using public key
 * @key: pointer to EC_KEY struct containing public key
 * @msg: pointer to characters to verify signature of
 * @msglen: len of msg
 * @sig: pointer to signature to check
 *
 * Return: 1 if signature valid, 0 if not
 */
int ec_verify(EC_KEY const *key, uint8_t const *msg, size_t msglen,
		sig_t const *sig)
{
	unsigned char dgst[SHA256_DIGEST_LENGTH];

	if (!key || !msg || !sig)
		return (0);

	if (!EC_KEY_check_key(key))
		return (0);
	if (!SHA256(msg, msglen, dgst))
		return (0);
	if (ECDSA_verify(0, dgst, SHA256_DIGEST_LENGTH, sig->sig, sig->len,
				(EC_KEY *)key) != 1)
		return (0);
	return (1);
}
