/* Copyright (c) 2022 Hansem Ro <hansemro@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef RGB_MATRIX_ENABLE
#include "mbi.h"
#include "rgb_matrix.h"
#include "host.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(63, 255, 255, 255);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(63, 0, 0, 0);
    }
    return false;
}

/*
 * Channel Setup:
 *         ┌───────┐
 *    SDI->│       │->SDO
 * R_ROW3<-│       │->unused
 * R_ROW2<-│       │->unused
 * R_ROW1<-│       │->B_ROW0
 * R_ROW0<-│MBIA043│->B_ROW1
 * unused<-│   A   │->B_ROW2
 * G_ROW3<-│       │->B_ROW3
 * G_ROW2<-│       │->unused
 * G_ROW1<-│       │->G_ROW0
 *         └───────┘
 */
// clang-format off
const mbi_channel_t g_mbi_channels[MBI_NUM_DRIVER][MBI_NUM_CHANNELS] = {
    /* MBI A */
    {
    /*    Color channel (RED, GREEN, BLUE, or UNUSED)
     *    |
     *    |           MBI-managed row/column index
     *    |           | */
        { MBI_RED_CH, 3 }, /* MBI output channel 0 */
        { MBI_RED_CH, 2 }, /* MBI output channel 1 */
        { MBI_RED_CH, 1 }, /* ... */
        { MBI_RED_CH, 0 },
        { MBI_UNUSED_CH, 0 },
        { MBI_GREEN_CH, 3 },
        { MBI_GREEN_CH, 2 },
        { MBI_GREEN_CH, 1 },
        { MBI_GREEN_CH, 0 },
        { MBI_UNUSED_CH, 0 },
        { MBI_BLUE_CH, 3 },
        { MBI_BLUE_CH, 2 },
        { MBI_BLUE_CH, 1 },
        { MBI_BLUE_CH, 0 },
        { MBI_UNUSED_CH, 0 },
        { MBI_UNUSED_CH, 0 }, /* MBI output channel 15 */
    },
};
// clang-format on

#ifndef NO_LED
#    define NLD 255
#else
#    define NLD NO_LED
#endif

// LED Matrix to LED Index
// Since COL2ROW, MBI manages rows while MCU manages columns
// clang-format off
const uint8_t g_mbi_led_matrix_co[MBI_NUM_CHANNELS][MBI_NUM_LED_GPIO_PINS] = {
    /*          Col0 Col1 Col2 Col3 Col4 Col5 */
    /*Row0*/ {  21,  NLD, 14,  NLD, 7,   3,    },
    /*Row1*/ {  20,  17,  13,  10,  6,   2,    },
    /*Row2*/ {  19,  16,  12,  9,   5,   1,    },
    /*Row3*/ {  18,  15,  11,  8,   4,   0,    },
    /*Row4*/ {  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row5*/ {  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row6*/ {  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row7*/ {  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row8*/ {  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row9*/ {  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row10*/{  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row11*/{  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row12*/{  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row13*/{  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row14*/{  NLD, NLD, NLD, NLD, NLD, NLD,  },
    /*Row15*/{  NLD, NLD, NLD, NLD, NLD, NLD,  },
};
// clang-format on
#endif
