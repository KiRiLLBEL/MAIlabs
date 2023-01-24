# Отчет по курсовому проекту
## по курсу "Логическое программирование"

### студент: Белоносов Кирилл Алексеевич

## Результат проверки

Вариант задания:

 - [ ] стандартный, без NLP (на 3)
 - [x] стандартный, с NLP (на 3-4)
 - [ ] продвинутый (на 3-5)
 
| Преподаватель     | Дата         |  Оценка       |
|-------------------|--------------|---------------|
| Сошников Д.В. |              |               |
| Левинская М.А.|              |               |

> *Комментарии проверяющих (обратите внимание, что более подробные комментарии возможны непосредственно в репозитории по тексту программы)*

## Введение

В результате данного курсового проекта я повторил многие темы из курса Логического программирования, а также углубился в некоторые более подробно, например в работу отсечений. Благодаря написанному мною реферату, я познакомился с удивительной темой программирования шахмат. Не могу не отметить впечатления которые произвел на меня на меня матч DeepBlue и Каспарова.

## Задание

1. Получить родословное дерево в формате GEDCOM, изучить сам формат
2. Полученное дерево преобразовать в набор фактов на языке пролог, используя представление `child(<CHILD>, <PARENT>)`, `male(<PERSON>)`, `female(<PERSON>)`.
3. Реализовать предикат поиска двоюродного брата
4. Реализовать предикат нахождения родства двух произвольных индивидуумов в дереве.
5. Реализовать естественный-языковой интерфейс к системе, в которой можно узнать степень родства.

## Получение родословного дерева

Я использовал готовое дерево на 70 человек и 20 уникальных фамилий. Было сложно написать дерево для своей семьи, дальше бабушек и дедушек я не ушел. Для работы с деревом я использовал визуализатор `GrampsAI`

## Конвертация родословного дерева

Для конвертации родословного дерева я выбрал язык Prolog, так как это показалось мне интересной задачой. Пригодились знания написания парсеров на языке Python. Программа основывается на механизме конечных автоматов, т.е. при считывания какого одного параметра, мы переходим в состояние для считывания уже следующего параметра.

Самые главные действия происходят в предикате `streamlines`
```prolog
stream_lines(In, Lines, Out) :-
    read_string(In, _, Str),
    split_string(Str, "\n", "", Lines),
    write_struct(Lines, Out, List, 0),
    write_child(Lines, Out, List, _, 0).
```

Сначала с помощью предиката `write_struct` мы получаем идентификаторы всех индивидуумов и храним их вместе с именами, в дальнейшем это очень сильно упростит нам жизнь. Далее в зависимости от пола нашего индивидуума, мы выводим его в файл в `output.pl`:

```prolog
write_struct(L, Out, [_:Name:"F"|R], 3) :-
    format(Out, '~q', [female(Name)]),
    write(Out,"."),
    write(Out, "\n"),
    write_struct(L, Out, R, 0).

write_struct(L, Out, [_:Name:"M"|R], 3) :- 
    format(Out, '~q', [male(Name)]),
    write(Out,"."),
    write(Out, "\n"),
    write_struct(L, Out, R, 0).
```

Далее мы работаем с предикатом `write_child`, необходимый для вывода детей. Так как мы уже имеем список всех людей(`List`), входядищих в древо, то мы можем спокойно, ориентируясь на теки `HUSB` и `WIFE` выводить детей, получая их имена с помощью унификации и предиката `member`:

```prolog
check_c([_, "CHIL", ID|_], M:W, List, Out) :-
    member(ID:Name:_, List),
    format(Out, '~q', [child(Name, M)]), write(Out,"."), write(Out,"\n"),
    format(Out, '~q', [child(Name, W)]), write(Out,"."), write(Out,"\n").
```

## Предикат поиска родственника

Предикат поиска двоюродного брата(Я также реализовал и поиск сестры, так как в английском языке для этого существует единый термин cousin)

```prolog
cousin_m(X, Y) :- child(X, Z), child(Z, H), child(K, H), child(Y, K), K \= Z, male(Y).
cousin_f(X, Y) :- child(X, Z), child(Z, H), child(K, H), child(Y, K), K \= Z, female(Y).
```

Идея предиката наива, если нам нужно найти двоюродного брата, сначала следует спросить у отца, потом у деда, потом спросить у другого сына деда, в конечном счете мы и получим нашего двоюродного брата. Есть ньюанс связанный с тем, что переменные для детей деда должны различаться, иначе мы можем вернуться к обратно к своему родному брату.

Пример работы:

```prolog
?- cousin_m("John Fitzgerald Kennedy", Y). 
Y = "Robert Sargent Bobby Shriver III" ;
Y = "Timothy Shriver" ;
Y = "Mark Kennedy Shriver" ;
Y = "Anthony Paul Kennedy Shriver" ;
Y = "Christopher Lawford" ;
Y = "Joseph Patrick Kennedy II" ;
Y = "Robert Francis Kennedy" ;
Y = "David Anthony Kennedy" ;
Y = "Michael L. Kennedy" ;
Y = "Christopher George Kennedy" ;
Y = "Matthew Maxwell Taylor Max Kennedy" ;
Y = "Douglas Harriman Kennedy" ;
Y = "William Kennedy Smith" ;
Y = "Stephen Smith Jr" ;
Y = "Edward Moore Kennedy Jr" ;
Y = "Patrick Joseph Kennedy II" ;
Y = "Robert Sargent Bobby Shriver III" ;
Y = "Timothy Shriver" ;
Y = "Mark Kennedy Shriver" ;
Y = "Anthony Paul Kennedy Shriver" ;
Y = "Christopher Lawford" ;
Y = "Joseph Patrick Kennedy II" ;
Y = "Robert Francis Kennedy" ;
Y = "David Anthony Kennedy" ;
Y = "Michael L. Kennedy" ;
Y = "Christopher George Kennedy" ;
Y = "Matthew Maxwell Taylor Max Kennedy" ;
Y = "Douglas Harriman Kennedy" ;
Y = "William Kennedy Smith" ;
Y = "Stephen Smith Jr" ;
Y = "Edward Moore Kennedy Jr" ;
Y = "Patrick Joseph Kennedy II" ;
false.
?- cousin_m("Patrick Kennedy", Y).         
false.
```

## Определение степени родства

Все решение находится в файле `solution.pl`. Основаня суть предиката определения степени родства заключается в поиске в ширину, т.е. нахождение кратчайшего пути, до необходимого нам родственника.

Для этого нам необходимо реализовать предикат `move`, чтобы двигаться в нашем дереве. Для этого мы реализуем основные отношения родства для близких родственников:

```prolog
cousin_m(X, Y) :- child(X, Z), child(Z, H), child(K, H), child(Y, K), K \= Z, male(Y).
cousin_f(X, Y) :- child(X, Z), child(Z, H), child(K, H), child(Y, K), K \= Z, female(Y).
brother(X, Y) :- child(X, Z), child(Y, Z), male(Y).
sister(X, Y) :- child(X, Z), child(Y, Z), female(Y).
father(X, Y) :- child(X, Y), male(Y).
mother(X, Y) :- child(X, Y), female(Y).
wife(X, Y) :- male(X), child(Z, X), child(Z, Y), female(Y).
husband(X, Y) :- female(X), child(Z, X), child(Z, Y), male(Y).
son(X, Y) :- child(Y, X), male(Y).
douther(X, Y) :- child(Y, X), female(Y).
grandmother(X, Y) :- child(X, Z), child(Z, Y), female(Y).
grandfather(X, Y) :- child(X, Z), child(Z, Y), male(Y).
grandson(X, Y) :- child(Z, X), child(Y, Z), male(Y).
granddouther(X, Y) :- child(Z, X), child(Y, Z), female(Y).
```

Теперь воспользуемся алгоритмом поиска в ширину, при этом ограничим глубину погружения, так как наше дерево не особо большое. В решении этой задачи, очень пригодились знания, полученные во время выполнения лабораторной работы #3.

```prolog
bfs(Start, End, Path) :-
    bfs_other([0:[Start]], End, Path).
bfs_other([_:[End|T]|_], End, [End|T]).
bfs_other([4:[_|_]|_], _, _) :- !, false.
bfs_other([Now|CheckTail], End, Path) :-
    findall(Z, prolong(Now, Z), T),
    append(CheckTail, T, Next), !,
    bfs_other(Next, End, Path).
bfs_other([_|T], End, L) :- bfs_other(T, End, L).

construct_path([_], []) :- !.
construct_path([X, Y|T], [R|Res]) :-
    relation(R, X, Y),
    construct_path([Y|T], Res).
```

Наш конечный предикат, выводящий отношение между X и Y:

```prolog
search_relation(X, Y, R) :- 
    bfs(X, Y, Buf),
    construct_path(Buf, R).
```

Примеры работы
```prolog
?- search_relation("Bridget Murphy", "Rose Elizabeth Fitzgerald", R).
R = [husband, grandmother] .
?- search_relation("John Fitzgerald Jack Kennedy", "Patrick Kennedy", R). 
R = [son, grandson] .
?- search_relation("Mary Josephine Hannon", "John Francis Honey Fitz Fitzgerald", R). 
R = [wife] .
```

## Естественно-языковый интерфейс

Реализация языкового интерфейса находится в файле `lex.pl`. Все наши запросы начинаются с предиката `launch`, с помощью него мы запускаем наш сеанс работы. Основным предикатами здесь выступают `query` - запросы, каждый из них содержит некоторое действие, выполняемое при работе с нашим запросом, понимаем, какое действие нам подходит по ключевым словам `What`, `Whose`, `Is` и т.д.

```prolog
launch(X) :- start(X, "").
start(X, N):- 
    split_string(X, " ", "", L), 
    maplist(atom_string, R, L),  
    query(R, N).

restart(N) :- read(X), nl,start(X, N).
```

Также было реализовано 2 особенности:

1. Программа способная запоминать лицо с предыдущего хода

Делается это с помощью предиката return, который также зацикливает нашу программу, для дальшнейшего выполнения запросов. Важной обязанностью является проверка, совпадает ли пол сохраненого нами лица, с текущим местоимением.

2. Нахождение количества родстенников

Для этого используется уже давно известный нам предикат `findall`, позволяющие найти все решения. Таким образом, если мы сложим эти решения в отдельный список и узнаем его длину это и будет ответом на поставленный перед нами вопрос. При выполнении этой части задания пригодился опыт полученный во время выполнения лабораторной работы №4. Хотелось бы отметить, что есть пути и учушение данной системы, к примеру применение русского языка и разбор на более глубокую структуру.

```prolog
query(['How', 'many'|T], Cache) :- 
    append(Rel, Part2, T),
    returnelem(Rel, Rel1),
    (append(['have'], ['him'], Part2), male(Cache), antirelation_m(Rel1, R),
    findall(N, (search_relation(Cache, N, [R]), male(N)), L), 
    length(L, Ans),!, write(Ans));
    (append(['have'], ['her'], Part2), female(Cache), antirelation_w(Rel1, R), 
    findall(N, (search_relation(Cache, N, [R]), female(N)), L), 
    length(L, Ans),!, write(Ans)), write("\n"), restart(Cache).
query(['How', 'many'|T], _) :- 
    append(Rel, Part2, T),
    append(['have'], Name1, Part2),
    returnelem(Rel, Rel1),
    atomic_list_concat(Name1, ' ', Atom1), atom_string(Atom1, String1),
    (male(String1), antirelation_m(Rel1, R), 
    findall(N, (search_relation(String1, N, [R]), male(N)), L), 
    length(L, Ans),!, write(Ans)); 
    (female(String1), antirelation_w(Rel1, R), 
    findall(N, (search_relation(String1, N, [R]), female(N)), L), 
    length(L, Ans),!, write(Ans)), write("\n"),restart(String1).
```

Примеры работы программый:
```prolog
?- launch("Whose father is Patrick Kennedy"). 
John Kennedy III
|    "Whose father is him".

John Kennedy III
|    "What relations between him and John Kennedy III".

[father]
|
false.
?- launch("How many children does have Patrick Kennedy").
5
|    "Whose husband is him".   

Bridget Murphy
|
false.
```

## Выводы

Выполняя задания данной курсовой работы, я еще сильнее закрепил знания полученные на курсе Логического программирования. Данное задания хорошо тем, что позволяет не только вспомнить уже слегка позабывшийся материал, но и применить его на практике. Больше всего меня поразила отличная работа Пролога в связке с алготмами поиска в дереве. Мне понравилось реализовавывать парсер и предикат определения родства, они показывают всю мощность пролога, что он способен решать задачи, сложные для других языков, в частности анализ текста. Данная работа была сложнее чем предыдущие, однако это только большего интереса её выполнять, так как полученные нами результаты уже действительно применимы в реальных задачах.
