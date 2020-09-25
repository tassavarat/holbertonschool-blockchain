#include "hblk_crypto.h"

/**
* ec_save - save pub/private key pair into a file
* @key: key pair
* @folder: directory where to store the file
* Return: 1 on success, 0 on failure
*/
int ec_save(EC_KEY *key, char const *folder)
{
	char file[512] = {0};
	FILE *fp;
	struct stat st = {0};

	if (!key || !folder)
		return (0);
	if (stat(folder, &st) == -1)
	{
		if (mkdir(folder, 0700) == -1)
			return (0);
	}
	sprintf(file, "%s/%s", folder, "key.pem");
	fp = fopen(file, "w");
	if (!fp)
		return (0);
	if (!PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL))
		return (0);
	fclose(fp);
	sprintf(file, "%s/%s", folder, "key_pub.pem");
	fp = fopen(file, "w");
	if (!fp)
		return (0);
	if (!PEM_write_EC_PUBKEY(fp, key))
		return (0);
	fclose(fp);
	return (1);
}
