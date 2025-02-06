# Keyboard Line Art in QMK `keymap.c`

I recently stumbled on [a comment in r/ErgoMechKeyboards][henrebotha-comment]
by [u/henrebotha][u-henrebotha]:

> That's quite nice, though I'm emotionally attached to my contrived layout
> comments. [https://github.com/henrebotha/…/keymap.c#L47][henrebotha-keymap]

"Contrived layout comments"? Curious, I clicked on the link and was greeted with
something amazing. A keymap which uses line art characters to *look like the
actual keyboard*.

``` text
  [LAYER_HOME] = LAYOUT_ergodox_pretty(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────╮      ╭───────┬───────┬───────┬───────┬───────┬───────┬───────╮
    KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,TG(1)  ,       XXXXXXX,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_BSPC,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┤      ├───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,TG(5)  ,       XXXXXXX,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_BSLS,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┤      ├───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    CTL_ESC,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,                       KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
// ├───────┼───────┼───────┼───────┼───────┼───────┤       │      │       ├───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LGUI,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_MINS,       KC_EQL ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_RGUI,
// ├───────┼───────┼───────┼───────┼───────┼───────┴───────╯      ╰───────┴───────┼───────┼───────┼───────┼───────┼───────┤
    KC_HYPR,KC_TASK,KC_LEAD,OSL(4) ,OSL(3) ,                                       OSL(3) ,OSL(4) ,KC_LEAD,XXXXXXX,KC_HYPR,
// ╰───────┴───────┴───────┴───────┴───────╯ ╭───────┬───────╮  ╭───────┬───────╮ ╰───────┴───────┴───────┴───────┴───────╯
                                              KC_MUTE,KC_VOLU,   KC_MPRV,KC_MNXT,
//                                   ╭───────┼───────┼───────┤  ├───────┼───────┼───────╮
                                                      KC_VOLD,   KC_MPLY,
//                                   │       │       ├───────┤  ├───────┤       │       │
                                      LSFT_TA,KC_SPC ,KC_LALT,   KC_RALT,KC_ENT ,RSFT_MI
//                                   ╰───────┴───────┴───────╯  ╰───────┴───────┴───────╯
  ),
```

Needless to say, I was quite inspired and spent the next hour fiddling with my
keymap rather than doing anything productive. I ended up going through a few
iterations, shown below, before settling on something which is as close to
perfect as I think I'm likely to manage.

[henrebotha-comment]: https://www.reddit.com/r/ErgoMechKeyboards/comments/16vuj4s/comment/k2uc0gg/
[u-henrebotha]: https://www.reddit.com/user/henrebotha/
[henrebotha-keymap]: https://github.com/henrebotha/qmk_keymap/blob/191863c/src/keymaps/henrebotha/keymap.c#L47

## No line art

This is where I started: keys placed in their approximate location, but arranged
in rigid columns. It doesn't look anything like an actual keyboard and the lines
are too long to see without scrolling (156 characters wide), even on my sizable
monitor.

``` text
[BASE] = LAYOUT_tkl_ansi(
    KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_MUTE, KC_PSCR, KC_SCRL, KC_CALC,
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_INS , KC_HOME, KC_PGUP,
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL , KC_END , KC_PGDN,
    KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,          KC_ENT ,
    KC_LSFT,          KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT,          KC_UP  ,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC ,                            KC_RALT, KC_RGUI, MO(FN) , KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
),
```

## Basic rectangles

Already a decent improvement! Adding a line art grid makes it look more
plausibly like a keyboard, if an atypical one. In particular, this gives the
rows "room to breathe" so that they don't run together as much and also
highlights the wide keys and arrow block a bit.

``` text
[BASE] = LAYOUT_tkl_ansi(
//┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_MUTE, KC_PSCR, KC_SCRL, KC_CALC,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_INS , KC_HOME, KC_PGUP,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL , KC_END , KC_PGDN,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┴────────┴────────┘
    KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,          KC_ENT ,
//├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼─────────────────┤        ┌────────┐
    KC_LSFT,          KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT,          KC_UP  ,
//├────────┬────────┼────────┼────────┴────────┴────────┴────────┴────────┴────────┴────────┼────────┼────────┼────────┬────────┼────────┼────────┼────────┐
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC ,                            KC_RALT, KC_RGUI, MO(FN) , KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
//└────────┴────────┴────────┴──────────────────────────────────────────────────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘
),
```

## Simple blocks

Looking at my first attempt, I immediately found myself wanting to be able to
see gaps between keys. The keyboard-spanning ones (below the F-key row and to
the left of the arrow keys) were easy enough, but my keyboard's encoder
(`KC_MUTE` in the map) made the first row too cramped to render the F-key groups
while the keys were still laid out in a grid.

``` text
[BASE] = LAYOUT_tkl_ansi(
//┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐┌────────┬────────┬────────┐
    KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_MUTE,  KC_PSCR, KC_SCRL, KC_CALC,
//└────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘└────────┴────────┴────────┘
//┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐┌────────┬────────┬────────┐
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,  KC_INS , KC_HOME, KC_PGUP,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,  KC_DEL , KC_END , KC_PGDN,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┤└────────┴────────┴────────┘
    KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,          KC_ENT ,
//├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼─────────────────┤         ┌────────┐
    KC_LSFT,          KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT,           KC_UP  ,
//├────────┬────────┼────────┼────────┴────────┴────────┴────────┴────────┴────────┴────────┼────────┼────────┼────────┬────────┤┌────────┼────────┼────────┐
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC ,                            KC_RALT, KC_RGUI, MO(FN) , KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT
//└────────┴────────┴────────┴──────────────────────────────────────────────────────────────┴────────┴────────┴────────┴────────┘└────────┴────────┴────────┘
),
```

## Short aliases

Varying the key widths would give me the extra space I needed and improve the
look a lot, too. But it would make the lines even longer, so it was time to
address that. I set up four-character `#define`s for all of my keys to narrow
the rows. I still gave each key padding on each side, thinking that cramming
them all together like that would be unreadable. Fortunately, dropping from
seven-character labels to four-character ones brought the lines down to
manageable length (123 characters; my editor can display 130+ easily enough)
even with the padding. As an unexpected bonus, making the keys narrower also
improved their look by making them less distorted-looking in the horizontal
direction.

``` text
[BASE] = LAYOUT_tkl_ansi(
//┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐┌──────┬──────┬──────┐
    ESC_ , _F1_ , _F2_ , _F3_ , _F4_ , _F5_ , _F6_ , _F7_ , _F8_ , _F9_ , F10_ , F11_ , F12_ , MUTE ,  PSCR , SCRL , CALC ,
//└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘└──────┴──────┴──────┘
//┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐┌──────┬──────┬──────┐
    GRV_ , _1__ , _2__ , _3__ , _4__ , _5__ , _6__ , _7__ , _8__ , _9__ , _0__ , MINU , EQL_ , BACK ,  INS_ , HOME , PGUP ,
//├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤├──────┼──────┼──────┤
    TAB_ , _Q__ , _W__ , _E__ , _R__ , _T__ , _Y__ , _U__ , _I__ , _O__ , _P__ , LBRC , RBRC , BSLS ,  DEL_ , END_ , PGDN ,
//├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┴──────┤└──────┴──────┴──────┘
    CAPS , _A__ , _S__ , _D__ , _F__ , _G__ , _H__ , _J__ , _K__ , _L__ , SEMI , QUOT ,    ENT_     ,
//├──────┴──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼─────────────┤       ┌──────┐
       SHF_     , _Z__ , _X__ , _C__ , _V__ , _B__ , _N__ , _M__ , COMM , DOT_ , SLSH ,    _SHF     ,         _UP_ ,
//├──────┬──────┼──────┼──────┴──────┴──────┴──────┴──────┴──────┴──────┼──────┼──────┼──────┬──────┤┌──────┼──────┼──────┐
    CTL_ , GUI_ , ALT_ ,                      SPC_                      , _ALT , _GUI , H_FN , _CTL ,  LEFT , DOWN , RGHT
//└──────┴──────┴──────┴────────────────────────────────────────────────┴──────┴──────┴──────┴──────┘└──────┴──────┴──────┘
),
```

## Proportional keys

Adding the gaps in the first row introduced additional horizontal space to the
main keyboard which needed distributed to the keys. I resisted the urge to
obsess over making all the keys *exactly* the right width, but after a lot of
fiddling and "that looks about right", I think the result looks simply
*glorious*. 🤩

``` text
[BASE] = LAYOUT_tkl_ansi(
//┌──────┐┌──────┬──────┬──────┬──────┐┌──────┬──────┬──────┬──────┐┌──────┬──────┬──────┬──────┐┌──────┐┌──────┬──────┬──────┐
    ESC_ ,  _F1_ , _F2_ , _F3_ , _F4_ ,  _F5_ , _F6_ , _F7_ , _F8_ ,  _F9_ , F10_ , F11_ , F12_ ,  MUTE ,  PSCR , SCRL , CALC ,
//└──────┘└──────┴──────┴──────┴──────┘└──────┴──────┴──────┴──────┘└──────┴──────┴──────┴──────┘└──────┘└──────┴──────┴──────┘
//┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────────┐┌──────┬──────┬──────┐
    GRV_ , _1__ , _2__ , _3__ , _4__ , _5__ , _6__ , _7__ , _8__ , _9__ , _0__ , MINU , EQL_ ,   BACK   ,  INS_ , HOME , PGUP ,
//├──────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────────┤├──────┼──────┼──────┤
     TAB_  , _Q__ , _W__ , _E__ , _R__ , _T__ , _Y__ , _U__ , _I__ , _O__ , _P__ , LBRC , RBRC ,  BSLS  ,  DEL_ , END_ , PGDN ,
//├────────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴────────┤└──────┴──────┴──────┘
      CAPS   , _A__ , _S__ , _D__ , _F__ , _G__ , _H__ , _J__ , _K__ , _L__ , SEMI , QUOT ,    ENT_     ,
//├──────────┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴─────────────┤       ┌──────┐
        SHF_     , _Z__ , _X__ , _C__ , _V__ , _B__ , _N__ , _M__ , COMM , DOT_ , SLSH ,      _SHF      ,         _UP_ ,
//├────────┬─────┴──┬───┴──┬───┴──────┴──────┴──────┴──────┴──────┴─────┬┴─────┬┴──────┴┬──────┬────────┤┌──────┼──────┼──────┐
     CTL_  ,  GUI_  , ALT_ ,                     SPC_                   , _ALT ,  _GUI  , H_FN ,  _CTL  ,  LEFT , DOWN , RGHT
//└────────┴────────┴──────┴────────────────────────────────────────────┴──────┴────────┴──────┴────────┘└──────┴──────┴──────┘
),
```
