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
short send_message(int qid, struct drawing_message *qbuf);
void read_message(int qid, struct drawing_message *qbuf);
void remove_queue(int qid);
void set_tty_parameters();
void change_queue_mode(int qid, char *mode);
key_t create_queue(int key, int* message_queue_id);
