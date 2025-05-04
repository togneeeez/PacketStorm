#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#ifndef TUI_H
#define TUI_H
    #include "../headers/tui.h"
#endif

// Main function
int main() {	

    print_debug();

    /* Initializing variables to keep track of the cursor placement */
	int ch;
    int row, col;
    int curX, curY;

    /* Initializing variables to define the program name and style to display on the main page */
    char* titolo = "Packet";
    char* titolo2 = "Storm";

    /* WINDOW variable to display the main menu. */
    WINDOW *main_menu;

    /* Starting cursor mode, enabling text colors and setting the cursor 
    to invisible while printing out the main menu.*/
	initscr();
    start_color();
    curs_set(0);
    init_colors();

    /* Storing the dimensions of the terminal in the row, col variables,
    and printing out the formatted string of the program title. */
    getmaxyx(stdscr, row, col);
    attron(A_BOLD);
    attron(COLOR_PAIR(1));
	mvprintw(1, 2, "%s", titolo);

    getyx(stdscr, curY, curX);
    attron(COLOR_PAIR(2) | A_BLINK);
    mvprintw(curY, curX, "%s", titolo2);
    refresh(); // Ultimately refresh the terminal to apply these changes.

    /* Instantiate a new window with a y,x offset of 2. */
    int startx = 2;
    int starty = 2;
    main_menu = create_newwin(3, row*2, starty, startx);

    m_print_menu(main_menu, startx, starty-1, curX, curY);
    
    /* Enabling the keypad function to get FN keys to work, and if the corresponding
    function keys are pressed, print out the corresponding menu to the user's terminal. */
    keypad(main_menu, TRUE);
    char* testo_menu;
    while (ch != KEY_F(Q_MKEY)) {
        switch (ch = wgetch(main_menu)) {
            case F_MKEY:
                getyx(main_menu, curY, curX);
            
                /* If the F_MKEY is pressed we need to spawn in another window
                providing a list of options inside the "File" section. */

                starty = 4;
                startx = 2;
                WINDOW* file_menu = create_newwin(6, row*0.8, starty, startx);
                f_print_menu(file_menu, startx, starty, curX, curY);
                wrefresh(file_menu);
                m_open = true;
                break;
            case S_MKEY:
                getyx(main_menu, curY, curX);
                
                /* If the S_MKEY is pressed, we need to clear the window and
                spawn in the settings window. */


                mvwprintw(main_menu, curY+1, startx+1, "%s", testo_menu);
                wrefresh(main_menu);
                m_open = true;
                break;
            case Q_MKEY:
                /* If the Q_MKEY is pressed, we can simply quit the program. */
                endwin();
                return 0;
        }
    }

	return 0;
}

void print_debug() {
    // TODO
}

void init_colors() {
    /* Initializing the COLOR PAIRS which will be used to style the main menu. */
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
}

/* Function returning a WINDOW object used to instantiate a new window with a box border,
used to simplify the new window feature's implementation. */
WINDOW *create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

/* Procedure used to destroy a window (and its borders), which needs to be provided as an
argument. */
void destroy_win(WINDOW *local_win) {	
    /* The border, wborder and box routines draw a box around the edges of a window. Other than the window, each argument is a character with attributes:

        ls - left side,
        rs - right side,
        ts - top side,
        bs - bottom side,
        tl - top left-hand corner,
        tr - top right-hand corner,
        bl - bottom left-hand corner, and
        br - bottom right-hand corner.

        If any of these arguments is zero, then the corresponding default values (defined in curses.h) are used instead:

        ACS_VLINE,
        ACS_VLINE,
        ACS_HLINE,
        ACS_HLINE,
        ACS_ULCORNER,
        ACS_URCORNER,
        ACS_LLCORNER,
        ACS_LRCORNER.
    */

    /* In order for this function to work, we need to place a whitespace char for each of the
    function's arguments. */

	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	
    /* We can ultimately refresh the window to apply the changes. */
	wrefresh(local_win);
    /* And finally delete the window. */
	delwin(local_win);
}

/* Procedure used to print the main menu displaying all the possibile operations (file, settings,
and quit. */
void m_print_menu(WINDOW* local_win, int startx, int starty, int curX, int curY) {
    for (int i = 0; i < N_OPTIONS; i++) {
        char menu[50]; // Fixed-size buffer (adjust size as needed)
        char tmp[10]; // Buffer for integer conversion

        switch(i) {
            case 0:
                snprintf(menu, sizeof(menu), "File ( F%d )", F_MKEY_INT);
                mvwprintw(local_win, starty, startx, "%s", menu);
                break;
            case 1:
                snprintf(menu, sizeof(menu), "Settings ( F%d )", S_MKEY_INT);
                break;
            case 2:
                snprintf(menu, sizeof(menu), "Quit ( F%d )", Q_MKEY_INT);
                break;
            default:
                break;
        }

        if (i > 0) {
            getyx(local_win, curY, curX);
            mvwprintw(local_win, curY, curX+5, "%s", menu);
            wrefresh(local_win);
        }
    }
}

/* Procedure used to print the file menu displaying all the possible operations on files
(new file, open an existing file, save the currently open file as a proper file on the file
system). */
void f_print_menu(WINDOW* local_win, int startx, int starty, int curX, int curY) {
    /* Going through the option list to print out the menu options. */
    for (int i = 0; i < F_MENU_N_OPT; i++) {
        char* menu;
        switch (i) {
            case 0:
                menu = "File";
                mvwprintw(local_win, curY, curX, "%s", menu);
                menu = "New... (1)";
                getyx(local_win, curY, curX);
                mvwprintw(local_win, curY+1, startx, "%s", menu);
                break;
            case 1:
                menu = "Open... (2)";
                break;
            case 2:
                menu = "Save as... (3)";
                break;
        }
        if (i > 0)
            // Otherwise, just offset basing on the previous.
            getyx(local_win, curY, curX);
            mvwprintw(local_win, curY+1, startx, "%s", menu); 
            wrefresh(local_win);
    }
}