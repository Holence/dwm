/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:pixelsize=14:style=Bold" };
static const char dmenufont[]       = "monospace:pixelsize=14:style=Bold";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_main[]        = "#2D3644";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_main,  col_main  },
};

/* systray patch */
static const unsigned int systraypinning = 0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst = 1; /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1; /* 0 means no systray */

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
	/*  use command `xprop` and click on any window, then find these attributes:
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	// { "Gimp",     NULL,       NULL,       0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ NULL,       "qemu",     NULL,       0,            1,           -1 },
	{ NULL, "io.github.cboxdoerfer.FSearch", "FSearch", 0, 1, -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[D]",      deck },
};

/* key definitions */
// use `xmodmap -pm` to check modifier map
#define NOMODKEY NoEventMask
#define MODKEY Mod4Mask // Win
#define ALTKEY Mod1Mask // Alt

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// Win+p open dmenu
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_main, "-sf", col_gray4, "-p", " Dmenu", NULL };
// Win+Shit+Enter open terminal
static const char *termcmd[]  = { "xfce4-terminal", NULL };
// Win+e open files
static const char *filescmd[]  = { "thunar", NULL };
// Win+q open fsearch
static const char *fsearchcmd[]  = { "fsearch", NULL };
/* volume */
static const char *volume_down[]  = { "amixer", "set", "Master", "5%-", NULL };
static const char *volume_up[]  = { "amixer", "set", "Master", "5%+", NULL };
static const char *volume_toggle[]  = { "amixer", "set", "Master", "toggle", NULL };
/* brightness */
static const char *brightness_down[] = { "xbacklight", "-dec", "10", NULL };
static const char *brightness_up[]   = { "xbacklight", "-inc", "10", NULL };
/* screenshot */
static const char *screenshot[] = { "flameshot", "gui", NULL };


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },   // Win+p open dmenu
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },    // Win+Shit+Enter open terminal
	{ MODKEY,                       XK_e,      spawn,          {.v = filescmd } },   // Win+e open files
	{ MODKEY,                       XK_q,      spawn,          {.v = fsearchcmd } }, // Win+q open fsearch
	
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	{ MODKEY,                       XK_bracketright,      focusstack,     {.i = +1 } }, // `Win` + `]`
	{ MODKEY,                       XK_bracketleft,       focusstack,     {.i = -1 } }, // `Win` + `[`
	{ ALTKEY,                       XK_Tab,               focusstack,     {.i = -1 } }, // `Alt` + `Tab`
	
	{ MODKEY,                       XK_equal,  incnmaster,     {.i = +1 } }, // `Win` + `+`
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = -1 } }, // `Win` + `-`
	
	{ MODKEY,                       XK_semicolon,      setmfact,       {.f = -0.02} }, // `Win` + `;`
	{ MODKEY,                       XK_apostrophe,     setmfact,       {.f = +0.02} }, // `Win` + `'`
	
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	
	// /usr/include/X11/XF86keysym.h
	{ NoEventMask,                  XF86XK_AudioMute,          spawn, {.v = volume_toggle } },
	{ NoEventMask,                  XF86XK_AudioLowerVolume,   spawn, {.v = volume_down } },
	{ NoEventMask,                  XF86XK_AudioRaiseVolume,   spawn, {.v = volume_up } },
	
	{ NoEventMask,                  XF86XK_MonBrightnessDown,  spawn, {.v = brightness_down } },
	{ NoEventMask,                  XF86XK_MonBrightnessUp,    spawn, {.v = brightness_up } },
	
	{ MODKEY,                       XK_Delete,                 spawn, {.v = screenshot } },
	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

