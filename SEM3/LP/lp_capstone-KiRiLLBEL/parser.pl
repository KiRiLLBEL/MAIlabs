run(Lines) :- file_lines('lp_capstone-KiRiLLBEL/family.ged', Lines).
file_lines(File, Lines) :-
    open("lp_capstone-KiRiLLBEL/output.pl", write, Out),
    setup_call_cleanup(open(File, read, In),
       stream_lines(In, Lines, Out),
       close(In)),
    close(Out).

stream_lines(In, Lines, Out) :-
    read_string(In, _, Str),
    split_string(Str, "\n", "", Lines),
    write_struct(Lines, Out, List, 0),
    write_child(Lines, Out, List, _, 0).

write_struct([], _, _, _) :- !.
write_struct([""], _, _, _) :- !.
write_struct([" "], _, _, _) :- !.
write_struct([' '], _, _, _) :- !.

write_struct([H|T], Out, [ID:Name:Sex|R], N) :- 
    N < 3,
    split_string(H, ' ', '/', L),
    (N = 0, check_id(L,ID:Name:Sex), N1 is N + 1; 
    N = 1, check_name(L, ID:Name:Sex), N1 is N + 1; 
    N = 2, check_sex(L, ID:Name:Sex, Out), N1 is N + 1),
    write_struct(T, Out, [ID:Name:Sex|R], N1).

write_struct([_|T], Out, [ID:Name:Sex|R], N) :- 
    N < 3,
    write_struct(T, Out, [ID:Name:Sex|R], N).

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


write_child([""], _, _, _, _) :- !.
write_child([" "], _, _, _, _) :- !.
write_child([' '], _, _, _, _) :- !.

write_child([H|T], Out, List, [M:W|R],N) :-
    split_string(H, ' ', '', L),
    (N = 0, check_fam(L), N1 is N + 1),
    write_child(T, Out, List, [M:W|R],N1).
write_child([H|T], Out, List, [M:W|R],N) :-
    split_string(H, ' ', '', L),
    ((N > 0, check_m(L, M:W, List), N1 is N + 1); 
    (N > 0, check_w(L, M:W, List), N1 is N + 1); 
    (N > 0, check_c(L, M:W, List, Out), N1 is N + 1)),
    write_child(T, Out, List, [M:W|R],N1). 
write_child([H|T], Out, List, [_:_|R],N) :-
    split_string(H, ' ', '', L),
    (N > 0, check_fam(L)),
    write_child(T, Out, List, R, 1).
write_child([_|T], Out, List, L, N) :-
    write_child(T, Out, List, L, N).

check_fam([_, _, "FAM"|_]).

check_m([_, "HUSB", ID|_], Name:_, List) :-
    member(ID:Name:_, List).

check_w([_, "WIFE", ID|_], _:Name, List) :-
    member(ID:Name:_, List).

check_c([_, "CHIL", ID|_], M:W, List, Out) :-
    member(ID:Name:_, List),
    format(Out, '~q', [child(Name, M)]), write(Out,"."), write(Out,"\n"),
    format(Out, '~q', [child(Name, W)]), write(Out,"."), write(Out,"\n").

check_id([_, H2, "INDI"|_],H2:_:_).

check_name([_, "NAME", H3|T], _:Name:_) :- 
    full_name(H3, T, Name).

check_sex([_, "SEX", "F"|_], _:_:"F", _).
check_sex([_, "SEX", "M"|_], _:_:"M", _).

full_name(R, [], R).
full_name(Name, [X|T], A) :- 
    string_concat(Name, " ", R1),
    split_string(X, "", "\"", [X1]),
    string_concat(R1, X1, R),
    full_name(R, T, A).

write_person([], _).

write_person([_:Name:"F"|T], Out) :-
    format(Out, '~q', [female(Name)]),
    write_person(T, Out).

write_person([_:Name:"M"|T], Out) :-
    write(Out, male(Name)),
    write_person(T, Out).
