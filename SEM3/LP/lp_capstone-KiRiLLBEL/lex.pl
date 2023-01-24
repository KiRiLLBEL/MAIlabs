:- ['solution.pl'].
launch(X) :- start(X, "").
start(X, N):- 
    split_string(X, " ", "", L), 
    maplist(atom_string, R, L),  
    query(R, N).

restart(N) :- read(X), nl,start(X, N).

query(['Is'|T], Cache) :-
    append(['her'], Part2, T), female(Cache),
    append(Rel, Name2, Part2),
    atomic_list_concat(Name2, ' ', Atom2), atom_string(Atom2, String2),
    (male(String2); female(String2)),
    search_relation(Cache, String2, Rel), !, write("Yes!"), nl,restart(Cache).

query(['Is'|T], Cache) :-
    append(['him'], Part2, T), male(Cache),
    append(Rel, Name2, Part2),
    atomic_list_concat(Name2, ' ', Atom2), atom_string(Atom2, String2),
    (male(String2); female(String2)),
    search_relation(Cache, String2, Rel), !, write("Yes!"),write("\n") ,restart(Cache).

query(['Is'|T], _) :-
    append(Name1, Part2, T),
    append(Rel, Name2, Part2),
    atomic_list_concat(Name1, ' ', Atom1), atom_string(Atom1, String1),
    (male(String1); female(String1)), 
    atomic_list_concat(Name2, ' ', Atom2), atom_string(Atom2, String2),
    (male(String2); female(String2)),
    search_relation(String1, String2, Rel), !, write("Yes!"), write("\n"),restart(String1).

query(['Whose'|T], Cache) :-
    append(Rel, Part2, T),
    (append(['is'], ['her'], Part2), female(Cache)),
    search_relation(Cache, String2, Rel), !, write(String2), write("\n"),restart(Cache).
query(['Whose'|T], Cache) :-
    append(Rel, Part2, T),
    (append(['is'], ['him'], Part2), male(Cache)),
    search_relation(Cache, String2, Rel), !, write(String2),write("\n"), restart(Cache).

query(['Whose'|T], _) :-
    append(Rel, Part2, T),
    append(['is'], Name1, Part2),
    atomic_list_concat(Name1, ' ', Atom1), atom_string(Atom1, String1),
    (male(String1); female(String1)), 
    search_relation(String1, String2, Rel), !, write(String2), write("\n"),restart(String1).

query(['What','relations','between'|T], Cache) :- 
    append(['him'], Part2, T), male(Cache),
    append(['and'], Name2, Part2),
    atomic_list_concat(Name2, ' ', Atom2), atom_string(Atom2, String2),
    (male(String2); female(String2)),
    search_relation(Cache, String2, Rel), !, write(Rel),write("\n"), restart(Cache).

query(['What','relations','between'|T], Cache) :- 
    append(['her'], Part2, T), female(Cache),
    append(['and'], Name2, Part2),
    atomic_list_concat(Name2, ' ', Atom2), atom_string(Atom2, String2),
    (male(String2); female(String2)),
    search_relation(Cache, String2, Rel), !, write(Rel),write("\n"), restart(Cache).

query(['What','relations','between'|T], _) :- 
    append(Name1, Part2, T),
    append(['and'], Name2, Part2),
    atomic_list_concat(Name1, ' ', Atom1), atom_string(Atom1, String1),
    (male(String1); female(String1)), 
    atomic_list_concat(Name2, ' ', Atom2), atom_string(Atom2, String2),
    (male(String2); female(String2)),
    search_relation(String1, String2, Rel), !, write(Rel),write("\n"), restart(String1).

returnelem([R], R).

query(['How', 'many', 'children', 'does'|T], Cache) :- 
    append(['have'], ['him'], T), male(Cache),
    findall(N, search_relation(Cache, N, [father]), L), 
    length(L, Ans), !, write(Ans),write("\n"), restart(Cache).

query(['How', 'many', 'children', 'does'|T], Cache) :- 
    append(['have'], ['her'], T), female(Cache),
    findall(N, search_relation(Cache, N, [father]), L), 
    length(L, Ans), !, write(Ans), write("\n"),restart(Cache).

query(['How', 'many', 'children', 'does'|T], _) :- 
    append(['have'], Name1, T),
    atomic_list_concat(Name1, ' ', Atom1), atom_string(Atom1, String1),
    (male(String1); female(String1)), 
    findall(N, search_relation(String1, N, [father]), L), 
    length(L, Ans), !, write(Ans), write("\n"),restart(String1).
query(['How', 'many'|T], Cache) :- 
    append(Rel, Part2, T),
    returnelem(Rel, Rel1),
    (append(['does','have'], ['him'], Part2), male(Cache), antirelation_m(Rel1, R),
    findall(N, (search_relation(Cache, N, [R]), male(N)), L), 
    length(L, Ans),!, write(Ans));
    (append(['does','have'], ['her'], Part2), female(Cache), antirelation_w(Rel1, R), 
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

query(_,_) :- false.
