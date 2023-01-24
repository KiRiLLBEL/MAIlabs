:- ['output.pl'].

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

relation(grandmother, X, Y) :- grandmother(X, Y).
relation(grandfather, X, Y) :- grandfather(X, Y).
relation(grandson, X, Y) :- grandson(X, Y).
relation(granddouther, X, Y) :- granddouther(X, Y).
relation(cousin_f, X, Y) :- cousin_f(X, Y).
relation(cousin_m, X, Y) :- cousin_m(X, Y).
relation(husband, X, Y) :- husband(X, Y).
relation(wife, X, Y) :- wife(X, Y).
relation(son, X, Y) :- son(X, Y).
relation(douther, X, Y) :- douther(X, Y).
relation(brother, X, Y) :- brother(X, Y).
relation(sister, X, Y) :- sister(X, Y).
relation(father, X, Y) :- father(X, Y).
relation(mother, X, Y) :- mother(X, Y).

children(sons, dother).

antirelation_m(son, father).
antirelation_m(dother, father).
antirelation_m(grandson, grandfather).
antirelation_m(granddouther, grandfather).
antirelation_m(brother, sister).

antirelation_w(sister, brother).
antirelation_w(granddouther, grandmother).
antirelation_w(grandson, grandmother).
antirelation_w(dother, mother).
antirelation_w(son, mother).

move(X, Y) :- relation(_, X, Y).

prolong(5:[_|_], _:[_, _|_]) :- false.
prolong(C:[Now|T], C1:[Next, Now|T]) :-
    move(Now, Next),
    not(member(Next,[Now|T])),
    C1 is C + 1.


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
search_relation(X, Y, R) :- 
    bfs(X, Y, Buf),
    construct_path(Buf, R).
