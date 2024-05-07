%--------------------------------------------------------------------------
% File     : PUZ031+1 : TPTP v2.6.0. Released v2.0.0.
% Domain   : Puzzles
% Problem  : Schubert's Steamroller
% Version  : Especial.
% English  : Wolves, foxes, birds, caterpillars, and snails are animals, and
%            there are some of each of them. Also there are some grains, and
%            grains are plants. Every animal either likes to eat all plants
%            or all animals much smaller than itself that like to eat some
%            plants. Caterpillars and snails are much smaller than birds,
%            which are much smaller than foxes, which in turn are much
%            smaller than wolves. Wolves do not like to eat foxes or grains,
%            while birds like to eat caterpillars but not snails.
%            Caterpillars and snails like to eat some plants. Therefore
%            there is an animal that likes to eat a grain eating animal.

% Refs     : [Pel86] Pelletier (1986), Seventy-five Problems for Testing Au
%          : [Hah94] Haehnle (1994), Email to G. Sutcliffe
% Source   : [Hah94]
% Names    : Pelletier 47 [Pel86]

% Status   : theorem
% Rating   : 0.00 v2.5.0, 0.33 v2.4.0, 0.33 v2.2.1, 0.00 v2.1.0
% Syntax   : Number of formulae    :   21 (   6 unit)
%            Number of atoms       :   55 (   0 equality)
%            Maximal formula depth :    9 (   3 average)
%            Number of connectives :   36 (   2 ~  ;   4  |;  14  &)
%                                         (   0 <=>;  16 =>;   0 <=)
%                                         (   0 <~>;   0 ~|;   0 ~&)
%            Number of predicates  :   10 (   0 propositional; 1-2 arity)
%            Number of functors    :    0 (   0 constant; --- arity)
%            Number of variables   :   33 (   0 singleton;  22 !;  11 ?)
%            Maximal term depth    :    1 (   1 average)

% Comments : This problem is named after Len Schubert.
%--------------------------------------------------------------------------
input_formula(pel47_1_1,axiom,(
    ! [X] : 
      ( wolf(X)
     => animal(X) )   )).

input_formula(pel47_1_2,axiom,(
    ? [X1] : wolf(X1)   )).

input_formula(pel47_2_1,axiom,(
    ! [X] : 
      ( fox(X)
     => animal(X) )   )).

input_formula(pel47_2_2,axiom,(
    ? [X1] : fox(X1)   )).

input_formula(pel47_3_1,axiom,(
    ! [X] : 
      ( bird(X)
     => animal(X) )   )).

input_formula(pel47_3_2,axiom,(
    ? [X1] : bird(X1)   )).

input_formula(pel47_4_1,axiom,(
    ! [X] : 
      ( caterpillar(X)
     => animal(X) )   )).

input_formula(pel47_4_2,axiom,(
    ? [X1] : caterpillar(X1)   )).

input_formula(pel47_5_1,axiom,(
    ! [X] : 
      ( snail(X)
     => animal(X) )   )).

input_formula(pel47_5_2,axiom,(
    ? [X1] : snail(X1)   )).

input_formula(pel47_6_1,axiom,(
    ? [X] : grain(X)   )).

input_formula(pel47_6_2,axiom,(
    ! [X1] : 
      ( grain(X1)
     => plant(X1) )   )).

input_formula(pel47_7,axiom,(
    ! [X] : 
      ( animal(X)
     => ( ! [Y] : 
            ( plant(Y)
           => eats(X,Y) )
        | ! [Y1] : 
            ( ( ( animal(Y1)
                & much_smaller(Y1,X) )
              & ? [Z] : 
                  ( plant(Z)
                  & eats(Y1,Z) ) )
           => eats(X,Y1) ) ) )   )).

input_formula(pel47_8,axiom,(
    ! [X,Y] : 
      ( ( bird(Y)
        & ( snail(X)
          | caterpillar(X) ) )
     => much_smaller(X,Y) )   )).

input_formula(pel47_9,axiom,(
    ! [X,Y] : 
      ( ( bird(X)
        & fox(Y) )
     => much_smaller(X,Y) )   )).

input_formula(pel47_10,axiom,(
    ! [X,Y] : 
      ( ( fox(X)
        & wolf(Y) )
     => much_smaller(X,Y) )   )).

input_formula(pel47_11,axiom,(
    ! [X,Y] : 
      ( ( wolf(X)
        & ( fox(Y)
          | grain(Y) ) )
     => ~ eats(X,Y) )   )).

input_formula(pel47_12,axiom,(
    ! [X,Y] : 
      ( ( bird(X)
        & caterpillar(Y) )
     => eats(X,Y) )   )).

input_formula(pel47_13,axiom,(
    ! [X,Y] : 
      ( ( bird(X)
        & snail(Y) )
     => ~ eats(X,Y) )   )).

input_formula(pel47_14,axiom,(
    ! [X] : 
      ( ( caterpillar(X)
        | snail(X) )
     => ? [Y] : 
          ( plant(Y)
          & eats(X,Y) ) )   )).

input_formula(pel47,conjecture,(
    ? [X,Y] : 
      ( ( animal(X)
        & animal(Y) )
      & ? [Z] : 
          ( ( grain(Z)
            & eats(Y,Z) )
          & eats(X,Y) ) )   )).
%--------------------------------------------------------------------------
