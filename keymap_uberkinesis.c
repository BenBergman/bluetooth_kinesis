#include "keymap_common.h"

/*
 * Hasu
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* 0: Qwerty
	 * ,-----------------------------------.   ,-----------------------------------.
	 * |ESC| F1| F2| F3| F4| F5| F6| F7| F8|   | F9|F10|F11|F12| PS| SL|Brk|Key|Prg|
	 * `-----------------------------------'   `-----------------------------------'
	 *     ,-----------------------.                   ,-----------------------.
	 *     |  =|  1|  2|  3|  4|  5|                   |  6|  7|  8|  9|  0|  -|
	 *     |---+---+---+---+---+---|                   |---+---+---+---+---+---|
	 *     |Tab|  Q|  W|  E|  R|  T|                   |  Y|  U|  I|  O|  P|  \|
	 *     |---+---+---+---+---+---|                   |---+---+---+---+---+---|
	 *     |Cap|  A|  S|  D|  F|  G|                   |  H|  J|  K|  L|  ;|  '|
	 *     |---+---+---+---+---+---|                   |---+---+---+---+---+---|
	 *     |Sft|  Z|  X|  C|  V|  B|                   |  N|  M|  ,|  .|  /|Sft|
	 *     `---+---+---+---+---+---'                   `---+---+---+---+---+---'
	 *         |  `|  \| Dn| Up|                           |Lft|Rgt|  [|  ]|
	 *         `---------------'   ,-------.   ,-------.   `---------------'
	 *                             |Alt|Win|   |Ctl|Alt|
	 *                         ,---+---+---|   |---+---+---.
	 *                         |BSp|Del|Hom|   |PgU|Ent|Spc|
	 *                         | - | - |---|   |---| - | - |
	 *                         | - | - |End|   |PgD| - | - |
	 *                         `-----------'   `-----------'
	 */
	KEYMAP(
	ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SLCK,BRK, TRNS, TRNS,
	EQL, 1,   2,   3,   4,   5,                                 6,   7,   8,   9,   0,   MINS,
	TAB, Q,   W,   E,   R,   T,                                 Y,   U,   I,   O,   P,   BSLS,
	CAPS,A,   S,   D,   F,   G,                                 H,   J,   K,   L,   SCLN,QUOT,
	LSFT,Z,   X,   C,   V,   B,                                 N,   M,   COMM,DOT, SLSH,RSFT,
	     GRV, BSLS,DOWN,UP,                                          LEFT,RGHT,LBRC,RBRC,
	                              LALT,LGUI,          RCTL,RALT,
	                         BSPC,DEL, HOME,          PGUP,ENT, SPC,
	                                   END,           PGDN
	),

	/* 1: Software Dvorak http://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard */
	/*
	KEYMAP(
	ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SLCK,BRK, FN1, FN2,
	EQL, 1,   2,   3,   4,   5,                                 6,   7,   8,   9,   0,   MINS,
	TAB, Q,   W,   E,   R,   T,                                 Y,   U,   I,   O,   P,   BSLS,
	CAPS,A,   S,   D,   F,   G,                                 H,   J,   K,   L,   SCLN,QUOT,
	LSFT,Z,   X,   C,   V,   B,                                 N,   M,   COMM,DOT, SLSH,RSFT,
	     GRV, BSLS,DOWN,UP,                                          LEFT,RGHT,LBRC,RBRC,
	                              LALT,LGUI,          RCTL,RALT,
	                         BSPC,DEL, HOME,          PGUP,ENT, SPC,
	                                   END,           PGDN
	),
	*/

	/* 2: Hardware Dvorak http://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard
	 * ,-----------------------------------.   ,-----------------------------------.
	 * |ESC| F1| F2| F3| F4| F5| F6| F7| F8|   | F9|F10|F11|F12| PS| SL|Brk|Key|Prg|
	 * `-----------------------------------'   `-----------------------------------'
	 *    ,------------------------.                   ,------------------------.
	 *    |   =|  1|  2|  3|  4|  5|                   |  6|  7|  8|  9|  0|   -|
	 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
	 *    | Tab|  '|  ,|  .|  P|  Y|                   |  F|  G|  C|  R|  L|   /|
	 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
	 *    |Caps|  A|  O|  E|  U|  I|                   |  D|  H|  T|  N|  S|   \|
	 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
	 *    |Shft|  ;|  Q|  J|  K|  X|                   |  B|  M|  W|  V|  Z|Shft|
	 *    `----+---+---+---+---+---'                   `---+---+---+---+---+----'
	 *         |  `|  \| Dn| Up|                           |Lft|Rgt|  [|  ]|
	 *         `---------------'   ,-------.   ,-------.   `---------------'
	 *                             |Alt|Win|   |Ctl|Alt|
	 *                         ,---+---+---|   |---+---+---.
	 *                         |BSp|Del|Hom|   |PgU|Ent|Spc|
	 *                         | - | - |---|   |---| - | - |
	 *                         | - | - |End|   |PgD| - | - |
	 *                         `-----------'   `-----------'
	 */
	KEYMAP(
	ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SLCK,BRK, FN1, FN2,
	EQL, 1,   2,   3,   4,   5,                                 6,   7,   8,   9,   0,   MINS,
	TAB, QUOT,COMM,DOT, P,   Y,                                 F,   G,   C,   R,   L,   SLSH,
	CAPS,A,   O,   E,   U,   I,                                 D,   H,   T,   N,   S,   BSLS,
	LSFT,SCLN,Q,   J,   K,   X,                                 B,   M,   W,   V,   Z,   RSFT,
	     GRV, BSLS,DOWN,UP,                                          LEFT,RGHT,LBRC,RBRC,
	                              LALT,LGUI,          RCTL,RALT,
	                         BSPC,DEL, HOME,          PGUP,ENT, SPC,
	                                   END,           PGDN
	),

	/* 2: Mouse/keypad mode
	 * NOTE: see hhkb keymap.c for iWRAP mouse wheel info
	 * ,-----------------------------------.   ,-----------------------------------.
	 * |ESC| F1| F2| F3| F4| F5| F6| F7| F8|   | F9|F10|F11|F12| PS| SL|Brk|Key|Prg|
	 * `-----------------------------------'   `-----------------------------------'
	 *    ,------------------------.                   ,------------------------.
	 *    |    |  1|  2|  3|  4|  5|                   |  6|NmL|  =|  /|  *|    |
	 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
	 *    | Tab|MwL|MwD|McU|MWU|MwR|                   |   |Nm7|Nm8|Nm9|Nm-|    |
	 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
	 *    |Caps|   |McL|McD|McR|   |                   |   |Nm4|Nm5|Nm6|Nm+|    |
	 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
	 *    |Shft|   |Mb1|Mb2|Mb3|   |                   |   |Nm1|Nm2|Nm3|Ent|Shft|
	 *    `----+---+---+---+---+---'                   `---+---+---+---+---+----'
	 *         |   |   | Dn| Up|                           |Lft|Rgt|Nm.|Ent|
	 *         `---------------'   ,-------.   ,-------.   `---------------'
	 *                             |Alt|Win|   |Ctl|Alt|
	 *                         ,---+---+---|   |---+---+---.
	 *                         |BSp|Del|Hom|   |PgU|Ent|Nm0|
	 *                         | - | - |---|   |---| - | - |
	 *                         | - | - |End|   |PgD| - | - |
	 *                         `-----------'   `-----------'
	 */
	KEYMAP(
	ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SLCK,BRK, FN1, FN2,
	TRNS,1,   2,   3,   4,   5,                                 6,   NLCK,PEQL,PSLS,PAST,TRNS,
	TAB, WH_L,WH_D,MS_U,WH_U,WH_R,                              TRNS,P7,  P8,  P9,  PMNS,TRNS,
	CAPS,TRNS,MS_L,MS_D,MS_R,TRNS,                              TRNS,P4,  P5,  P6,  PPLS,TRNS,
	LSFT,TRNS,BTN1,BTN2,BTN3,TRNS,                              TRNS,P1,  P2,  P3,  PENT,RSFT,
	     TRNS,TRNS,DOWN,UP,                                          LEFT,RGHT,PDOT,PENT,
	                              LALT,LGUI,          RCTL,RALT,
	                         BSPC,DEL, HOME,          PGUP,ENT, P0,
	                                   END,           PGDN
	),

	/* N: Layout selector
	 * ,-----------------------------------.   ,-----------------------------------.
	 * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	 * `-----------------------------------'   `-----------------------------------'
	 *    ,------------------------.                   ,------------------------.
	 *    |    | LQ|LSD|LHD|   |   |                   |   |   |   |   |   |    |
	 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
	 *    |    | LQ|   |   |   |   |                   |   |   |   |   |   |    |
	 *    |----+---+---+---+---+---|                   |---+---+---+---+---+----|
	 *    |    |   |LSD|LHD|   |   |                   |   |   |   |   |   |    |
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
     * LQ:  set Qwerty layout
     * LSD: set software Dvorak layout
     * LHD: set hardware Dvorak layout
	 */
	/*
	KEYMAP(
	TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
	TRNS,FN5, FN6, FN7, TRNS,TRNS,                              TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
	TRNS,FN5, TRNS,TRNS,TRNS,TRNS,                              TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
	TRNS,TRNS,FN6, FN7, TRNS,TRNS,                              TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
	TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,                              TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
	     TRNS,TRNS,TRNS,TRNS,                                        TRNS,TRNS,TRNS,TRNS,
	                              TRNS,TRNS,          TRNS,TRNS,
	                         TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,
	                                   TRNS,          TRNS
	),
	*/
};

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
//    [0] = ACTION_LAYER_MOMENTARY(4),
//    [1] = ACTION_LAYER_TAP_KEY(5, KC_SLASH),
//    [2] = ACTION_LAYER_TAP_KEY(6, KC_SCLN),
//    [3] = ACTION_LAYER_MOMENTARY(6),
//    [4] = ACTION_LAYER_MOMENTARY(7),   // to Layout selector
//    [5] = ACTION_DEFAULT_LAYER_SET(0),  // set qwerty layout
//    [6] = ACTION_DEFAULT_LAYER_SET(1),  // set software dvorak layout
//    [7] = ACTION_DEFAULT_LAYER_SET(2),  // set hardware dvorak layout
};
