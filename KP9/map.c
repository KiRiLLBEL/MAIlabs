#include "map.h"
#include "time.h"
int size(map * m) {
    return m->size;
}
map * create_map() {
    map * m = malloc(sizeof(map));
    m->size = 0;
    return m;
}
void delete_map(map * m) {
    for(int i = 0; i != size(m); ++i) {
        free(m->maps[i]);
    }
}
void push_back(map *m, int key, char * value) {
    mapitem *tmp = (mapitem *) malloc(sizeof(mapitem));
    tmp->key = key;
    strcpy(tmp->value, value);
    m->maps[size(m)] = tmp;
    m->size++;
}
void erase(map * m, int key) {
    int tmp = -1;
    for (int i = 0; i != size(m); ++i) {
        if (m->maps[i]->key == key) {
            free(m->maps[i]);
            tmp = i;
        }
        if (i > tmp && tmp != -1) {
            m->maps[i - 1] = m->maps[i];
        }
    }
    m->size--;
}
void read_table(map * m, FILE * fin) {
    char str[MAXLEN];
    int key = 0;
    while(fscanf(fin, "%d", &key) != EOF) {
        fgets(str, MAXLEN, fin);
        int len = strlen(str);
        for(int i = 0; i != len; ++i) {
            if (str[i] == '\n')
                str[i] = '\000';
        }
        push_back(m, key, str);
    }
}
void print_table(map * m) {
    printf("+-----+-----------------------------------------------------------------------------------+\n");
    printf("| key |                                      value                                        |\n");
    printf("+-----+-----------------------------------------------------------------------------------+\n");
    for (int i = 0; i != size(m); ++i) {
        printf("| %-3d | %-81s |\n", m->maps[i]->key, m->maps[i]->value);
        printf("+-----+-----------------------------------------------------------------------------------+\n");
    }
}
void bin_search(map * m, int key) {
    int left = -1;
    int right = size(m);
    while(left < right - 1) {
        int middle = (left + right) / 2;
        if(m->maps[middle]->key < key) {
            left = middle;
        } else {
            right = middle;
        }
    }
    if (m->maps[right]->key != key) {
        printf("Element not found");
    }
    else {
        printf("+-----+-----------------------------------------------------------------------------------+\n");
        printf("| key |                                      value                                        |\n");
        printf("+-----+-----------------------------------------------------------------------------------+\n");
        printf("| %-3d | %-81s |\n", m->maps[right]->key, m->maps[right]->value);
        printf("+-----+-----------------------------------------------------------------------------------+\n");
    }

}
void reverse_table(map * m) {
    print_table(m);
    printf("\n");
    for (int i = 0, j = size(m) - 1; i < j; ++i, --j) {
        mapitem * tmp = m->maps[i];
        m->maps[i] = m->maps[j];
        m->maps[j] = tmp;
    }
    print_table(m);
    printf("\n");
}
void diffuse(map * m) {
    print_table(m);
    printf("\n");
    srand(time(0));
    int i, j = 0;
    for (int k = 0; k < size(m); ++k) {
        i = rand() % (size(m) - 1);
        j = rand() % (size(m) - 1);
        mapitem * tmp = m->maps[i];
        m->maps[i] = m->maps[j];
        m->maps[j] = tmp;
    }
    print_table(m);
    printf("\n");
}
void sort(map * m) {
    print_table(m);
    printf("\n");
    for (int i = 0; i < size(m) - 1; i++) {
        for (int j = 0; j < size(m) - i - 1; j++) {
            if(m->maps[j]->key > m->maps[j + 1]->key) {
                mapitem * tmp = m->maps[j];
                m->maps[j] = m->maps[j + 1];
                m->maps[j + 1] = tmp;
            }
        }
    }
    print_table(m);
    printf("\n");
}