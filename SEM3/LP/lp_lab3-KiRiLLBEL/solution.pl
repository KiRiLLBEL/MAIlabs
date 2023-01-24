% Описание предиката перехода состояний
move(Now, Next) :-
    append(H, [0, b|T], Now),
    append(H, [b, 0|T], Next).
move(Now, Next) :-
    append(H, [w, 0|T], Now),
    append(H, [0, w|T], Next).
move(Now, Next) :-
    append(H, [w, b, 0|T], Now),
    append(H, [0, b, w|T], Next).
move(Now, Next) :-
    append(H, [0, w, b|T], Now),
    append(H, [b, w, 0|T], Next).

% Предикат для вывода пути
print_list([], 0).
print_list([End|T], C) :-
    print_list(T, C1),
    C is C1 + 1,
    print(End),
    nl.

prolong([Now|T], [Next, Now|T]) :-
    move(Now, Next),
    not(member(Next, [Now|T])).
% Алгоритм dfs с подсчетом времени работы
dfs(Start, End) :- 
    get_time(Start_time), 
    dfs_other([Start], End, Length), !,
    get_time(Finish_time), 
    Time is Finish_time - Start_time,
    write("Statitics: "), write("Time: "), write(Time), write("\tLength: "), write(Length), nl.
dfs_other([End|T], End, Length) :- 
    print_list([End|T], C),
    Length=C.
dfs_other(Now, End, Length) :-
    prolong(Now, Next),
    dfs_other(Next, End, Length).

% Алгоритм bfs с подсчетом времени работы
bfs(Start, End) :-
    get_time(Start_time),
    bfs_other([[Start]], End, Length), !,
    get_time(Finish_time), 
    Time is Finish_time - Start_time,
    write("Statitics: "), write("Time: "), write(Time), write("\tLength: "), write(Length), nl.
bfs_other([[End|T]], End, Length) :- 
    print_list([End|T], C),
    Length=C.
bfs_other([Now|CheckTail], End, Length) :-
    findall(Z, prolong(Now, Z), T),
    append(CheckTail, T, Next), !,
    bfs_other(Next, End, Length).

% Поиск с итерационным погружением с подсчетом времени работы
% Предикат для генерации числе начиная с 1
integer_c(1).
integer_c(X) :-
    integer_c(Y),
    X is Y+1.

iddfs(Start, End) :-
    get_time(Start_time),
    integer_c(Level),
    depth_id([Start], End, Level, Length), !,
    get_time(Finish_time), 
    Time is Finish_time - Start_time,
    write("Statitics: "), write("Time: "), write(Time), write("\tLength: "), write(Length), nl.
depth_id([End|T], End, 0, Length) :- 
    print_list([End|T], C),
    Length=C.
depth_id(Path, End, N, Length) :-
    N > 0,
    prolong(Path, NextPath), 
    N1 is N - 1,
    depth_id(NextPath, End, N1, Length).

% Функция для подсчета эвристики
check_differ([],[],0).
check_differ([X|T],[Y|T1],C) :-
    X \= Y,
    check_differ(T, T1, C1),
    C is C1 + 1.
check_differ([X|T],[Y|T1],C) :-
    X = Y,
    check_differ(T, T1, C).

h(X, C, End) :- check_differ(X, End, C).
% Считаем сумму эвристики и стоимости перехода
weight(C:[X|_], C1, End) :- h(X, H, End), C1 is C + H.

prolong_a(C:[Now|T], C1:[Next, Now|T]) :-
    move(Now, Next),
    not(member(Next,[Now|T])),
    C1 is C + 1.

% Алгоритм a* с подсчетом времени работы
a*(Start, End) :-
    get_time(Start_time),
    a_search([0:[Start]], End, Length), !,
    get_time(Finish_time), 
    Time is Finish_time - Start_time,
    write("Statitics: "), write("Time: "), write(Time), write("\tLength: "), write(Length), nl.
a_search([_:[End|T]], End, Length) :-
    print_list([End|T], N),
    Length=N.
a_search([Now|Queue], End, Length) :-
    findall(Next, prolong_a(Now, Next), Ways),
    insertall(Ways, Queue, NewQueue, End),
    a_search(NewQueue, End, Length).

% Реализуем необходимые предикаты для специальной вставки в наш список состояний
insert(I, [P|T], [I, P|T], End) :-
    weight(I, C, End), weight(P, C1, End), C=<C1, !.
insert(I, [P|T], [P|R], End) :- 
    insert(I, T, R, End).
insert(P,[],[P], _).

insertall([], Queue, Queue, _).
insertall([P|T], Queue, ResQueue, End) :-
    insert(P, Queue, NewQueue, End),
    insertall(T, NewQueue, ResQueue, End).

% Основной предикат запускающий все алгоритмы
solve(Start, End) :-
    write("DFS START:"), nl,
    dfs(Start, End),
    write("DFS END"), nl, nl,
    print("BFS START:"), nl, 
    bfs(Start, End),
    write("BFS END"), nl, nl,
    write("IDDFS, START:"), nl,
    iddfs(Start, End),
    write("IDDFS, END"), nl, nl,
    write("A-STAR, START:"), nl,
    a*(Start, End),
    write("A-STAR, END"), nl, !.
