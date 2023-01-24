#include "errorlib.h"
int oerror(const char * error, int id) {
    write(STDERR_FILENO, error, strlen(error));
    exit(id);
}
