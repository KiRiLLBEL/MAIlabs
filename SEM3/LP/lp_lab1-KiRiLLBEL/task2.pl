:- ['one.pl'].

% Стандартные предикаты
length_c([], 0).
length_c([_|X], N) :- 
    length_c(X, N1), N is N1 + 1.

member_c(X, [X|_]).
member_c(X, [_|T]) :- 
    member_c(X, T).

remove_c(X, [X|T], T).
remove_c(X, [Y|T], [Y|T1]) :- 
    remove_c(X, T, T1).

% Напечатать средний балл для каждого предмета
sum([], 0).
sum([H|L], S) :- 
    sum(L, S1), S is S1 + H.

average([]):-!.
average([Subject|OtherSubjects]) :- 
    findall(Mark, grade(_, Subject, Mark), ListOfMarks), sum(ListOfMarks, SumOfMarks), 
    length_c(ListOfMarks, CountOfMarks), Average is SumOfMarks / CountOfMarks, 
    write(Subject), write(" = "),format('~2f~n', [Average]), 
    average(OtherSubjects).

solution_1() :- findall(Subject, subject(Subject, _), ListOfSubjects), average(ListOfSubjects).

% Для каждой группы, найти количество не сдавших студентов 
group_count(SetOfGroups) :-
    findall(Group, student(Group, _), ListOfGroups), setof(Buf, member_c(Buf, ListOfGroups), SetOfGroups).

group_fail([]) :- !.
group_fail([Group|OtherGroups]) :- 
    findall(Name, (student(Group,Name), grade(Name, _, Mark), Mark = 2), ListOfMarks), 
    setof(UniqName, member_c(UniqName, ListOfMarks), ListOfNames),
    write(Group), write(" = "), 
    length_c(ListOfNames, CountOfFail), write(CountOfFail), write("\n"),
    group_fail(OtherGroups). 

solution_2() :- group_count(ListOfGroups), group_fail(ListOfGroups).

% Найти количество не сдавших студентов для каждого из предметов
subject_fail([]) :- !.
subject_fail([Subject|OtherSubjects]) :- 
    findall(Mark, (grade(_, Subject, Mark), Mark = 2), ListOfMarks), length_c(ListOfMarks, CountOfFail), 
    write(Subject), write(" = "),write(CountOfFail),write("\n"),
    subject_fail(OtherSubjects).

solution_3() :- findall(Subject, subject(Subject, _), ListOfSubjects), subject_fail(ListOfSubjects).