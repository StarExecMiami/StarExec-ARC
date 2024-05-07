#ifndef COMPARE_H
#define COMPARE_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
#include "Utilities.h"
//-------------------------------------------------------------------------------------------------
typedef struct VariableRenamingTag {
    VARIABLENODE OriginalVariable;
    VARIABLENODE RenamedVariable;
    struct VariableRenamingTag * NextVariableRenaming;
} VariableRenamingNode;

typedef VariableRenamingNode * VARIABLERENAMING;
//-------------------------------------------------------------------------------------------------
int SameFormula(FORMULA Formula1,FORMULA Formula2,int AllowVariableRenaming,int AllowCommutation);
int SameFormulaInAnnotatedFormulae(ANNOTATEDFORMULA AnnotatedFormula1,
ANNOTATEDFORMULA AnnotatedFormula2,int AllowVariableRenaming,int AllowCommutation);
//-------------------------------------------------------------------------------------------------
#endif
