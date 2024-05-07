// Generated from TPTP.g4 by ANTLR 4.10.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link TPTPParser}.
 */
public interface TPTPListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tptp_file}.
	 * @param ctx the parse tree
	 */
	void enterTptp_file(TPTPParser.Tptp_fileContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tptp_file}.
	 * @param ctx the parse tree
	 */
	void exitTptp_file(TPTPParser.Tptp_fileContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tptp_input}.
	 * @param ctx the parse tree
	 */
	void enterTptp_input(TPTPParser.Tptp_inputContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tptp_input}.
	 * @param ctx the parse tree
	 */
	void exitTptp_input(TPTPParser.Tptp_inputContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#annotated_formula}.
	 * @param ctx the parse tree
	 */
	void enterAnnotated_formula(TPTPParser.Annotated_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#annotated_formula}.
	 * @param ctx the parse tree
	 */
	void exitAnnotated_formula(TPTPParser.Annotated_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tpi_annotated}.
	 * @param ctx the parse tree
	 */
	void enterTpi_annotated(TPTPParser.Tpi_annotatedContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tpi_annotated}.
	 * @param ctx the parse tree
	 */
	void exitTpi_annotated(TPTPParser.Tpi_annotatedContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tpi_formula}.
	 * @param ctx the parse tree
	 */
	void enterTpi_formula(TPTPParser.Tpi_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tpi_formula}.
	 * @param ctx the parse tree
	 */
	void exitTpi_formula(TPTPParser.Tpi_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_annotated}.
	 * @param ctx the parse tree
	 */
	void enterThf_annotated(TPTPParser.Thf_annotatedContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_annotated}.
	 * @param ctx the parse tree
	 */
	void exitThf_annotated(TPTPParser.Thf_annotatedContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_annotated}.
	 * @param ctx the parse tree
	 */
	void enterTff_annotated(TPTPParser.Tff_annotatedContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_annotated}.
	 * @param ctx the parse tree
	 */
	void exitTff_annotated(TPTPParser.Tff_annotatedContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tcf_annotated}.
	 * @param ctx the parse tree
	 */
	void enterTcf_annotated(TPTPParser.Tcf_annotatedContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tcf_annotated}.
	 * @param ctx the parse tree
	 */
	void exitTcf_annotated(TPTPParser.Tcf_annotatedContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_annotated}.
	 * @param ctx the parse tree
	 */
	void enterFof_annotated(TPTPParser.Fof_annotatedContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_annotated}.
	 * @param ctx the parse tree
	 */
	void exitFof_annotated(TPTPParser.Fof_annotatedContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#cnf_annotated}.
	 * @param ctx the parse tree
	 */
	void enterCnf_annotated(TPTPParser.Cnf_annotatedContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#cnf_annotated}.
	 * @param ctx the parse tree
	 */
	void exitCnf_annotated(TPTPParser.Cnf_annotatedContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#annotations}.
	 * @param ctx the parse tree
	 */
	void enterAnnotations(TPTPParser.AnnotationsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#annotations}.
	 * @param ctx the parse tree
	 */
	void exitAnnotations(TPTPParser.AnnotationsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#formula_role}.
	 * @param ctx the parse tree
	 */
	void enterFormula_role(TPTPParser.Formula_roleContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#formula_role}.
	 * @param ctx the parse tree
	 */
	void exitFormula_role(TPTPParser.Formula_roleContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_formula(TPTPParser.Thf_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_formula(TPTPParser.Thf_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_logic_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_logic_formula(TPTPParser.Thf_logic_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_logic_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_logic_formula(TPTPParser.Thf_logic_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_binary_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_binary_formula(TPTPParser.Thf_binary_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_binary_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_binary_formula(TPTPParser.Thf_binary_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_binary_nonassoc}.
	 * @param ctx the parse tree
	 */
	void enterThf_binary_nonassoc(TPTPParser.Thf_binary_nonassocContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_binary_nonassoc}.
	 * @param ctx the parse tree
	 */
	void exitThf_binary_nonassoc(TPTPParser.Thf_binary_nonassocContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_binary_assoc}.
	 * @param ctx the parse tree
	 */
	void enterThf_binary_assoc(TPTPParser.Thf_binary_assocContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_binary_assoc}.
	 * @param ctx the parse tree
	 */
	void exitThf_binary_assoc(TPTPParser.Thf_binary_assocContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_or_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_or_formula(TPTPParser.Thf_or_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_or_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_or_formula(TPTPParser.Thf_or_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_and_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_and_formula(TPTPParser.Thf_and_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_and_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_and_formula(TPTPParser.Thf_and_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_apply_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_apply_formula(TPTPParser.Thf_apply_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_apply_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_apply_formula(TPTPParser.Thf_apply_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_unit_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_unit_formula(TPTPParser.Thf_unit_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_unit_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_unit_formula(TPTPParser.Thf_unit_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_preunit_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_preunit_formula(TPTPParser.Thf_preunit_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_preunit_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_preunit_formula(TPTPParser.Thf_preunit_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_unitary_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_unitary_formula(TPTPParser.Thf_unitary_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_unitary_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_unitary_formula(TPTPParser.Thf_unitary_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_quantified_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_quantified_formula(TPTPParser.Thf_quantified_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_quantified_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_quantified_formula(TPTPParser.Thf_quantified_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_quantification}.
	 * @param ctx the parse tree
	 */
	void enterThf_quantification(TPTPParser.Thf_quantificationContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_quantification}.
	 * @param ctx the parse tree
	 */
	void exitThf_quantification(TPTPParser.Thf_quantificationContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_variable_list}.
	 * @param ctx the parse tree
	 */
	void enterThf_variable_list(TPTPParser.Thf_variable_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_variable_list}.
	 * @param ctx the parse tree
	 */
	void exitThf_variable_list(TPTPParser.Thf_variable_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_variable}.
	 * @param ctx the parse tree
	 */
	void enterThf_variable(TPTPParser.Thf_variableContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_variable}.
	 * @param ctx the parse tree
	 */
	void exitThf_variable(TPTPParser.Thf_variableContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_typed_variable}.
	 * @param ctx the parse tree
	 */
	void enterThf_typed_variable(TPTPParser.Thf_typed_variableContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_typed_variable}.
	 * @param ctx the parse tree
	 */
	void exitThf_typed_variable(TPTPParser.Thf_typed_variableContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_unary_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_unary_formula(TPTPParser.Thf_unary_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_unary_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_unary_formula(TPTPParser.Thf_unary_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_prefix_unary}.
	 * @param ctx the parse tree
	 */
	void enterThf_prefix_unary(TPTPParser.Thf_prefix_unaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_prefix_unary}.
	 * @param ctx the parse tree
	 */
	void exitThf_prefix_unary(TPTPParser.Thf_prefix_unaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_infix_unary}.
	 * @param ctx the parse tree
	 */
	void enterThf_infix_unary(TPTPParser.Thf_infix_unaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_infix_unary}.
	 * @param ctx the parse tree
	 */
	void exitThf_infix_unary(TPTPParser.Thf_infix_unaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void enterThf_atomic_formula(TPTPParser.Thf_atomic_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void exitThf_atomic_formula(TPTPParser.Thf_atomic_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_plain_atomic}.
	 * @param ctx the parse tree
	 */
	void enterThf_plain_atomic(TPTPParser.Thf_plain_atomicContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_plain_atomic}.
	 * @param ctx the parse tree
	 */
	void exitThf_plain_atomic(TPTPParser.Thf_plain_atomicContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_defined_atomic}.
	 * @param ctx the parse tree
	 */
	void enterThf_defined_atomic(TPTPParser.Thf_defined_atomicContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_defined_atomic}.
	 * @param ctx the parse tree
	 */
	void exitThf_defined_atomic(TPTPParser.Thf_defined_atomicContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_defined_term}.
	 * @param ctx the parse tree
	 */
	void enterThf_defined_term(TPTPParser.Thf_defined_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_defined_term}.
	 * @param ctx the parse tree
	 */
	void exitThf_defined_term(TPTPParser.Thf_defined_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_defined_infix}.
	 * @param ctx the parse tree
	 */
	void enterThf_defined_infix(TPTPParser.Thf_defined_infixContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_defined_infix}.
	 * @param ctx the parse tree
	 */
	void exitThf_defined_infix(TPTPParser.Thf_defined_infixContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_system_atomic}.
	 * @param ctx the parse tree
	 */
	void enterThf_system_atomic(TPTPParser.Thf_system_atomicContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_system_atomic}.
	 * @param ctx the parse tree
	 */
	void exitThf_system_atomic(TPTPParser.Thf_system_atomicContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_let}.
	 * @param ctx the parse tree
	 */
	void enterThf_let(TPTPParser.Thf_letContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_let}.
	 * @param ctx the parse tree
	 */
	void exitThf_let(TPTPParser.Thf_letContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_let_types}.
	 * @param ctx the parse tree
	 */
	void enterThf_let_types(TPTPParser.Thf_let_typesContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_let_types}.
	 * @param ctx the parse tree
	 */
	void exitThf_let_types(TPTPParser.Thf_let_typesContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_atom_typing_list}.
	 * @param ctx the parse tree
	 */
	void enterThf_atom_typing_list(TPTPParser.Thf_atom_typing_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_atom_typing_list}.
	 * @param ctx the parse tree
	 */
	void exitThf_atom_typing_list(TPTPParser.Thf_atom_typing_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_let_defns}.
	 * @param ctx the parse tree
	 */
	void enterThf_let_defns(TPTPParser.Thf_let_defnsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_let_defns}.
	 * @param ctx the parse tree
	 */
	void exitThf_let_defns(TPTPParser.Thf_let_defnsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_let_defn}.
	 * @param ctx the parse tree
	 */
	void enterThf_let_defn(TPTPParser.Thf_let_defnContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_let_defn}.
	 * @param ctx the parse tree
	 */
	void exitThf_let_defn(TPTPParser.Thf_let_defnContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_let_defn_list}.
	 * @param ctx the parse tree
	 */
	void enterThf_let_defn_list(TPTPParser.Thf_let_defn_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_let_defn_list}.
	 * @param ctx the parse tree
	 */
	void exitThf_let_defn_list(TPTPParser.Thf_let_defn_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_unitary_term}.
	 * @param ctx the parse tree
	 */
	void enterThf_unitary_term(TPTPParser.Thf_unitary_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_unitary_term}.
	 * @param ctx the parse tree
	 */
	void exitThf_unitary_term(TPTPParser.Thf_unitary_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_conn_term}.
	 * @param ctx the parse tree
	 */
	void enterThf_conn_term(TPTPParser.Thf_conn_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_conn_term}.
	 * @param ctx the parse tree
	 */
	void exitThf_conn_term(TPTPParser.Thf_conn_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_tuple}.
	 * @param ctx the parse tree
	 */
	void enterThf_tuple(TPTPParser.Thf_tupleContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_tuple}.
	 * @param ctx the parse tree
	 */
	void exitThf_tuple(TPTPParser.Thf_tupleContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_fof_function}.
	 * @param ctx the parse tree
	 */
	void enterThf_fof_function(TPTPParser.Thf_fof_functionContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_fof_function}.
	 * @param ctx the parse tree
	 */
	void exitThf_fof_function(TPTPParser.Thf_fof_functionContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_arguments}.
	 * @param ctx the parse tree
	 */
	void enterThf_arguments(TPTPParser.Thf_argumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_arguments}.
	 * @param ctx the parse tree
	 */
	void exitThf_arguments(TPTPParser.Thf_argumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_formula_list}.
	 * @param ctx the parse tree
	 */
	void enterThf_formula_list(TPTPParser.Thf_formula_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_formula_list}.
	 * @param ctx the parse tree
	 */
	void exitThf_formula_list(TPTPParser.Thf_formula_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_atom_typing}.
	 * @param ctx the parse tree
	 */
	void enterThf_atom_typing(TPTPParser.Thf_atom_typingContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_atom_typing}.
	 * @param ctx the parse tree
	 */
	void exitThf_atom_typing(TPTPParser.Thf_atom_typingContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_top_level_type}.
	 * @param ctx the parse tree
	 */
	void enterThf_top_level_type(TPTPParser.Thf_top_level_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_top_level_type}.
	 * @param ctx the parse tree
	 */
	void exitThf_top_level_type(TPTPParser.Thf_top_level_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_unitary_type}.
	 * @param ctx the parse tree
	 */
	void enterThf_unitary_type(TPTPParser.Thf_unitary_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_unitary_type}.
	 * @param ctx the parse tree
	 */
	void exitThf_unitary_type(TPTPParser.Thf_unitary_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_apply_type}.
	 * @param ctx the parse tree
	 */
	void enterThf_apply_type(TPTPParser.Thf_apply_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_apply_type}.
	 * @param ctx the parse tree
	 */
	void exitThf_apply_type(TPTPParser.Thf_apply_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_binary_type}.
	 * @param ctx the parse tree
	 */
	void enterThf_binary_type(TPTPParser.Thf_binary_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_binary_type}.
	 * @param ctx the parse tree
	 */
	void exitThf_binary_type(TPTPParser.Thf_binary_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_mapping_type}.
	 * @param ctx the parse tree
	 */
	void enterThf_mapping_type(TPTPParser.Thf_mapping_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_mapping_type}.
	 * @param ctx the parse tree
	 */
	void exitThf_mapping_type(TPTPParser.Thf_mapping_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_xprod_type}.
	 * @param ctx the parse tree
	 */
	void enterThf_xprod_type(TPTPParser.Thf_xprod_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_xprod_type}.
	 * @param ctx the parse tree
	 */
	void exitThf_xprod_type(TPTPParser.Thf_xprod_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_union_type}.
	 * @param ctx the parse tree
	 */
	void enterThf_union_type(TPTPParser.Thf_union_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_union_type}.
	 * @param ctx the parse tree
	 */
	void exitThf_union_type(TPTPParser.Thf_union_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_subtype}.
	 * @param ctx the parse tree
	 */
	void enterThf_subtype(TPTPParser.Thf_subtypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_subtype}.
	 * @param ctx the parse tree
	 */
	void exitThf_subtype(TPTPParser.Thf_subtypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_definition}.
	 * @param ctx the parse tree
	 */
	void enterThf_definition(TPTPParser.Thf_definitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_definition}.
	 * @param ctx the parse tree
	 */
	void exitThf_definition(TPTPParser.Thf_definitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_sequent}.
	 * @param ctx the parse tree
	 */
	void enterThf_sequent(TPTPParser.Thf_sequentContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_sequent}.
	 * @param ctx the parse tree
	 */
	void exitThf_sequent(TPTPParser.Thf_sequentContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_formula(TPTPParser.Tff_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_formula(TPTPParser.Tff_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_logic_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_logic_formula(TPTPParser.Tff_logic_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_logic_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_logic_formula(TPTPParser.Tff_logic_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_binary_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_binary_formula(TPTPParser.Tff_binary_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_binary_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_binary_formula(TPTPParser.Tff_binary_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_binary_nonassoc}.
	 * @param ctx the parse tree
	 */
	void enterTff_binary_nonassoc(TPTPParser.Tff_binary_nonassocContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_binary_nonassoc}.
	 * @param ctx the parse tree
	 */
	void exitTff_binary_nonassoc(TPTPParser.Tff_binary_nonassocContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_binary_assoc}.
	 * @param ctx the parse tree
	 */
	void enterTff_binary_assoc(TPTPParser.Tff_binary_assocContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_binary_assoc}.
	 * @param ctx the parse tree
	 */
	void exitTff_binary_assoc(TPTPParser.Tff_binary_assocContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_or_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_or_formula(TPTPParser.Tff_or_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_or_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_or_formula(TPTPParser.Tff_or_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_and_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_and_formula(TPTPParser.Tff_and_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_and_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_and_formula(TPTPParser.Tff_and_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_unit_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_unit_formula(TPTPParser.Tff_unit_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_unit_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_unit_formula(TPTPParser.Tff_unit_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_preunit_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_preunit_formula(TPTPParser.Tff_preunit_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_preunit_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_preunit_formula(TPTPParser.Tff_preunit_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_unitary_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_unitary_formula(TPTPParser.Tff_unitary_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_unitary_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_unitary_formula(TPTPParser.Tff_unitary_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_unitary_formula}.
	 * @param ctx the parse tree
	 */
	void enterTxf_unitary_formula(TPTPParser.Txf_unitary_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_unitary_formula}.
	 * @param ctx the parse tree
	 */
	void exitTxf_unitary_formula(TPTPParser.Txf_unitary_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_quantified_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_quantified_formula(TPTPParser.Tff_quantified_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_quantified_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_quantified_formula(TPTPParser.Tff_quantified_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_variable_list}.
	 * @param ctx the parse tree
	 */
	void enterTff_variable_list(TPTPParser.Tff_variable_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_variable_list}.
	 * @param ctx the parse tree
	 */
	void exitTff_variable_list(TPTPParser.Tff_variable_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_variable}.
	 * @param ctx the parse tree
	 */
	void enterTff_variable(TPTPParser.Tff_variableContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_variable}.
	 * @param ctx the parse tree
	 */
	void exitTff_variable(TPTPParser.Tff_variableContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_typed_variable}.
	 * @param ctx the parse tree
	 */
	void enterTff_typed_variable(TPTPParser.Tff_typed_variableContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_typed_variable}.
	 * @param ctx the parse tree
	 */
	void exitTff_typed_variable(TPTPParser.Tff_typed_variableContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_unary_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_unary_formula(TPTPParser.Tff_unary_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_unary_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_unary_formula(TPTPParser.Tff_unary_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_prefix_unary}.
	 * @param ctx the parse tree
	 */
	void enterTff_prefix_unary(TPTPParser.Tff_prefix_unaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_prefix_unary}.
	 * @param ctx the parse tree
	 */
	void exitTff_prefix_unary(TPTPParser.Tff_prefix_unaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_infix_unary}.
	 * @param ctx the parse tree
	 */
	void enterTff_infix_unary(TPTPParser.Tff_infix_unaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_infix_unary}.
	 * @param ctx the parse tree
	 */
	void exitTff_infix_unary(TPTPParser.Tff_infix_unaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void enterTff_atomic_formula(TPTPParser.Tff_atomic_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void exitTff_atomic_formula(TPTPParser.Tff_atomic_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_plain_atomic}.
	 * @param ctx the parse tree
	 */
	void enterTff_plain_atomic(TPTPParser.Tff_plain_atomicContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_plain_atomic}.
	 * @param ctx the parse tree
	 */
	void exitTff_plain_atomic(TPTPParser.Tff_plain_atomicContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_defined_atomic}.
	 * @param ctx the parse tree
	 */
	void enterTff_defined_atomic(TPTPParser.Tff_defined_atomicContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_defined_atomic}.
	 * @param ctx the parse tree
	 */
	void exitTff_defined_atomic(TPTPParser.Tff_defined_atomicContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_defined_plain}.
	 * @param ctx the parse tree
	 */
	void enterTff_defined_plain(TPTPParser.Tff_defined_plainContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_defined_plain}.
	 * @param ctx the parse tree
	 */
	void exitTff_defined_plain(TPTPParser.Tff_defined_plainContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_defined_infix}.
	 * @param ctx the parse tree
	 */
	void enterTff_defined_infix(TPTPParser.Tff_defined_infixContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_defined_infix}.
	 * @param ctx the parse tree
	 */
	void exitTff_defined_infix(TPTPParser.Tff_defined_infixContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_system_atomic}.
	 * @param ctx the parse tree
	 */
	void enterTff_system_atomic(TPTPParser.Tff_system_atomicContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_system_atomic}.
	 * @param ctx the parse tree
	 */
	void exitTff_system_atomic(TPTPParser.Tff_system_atomicContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_let}.
	 * @param ctx the parse tree
	 */
	void enterTxf_let(TPTPParser.Txf_letContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_let}.
	 * @param ctx the parse tree
	 */
	void exitTxf_let(TPTPParser.Txf_letContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_let_types}.
	 * @param ctx the parse tree
	 */
	void enterTxf_let_types(TPTPParser.Txf_let_typesContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_let_types}.
	 * @param ctx the parse tree
	 */
	void exitTxf_let_types(TPTPParser.Txf_let_typesContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_atom_typing_list}.
	 * @param ctx the parse tree
	 */
	void enterTff_atom_typing_list(TPTPParser.Tff_atom_typing_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_atom_typing_list}.
	 * @param ctx the parse tree
	 */
	void exitTff_atom_typing_list(TPTPParser.Tff_atom_typing_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_let_defns}.
	 * @param ctx the parse tree
	 */
	void enterTxf_let_defns(TPTPParser.Txf_let_defnsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_let_defns}.
	 * @param ctx the parse tree
	 */
	void exitTxf_let_defns(TPTPParser.Txf_let_defnsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_let_defn}.
	 * @param ctx the parse tree
	 */
	void enterTxf_let_defn(TPTPParser.Txf_let_defnContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_let_defn}.
	 * @param ctx the parse tree
	 */
	void exitTxf_let_defn(TPTPParser.Txf_let_defnContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_let_LHS}.
	 * @param ctx the parse tree
	 */
	void enterTxf_let_LHS(TPTPParser.Txf_let_LHSContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_let_LHS}.
	 * @param ctx the parse tree
	 */
	void exitTxf_let_LHS(TPTPParser.Txf_let_LHSContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_let_defn_list}.
	 * @param ctx the parse tree
	 */
	void enterTxf_let_defn_list(TPTPParser.Txf_let_defn_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_let_defn_list}.
	 * @param ctx the parse tree
	 */
	void exitTxf_let_defn_list(TPTPParser.Txf_let_defn_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_ntf_atom}.
	 * @param ctx the parse tree
	 */
	void enterTxf_ntf_atom(TPTPParser.Txf_ntf_atomContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_ntf_atom}.
	 * @param ctx the parse tree
	 */
	void exitTxf_ntf_atom(TPTPParser.Txf_ntf_atomContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_term}.
	 * @param ctx the parse tree
	 */
	void enterTff_term(TPTPParser.Tff_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_term}.
	 * @param ctx the parse tree
	 */
	void exitTff_term(TPTPParser.Tff_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_unitary_term}.
	 * @param ctx the parse tree
	 */
	void enterTff_unitary_term(TPTPParser.Tff_unitary_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_unitary_term}.
	 * @param ctx the parse tree
	 */
	void exitTff_unitary_term(TPTPParser.Tff_unitary_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_tuple}.
	 * @param ctx the parse tree
	 */
	void enterTxf_tuple(TPTPParser.Txf_tupleContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_tuple}.
	 * @param ctx the parse tree
	 */
	void exitTxf_tuple(TPTPParser.Txf_tupleContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_arguments}.
	 * @param ctx the parse tree
	 */
	void enterTff_arguments(TPTPParser.Tff_argumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_arguments}.
	 * @param ctx the parse tree
	 */
	void exitTff_arguments(TPTPParser.Tff_argumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_atom_typing}.
	 * @param ctx the parse tree
	 */
	void enterTff_atom_typing(TPTPParser.Tff_atom_typingContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_atom_typing}.
	 * @param ctx the parse tree
	 */
	void exitTff_atom_typing(TPTPParser.Tff_atom_typingContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_top_level_type}.
	 * @param ctx the parse tree
	 */
	void enterTff_top_level_type(TPTPParser.Tff_top_level_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_top_level_type}.
	 * @param ctx the parse tree
	 */
	void exitTff_top_level_type(TPTPParser.Tff_top_level_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_non_atomic_type}.
	 * @param ctx the parse tree
	 */
	void enterTff_non_atomic_type(TPTPParser.Tff_non_atomic_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_non_atomic_type}.
	 * @param ctx the parse tree
	 */
	void exitTff_non_atomic_type(TPTPParser.Tff_non_atomic_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tf1_quantified_type}.
	 * @param ctx the parse tree
	 */
	void enterTf1_quantified_type(TPTPParser.Tf1_quantified_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tf1_quantified_type}.
	 * @param ctx the parse tree
	 */
	void exitTf1_quantified_type(TPTPParser.Tf1_quantified_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_monotype}.
	 * @param ctx the parse tree
	 */
	void enterTff_monotype(TPTPParser.Tff_monotypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_monotype}.
	 * @param ctx the parse tree
	 */
	void exitTff_monotype(TPTPParser.Tff_monotypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_unitary_type}.
	 * @param ctx the parse tree
	 */
	void enterTff_unitary_type(TPTPParser.Tff_unitary_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_unitary_type}.
	 * @param ctx the parse tree
	 */
	void exitTff_unitary_type(TPTPParser.Tff_unitary_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_atomic_type}.
	 * @param ctx the parse tree
	 */
	void enterTff_atomic_type(TPTPParser.Tff_atomic_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_atomic_type}.
	 * @param ctx the parse tree
	 */
	void exitTff_atomic_type(TPTPParser.Tff_atomic_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_type_arguments}.
	 * @param ctx the parse tree
	 */
	void enterTff_type_arguments(TPTPParser.Tff_type_argumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_type_arguments}.
	 * @param ctx the parse tree
	 */
	void exitTff_type_arguments(TPTPParser.Tff_type_argumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_mapping_type}.
	 * @param ctx the parse tree
	 */
	void enterTff_mapping_type(TPTPParser.Tff_mapping_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_mapping_type}.
	 * @param ctx the parse tree
	 */
	void exitTff_mapping_type(TPTPParser.Tff_mapping_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_xprod_type}.
	 * @param ctx the parse tree
	 */
	void enterTff_xprod_type(TPTPParser.Tff_xprod_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_xprod_type}.
	 * @param ctx the parse tree
	 */
	void exitTff_xprod_type(TPTPParser.Tff_xprod_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_tuple_type}.
	 * @param ctx the parse tree
	 */
	void enterTxf_tuple_type(TPTPParser.Txf_tuple_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_tuple_type}.
	 * @param ctx the parse tree
	 */
	void exitTxf_tuple_type(TPTPParser.Txf_tuple_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_type_list}.
	 * @param ctx the parse tree
	 */
	void enterTff_type_list(TPTPParser.Tff_type_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_type_list}.
	 * @param ctx the parse tree
	 */
	void exitTff_type_list(TPTPParser.Tff_type_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tff_subtype}.
	 * @param ctx the parse tree
	 */
	void enterTff_subtype(TPTPParser.Tff_subtypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tff_subtype}.
	 * @param ctx the parse tree
	 */
	void exitTff_subtype(TPTPParser.Tff_subtypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_definition}.
	 * @param ctx the parse tree
	 */
	void enterTxf_definition(TPTPParser.Txf_definitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_definition}.
	 * @param ctx the parse tree
	 */
	void exitTxf_definition(TPTPParser.Txf_definitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#txf_sequent}.
	 * @param ctx the parse tree
	 */
	void enterTxf_sequent(TPTPParser.Txf_sequentContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#txf_sequent}.
	 * @param ctx the parse tree
	 */
	void exitTxf_sequent(TPTPParser.Txf_sequentContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#ntf_connective}.
	 * @param ctx the parse tree
	 */
	void enterNtf_connective(TPTPParser.Ntf_connectiveContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#ntf_connective}.
	 * @param ctx the parse tree
	 */
	void exitNtf_connective(TPTPParser.Ntf_connectiveContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#ntf_short_connective}.
	 * @param ctx the parse tree
	 */
	void enterNtf_short_connective(TPTPParser.Ntf_short_connectiveContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#ntf_short_connective}.
	 * @param ctx the parse tree
	 */
	void exitNtf_short_connective(TPTPParser.Ntf_short_connectiveContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#ntf_long_connective}.
	 * @param ctx the parse tree
	 */
	void enterNtf_long_connective(TPTPParser.Ntf_long_connectiveContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#ntf_long_connective}.
	 * @param ctx the parse tree
	 */
	void exitNtf_long_connective(TPTPParser.Ntf_long_connectiveContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#ntf_connective_name}.
	 * @param ctx the parse tree
	 */
	void enterNtf_connective_name(TPTPParser.Ntf_connective_nameContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#ntf_connective_name}.
	 * @param ctx the parse tree
	 */
	void exitNtf_connective_name(TPTPParser.Ntf_connective_nameContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#ntf_parameter_list}.
	 * @param ctx the parse tree
	 */
	void enterNtf_parameter_list(TPTPParser.Ntf_parameter_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#ntf_parameter_list}.
	 * @param ctx the parse tree
	 */
	void exitNtf_parameter_list(TPTPParser.Ntf_parameter_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#ntf_parameter}.
	 * @param ctx the parse tree
	 */
	void enterNtf_parameter(TPTPParser.Ntf_parameterContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#ntf_parameter}.
	 * @param ctx the parse tree
	 */
	void exitNtf_parameter(TPTPParser.Ntf_parameterContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#ntf_index}.
	 * @param ctx the parse tree
	 */
	void enterNtf_index(TPTPParser.Ntf_indexContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#ntf_index}.
	 * @param ctx the parse tree
	 */
	void exitNtf_index(TPTPParser.Ntf_indexContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#ntf_key_pair}.
	 * @param ctx the parse tree
	 */
	void enterNtf_key_pair(TPTPParser.Ntf_key_pairContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#ntf_key_pair}.
	 * @param ctx the parse tree
	 */
	void exitNtf_key_pair(TPTPParser.Ntf_key_pairContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#logic_defn_rule}.
	 * @param ctx the parse tree
	 */
	void enterLogic_defn_rule(TPTPParser.Logic_defn_ruleContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#logic_defn_rule}.
	 * @param ctx the parse tree
	 */
	void exitLogic_defn_rule(TPTPParser.Logic_defn_ruleContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#logic_defn_LHS}.
	 * @param ctx the parse tree
	 */
	void enterLogic_defn_LHS(TPTPParser.Logic_defn_LHSContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#logic_defn_LHS}.
	 * @param ctx the parse tree
	 */
	void exitLogic_defn_LHS(TPTPParser.Logic_defn_LHSContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#logic_defn_RHS}.
	 * @param ctx the parse tree
	 */
	void enterLogic_defn_RHS(TPTPParser.Logic_defn_RHSContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#logic_defn_RHS}.
	 * @param ctx the parse tree
	 */
	void exitLogic_defn_RHS(TPTPParser.Logic_defn_RHSContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tcf_formula}.
	 * @param ctx the parse tree
	 */
	void enterTcf_formula(TPTPParser.Tcf_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tcf_formula}.
	 * @param ctx the parse tree
	 */
	void exitTcf_formula(TPTPParser.Tcf_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tcf_logic_formula}.
	 * @param ctx the parse tree
	 */
	void enterTcf_logic_formula(TPTPParser.Tcf_logic_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tcf_logic_formula}.
	 * @param ctx the parse tree
	 */
	void exitTcf_logic_formula(TPTPParser.Tcf_logic_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#tcf_quantified_formula}.
	 * @param ctx the parse tree
	 */
	void enterTcf_quantified_formula(TPTPParser.Tcf_quantified_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#tcf_quantified_formula}.
	 * @param ctx the parse tree
	 */
	void exitTcf_quantified_formula(TPTPParser.Tcf_quantified_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_formula(TPTPParser.Fof_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_formula(TPTPParser.Fof_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_logic_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_logic_formula(TPTPParser.Fof_logic_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_logic_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_logic_formula(TPTPParser.Fof_logic_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_binary_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_binary_formula(TPTPParser.Fof_binary_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_binary_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_binary_formula(TPTPParser.Fof_binary_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_binary_nonassoc}.
	 * @param ctx the parse tree
	 */
	void enterFof_binary_nonassoc(TPTPParser.Fof_binary_nonassocContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_binary_nonassoc}.
	 * @param ctx the parse tree
	 */
	void exitFof_binary_nonassoc(TPTPParser.Fof_binary_nonassocContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_binary_assoc}.
	 * @param ctx the parse tree
	 */
	void enterFof_binary_assoc(TPTPParser.Fof_binary_assocContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_binary_assoc}.
	 * @param ctx the parse tree
	 */
	void exitFof_binary_assoc(TPTPParser.Fof_binary_assocContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_or_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_or_formula(TPTPParser.Fof_or_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_or_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_or_formula(TPTPParser.Fof_or_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_and_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_and_formula(TPTPParser.Fof_and_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_and_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_and_formula(TPTPParser.Fof_and_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_unary_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_unary_formula(TPTPParser.Fof_unary_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_unary_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_unary_formula(TPTPParser.Fof_unary_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_infix_unary}.
	 * @param ctx the parse tree
	 */
	void enterFof_infix_unary(TPTPParser.Fof_infix_unaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_infix_unary}.
	 * @param ctx the parse tree
	 */
	void exitFof_infix_unary(TPTPParser.Fof_infix_unaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_unit_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_unit_formula(TPTPParser.Fof_unit_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_unit_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_unit_formula(TPTPParser.Fof_unit_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_unitary_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_unitary_formula(TPTPParser.Fof_unitary_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_unitary_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_unitary_formula(TPTPParser.Fof_unitary_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_quantified_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_quantified_formula(TPTPParser.Fof_quantified_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_quantified_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_quantified_formula(TPTPParser.Fof_quantified_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_variable_list}.
	 * @param ctx the parse tree
	 */
	void enterFof_variable_list(TPTPParser.Fof_variable_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_variable_list}.
	 * @param ctx the parse tree
	 */
	void exitFof_variable_list(TPTPParser.Fof_variable_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_atomic_formula(TPTPParser.Fof_atomic_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_atomic_formula(TPTPParser.Fof_atomic_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_plain_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_plain_atomic_formula(TPTPParser.Fof_plain_atomic_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_plain_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_plain_atomic_formula(TPTPParser.Fof_plain_atomic_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_defined_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_defined_atomic_formula(TPTPParser.Fof_defined_atomic_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_defined_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_defined_atomic_formula(TPTPParser.Fof_defined_atomic_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_defined_plain_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_defined_plain_formula(TPTPParser.Fof_defined_plain_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_defined_plain_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_defined_plain_formula(TPTPParser.Fof_defined_plain_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_defined_infix_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_defined_infix_formula(TPTPParser.Fof_defined_infix_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_defined_infix_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_defined_infix_formula(TPTPParser.Fof_defined_infix_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_system_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void enterFof_system_atomic_formula(TPTPParser.Fof_system_atomic_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_system_atomic_formula}.
	 * @param ctx the parse tree
	 */
	void exitFof_system_atomic_formula(TPTPParser.Fof_system_atomic_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_plain_term}.
	 * @param ctx the parse tree
	 */
	void enterFof_plain_term(TPTPParser.Fof_plain_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_plain_term}.
	 * @param ctx the parse tree
	 */
	void exitFof_plain_term(TPTPParser.Fof_plain_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_defined_term}.
	 * @param ctx the parse tree
	 */
	void enterFof_defined_term(TPTPParser.Fof_defined_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_defined_term}.
	 * @param ctx the parse tree
	 */
	void exitFof_defined_term(TPTPParser.Fof_defined_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_defined_atomic_term}.
	 * @param ctx the parse tree
	 */
	void enterFof_defined_atomic_term(TPTPParser.Fof_defined_atomic_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_defined_atomic_term}.
	 * @param ctx the parse tree
	 */
	void exitFof_defined_atomic_term(TPTPParser.Fof_defined_atomic_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_defined_plain_term}.
	 * @param ctx the parse tree
	 */
	void enterFof_defined_plain_term(TPTPParser.Fof_defined_plain_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_defined_plain_term}.
	 * @param ctx the parse tree
	 */
	void exitFof_defined_plain_term(TPTPParser.Fof_defined_plain_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_system_term}.
	 * @param ctx the parse tree
	 */
	void enterFof_system_term(TPTPParser.Fof_system_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_system_term}.
	 * @param ctx the parse tree
	 */
	void exitFof_system_term(TPTPParser.Fof_system_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_arguments}.
	 * @param ctx the parse tree
	 */
	void enterFof_arguments(TPTPParser.Fof_argumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_arguments}.
	 * @param ctx the parse tree
	 */
	void exitFof_arguments(TPTPParser.Fof_argumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_term}.
	 * @param ctx the parse tree
	 */
	void enterFof_term(TPTPParser.Fof_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_term}.
	 * @param ctx the parse tree
	 */
	void exitFof_term(TPTPParser.Fof_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_function_term}.
	 * @param ctx the parse tree
	 */
	void enterFof_function_term(TPTPParser.Fof_function_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_function_term}.
	 * @param ctx the parse tree
	 */
	void exitFof_function_term(TPTPParser.Fof_function_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_sequent}.
	 * @param ctx the parse tree
	 */
	void enterFof_sequent(TPTPParser.Fof_sequentContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_sequent}.
	 * @param ctx the parse tree
	 */
	void exitFof_sequent(TPTPParser.Fof_sequentContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_formula_tuple}.
	 * @param ctx the parse tree
	 */
	void enterFof_formula_tuple(TPTPParser.Fof_formula_tupleContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_formula_tuple}.
	 * @param ctx the parse tree
	 */
	void exitFof_formula_tuple(TPTPParser.Fof_formula_tupleContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_formula_tuple_list}.
	 * @param ctx the parse tree
	 */
	void enterFof_formula_tuple_list(TPTPParser.Fof_formula_tuple_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_formula_tuple_list}.
	 * @param ctx the parse tree
	 */
	void exitFof_formula_tuple_list(TPTPParser.Fof_formula_tuple_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#cnf_formula}.
	 * @param ctx the parse tree
	 */
	void enterCnf_formula(TPTPParser.Cnf_formulaContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#cnf_formula}.
	 * @param ctx the parse tree
	 */
	void exitCnf_formula(TPTPParser.Cnf_formulaContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#cnf_disjunction}.
	 * @param ctx the parse tree
	 */
	void enterCnf_disjunction(TPTPParser.Cnf_disjunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#cnf_disjunction}.
	 * @param ctx the parse tree
	 */
	void exitCnf_disjunction(TPTPParser.Cnf_disjunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#cnf_literal}.
	 * @param ctx the parse tree
	 */
	void enterCnf_literal(TPTPParser.Cnf_literalContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#cnf_literal}.
	 * @param ctx the parse tree
	 */
	void exitCnf_literal(TPTPParser.Cnf_literalContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#thf_quantifier}.
	 * @param ctx the parse tree
	 */
	void enterThf_quantifier(TPTPParser.Thf_quantifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#thf_quantifier}.
	 * @param ctx the parse tree
	 */
	void exitThf_quantifier(TPTPParser.Thf_quantifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#th1_quantifier}.
	 * @param ctx the parse tree
	 */
	void enterTh1_quantifier(TPTPParser.Th1_quantifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#th1_quantifier}.
	 * @param ctx the parse tree
	 */
	void exitTh1_quantifier(TPTPParser.Th1_quantifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#th0_quantifier}.
	 * @param ctx the parse tree
	 */
	void enterTh0_quantifier(TPTPParser.Th0_quantifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#th0_quantifier}.
	 * @param ctx the parse tree
	 */
	void exitTh0_quantifier(TPTPParser.Th0_quantifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#fof_quantifier}.
	 * @param ctx the parse tree
	 */
	void enterFof_quantifier(TPTPParser.Fof_quantifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#fof_quantifier}.
	 * @param ctx the parse tree
	 */
	void exitFof_quantifier(TPTPParser.Fof_quantifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#nonassoc_connective}.
	 * @param ctx the parse tree
	 */
	void enterNonassoc_connective(TPTPParser.Nonassoc_connectiveContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#nonassoc_connective}.
	 * @param ctx the parse tree
	 */
	void exitNonassoc_connective(TPTPParser.Nonassoc_connectiveContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#assoc_connective}.
	 * @param ctx the parse tree
	 */
	void enterAssoc_connective(TPTPParser.Assoc_connectiveContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#assoc_connective}.
	 * @param ctx the parse tree
	 */
	void exitAssoc_connective(TPTPParser.Assoc_connectiveContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#unary_connective}.
	 * @param ctx the parse tree
	 */
	void enterUnary_connective(TPTPParser.Unary_connectiveContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#unary_connective}.
	 * @param ctx the parse tree
	 */
	void exitUnary_connective(TPTPParser.Unary_connectiveContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#type_constant}.
	 * @param ctx the parse tree
	 */
	void enterType_constant(TPTPParser.Type_constantContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#type_constant}.
	 * @param ctx the parse tree
	 */
	void exitType_constant(TPTPParser.Type_constantContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#type_functor}.
	 * @param ctx the parse tree
	 */
	void enterType_functor(TPTPParser.Type_functorContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#type_functor}.
	 * @param ctx the parse tree
	 */
	void exitType_functor(TPTPParser.Type_functorContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#defined_type}.
	 * @param ctx the parse tree
	 */
	void enterDefined_type(TPTPParser.Defined_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#defined_type}.
	 * @param ctx the parse tree
	 */
	void exitDefined_type(TPTPParser.Defined_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#system_type}.
	 * @param ctx the parse tree
	 */
	void enterSystem_type(TPTPParser.System_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#system_type}.
	 * @param ctx the parse tree
	 */
	void exitSystem_type(TPTPParser.System_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#atom}.
	 * @param ctx the parse tree
	 */
	void enterAtom(TPTPParser.AtomContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#atom}.
	 * @param ctx the parse tree
	 */
	void exitAtom(TPTPParser.AtomContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#untyped_atom}.
	 * @param ctx the parse tree
	 */
	void enterUntyped_atom(TPTPParser.Untyped_atomContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#untyped_atom}.
	 * @param ctx the parse tree
	 */
	void exitUntyped_atom(TPTPParser.Untyped_atomContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#defined_proposition}.
	 * @param ctx the parse tree
	 */
	void enterDefined_proposition(TPTPParser.Defined_propositionContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#defined_proposition}.
	 * @param ctx the parse tree
	 */
	void exitDefined_proposition(TPTPParser.Defined_propositionContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#defined_predicate}.
	 * @param ctx the parse tree
	 */
	void enterDefined_predicate(TPTPParser.Defined_predicateContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#defined_predicate}.
	 * @param ctx the parse tree
	 */
	void exitDefined_predicate(TPTPParser.Defined_predicateContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#defined_infix_pred}.
	 * @param ctx the parse tree
	 */
	void enterDefined_infix_pred(TPTPParser.Defined_infix_predContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#defined_infix_pred}.
	 * @param ctx the parse tree
	 */
	void exitDefined_infix_pred(TPTPParser.Defined_infix_predContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#constant}.
	 * @param ctx the parse tree
	 */
	void enterConstant(TPTPParser.ConstantContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#constant}.
	 * @param ctx the parse tree
	 */
	void exitConstant(TPTPParser.ConstantContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#functor}.
	 * @param ctx the parse tree
	 */
	void enterFunctor(TPTPParser.FunctorContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#functor}.
	 * @param ctx the parse tree
	 */
	void exitFunctor(TPTPParser.FunctorContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#defined_constant}.
	 * @param ctx the parse tree
	 */
	void enterDefined_constant(TPTPParser.Defined_constantContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#defined_constant}.
	 * @param ctx the parse tree
	 */
	void exitDefined_constant(TPTPParser.Defined_constantContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#defined_functor}.
	 * @param ctx the parse tree
	 */
	void enterDefined_functor(TPTPParser.Defined_functorContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#defined_functor}.
	 * @param ctx the parse tree
	 */
	void exitDefined_functor(TPTPParser.Defined_functorContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#system_constant}.
	 * @param ctx the parse tree
	 */
	void enterSystem_constant(TPTPParser.System_constantContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#system_constant}.
	 * @param ctx the parse tree
	 */
	void exitSystem_constant(TPTPParser.System_constantContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#system_functor}.
	 * @param ctx the parse tree
	 */
	void enterSystem_functor(TPTPParser.System_functorContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#system_functor}.
	 * @param ctx the parse tree
	 */
	void exitSystem_functor(TPTPParser.System_functorContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#def_or_sys_constant}.
	 * @param ctx the parse tree
	 */
	void enterDef_or_sys_constant(TPTPParser.Def_or_sys_constantContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#def_or_sys_constant}.
	 * @param ctx the parse tree
	 */
	void exitDef_or_sys_constant(TPTPParser.Def_or_sys_constantContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#th1_defined_term}.
	 * @param ctx the parse tree
	 */
	void enterTh1_defined_term(TPTPParser.Th1_defined_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#th1_defined_term}.
	 * @param ctx the parse tree
	 */
	void exitTh1_defined_term(TPTPParser.Th1_defined_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#defined_term}.
	 * @param ctx the parse tree
	 */
	void enterDefined_term(TPTPParser.Defined_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#defined_term}.
	 * @param ctx the parse tree
	 */
	void exitDefined_term(TPTPParser.Defined_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#variable}.
	 * @param ctx the parse tree
	 */
	void enterVariable(TPTPParser.VariableContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#variable}.
	 * @param ctx the parse tree
	 */
	void exitVariable(TPTPParser.VariableContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#source}.
	 * @param ctx the parse tree
	 */
	void enterSource(TPTPParser.SourceContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#source}.
	 * @param ctx the parse tree
	 */
	void exitSource(TPTPParser.SourceContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#sources}.
	 * @param ctx the parse tree
	 */
	void enterSources(TPTPParser.SourcesContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#sources}.
	 * @param ctx the parse tree
	 */
	void exitSources(TPTPParser.SourcesContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#dag_source}.
	 * @param ctx the parse tree
	 */
	void enterDag_source(TPTPParser.Dag_sourceContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#dag_source}.
	 * @param ctx the parse tree
	 */
	void exitDag_source(TPTPParser.Dag_sourceContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#inference_record}.
	 * @param ctx the parse tree
	 */
	void enterInference_record(TPTPParser.Inference_recordContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#inference_record}.
	 * @param ctx the parse tree
	 */
	void exitInference_record(TPTPParser.Inference_recordContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#inference_rule}.
	 * @param ctx the parse tree
	 */
	void enterInference_rule(TPTPParser.Inference_ruleContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#inference_rule}.
	 * @param ctx the parse tree
	 */
	void exitInference_rule(TPTPParser.Inference_ruleContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#inference_parents}.
	 * @param ctx the parse tree
	 */
	void enterInference_parents(TPTPParser.Inference_parentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#inference_parents}.
	 * @param ctx the parse tree
	 */
	void exitInference_parents(TPTPParser.Inference_parentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#parent_list}.
	 * @param ctx the parse tree
	 */
	void enterParent_list(TPTPParser.Parent_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#parent_list}.
	 * @param ctx the parse tree
	 */
	void exitParent_list(TPTPParser.Parent_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#parent_info}.
	 * @param ctx the parse tree
	 */
	void enterParent_info(TPTPParser.Parent_infoContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#parent_info}.
	 * @param ctx the parse tree
	 */
	void exitParent_info(TPTPParser.Parent_infoContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#parent_details}.
	 * @param ctx the parse tree
	 */
	void enterParent_details(TPTPParser.Parent_detailsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#parent_details}.
	 * @param ctx the parse tree
	 */
	void exitParent_details(TPTPParser.Parent_detailsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#internal_source}.
	 * @param ctx the parse tree
	 */
	void enterInternal_source(TPTPParser.Internal_sourceContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#internal_source}.
	 * @param ctx the parse tree
	 */
	void exitInternal_source(TPTPParser.Internal_sourceContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#intro_type}.
	 * @param ctx the parse tree
	 */
	void enterIntro_type(TPTPParser.Intro_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#intro_type}.
	 * @param ctx the parse tree
	 */
	void exitIntro_type(TPTPParser.Intro_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#external_source}.
	 * @param ctx the parse tree
	 */
	void enterExternal_source(TPTPParser.External_sourceContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#external_source}.
	 * @param ctx the parse tree
	 */
	void exitExternal_source(TPTPParser.External_sourceContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#file_source}.
	 * @param ctx the parse tree
	 */
	void enterFile_source(TPTPParser.File_sourceContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#file_source}.
	 * @param ctx the parse tree
	 */
	void exitFile_source(TPTPParser.File_sourceContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#file_info}.
	 * @param ctx the parse tree
	 */
	void enterFile_info(TPTPParser.File_infoContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#file_info}.
	 * @param ctx the parse tree
	 */
	void exitFile_info(TPTPParser.File_infoContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#theory}.
	 * @param ctx the parse tree
	 */
	void enterTheory(TPTPParser.TheoryContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#theory}.
	 * @param ctx the parse tree
	 */
	void exitTheory(TPTPParser.TheoryContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#theory_name}.
	 * @param ctx the parse tree
	 */
	void enterTheory_name(TPTPParser.Theory_nameContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#theory_name}.
	 * @param ctx the parse tree
	 */
	void exitTheory_name(TPTPParser.Theory_nameContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#creator_source}.
	 * @param ctx the parse tree
	 */
	void enterCreator_source(TPTPParser.Creator_sourceContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#creator_source}.
	 * @param ctx the parse tree
	 */
	void exitCreator_source(TPTPParser.Creator_sourceContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#creator_name}.
	 * @param ctx the parse tree
	 */
	void enterCreator_name(TPTPParser.Creator_nameContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#creator_name}.
	 * @param ctx the parse tree
	 */
	void exitCreator_name(TPTPParser.Creator_nameContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#optional_info}.
	 * @param ctx the parse tree
	 */
	void enterOptional_info(TPTPParser.Optional_infoContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#optional_info}.
	 * @param ctx the parse tree
	 */
	void exitOptional_info(TPTPParser.Optional_infoContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#useful_info}.
	 * @param ctx the parse tree
	 */
	void enterUseful_info(TPTPParser.Useful_infoContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#useful_info}.
	 * @param ctx the parse tree
	 */
	void exitUseful_info(TPTPParser.Useful_infoContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#info_items}.
	 * @param ctx the parse tree
	 */
	void enterInfo_items(TPTPParser.Info_itemsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#info_items}.
	 * @param ctx the parse tree
	 */
	void exitInfo_items(TPTPParser.Info_itemsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#info_item}.
	 * @param ctx the parse tree
	 */
	void enterInfo_item(TPTPParser.Info_itemContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#info_item}.
	 * @param ctx the parse tree
	 */
	void exitInfo_item(TPTPParser.Info_itemContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#formula_item}.
	 * @param ctx the parse tree
	 */
	void enterFormula_item(TPTPParser.Formula_itemContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#formula_item}.
	 * @param ctx the parse tree
	 */
	void exitFormula_item(TPTPParser.Formula_itemContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#description_item}.
	 * @param ctx the parse tree
	 */
	void enterDescription_item(TPTPParser.Description_itemContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#description_item}.
	 * @param ctx the parse tree
	 */
	void exitDescription_item(TPTPParser.Description_itemContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#iquote_item}.
	 * @param ctx the parse tree
	 */
	void enterIquote_item(TPTPParser.Iquote_itemContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#iquote_item}.
	 * @param ctx the parse tree
	 */
	void exitIquote_item(TPTPParser.Iquote_itemContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#inference_item}.
	 * @param ctx the parse tree
	 */
	void enterInference_item(TPTPParser.Inference_itemContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#inference_item}.
	 * @param ctx the parse tree
	 */
	void exitInference_item(TPTPParser.Inference_itemContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#inference_status}.
	 * @param ctx the parse tree
	 */
	void enterInference_status(TPTPParser.Inference_statusContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#inference_status}.
	 * @param ctx the parse tree
	 */
	void exitInference_status(TPTPParser.Inference_statusContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#status_value}.
	 * @param ctx the parse tree
	 */
	void enterStatus_value(TPTPParser.Status_valueContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#status_value}.
	 * @param ctx the parse tree
	 */
	void exitStatus_value(TPTPParser.Status_valueContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#inference_info}.
	 * @param ctx the parse tree
	 */
	void enterInference_info(TPTPParser.Inference_infoContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#inference_info}.
	 * @param ctx the parse tree
	 */
	void exitInference_info(TPTPParser.Inference_infoContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#assumptions_record}.
	 * @param ctx the parse tree
	 */
	void enterAssumptions_record(TPTPParser.Assumptions_recordContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#assumptions_record}.
	 * @param ctx the parse tree
	 */
	void exitAssumptions_record(TPTPParser.Assumptions_recordContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#refutation}.
	 * @param ctx the parse tree
	 */
	void enterRefutation(TPTPParser.RefutationContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#refutation}.
	 * @param ctx the parse tree
	 */
	void exitRefutation(TPTPParser.RefutationContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#new_symbol_record}.
	 * @param ctx the parse tree
	 */
	void enterNew_symbol_record(TPTPParser.New_symbol_recordContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#new_symbol_record}.
	 * @param ctx the parse tree
	 */
	void exitNew_symbol_record(TPTPParser.New_symbol_recordContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#new_symbol_list}.
	 * @param ctx the parse tree
	 */
	void enterNew_symbol_list(TPTPParser.New_symbol_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#new_symbol_list}.
	 * @param ctx the parse tree
	 */
	void exitNew_symbol_list(TPTPParser.New_symbol_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#principal_symbol}.
	 * @param ctx the parse tree
	 */
	void enterPrincipal_symbol(TPTPParser.Principal_symbolContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#principal_symbol}.
	 * @param ctx the parse tree
	 */
	void exitPrincipal_symbol(TPTPParser.Principal_symbolContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#include}.
	 * @param ctx the parse tree
	 */
	void enterInclude(TPTPParser.IncludeContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#include}.
	 * @param ctx the parse tree
	 */
	void exitInclude(TPTPParser.IncludeContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#formula_selection}.
	 * @param ctx the parse tree
	 */
	void enterFormula_selection(TPTPParser.Formula_selectionContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#formula_selection}.
	 * @param ctx the parse tree
	 */
	void exitFormula_selection(TPTPParser.Formula_selectionContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#name_list}.
	 * @param ctx the parse tree
	 */
	void enterName_list(TPTPParser.Name_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#name_list}.
	 * @param ctx the parse tree
	 */
	void exitName_list(TPTPParser.Name_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#general_term}.
	 * @param ctx the parse tree
	 */
	void enterGeneral_term(TPTPParser.General_termContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#general_term}.
	 * @param ctx the parse tree
	 */
	void exitGeneral_term(TPTPParser.General_termContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#general_data}.
	 * @param ctx the parse tree
	 */
	void enterGeneral_data(TPTPParser.General_dataContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#general_data}.
	 * @param ctx the parse tree
	 */
	void exitGeneral_data(TPTPParser.General_dataContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#general_function}.
	 * @param ctx the parse tree
	 */
	void enterGeneral_function(TPTPParser.General_functionContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#general_function}.
	 * @param ctx the parse tree
	 */
	void exitGeneral_function(TPTPParser.General_functionContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#formula_data}.
	 * @param ctx the parse tree
	 */
	void enterFormula_data(TPTPParser.Formula_dataContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#formula_data}.
	 * @param ctx the parse tree
	 */
	void exitFormula_data(TPTPParser.Formula_dataContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#general_list}.
	 * @param ctx the parse tree
	 */
	void enterGeneral_list(TPTPParser.General_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#general_list}.
	 * @param ctx the parse tree
	 */
	void exitGeneral_list(TPTPParser.General_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#general_terms}.
	 * @param ctx the parse tree
	 */
	void enterGeneral_terms(TPTPParser.General_termsContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#general_terms}.
	 * @param ctx the parse tree
	 */
	void exitGeneral_terms(TPTPParser.General_termsContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#name}.
	 * @param ctx the parse tree
	 */
	void enterName(TPTPParser.NameContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#name}.
	 * @param ctx the parse tree
	 */
	void exitName(TPTPParser.NameContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#atomic_word}.
	 * @param ctx the parse tree
	 */
	void enterAtomic_word(TPTPParser.Atomic_wordContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#atomic_word}.
	 * @param ctx the parse tree
	 */
	void exitAtomic_word(TPTPParser.Atomic_wordContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#atomic_defined_word}.
	 * @param ctx the parse tree
	 */
	void enterAtomic_defined_word(TPTPParser.Atomic_defined_wordContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#atomic_defined_word}.
	 * @param ctx the parse tree
	 */
	void exitAtomic_defined_word(TPTPParser.Atomic_defined_wordContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#atomic_system_word}.
	 * @param ctx the parse tree
	 */
	void enterAtomic_system_word(TPTPParser.Atomic_system_wordContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#atomic_system_word}.
	 * @param ctx the parse tree
	 */
	void exitAtomic_system_word(TPTPParser.Atomic_system_wordContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#number}.
	 * @param ctx the parse tree
	 */
	void enterNumber(TPTPParser.NumberContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#number}.
	 * @param ctx the parse tree
	 */
	void exitNumber(TPTPParser.NumberContext ctx);
	/**
	 * Enter a parse tree produced by {@link TPTPParser#file_name}.
	 * @param ctx the parse tree
	 */
	void enterFile_name(TPTPParser.File_nameContext ctx);
	/**
	 * Exit a parse tree produced by {@link TPTPParser#file_name}.
	 * @param ctx the parse tree
	 */
	void exitFile_name(TPTPParser.File_nameContext ctx);
}