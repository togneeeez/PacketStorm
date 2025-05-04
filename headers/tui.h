/* Functions' prototypes. */
void print_debug();
void init_colors();
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void m_print_menu(WINDOW* local_win, int startx, int starty, int curX, int curY);
void f_print_menu(WINDOW* local_win, int startx, int starty, int curX, int curY);

/* Costants for future enhancements/updates. */
const int N_OPTIONS = 3;
const int F_MENU_N_OPT = 3;

/* Provides info on whether a menu is currently open, to disable the FN keys. */
bool m_open = false;

/* Provides a way to change function keys to access the main menu options. */
enum key_settings {
    F_MKEY = KEY_F(1),
    F_MKEY_INT = 1,
    S_MKEY = KEY_F(2),
    S_MKEY_INT = 2,
    Q_MKEY = KEY_F(3),
    Q_MKEY_INT = 3
};