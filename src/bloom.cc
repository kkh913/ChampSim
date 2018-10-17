#include <assert.h>
#include <memory.h>
#include "bloom.h"
#include "murmurhash2.h"

inline static int test_bit_set_bit(unsigned char *buf, unsigned int x, int set_bit) {
  unsigned int byte = x >> 3;
  unsigned char c = buf[byte];  // expensive memory access
  unsigned int mask = 1 << (x % 8);

  if (c & mask) {
    return 1;
  } else {
    if (set_bit) {
      buf[byte] = c | mask;
    }
    return 0;
  }
}

static int bloom_check_add(BLOOM *bloom, const void *buffer, int len, int add) {
  int hits = 0;
  unsigned int a = murmurhash2(buffer, len, 0x9747b28c);
  unsigned int b = murmurhash2(buffer, len, a);
  unsigned int x;
  unsigned int i;

  for (i = 0; i < bloom->hashes; i++) {
    x = (a + i * b) % bloom->bits;
    if (test_bit_set_bit(bloom->bf, x, add)) {
      hits++;
    }
  }

  if (hits == bloom->hashes) {
    return 1;  // 1 == element already in (or collision)
  }

  return 0;
}

void bloom_init(BLOOM *bloom, int bytes, int hashes) {
  bloom->bytes = bytes;
  bloom->bits = bytes << 3;
  bloom->hashes = hashes;

  bloom->bf = new uint8_t[bloom->bytes]{};
  assert(bloom->bf);
}

int bloom_check(BLOOM *bloom, const void *buffer, int len) {
  return bloom_check_add(bloom, buffer, len, 0);
}

int bloom_add(BLOOM *bloom, const void *buffer, int len) {
  return bloom_check_add(bloom, buffer, len, 1);
}

void bloom_free(BLOOM *bloom) { memset(bloom->bf, 0, bloom->bytes); }
