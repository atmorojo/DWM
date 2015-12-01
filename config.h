/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = { "Stlarch:size=10", "ProFont:size=10", };
static const char dmenufont[] = "-*-profont-medium-r-*-*-12-*-*-*-*-*-*-*" "," "-*-stlarch-*-*-*-*-10-*-*-*-*-*-*-*";

#define NUMCOLORS         4
static const char colors[NUMCOLORS][MAXCOLORS][8] = {
  // border   foreground background
  { "#000033", "#dddddd", "#000033" },  // normal
  { "#000088", "#ffffff", "#000088" },  // selected
  { "#ff0000", "#000000", "#ffff00" },  // urgent/warning  (black on yellow)
  { "#ff0000", "#ffffff", "#ff0000" },  // error (white on red)
  // add more here
};

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" , "5" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Chromium", NULL,       NULL,       1 << 1,       False,       -1 },
    { "Firefox",  NULL,       NULL,       1 << 1,       False,       -1 },
    { "Thunar",   NULL,       NULL,       1 << 2,       False,       -1 },
    { "Gimp",     NULL,       NULL,       1 << 3,       False,       -1 },
    { "Inkscape", NULL,       NULL,       1 << 3,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-p", "\uE06E", "-fn", dmenufont, "-nb", colors[0][2], "-nf", colors[0][1], "-sb", colors[1][2], "-sf", colors[1][1], NULL };

static const char *termcmd[]    = { "urxvtc", NULL };
static const char *shotf[]  = { "maim", "/home/atmorojo/Pictures/Screenshots/$(date %b%d::%H%M%S).png", NULL };
static const char *shotp[]  = { "maim", "-s", "/home/atmorojo/Pictures/Screenshots/$(date %b%d::%H%M%S.png)", NULL };
static const char *volup[]  = { "amixer", "-q", "sset", "Master", "5%+", "unmute", NULL };
static const char *voldown[]    = { "amixer", "-q", "sset", "Master", "5%-", "unmute", NULL };
static const char *volmute[]    = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *mpdnext[]    = { "mpc", "next", NULL };
static const char *mpdprev[]    = { "mpc", "prev", NULL };
static const char *mpdsel[] = { "mpsel", NULL };
static const char *mpdtog[] = { "mptog", NULL };
static const char *lock[]   = { "slock", NULL };
static const char *brightup[]   = { "xbacklight", "+10", NULL };
static const char *brightdown[] = { "xbacklight", "-10", NULL };
static const char *shutup[] = { "shutup", NULL };
static const char *arandr[] = { "arandr", NULL };

static Key keys[] = {
    /* modifier                     key             function        argument */
    { MODKEY,                       XK_b,           togglebar,      {0} },
    { MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,           incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,           incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return,      zoom,           {0} },
    { MODKEY,                       XK_Tab,         view,           {0} },
    { MODKEY|ShiftMask,             XK_c,           killclient,     {0} },
    { MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,           setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,           setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,       setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
    { MODKEY,                       XK_0,           view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,       focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,       tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,      tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask,             XK_q,           quit,           {0} },

    { MODKEY,                       XK_p,           spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return,      spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_Delete,      spawn,          {.v = shutup } },

    TAGKEYS(                        XK_1,                          0)
    TAGKEYS(                        XK_2,                          1)
    TAGKEYS(                        XK_3,                          2)
    TAGKEYS(                        XK_4,                          3)
    TAGKEYS(                        XK_5,                          4)
    TAGKEYS(                        XK_6,                          5)

    { MODKEY,                       XK_Right,       spawn,          {.v = mpdnext } },
    { MODKEY,                       XK_Left,        spawn,          {.v = mpdprev } },
    { 0,                            0x1008ff12,     spawn,          {.v = volmute } },
    { 0,                            0x1008ff11,     spawn,          {.v = voldown } },
    { 0,                            0x1008ff13,     spawn,          {.v = volup } },
    { 0,                            0x1008ff03,     spawn,          {.v = brightdown } },
    { 0,                            0x1008ff02,     spawn,          {.v = brightup } },
    { 0,                            0x1008ff59,     spawn,          {.v = arandr } },
    { 0,                            XK_Print,       spawn,          {.v = shotf } },
    { MODKEY,                       XK_Print,       spawn,          {.v = shotp } },
    { MODKEY,                       XK_grave,       spawn,          {.v = mpdtog } },
    { MODKEY,                       XK_equal,       spawn,          {.v = mpdsel } },
    { MODKEY|ShiftMask,             XK_l,           spawn,          {.v = lock } },
    { MODKEY|ShiftMask,             XK_Delete,      spawn,          {.v = shutup } },
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

