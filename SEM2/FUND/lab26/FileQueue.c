#include "FileQueue.h"
void FCreateQueue(Queue * q) {
    q->fqueue = fopen("queue.bin", "w+");
    fclose(q->fqueue);
}
bool FEmptyQueue(Queue * q) {
    q->fqueue = fopen("queue.bin", "r+");
    fseek(q->fqueue, 0, SEEK_END);
    int pos = ftell(q->fqueue);
    fclose(q->fqueue);
    return (pos == 0) ? 1 : 0;
}
void FPushQueue(Queue * q, int t) {
    q->fqueue = fopen("queue.bin", "r+");
    fseek(q->fqueue, 0, SEEK_END);
    fwrite(&t, sizeof(int), 1, q->fqueue);
    fclose(q->fqueue);
}
int FTopQueue(Queue * q) {
    q->fqueue = fopen("queue.bin", "r+");
    int buf;
    fread(&buf, sizeof(int), 1, q->fqueue);
    fclose(q->fqueue);
    return buf;
}
void FPopQUEUE(Queue * q) {
    Queue q1;
    q->fqueue = fopen("queue.bin", "r+");
    q1.fqueue = fopen("queue_buf.bin", "w+");
    int buf;
    fread(&buf, sizeof(int), 1, q->fqueue);
    while (fread(&buf, sizeof(int), 1, q->fqueue) == 1) {
        fwrite(&buf, sizeof(int), 1, q1.fqueue);
    }
    fclose(q->fqueue);
    fopen("queue.bin", "w+");
    fseek(q1.fqueue, 0, SEEK_SET);
    while (fread(&buf, sizeof(int), 1, q1.fqueue) == 1) {
        fwrite(&buf, sizeof(int), 1, q->fqueue);
    }
    fclose(q1.fqueue);
    fclose(q->fqueue);
    remove("queue_buf.bin");
}
void FDestroyQueue(Queue * q){
    remove("queue.bin");
}