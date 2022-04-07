#include "table.h"

int main () {
    FILE * f;
    f = fopen("BD.bin", "wb");
    Person p = {"Ivanov", "IV", 10, 19.5, "Chicago", "1930", 1, 0};
    addPerson(&p, f);
    Person p1 = {"Petrov", "AV", 8, 17.8, "Moscow", "2338", 0, 3};
    addPerson(&p1, f);
    Person p2 = {"Sidorov", "GA", 3, 15.9, "Chita", "2136", 1, 1};
    addPerson(&p2, f);
    Person p3 = {"Trofimov", "VD", 4, 5.9, "Sochi", "0956", 0, 0};
    addPerson(&p3, f);
    Person p4 = {"Egorov", "VS", 3, 9.8, "Novgorod", "2122", 1, 6};
    addPerson(&p4, f);
    Person p5 = {"Dolmatin", "PK", 4, 4.8, "New-York", "1934", 1, 2};
    addPerson(&p5, f);
    Person p6 = {"Tokmakova", "MI", 3, 2.5, "Ottawa", "0730", 1, 0};
    addPerson(&p6, f);
    Person p7 = {"Zvereva", "LA", 2, 10.5, "Moscow", "1538", 0, 1};
    addPerson(&p7, f);
    Person p8 = {"Paladi", "AI", 5, 30.7, "Anapa", "0813", 1, 0};
    addPerson(&p8, f);
    Person p9 = {"Kalinin", "KA", 10, 105.4, "Vladivostok", "0634", 1, 9};
    addPerson(&p9, f);
    fclose(f);
}