#include <stdio.h>
#include "drawing.h"

int main(int argc, char **argv)
{
	key_t message_queue_key;
    int message_queue_id;
    struct drawing_message message_buffer;
    //struct drawing_message mbuf;
    //Aaand I know atoi is c++. :D
    message_queue_key = create_queue(atoi("drawing_test"), &message_queue_id);
    while (read_message(message_queue_id,&message_buffer)) {
        
    }
	return 0;
}
