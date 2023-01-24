% Стандартные предикаты
length_c([], 0).
length_c([_|X], N) :- 
    length_c(X, N1), N is N1 + 1.

member_c(X, [X|_]).
member_c(X, [_|T]) :- 
    member_c(X, T).

append_c([], X, X).
append_c([A|X], Y, [A|Z]) :- 
    append_c(X, Y, Z).

remove_c(X, [X|T], T).
remove_c(X, [Y|T], [Y|T1]) :- 
    remove_c(X, T, T1).

permute_c([],[]).
permute_c(L, [X|T]) :- 
    remove_c(X, L, R), permute_c(R, T).

sublist_c(S,L) :- 
    append_c(_,L1,L), append_c(S,_,L1).

% Удаление первых N элементов без стандартных предикатов
remove_n_first(0, List, List).
remove_n_first(N, [_|Tail], Result) :- 
    remove_n_first(N1, Tail, Result), N is N1 + 1.

% Удаление первых N элементов с использованием стандартных предикатов
remove_n_first_c(N, List, Result) :- 
    append_c(Difference, Result, List), length_c(Difference,N).

% Лексикографическое сравнение без стандратных предикатов
compare_lex([], [], []) :- 
    write("=\n"), !.
compare_lex([], _, []) :- 
    write("<\n"), !.
compare_lex(_, [], []) :- 
    write(">\n"), !.

compare_lex([X|LeftTail], [Y|RightTail], [X|ResultTail]) :- 
    X=Y, compare_lex(LeftTail, RightTail, ResultTail).
compare_lex([X|LeftTail], [Y|_], [X|LeftTail]) :- 
    X < Y, write("<\n").
compare_lex([X|_], [Y|RightTail], [Y|RightTail]) :- 
    X > Y,  write(">\n").

% Лексикографическое сравнение с использованием стандратных предикатов
compare_difference(Left, Right) :-
    length(Left, LeftSize), LeftSize = 0,
    length(Right, RightSize), RightSize >= 0.

compare_difference([X|_], [Y|_]) :- X < Y.

compare_lex_c(Left, Right) :-
    append(Intersection, LeftTail, Left),
    append(Intersection, RightTail, Right),
    compare_difference(LeftTail, RightTail).

% Пример совмещения двух предикатов, сравнение всех элементов, кроме первых N.
compare_n(Left, Right, N, Result) :- 
    remove_n_first(N, Left, SliceL), 
    remove_n_first(N, Right, SliceR), 
    compare_lex(SliceL, SliceR, Result).