//
// Created by Bruno Philipe on 7/1/15.
//

#ifndef BOGOCRYPT_BOGOCRYPT_H
#define BOGOCRYPT_BOGOCRYPT_H

/**
 * Calculates the size required for the encryption output buffer.
 *
 * @param pInputLength The length of the input buffer.
 * @param pKeyLength The length of the key buffer.
 *
 * @returns The length of the output buffer to be output by @p bogocrypt(5).
 */
long bogocryptsize(long pInputLength, int pKeyLength);

/**
 * Calculates the size required for the decryption output buffer.
 *
 * @param pInputLength The length of the input buffer.
 * @param pKeyLength The length of the key buffer.
 *
 * @returns The length of the output buffer to be output by @p bogodecrypt(5).
 */
long bogodecryptsize(long pInputLength, int pKeyLength);

/**
 * Encrypts the input buffer with the specified key.
 *
 * @p pOutput should have already been allocated with length equal to the output of @p bogocryptsize(2).
 *
 * @param pInput The input buffer, preferably ASCII valid characters (base64 string).
 * @param pInputLength The length of input buffer.
 * @param pKey The key buffer.
 * @param pKeyLength The length of the key buffer.
 * @param pOutput The buffer where the output will be written to.
 */
int bogocrypt(const char *pInput, long pInputLength, const char *pKey, int pKeyLength, char **pOutput);

/**
 * Decrypts the input buffer with the specified key.
 *
 * @p pOutput should have already been allocated with length equal to the output of @p bogodecryptsize(2).
 *
 * @param pInput The input buffer exactly as output by @p bogocrypt(5).
 * @param pInputLength The length of input buffer.
 * @param pKey The key buffer.
 * @param pKeyLength The length of the key buffer.
 * @param pOutput The buffer where the output will be written to.
 */
int bogodecrypt(const char *pInput, long pInputLength, const char *pKey, int pKeyLength, char **pOutput);

#endif //BOGOCRYPT_BOGOCRYPT_H
