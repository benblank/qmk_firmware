// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************/

#pragma once

// Autocorrection dictionary (9 entries):
//   :ehco:     -> echo
//   :ehcoes:   -> echoes
//   :gamepaly: -> gameplay
//   :lenght:   -> length
//   :lenghts:  -> lengths
//   :naon:     -> nano
//   :paly:     -> play
//   :widht:    -> width
//   :widhts:   -> widths

#define AUTOCORRECT_MIN_LENGTH 6 // ":ehco:"
#define AUTOCORRECT_MAX_LENGTH 10 // ":gamepaly:"
#define DICTIONARY_SIZE 137

static const uint8_t autocorrect_data[DICTIONARY_SIZE] PROGMEM = {
    0x2C, 0x00, 0x51, 0x12, 0x00, 0x12, 0x1B, 0x00, 0x16, 0x25, 0x00, 0x17, 0x55, 0x00, 0x1C, 0x6F,
    0x00, 0x00, 0x12, 0x04, 0x11, 0x2C, 0x00, 0x82, 0x6E, 0x6F, 0x00, 0x06, 0x0B, 0x08, 0x2C, 0x00,
    0x83, 0x63, 0x68, 0x6F, 0x00, 0x48, 0x2C, 0x00, 0x17, 0x39, 0x00, 0x00, 0x12, 0x06, 0x0B, 0x08,
    0x2C, 0x00, 0x85, 0x63, 0x68, 0x6F, 0x65, 0x73, 0x00, 0x0B, 0x00, 0x47, 0x42, 0x00, 0x0A, 0x4B,
    0x00, 0x00, 0x0C, 0x1A, 0x2C, 0x00, 0x83, 0x74, 0x68, 0x73, 0x00, 0x11, 0x08, 0x0F, 0x2C, 0x00,
    0x83, 0x74, 0x68, 0x73, 0x00, 0x0B, 0x00, 0x47, 0x5E, 0x00, 0x0A, 0x66, 0x00, 0x00, 0x0C, 0x1A,
    0x2C, 0x00, 0x82, 0x74, 0x68, 0x00, 0x11, 0x08, 0x0F, 0x2C, 0x00, 0x82, 0x74, 0x68, 0x00, 0x0F,
    0x04, 0x13, 0x00, 0x6C, 0x7A, 0x00, 0x08, 0x7F, 0x00, 0x00, 0x83, 0x6C, 0x61, 0x79, 0x00, 0x10,
    0x04, 0x0A, 0x2C, 0x00, 0x83, 0x6C, 0x61, 0x79, 0x00
};
