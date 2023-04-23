/* appearance */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"
#define MENU "bemenu"

static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const float bordercolor[]           = {0.5, 0.5, 0.5, 1.0};
static const float focuscolor[]            = {1.0, 0.0, 0.0, 1.0};
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1, 0.1, 0.1, 1.0};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* app_id		title		tags mask	isfloating	isterm		noswallow	monitor		scratchkey*/
	/* examples:
	{ "Gimp",		NULL,		0,		1,		0,		1,		-1 },
	*/
	{ "Chromium",		NULL,		1 << 1,		0,		0,		1,		-1 },
	{ TERMCLASS,		NULL,		0,		0,		1,		0,		-1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = "caps:escape",
};

static const int repeat_rate = 50;
static const int repeat_delay = 300;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { TERMINAL, NULL };
static const char *menucmd[] = { "bemenu-run", NULL };
//static const char *menucmd[] = { "dmenu-wl_run", "-fn", "monospace", "-nb", "#080808","-nf", "#f9f5d67","-sb","#202020","-sf","#f9f5d7", NULL };

/* named scratchpads - First arg only serves to match against key in rules*/
//static const char *spterm[] = { "s", TERMINAL, "-t", "scratchpad", "-w", "120x34", NULL };
static const char *scratchpadcmd[] = { "s", TERMINAL, "-t", "scratchpad", "-w", "120x34", NULL };
//const char *spterm[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };



static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier			key			function        argument */
	{ MODKEY,			XKB_KEY_r,		spawn,          {.v = menucmd} },
	{ MODKEY,			XKB_KEY_x,		spawn,          {.v = termcmd} },

	{ MODKEY,			XKB_KEY_b,		toggle_visibility, {0}},
	{ MODKEY,			XKB_KEY_j,		focusstack,     {.i = +1} },
	{ MODKEY,			XKB_KEY_k,		focusstack,     {.i = -1} },
	{ MODKEY,			XKB_KEY_i,		incnmaster,     {.i = +1} },
	{ MODKEY,			XKB_KEY_d,		incnmaster,     {.i = -1} },
	{ MODKEY,			XKB_KEY_h,		setmfact,       {.f = -0.05} },
	{ MODKEY,			XKB_KEY_l,		setmfact,       {.f = +0.05} },
//	{ MODKEY,			XKB_KEY_Return,		zoom,           {0} },
	{ MODKEY,			XKB_KEY_Tab,		view,           {0} },
	{ MODKEY,			XKB_KEY_q,		killclient,     {0} },
	{ MODKEY,			XKB_KEY_t,		setlayout,      {.v = &layouts[0]} },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_T,		setlayout,      {.v = &layouts[1]} },
	{ MODKEY,			XKB_KEY_y,		setlayout,      {.v = &layouts[2]} },

//	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_X,		togglescratch,  {.v = scratchpadcmd } },
//	{ MODKEY,			XKB_KEY_space,		setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_Return,		togglefloating, {0} },
	{ MODKEY,			XKB_KEY_f,		togglefullscreen,{0} },
	{ MODKEY,			XKB_KEY_0,		view,           {.ui = ~0} },
	{ MODKEY,			XKB_KEY_s,		togglesticky,	{0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_parenright,	tag,            {.ui = ~0} },
	{ MODKEY,			XKB_KEY_comma,		focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,			XKB_KEY_period,		focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_less,		tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_greater,	tagmon,         {.i = WLR_DIRECTION_RIGHT} },



	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_L,		spawn,		SHCMD("swaylock -i ~/.local/share/bg") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_B,		spawn,		SHCMD("wtype $(grep -v '^#'  ~/.config/bookmarks | bemenu -i -l 10 | cut -d' ' -f1)") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_S,		spawn,		SHCMD("togglesk") },
//	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_s,		spawn,		SHCMD("sysact") },
	{ MODKEY,			XKB_KEY_w,		spawn,		SHCMD("chromium --enable-features=UseOzonePlatform --ozone-platform=wayland") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_W,		spawn,		SHCMD("watchyt") },
	{ MODKEY,			XKB_KEY_e,		spawn,		SHCMD(TERMINAL " -e lf ~/") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_W,		spawn,		SHCMD(TERMINAL " -e thunar ~/") },
	{ MODKEY,			XKB_KEY_n,		spawn,		SHCMD(TERMINAL " -e nmtui") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_N,		spawn,		SHCMD(TERMINAL " -e newsboat") },
	{ MODKEY,			XKB_KEY_m,		spawn,		SHCMD(TERMINAL " -e ncmpcpp") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_M,		spawn,		SHCMD(TERMINAL " -e neomutt") },
	{ MODKEY,			XKB_KEY_z,		spawn,		SHCMD(TERMINAL " -e watchv") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_Z,		spawn,		SHCMD("qmusic") },
	{ MODKEY,			XKB_KEY_space,		spawn,		SHCMD("mpc toggle") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_space,		spawn,		SHCMD("qsongs") },
	{ MODKEY,			XKB_KEY_v,		spawn,		SHCMD("btcon") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_V,		spawn,		SHCMD("btdcon") },
	{ MODKEY,			XKB_KEY_c,		spawn,		SHCMD(TERMINAL " -e camtoggle") },
//	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_C,		spawn,		SHCMD("") },
	{ MODKEY,			XKB_KEY_a,		spawn,		SHCMD(TERMINAL " -e android-file-transfer") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_A,		spawn,		SHCMD("dla") },
	{ MODKEY,			XKB_KEY_Up,		spawn,		SHCMD("pamixer --allow-boost -i 5") },
//	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_Up,		spawn,		SHCMD("randr") },
	{ MODKEY,			XKB_KEY_Down,		spawn,		SHCMD("pamixer --allow-boost -d 5") },
//	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_Down,		spawn,		SHCMD("randr") },
	{ MODKEY,			XKB_KEY_p,		spawn,		SHCMD("flameshot gui") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_P,		spawn,		SHCMD("passes") },
	{ MODKEY,			XKB_KEY_Print,		spawn,		SHCMD("dmenurecord") },
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_Print,		spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XKB_KEY_Left,		spawn,		SHCMD("mpc next") },
//	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_Left,		spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XKB_KEY_Right,		spawn,		SHCMD("mpc prev") },
//	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_Right,		spawn,		SHCMD("dmenurecord kill") },

	TAGKEYS(          XKB_KEY_1,	XKB_KEY_exclam,				0),
	TAGKEYS(          XKB_KEY_2,	XKB_KEY_at,				1),
	TAGKEYS(          XKB_KEY_3,	XKB_KEY_numbersign,			2),
	TAGKEYS(          XKB_KEY_4,	XKB_KEY_dollar,				3),
	TAGKEYS(          XKB_KEY_5,	XKB_KEY_percent,			4),
	TAGKEYS(          XKB_KEY_6,	XKB_KEY_asciicircum,			5),
	TAGKEYS(          XKB_KEY_7,	XKB_KEY_ampersand,			6),
	TAGKEYS(          XKB_KEY_8,	XKB_KEY_asterisk,			7),
	TAGKEYS(          XKB_KEY_9,	XKB_KEY_parenleft,			8),
	{ MODKEY|WLR_MODIFIER_SHIFT,	XKB_KEY_Q,		quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
