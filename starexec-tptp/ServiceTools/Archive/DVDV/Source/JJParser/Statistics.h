#ifndef STATISTICS_H
#define STATISTICS_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"

typedef enum {
    nodes,
    fof_nodes,
    cnf_nodes,
//----For CNF problems
    count_horn_clauses,
    count_rr_clauses,

//----General
    unit_formulae,
    atoms,
    equality_atoms,
    terms,
    count_variables,
    count_singletons,
    count_formula_depth,
    count_term_depth,
    count_nothing
} CountType;

typedef enum {
    depth,
    literals,
    term_depth,
    formula_depth,
    maximize_nothing
} MaximizeType;

//-----------------------------------------------------------------------------
#endif
