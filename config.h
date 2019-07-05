/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=9" };
static const char dmenufont[]       = "monospace:size=12";
static const char dmenulines[]      = "20";
static const char bgcol[]           = "#06101c";
static const char bordercol[]       = "#1e344e";
static const char textcol[]         = "#afafaf";
static const char selectedcol[]     = "#ffcc00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { textcol, bgcol, bordercol },
	[SchemeSel]  = { selectedcol, bgcol,  selectedcol  },
};

/* tagging */
static const char *tags[] = { "term", "code", "web", "slack", "games", "extra" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance    title        tags mask     isfloating   monitor */
	{ "Alacritty",            NULL,       NULL,        1 << 0,       0,           -1 },
	{ "Firefox",              NULL,       NULL,        1 << 2,       0,           -1 },
	{ "code-oss",             NULL,       NULL,        1 << 1,       0,           -1 },
	{ "Google-chrome",        NULL,       NULL,        1 << 2,       0,           -1 },
	{ "Google-chrome",        NULL,       "^DevTools", 1 << 4,       0,           -1 },
	{ "Slack",                NULL,       NULL,        1 << 3,       0,           -1 },
	{ "Steam",                NULL,       NULL,        1 << 4,       1,           -1 },
	{ "Pavucontrol",          NULL,       NULL,        0,            1,           -1 },
	{ "Arandr",               NULL,       NULL,        0,            1,           -1 },
	{ "Next",                 NULL,       NULL,        1 >> 2,       0,           -1 },
	{ "Blueman-manager",      NULL,       NULL,        0,            1,           -1 },
	{ "Blueman-assistant",    NULL,       NULL,        0,            1,           -1 },
	{ "Lutris",               NULL,       NULL,        1 << 4,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Include XF86 keys */
#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", bgcol, "-nf", textcol, "-sb", bgcol, "-sf", selectedcol, "-l", dmenulines, NULL };
/*static const char *clipmenucmd[] = { "/usr/bin/clipmenu", "-i", "-fn", dmenufont, "-nb", bgcol, "-nf", textcol, "-sb", bgcol, "-sf", selectedcol, "-l", dmenulines, NULL };*/
static const char *bitwardencmd[] = { "$HOME/.dwm/bitwarden.sh", NULL };
static const char *termcmd[] = { "alacritty", NULL };
static const char *calcmd[] = { "=", "--dmenu=dmenu", "-m", dmenumon, "-fn", dmenufont, "-nb", bgcol, "-nf", textcol, "-sb", bgcol, "-sf", selectedcol, "-l", dmenulines, NULL };
/*static const char *logoutusercmd[] = { "~/.dwm/system.sh logout", NULL };*/

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          SHCMD("$HOME/.dwm/favorite-apps.sh") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = bitwardencmd } },
	{ MODKEY|ControlMask,           XK_l,      spawn,          SHCMD("$HOME/.dwm/lock.sh") },
	/*{ MODKEY|ControlMask,           XK_o,       spawn,         {.v = logoutusercmd } },*/
	{ MODKEY|ControlMask|ShiftMask, XK_BackSpace, quit,        {0} },
    { MODKEY|ControlMask,           XK_BackSpace, spawn,       SHCMD("$HOME/.dwm/system.sh") },
	/*{ Mod1Mask|ControlMask,         XK_v,      spawn,          {.v = clipmenucmd } },*/
	{ Mod1Mask|ControlMask,         XK_v,      spawn,          SHCMD("CM_DIR=$HOME/.cache/clipmenu /usr/bin/clipmenu -i -fn monospace:size=13 -nb '#06101c' -nf '#afafaf' -sb '#06101c' -sf '#ffcc00' -l 30") },
	{ 0,                            XK_Print,  spawn,          SHCMD("$HOME/bin/screenshot.sh") },
	{ MODKEY|ControlMask,           XK_Print,  spawn,          SHCMD("$HOME/bin/screenshot.sh select") },
	{ MODKEY,                       XK_Print,  spawn,          SHCMD("$HOME/bin/screenshot.sh select-cb") },
	{ 0,             XF86XK_AudioLowerVolume,  spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") },
	{ 0,             XF86XK_AudioRaiseVolume,  spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },
	{ 0,             XF86XK_AudioMute,         spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ toggle") },
	{ 0,             XF86XK_Calculator,        spawn,          {.v = calcmd } },
	{ 0,             XF86XK_HomePage,          spawn,          SHCMD("colorpicker --preview --one-shot --short | c") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

