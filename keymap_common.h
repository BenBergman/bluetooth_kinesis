/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"


extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];


/*
 * ,-----------------------------------.   ,-----------------------------------.
 * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * `-----------------------------------'   `-----------------------------------'
 *    ,------------------------.                   ,------------------------.
 *    |    |   |   |   |   |   |                   |   |   |   |   |   |    |
 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
 *    |    |   |   |   |   |   |                   |   |   |   |   |   |    |
 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
 *    |    |   |   |   |   |   |                   |   |   |   |   |   |    |
 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
 *    |    |   |   |   |   |   |                   |   |   |   |   |   |    |
 *    `----+---+---+---+---+---'                   `---+---+---+---+---+----'
 *         |   |   |   |   |                           |   |   |   |   |
 *         `---------------'   ,-------.   ,-------.   `---------------'
 *                             |   |   |   |   |   |
 *                         ,---+---+---|   |---+---+---.
 *                         |   |   |   |   |   |   |   |
 *                         | - | - |---|   |---| - | - |
 *                         | - | - |   |   |   | - | - |
 *                         `-----------'   `-----------'
 */

/*
 * Condensed Kinesis matrix (original qwerty labelling)
 *   | 0     1     2     3     4     5     6     7     8     9     10    11
 * --+-----------------------------------------------------------------------
 * 0 | =     1     2     3     4     5     6     7     8     9     0     -
 * 1 | TB    Q     W     E     R     T     Y     U     I     O     P     \
 * 2 | CP    A     S     D     F     G     H     J     K     L     ;     ‘
 * 3 | LS    Z     X     C     V     B     N     M     ,     .     /     RS
 * 4 |       `     IN    LT          RT    UP          DN    [     ]
 * 5 |       F6    F7    F8                            F9    F10   F11
 * 6 | BKSP  F3    F4    F5    DEL   LCTRL SPACE ENTER F12   PS    SL    RALT
 * 7 | HOME  ESC   F1    F2    END   LALT  PGDN  RCTRL PB    PG    KY    PGUP
 */

// Convert physical keyboard layout to matrix array.
// This is a macro to define keymap easily in keyboard layout form.
#define	KEYMAP( \
	K701, K702, K703, K601, K602, K603, K501, K502, K503, K508, K509, K510, K608, K609, K610, K708, K709, K710, \
	K000, K001, K002, K003, K004, K005,                                     K006, K007, K008, K009, K010, K011, \
	K100, K101, K102, K103, K104, K105,                                     K106, K107, K108, K109, K110, K111, \
	K200, K201, K202, K203, K204, K205,                                     K206, K207, K208, K209, K210, K211, \
	K300, K301, K302, K303, K304, K305,                                     K306, K307, K308, K309, K310, K311, \
	      K401, K402, K403, K405,                                                 K406, K408, K409, K410, \
	                                    K605, K705,             K611, K707, \
	                              K600, K604, K700,             K711, K607, K606, \
	                                          K704,             K706 \
) \
{ \
	{ KC_##K000, KC_##K100, KC_##K200, KC_##K300, KC_NO,     KC_NO,     KC_##K600, KC_##K700 }, \
	{ KC_##K001, KC_##K101, KC_##K201, KC_##K301, KC_##K401, KC_##K501, KC_##K601, KC_##K701 }, \
	{ KC_##K002, KC_##K102, KC_##K202, KC_##K302, KC_##K402, KC_##K502, KC_##K602, KC_##K702 }, \
	{ KC_##K003, KC_##K103, KC_##K203, KC_##K303, KC_##K403, KC_##K503, KC_##K603, KC_##K703 }, \
	{ KC_##K004, KC_##K104, KC_##K204, KC_##K304, KC_NO,     KC_NO,     KC_##K604, KC_##K704 }, \
	{ KC_##K005, KC_##K105, KC_##K205, KC_##K305, KC_##K405, KC_NO,     KC_##K605, KC_##K705 }, \
	{ KC_##K006, KC_##K106, KC_##K206, KC_##K306, KC_##K406, KC_NO,     KC_##K606, KC_##K706 }, \
	{ KC_##K007, KC_##K107, KC_##K207, KC_##K307, KC_NO,     KC_NO,     KC_##K607, KC_##K707 }, \
	{ KC_##K008, KC_##K108, KC_##K208, KC_##K308, KC_##K408, KC_##K508, KC_##K608, KC_##K708 }, \
	{ KC_##K009, KC_##K109, KC_##K209, KC_##K309, KC_##K409, KC_##K509, KC_##K609, KC_##K709 }, \
	{ KC_##K010, KC_##K110, KC_##K210, KC_##K310, KC_##K410, KC_##K510, KC_##K610, KC_##K710 }, \
	{ KC_##K011, KC_##K111, KC_##K211, KC_##K311, KC_NO,     KC_NO,     KC_##K611, KC_##K711 } \
}

#endif
