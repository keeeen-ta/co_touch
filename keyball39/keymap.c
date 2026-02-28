/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "lib/co_touch/co_touch.h"

enum keymap_layers {
  _ENG_,
  _JPN_,
  _SYM_,
  _NUM_,
  _CMD_,
};

// Special key codes for shorthand
#define   ___ENG_   TO(_ENG_)
#define   ___JPN_   TO(_JPN_)
#define   ___T_L3   KC_ESC
#define   ___T_L2   LT(_CMD_, KC_TAB)
#define   ___T_L1   LT(_NUM_, KC_SPC)
#define   ___T_R1   LT(_SYM_, KC_BSPC)
#define   ___T_R2   SFT_T(KC_ENT)
#define   ___T_R3   KC_ESC
#define   ___COMM   CTL_T(KC_COMM)
#define   ___DOT_   CTL_T(KC_DOT)
#define   ___SENT   S(KC_ENT)       // Shift + Enter
#define   ___AENT   A(KC_ENT)       // ALT + Enter
#define   ___INCR   C(KC_A)         // 加算
#define   ___DECR   C(KC_X)         // 減算
#define   ___CUT_   C(KC_X)         // 切り取り
#define   ___COPY   C(KC_C)         // コピー
#define   ___PSTE   C(KC_V)         // 貼り付け
#define   ___COUT   C(KC_SLSH)      // コメントアウト
#define   ___CPDR   A(KC_X)         // コピーダイレクト
#define   ___CPCM   A(KC_C)         // コピー定型文
#define   ___CPHS   A(KC_V)         // コピー履歴
#define   ___SRCH   A(KC_SPC)       // 全検索
#define   ___NEXT   C(KC_PGUP)      // 次のタブ
#define   ___PREV   C(KC_PGDN)      // 前のタブ
#define   ___UNDO   C(KC_Z)         // Undo
#define   ___REDO   C(S(KC_Z))      // Redo
#define   ___ALL_   C(KC_A)         // 全選択
#define   ___S_UP   S(KC_UP)        // Shift + ↑
#define   ___S_DN   S(KC_DOWN)      // Shift + ↓
#define   ___S_LT   S(KC_LEFT)      // Shift + ←
#define   ___S_RT   S(KC_RGHT)      // Shift + →
#define   ___NEW_   C(KC_N)         // 新規作成
#define   ___CLSE   C(KC_W)         // 閉じる
#define   ___SAVE   C(KC_S)         // 保存
#define   ___FIND   C(KC_F)         // 検索
#define   ___EXPL   G(KC_E)         // エクスプローラ
#define   ___LOCK   G(KC_L)         // ロック

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_ENG_] = LAYOUT_universal(
    KC_Q     , KC_V     , KC_S     , KC_F     , JP_COLN  ,                            JP_SCLN  , KC_U     , KC_I     , KC_R     , KC_K     ,
    KC_G     , KC_T     , ___COMM  , KC_E     , KC_O     ,                            KC_C     , KC_A     , ___DOT_  , KC_N     , KC_J     ,
    KC_B     , KC_L     , KC_M     , KC_H     , KC_W     ,                            KC_X     , KC_D     , KC_P     , KC_Y     , KC_Z     ,
    ___ENG_  , _______  , _______  , ___T_L3  , ___T_L2  , ___T_L1  ,      ___T_R1  , ___T_R2  , ___T_R3  , _______  , _______  , ___JPN_
  ),

  [_JPN_] = LAYOUT_universal(
    CT_00    , CT_01    , CT_02    , CT_03    , CT_04    ,                            CT_05    , CT_06    , CT_07    , CT_08    , CT_09    ,
    CT_10    , CT_11    , CT_12    , CT_13    , CT_14    ,                            CT_15    , CT_16    , CT_17    , CT_18    , CT_19    ,
    CT_20    , CT_21    , CT_22    , CT_23    , CT_24    ,                            CT_25    , CT_26    , CT_27    , CT_28    , CT_29    ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [_SYM_] = LAYOUT_universal(
    JP_LABK  , JP_LBRC  , JP_LPRN  , JP_LCBR  , _______  ,                            JP_GRV   , JP_RCBR  , JP_RPRN  , JP_RBRC  , JP_RABK  ,
    _______  , _______  , ___COUT  , ___S_UP  , ___NEXT  ,                            JP_DQUO  , JP_HASH  , KC_QUES  , JP_PIPE  , JP_TILD  ,
    _______  , ___S_LT  , ___S_RT  , ___S_DN  , ___PREV  ,                            JP_QUOT  , JP_AMPR  , JP_CIRC  , JP_AT    , _______  ,
    CT_PW1   , _______  , _______  , _______  , CT_TAB   , ___SRCH  ,      _______  , _______  , _______  , _______  , _______  , _______ 
  ),

  [_NUM_] = LAYOUT_universal(
    _______  , JP_SLSH  , JP_ASTR  , _______  , _______  ,                            _______  , KC_4     , KC_5     , KC_6     , KC_7     ,
    JP_BSLS  , JP_EQL   , JP_EXLM  , JP_PLUS  , _______  ,                            KC_8     , KC_9     , KC_1     , KC_2     , KC_3     ,
    _______  , JP_PERC  , JP_DLR   , JP_MINS  , JP_UNDS  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,     ___INCR   , KC_0     , ___DECR  , _______  , _______  , _______
  ),

  [_CMD_] = LAYOUT_universal(
    ___EXPL  , ___CLSE  , ___SAVE  , ___FIND  , ___LOCK  ,                            _______  , KC_F4    , KC_F5    , KC_F6    , KC_F7    ,
    KC_BTN2  , KC_APP   , KC_BTN1  , KC_UP    , KC_PGUP  ,                            KC_F8    , KC_F9    , KC_F1    , KC_F2    , KC_F3    ,
    ___UNDO  , KC_LEFT  , KC_RGHT  , KC_DOWN  , KC_PGDN  ,                            ___CPHS  , ___CUT_  , ___PSTE  , ___COPY  , ___CPCM  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      KC_DEL   , ___AENT  , ___SENT  , _______  , _______  , CT_PW2 
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  keyball_set_scroll_mode(get_highest_layer(state) == _SYM_);

  switch (get_highest_layer(state)) {
    case _ENG_:
      tap_code16(KC_LNG2);
      break;
    case _JPN_:
      tap_code16(KC_LNG1);
      break;
    default:
      break;
  }

  return state;
}

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_ESC:
      if (record->event.pressed) {
        layer_off(_JPN_);
        layer_on(_ENG_);
        tap_code16(KC_ESC);
        return false;
      }
      break;
    case CT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case KC_UP:
    case KC_DOWN:
    case KC_LEFT:
    case KC_RGHT:
      if (record->event.pressed) {
        if (is_alt_tab_active) {
          alt_tab_timer = timer_read();
        }
      }
      break;
    case CT_PW1:
      return false;
    case CT_PW2:
      return false;
  }

  // こだち配列
  if (get_highest_layer(layer_state) == _JPN_) {
    return process_cotouch(keycode, record);
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
