#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern void send_string(const char *string);

extern void register_code(uint8_t kc);

extern void unregister_code(uint8_t kc);

extern void tap_code(uint8_t kc);

void handle_chord(const uint8_t *geminipr_packet);
