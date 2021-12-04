/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 20;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
//static const char *fonts[]          = { 
    //"Fixedsys Excelsior:size=8:antialias=true:hinting=true",
    //"-wuncon-siji-medium-r-normal--10-100-75-75-c-80-iso10646-1",
    //"-*-tamsyn-medium-r-normal-*-12-*-*-*-*-*-*-1"
//};
static const char *fonts[]          = {
    "MesloLGS NF:size=7",
    "siji:size=10"
};
//static const char *fonts[]          = {
    //"Fixedsys Excelsior:size=8:antialias=true:hinting=true",
    //"MesloLGS NF:size=12:antialias=true:hinting:true"
//};
/*static const char *fonts[]          = { "monospace:size=9" };*/
static const char dmenufont[]       = "MesloLGS NF:size=7:antialias=true:hinting:true";
static const char dmenulines[]      = "20";
static const char bgcol[]           = "#06101c";
static const char bordercol[]       = "#06101c";
static const char textcol[]         = "#afafaf";
static const char selectedcol[]     = "#ffcc00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { textcol, bgcol, bordercol },
	[SchemeSel]  = { selectedcol, bgcol,  selectedcol  },
};

/* tagging */
static const char *tags[] = { "term", "code", "web", "social", "games", "extra", "music" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance      title        tags mask     isfloating   monitor */
	{ NULL,                   "ncmpcpp",    "Music",     0,            1,           -1 },
	{ "Alacritty",            "Alacritty",  NULL,        1 << 0,       0,           -1 },
	{ "firefox",              NULL,         NULL,        1 << 2,       0,           -1 },
	{ "code-oss",             NULL,         NULL,        1 << 1,       0,           -1 },
	{ "Google-chrome",        NULL,         NULL,        1 << 2,       0,           -1 },
	{ "Google-chrome",        NULL,         "^DevTools", 1 << 2,       0,           -1 },
	{ "qutebrowser",          NULL,         NULL,        1 << 2,       0,           -1 },
	{ "Brave-browser",        NULL,         NULL,        1 << 2,       0,           -1 },
	{ "qb-url-edit",          NULL,         NULL,        1 << 2,       1,           -1 },
	{ "Slack",                NULL,         NULL,        1 << 3,       0,           -1 },
	{ "discord",              NULL,         NULL,        1 << 3,       0,           -1 },
	{ "Steam",                NULL,         NULL,        1 << 4,       0,           -1 },
	{ "mpv",                  NULL,         NULL,        1 << 7,       0,           -1 },
	{ NULL,        	          NULL,         "Steam",     1 << 4,       1,           -1 },
	{ "Pavucontrol",          NULL,         NULL,        0,            1,           -1 },
	{ "Arandr",               NULL,         NULL,        0,            1,           -1 },
	{ "Blueman-manager",      NULL,         NULL,        0,            1,           -1 },
	{ "Blueman-assistant",    NULL,         NULL,        0,            1,           -1 },
	{ "Lutris",               NULL,         NULL,        1 << 4,       1,           -1 },
	{ "Wine",                 NULL,         NULL,        1 << 4,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
static const char *termcmd[] = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
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
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,           XK_Escape, quit,        {0} },
    { MODKEY|ControlMask|ShiftMask, XK_Escape, quit,        {1} },
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
