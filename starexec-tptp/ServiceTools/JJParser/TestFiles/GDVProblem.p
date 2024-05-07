%------------------------------------------------------------------------------
% File     : PUZ131_1 : TPTP v8.2.0. Released v5.0.0.
% Domain   : Puzzles
% Problem  : Victor teaches Michael
% Version  : Especial.
% English  : Every student is enrolled in at least one course. Every professor
%            teaches at least one course. Every course has at least one student
%            enrolled. Every course has at least one professor teaching. The
%            coordinator of a course teaches the course. If a student is
%            enroled in a course then the student is taught by every professor
%            who teaches the course. Michael is enrolled in CSC410. Victor is
%            the coordinator of CSC410. Therefore, Michael is taught by Victor.

% Refs     :
% Source   : [TPTP]
% Names    :

% Status   : Theorem
% Rating   : 0.00 v5.0.0
% Syntax   : Number of formulae    :   19 (   8 unt;  10 typ;   0 def)
%            Number of atoms       :   11 (   1 equ)
%            Maximal formula atoms :    3 (   0 avg)
%            Number of connectives :    2 (   0   ~;   0   |;   0   &)
%                                         (   0 <=>;   2  =>;   0  <=;   0 <~>)
%            Maximal formula depth :    6 (   3 avg)
%            Maximal term depth    :    2 (   1 avg)
%            Number of types       :    4 (   3 usr)
%            Number of type conns  :    7 (   4   >;   3   *;   0   +;   0  <<)
%            Number of predicates  :    4 (   3 usr;   0 prp; 2-2 aty)
%            Number of functors    :    4 (   4 usr;   3 con; 0-1 aty)
%            Number of variables   :   12 (   8   !;   4   ?;  12   :)
% SPC      : TF0_THM_EQU_NAR

% Comments :
%------------------------------------------------------------------------------
tff(student_type_0001,type,
    student: $tType ).

tff(professor_type_0002,type,
    professor: $tType ).

tff(course_type_0003,type,
    course: $tType ).

tff(michael_type_0004,type,
    michael: student ).

tff(victor_type_0005,type,
    victor: professor ).

tff(csc410_type_0006,type,
    csc410: course ).

tff(enrolled_type_0007,type,
    enrolled: ( student * course ) > $o ).

tff(teaches_type_0008,type,
    teaches: ( professor * course ) > $o ).

tff(taught_by_type_0009,type,
    taughtby: ( student * professor ) > $o ).

tff(coordinator_of_type_0010,type,
    coordinatorof: course > professor ).

tff(student_enrolled_axiom_0011,axiom,
    ! [X: student] :
    ? [Y: course] : enrolled(X,Y) ).

tff(professor_teaches_0012,axiom,
    ! [X: professor] :
    ? [Y: course] : teaches(X,Y) ).

tff(course_enrolled_0013,axiom,
    ! [X: course] :
    ? [Y: student] : enrolled(Y,X) ).

tff(course_teaches_0014,axiom,
    ! [X: course] :
    ? [Y: professor] : teaches(Y,X) ).

tff(coordinator_teaches_0015,axiom,
    ! [X: course] : teaches(coordinatorof(X),X) ).

tff(student_enrolled_taught_0016,axiom,
    ! [X: student,Y: course] :
      ( enrolled(X,Y)
     => ! [Z: professor] :
          ( teaches(Z,Y)
         => taughtby(X,Z) ) ) ).

tff(michael_enrolled_csc410_axiom_0017,axiom,
    enrolled(michael,csc410) ).

tff(victor_coordinator_csc410_axiom_0018,axiom,
    coordinatorof(csc410) = victor ).

tff(teaching_conjecture_0019,conjecture,
    taughtby(michael,victor) ).

%------------------------------------------------------------------------------
