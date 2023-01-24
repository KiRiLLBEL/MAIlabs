#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "library/zmq_struct.h"
#include <signal.h>


int do_something = 1;

void sig_handler(int signum){
    do_something = 0;
}

const int WAIT_TIME = 1000;

int main (int argc, char * argv[])
{   
    int rc;
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_PAIR);
    assert(argc == 2);
    int id = atoi(argv[1]);
    int new_port = id + 5555;
    char port[40];
    sprintf(port, "%d", new_port);
    char path[40] = "tcp://localhost:";
    strcat(path, port);
    rc = zmq_connect(socket, path);
    assert(rc == 0);
    void * right_context;
    void * right_socket;
    int right_tree = 0;
    void * left_context;
    void * left_socket;
    int left_tree = 0;
    while (do_something) {
        message_zmq * data = ping_receive(socket);
        if(data != NULL) {
            int new_id = data->id;
            int new_size = data->size;
            if(data->key == CHECK) {
                message_zmq answer = {SUCCESS, getpid()};
                ping_send(socket, &answer);
            }
            if(data->key == CREATE) {
                if(new_id < id) {
                    if(left_tree == 0) {
                        int rc;
                        left_context = zmq_ctx_new();
                        left_socket = zmq_socket(left_context, ZMQ_PAIR);
                        rc = zmq_setsockopt(left_socket, ZMQ_RCVTIMEO, &WAIT_TIME, sizeof(int));
                        assert(rc == 0);
                        rc = zmq_setsockopt(left_socket, ZMQ_SNDTIMEO, &WAIT_TIME, sizeof(int));
                        assert(rc == 0);
                        create_conn(new_id, left_socket, left_context);
                        char id_str[12];
                        sprintf(id_str, "%d", new_id);
                        if(fork() == 0) {
                            execlp("./server", "server", id_str, NULL);
                            perror("execlp");
                            exit(EXIT_FAILURE);
                        } else {
                            message_zmq reply = {CHECK, getpid()};
                            ping_send(left_socket, &reply);
                            message_zmq * new_data = ping_receive(left_socket);
                            if(new_data != NULL) {
                                int pid = new_data->id;
                                if(new_data->key == SUCCESS) {
                                    left_tree = new_id;
                                    message_zmq new_reply = {SUCCESS, pid};
                                    ping_send(socket, &new_reply);
                                } else {
                                    rc = zmq_close(left_socket);
                                    assert(rc == 0);
                                    rc = zmq_ctx_destroy(left_context);
                                    assert(rc == 0);
                                    message_zmq new_reply = {FAIL_CREATE, pid};
                                    ping_send(socket, &new_reply);
                                }
                            } else {
                                message_zmq new_reply = {FAIL_PING, new_id};
                                ping_send(socket, &new_reply);
                            }
                        }
                    } 
                    else {
                        message_zmq reply = {CREATE, new_id};
                        ping_send(left_socket, &reply);
                        message_zmq * new_data = ping_receive(left_socket);
                        if(new_data != NULL) {
                            message_zmq msg = *new_data;
                            ping_send(socket, &msg);
                        } else {
                            message_zmq new_reply = {FAIL_PING, new_id};
                            ping_send(socket, &new_reply);
                        }
                    }
                } else if(new_id == id) {
                    message_zmq reply = {FAIL, getpid()};
                    ping_send(socket, &reply);
                } else {
                    if(right_tree == 0) {
                        int rc;
                        right_context = zmq_ctx_new();
                        right_socket = zmq_socket(right_context, ZMQ_PAIR);
                        rc = zmq_setsockopt(right_socket, ZMQ_RCVTIMEO, &WAIT_TIME, sizeof(int));
                        assert(rc == 0);
                        rc = zmq_setsockopt(right_socket, ZMQ_SNDTIMEO, &WAIT_TIME, sizeof(int));
                        assert(rc == 0);
                        create_conn(new_id, right_socket, right_context);
                        char id_str[10];
                        sprintf(id_str, "%d", new_id);
                        if(fork() == 0) {
                            execlp("./server", "server", id_str, NULL);
                            perror("execlp");
                            exit(EXIT_FAILURE);
                        } else {
                            message_zmq reply = {CHECK, getpid()};
                            ping_send(right_socket, &reply);
                            message_zmq * new_data = ping_receive(right_socket);
                            if(new_data != NULL) {
                                int pid = new_data->id;
                                if(new_data->key == SUCCESS) {
                                    right_tree = new_id;
                                    message_zmq new_reply = {SUCCESS, pid};
                                    ping_send(socket, &new_reply);
                                } else {
                                    rc = zmq_close(right_socket);
                                    assert(rc == 0);
                                    rc = zmq_ctx_destroy(right_context);
                                    assert(rc == 0);
                                    message_zmq new_reply = {FAIL_CREATE, pid};
                                    ping_send(socket, &new_reply);
                                }
                            }
                            else {
                                message_zmq new_reply = {FAIL_PING, new_id};
                                ping_send(socket, &new_reply);
                            }
                        }
                    } 
                    else {
                        message_zmq reply = {CREATE, new_id};
                        ping_send(right_socket, &reply);
                        message_zmq * new_data = ping_receive(right_socket);
                        if(new_data != NULL) {
                            message_zmq msg = *new_data;
                            ping_send(socket, &msg);
                        } else {
                            message_zmq new_reply = {FAIL_PING, new_id};
                            ping_send(socket, &new_reply);
                        }
                    }
                }
            }
            if(data->key == REMOVE) {
                if(new_id < id) {
                    if(left_tree == 0) {
                        message_zmq reply = {FAIL, getpid()};
                        ping_send(socket, &reply);
                    }
                    else if(left_tree == new_id) {
                        message_zmq reply = {REMOVE, left_tree};
                        ping_send(left_socket, &reply);
                        message_zmq * new_data = ping_receive(left_socket);
                        if(new_data != NULL) {
                            if(new_data->key == SUCCESS) {
                                message_zmq msg = *new_data;
                                ping_send(socket, &msg);
                                left_tree = 0;
                                rc = zmq_close(left_socket);
                                assert(rc == 0);
                                rc = zmq_ctx_destroy(left_context);
                                assert(rc == 0);
                            } else {
                                message_zmq msg = *new_data;
                                ping_send(socket, &msg);
                            }
                        }
                        else {
                            message_zmq new_reply = {FAIL_PING, new_id};
                            ping_send(socket, &new_reply);
                        }
                    }
                    else {
                        message_zmq reply = {REMOVE, new_id};
                        ping_send(left_socket, &reply);
                        message_zmq * new_data = ping_receive(left_socket);
                        if(new_data != NULL) {
                            message_zmq msg = *new_data;
                            ping_send(socket, &msg);
                        } else {
                            message_zmq new_reply = {FAIL_PING, new_id};
                            ping_send(socket, &new_reply);
                        }
                    }
                } 
                else if(new_id == id) {
                    if(left_tree != 0) {
                        message_zmq reply = {REMOVE, left_tree};
                        ping_send(left_socket, &reply);
                        message_zmq * new_data = ping_receive(left_socket);
                        if(new_data != NULL) {
                            message_zmq msg = *new_data;
                            ping_send(socket, &msg);
                        } else {
                            message_zmq new_reply = {FAIL_PING, new_id};
                            ping_send(socket, &new_reply);
                        }
                    }
                    if(right_tree != 0) {
                        message_zmq reply = {REMOVE, right_tree};
                        ping_send(right_socket, &reply);
                        message_zmq * new_data = ping_receive(right_socket);
                        if(new_data != NULL) {
                            message_zmq msg = *new_data;
                            ping_send(socket, &msg);
                        } else {
                            message_zmq new_reply = {FAIL_PING, new_id};
                            ping_send(socket, &new_reply);
                        }
                    }
                    do_something = 0;
                    message_zmq reply = {SUCCESS, getpid()};
                    ping_send(socket, &reply);
                }
                else {
                    if(right_tree == 0) {
                        message_zmq reply = {FAIL, getpid()};
                        ping_send(socket, &reply);
                    }
                    else if(right_tree == new_id) {
                        message_zmq reply = {REMOVE, right_tree};
                        ping_send(right_socket, &reply);
                        message_zmq * new_data = ping_receive(right_socket);
                        if(new_data != NULL) {
                            if(new_data->key == SUCCESS) {
                                message_zmq msg = *new_data;
                                ping_send(socket, &msg);
                                right_tree = 0;
                                rc = zmq_close(right_socket);
                                assert(rc == 0);
                                rc = zmq_ctx_destroy(right_context);
                                assert(rc == 0);
                            } else {
                                message_zmq msg = *new_data;
                                ping_send(socket, &msg);
                            }
                        }
                        else {
                            message_zmq new_reply = {FAIL_PING, new_id};
                            ping_send(socket, &new_reply);
                        }
                    }
                    else {
                        message_zmq reply = {REMOVE, new_id};
                        ping_send(right_socket, &reply);
                        message_zmq * new_data = ping_receive(right_socket);
                        if(new_data != NULL) {
                            message_zmq msg = *new_data;
                            ping_send(socket, &msg);
                        } else {
                            message_zmq new_reply = {FAIL_PING, new_id};
                            ping_send(socket, &new_reply);
                        }
                    }
                }
            }
            if(data->key == PING) {
                if(new_id < id) {
                    if(left_tree == 0) {
                        message_zmq reply = {FAIL, 0};
                        ping_send(socket, &reply);
                    }
                    else if(left_tree == new_id) {
                        message_zmq reply = {CHECK, new_id};
                        if(ping_send(left_socket, &reply)) {
                            message_zmq * new_data = ping_receive(left_socket);
                            if(new_data != NULL) {
                                message_zmq msg = *new_data;
                                ping_send(socket, &msg);
                            } else {
                                message_zmq new_data = {FAIL_PING, new_id};
                                ping_send(socket, &new_data);
                            }
                        }
                        else {
                            message_zmq new_data = {FAIL_PING, new_id};
                            ping_send(socket, &new_data);
                        }
                    }
                    else {
                        message_zmq reply = {PING, new_id};
                        ping_send(left_socket, &reply);
                        message_zmq * new_data = ping_receive(left_socket);
                        if(new_data != NULL) {
                            message_zmq msg = *new_data;
                            ping_send(socket, &msg);
                        } else {
                            message_zmq new_data = {FAIL_PING, new_id};
                            ping_send(socket, &new_data);
                        }
                    }
                } 
                else if(new_id == id) {
                    message_zmq reply = {SUCCESS, 1};
                    ping_send(socket, &reply);
                }
                else {
                    if(right_tree == 0) {
                        message_zmq reply = {FAIL, 2};
                        ping_send(socket, &reply);
                    }
                    else if(right_tree == new_id) {
                        message_zmq reply = {CHECK, new_id};
                        if(ping_send(right_socket, &reply)) {
                            message_zmq * new_data = ping_receive(right_socket);
                            if(new_data != NULL) {
                                message_zmq msg = *new_data;
                                ping_send(socket, &msg);
                            } else {
                                message_zmq new_data = {FAIL_PING, new_id};
                                ping_send(socket, &new_data);
                            }
                        }
                        else {
                            message_zmq new_data = {FAIL_PING, new_id};
                            ping_send(socket, &new_data);
                        }
                    }
                    else {
                        message_zmq reply = {PING, new_id};
                        ping_send(right_socket, &reply);
                        message_zmq * new_data = ping_receive(right_socket);
                        if(new_data != NULL) {
                            message_zmq msg = *new_data;
                            ping_send(socket, &msg);
                        } else {
                            message_zmq new_data = {FAIL_PING, new_id};
                            ping_send(socket, &new_data);
                        }
                    }
                }
            }
            if(data->key == EXEC) {
                char * query = recv_string(socket, new_size);
                if(new_id < id) {
                    if(left_tree == 0) {
                        message_zmq reply = {FAIL, new_id};
                        ping_send(socket, &reply);
                    }
                    else {
                        message_zmq reply = {EXEC, new_id, new_size};
                        ping_send(left_socket, &reply);
                        send_string(left_socket, query);
                        message_zmq * new_data = ping_receive(left_socket);
                        if(new_data != NULL) {
                            message_zmq msg = *new_data;
                            ping_send(socket, &msg);
                        } else {
                            message_zmq new_data = {FAIL_PING, new_id};
                            ping_send(socket, &new_data);
                        }
                    }
                } 
                else if(new_id == id) {
                    strtok(query, " ");
                    int n = atoi(query);
                    long long sum = 0;
                    for(int i = 0; i < n; ++i) {
                        query = strtok(NULL, " ");
                        int a = atoi(query);
                        sum += a;
                    }
                    message_zmq reply = {SUCCESS, new_id, sum};
                    ping_send(socket, &reply);
                }
                else {
                    if(right_tree == 0) {
                        message_zmq reply = {FAIL, new_id};
                        ping_send(socket, &reply);
                    }
                    else {
                        message_zmq reply = {EXEC, new_id, new_size};
                        ping_send(right_socket, &reply);
                        send_string(right_socket, query);
                        message_zmq * new_data = ping_receive(right_socket);
                        if(new_data != NULL) {
                            message_zmq msg = *new_data;
                            ping_send(socket, &msg);
                        } else {
                            message_zmq new_data = {FAIL_PING, new_id};
                            ping_send(socket, &new_data);
                        }
                    }
                }
            }
        }
        else {
            message_zmq new_reply = {FAIL_PING, id};
            ping_send(socket, &new_reply);
        }
    }
    rc = zmq_close(socket);
    assert(rc == 0);
    rc = zmq_ctx_destroy(context);
    assert(rc == 0);
    return 0;
}