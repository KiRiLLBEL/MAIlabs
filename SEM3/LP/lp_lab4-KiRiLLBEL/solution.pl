% Задание операторов, необходимых для исчесления предикатов
:- op(900, xfx, =>).
:- op(800, xfy, &).
:- op(300, xfx, :).
% Ввод последовательности, разбиение на часть с сущиствительным и часть с глаголом
sequance(R, In) :-
    append(In1, In2, In),
    part_of_noun(X, In1, Buf, R),
    part_of_verb(X, In2, Buf).
% Часть существительного
part_of_noun(X, In, Buf, R) :-
    append(_, Buf1, In),
    % Определяем, необходим ли нам квантор
    quantifier(X, Buf1, Tmp, F, Buf, R),
    % Определяем наше существительное
    noun(X, Tmp, T, Person),
    % Смотрим, каким свойствами обладает наше существительное(that lives)
    properties(X, Person, T, F).
part_of_noun(X, In, R, R) :-
    name(X, In).
% Часть глагола
part_of_verb(X, Buf, R) :-
    % Определяем глагол
    verb1(X, Buf, R).
part_of_verb(X, Buf, R) :-
    % Определяем глагол
    verb2(X, Y, Buf, Tmp, R1), 
    % Определяем на какой объект направлено действие
    part_of_noun(Y, Tmp, R1, R).
% Выбираем квантор по определителю
quantifier(X, [every|Buf1], Buf1, F, Buf2, all(X):(F=>Buf2)).
quantifier(X, [a|Buf1], Buf1, F, Buf2, exists(X):(F&Buf2)). 

% Существительное
noun(X, [man|T], T, man(X)).
noun(X, [woman|T], T, woman(X)).

% Свойства сущиствительного
properties(X, Person, [that|Tail],Person&Properties) :-
    part_of_verb(X, Tail, Properties).
properties(_, Person, [], Person).

% Глагол
verb1(X, [lives], lives(X)).
verb2(X, Y, [loves|Tmp], Tmp, loves(X, Y)).

% Имена
name(ivan, [ivan]).
name(maria, [maria]).