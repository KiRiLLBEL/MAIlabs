#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned set_data_elem;
enum {
    bits_per_char = 8,
    bits_per_elem = sizeof(set_data_elem) * bits_per_char,
    datalen = (1 << bits_per_char) / bits_per_elem
};

typedef struct {
    set_data_elem data[datalen];
} set;

void set_clear(set *s)
{
    memset(s -> data, 0, sizeof(s->data));
}

void set_insert(set *s, int c)
{
    s -> data[c / bits_per_elem] |= 1u << (c % bits_per_elem);
}
void set_generate(set *s, bool indicator(int))
{
    set_clear(s);
    for (int i = 0; i != 1 << bits_per_char; ++i) {
        if (indicator(i)) {
            set_insert(s, i);
        }
    }
}

void set_erease(set *s, int c)
{
    s -> data[c / bits_per_elem] &= ~(1u << c % bits_per_elem);
}

bool set_in(const set *s, int c)
{
    return (s->data[c / bits_per_elem] & (1u << c % bits_per_elem)) != 0;
}

int set_size(const set *s)
{
    int size = 0;
    for (int i = 0; i != 1 << bits_per_char; ++i) {
        if (set_in(s, i)) {
            ++size;
        }
    }
    return size;
}

bool set_equal(const set *s1, const set *s2)
{
    for (int i = 0; i != datalen; ++i) {
        if (s1->data[i] != s2->data[i]) {
            return false;
        }
    }
    return true;
}

bool set_includes(const set *s1, const set *s2)
{
    for (int i = 0; i != datalen; ++i) {
        if ((s1 -> data[i] | s2->data[i]) != s1 -> data[i]) {
            return false;
        }
    }
    return true;
}

set set_union(const set *s1, const set *s2)
{
    set result;
    for (int i = 0; i != datalen; ++i) {
        result.data[i] = s1 -> data[i] | s2 -> data[i];
    }
    return result;
}

set set_intersection(const set *s1, const set *s2)
{
    set result;
    for (int i = 0; i != datalen; ++i) {
        result.data[i] = s1 -> data[i] & s2 -> data[i];
    }
    return result;
}

set set_difference(const set *s1, const set *s2)
{
    set result;
    for (int i = 0; i != datalen; ++i) {
        result.data[i] = s1 -> data[i] & ~(s2 -> data[i]);
    }
    return result;
}

set set_symmetric_difference(const set *s1, const set *s2)
{
    set result;
    for (int i = 0; i != datalen; ++i) {
        result.data[i] = s1 -> data[i] ^ s2 -> data[i];
    }
    return result;
}
bool is_alpha(int c)
{
    return isalpha(c);
}
bool is_digit(int c)
{
    return isdigit(c);
}

int main(void)
{
    set s1;
    set_clear(&s1);
    char Symbol;
    bool Repeat = 0;
    while (scanf("%c", &Symbol) != EOF) {
        Symbol = tolower(Symbol);
        switch (Symbol) {
            case 'a':
                if (set_in(&s1, Symbol)) {
                    Repeat = 1;
                } else {
                    set_insert(&s1, 'a');
                }
                break;

            case 'e':
                if (set_in(&s1, Symbol)) {
                    Repeat = 1;
                } else {
                    set_insert(&s1, 'e');
                }
                break;

            case 'i':
                if (set_in(&s1, Symbol)) {
                    Repeat = 1;
                } else {
                    set_insert(&s1, 'i');
                }
                break;

            case 'o':
                if (set_in(&s1, Symbol)) {
                    Repeat = 1;
                } else {
                    set_insert(&s1, 'o');
                }
                break;

            case 'u':
                if (set_in(&s1, Symbol)) {
                    Repeat = 1;
                } else {
                    set_insert(&s1, 'u');
                }
                break;
            
            case ' ':
                set_clear(&s1);
                break;

            case '\n':
                set_clear(&s1);
                break;

            case '\t':
                set_clear(&s1);
                break;

            case ',':
                set_clear(&s1);
                break;
            case 13:
                set_clear(&s1);
                break;
            default:
                break;
            
        }
    }
    if (Repeat == 1) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}