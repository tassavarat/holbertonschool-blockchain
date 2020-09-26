#include "hblk_crypto.h"

/**
 * ec_save - save existing EC key pair to disk
 * @key: EC key pair to save
 * @folder: path to folder to save keys
 *
 * Return: 1 on success, 0 on error
 */
int ec_save(EC_KEY *key, char const *folder)
{
	char buf[BUFSIZ] = {0};
	FILE *fp;

	if (!key || !folder)
		return (0);
	if (mkdir(folder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) ==
			-1)
		return (0);
	sprintf(buf, "%s/%s", folder, PUB_FILENAME);
	fp = fopen(buf, "w");
	if (!fp)
		return (0);
	if (!PEM_write_EC_PUBKEY(fp, key))
		goto out;
	fclose(fp);
	sprintf(buf, "%s/%s", folder, PRI_FILENAME);
	fp = fopen(buf, "w");
	if (!fp)
		return (0);
	if (!PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL))
		goto out;
	fclose(fp);
	return (1);
out:
	fclose(fp);
	return (0);
}
