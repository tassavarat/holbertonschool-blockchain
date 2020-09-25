#include "hblk_crypto.h"

/**
 * write_file - write EC key to disk
 * @folder: path to folder to save keys
 * @fname: name of file to write
 * @type: specifies whether to write private or public key
 * @key: EC key pair to save
 *
 * Return: 1 on success, 0 on error
 */
int write_file(char const *folder, char *fname, int type, EC_KEY *key)
{
	char buf[BUFSIZ];
	FILE *fp;

	sprintf(buf, "%s/%s", folder, fname);
	fp = fopen(buf, "w");
	if (!fp)
		return (0);
	if (type == PRIV_TYPE)
	{
		if (!PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL,
					NULL))
			goto out;
	}
	else if (type == PUB_TYPE)
	{
		if (!PEM_write_EC_PUBKEY(fp, key))
			goto out;
	}
	else
	{
out:
		fclose(fp);
		return (0);
	}
	fclose(fp);
	return (1);
}

/**
 * ec_save - save existing EC key pair to disk
 * @key: EC key pair to save
 * @folder: path to folder to save keys
 *
 * Return: 1 on success, 0 on error
 */
int ec_save(EC_KEY *key, char const *folder)
{

	if (!key || !folder)
		return (0);
	if (mkdir(folder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) ==
			-1)
		return (0);
	if (!write_file(folder, PRIV_NAME, PRIV_TYPE, key))
		return (0);
	if (!write_file(folder, PUB_NAME, PUB_TYPE, key))
		return (0);
	return (1);
}
