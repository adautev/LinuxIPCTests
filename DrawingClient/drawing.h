#include <sys/msg.h>
#define MAX_SEND_SIZE 80
enum drawing_command {
    MOVE,
    PAINT,
    CLEAR
};

struct drawing_message {
    long mtype;
    enum drawing_command command;
    char mtext[MAX_SEND_SIZE];
};
short send_message(int queue_id, struct drawing_message *message_buffer);
short read_message(int queue_id, struct drawing_message *message_buffer);
void remove_queue(int queue_id);
void set_tty_parameters();
void change_queue_mode(int queue_id, char *mode);
key_t create_queue(int key, int* message_queue_id);
