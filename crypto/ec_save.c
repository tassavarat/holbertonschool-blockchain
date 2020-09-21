#include "hblk_crypto.h"

int write_file(char *buf, char const *folder, char *fname, int type,
		EC_KEY *key)
{
	FILE *fp;

	sprintf(buf, "%s/%s", folder, fname);
	fp = fopen(buf, "w");
	if (!fp)
		return (0);
	if (type == PRIV_TYPE)
	{
		if (!PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL))
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
	char buf[BUFSIZ];

	if (!key || !folder || strlen(folder) + strlen(PUB_NAME) > BUFSIZ)
		return (0);
	if (mkdir(folder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) ==
			-1)
		return (0);
	if (!write_file(buf, folder, PRIV_NAME, PRIV_TYPE, key))
		return (0);
	if (!write_file(buf, folder, PUB_NAME, PUB_TYPE, key))
		return (0);
	return (1);
}
