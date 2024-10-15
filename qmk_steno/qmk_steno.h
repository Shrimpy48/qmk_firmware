#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct NextKey {
  uint8_t mode;
  uint8_t key;
} NextKey;

extern void oled_write(const char *data, bool invert);

uint32_t translate_chord(const uint8_t *geminipr_packet);

void handle_stroke(uint32_t stroke, uint8_t host_os);

void oled_write_stroke(uint32_t stroke);

struct NextKey get_next_key(void);
