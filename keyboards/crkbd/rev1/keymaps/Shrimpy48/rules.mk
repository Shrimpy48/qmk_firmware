RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes

MOUSEKEY_ENABLE = yes
DIGITIZER_ENABLE = yes

KEY_OVERRIDE_ENABLE = yes

SWAP_HANDS_ENABLE = no

COMBO_ENABLE = yes

BOOTMAGIC_ENABLE = no

STENO_ENABLE = yes
STENO_PROTOCOL = geminipr

MIDI_ENABLE = yes

NKRO_ENABLE = yes

REPEAT_KEY_ENABLE = yes

LTO_ENABLE = yes

# SRC += oneshot.c
# SRC += swapper.c
SRC += snek.c
LIB_SRC += /home/philip/python/steno/rust/target/thumbv6m-none-eabi/release/libsteno_engine.a
