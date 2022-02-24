#!/bin/bash
if [ "$1" = "?" ]
    then
    echo "Использование: ./catf [ПАРАМЕТР]... [РАСШИРЕНИЕ]"
    echo "Объединяет файлы с указанным расширением, имеющих размер меньше заданного"
    echo "  -n              объединить файлы с указанным размером"
    echo "Размер указывать с расширением K, M"
    echo "Пример ./catf -n 10k txt"
    echo "'c' для байтов
    'w' для двубайтовых слов
    'k' для килобайтов
    'M' для мегабайтов
    'G' для гигабайтов"
    else
    if [ "$1" = "-n" ] 
        then
        if (echo "$2" | grep -E -q "^?[0-9]+[w,k,M,G]?$");
            then
            size=$2
            shift
            shift
            if [ -n "$1" ]
                then
                files=$(find . -name "*.$1" -size -$size)
                echo "Объединить файлы:"
                echo "$files"
                echo -n "Продолжить? (y/n) "
                read item
                case "$item" in
                    y|Y) echo "Ок"
                        cat $files > output.$1
                        echo "Создан файл: output.$1"
                        ;;
                    n|N) echo "Отказ"
                        exit 0
                        ;;
                    *) echo "Вы ничего не ввели, файлы будут объеденены"
                        ;;
                esac
                else
                echo "Укажите расширение файла: ./catf -n <размер> <расширение>" >&2
                echo "                                             ^^^^^^^^^^^^" >&2
            fi
            else
            echo "Укажите размер файлов: ./catf -n <размер> <расширение>" >&2
            echo "                                 ^^^^^^^^" >&2
        fi
        else
        if [ -n "$1" ] 
            then
            files=$(find . -name "*.$1")
            echo "Объединить файлы:"
                echo "$files"
                echo -n "Продолжить? (y/n) "
                read item
                case "$item" in
                    y|Y) echo "Ок"
                        cat $files > output.$1
                        echo "Создан файл: output.$1"
                        ;;
                    n|N) echo "Отказ"
                        exit 0
                        ;;
                    *) echo "Вы ничего не ввели, файлы будут объеденены"
                        ;;
                esac
            else
            echo "укажите расширение файла: ./catf <расширение>" >&2
            echo "                                 ^^^^^^^^^^^^" >&2
        fi
    fi
fi