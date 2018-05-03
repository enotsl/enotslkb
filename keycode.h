
/**
 * @file    keycode.h
 * @author    Enotsl Lee
 * @date      5-3-2018
 *
 * @mainpage  KEYCODE
 */

ifndef KEYCODE_H_
#define KEYCODE_H_

#define KC_TRNS 0

//#define KC_DC1 			17
//#define KC_DC2 			18
//#define KC_DC3 			19
//#define KC_DC4 			20

#define KC_SPACE 32 //' '

#define KC_QUOT 39  //','
#define KC_COMM 44  //','
#define KC_MINUS 45 //'-'
#define KC_DOT 46   //'.'
#define KC_SLSH 47  //'/'
#define KC_0 48     //'0'
#define KC_1 49     //'1'
#define KC_2 50     //'2'
#define KC_3 51     //'3'
#define KC_4 52     //'4'
#define KC_5 53     //'5'
#define KC_6 54     //'6'
#define KC_7 55     //'7'
#define KC_8 56     //'8'
#define KC_9 57     //'9'

#define KC_SCLN 59 //';'

#define KC_EQL 61 //'='

#define KC_LBRC 91 //'['
#define KC_BSLS 92 //'\'
#define KC_RBRC 93 //']'
#define KC_NUHS 96 //'`'
#define KC_A 97    //'a'
#define KC_B 98    //'b'
#define KC_C 99    //'c'
#define KC_D 100   //'d'
#define KC_E 101   //'e'
#define KC_F 102   //'f'
#define KC_G 103   //'g'
#define KC_H 104   //'h'
#define KC_I 105   //'i'
#define KC_J 106   //'j'
#define KC_K 107   //'k'
#define KC_L 108   //'l'
#define KC_M 109   //'m'
#define KC_N 110   //'n'
#define KC_O 111   //'o'
#define KC_P 112   //'p'
#define KC_Q 113   //'q'
#define KC_R 114   //'r'
#define KC_S 115   //'s'
#define KC_T 116   //'t'
#define KC_U 117   //'u'
#define KC_V 118   //'v'
#define KC_W 119   //'w'
#define KC_X 120   //'x'
#define KC_Y 121   //'y'
#define KC_Z 122   //'z'
//

///* Modifiers */
#define KC_LCTRL 128  //KEY_LEFT_CTRL
#define KC_LSHIFT 129 //KEY_LEFT_SHIFT
#define KC_LALT 130   //KEY_LEFT_ALT
#define KC_LGUI 131   //KEY_LEFT_GUI
#define KC_RCTRL 132  //KEY_RIGHT_CTRL
#define KC_RSHIFT 133 //KEY_RIGHT_SHIFT
#define KC_RALT 134   //KEY_RIGHT_ALT
#define KC_RGUI 135   //KEY_RIGHT_GUI

#define KC_ENTER 176  //KEY_RETURN
#define KC_ESC 177    //KEY_ESC
#define KC_BSPACE 178 //KEY_BACKSPACE
#define KC_TAB 179    //KEY_TAB

#define KC_CAPS 193  //KEY_CAPS_LOCK
#define KC_F1 194    //KEY_F1
#define KC_F2 195    //KEY_F2
#define KC_F3 196    //KEY_F3
#define KC_F4 197    //KEY_F4
#define KC_F5 198    //KEY_F5
#define KC_F6 199    //KEY_F6
#define KC_F7 200    //KEY_F7
#define KC_F8 201    //KEY_F8
#define KC_F9 202    //KEY_F9
#define KC_F10 203   //KEY_F10
#define KC_F11 204   //KEY_F11
#define KC_F12 205   //KEY_F12
#define KC_PSCR 206  //  0x46 = 70 + 136 = 206
#define KC_SLCK 207  //  0x47 = 71 + 136 = 207
#define KC_PAUSE 208 //  0x48 = 72 + 136 = 208

#define KC_INSERT 209 //KEY_INSERT
#define KC_HOME 210   //KEY_HOME
#define KC_PGUP 211   //KEY_PAGE_UP
#define KC_DELETE 212 //KEY_DELETE
#define KC_END 213    //KEY_END
#define KC_PGDOWN 214 //KEY_PAGE_DOWN

#define KC_RIGHT 215 //KEY_RIGHT_ARROW
#define KC_LEFT 216  //KEY_LEFT_ARROW
#define KC_DOWN 217  //KEY_DOWN_ARROW
#define KC_UP 218    //KEY_UP_ARROW

#define KC_NUMLOCK 219 //  0x53 = 83 + 136 = 219
#define KC_PSLS 220    //  0x54 = 84 + 136 = 220 Keypad /
#define KC_PAST 221    // 0x55 Keypad *
#define KC_PMNS 222    // 0x56 Keypad -
#define KC_PPLS 223    // 0x57 Keypad +
#define KC_PENT 224    // 0x58 Keypad ENTER5

#define KC_P1 225   // 0x59 Keypad 1 and End
#define KC_P2 226   // 0x5A Keypad 2 and Down Arrow
#define KC_P3 227   // 0x5B Keypad 3 and PageDn
#define KC_P4 228   // 0x5C Keypad 4 and Left Arrow
#define KC_P5 229   // 0x5D Keypad 5
#define KC_P6 230   // 0x5E Keypad 6 and Right Arrow
#define KC_P7 231   // 0x5F Keypad 7 and Home
#define KC_P8 232   // 0x60 Keypad 8 and Up Arrow
#define KC_P9 233   // 0x61 Keypad 9 and PageUp
#define KC_P0 234   // 0x62 Keypad 0 and Insert
#define KC_PDOT 235 // 0x63 Keypad . and Delete
#define KC_NUBS 236 // 0x64 Keyboard Non-US \ and |
//KC_APPLICATION      KC_APP          65 Keyboard Application10
//KC_POWER                            66 Keyboard Power9
#define KC_PEQL 239 // 0x67 Keypad =

//KC_F13                              68 Keyboard F13
//KC_F14                              69 Keyboard F14
//KC_F15                              6A Keyboard F15
//KC_F16                              6B Keyboard F16
//KC_F17                              6C Keyboard F17
//KC_F18                              6D Keyboard F18
//KC_F19                              6E Keyboard F19
//KC_F20                              6F Keyboard F20
//KC_F21                              70 Keyboard F21
//KC_F22                              71 Keyboard F22
//KC_F23                              72 Keyboard F23
//KC_F24                              73 Keyboard F24
//KC_EXECUTE                          74 Keyboard Execute
//KC_HELP                             75 Keyboard Help
//KC_MENU                             76 Keyboard Menu
//KC_SELECT                           77 Keyboard Select
//KC_STOP                             78 Keyboard Stop
//KC_AGAIN                            79 Keyboard Again
//KC_UNDO                             7A Keyboard Undo
//KC_CUT                              7B Keyboard Cut
//KC_COPY                             7C Keyboard Copy
//KC_PASTE                            7D Keyboard Paste
//KC_FIND                             7E Keyboard Find
//KC__MUTE                            7F Keyboard Mute
//#define KC_VOLUP 	    128             // 0x80 128 + 136 = 264 Keyboard Volume Up
//#define KC_VOLDOWN    129             // 0x81 129 + 136 = 265 Keyboard Volume Down
//KC_LOCKING_CAPS                     82 Keyboard Locking Caps Lock12
//KC_LOCKING_NUM                      83 Keyboard Locking Num Lock12
//KC_LOCKING_SCROLL                   84 Keyboard Locking Scroll Lock12
//KC_KP_COMMA         KC_PCMM         85 Keypad Comma27
//KC_KP_EQUAL_AS400                   86 Keypad Equal Sign29
//KC_INT1             KC_RO           87 Keyboard International115,28
//KC_INT2             KC_KANA         88 Keyboard International216
//KC_INT3             KC_JYEN         89 Keyboard International317
//KC_INT4             KC_HENK         8A Keyboard International418
//KC_INT5             KC_MHEN         8B Keyboard International519
//KC_INT6                             8C Keyboard International620
//KC_INT7                             8D Keyboard International721
//KC_INT8                             8E Keyboard International822
//KC_INT9                             8F Keyboard International922
//KC_LANG1                            90 Keyboard LANG125
//KC_LANG2                            91 Keyboard LANG226
//KC_LANG3                            92 Keyboard LANG330
//KC_LANG4                            93 Keyboard LANG431
//KC_LANG5                            94 Keyboard LANG532
//KC_LANG6                            95 Keyboard LANG68
//KC_LANG7                            96 Keyboard LANG78
//KC_LANG8                            97 Keyboard LANG88
//KC_LANG9                            98 Keyboard LANG98
//KC_ALT_ERASE                        99 Keyboard Alternate Erase7
//KC_SYSREQ                           9A Keyboard SysReq/Attention1
//KC_CANCEL                           9B Keyboard Cancel
//KC_CLEAR                            9C Keyboard Clear
//KC_PRIOR                            9D Keyboard Prior
//KC_RETURN                           9E Keyboard Return
//KC_SEPARATOR                        9F Keyboard Separator
//KC_OUT                              A0 Keyboard Out
//KC_OPER                             A1 Keyboard Oper
//KC_CLEAR_AGAIN                      A2 Keyboard Clear/Again
//KC_CRSEL                            A3 Keyboard CrSel/Props
//KC_EXSEL                            A4 Keyboard ExSel

#define KC_FN0 254
#define KC_FN1 253
#define KC_FN2 252
#define KC_FN3 251
#define KC_FN4 250
#define KC_FN5 249
#define KC_FN6 248
#define KC_FN7 247
#define KC_FN8 246
#define KC_FN9 245

#define KC_LMOUSE 244
#define KC_MMOUSE 243
#define KC_RMOUSE 242

#define KC_MLEFT 17
#define KC_MRIGHT 18
#define KC_MUP 19
#define KC_MDOWN 20

//#define KC_MSLEFT 241
//#define KC_MSRIGHT 240
//#define KC_MSUP 239
//#define KC_MSDOWN 238

#endif /* KEYCODE_H_ */
