#include "hblk_crypto.h"

/**
 * ec_from_pub - create an EC_KEY structure from a public key
 * @pub: public key to be converted
 *
 * Return: pointer to created EC_KEY, NULL on error
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key;
	EC_GROUP *group;
	EC_POINT *p;

	if (!pub)
		return (NULL);
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (NULL);
	group = (EC_GROUP *)EC_KEY_get0_group(key);
	p = EC_POINT_new(group);
	if (!p)
	{
		EC_KEY_free(key);
		return (NULL);
	}
	if (!EC_POINT_oct2point(group, p, pub, EC_PUB_LEN, NULL))
		goto out;
	if (!EC_KEY_set_public_key(key, p))
		goto out;
	EC_POINT_free(p);
	return (key);
out:
	EC_KEY_free(key);
	EC_POINT_free(p);
	return (NULL);
}
