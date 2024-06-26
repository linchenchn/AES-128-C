/*
 * TODO: Add your name and student number here, along with
 *       a brief description of this code.
 * Name: Lin Chen
 * Number: D23125391
 */

#include <stdio.h>
#include <stdlib.h>  // for malloc, free
// TODO: Any other files you need to include should go here

#include <string.h>

#include "rijndael.h"

// Implementation: Substitution Box
unsigned char s_box[256] = {
    // 0     1    2      3     4    5     6     7      8    9     A      B    C
    // D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,  // 0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,  // 1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
    0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,  // 2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
    0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,  // 3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,  // 4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,  // 5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
    0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,  // 6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,  // 7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
    0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,  // 8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
    0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,  // 9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,  // A
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
    0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,  // B
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
    0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,  // C
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,  // D
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
    0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,  // E
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
    0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};  // F

// Implementation: Rijndael S-box
unsigned char r_sbox[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E,
    0x81, 0xF3, 0xD7, 0xFB, 0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
    0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB, 0x54, 0x7B, 0x94, 0x32,
    0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49,
    0x6D, 0x8B, 0xD1, 0x25, 0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92, 0x6C, 0x70, 0x48, 0x50,
    0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05,
    0xB8, 0xB3, 0x45, 0x06, 0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
    0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B, 0x3A, 0x91, 0x11, 0x41,
    0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8,
    0x1C, 0x75, 0xDF, 0x6E, 0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
    0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B, 0xFC, 0x56, 0x3E, 0x4B,
    0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59,
    0x27, 0x80, 0xEC, 0x5F, 0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
    0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF, 0xA0, 0xE0, 0x3B, 0x4D,
    0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63,
    0x55, 0x21, 0x0C, 0x7D};

// Implementation: Round Constant
unsigned char Rcon[32] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36,
    0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97,
    0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
};

/*
  Operations used when encrypting a block.
  SubBytes operates on each byte of the block independently,
  applying a substitution to each byte based on
  a fixed lookup table called the S-box.
 */
void sub_bytes(unsigned char *block) {
  // TODO: This function performs the SubBytes transformation during encryption.
  // substitute all the values from the block with the value in the S_Box
  // using the block value as index for the S_Box
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block[i] = s_box[block[i]];
  }
}

/*
  ShiftRows operates on the rows of the block,
  cyclically shifting the bytes of each row to the left by different offsets.
 */
void shift_rows(unsigned char *block) {
  // TODO: This function performs the ShiftRows transformation during
  // encryption. Declare a temporary block to store intermediate results
  unsigned char temp_block[BLOCK_SIZE];
  // Iterate over each column in the block
  for (int i = 0; i < BLOCK_SIZE; i += 4) {
    // Perform row shifting with diagonal effect
    // Shift the first byte in the row, no shift for the first column
    temp_block[i] = block[i];
    // Shift the second byte in the row, cyclically shift left by 1
    temp_block[i + 1] = block[(i + 5) % BLOCK_SIZE];
    // Shift the third byte in the row, cyclically shift left by 2
    temp_block[i + 2] = block[(i + 10) % BLOCK_SIZE];
    // Shift the fourth byte in the row, cyclically shift left by 3
    temp_block[i + 3] = block[(i + 15) % BLOCK_SIZE];
  }

  // Copy the contents of the temporary block back to the original plain_text
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block[i] = temp_block[i];
  }
}

// Function gmul implements multiplication in Galois Field (GF).
unsigned char gmul(unsigned char rhs, unsigned char lhs) {
  unsigned char peasant = 0;         // Store the final result
  unsigned int irreducible = 0x11b;  // Irreducible polynomial used in GF(2^8)
  // Use the peasant's algorithm for multiplication
  while (lhs) {
    if (lhs & 1) {              // If the lowest bit of the left-hand side is 1
      peasant = peasant ^ rhs;  // Add rhs to the result
    }
    if (rhs & 0x80) {  // If the highest bit of rhs is 1
      // Perform left shift and XOR with the irreducible polynomial
      rhs = (rhs << 1) ^ irreducible;
    } else {
      rhs = rhs << 1;  // Otherwise, only perform left shift
    }
    lhs = lhs >> 1;  // Right shift the left-hand side by 1
  }
  return peasant;
}

/* MixColumns operates on the columns of the block,
   treating each column as a four-term polynomial and multiplying it
   with a fixed polynomial modulo a predefined polynomial.
*/
void mix_columns(unsigned char *block) {
  // TODO: This function performs the MixColumns
  //       transformation during encryption.

  // Array to store the temporary result
  unsigned char temp_block[BLOCK_SIZE];
  for (int i = 0; i < BLOCK_SIZE; i += 4) {
    // Apply the MixColumns transformation to each column
    // Each column has a length of 4, so the loop has a step of 4
    temp_block[i] = gmul(block[i], (unsigned char)2) ^
                    gmul(block[i + 1], (unsigned char)3) ^ block[i + 2] ^
                    block[i + 3];
    temp_block[i + 1] = block[i] ^ gmul(block[i + 1], (unsigned char)2) ^
                        gmul(block[i + 2], (unsigned char)3) ^ block[i + 3];
    temp_block[i + 2] = block[i] ^ block[i + 1] ^
                        gmul(block[i + 2], (unsigned char)2) ^
                        gmul(block[i + 3], (unsigned char)3);
    temp_block[i + 3] = gmul(block[i], (unsigned char)3) ^ block[i + 1] ^
                        block[i + 2] ^ gmul(block[i + 3], (unsigned char)2);
  }
  // Copy the computed result back to the original array
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block[i] = temp_block[i];
  }
}

/*
 * Operations used when decrypting a block
 */
void invert_sub_bytes(unsigned char *block) {
  // TODO: This function performs the inverse of the SubBytes transformation
  // during decryption.
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block[i] = r_sbox[block[i]];
  }
}

void invert_shift_rows(unsigned char *block) {
  // TODO: undoes the row shifts performed in ShiftRows.
  unsigned char temp_block[BLOCK_SIZE];

  for (int i = 0; i < BLOCK_SIZE; i += 4) {
    // incrementing by 5 causes the diagonal shift effect
    temp_block[i] = block[i];
    temp_block[(i + 5) % BLOCK_SIZE] = block[i + 1];
    temp_block[(i + 10) % BLOCK_SIZE] = block[i + 2];
    temp_block[(i + 15) % BLOCK_SIZE] = block[i + 3];
  }
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block[i] = temp_block[i];
  }
}

void invert_mix_columns(unsigned char *block) {
  unsigned char temp_block[BLOCK_SIZE];

  for (int i = 0; i < BLOCK_SIZE; i += 4) {
    // inverse multiplication > 9,11,13,14
    temp_block[i] = gmul(block[i], (unsigned char)14) ^
                    gmul(block[i + 1], (unsigned char)11) ^
                    gmul(block[i + 2], (unsigned char)13) ^
                    gmul(block[i + 3], (unsigned char)9);

    temp_block[i + 1] = gmul(block[i], (unsigned char)9) ^
                        gmul(block[i + 1], (unsigned char)14) ^
                        gmul(block[i + 2], (unsigned char)11) ^
                        gmul(block[i + 3], (unsigned char)13);

    temp_block[i + 2] = gmul(block[i], (unsigned char)13) ^
                        gmul(block[i + 1], (unsigned char)9) ^
                        gmul(block[i + 2], (unsigned char)14) ^
                        gmul(block[i + 3], (unsigned char)11);

    temp_block[i + 3] = gmul(block[i], (unsigned char)11) ^
                        gmul(block[i + 1], (unsigned char)13) ^
                        gmul(block[i + 2], (unsigned char)9) ^
                        gmul(block[i + 3], (unsigned char)14);
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    block[i] = temp_block[i];
  }
}

/*
 * This operation is shared between encryption and decryption.
 */
void add_round_key(unsigned char *block, unsigned char *round_key) {
  // TODO: AddRoundKey XORs each byte of the block with the corresponding byte
  // of the round key.
  int i;
  for (i = 0; i < BLOCK_SIZE; i++) {
    block[i] = block[i] ^ round_key[i];
  }
}

// Declaration of key schedule core function
void key_schedule_core(unsigned char *word, int iteration);
/*
 * This function should expand the round key. Given an input,
 * which is a single 128-bit key, it should return a 176-byte
 * vector, containing the 11 round keys one after the other
 */
unsigned char *expand_key(unsigned char *cipher_key) {
  // TODO: Implementation of key expansion function
  // 1.ExpandKey takes the original cipher key and
  // generates a series of round keys using a key schedule algorithm.
  // 2.These round keys are derived from the original key and are used
  // in each round of encryption and decryption.
  if (cipher_key == NULL) {
    printf("Error: Cipher key is NULL.\n");
    return NULL;
  }

  // Memory allocation
  unsigned char *expanded_key = malloc(EXPANDED_KEY_SIZE);
  if (expanded_key == NULL) {
    printf("Error: Memory allocation failed!\n");
    return NULL;
  }

  // Copy the initial key to the beginning of the expanded key
  memcpy(expanded_key, cipher_key, BLOCK_SIZE);

  int bytes_generated = BLOCK_SIZE;  // Initial key takes 16 bytes
  int rcon_iteration = 1;            // Round constant iteration

  // Key expansion loop
  while (bytes_generated < EXPANDED_KEY_SIZE) {
    unsigned char temp[4];  // Temporary bytes storage

    // Fetch four bytes from the previous round key as temporary bytes
    memcpy(temp, expanded_key + bytes_generated - 4, 4);

    // Perform key schedule if the boundary of each key block is reached
    if (bytes_generated % BLOCK_SIZE == 0) {
      // Perform key schedule
      key_schedule_core(temp, rcon_iteration++);
      // rcon_iteration++;
    }

    // Perform key expansion
    for (int i = 0; i < 4; i++) {
      expanded_key[bytes_generated] =
          expanded_key[bytes_generated - BLOCK_SIZE] ^ temp[i];
      bytes_generated++;
    }
  }
  // Return the expanded key sequence
  return expanded_key;
}

// Key schedule core function
void key_schedule_core(unsigned char *word, int iteration) {
  // Rotate left by one byte
  unsigned char temp = word[0];
  word[0] = word[1];
  word[1] = word[2];
  word[2] = word[3];
  word[3] = temp;

  // Substitution with S-box
  for (int i = 0; i < 4; i++) {
    word[i] = s_box[word[i]];
  }

  // Apply round constant
  word[0] ^= Rcon[iteration];
}

/*
 * The implementations of the functions declared in the
 * header file should go here
 */
unsigned char *aes_encrypt_block(unsigned char *plaintext, unsigned char *key) {
  // TODO: AES encryption on a single block of plaintext using the given key.

  // Allocate memory for the output ciphertext
  unsigned char *output =
      (unsigned char *)malloc(sizeof(unsigned char) * BLOCK_SIZE);
  if (!output) return NULL;

  // Step 0: Expand the key using the key expansion function
  unsigned char *expanded_key = expand_key(key);
  if (!expanded_key) {
    free(output);
    return NULL;
  }

  // Copy the plaintext into the output buffer to start the encryption process
  for (int i = 0; i < BLOCK_SIZE; i++) {
    output[i] = plaintext[i];
  }

  // Step 1: Initial Round
  // add_round_key(plaintext, key);  // Add the initial round key to the
  // plaintext
  add_round_key(output, expanded_key);

  // Step 2: Main Rounds
  for (int round = 1; round < NUM_ROUNDS; round++) {  // 9 rounds
    sub_bytes(output);
    shift_rows(output);
    mix_columns(output);
    add_round_key(output, expanded_key + (round * BLOCK_SIZE));
  }

  // Step 3: Final Round (without MixColumns)
  sub_bytes(output);
  shift_rows(output);
  add_round_key(output, expanded_key + NUM_ROUNDS * BLOCK_SIZE);

  // Free the memory allocated for expanded_key
  free(expanded_key);

  // Return the output ciphertext
  return output;
}

unsigned char *aes_decrypt_block(unsigned char *ciphertext,
                                 unsigned char *key) {
  // TODO: AES decryption on a single block of ciphertext using the given key.

  // Allocate memory for the output plaintext
  unsigned char *output =
      (unsigned char *)malloc(sizeof(unsigned char) * BLOCK_SIZE);
  // Handle memory allocation error
  if (!output) return NULL;

  // Step 0: Expand the key
  unsigned char *expanded_key = expand_key(key);
  if (!expanded_key) {
    free(output);
    return NULL;
  }

  // Copy the ciphertext into the output buffer to start the decryption process
  for (int i = 0; i < BLOCK_SIZE; i++) {
    output[i] = ciphertext[i];
  }

  // Step 1: Initial Round
  add_round_key(output, expanded_key + NUM_ROUNDS * BLOCK_SIZE);
  invert_shift_rows(output);
  invert_sub_bytes(output);

  // Step 2: Main Rounds (Inverse operations)
  for (int round = NUM_ROUNDS - 1; round > 0; round--) {
    add_round_key(output, expanded_key + round * BLOCK_SIZE);
    invert_mix_columns(output);
    invert_shift_rows(output);
    invert_sub_bytes(output);
  }

  // Step 3: Final Round (without invert_mix_columns)
  add_round_key(output, expanded_key);

  // Free the memory allocated for expanded_key
  free(expanded_key);

  // Return the output plaintext
  return output;
}