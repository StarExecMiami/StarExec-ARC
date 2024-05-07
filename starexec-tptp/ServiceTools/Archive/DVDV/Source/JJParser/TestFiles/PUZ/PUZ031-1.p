%--------------------------------------------------------------------------
% File     : PUZ031-1 : TPTP v2.6.0. Released v1.0.0.
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

% Refs     : [Sti86] Stickel (1986), Schubert's Steamroller Problem: Formul
%          : [Pel86] Pelletier (1986), Seventy-five Problems for Testing Au
%          : [WB87]  Wang & Bledsoe (1987), Hierarchical Deduction
%          : [MB88]  Manthey & Bry (1988), SATCHMO: A Theorem Prover Implem
% Source   : [Pel86]
% Names    : Pelletier 47 [Pel86]
%          : steamroller.ver1.in [ANL]
%          : steam.in [OTTER]
%          : SST [WB87]

% Status   : unsatisfiable
% Rating   : 0.00 v2.2.1, 0.25 v2.1.0, 0.00 v2.0.0
% Syntax   : Number of clauses    :   26 (   1 non-Horn;   6 unit;  26 RR)
%            Number of literals   :   63 (   0 equality)
%            Maximal clause size  :    8 (   2 average)
%            Number of predicates :   10 (   0 propositional; 1-2 arity)
%            Number of functors   :    8 (   6 constant; 0-1 arity)
%            Number of variables  :   33 (   0 singleton)
%            Maximal term depth   :    2 (   1 average)

% Comments : This problem is named after Len Schubert.
%--------------------------------------------------------------------------
input_clause(wolf_is_an_animal,axiom,
    [++animal(X),
     --wolf(X)]).

input_clause(fox_is_an_animal,axiom,
    [++animal(X),
     --fox(X)]).

input_clause(bird_is_an_animal,axiom,
    [++animal(X),
     --bird(X)]).

input_clause(caterpillar_is_an_animal,axiom,
    [++animal(X),
     --caterpillar(X)]).

input_clause(snail_is_an_animal,axiom,
    [++animal(X),
     --snail(X)]).

input_clause(there_is_a_wolf,axiom,
    [++wolf(a_wolf)]).

input_clause(there_is_a_fox,axiom,
    [++fox(a_fox)]).

input_clause(there_is_a_bird,axiom,
    [++bird(a_bird)]).

input_clause(there_is_a_caterpillar,axiom,
    [++caterpillar(a_caterpillar)]).

input_clause(there_is_a_snail,axiom,
    [++snail(a_snail)]).

input_clause(there_is_a_grain,axiom,
    [++grain(a_grain)]).

input_clause(grain_is_a_plant,axiom,
    [++plant(X),
     --grain(X)]).

input_clause(eating_habits,axiom,
    [++eats(Animal,Plant),
     ++eats(Animal,Small_animal),
     --animal(Animal),
     --plant(Plant),
     --animal(Small_animal),
     --plant(Other_plant),
     --much_smaller(Small_animal,Animal),
     --eats(Small_animal,Other_plant)]).

input_clause(caterpillar_smaller_than_bird,axiom,
    [++much_smaller(Catapillar,Bird),
     --caterpillar(Catapillar),
     --bird(Bird)]).

input_clause(snail_smaller_than_bird,axiom,
    [++much_smaller(Snail,Bird),
     --snail(Snail),
     --bird(Bird)]).

input_clause(bird_smaller_than_fox,axiom,
    [++much_smaller(Bird,Fox),
     --bird(Bird),
     --fox(Fox)]).

input_clause(fox_smaller_than_wolf,axiom,
    [++much_smaller(Fox,Wolf),
     --fox(Fox),
     --wolf(Wolf)]).

input_clause(wolf_dont_eat_fox,axiom,
    [--wolf(Wolf),
     --fox(Fox),
     --eats(Wolf,Fox)]).

input_clause(wolf_dont_eat_grain,axiom,
    [--wolf(Wolf),
     --grain(Grain),
     --eats(Wolf,Grain)]).

input_clause(bird_eats_caterpillar,axiom,
    [++eats(Bird,Catapillar),
     --bird(Bird),
     --caterpillar(Catapillar)]).

input_clause(bird_dont_eat_snail,axiom,
    [--bird(Bird),
     --snail(Snail),
     --eats(Bird,Snail)]).

input_clause(caterpillar_food_is_a_plant,axiom,
    [++plant(caterpillar_food_of(Catapillar)),
     --caterpillar(Catapillar)]).

input_clause(caterpillar_eats_caterpillar_food,axiom,
    [++eats(Catapillar,caterpillar_food_of(Catapillar)),
     --caterpillar(Catapillar)]).

input_clause(snail_food_is_a_plant,axiom,
    [++plant(snail_food_of(Snail)),
     --snail(Snail)]).

input_clause(snail_eats_snail_food,axiom,
    [++eats(Snail,snail_food_of(Snail)),
     --snail(Snail)]).

input_clause(prove_the_animal_exists,conjecture,
    [--animal(Animal),
     --animal(Grain_eater),
     --grain(Grain),
     --eats(Animal,Grain_eater),
     --eats(Grain_eater,Grain)]).
%--------------------------------------------------------------------------
