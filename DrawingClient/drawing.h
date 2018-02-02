#include <sys/msg.h>
enum drawing_command {
    MOVE,
    PAINT,
    CLEAR
};

struct drawing_message {
    enum drawing_command command;
    char* drawing_parameter;
};
short send_message(int queue_id, struct drawing_message *message_buffer);
short read_message(int queue_id, struct drawing_message *message_buffer);
void remove_queue(int queue_id);
void set_tty_parameters();
void change_queue_mode(int queue_id, char *mode);
key_t create_queue(int key, int* message_queue_id);
