/* See LICENSE file for copyright and license details. */
#include "fibonacci.c"

/* appearance */
static const char font[]            = "Sans 8";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool statusmarkup      = True;     /* True means use pango markup in status message */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Spotify",     NULL,       NULL,       0,            True,        -1 },
	{ "trayer",        NULL,       NULL,    ~0,        True,    -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[\\]",     dwindle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,                          44,       ACTION##stack,  {.i = INC(+1) } }, \
	{ MOD,                          45,       ACTION##stack,  {.i = INC(-1) } }, \
	{ MOD,                          34,       ACTION##stack,  {.i = PREVSEL } }, \
	{ MOD,                          24,       ACTION##stack,  {.i = 0 } }, \
	{ MOD,                          38,       ACTION##stack,  {.i = 1 } }, \
	{ MOD,                          52,       ACTION##stack,  {.i = 2 } }, \
	{ MOD,                          53,       ACTION##stack,  {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "sakura", NULL };
static const char *termlock[]  = { "slock", NULL };
static const char *volumedown[] = { "amixer","-q", "set", "Master", "5%-", "unmute", NULL };
static const char *volumeup[]   = { "amixer","-q", "set", "Master", "5%+", "unmute", NULL };
static const char *mute[]       = { "amixer","-q", "set", "Master", "toggle", NULL };
static const char *backlightdown[] = { "xbacklight", "-dec", "5", NULL };
static const char *backlightup[]   = { "xbacklight", "-inc", "5", NULL };

static Key keys[] = {
       /* modifier             key    function        argument */
       { 0, 		       232,   spawn,          { .v = backlightdown } },
       { 0, 		       233,   spawn,          { .v = backlightup } }, 
       { 0, 		       122,   spawn,          { .v = volumedown } },
       { 0, 		       123,   spawn,          { .v = volumeup } }, 
       { 0, 		       121,   spawn,          { .v = mute } }, 
       { MODKEY,               113,   viewtoleft,     {0} },
       { MODKEY,               114,   viewtoright,    {0} },
       { MODKEY|ShiftMask,     113,   tagtoleft,      {0} },
       { MODKEY|ShiftMask,     114,   tagtoright,     {0} },
       { MODKEY|ShiftMask,     46,    spawn,          {.v = termlock } },
       { MODKEY,               33,    spawn,          {.v = dmenucmd } }, // p
       { MODKEY|ShiftMask,     36,    spawn,          {.v = termcmd } }, // Return
       { MODKEY,               56,    togglebar,      {0} },             // b
       //{ MODKEY,               44,    focusstack,     {.i = +1 } },      // j
       //{ MODKEY,               45,    focusstack,     {.i = -1 } },      // k
       STACKKEYS(MODKEY,              focus)
       STACKKEYS(MODKEY|ShiftMask,    push)
       { MODKEY,               31,    incnmaster,     {.i = +1 } },      // i
       { MODKEY,               40,    incnmaster,     {.i = -1 } },      // d
       { MODKEY,               43,    setmfact,       {.f = -0.05} },    // h
       { MODKEY,               46,    setmfact,       {.f = +0.05} },    // l
       { MODKEY,               36,    zoom,           {0} },             // Return
       { MODKEY,               23,    view,           {0} },             // Tab
       { MODKEY|ShiftMask,     54,    killclient,     {0} },             // c
       { MODKEY,               28,    setlayout,      {.v = &layouts[0]} }, // t
       { MODKEY,               41,    setlayout,      {.v = &layouts[1]} }, // f
       { MODKEY,               58,    setlayout,      {.v = &layouts[2]} }, // m
       { MODKEY,               25,    setlayout,      {.v = &layouts[3]} }, // m
       { MODKEY,               24,    setlayout,      {.v = &layouts[4]} }, // m
       { MODKEY,               65,    setlayout,      {0} },             // space           
       { MODKEY|ShiftMask,     65,    togglefloating, {0} },             // space
       { MODKEY,               19,    view,           {.ui = ~0 } },     // 0
       { MODKEY|ShiftMask,     19,    tag,            {.ui = ~0 } },     // 0
       { MODKEY,               59,    focusmon,       {.i = -1 } },      // comma
       { MODKEY,               60,    focusmon,       {.i = +1 } },      // period
       { MODKEY|ShiftMask,     59,    tagmon,         {.i = -1 } },      // comma
       { MODKEY|ShiftMask,     60,    tagmon,         {.i = +1 } },      // period
       TAGKEYS(                10,                    0)                 // 1
       TAGKEYS(                11,                    1)                 // 2
       TAGKEYS(                12,                    2)                 // 3
       TAGKEYS(                13,                    3)                 // 4
       TAGKEYS(                14,                    4)                 // 5
       TAGKEYS(                15,                    5)                 // 6
       TAGKEYS(                16,                    6)                 // 7
       TAGKEYS(                17,                    7)                 // 8
       TAGKEYS(                18,                    8)                 // 9
       { MODKEY|ShiftMask,     22,    quit,           {0} },             // backspace

};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

