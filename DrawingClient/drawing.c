#include "drawing.h"
#include <stdio.h>
void send_message(int qid, struct drawing_message *qbuf) {
    
}
void read_message(int qid, struct drawing_message *qbuf) {
    
}
void remove_queue(int qid) {
    
}
void change_queue_mode(int qid, char *mode) {
    
}
key_t create_queue(char* key, int* message_queue_id) {
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