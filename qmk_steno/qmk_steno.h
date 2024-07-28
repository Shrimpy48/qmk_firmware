#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern void send_string(const char *string);

extern void register_code(uint8_t kc);

extern void unregister_code(uint8_t kc);

extern void tap_code(uint8_t kc);

extern void oled_write(const char *data, bool invert);

uint32_t translate_chord(const uint8_t *geminipr_packet);

void handle_stroke(uint32_t stroke);

void oled_write_stroke(uint32_t stroke);
