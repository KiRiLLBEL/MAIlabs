#include <stdio.h>

int main() {
    FILE * fin = fopen("input.txt", "r");
    FILE * fbuffer = fopen("buffer.txt", "w+");
    char buf = '\0';
    int height = 0;
    int width = 0;
    while (buf != EOF)
    {
        int number;
        fscanf(fin, "%d", &number);
        buf = fgetc(fin);
        fprintf(fbuffer, "%d", number);
        if (buf == '\n') {
            fputc(' ', fbuffer);
            height++;
            width = 0;
        }
        else if(buf == EOF) {
            fputc(' ', fbuffer);
            height++;
            width++;
        }
        else {
            fputc(buf, fbuffer);
            width++;
        }
    }
    fclose(fin);
    fclose(fbuffer);
    fin = fopen("input.txt", "w+");
    for (int i = 0; i != width; i++) {
        fbuffer = fopen("buffer.txt", "r");
        for (int j = 0; j != height*width; j++) {
            int number;
            fscanf(fbuffer, "%d", &number);
            if (j % width == i) {
                fprintf(fin, "%d ", number);
            }
        }
        fclose(fbuffer);
        fprintf(fin, "\n");

    }
    fclose(fin);
    fclose(fbuffer);
    return 0;
}