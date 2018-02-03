#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
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
    message_buffer.mtype = 1001;
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
                memset(message_buffer.mtext,0,sizeof(message_buffer.mtext));
                message_buffer.command = MOVE;
                strcpy(message_buffer.mtext,"up");
                send_message(message_queue_id, &message_buffer);
                break;
            case 66:
                printf("%s","Moving Down...\r\n");
                message_buffer.command = MOVE;
                memset(message_buffer.mtext,0,sizeof(message_buffer.mtext));
                strcpy(message_buffer.mtext,"down");
                send_message(message_queue_id, &message_buffer);
                break;
            case 68:
                printf("%s","Moving Left...\r\n");
                message_buffer.command = MOVE;
                memset(message_buffer.mtext,0,sizeof(message_buffer.mtext));
                strcpy(message_buffer.mtext,"left");
                send_message(message_queue_id, &message_buffer);
                break;
            case 67:
                printf("%s","Moving Right...\r\n");
                message_buffer.command = MOVE;
                strcpy(message_buffer.mtext,"right");
                send_message(message_queue_id, &message_buffer);
                break;
            case 120:
                printf("%s","Painting white...\r\n");
                message_buffer.command = PAINT;
                strcpy(message_buffer.mtext,"white");
                send_message(message_queue_id, &message_buffer);
                break;
            case 122:
                printf("%s","Painting blue...\r\n");
                message_buffer.command = PAINT;
                strcpy(message_buffer.mtext,"blue");
                send_message(message_queue_id, &message_buffer);
                break;
            case 99:
                printf("%s","Clearing...\r\n");
                message_buffer.command = CLEAR;
                strcpy(message_buffer.mtext,"");
                send_message(message_queue_id, &message_buffer);
                break;
            default:
                //printf("Unknown command %c \r\n", command);
                break;
            
        }
    }
}
void set_tty_parameters() {
    //We want no enter to succeed our input
    raw();
    noecho();
    curs_set(0);
    
}