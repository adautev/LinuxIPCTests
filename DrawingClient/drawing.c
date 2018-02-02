#include "drawing.h"
#include <stdio.h>
#include <string.h>
short send_message(int queue_id, struct drawing_message *message_buffer) {
    if((msgsnd(queue_id, (struct drawing_message *)message_buffer,
            strlen(message_buffer->drawing_parameter)+1, 0)) ==-1)
    {
            perror("msgsnd");
            return -1;
    }
    return 0;
}
void read_message(int queue_id, struct drawing_message *message_buffer) {
    
}
void remove_queue(int queue_id) {
    
}
void change_queue_mode(int queue_id, char *mode) {
    
}
key_t create_queue(int key, int* message_queue_id) {
    /* Create unique key via call to ftok() */
    key_t queue_key;
    if((queue_key = ftok("/tmp", key)) == (key_t)-1) {
        printf("%s", "Unable to initialize message queue key.");
        return 0;
    }
    int queue_id;
    /* Open the queue - create if necessary */
    if((queue_id = msgget(queue_key, IPC_CREAT|0660)) == -1) {
            printf("%s", "Unable to initialize message queue.");
            return 0;
    }
    message_queue_id = &queue_id;
    return queue_key;
}