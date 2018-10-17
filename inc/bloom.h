#ifndef _BLOOM_H_
#define _BLOOM_H_

#include <stdint.h>

typedef struct bloom {
  int bits;
  int bytes;
  int hashes;
  uint8_t* bf;
} BLOOM;

void bloom_init(BLOOM* bloom, int bytes, int hashes);

int bloom_check(BLOOM* bloom, const void* buffer, int len);

int bloom_add(BLOOM* bloom, const void* buffer, int len);

void bloom_free(BLOOM* bloom);

#endif
