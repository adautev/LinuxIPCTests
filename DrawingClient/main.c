#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
//Terminal manipulation
#include <termios.h>
//sudo apt-get install libncurses5-dev
#include <ncurses.h>
#include <unistd.h>
#include "drawing.h"

int main(int argc, char **argv)
{
	key_t message_queue_key;
    int message_queue_id;
    struct drawing_message message_buffer;
    //struct drawing_message mbuf;
    //Aaand I know atoi is c++. :D
    message_queue_key = create_queue(atoi("drawing_test"), &message_queue_id);
    int command;
    set_tty_parameters();
    while((command = getchar()) != -0) {
        switch(command) {
            case (int)'q':
                printf("%s","Exiting...\r\n");
                return(0);
            case 65:
                printf("%s","Moving Up...\r\n");
                message_buffer.command = MOVE;
                message_buffer.drawing_parameter = "up";
                send_message(message_queue_id, &message_buffer);
                break;
            case 66:
                printf("%s","Moving Down...\r\n");
                message_buffer.command = MOVE;
                message_buffer.drawing_parameter = "down";
                break;
            case 68:
                printf("%s","Moving Left...\r\n");
                message_buffer.command = MOVE;
                message_buffer.drawing_parameter = "left";
                break;
            case 67:
                printf("%s","Moving Right...\r\n");
                message_buffer.command = MOVE;
                message_buffer.drawing_parameter = "right";
                break;
            case 120:
                printf("%s","Painting white...\r\n");
                message_buffer.command = PAINT;
                message_buffer.drawing_parameter = "white";
                break;
            case 122:
                printf("%s","Painting blue...\r\n");
                message_buffer.command = PAINT;
                message_buffer.drawing_parameter = "blue";
                break;
            case 99:
                printf("%s","Clearing...\r\n");
                message_buffer.command = CLEAR;
                message_buffer.drawing_parameter = "";
                break;
            default:
                printf("Unknown command %c \r\n", command);
                break;
            
        }
    }
}
void set_tty_parameters() {
    //We want no enter to succeed our input
    system ("/bin/stty raw");
    struct termios tp;
    if (tcgetattr(STDIN_FILENO, &tp) == -1) {
        printf("%s","Unable to disable echo...");
        return;
    }
    tp.c_lflag &= ~ECHO;                /* ECHO off, other bits unchanged */
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1) {
        printf("%s","Unable to disable echo...");
        return;
    }
    //We want no escape chars
    curs_set(1);
}