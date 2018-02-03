#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "../DrawingClient/drawing.h"

int main(int argc, char **argv)
{
    int ch, prev, row, col, max_row, max_col;
    initscr();				/* Start curses mode */
    getmaxyx(stdscr, max_row, max_col);
    start_color();	
    move(max_row,0);
	key_t message_queue_key;
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_BLACK);
    int message_queue_id;
    struct drawing_message message_buffer;
    //struct drawing_message mbuf;
    //Aaand I know atoi is c++. :D
    message_queue_key = create_queue(atoi("drawing_test"), &message_queue_id);
    refresh();
    while (read_message(message_queue_id,&message_buffer) == 1) {
        //printf("Command: %d, parameter: %s\r\n", message_buffer.command, message_buffer.mtext);
        
        switch(message_buffer.command) {
            case MOVE:
                //printf("Moving %s\r\n", message_buffer.mtext);
                if(strcmp(message_buffer.mtext, "down") == 0) {
                    if(max_row > row) {
                        move(++row, col);
                    }
                } else if(strcmp(message_buffer.mtext, "up") == 0) {
                    if(row > 0) {
                        move(--row, col);
                    }
                } else if(strcmp(message_buffer.mtext, "left") == 0) {
                    if(col > 0) {
                        move(row, --col);
                    }
                } else if(strcmp(message_buffer.mtext, "right") == 0) {
                    if(col < max_col) {
                        move(row, ++col);
                    }
                }
                break;
            case CLEAR:
                   attron(COLOR_PAIR(3));
                   addch('x');
                   move(row,col);
                   attroff(COLOR_PAIR(3));
                break;
            case PAINT:
                if(strcmp(message_buffer.mtext, "white") == 0) {
                   attron(COLOR_PAIR(2));
                   addch('x');
                   move(row,col);
                   attroff(COLOR_PAIR(2));
                } else if(strcmp(message_buffer.mtext, "blue") == 0) {
                   attron(COLOR_PAIR(1));
                   addch('x');
                   move(row,col);
                   attron(COLOR_PAIR(1));
                }
                break;
        }
        refresh();
    }
    endwin();
	return 0;
}
