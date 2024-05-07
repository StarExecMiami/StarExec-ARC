// Generated from tptp_v7_0_0_0.g4 by ANTLR 4.10.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class tptp_v7_0_0_0Parser extends Parser {
	static { RuntimeMetaData.checkVersion("4.10.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, T__25=26, T__26=27, T__27=28, T__28=29, T__29=30, T__30=31, 
		T__31=32, T__32=33, T__33=34, T__34=35, T__35=36, T__36=37, T__37=38, 
		T__38=39, T__39=40, Or=41, And=42, Iff=43, Impl=44, If=45, Niff=46, Nor=47, 
		Nand=48, Not=49, ForallComb=50, TyForall=51, Infix_inequality=52, Infix_equality=53, 
		Forall=54, ExistsComb=55, TyExists=56, Exists=57, Lambda=58, ChoiceComb=59, 
		Choice=60, DescriptionComb=61, Description=62, EqComb=63, App=64, Assignment=65, 
		Identical=66, Arrow=67, Star=68, Plus=69, Hash=70, Subtype_sign=71, Gentzen_arrow=72, 
		Real=73, Signed_real=74, Unsigned_real=75, Rational=76, Signed_rational=77, 
		Unsigned_rational=78, Integer=79, Signed_integer=80, Unsigned_integer=81, 
		Decimal=82, Positive_decimal=83, Decimal_exponent=84, Decimal_fraction=85, 
		Dot_decimal=86, Exp_integer=87, Signed_exp_integer=88, Unsigned_exp_integer=89, 
		Dollar_word=90, Dollar_dollar_word=91, Upper_word=92, Lower_word=93, Single_quoted=94, 
		Distinct_object=95, WS=96, Line_comment=97, Block_comment=98;
	public static final int
		RULE_tptp_file = 0, RULE_tptp_input = 1, RULE_annotated_formula = 2, RULE_tpi_annotated = 3, 
		RULE_tpi_formula = 4, RULE_thf_annotated = 5, RULE_tff_annotated = 6, 
		RULE_tcf_annotated = 7, RULE_fof_annotated = 8, RULE_cnf_annotated = 9, 
		RULE_annotations = 10, RULE_formula_role = 11, RULE_thf_formula = 12, 
		RULE_thf_logic_formula = 13, RULE_thf_binary_formula = 14, RULE_thf_binary_nonassoc = 15, 
		RULE_thf_binary_assoc = 16, RULE_thf_or_formula = 17, RULE_thf_and_formula = 18, 
		RULE_thf_apply_formula = 19, RULE_thf_unit_formula = 20, RULE_thf_preunit_formula = 21, 
		RULE_thf_unitary_formula = 22, RULE_thf_quantified_formula = 23, RULE_thf_quantification = 24, 
		RULE_thf_variable_list = 25, RULE_thf_variable = 26, RULE_thf_typed_variable = 27, 
		RULE_thf_unary_formula = 28, RULE_thf_prefix_unary = 29, RULE_thf_infix_unary = 30, 
		RULE_thf_atomic_formula = 31, RULE_thf_plain_atomic = 32, RULE_thf_defined_atomic = 33, 
		RULE_thf_defined_term = 34, RULE_thf_defined_infix = 35, RULE_thf_system_atomic = 36, 
		RULE_thf_let = 37, RULE_thf_let_types = 38, RULE_thf_atom_typing_list = 39, 
		RULE_thf_let_defns = 40, RULE_thf_let_defn = 41, RULE_thf_let_defn_list = 42, 
		RULE_thf_unitary_term = 43, RULE_thf_conn_term = 44, RULE_thf_tuple = 45, 
		RULE_thf_fof_function = 46, RULE_thf_arguments = 47, RULE_thf_formula_list = 48, 
		RULE_thf_atom_typing = 49, RULE_thf_top_level_type = 50, RULE_thf_unitary_type = 51, 
		RULE_thf_apply_type = 52, RULE_thf_binary_type = 53, RULE_thf_mapping_type = 54, 
		RULE_thf_xprod_type = 55, RULE_thf_union_type = 56, RULE_thf_subtype = 57, 
		RULE_thf_definition = 58, RULE_thf_sequent = 59, RULE_tff_formula = 60, 
		RULE_tff_logic_formula = 61, RULE_tff_binary_formula = 62, RULE_tff_binary_nonassoc = 63, 
		RULE_tff_binary_assoc = 64, RULE_tff_or_formula = 65, RULE_tff_and_formula = 66, 
		RULE_tff_unit_formula = 67, RULE_tff_preunit_formula = 68, RULE_tff_unitary_formula = 69, 
		RULE_txf_unitary_formula = 70, RULE_tff_quantified_formula = 71, RULE_tff_variable_list = 72, 
		RULE_tff_variable = 73, RULE_tff_typed_variable = 74, RULE_tff_unary_formula = 75, 
		RULE_tff_prefix_unary = 76, RULE_tff_infix_unary = 77, RULE_tff_atomic_formula = 78, 
		RULE_tff_plain_atomic = 79, RULE_tff_defined_atomic = 80, RULE_tff_defined_plain = 81, 
		RULE_tff_defined_infix = 82, RULE_tff_system_atomic = 83, RULE_txf_let = 84, 
		RULE_txf_let_types = 85, RULE_tff_atom_typing_list = 86, RULE_txf_let_defns = 87, 
		RULE_txf_let_defn = 88, RULE_txf_let_LHS = 89, RULE_txf_let_defn_list = 90, 
		RULE_txf_ntf_atom = 91, RULE_tff_term = 92, RULE_tff_unitary_term = 93, 
		RULE_txf_tuple = 94, RULE_tff_arguments = 95, RULE_tff_atom_typing = 96, 
		RULE_tff_top_level_type = 97, RULE_tff_non_atomic_type = 98, RULE_tf1_quantified_type = 99, 
		RULE_tff_monotype = 100, RULE_tff_unitary_type = 101, RULE_tff_atomic_type = 102, 
		RULE_tff_type_arguments = 103, RULE_tff_mapping_type = 104, RULE_tff_xprod_type = 105, 
		RULE_txf_tuple_type = 106, RULE_tff_type_list = 107, RULE_tff_subtype = 108, 
		RULE_txf_definition = 109, RULE_txf_sequent = 110, RULE_ntf_connective = 111, 
		RULE_ntf_short_connective = 112, RULE_ntf_long_connective = 113, RULE_ntf_connective_name = 114, 
		RULE_ntf_parameter_list = 115, RULE_ntf_parameter = 116, RULE_ntf_index = 117, 
		RULE_ntf_key_pair = 118, RULE_logic_defn_rule = 119, RULE_logic_defn_LHS = 120, 
		RULE_logic_defn_RHS = 121, RULE_tcf_formula = 122, RULE_tcf_logic_formula = 123, 
		RULE_tcf_quantified_formula = 124, RULE_fof_formula = 125, RULE_fof_logic_formula = 126, 
		RULE_fof_binary_formula = 127, RULE_fof_binary_nonassoc = 128, RULE_fof_binary_assoc = 129, 
		RULE_fof_or_formula = 130, RULE_fof_and_formula = 131, RULE_fof_unary_formula = 132, 
		RULE_fof_infix_unary = 133, RULE_fof_unit_formula = 134, RULE_fof_unitary_formula = 135, 
		RULE_fof_quantified_formula = 136, RULE_fof_variable_list = 137, RULE_fof_atomic_formula = 138, 
		RULE_fof_plain_atomic_formula = 139, RULE_fof_defined_atomic_formula = 140, 
		RULE_fof_defined_plain_formula = 141, RULE_fof_defined_infix_formula = 142, 
		RULE_fof_system_atomic_formula = 143, RULE_fof_plain_term = 144, RULE_fof_defined_term = 145, 
		RULE_fof_defined_atomic_term = 146, RULE_fof_defined_plain_term = 147, 
		RULE_fof_system_term = 148, RULE_fof_arguments = 149, RULE_fof_term = 150, 
		RULE_fof_function_term = 151, RULE_fof_sequent = 152, RULE_fof_formula_tuple = 153, 
		RULE_fof_formula_tuple_list = 154, RULE_cnf_formula = 155, RULE_cnf_disjunction = 156, 
		RULE_cnf_literal = 157, RULE_thf_quantifier = 158, RULE_th1_quantifier = 159, 
		RULE_th0_quantifier = 160, RULE_fof_quantifier = 161, RULE_nonassoc_connective = 162, 
		RULE_assoc_connective = 163, RULE_unary_connective = 164, RULE_type_constant = 165, 
		RULE_type_functor = 166, RULE_defined_type = 167, RULE_system_type = 168, 
		RULE_atom = 169, RULE_untyped_atom = 170, RULE_defined_proposition = 171, 
		RULE_defined_predicate = 172, RULE_defined_infix_pred = 173, RULE_constant = 174, 
		RULE_functor = 175, RULE_defined_constant = 176, RULE_defined_functor = 177, 
		RULE_system_constant = 178, RULE_system_functor = 179, RULE_def_or_sys_constant = 180, 
		RULE_th1_defined_term = 181, RULE_defined_term = 182, RULE_variable = 183, 
		RULE_source = 184, RULE_sources = 185, RULE_dag_source = 186, RULE_inference_record = 187, 
		RULE_inference_rule = 188, RULE_inference_parents = 189, RULE_parent_list = 190, 
		RULE_parent_info = 191, RULE_parent_details = 192, RULE_internal_source = 193, 
		RULE_intro_type = 194, RULE_external_source = 195, RULE_file_source = 196, 
		RULE_file_info = 197, RULE_theory = 198, RULE_theory_name = 199, RULE_creator_source = 200, 
		RULE_creator_name = 201, RULE_optional_info = 202, RULE_useful_info = 203, 
		RULE_info_items = 204, RULE_info_item = 205, RULE_formula_item = 206, 
		RULE_description_item = 207, RULE_iquote_item = 208, RULE_inference_item = 209, 
		RULE_inference_status = 210, RULE_status_value = 211, RULE_inference_info = 212, 
		RULE_assumptions_record = 213, RULE_refutation = 214, RULE_new_symbol_record = 215, 
		RULE_new_symbol_list = 216, RULE_principal_symbol = 217, RULE_include = 218, 
		RULE_formula_selection = 219, RULE_name_list = 220, RULE_general_term = 221, 
		RULE_general_data = 222, RULE_general_function = 223, RULE_formula_data = 224, 
		RULE_general_list = 225, RULE_general_terms = 226, RULE_name = 227, RULE_atomic_word = 228, 
		RULE_atomic_defined_word = 229, RULE_atomic_system_word = 230, RULE_number = 231, 
		RULE_file_name = 232;
	private static String[] makeRuleNames() {
		return new String[] {
			"tptp_file", "tptp_input", "annotated_formula", "tpi_annotated", "tpi_formula", 
			"thf_annotated", "tff_annotated", "tcf_annotated", "fof_annotated", "cnf_annotated", 
			"annotations", "formula_role", "thf_formula", "thf_logic_formula", "thf_binary_formula", 
			"thf_binary_nonassoc", "thf_binary_assoc", "thf_or_formula", "thf_and_formula", 
			"thf_apply_formula", "thf_unit_formula", "thf_preunit_formula", "thf_unitary_formula", 
			"thf_quantified_formula", "thf_quantification", "thf_variable_list", 
			"thf_variable", "thf_typed_variable", "thf_unary_formula", "thf_prefix_unary", 
			"thf_infix_unary", "thf_atomic_formula", "thf_plain_atomic", "thf_defined_atomic", 
			"thf_defined_term", "thf_defined_infix", "thf_system_atomic", "thf_let", 
			"thf_let_types", "thf_atom_typing_list", "thf_let_defns", "thf_let_defn", 
			"thf_let_defn_list", "thf_unitary_term", "thf_conn_term", "thf_tuple", 
			"thf_fof_function", "thf_arguments", "thf_formula_list", "thf_atom_typing", 
			"thf_top_level_type", "thf_unitary_type", "thf_apply_type", "thf_binary_type", 
			"thf_mapping_type", "thf_xprod_type", "thf_union_type", "thf_subtype", 
			"thf_definition", "thf_sequent", "tff_formula", "tff_logic_formula", 
			"tff_binary_formula", "tff_binary_nonassoc", "tff_binary_assoc", "tff_or_formula", 
			"tff_and_formula", "tff_unit_formula", "tff_preunit_formula", "tff_unitary_formula", 
			"txf_unitary_formula", "tff_quantified_formula", "tff_variable_list", 
			"tff_variable", "tff_typed_variable", "tff_unary_formula", "tff_prefix_unary", 
			"tff_infix_unary", "tff_atomic_formula", "tff_plain_atomic", "tff_defined_atomic", 
			"tff_defined_plain", "tff_defined_infix", "tff_system_atomic", "txf_let", 
			"txf_let_types", "tff_atom_typing_list", "txf_let_defns", "txf_let_defn", 
			"txf_let_LHS", "txf_let_defn_list", "txf_ntf_atom", "tff_term", "tff_unitary_term", 
			"txf_tuple", "tff_arguments", "tff_atom_typing", "tff_top_level_type", 
			"tff_non_atomic_type", "tf1_quantified_type", "tff_monotype", "tff_unitary_type", 
			"tff_atomic_type", "tff_type_arguments", "tff_mapping_type", "tff_xprod_type", 
			"txf_tuple_type", "tff_type_list", "tff_subtype", "txf_definition", "txf_sequent", 
			"ntf_connective", "ntf_short_connective", "ntf_long_connective", "ntf_connective_name", 
			"ntf_parameter_list", "ntf_parameter", "ntf_index", "ntf_key_pair", "logic_defn_rule", 
			"logic_defn_LHS", "logic_defn_RHS", "tcf_formula", "tcf_logic_formula", 
			"tcf_quantified_formula", "fof_formula", "fof_logic_formula", "fof_binary_formula", 
			"fof_binary_nonassoc", "fof_binary_assoc", "fof_or_formula", "fof_and_formula", 
			"fof_unary_formula", "fof_infix_unary", "fof_unit_formula", "fof_unitary_formula", 
			"fof_quantified_formula", "fof_variable_list", "fof_atomic_formula", 
			"fof_plain_atomic_formula", "fof_defined_atomic_formula", "fof_defined_plain_formula", 
			"fof_defined_infix_formula", "fof_system_atomic_formula", "fof_plain_term", 
			"fof_defined_term", "fof_defined_atomic_term", "fof_defined_plain_term", 
			"fof_system_term", "fof_arguments", "fof_term", "fof_function_term", 
			"fof_sequent", "fof_formula_tuple", "fof_formula_tuple_list", "cnf_formula", 
			"cnf_disjunction", "cnf_literal", "thf_quantifier", "th1_quantifier", 
			"th0_quantifier", "fof_quantifier", "nonassoc_connective", "assoc_connective", 
			"unary_connective", "type_constant", "type_functor", "defined_type", 
			"system_type", "atom", "untyped_atom", "defined_proposition", "defined_predicate", 
			"defined_infix_pred", "constant", "functor", "defined_constant", "defined_functor", 
			"system_constant", "system_functor", "def_or_sys_constant", "th1_defined_term", 
			"defined_term", "variable", "source", "sources", "dag_source", "inference_record", 
			"inference_rule", "inference_parents", "parent_list", "parent_info", 
			"parent_details", "internal_source", "intro_type", "external_source", 
			"file_source", "file_info", "theory", "theory_name", "creator_source", 
			"creator_name", "optional_info", "useful_info", "info_items", "info_item", 
			"formula_item", "description_item", "iquote_item", "inference_item", 
			"inference_status", "status_value", "inference_info", "assumptions_record", 
			"refutation", "new_symbol_record", "new_symbol_list", "principal_symbol", 
			"include", "formula_selection", "name_list", "general_term", "general_data", 
			"general_function", "formula_data", "general_list", "general_terms", 
			"name", "atomic_word", "atomic_defined_word", "atomic_system_word", "number", 
			"file_name"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'tpi('", "','", "').'", "'thf('", "'tff('", "'tcf('", "'fof('", 
			"'cnf('", "'('", "')'", "'['", "']'", "':'", "'$let('", "'[]'", "'[.]'", 
			"'<.>'", "'{.}'", "'<'", "'{'", "'}'", "')}'", "'{}'", "'inference('", 
			"'introduced('", "'file('", "'theory('", "'creator('", "'description('", 
			"'iquote('", "'status('", "'assumptions('", "'refutation('", "'new_symbols('", 
			"'include('", "'$thf('", "'$tff('", "'$fof('", "'$cnf('", "'$fot('", 
			"'|'", "'&'", "'<=>'", "'=>'", "'<='", "'<~>'", "'~|'", "'~&'", "'~'", 
			"'!!'", "'!>'", "'!='", "'='", "'!'", "'??'", "'?*'", "'?'", "'^'", "'@@+'", 
			"'@+'", "'@@-'", "'@-'", "'@='", "'@'", "':='", "'=='", "'>'", "'*'", 
			"'+'", "'#'", "'<<'", "'-->'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, "Or", "And", "Iff", "Impl", "If", "Niff", 
			"Nor", "Nand", "Not", "ForallComb", "TyForall", "Infix_inequality", "Infix_equality", 
			"Forall", "ExistsComb", "TyExists", "Exists", "Lambda", "ChoiceComb", 
			"Choice", "DescriptionComb", "Description", "EqComb", "App", "Assignment", 
			"Identical", "Arrow", "Star", "Plus", "Hash", "Subtype_sign", "Gentzen_arrow", 
			"Real", "Signed_real", "Unsigned_real", "Rational", "Signed_rational", 
			"Unsigned_rational", "Integer", "Signed_integer", "Unsigned_integer", 
			"Decimal", "Positive_decimal", "Decimal_exponent", "Decimal_fraction", 
			"Dot_decimal", "Exp_integer", "Signed_exp_integer", "Unsigned_exp_integer", 
			"Dollar_word", "Dollar_dollar_word", "Upper_word", "Lower_word", "Single_quoted", 
			"Distinct_object", "WS", "Line_comment", "Block_comment"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "tptp_v7_0_0_0.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public tptp_v7_0_0_0Parser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class Tptp_fileContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(tptp_v7_0_0_0Parser.EOF, 0); }
		public List<Tptp_inputContext> tptp_input() {
			return getRuleContexts(Tptp_inputContext.class);
		}
		public Tptp_inputContext tptp_input(int i) {
			return getRuleContext(Tptp_inputContext.class,i);
		}
		public Tptp_fileContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tptp_file; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTptp_file(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTptp_file(this);
		}
	}

	public final Tptp_fileContext tptp_file() throws RecognitionException {
		Tptp_fileContext _localctx = new Tptp_fileContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_tptp_file);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(469);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__3) | (1L << T__4) | (1L << T__5) | (1L << T__6) | (1L << T__7) | (1L << T__34))) != 0)) {
				{
				{
				setState(466);
				tptp_input();
				}
				}
				setState(471);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(472);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tptp_inputContext extends ParserRuleContext {
		public Annotated_formulaContext annotated_formula() {
			return getRuleContext(Annotated_formulaContext.class,0);
		}
		public IncludeContext include() {
			return getRuleContext(IncludeContext.class,0);
		}
		public Tptp_inputContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tptp_input; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTptp_input(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTptp_input(this);
		}
	}

	public final Tptp_inputContext tptp_input() throws RecognitionException {
		Tptp_inputContext _localctx = new Tptp_inputContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_tptp_input);
		try {
			setState(476);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__0:
			case T__3:
			case T__4:
			case T__5:
			case T__6:
			case T__7:
				enterOuterAlt(_localctx, 1);
				{
				setState(474);
				annotated_formula();
				}
				break;
			case T__34:
				enterOuterAlt(_localctx, 2);
				{
				setState(475);
				include();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Annotated_formulaContext extends ParserRuleContext {
		public Thf_annotatedContext thf_annotated() {
			return getRuleContext(Thf_annotatedContext.class,0);
		}
		public Tff_annotatedContext tff_annotated() {
			return getRuleContext(Tff_annotatedContext.class,0);
		}
		public Tcf_annotatedContext tcf_annotated() {
			return getRuleContext(Tcf_annotatedContext.class,0);
		}
		public Fof_annotatedContext fof_annotated() {
			return getRuleContext(Fof_annotatedContext.class,0);
		}
		public Cnf_annotatedContext cnf_annotated() {
			return getRuleContext(Cnf_annotatedContext.class,0);
		}
		public Tpi_annotatedContext tpi_annotated() {
			return getRuleContext(Tpi_annotatedContext.class,0);
		}
		public Annotated_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotated_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterAnnotated_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitAnnotated_formula(this);
		}
	}

	public final Annotated_formulaContext annotated_formula() throws RecognitionException {
		Annotated_formulaContext _localctx = new Annotated_formulaContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_annotated_formula);
		try {
			setState(484);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__3:
				enterOuterAlt(_localctx, 1);
				{
				setState(478);
				thf_annotated();
				}
				break;
			case T__4:
				enterOuterAlt(_localctx, 2);
				{
				setState(479);
				tff_annotated();
				}
				break;
			case T__5:
				enterOuterAlt(_localctx, 3);
				{
				setState(480);
				tcf_annotated();
				}
				break;
			case T__6:
				enterOuterAlt(_localctx, 4);
				{
				setState(481);
				fof_annotated();
				}
				break;
			case T__7:
				enterOuterAlt(_localctx, 5);
				{
				setState(482);
				cnf_annotated();
				}
				break;
			case T__0:
				enterOuterAlt(_localctx, 6);
				{
				setState(483);
				tpi_annotated();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tpi_annotatedContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public Formula_roleContext formula_role() {
			return getRuleContext(Formula_roleContext.class,0);
		}
		public Tpi_formulaContext tpi_formula() {
			return getRuleContext(Tpi_formulaContext.class,0);
		}
		public AnnotationsContext annotations() {
			return getRuleContext(AnnotationsContext.class,0);
		}
		public Tpi_annotatedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tpi_annotated; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTpi_annotated(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTpi_annotated(this);
		}
	}

	public final Tpi_annotatedContext tpi_annotated() throws RecognitionException {
		Tpi_annotatedContext _localctx = new Tpi_annotatedContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_tpi_annotated);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(486);
			match(T__0);
			setState(487);
			name();
			setState(488);
			match(T__1);
			setState(489);
			formula_role();
			setState(490);
			match(T__1);
			setState(491);
			tpi_formula();
			setState(493);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(492);
				annotations();
				}
			}

			setState(495);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tpi_formulaContext extends ParserRuleContext {
		public Fof_formulaContext fof_formula() {
			return getRuleContext(Fof_formulaContext.class,0);
		}
		public Tpi_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tpi_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTpi_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTpi_formula(this);
		}
	}

	public final Tpi_formulaContext tpi_formula() throws RecognitionException {
		Tpi_formulaContext _localctx = new Tpi_formulaContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_tpi_formula);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(497);
			fof_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_annotatedContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public Formula_roleContext formula_role() {
			return getRuleContext(Formula_roleContext.class,0);
		}
		public Thf_formulaContext thf_formula() {
			return getRuleContext(Thf_formulaContext.class,0);
		}
		public AnnotationsContext annotations() {
			return getRuleContext(AnnotationsContext.class,0);
		}
		public Thf_annotatedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_annotated; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_annotated(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_annotated(this);
		}
	}

	public final Thf_annotatedContext thf_annotated() throws RecognitionException {
		Thf_annotatedContext _localctx = new Thf_annotatedContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_thf_annotated);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(499);
			match(T__3);
			setState(500);
			name();
			setState(501);
			match(T__1);
			setState(502);
			formula_role();
			setState(503);
			match(T__1);
			setState(504);
			thf_formula();
			setState(506);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(505);
				annotations();
				}
			}

			setState(508);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_annotatedContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public Formula_roleContext formula_role() {
			return getRuleContext(Formula_roleContext.class,0);
		}
		public Tff_formulaContext tff_formula() {
			return getRuleContext(Tff_formulaContext.class,0);
		}
		public AnnotationsContext annotations() {
			return getRuleContext(AnnotationsContext.class,0);
		}
		public Tff_annotatedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_annotated; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_annotated(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_annotated(this);
		}
	}

	public final Tff_annotatedContext tff_annotated() throws RecognitionException {
		Tff_annotatedContext _localctx = new Tff_annotatedContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_tff_annotated);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(510);
			match(T__4);
			setState(511);
			name();
			setState(512);
			match(T__1);
			setState(513);
			formula_role();
			setState(514);
			match(T__1);
			setState(515);
			tff_formula();
			setState(517);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(516);
				annotations();
				}
			}

			setState(519);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tcf_annotatedContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public Formula_roleContext formula_role() {
			return getRuleContext(Formula_roleContext.class,0);
		}
		public Tcf_formulaContext tcf_formula() {
			return getRuleContext(Tcf_formulaContext.class,0);
		}
		public AnnotationsContext annotations() {
			return getRuleContext(AnnotationsContext.class,0);
		}
		public Tcf_annotatedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tcf_annotated; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTcf_annotated(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTcf_annotated(this);
		}
	}

	public final Tcf_annotatedContext tcf_annotated() throws RecognitionException {
		Tcf_annotatedContext _localctx = new Tcf_annotatedContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_tcf_annotated);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(521);
			match(T__5);
			setState(522);
			name();
			setState(523);
			match(T__1);
			setState(524);
			formula_role();
			setState(525);
			match(T__1);
			setState(526);
			tcf_formula();
			setState(528);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(527);
				annotations();
				}
			}

			setState(530);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_annotatedContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public Formula_roleContext formula_role() {
			return getRuleContext(Formula_roleContext.class,0);
		}
		public Fof_formulaContext fof_formula() {
			return getRuleContext(Fof_formulaContext.class,0);
		}
		public AnnotationsContext annotations() {
			return getRuleContext(AnnotationsContext.class,0);
		}
		public Fof_annotatedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_annotated; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_annotated(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_annotated(this);
		}
	}

	public final Fof_annotatedContext fof_annotated() throws RecognitionException {
		Fof_annotatedContext _localctx = new Fof_annotatedContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_fof_annotated);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(532);
			match(T__6);
			setState(533);
			name();
			setState(534);
			match(T__1);
			setState(535);
			formula_role();
			setState(536);
			match(T__1);
			setState(537);
			fof_formula();
			setState(539);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(538);
				annotations();
				}
			}

			setState(541);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Cnf_annotatedContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public Formula_roleContext formula_role() {
			return getRuleContext(Formula_roleContext.class,0);
		}
		public Cnf_formulaContext cnf_formula() {
			return getRuleContext(Cnf_formulaContext.class,0);
		}
		public AnnotationsContext annotations() {
			return getRuleContext(AnnotationsContext.class,0);
		}
		public Cnf_annotatedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cnf_annotated; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterCnf_annotated(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitCnf_annotated(this);
		}
	}

	public final Cnf_annotatedContext cnf_annotated() throws RecognitionException {
		Cnf_annotatedContext _localctx = new Cnf_annotatedContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_cnf_annotated);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(543);
			match(T__7);
			setState(544);
			name();
			setState(545);
			match(T__1);
			setState(546);
			formula_role();
			setState(547);
			match(T__1);
			setState(548);
			cnf_formula();
			setState(550);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(549);
				annotations();
				}
			}

			setState(552);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AnnotationsContext extends ParserRuleContext {
		public SourceContext source() {
			return getRuleContext(SourceContext.class,0);
		}
		public Optional_infoContext optional_info() {
			return getRuleContext(Optional_infoContext.class,0);
		}
		public AnnotationsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotations; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterAnnotations(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitAnnotations(this);
		}
	}

	public final AnnotationsContext annotations() throws RecognitionException {
		AnnotationsContext _localctx = new AnnotationsContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_annotations);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(554);
			match(T__1);
			setState(555);
			source();
			setState(557);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(556);
				optional_info();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Formula_roleContext extends ParserRuleContext {
		public TerminalNode Lower_word() { return getToken(tptp_v7_0_0_0Parser.Lower_word, 0); }
		public Formula_roleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_formula_role; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFormula_role(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFormula_role(this);
		}
	}

	public final Formula_roleContext formula_role() throws RecognitionException {
		Formula_roleContext _localctx = new Formula_roleContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_formula_role);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(559);
			match(Lower_word);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_formulaContext extends ParserRuleContext {
		public Thf_logic_formulaContext thf_logic_formula() {
			return getRuleContext(Thf_logic_formulaContext.class,0);
		}
		public Thf_atom_typingContext thf_atom_typing() {
			return getRuleContext(Thf_atom_typingContext.class,0);
		}
		public Thf_subtypeContext thf_subtype() {
			return getRuleContext(Thf_subtypeContext.class,0);
		}
		public Thf_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_formula(this);
		}
	}

	public final Thf_formulaContext thf_formula() throws RecognitionException {
		Thf_formulaContext _localctx = new Thf_formulaContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_thf_formula);
		try {
			setState(564);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(561);
				thf_logic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(562);
				thf_atom_typing();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(563);
				thf_subtype();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_logic_formulaContext extends ParserRuleContext {
		public Thf_unitary_formulaContext thf_unitary_formula() {
			return getRuleContext(Thf_unitary_formulaContext.class,0);
		}
		public Thf_unary_formulaContext thf_unary_formula() {
			return getRuleContext(Thf_unary_formulaContext.class,0);
		}
		public Thf_binary_formulaContext thf_binary_formula() {
			return getRuleContext(Thf_binary_formulaContext.class,0);
		}
		public Thf_defined_infixContext thf_defined_infix() {
			return getRuleContext(Thf_defined_infixContext.class,0);
		}
		public Thf_definitionContext thf_definition() {
			return getRuleContext(Thf_definitionContext.class,0);
		}
		public Thf_sequentContext thf_sequent() {
			return getRuleContext(Thf_sequentContext.class,0);
		}
		public Thf_logic_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_logic_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_logic_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_logic_formula(this);
		}
	}

	public final Thf_logic_formulaContext thf_logic_formula() throws RecognitionException {
		Thf_logic_formulaContext _localctx = new Thf_logic_formulaContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_thf_logic_formula);
		try {
			setState(572);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(566);
				thf_unitary_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(567);
				thf_unary_formula();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(568);
				thf_binary_formula();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(569);
				thf_defined_infix();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(570);
				thf_definition();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(571);
				thf_sequent();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_binary_formulaContext extends ParserRuleContext {
		public Thf_binary_nonassocContext thf_binary_nonassoc() {
			return getRuleContext(Thf_binary_nonassocContext.class,0);
		}
		public Thf_binary_assocContext thf_binary_assoc() {
			return getRuleContext(Thf_binary_assocContext.class,0);
		}
		public Thf_binary_typeContext thf_binary_type() {
			return getRuleContext(Thf_binary_typeContext.class,0);
		}
		public Thf_binary_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_binary_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_binary_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_binary_formula(this);
		}
	}

	public final Thf_binary_formulaContext thf_binary_formula() throws RecognitionException {
		Thf_binary_formulaContext _localctx = new Thf_binary_formulaContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_thf_binary_formula);
		try {
			setState(577);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(574);
				thf_binary_nonassoc();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(575);
				thf_binary_assoc();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(576);
				thf_binary_type();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_binary_nonassocContext extends ParserRuleContext {
		public List<Thf_unit_formulaContext> thf_unit_formula() {
			return getRuleContexts(Thf_unit_formulaContext.class);
		}
		public Thf_unit_formulaContext thf_unit_formula(int i) {
			return getRuleContext(Thf_unit_formulaContext.class,i);
		}
		public Nonassoc_connectiveContext nonassoc_connective() {
			return getRuleContext(Nonassoc_connectiveContext.class,0);
		}
		public Thf_binary_nonassocContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_binary_nonassoc; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_binary_nonassoc(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_binary_nonassoc(this);
		}
	}

	public final Thf_binary_nonassocContext thf_binary_nonassoc() throws RecognitionException {
		Thf_binary_nonassocContext _localctx = new Thf_binary_nonassocContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_thf_binary_nonassoc);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(579);
			thf_unit_formula();
			setState(580);
			nonassoc_connective();
			setState(581);
			thf_unit_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_binary_assocContext extends ParserRuleContext {
		public Thf_or_formulaContext thf_or_formula() {
			return getRuleContext(Thf_or_formulaContext.class,0);
		}
		public Thf_and_formulaContext thf_and_formula() {
			return getRuleContext(Thf_and_formulaContext.class,0);
		}
		public Thf_apply_formulaContext thf_apply_formula() {
			return getRuleContext(Thf_apply_formulaContext.class,0);
		}
		public Thf_binary_assocContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_binary_assoc; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_binary_assoc(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_binary_assoc(this);
		}
	}

	public final Thf_binary_assocContext thf_binary_assoc() throws RecognitionException {
		Thf_binary_assocContext _localctx = new Thf_binary_assocContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_thf_binary_assoc);
		try {
			setState(586);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(583);
				thf_or_formula(0);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(584);
				thf_and_formula(0);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(585);
				thf_apply_formula(0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_or_formulaContext extends ParserRuleContext {
		public List<Thf_unit_formulaContext> thf_unit_formula() {
			return getRuleContexts(Thf_unit_formulaContext.class);
		}
		public Thf_unit_formulaContext thf_unit_formula(int i) {
			return getRuleContext(Thf_unit_formulaContext.class,i);
		}
		public TerminalNode Or() { return getToken(tptp_v7_0_0_0Parser.Or, 0); }
		public Thf_or_formulaContext thf_or_formula() {
			return getRuleContext(Thf_or_formulaContext.class,0);
		}
		public Thf_or_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_or_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_or_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_or_formula(this);
		}
	}

	public final Thf_or_formulaContext thf_or_formula() throws RecognitionException {
		return thf_or_formula(0);
	}

	private Thf_or_formulaContext thf_or_formula(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Thf_or_formulaContext _localctx = new Thf_or_formulaContext(_ctx, _parentState);
		Thf_or_formulaContext _prevctx = _localctx;
		int _startState = 34;
		enterRecursionRule(_localctx, 34, RULE_thf_or_formula, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(589);
			thf_unit_formula();
			setState(590);
			match(Or);
			setState(591);
			thf_unit_formula();
			}
			_ctx.stop = _input.LT(-1);
			setState(598);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,14,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Thf_or_formulaContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_thf_or_formula);
					setState(593);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(594);
					match(Or);
					setState(595);
					thf_unit_formula();
					}
					} 
				}
				setState(600);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,14,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Thf_and_formulaContext extends ParserRuleContext {
		public List<Thf_unit_formulaContext> thf_unit_formula() {
			return getRuleContexts(Thf_unit_formulaContext.class);
		}
		public Thf_unit_formulaContext thf_unit_formula(int i) {
			return getRuleContext(Thf_unit_formulaContext.class,i);
		}
		public TerminalNode And() { return getToken(tptp_v7_0_0_0Parser.And, 0); }
		public Thf_and_formulaContext thf_and_formula() {
			return getRuleContext(Thf_and_formulaContext.class,0);
		}
		public Thf_and_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_and_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_and_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_and_formula(this);
		}
	}

	public final Thf_and_formulaContext thf_and_formula() throws RecognitionException {
		return thf_and_formula(0);
	}

	private Thf_and_formulaContext thf_and_formula(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Thf_and_formulaContext _localctx = new Thf_and_formulaContext(_ctx, _parentState);
		Thf_and_formulaContext _prevctx = _localctx;
		int _startState = 36;
		enterRecursionRule(_localctx, 36, RULE_thf_and_formula, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(602);
			thf_unit_formula();
			setState(603);
			match(And);
			setState(604);
			thf_unit_formula();
			}
			_ctx.stop = _input.LT(-1);
			setState(611);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,15,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Thf_and_formulaContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_thf_and_formula);
					setState(606);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(607);
					match(And);
					setState(608);
					thf_unit_formula();
					}
					} 
				}
				setState(613);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,15,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Thf_apply_formulaContext extends ParserRuleContext {
		public List<Thf_unit_formulaContext> thf_unit_formula() {
			return getRuleContexts(Thf_unit_formulaContext.class);
		}
		public Thf_unit_formulaContext thf_unit_formula(int i) {
			return getRuleContext(Thf_unit_formulaContext.class,i);
		}
		public TerminalNode App() { return getToken(tptp_v7_0_0_0Parser.App, 0); }
		public Thf_apply_formulaContext thf_apply_formula() {
			return getRuleContext(Thf_apply_formulaContext.class,0);
		}
		public Thf_apply_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_apply_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_apply_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_apply_formula(this);
		}
	}

	public final Thf_apply_formulaContext thf_apply_formula() throws RecognitionException {
		return thf_apply_formula(0);
	}

	private Thf_apply_formulaContext thf_apply_formula(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Thf_apply_formulaContext _localctx = new Thf_apply_formulaContext(_ctx, _parentState);
		Thf_apply_formulaContext _prevctx = _localctx;
		int _startState = 38;
		enterRecursionRule(_localctx, 38, RULE_thf_apply_formula, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(615);
			thf_unit_formula();
			setState(616);
			match(App);
			setState(617);
			thf_unit_formula();
			}
			_ctx.stop = _input.LT(-1);
			setState(624);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,16,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Thf_apply_formulaContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_thf_apply_formula);
					setState(619);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(620);
					match(App);
					setState(621);
					thf_unit_formula();
					}
					} 
				}
				setState(626);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,16,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Thf_unit_formulaContext extends ParserRuleContext {
		public Thf_unitary_formulaContext thf_unitary_formula() {
			return getRuleContext(Thf_unitary_formulaContext.class,0);
		}
		public Thf_unary_formulaContext thf_unary_formula() {
			return getRuleContext(Thf_unary_formulaContext.class,0);
		}
		public Thf_unit_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_unit_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_unit_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_unit_formula(this);
		}
	}

	public final Thf_unit_formulaContext thf_unit_formula() throws RecognitionException {
		Thf_unit_formulaContext _localctx = new Thf_unit_formulaContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_thf_unit_formula);
		try {
			setState(629);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,17,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(627);
				thf_unitary_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(628);
				thf_unary_formula();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_preunit_formulaContext extends ParserRuleContext {
		public Thf_unitary_formulaContext thf_unitary_formula() {
			return getRuleContext(Thf_unitary_formulaContext.class,0);
		}
		public Thf_prefix_unaryContext thf_prefix_unary() {
			return getRuleContext(Thf_prefix_unaryContext.class,0);
		}
		public Thf_preunit_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_preunit_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_preunit_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_preunit_formula(this);
		}
	}

	public final Thf_preunit_formulaContext thf_preunit_formula() throws RecognitionException {
		Thf_preunit_formulaContext _localctx = new Thf_preunit_formulaContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_thf_preunit_formula);
		try {
			setState(633);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__8:
			case T__10:
			case T__13:
			case T__14:
			case T__15:
			case T__16:
			case T__17:
			case T__18:
			case T__19:
			case ForallComb:
			case TyForall:
			case Forall:
			case ExistsComb:
			case TyExists:
			case Exists:
			case Lambda:
			case ChoiceComb:
			case Choice:
			case DescriptionComb:
			case Description:
			case EqComb:
			case Real:
			case Rational:
			case Integer:
			case Dollar_word:
			case Dollar_dollar_word:
			case Upper_word:
			case Lower_word:
			case Single_quoted:
			case Distinct_object:
				enterOuterAlt(_localctx, 1);
				{
				setState(631);
				thf_unitary_formula();
				}
				break;
			case Not:
				enterOuterAlt(_localctx, 2);
				{
				setState(632);
				thf_prefix_unary();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_unitary_formulaContext extends ParserRuleContext {
		public Thf_quantified_formulaContext thf_quantified_formula() {
			return getRuleContext(Thf_quantified_formulaContext.class,0);
		}
		public Thf_atomic_formulaContext thf_atomic_formula() {
			return getRuleContext(Thf_atomic_formulaContext.class,0);
		}
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Thf_logic_formulaContext thf_logic_formula() {
			return getRuleContext(Thf_logic_formulaContext.class,0);
		}
		public Thf_unitary_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_unitary_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_unitary_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_unitary_formula(this);
		}
	}

	public final Thf_unitary_formulaContext thf_unitary_formula() throws RecognitionException {
		Thf_unitary_formulaContext _localctx = new Thf_unitary_formulaContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_thf_unitary_formula);
		try {
			setState(642);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,19,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(635);
				thf_quantified_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(636);
				thf_atomic_formula();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(637);
				variable();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(638);
				match(T__8);
				setState(639);
				thf_logic_formula();
				setState(640);
				match(T__9);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_quantified_formulaContext extends ParserRuleContext {
		public Thf_quantificationContext thf_quantification() {
			return getRuleContext(Thf_quantificationContext.class,0);
		}
		public Thf_unitary_formulaContext thf_unitary_formula() {
			return getRuleContext(Thf_unitary_formulaContext.class,0);
		}
		public Thf_quantified_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_quantified_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_quantified_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_quantified_formula(this);
		}
	}

	public final Thf_quantified_formulaContext thf_quantified_formula() throws RecognitionException {
		Thf_quantified_formulaContext _localctx = new Thf_quantified_formulaContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_thf_quantified_formula);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(644);
			thf_quantification();
			setState(645);
			thf_unitary_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_quantificationContext extends ParserRuleContext {
		public Thf_quantifierContext thf_quantifier() {
			return getRuleContext(Thf_quantifierContext.class,0);
		}
		public Thf_variable_listContext thf_variable_list() {
			return getRuleContext(Thf_variable_listContext.class,0);
		}
		public Thf_quantificationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_quantification; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_quantification(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_quantification(this);
		}
	}

	public final Thf_quantificationContext thf_quantification() throws RecognitionException {
		Thf_quantificationContext _localctx = new Thf_quantificationContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_thf_quantification);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(647);
			thf_quantifier();
			setState(648);
			match(T__10);
			setState(649);
			thf_variable_list();
			setState(650);
			match(T__11);
			setState(651);
			match(T__12);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_variable_listContext extends ParserRuleContext {
		public List<Thf_variableContext> thf_variable() {
			return getRuleContexts(Thf_variableContext.class);
		}
		public Thf_variableContext thf_variable(int i) {
			return getRuleContext(Thf_variableContext.class,i);
		}
		public Thf_variable_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_variable_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_variable_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_variable_list(this);
		}
	}

	public final Thf_variable_listContext thf_variable_list() throws RecognitionException {
		Thf_variable_listContext _localctx = new Thf_variable_listContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_thf_variable_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(653);
			thf_variable();
			setState(658);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(654);
				match(T__1);
				setState(655);
				thf_variable();
				}
				}
				setState(660);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_variableContext extends ParserRuleContext {
		public Thf_typed_variableContext thf_typed_variable() {
			return getRuleContext(Thf_typed_variableContext.class,0);
		}
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Thf_variableContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_variable; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_variable(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_variable(this);
		}
	}

	public final Thf_variableContext thf_variable() throws RecognitionException {
		Thf_variableContext _localctx = new Thf_variableContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_thf_variable);
		try {
			setState(663);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,21,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(661);
				thf_typed_variable();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(662);
				variable();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_typed_variableContext extends ParserRuleContext {
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Thf_top_level_typeContext thf_top_level_type() {
			return getRuleContext(Thf_top_level_typeContext.class,0);
		}
		public Thf_typed_variableContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_typed_variable; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_typed_variable(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_typed_variable(this);
		}
	}

	public final Thf_typed_variableContext thf_typed_variable() throws RecognitionException {
		Thf_typed_variableContext _localctx = new Thf_typed_variableContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_thf_typed_variable);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(665);
			variable();
			setState(666);
			match(T__12);
			setState(667);
			thf_top_level_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_unary_formulaContext extends ParserRuleContext {
		public Thf_prefix_unaryContext thf_prefix_unary() {
			return getRuleContext(Thf_prefix_unaryContext.class,0);
		}
		public Thf_infix_unaryContext thf_infix_unary() {
			return getRuleContext(Thf_infix_unaryContext.class,0);
		}
		public Thf_unary_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_unary_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_unary_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_unary_formula(this);
		}
	}

	public final Thf_unary_formulaContext thf_unary_formula() throws RecognitionException {
		Thf_unary_formulaContext _localctx = new Thf_unary_formulaContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_thf_unary_formula);
		try {
			setState(671);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Not:
				enterOuterAlt(_localctx, 1);
				{
				setState(669);
				thf_prefix_unary();
				}
				break;
			case T__8:
			case T__10:
			case T__13:
			case T__14:
			case T__15:
			case T__16:
			case T__17:
			case T__18:
			case T__19:
			case ForallComb:
			case ExistsComb:
			case ChoiceComb:
			case DescriptionComb:
			case EqComb:
			case Real:
			case Rational:
			case Integer:
			case Dollar_word:
			case Dollar_dollar_word:
			case Upper_word:
			case Lower_word:
			case Single_quoted:
			case Distinct_object:
				enterOuterAlt(_localctx, 2);
				{
				setState(670);
				thf_infix_unary();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_prefix_unaryContext extends ParserRuleContext {
		public Unary_connectiveContext unary_connective() {
			return getRuleContext(Unary_connectiveContext.class,0);
		}
		public Thf_preunit_formulaContext thf_preunit_formula() {
			return getRuleContext(Thf_preunit_formulaContext.class,0);
		}
		public Thf_prefix_unaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_prefix_unary; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_prefix_unary(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_prefix_unary(this);
		}
	}

	public final Thf_prefix_unaryContext thf_prefix_unary() throws RecognitionException {
		Thf_prefix_unaryContext _localctx = new Thf_prefix_unaryContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_thf_prefix_unary);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(673);
			unary_connective();
			setState(674);
			thf_preunit_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_infix_unaryContext extends ParserRuleContext {
		public List<Thf_unitary_termContext> thf_unitary_term() {
			return getRuleContexts(Thf_unitary_termContext.class);
		}
		public Thf_unitary_termContext thf_unitary_term(int i) {
			return getRuleContext(Thf_unitary_termContext.class,i);
		}
		public TerminalNode Infix_inequality() { return getToken(tptp_v7_0_0_0Parser.Infix_inequality, 0); }
		public Thf_infix_unaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_infix_unary; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_infix_unary(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_infix_unary(this);
		}
	}

	public final Thf_infix_unaryContext thf_infix_unary() throws RecognitionException {
		Thf_infix_unaryContext _localctx = new Thf_infix_unaryContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_thf_infix_unary);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(676);
			thf_unitary_term();
			setState(677);
			match(Infix_inequality);
			setState(678);
			thf_unitary_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_atomic_formulaContext extends ParserRuleContext {
		public Thf_plain_atomicContext thf_plain_atomic() {
			return getRuleContext(Thf_plain_atomicContext.class,0);
		}
		public Thf_defined_atomicContext thf_defined_atomic() {
			return getRuleContext(Thf_defined_atomicContext.class,0);
		}
		public Thf_system_atomicContext thf_system_atomic() {
			return getRuleContext(Thf_system_atomicContext.class,0);
		}
		public Thf_fof_functionContext thf_fof_function() {
			return getRuleContext(Thf_fof_functionContext.class,0);
		}
		public Thf_atomic_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_atomic_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_atomic_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_atomic_formula(this);
		}
	}

	public final Thf_atomic_formulaContext thf_atomic_formula() throws RecognitionException {
		Thf_atomic_formulaContext _localctx = new Thf_atomic_formulaContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_thf_atomic_formula);
		try {
			setState(684);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,23,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(680);
				thf_plain_atomic();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(681);
				thf_defined_atomic();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(682);
				thf_system_atomic();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(683);
				thf_fof_function();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_plain_atomicContext extends ParserRuleContext {
		public ConstantContext constant() {
			return getRuleContext(ConstantContext.class,0);
		}
		public Thf_tupleContext thf_tuple() {
			return getRuleContext(Thf_tupleContext.class,0);
		}
		public Thf_plain_atomicContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_plain_atomic; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_plain_atomic(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_plain_atomic(this);
		}
	}

	public final Thf_plain_atomicContext thf_plain_atomic() throws RecognitionException {
		Thf_plain_atomicContext _localctx = new Thf_plain_atomicContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_thf_plain_atomic);
		try {
			setState(688);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(686);
				constant();
				}
				break;
			case T__10:
			case T__14:
				enterOuterAlt(_localctx, 2);
				{
				setState(687);
				thf_tuple();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_defined_atomicContext extends ParserRuleContext {
		public Defined_constantContext defined_constant() {
			return getRuleContext(Defined_constantContext.class,0);
		}
		public Thf_defined_termContext thf_defined_term() {
			return getRuleContext(Thf_defined_termContext.class,0);
		}
		public Thf_conn_termContext thf_conn_term() {
			return getRuleContext(Thf_conn_termContext.class,0);
		}
		public Ntf_connectiveContext ntf_connective() {
			return getRuleContext(Ntf_connectiveContext.class,0);
		}
		public Thf_letContext thf_let() {
			return getRuleContext(Thf_letContext.class,0);
		}
		public Thf_defined_atomicContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_defined_atomic; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_defined_atomic(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_defined_atomic(this);
		}
	}

	public final Thf_defined_atomicContext thf_defined_atomic() throws RecognitionException {
		Thf_defined_atomicContext _localctx = new Thf_defined_atomicContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_thf_defined_atomic);
		try {
			setState(698);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Dollar_word:
				enterOuterAlt(_localctx, 1);
				{
				setState(690);
				defined_constant();
				}
				break;
			case ForallComb:
			case ExistsComb:
			case ChoiceComb:
			case DescriptionComb:
			case EqComb:
			case Real:
			case Rational:
			case Integer:
			case Distinct_object:
				enterOuterAlt(_localctx, 2);
				{
				setState(691);
				thf_defined_term();
				}
				break;
			case T__8:
				enterOuterAlt(_localctx, 3);
				{
				setState(692);
				match(T__8);
				setState(693);
				thf_conn_term();
				setState(694);
				match(T__9);
				}
				break;
			case T__10:
			case T__15:
			case T__16:
			case T__17:
			case T__18:
			case T__19:
				enterOuterAlt(_localctx, 4);
				{
				setState(696);
				ntf_connective();
				}
				break;
			case T__13:
				enterOuterAlt(_localctx, 5);
				{
				setState(697);
				thf_let();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_defined_termContext extends ParserRuleContext {
		public Defined_termContext defined_term() {
			return getRuleContext(Defined_termContext.class,0);
		}
		public Th1_defined_termContext th1_defined_term() {
			return getRuleContext(Th1_defined_termContext.class,0);
		}
		public Thf_defined_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_defined_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_defined_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_defined_term(this);
		}
	}

	public final Thf_defined_termContext thf_defined_term() throws RecognitionException {
		Thf_defined_termContext _localctx = new Thf_defined_termContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_thf_defined_term);
		try {
			setState(702);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Real:
			case Rational:
			case Integer:
			case Distinct_object:
				enterOuterAlt(_localctx, 1);
				{
				setState(700);
				defined_term();
				}
				break;
			case ForallComb:
			case ExistsComb:
			case ChoiceComb:
			case DescriptionComb:
			case EqComb:
				enterOuterAlt(_localctx, 2);
				{
				setState(701);
				th1_defined_term();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_defined_infixContext extends ParserRuleContext {
		public List<Thf_unitary_termContext> thf_unitary_term() {
			return getRuleContexts(Thf_unitary_termContext.class);
		}
		public Thf_unitary_termContext thf_unitary_term(int i) {
			return getRuleContext(Thf_unitary_termContext.class,i);
		}
		public Defined_infix_predContext defined_infix_pred() {
			return getRuleContext(Defined_infix_predContext.class,0);
		}
		public Thf_defined_infixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_defined_infix; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_defined_infix(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_defined_infix(this);
		}
	}

	public final Thf_defined_infixContext thf_defined_infix() throws RecognitionException {
		Thf_defined_infixContext _localctx = new Thf_defined_infixContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_thf_defined_infix);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(704);
			thf_unitary_term();
			setState(705);
			defined_infix_pred();
			setState(706);
			thf_unitary_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_system_atomicContext extends ParserRuleContext {
		public System_constantContext system_constant() {
			return getRuleContext(System_constantContext.class,0);
		}
		public Thf_system_atomicContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_system_atomic; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_system_atomic(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_system_atomic(this);
		}
	}

	public final Thf_system_atomicContext thf_system_atomic() throws RecognitionException {
		Thf_system_atomicContext _localctx = new Thf_system_atomicContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_thf_system_atomic);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(708);
			system_constant();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_letContext extends ParserRuleContext {
		public Thf_let_typesContext thf_let_types() {
			return getRuleContext(Thf_let_typesContext.class,0);
		}
		public Thf_let_defnsContext thf_let_defns() {
			return getRuleContext(Thf_let_defnsContext.class,0);
		}
		public Thf_logic_formulaContext thf_logic_formula() {
			return getRuleContext(Thf_logic_formulaContext.class,0);
		}
		public Thf_letContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_let; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_let(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_let(this);
		}
	}

	public final Thf_letContext thf_let() throws RecognitionException {
		Thf_letContext _localctx = new Thf_letContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_thf_let);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(710);
			match(T__13);
			setState(711);
			thf_let_types();
			setState(712);
			match(T__1);
			setState(713);
			thf_let_defns();
			setState(714);
			match(T__1);
			setState(715);
			thf_logic_formula();
			setState(716);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_let_typesContext extends ParserRuleContext {
		public Thf_atom_typingContext thf_atom_typing() {
			return getRuleContext(Thf_atom_typingContext.class,0);
		}
		public Thf_atom_typing_listContext thf_atom_typing_list() {
			return getRuleContext(Thf_atom_typing_listContext.class,0);
		}
		public Thf_let_typesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_let_types; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_let_types(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_let_types(this);
		}
	}

	public final Thf_let_typesContext thf_let_types() throws RecognitionException {
		Thf_let_typesContext _localctx = new Thf_let_typesContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_thf_let_types);
		try {
			setState(723);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__8:
			case Dollar_dollar_word:
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(718);
				thf_atom_typing();
				}
				break;
			case T__10:
				enterOuterAlt(_localctx, 2);
				{
				setState(719);
				match(T__10);
				setState(720);
				thf_atom_typing_list();
				setState(721);
				match(T__11);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_atom_typing_listContext extends ParserRuleContext {
		public Thf_atom_typingContext thf_atom_typing() {
			return getRuleContext(Thf_atom_typingContext.class,0);
		}
		public Thf_atom_typing_listContext thf_atom_typing_list() {
			return getRuleContext(Thf_atom_typing_listContext.class,0);
		}
		public Thf_atom_typing_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_atom_typing_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_atom_typing_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_atom_typing_list(this);
		}
	}

	public final Thf_atom_typing_listContext thf_atom_typing_list() throws RecognitionException {
		Thf_atom_typing_listContext _localctx = new Thf_atom_typing_listContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_thf_atom_typing_list);
		try {
			setState(730);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,28,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(725);
				thf_atom_typing();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(726);
				thf_atom_typing();
				setState(727);
				match(T__1);
				setState(728);
				thf_atom_typing_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_let_defnsContext extends ParserRuleContext {
		public Thf_let_defnContext thf_let_defn() {
			return getRuleContext(Thf_let_defnContext.class,0);
		}
		public Thf_let_defn_listContext thf_let_defn_list() {
			return getRuleContext(Thf_let_defn_listContext.class,0);
		}
		public Thf_let_defnsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_let_defns; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_let_defns(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_let_defns(this);
		}
	}

	public final Thf_let_defnsContext thf_let_defns() throws RecognitionException {
		Thf_let_defnsContext _localctx = new Thf_let_defnsContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_thf_let_defns);
		try {
			setState(737);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,29,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(732);
				thf_let_defn();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(733);
				match(T__10);
				setState(734);
				thf_let_defn_list();
				setState(735);
				match(T__11);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_let_defnContext extends ParserRuleContext {
		public List<Thf_logic_formulaContext> thf_logic_formula() {
			return getRuleContexts(Thf_logic_formulaContext.class);
		}
		public Thf_logic_formulaContext thf_logic_formula(int i) {
			return getRuleContext(Thf_logic_formulaContext.class,i);
		}
		public TerminalNode Assignment() { return getToken(tptp_v7_0_0_0Parser.Assignment, 0); }
		public Thf_let_defnContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_let_defn; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_let_defn(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_let_defn(this);
		}
	}

	public final Thf_let_defnContext thf_let_defn() throws RecognitionException {
		Thf_let_defnContext _localctx = new Thf_let_defnContext(_ctx, getState());
		enterRule(_localctx, 82, RULE_thf_let_defn);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(739);
			thf_logic_formula();
			setState(740);
			match(Assignment);
			setState(741);
			thf_logic_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_let_defn_listContext extends ParserRuleContext {
		public Thf_let_defnContext thf_let_defn() {
			return getRuleContext(Thf_let_defnContext.class,0);
		}
		public Thf_let_defn_listContext thf_let_defn_list() {
			return getRuleContext(Thf_let_defn_listContext.class,0);
		}
		public Thf_let_defn_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_let_defn_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_let_defn_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_let_defn_list(this);
		}
	}

	public final Thf_let_defn_listContext thf_let_defn_list() throws RecognitionException {
		Thf_let_defn_listContext _localctx = new Thf_let_defn_listContext(_ctx, getState());
		enterRule(_localctx, 84, RULE_thf_let_defn_list);
		try {
			setState(748);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,30,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(743);
				thf_let_defn();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(744);
				thf_let_defn();
				setState(745);
				match(T__1);
				setState(746);
				thf_let_defn_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_unitary_termContext extends ParserRuleContext {
		public Thf_atomic_formulaContext thf_atomic_formula() {
			return getRuleContext(Thf_atomic_formulaContext.class,0);
		}
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Thf_logic_formulaContext thf_logic_formula() {
			return getRuleContext(Thf_logic_formulaContext.class,0);
		}
		public Thf_unitary_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_unitary_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_unitary_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_unitary_term(this);
		}
	}

	public final Thf_unitary_termContext thf_unitary_term() throws RecognitionException {
		Thf_unitary_termContext _localctx = new Thf_unitary_termContext(_ctx, getState());
		enterRule(_localctx, 86, RULE_thf_unitary_term);
		try {
			setState(756);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,31,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(750);
				thf_atomic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(751);
				variable();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(752);
				match(T__8);
				setState(753);
				thf_logic_formula();
				setState(754);
				match(T__9);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_conn_termContext extends ParserRuleContext {
		public Nonassoc_connectiveContext nonassoc_connective() {
			return getRuleContext(Nonassoc_connectiveContext.class,0);
		}
		public Assoc_connectiveContext assoc_connective() {
			return getRuleContext(Assoc_connectiveContext.class,0);
		}
		public TerminalNode Infix_equality() { return getToken(tptp_v7_0_0_0Parser.Infix_equality, 0); }
		public TerminalNode Infix_inequality() { return getToken(tptp_v7_0_0_0Parser.Infix_inequality, 0); }
		public Unary_connectiveContext unary_connective() {
			return getRuleContext(Unary_connectiveContext.class,0);
		}
		public Thf_conn_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_conn_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_conn_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_conn_term(this);
		}
	}

	public final Thf_conn_termContext thf_conn_term() throws RecognitionException {
		Thf_conn_termContext _localctx = new Thf_conn_termContext(_ctx, getState());
		enterRule(_localctx, 88, RULE_thf_conn_term);
		try {
			setState(763);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Iff:
			case Impl:
			case If:
			case Niff:
			case Nor:
			case Nand:
				enterOuterAlt(_localctx, 1);
				{
				setState(758);
				nonassoc_connective();
				}
				break;
			case Or:
			case And:
				enterOuterAlt(_localctx, 2);
				{
				setState(759);
				assoc_connective();
				}
				break;
			case Infix_equality:
				enterOuterAlt(_localctx, 3);
				{
				setState(760);
				match(Infix_equality);
				}
				break;
			case Infix_inequality:
				enterOuterAlt(_localctx, 4);
				{
				setState(761);
				match(Infix_inequality);
				}
				break;
			case Not:
				enterOuterAlt(_localctx, 5);
				{
				setState(762);
				unary_connective();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_tupleContext extends ParserRuleContext {
		public Thf_formula_listContext thf_formula_list() {
			return getRuleContext(Thf_formula_listContext.class,0);
		}
		public Thf_tupleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_tuple; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_tuple(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_tuple(this);
		}
	}

	public final Thf_tupleContext thf_tuple() throws RecognitionException {
		Thf_tupleContext _localctx = new Thf_tupleContext(_ctx, getState());
		enterRule(_localctx, 90, RULE_thf_tuple);
		try {
			setState(770);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__14:
				enterOuterAlt(_localctx, 1);
				{
				setState(765);
				match(T__14);
				}
				break;
			case T__10:
				enterOuterAlt(_localctx, 2);
				{
				setState(766);
				match(T__10);
				setState(767);
				thf_formula_list();
				setState(768);
				match(T__11);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_fof_functionContext extends ParserRuleContext {
		public FunctorContext functor() {
			return getRuleContext(FunctorContext.class,0);
		}
		public Thf_argumentsContext thf_arguments() {
			return getRuleContext(Thf_argumentsContext.class,0);
		}
		public Defined_functorContext defined_functor() {
			return getRuleContext(Defined_functorContext.class,0);
		}
		public System_functorContext system_functor() {
			return getRuleContext(System_functorContext.class,0);
		}
		public Thf_fof_functionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_fof_function; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_fof_function(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_fof_function(this);
		}
	}

	public final Thf_fof_functionContext thf_fof_function() throws RecognitionException {
		Thf_fof_functionContext _localctx = new Thf_fof_functionContext(_ctx, getState());
		enterRule(_localctx, 92, RULE_thf_fof_function);
		try {
			setState(787);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(772);
				functor();
				setState(773);
				match(T__8);
				setState(774);
				thf_arguments();
				setState(775);
				match(T__9);
				}
				break;
			case Dollar_word:
				enterOuterAlt(_localctx, 2);
				{
				setState(777);
				defined_functor();
				setState(778);
				match(T__8);
				setState(779);
				thf_arguments();
				setState(780);
				match(T__9);
				}
				break;
			case Dollar_dollar_word:
				enterOuterAlt(_localctx, 3);
				{
				setState(782);
				system_functor();
				setState(783);
				match(T__8);
				setState(784);
				thf_arguments();
				setState(785);
				match(T__9);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_argumentsContext extends ParserRuleContext {
		public Thf_formula_listContext thf_formula_list() {
			return getRuleContext(Thf_formula_listContext.class,0);
		}
		public Thf_argumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_arguments; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_arguments(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_arguments(this);
		}
	}

	public final Thf_argumentsContext thf_arguments() throws RecognitionException {
		Thf_argumentsContext _localctx = new Thf_argumentsContext(_ctx, getState());
		enterRule(_localctx, 94, RULE_thf_arguments);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(789);
			thf_formula_list();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_formula_listContext extends ParserRuleContext {
		public Thf_logic_formulaContext thf_logic_formula() {
			return getRuleContext(Thf_logic_formulaContext.class,0);
		}
		public Thf_formula_listContext thf_formula_list() {
			return getRuleContext(Thf_formula_listContext.class,0);
		}
		public Thf_formula_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_formula_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_formula_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_formula_list(this);
		}
	}

	public final Thf_formula_listContext thf_formula_list() throws RecognitionException {
		Thf_formula_listContext _localctx = new Thf_formula_listContext(_ctx, getState());
		enterRule(_localctx, 96, RULE_thf_formula_list);
		try {
			setState(796);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,35,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(791);
				thf_logic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(792);
				thf_logic_formula();
				setState(793);
				match(T__1);
				setState(794);
				thf_formula_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_atom_typingContext extends ParserRuleContext {
		public Untyped_atomContext untyped_atom() {
			return getRuleContext(Untyped_atomContext.class,0);
		}
		public Thf_top_level_typeContext thf_top_level_type() {
			return getRuleContext(Thf_top_level_typeContext.class,0);
		}
		public Thf_atom_typingContext thf_atom_typing() {
			return getRuleContext(Thf_atom_typingContext.class,0);
		}
		public Thf_atom_typingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_atom_typing; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_atom_typing(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_atom_typing(this);
		}
	}

	public final Thf_atom_typingContext thf_atom_typing() throws RecognitionException {
		Thf_atom_typingContext _localctx = new Thf_atom_typingContext(_ctx, getState());
		enterRule(_localctx, 98, RULE_thf_atom_typing);
		try {
			setState(806);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Dollar_dollar_word:
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(798);
				untyped_atom();
				setState(799);
				match(T__12);
				setState(800);
				thf_top_level_type();
				}
				break;
			case T__8:
				enterOuterAlt(_localctx, 2);
				{
				setState(802);
				match(T__8);
				setState(803);
				thf_atom_typing();
				setState(804);
				match(T__9);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_top_level_typeContext extends ParserRuleContext {
		public Thf_unitary_typeContext thf_unitary_type() {
			return getRuleContext(Thf_unitary_typeContext.class,0);
		}
		public Thf_mapping_typeContext thf_mapping_type() {
			return getRuleContext(Thf_mapping_typeContext.class,0);
		}
		public Thf_apply_typeContext thf_apply_type() {
			return getRuleContext(Thf_apply_typeContext.class,0);
		}
		public Thf_top_level_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_top_level_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_top_level_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_top_level_type(this);
		}
	}

	public final Thf_top_level_typeContext thf_top_level_type() throws RecognitionException {
		Thf_top_level_typeContext _localctx = new Thf_top_level_typeContext(_ctx, getState());
		enterRule(_localctx, 100, RULE_thf_top_level_type);
		try {
			setState(811);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,37,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(808);
				thf_unitary_type();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(809);
				thf_mapping_type();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(810);
				thf_apply_type();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_unitary_typeContext extends ParserRuleContext {
		public Thf_unitary_formulaContext thf_unitary_formula() {
			return getRuleContext(Thf_unitary_formulaContext.class,0);
		}
		public Thf_unitary_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_unitary_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_unitary_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_unitary_type(this);
		}
	}

	public final Thf_unitary_typeContext thf_unitary_type() throws RecognitionException {
		Thf_unitary_typeContext _localctx = new Thf_unitary_typeContext(_ctx, getState());
		enterRule(_localctx, 102, RULE_thf_unitary_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(813);
			thf_unitary_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_apply_typeContext extends ParserRuleContext {
		public Thf_apply_formulaContext thf_apply_formula() {
			return getRuleContext(Thf_apply_formulaContext.class,0);
		}
		public Thf_apply_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_apply_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_apply_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_apply_type(this);
		}
	}

	public final Thf_apply_typeContext thf_apply_type() throws RecognitionException {
		Thf_apply_typeContext _localctx = new Thf_apply_typeContext(_ctx, getState());
		enterRule(_localctx, 104, RULE_thf_apply_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(815);
			thf_apply_formula(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_binary_typeContext extends ParserRuleContext {
		public Thf_mapping_typeContext thf_mapping_type() {
			return getRuleContext(Thf_mapping_typeContext.class,0);
		}
		public Thf_xprod_typeContext thf_xprod_type() {
			return getRuleContext(Thf_xprod_typeContext.class,0);
		}
		public Thf_union_typeContext thf_union_type() {
			return getRuleContext(Thf_union_typeContext.class,0);
		}
		public Thf_binary_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_binary_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_binary_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_binary_type(this);
		}
	}

	public final Thf_binary_typeContext thf_binary_type() throws RecognitionException {
		Thf_binary_typeContext _localctx = new Thf_binary_typeContext(_ctx, getState());
		enterRule(_localctx, 106, RULE_thf_binary_type);
		try {
			setState(820);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,38,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(817);
				thf_mapping_type();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(818);
				thf_xprod_type(0);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(819);
				thf_union_type(0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_mapping_typeContext extends ParserRuleContext {
		public List<Thf_unitary_typeContext> thf_unitary_type() {
			return getRuleContexts(Thf_unitary_typeContext.class);
		}
		public Thf_unitary_typeContext thf_unitary_type(int i) {
			return getRuleContext(Thf_unitary_typeContext.class,i);
		}
		public TerminalNode Arrow() { return getToken(tptp_v7_0_0_0Parser.Arrow, 0); }
		public Thf_mapping_typeContext thf_mapping_type() {
			return getRuleContext(Thf_mapping_typeContext.class,0);
		}
		public Thf_mapping_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_mapping_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_mapping_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_mapping_type(this);
		}
	}

	public final Thf_mapping_typeContext thf_mapping_type() throws RecognitionException {
		Thf_mapping_typeContext _localctx = new Thf_mapping_typeContext(_ctx, getState());
		enterRule(_localctx, 108, RULE_thf_mapping_type);
		try {
			setState(830);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,39,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(822);
				thf_unitary_type();
				setState(823);
				match(Arrow);
				setState(824);
				thf_unitary_type();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(826);
				thf_unitary_type();
				setState(827);
				match(Arrow);
				setState(828);
				thf_mapping_type();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_xprod_typeContext extends ParserRuleContext {
		public List<Thf_unitary_typeContext> thf_unitary_type() {
			return getRuleContexts(Thf_unitary_typeContext.class);
		}
		public Thf_unitary_typeContext thf_unitary_type(int i) {
			return getRuleContext(Thf_unitary_typeContext.class,i);
		}
		public TerminalNode Star() { return getToken(tptp_v7_0_0_0Parser.Star, 0); }
		public Thf_xprod_typeContext thf_xprod_type() {
			return getRuleContext(Thf_xprod_typeContext.class,0);
		}
		public Thf_xprod_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_xprod_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_xprod_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_xprod_type(this);
		}
	}

	public final Thf_xprod_typeContext thf_xprod_type() throws RecognitionException {
		return thf_xprod_type(0);
	}

	private Thf_xprod_typeContext thf_xprod_type(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Thf_xprod_typeContext _localctx = new Thf_xprod_typeContext(_ctx, _parentState);
		Thf_xprod_typeContext _prevctx = _localctx;
		int _startState = 110;
		enterRecursionRule(_localctx, 110, RULE_thf_xprod_type, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(833);
			thf_unitary_type();
			setState(834);
			match(Star);
			setState(835);
			thf_unitary_type();
			}
			_ctx.stop = _input.LT(-1);
			setState(842);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,40,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Thf_xprod_typeContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_thf_xprod_type);
					setState(837);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(838);
					match(Star);
					setState(839);
					thf_unitary_type();
					}
					} 
				}
				setState(844);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,40,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Thf_union_typeContext extends ParserRuleContext {
		public List<Thf_unitary_typeContext> thf_unitary_type() {
			return getRuleContexts(Thf_unitary_typeContext.class);
		}
		public Thf_unitary_typeContext thf_unitary_type(int i) {
			return getRuleContext(Thf_unitary_typeContext.class,i);
		}
		public TerminalNode Plus() { return getToken(tptp_v7_0_0_0Parser.Plus, 0); }
		public Thf_union_typeContext thf_union_type() {
			return getRuleContext(Thf_union_typeContext.class,0);
		}
		public Thf_union_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_union_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_union_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_union_type(this);
		}
	}

	public final Thf_union_typeContext thf_union_type() throws RecognitionException {
		return thf_union_type(0);
	}

	private Thf_union_typeContext thf_union_type(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Thf_union_typeContext _localctx = new Thf_union_typeContext(_ctx, _parentState);
		Thf_union_typeContext _prevctx = _localctx;
		int _startState = 112;
		enterRecursionRule(_localctx, 112, RULE_thf_union_type, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(846);
			thf_unitary_type();
			setState(847);
			match(Plus);
			setState(848);
			thf_unitary_type();
			}
			_ctx.stop = _input.LT(-1);
			setState(855);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,41,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Thf_union_typeContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_thf_union_type);
					setState(850);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(851);
					match(Plus);
					setState(852);
					thf_unitary_type();
					}
					} 
				}
				setState(857);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,41,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Thf_subtypeContext extends ParserRuleContext {
		public Untyped_atomContext untyped_atom() {
			return getRuleContext(Untyped_atomContext.class,0);
		}
		public TerminalNode Subtype_sign() { return getToken(tptp_v7_0_0_0Parser.Subtype_sign, 0); }
		public AtomContext atom() {
			return getRuleContext(AtomContext.class,0);
		}
		public Thf_subtypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_subtype; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_subtype(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_subtype(this);
		}
	}

	public final Thf_subtypeContext thf_subtype() throws RecognitionException {
		Thf_subtypeContext _localctx = new Thf_subtypeContext(_ctx, getState());
		enterRule(_localctx, 114, RULE_thf_subtype);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(858);
			untyped_atom();
			setState(859);
			match(Subtype_sign);
			setState(860);
			atom();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_definitionContext extends ParserRuleContext {
		public Thf_atomic_formulaContext thf_atomic_formula() {
			return getRuleContext(Thf_atomic_formulaContext.class,0);
		}
		public TerminalNode Identical() { return getToken(tptp_v7_0_0_0Parser.Identical, 0); }
		public Thf_logic_formulaContext thf_logic_formula() {
			return getRuleContext(Thf_logic_formulaContext.class,0);
		}
		public Thf_definitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_definition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_definition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_definition(this);
		}
	}

	public final Thf_definitionContext thf_definition() throws RecognitionException {
		Thf_definitionContext _localctx = new Thf_definitionContext(_ctx, getState());
		enterRule(_localctx, 116, RULE_thf_definition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(862);
			thf_atomic_formula();
			setState(863);
			match(Identical);
			setState(864);
			thf_logic_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_sequentContext extends ParserRuleContext {
		public List<Thf_tupleContext> thf_tuple() {
			return getRuleContexts(Thf_tupleContext.class);
		}
		public Thf_tupleContext thf_tuple(int i) {
			return getRuleContext(Thf_tupleContext.class,i);
		}
		public TerminalNode Gentzen_arrow() { return getToken(tptp_v7_0_0_0Parser.Gentzen_arrow, 0); }
		public Thf_sequentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_sequent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_sequent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_sequent(this);
		}
	}

	public final Thf_sequentContext thf_sequent() throws RecognitionException {
		Thf_sequentContext _localctx = new Thf_sequentContext(_ctx, getState());
		enterRule(_localctx, 118, RULE_thf_sequent);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(866);
			thf_tuple();
			setState(867);
			match(Gentzen_arrow);
			setState(868);
			thf_tuple();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_formulaContext extends ParserRuleContext {
		public Tff_logic_formulaContext tff_logic_formula() {
			return getRuleContext(Tff_logic_formulaContext.class,0);
		}
		public Tff_atom_typingContext tff_atom_typing() {
			return getRuleContext(Tff_atom_typingContext.class,0);
		}
		public Tff_subtypeContext tff_subtype() {
			return getRuleContext(Tff_subtypeContext.class,0);
		}
		public Tff_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_formula(this);
		}
	}

	public final Tff_formulaContext tff_formula() throws RecognitionException {
		Tff_formulaContext _localctx = new Tff_formulaContext(_ctx, getState());
		enterRule(_localctx, 120, RULE_tff_formula);
		try {
			setState(873);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,42,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(870);
				tff_logic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(871);
				tff_atom_typing();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(872);
				tff_subtype();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_logic_formulaContext extends ParserRuleContext {
		public Tff_unitary_formulaContext tff_unitary_formula() {
			return getRuleContext(Tff_unitary_formulaContext.class,0);
		}
		public Tff_unary_formulaContext tff_unary_formula() {
			return getRuleContext(Tff_unary_formulaContext.class,0);
		}
		public Tff_binary_formulaContext tff_binary_formula() {
			return getRuleContext(Tff_binary_formulaContext.class,0);
		}
		public Tff_defined_infixContext tff_defined_infix() {
			return getRuleContext(Tff_defined_infixContext.class,0);
		}
		public Txf_definitionContext txf_definition() {
			return getRuleContext(Txf_definitionContext.class,0);
		}
		public Txf_sequentContext txf_sequent() {
			return getRuleContext(Txf_sequentContext.class,0);
		}
		public Tff_logic_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_logic_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_logic_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_logic_formula(this);
		}
	}

	public final Tff_logic_formulaContext tff_logic_formula() throws RecognitionException {
		Tff_logic_formulaContext _localctx = new Tff_logic_formulaContext(_ctx, getState());
		enterRule(_localctx, 122, RULE_tff_logic_formula);
		try {
			setState(881);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,43,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(875);
				tff_unitary_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(876);
				tff_unary_formula();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(877);
				tff_binary_formula();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(878);
				tff_defined_infix();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(879);
				txf_definition();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(880);
				txf_sequent();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_binary_formulaContext extends ParserRuleContext {
		public Tff_binary_nonassocContext tff_binary_nonassoc() {
			return getRuleContext(Tff_binary_nonassocContext.class,0);
		}
		public Tff_binary_assocContext tff_binary_assoc() {
			return getRuleContext(Tff_binary_assocContext.class,0);
		}
		public Tff_binary_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_binary_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_binary_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_binary_formula(this);
		}
	}

	public final Tff_binary_formulaContext tff_binary_formula() throws RecognitionException {
		Tff_binary_formulaContext _localctx = new Tff_binary_formulaContext(_ctx, getState());
		enterRule(_localctx, 124, RULE_tff_binary_formula);
		try {
			setState(885);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,44,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(883);
				tff_binary_nonassoc();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(884);
				tff_binary_assoc();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_binary_nonassocContext extends ParserRuleContext {
		public List<Tff_unit_formulaContext> tff_unit_formula() {
			return getRuleContexts(Tff_unit_formulaContext.class);
		}
		public Tff_unit_formulaContext tff_unit_formula(int i) {
			return getRuleContext(Tff_unit_formulaContext.class,i);
		}
		public Nonassoc_connectiveContext nonassoc_connective() {
			return getRuleContext(Nonassoc_connectiveContext.class,0);
		}
		public Tff_binary_nonassocContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_binary_nonassoc; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_binary_nonassoc(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_binary_nonassoc(this);
		}
	}

	public final Tff_binary_nonassocContext tff_binary_nonassoc() throws RecognitionException {
		Tff_binary_nonassocContext _localctx = new Tff_binary_nonassocContext(_ctx, getState());
		enterRule(_localctx, 126, RULE_tff_binary_nonassoc);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(887);
			tff_unit_formula();
			setState(888);
			nonassoc_connective();
			setState(889);
			tff_unit_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_binary_assocContext extends ParserRuleContext {
		public Tff_or_formulaContext tff_or_formula() {
			return getRuleContext(Tff_or_formulaContext.class,0);
		}
		public Tff_and_formulaContext tff_and_formula() {
			return getRuleContext(Tff_and_formulaContext.class,0);
		}
		public Tff_binary_assocContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_binary_assoc; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_binary_assoc(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_binary_assoc(this);
		}
	}

	public final Tff_binary_assocContext tff_binary_assoc() throws RecognitionException {
		Tff_binary_assocContext _localctx = new Tff_binary_assocContext(_ctx, getState());
		enterRule(_localctx, 128, RULE_tff_binary_assoc);
		try {
			setState(893);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,45,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(891);
				tff_or_formula(0);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(892);
				tff_and_formula(0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_or_formulaContext extends ParserRuleContext {
		public List<Tff_unit_formulaContext> tff_unit_formula() {
			return getRuleContexts(Tff_unit_formulaContext.class);
		}
		public Tff_unit_formulaContext tff_unit_formula(int i) {
			return getRuleContext(Tff_unit_formulaContext.class,i);
		}
		public TerminalNode Or() { return getToken(tptp_v7_0_0_0Parser.Or, 0); }
		public Tff_or_formulaContext tff_or_formula() {
			return getRuleContext(Tff_or_formulaContext.class,0);
		}
		public Tff_or_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_or_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_or_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_or_formula(this);
		}
	}

	public final Tff_or_formulaContext tff_or_formula() throws RecognitionException {
		return tff_or_formula(0);
	}

	private Tff_or_formulaContext tff_or_formula(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Tff_or_formulaContext _localctx = new Tff_or_formulaContext(_ctx, _parentState);
		Tff_or_formulaContext _prevctx = _localctx;
		int _startState = 130;
		enterRecursionRule(_localctx, 130, RULE_tff_or_formula, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(896);
			tff_unit_formula();
			setState(897);
			match(Or);
			setState(898);
			tff_unit_formula();
			}
			_ctx.stop = _input.LT(-1);
			setState(905);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,46,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Tff_or_formulaContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_tff_or_formula);
					setState(900);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(901);
					match(Or);
					setState(902);
					tff_unit_formula();
					}
					} 
				}
				setState(907);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,46,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Tff_and_formulaContext extends ParserRuleContext {
		public List<Tff_unit_formulaContext> tff_unit_formula() {
			return getRuleContexts(Tff_unit_formulaContext.class);
		}
		public Tff_unit_formulaContext tff_unit_formula(int i) {
			return getRuleContext(Tff_unit_formulaContext.class,i);
		}
		public TerminalNode And() { return getToken(tptp_v7_0_0_0Parser.And, 0); }
		public Tff_and_formulaContext tff_and_formula() {
			return getRuleContext(Tff_and_formulaContext.class,0);
		}
		public Tff_and_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_and_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_and_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_and_formula(this);
		}
	}

	public final Tff_and_formulaContext tff_and_formula() throws RecognitionException {
		return tff_and_formula(0);
	}

	private Tff_and_formulaContext tff_and_formula(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Tff_and_formulaContext _localctx = new Tff_and_formulaContext(_ctx, _parentState);
		Tff_and_formulaContext _prevctx = _localctx;
		int _startState = 132;
		enterRecursionRule(_localctx, 132, RULE_tff_and_formula, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(909);
			tff_unit_formula();
			setState(910);
			match(And);
			setState(911);
			tff_unit_formula();
			}
			_ctx.stop = _input.LT(-1);
			setState(918);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,47,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Tff_and_formulaContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_tff_and_formula);
					setState(913);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(914);
					match(And);
					setState(915);
					tff_unit_formula();
					}
					} 
				}
				setState(920);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,47,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Tff_unit_formulaContext extends ParserRuleContext {
		public Tff_unitary_formulaContext tff_unitary_formula() {
			return getRuleContext(Tff_unitary_formulaContext.class,0);
		}
		public Tff_unary_formulaContext tff_unary_formula() {
			return getRuleContext(Tff_unary_formulaContext.class,0);
		}
		public Tff_defined_infixContext tff_defined_infix() {
			return getRuleContext(Tff_defined_infixContext.class,0);
		}
		public Tff_unit_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_unit_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_unit_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_unit_formula(this);
		}
	}

	public final Tff_unit_formulaContext tff_unit_formula() throws RecognitionException {
		Tff_unit_formulaContext _localctx = new Tff_unit_formulaContext(_ctx, getState());
		enterRule(_localctx, 134, RULE_tff_unit_formula);
		try {
			setState(924);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,48,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(921);
				tff_unitary_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(922);
				tff_unary_formula();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(923);
				tff_defined_infix();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_preunit_formulaContext extends ParserRuleContext {
		public Tff_unitary_formulaContext tff_unitary_formula() {
			return getRuleContext(Tff_unitary_formulaContext.class,0);
		}
		public Tff_prefix_unaryContext tff_prefix_unary() {
			return getRuleContext(Tff_prefix_unaryContext.class,0);
		}
		public Tff_preunit_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_preunit_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_preunit_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_preunit_formula(this);
		}
	}

	public final Tff_preunit_formulaContext tff_preunit_formula() throws RecognitionException {
		Tff_preunit_formulaContext _localctx = new Tff_preunit_formulaContext(_ctx, getState());
		enterRule(_localctx, 136, RULE_tff_preunit_formula);
		try {
			setState(928);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__8:
			case T__10:
			case T__13:
			case T__15:
			case T__16:
			case T__17:
			case T__18:
			case T__19:
			case Forall:
			case Exists:
			case Dollar_word:
			case Dollar_dollar_word:
			case Upper_word:
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(926);
				tff_unitary_formula();
				}
				break;
			case Not:
				enterOuterAlt(_localctx, 2);
				{
				setState(927);
				tff_prefix_unary();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_unitary_formulaContext extends ParserRuleContext {
		public Tff_quantified_formulaContext tff_quantified_formula() {
			return getRuleContext(Tff_quantified_formulaContext.class,0);
		}
		public Tff_atomic_formulaContext tff_atomic_formula() {
			return getRuleContext(Tff_atomic_formulaContext.class,0);
		}
		public Txf_unitary_formulaContext txf_unitary_formula() {
			return getRuleContext(Txf_unitary_formulaContext.class,0);
		}
		public Tff_logic_formulaContext tff_logic_formula() {
			return getRuleContext(Tff_logic_formulaContext.class,0);
		}
		public Tff_unitary_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_unitary_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_unitary_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_unitary_formula(this);
		}
	}

	public final Tff_unitary_formulaContext tff_unitary_formula() throws RecognitionException {
		Tff_unitary_formulaContext _localctx = new Tff_unitary_formulaContext(_ctx, getState());
		enterRule(_localctx, 138, RULE_tff_unitary_formula);
		try {
			setState(937);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Forall:
			case Exists:
				enterOuterAlt(_localctx, 1);
				{
				setState(930);
				tff_quantified_formula();
				}
				break;
			case T__10:
			case T__13:
			case T__15:
			case T__16:
			case T__17:
			case T__18:
			case T__19:
			case Dollar_word:
			case Dollar_dollar_word:
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 2);
				{
				setState(931);
				tff_atomic_formula();
				}
				break;
			case Upper_word:
				enterOuterAlt(_localctx, 3);
				{
				setState(932);
				txf_unitary_formula();
				}
				break;
			case T__8:
				enterOuterAlt(_localctx, 4);
				{
				setState(933);
				match(T__8);
				setState(934);
				tff_logic_formula();
				setState(935);
				match(T__9);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_unitary_formulaContext extends ParserRuleContext {
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Txf_unitary_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_unitary_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_unitary_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_unitary_formula(this);
		}
	}

	public final Txf_unitary_formulaContext txf_unitary_formula() throws RecognitionException {
		Txf_unitary_formulaContext _localctx = new Txf_unitary_formulaContext(_ctx, getState());
		enterRule(_localctx, 140, RULE_txf_unitary_formula);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(939);
			variable();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_quantified_formulaContext extends ParserRuleContext {
		public Fof_quantifierContext fof_quantifier() {
			return getRuleContext(Fof_quantifierContext.class,0);
		}
		public Tff_variable_listContext tff_variable_list() {
			return getRuleContext(Tff_variable_listContext.class,0);
		}
		public Tff_unit_formulaContext tff_unit_formula() {
			return getRuleContext(Tff_unit_formulaContext.class,0);
		}
		public Tff_quantified_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_quantified_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_quantified_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_quantified_formula(this);
		}
	}

	public final Tff_quantified_formulaContext tff_quantified_formula() throws RecognitionException {
		Tff_quantified_formulaContext _localctx = new Tff_quantified_formulaContext(_ctx, getState());
		enterRule(_localctx, 142, RULE_tff_quantified_formula);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(941);
			fof_quantifier();
			setState(942);
			match(T__10);
			setState(943);
			tff_variable_list();
			setState(944);
			match(T__11);
			setState(945);
			match(T__12);
			setState(946);
			tff_unit_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_variable_listContext extends ParserRuleContext {
		public Tff_variableContext tff_variable() {
			return getRuleContext(Tff_variableContext.class,0);
		}
		public Tff_variable_listContext tff_variable_list() {
			return getRuleContext(Tff_variable_listContext.class,0);
		}
		public Tff_variable_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_variable_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_variable_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_variable_list(this);
		}
	}

	public final Tff_variable_listContext tff_variable_list() throws RecognitionException {
		Tff_variable_listContext _localctx = new Tff_variable_listContext(_ctx, getState());
		enterRule(_localctx, 144, RULE_tff_variable_list);
		try {
			setState(953);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,51,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(948);
				tff_variable();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(949);
				tff_variable();
				setState(950);
				match(T__1);
				setState(951);
				tff_variable_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_variableContext extends ParserRuleContext {
		public Tff_typed_variableContext tff_typed_variable() {
			return getRuleContext(Tff_typed_variableContext.class,0);
		}
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Tff_variableContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_variable; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_variable(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_variable(this);
		}
	}

	public final Tff_variableContext tff_variable() throws RecognitionException {
		Tff_variableContext _localctx = new Tff_variableContext(_ctx, getState());
		enterRule(_localctx, 146, RULE_tff_variable);
		try {
			setState(957);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,52,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(955);
				tff_typed_variable();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(956);
				variable();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_typed_variableContext extends ParserRuleContext {
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Tff_atomic_typeContext tff_atomic_type() {
			return getRuleContext(Tff_atomic_typeContext.class,0);
		}
		public Tff_typed_variableContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_typed_variable; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_typed_variable(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_typed_variable(this);
		}
	}

	public final Tff_typed_variableContext tff_typed_variable() throws RecognitionException {
		Tff_typed_variableContext _localctx = new Tff_typed_variableContext(_ctx, getState());
		enterRule(_localctx, 148, RULE_tff_typed_variable);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(959);
			variable();
			setState(960);
			match(T__12);
			setState(961);
			tff_atomic_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_unary_formulaContext extends ParserRuleContext {
		public Tff_prefix_unaryContext tff_prefix_unary() {
			return getRuleContext(Tff_prefix_unaryContext.class,0);
		}
		public Tff_infix_unaryContext tff_infix_unary() {
			return getRuleContext(Tff_infix_unaryContext.class,0);
		}
		public Tff_unary_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_unary_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_unary_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_unary_formula(this);
		}
	}

	public final Tff_unary_formulaContext tff_unary_formula() throws RecognitionException {
		Tff_unary_formulaContext _localctx = new Tff_unary_formulaContext(_ctx, getState());
		enterRule(_localctx, 150, RULE_tff_unary_formula);
		try {
			setState(965);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Not:
				enterOuterAlt(_localctx, 1);
				{
				setState(963);
				tff_prefix_unary();
				}
				break;
			case T__8:
			case T__10:
			case T__13:
			case T__14:
			case T__15:
			case T__16:
			case T__17:
			case T__18:
			case T__19:
			case Real:
			case Rational:
			case Integer:
			case Dollar_word:
			case Dollar_dollar_word:
			case Upper_word:
			case Lower_word:
			case Single_quoted:
			case Distinct_object:
				enterOuterAlt(_localctx, 2);
				{
				setState(964);
				tff_infix_unary();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_prefix_unaryContext extends ParserRuleContext {
		public Unary_connectiveContext unary_connective() {
			return getRuleContext(Unary_connectiveContext.class,0);
		}
		public Tff_preunit_formulaContext tff_preunit_formula() {
			return getRuleContext(Tff_preunit_formulaContext.class,0);
		}
		public Tff_prefix_unaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_prefix_unary; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_prefix_unary(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_prefix_unary(this);
		}
	}

	public final Tff_prefix_unaryContext tff_prefix_unary() throws RecognitionException {
		Tff_prefix_unaryContext _localctx = new Tff_prefix_unaryContext(_ctx, getState());
		enterRule(_localctx, 152, RULE_tff_prefix_unary);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(967);
			unary_connective();
			setState(968);
			tff_preunit_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_infix_unaryContext extends ParserRuleContext {
		public List<Tff_unitary_termContext> tff_unitary_term() {
			return getRuleContexts(Tff_unitary_termContext.class);
		}
		public Tff_unitary_termContext tff_unitary_term(int i) {
			return getRuleContext(Tff_unitary_termContext.class,i);
		}
		public TerminalNode Infix_inequality() { return getToken(tptp_v7_0_0_0Parser.Infix_inequality, 0); }
		public Tff_infix_unaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_infix_unary; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_infix_unary(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_infix_unary(this);
		}
	}

	public final Tff_infix_unaryContext tff_infix_unary() throws RecognitionException {
		Tff_infix_unaryContext _localctx = new Tff_infix_unaryContext(_ctx, getState());
		enterRule(_localctx, 154, RULE_tff_infix_unary);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(970);
			tff_unitary_term();
			setState(971);
			match(Infix_inequality);
			setState(972);
			tff_unitary_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_atomic_formulaContext extends ParserRuleContext {
		public Tff_plain_atomicContext tff_plain_atomic() {
			return getRuleContext(Tff_plain_atomicContext.class,0);
		}
		public Tff_defined_atomicContext tff_defined_atomic() {
			return getRuleContext(Tff_defined_atomicContext.class,0);
		}
		public Tff_system_atomicContext tff_system_atomic() {
			return getRuleContext(Tff_system_atomicContext.class,0);
		}
		public Tff_atomic_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_atomic_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_atomic_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_atomic_formula(this);
		}
	}

	public final Tff_atomic_formulaContext tff_atomic_formula() throws RecognitionException {
		Tff_atomic_formulaContext _localctx = new Tff_atomic_formulaContext(_ctx, getState());
		enterRule(_localctx, 156, RULE_tff_atomic_formula);
		try {
			setState(977);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(974);
				tff_plain_atomic();
				}
				break;
			case T__10:
			case T__13:
			case T__15:
			case T__16:
			case T__17:
			case T__18:
			case T__19:
			case Dollar_word:
				enterOuterAlt(_localctx, 2);
				{
				setState(975);
				tff_defined_atomic();
				}
				break;
			case Dollar_dollar_word:
				enterOuterAlt(_localctx, 3);
				{
				setState(976);
				tff_system_atomic();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_plain_atomicContext extends ParserRuleContext {
		public ConstantContext constant() {
			return getRuleContext(ConstantContext.class,0);
		}
		public FunctorContext functor() {
			return getRuleContext(FunctorContext.class,0);
		}
		public Tff_argumentsContext tff_arguments() {
			return getRuleContext(Tff_argumentsContext.class,0);
		}
		public Tff_plain_atomicContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_plain_atomic; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_plain_atomic(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_plain_atomic(this);
		}
	}

	public final Tff_plain_atomicContext tff_plain_atomic() throws RecognitionException {
		Tff_plain_atomicContext _localctx = new Tff_plain_atomicContext(_ctx, getState());
		enterRule(_localctx, 158, RULE_tff_plain_atomic);
		try {
			setState(985);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,55,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(979);
				constant();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(980);
				functor();
				setState(981);
				match(T__8);
				setState(982);
				tff_arguments();
				setState(983);
				match(T__9);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_defined_atomicContext extends ParserRuleContext {
		public Tff_defined_plainContext tff_defined_plain() {
			return getRuleContext(Tff_defined_plainContext.class,0);
		}
		public Ntf_connectiveContext ntf_connective() {
			return getRuleContext(Ntf_connectiveContext.class,0);
		}
		public Tff_defined_atomicContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_defined_atomic; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_defined_atomic(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_defined_atomic(this);
		}
	}

	public final Tff_defined_atomicContext tff_defined_atomic() throws RecognitionException {
		Tff_defined_atomicContext _localctx = new Tff_defined_atomicContext(_ctx, getState());
		enterRule(_localctx, 160, RULE_tff_defined_atomic);
		try {
			setState(989);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,56,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(987);
				tff_defined_plain();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(988);
				ntf_connective();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_defined_plainContext extends ParserRuleContext {
		public Defined_constantContext defined_constant() {
			return getRuleContext(Defined_constantContext.class,0);
		}
		public Defined_functorContext defined_functor() {
			return getRuleContext(Defined_functorContext.class,0);
		}
		public Tff_argumentsContext tff_arguments() {
			return getRuleContext(Tff_argumentsContext.class,0);
		}
		public Txf_ntf_atomContext txf_ntf_atom() {
			return getRuleContext(Txf_ntf_atomContext.class,0);
		}
		public Txf_letContext txf_let() {
			return getRuleContext(Txf_letContext.class,0);
		}
		public Tff_defined_plainContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_defined_plain; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_defined_plain(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_defined_plain(this);
		}
	}

	public final Tff_defined_plainContext tff_defined_plain() throws RecognitionException {
		Tff_defined_plainContext _localctx = new Tff_defined_plainContext(_ctx, getState());
		enterRule(_localctx, 162, RULE_tff_defined_plain);
		try {
			setState(999);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,57,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(991);
				defined_constant();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(992);
				defined_functor();
				setState(993);
				match(T__8);
				setState(994);
				tff_arguments();
				setState(995);
				match(T__9);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(997);
				txf_ntf_atom();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(998);
				txf_let();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_defined_infixContext extends ParserRuleContext {
		public List<Tff_unitary_termContext> tff_unitary_term() {
			return getRuleContexts(Tff_unitary_termContext.class);
		}
		public Tff_unitary_termContext tff_unitary_term(int i) {
			return getRuleContext(Tff_unitary_termContext.class,i);
		}
		public Defined_infix_predContext defined_infix_pred() {
			return getRuleContext(Defined_infix_predContext.class,0);
		}
		public Tff_defined_infixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_defined_infix; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_defined_infix(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_defined_infix(this);
		}
	}

	public final Tff_defined_infixContext tff_defined_infix() throws RecognitionException {
		Tff_defined_infixContext _localctx = new Tff_defined_infixContext(_ctx, getState());
		enterRule(_localctx, 164, RULE_tff_defined_infix);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1001);
			tff_unitary_term();
			setState(1002);
			defined_infix_pred();
			setState(1003);
			tff_unitary_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_system_atomicContext extends ParserRuleContext {
		public System_constantContext system_constant() {
			return getRuleContext(System_constantContext.class,0);
		}
		public System_functorContext system_functor() {
			return getRuleContext(System_functorContext.class,0);
		}
		public Tff_argumentsContext tff_arguments() {
			return getRuleContext(Tff_argumentsContext.class,0);
		}
		public Tff_system_atomicContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_system_atomic; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_system_atomic(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_system_atomic(this);
		}
	}

	public final Tff_system_atomicContext tff_system_atomic() throws RecognitionException {
		Tff_system_atomicContext _localctx = new Tff_system_atomicContext(_ctx, getState());
		enterRule(_localctx, 166, RULE_tff_system_atomic);
		try {
			setState(1011);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,58,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1005);
				system_constant();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1006);
				system_functor();
				setState(1007);
				match(T__8);
				setState(1008);
				tff_arguments();
				setState(1009);
				match(T__9);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_letContext extends ParserRuleContext {
		public Txf_let_typesContext txf_let_types() {
			return getRuleContext(Txf_let_typesContext.class,0);
		}
		public Txf_let_defnsContext txf_let_defns() {
			return getRuleContext(Txf_let_defnsContext.class,0);
		}
		public Tff_termContext tff_term() {
			return getRuleContext(Tff_termContext.class,0);
		}
		public Txf_letContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_let; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_let(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_let(this);
		}
	}

	public final Txf_letContext txf_let() throws RecognitionException {
		Txf_letContext _localctx = new Txf_letContext(_ctx, getState());
		enterRule(_localctx, 168, RULE_txf_let);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1013);
			match(T__13);
			setState(1014);
			txf_let_types();
			setState(1015);
			match(T__1);
			setState(1016);
			txf_let_defns();
			setState(1017);
			match(T__1);
			setState(1018);
			tff_term();
			setState(1019);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_let_typesContext extends ParserRuleContext {
		public Tff_atom_typingContext tff_atom_typing() {
			return getRuleContext(Tff_atom_typingContext.class,0);
		}
		public Tff_atom_typing_listContext tff_atom_typing_list() {
			return getRuleContext(Tff_atom_typing_listContext.class,0);
		}
		public Txf_let_typesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_let_types; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_let_types(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_let_types(this);
		}
	}

	public final Txf_let_typesContext txf_let_types() throws RecognitionException {
		Txf_let_typesContext _localctx = new Txf_let_typesContext(_ctx, getState());
		enterRule(_localctx, 170, RULE_txf_let_types);
		try {
			setState(1026);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__8:
			case Dollar_dollar_word:
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(1021);
				tff_atom_typing();
				}
				break;
			case T__10:
				enterOuterAlt(_localctx, 2);
				{
				setState(1022);
				match(T__10);
				setState(1023);
				tff_atom_typing_list();
				setState(1024);
				match(T__11);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_atom_typing_listContext extends ParserRuleContext {
		public Tff_atom_typingContext tff_atom_typing() {
			return getRuleContext(Tff_atom_typingContext.class,0);
		}
		public Tff_atom_typing_listContext tff_atom_typing_list() {
			return getRuleContext(Tff_atom_typing_listContext.class,0);
		}
		public Tff_atom_typing_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_atom_typing_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_atom_typing_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_atom_typing_list(this);
		}
	}

	public final Tff_atom_typing_listContext tff_atom_typing_list() throws RecognitionException {
		Tff_atom_typing_listContext _localctx = new Tff_atom_typing_listContext(_ctx, getState());
		enterRule(_localctx, 172, RULE_tff_atom_typing_list);
		try {
			setState(1033);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,60,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1028);
				tff_atom_typing();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1029);
				tff_atom_typing();
				setState(1030);
				match(T__1);
				setState(1031);
				tff_atom_typing_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_let_defnsContext extends ParserRuleContext {
		public Txf_let_defnContext txf_let_defn() {
			return getRuleContext(Txf_let_defnContext.class,0);
		}
		public Txf_let_defn_listContext txf_let_defn_list() {
			return getRuleContext(Txf_let_defn_listContext.class,0);
		}
		public Txf_let_defnsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_let_defns; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_let_defns(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_let_defns(this);
		}
	}

	public final Txf_let_defnsContext txf_let_defns() throws RecognitionException {
		Txf_let_defnsContext _localctx = new Txf_let_defnsContext(_ctx, getState());
		enterRule(_localctx, 174, RULE_txf_let_defns);
		try {
			setState(1040);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,61,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1035);
				txf_let_defn();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1036);
				match(T__10);
				setState(1037);
				txf_let_defn_list();
				setState(1038);
				match(T__11);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_let_defnContext extends ParserRuleContext {
		public Txf_let_LHSContext txf_let_LHS() {
			return getRuleContext(Txf_let_LHSContext.class,0);
		}
		public TerminalNode Assignment() { return getToken(tptp_v7_0_0_0Parser.Assignment, 0); }
		public Tff_termContext tff_term() {
			return getRuleContext(Tff_termContext.class,0);
		}
		public Txf_let_defnContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_let_defn; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_let_defn(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_let_defn(this);
		}
	}

	public final Txf_let_defnContext txf_let_defn() throws RecognitionException {
		Txf_let_defnContext _localctx = new Txf_let_defnContext(_ctx, getState());
		enterRule(_localctx, 176, RULE_txf_let_defn);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1042);
			txf_let_LHS();
			setState(1043);
			match(Assignment);
			setState(1044);
			tff_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_let_LHSContext extends ParserRuleContext {
		public Tff_plain_atomicContext tff_plain_atomic() {
			return getRuleContext(Tff_plain_atomicContext.class,0);
		}
		public Txf_tupleContext txf_tuple() {
			return getRuleContext(Txf_tupleContext.class,0);
		}
		public Txf_let_LHSContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_let_LHS; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_let_LHS(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_let_LHS(this);
		}
	}

	public final Txf_let_LHSContext txf_let_LHS() throws RecognitionException {
		Txf_let_LHSContext _localctx = new Txf_let_LHSContext(_ctx, getState());
		enterRule(_localctx, 178, RULE_txf_let_LHS);
		try {
			setState(1048);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(1046);
				tff_plain_atomic();
				}
				break;
			case T__10:
			case T__14:
				enterOuterAlt(_localctx, 2);
				{
				setState(1047);
				txf_tuple();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_let_defn_listContext extends ParserRuleContext {
		public Txf_let_defnContext txf_let_defn() {
			return getRuleContext(Txf_let_defnContext.class,0);
		}
		public Txf_let_defn_listContext txf_let_defn_list() {
			return getRuleContext(Txf_let_defn_listContext.class,0);
		}
		public Txf_let_defn_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_let_defn_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_let_defn_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_let_defn_list(this);
		}
	}

	public final Txf_let_defn_listContext txf_let_defn_list() throws RecognitionException {
		Txf_let_defn_listContext _localctx = new Txf_let_defn_listContext(_ctx, getState());
		enterRule(_localctx, 180, RULE_txf_let_defn_list);
		try {
			setState(1055);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,63,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1050);
				txf_let_defn();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1051);
				txf_let_defn();
				setState(1052);
				match(T__1);
				setState(1053);
				txf_let_defn_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_ntf_atomContext extends ParserRuleContext {
		public Ntf_connectiveContext ntf_connective() {
			return getRuleContext(Ntf_connectiveContext.class,0);
		}
		public TerminalNode App() { return getToken(tptp_v7_0_0_0Parser.App, 0); }
		public Tff_argumentsContext tff_arguments() {
			return getRuleContext(Tff_argumentsContext.class,0);
		}
		public Txf_ntf_atomContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_ntf_atom; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_ntf_atom(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_ntf_atom(this);
		}
	}

	public final Txf_ntf_atomContext txf_ntf_atom() throws RecognitionException {
		Txf_ntf_atomContext _localctx = new Txf_ntf_atomContext(_ctx, getState());
		enterRule(_localctx, 182, RULE_txf_ntf_atom);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1057);
			ntf_connective();
			setState(1058);
			match(App);
			setState(1059);
			match(T__8);
			setState(1060);
			tff_arguments();
			setState(1061);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_termContext extends ParserRuleContext {
		public Tff_logic_formulaContext tff_logic_formula() {
			return getRuleContext(Tff_logic_formulaContext.class,0);
		}
		public Defined_termContext defined_term() {
			return getRuleContext(Defined_termContext.class,0);
		}
		public Txf_tupleContext txf_tuple() {
			return getRuleContext(Txf_tupleContext.class,0);
		}
		public Ntf_key_pairContext ntf_key_pair() {
			return getRuleContext(Ntf_key_pairContext.class,0);
		}
		public Tff_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_term(this);
		}
	}

	public final Tff_termContext tff_term() throws RecognitionException {
		Tff_termContext _localctx = new Tff_termContext(_ctx, getState());
		enterRule(_localctx, 184, RULE_tff_term);
		try {
			setState(1067);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,64,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1063);
				tff_logic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1064);
				defined_term();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1065);
				txf_tuple();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1066);
				ntf_key_pair();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_unitary_termContext extends ParserRuleContext {
		public Tff_atomic_formulaContext tff_atomic_formula() {
			return getRuleContext(Tff_atomic_formulaContext.class,0);
		}
		public Defined_termContext defined_term() {
			return getRuleContext(Defined_termContext.class,0);
		}
		public Txf_tupleContext txf_tuple() {
			return getRuleContext(Txf_tupleContext.class,0);
		}
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Tff_logic_formulaContext tff_logic_formula() {
			return getRuleContext(Tff_logic_formulaContext.class,0);
		}
		public Tff_unitary_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_unitary_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_unitary_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_unitary_term(this);
		}
	}

	public final Tff_unitary_termContext tff_unitary_term() throws RecognitionException {
		Tff_unitary_termContext _localctx = new Tff_unitary_termContext(_ctx, getState());
		enterRule(_localctx, 186, RULE_tff_unitary_term);
		try {
			setState(1077);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,65,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1069);
				tff_atomic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1070);
				defined_term();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1071);
				txf_tuple();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1072);
				variable();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(1073);
				match(T__8);
				setState(1074);
				tff_logic_formula();
				setState(1075);
				match(T__9);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_tupleContext extends ParserRuleContext {
		public Tff_argumentsContext tff_arguments() {
			return getRuleContext(Tff_argumentsContext.class,0);
		}
		public Txf_tupleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_tuple; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_tuple(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_tuple(this);
		}
	}

	public final Txf_tupleContext txf_tuple() throws RecognitionException {
		Txf_tupleContext _localctx = new Txf_tupleContext(_ctx, getState());
		enterRule(_localctx, 188, RULE_txf_tuple);
		try {
			setState(1084);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__14:
				enterOuterAlt(_localctx, 1);
				{
				setState(1079);
				match(T__14);
				}
				break;
			case T__10:
				enterOuterAlt(_localctx, 2);
				{
				setState(1080);
				match(T__10);
				setState(1081);
				tff_arguments();
				setState(1082);
				match(T__11);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_argumentsContext extends ParserRuleContext {
		public Tff_termContext tff_term() {
			return getRuleContext(Tff_termContext.class,0);
		}
		public Tff_argumentsContext tff_arguments() {
			return getRuleContext(Tff_argumentsContext.class,0);
		}
		public Tff_argumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_arguments; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_arguments(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_arguments(this);
		}
	}

	public final Tff_argumentsContext tff_arguments() throws RecognitionException {
		Tff_argumentsContext _localctx = new Tff_argumentsContext(_ctx, getState());
		enterRule(_localctx, 190, RULE_tff_arguments);
		try {
			setState(1091);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,67,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1086);
				tff_term();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1087);
				tff_term();
				setState(1088);
				match(T__1);
				setState(1089);
				tff_arguments();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_atom_typingContext extends ParserRuleContext {
		public Untyped_atomContext untyped_atom() {
			return getRuleContext(Untyped_atomContext.class,0);
		}
		public Tff_top_level_typeContext tff_top_level_type() {
			return getRuleContext(Tff_top_level_typeContext.class,0);
		}
		public Tff_atom_typingContext tff_atom_typing() {
			return getRuleContext(Tff_atom_typingContext.class,0);
		}
		public Tff_atom_typingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_atom_typing; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_atom_typing(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_atom_typing(this);
		}
	}

	public final Tff_atom_typingContext tff_atom_typing() throws RecognitionException {
		Tff_atom_typingContext _localctx = new Tff_atom_typingContext(_ctx, getState());
		enterRule(_localctx, 192, RULE_tff_atom_typing);
		try {
			setState(1101);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Dollar_dollar_word:
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(1093);
				untyped_atom();
				setState(1094);
				match(T__12);
				setState(1095);
				tff_top_level_type();
				}
				break;
			case T__8:
				enterOuterAlt(_localctx, 2);
				{
				setState(1097);
				match(T__8);
				setState(1098);
				tff_atom_typing();
				setState(1099);
				match(T__9);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_top_level_typeContext extends ParserRuleContext {
		public Tff_atomic_typeContext tff_atomic_type() {
			return getRuleContext(Tff_atomic_typeContext.class,0);
		}
		public Tff_non_atomic_typeContext tff_non_atomic_type() {
			return getRuleContext(Tff_non_atomic_typeContext.class,0);
		}
		public Tff_top_level_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_top_level_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_top_level_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_top_level_type(this);
		}
	}

	public final Tff_top_level_typeContext tff_top_level_type() throws RecognitionException {
		Tff_top_level_typeContext _localctx = new Tff_top_level_typeContext(_ctx, getState());
		enterRule(_localctx, 194, RULE_tff_top_level_type);
		try {
			setState(1105);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,69,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1103);
				tff_atomic_type();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1104);
				tff_non_atomic_type();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_non_atomic_typeContext extends ParserRuleContext {
		public Tff_mapping_typeContext tff_mapping_type() {
			return getRuleContext(Tff_mapping_typeContext.class,0);
		}
		public Tff_non_atomic_typeContext tff_non_atomic_type() {
			return getRuleContext(Tff_non_atomic_typeContext.class,0);
		}
		public Tff_non_atomic_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_non_atomic_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_non_atomic_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_non_atomic_type(this);
		}
	}

	public final Tff_non_atomic_typeContext tff_non_atomic_type() throws RecognitionException {
		Tff_non_atomic_typeContext _localctx = new Tff_non_atomic_typeContext(_ctx, getState());
		enterRule(_localctx, 196, RULE_tff_non_atomic_type);
		try {
			setState(1113);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,70,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1107);
				tff_mapping_type();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1109);
				match(T__8);
				setState(1110);
				tff_non_atomic_type();
				setState(1111);
				match(T__9);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tf1_quantified_typeContext extends ParserRuleContext {
		public TerminalNode TyForall() { return getToken(tptp_v7_0_0_0Parser.TyForall, 0); }
		public Tff_variable_listContext tff_variable_list() {
			return getRuleContext(Tff_variable_listContext.class,0);
		}
		public Tff_monotypeContext tff_monotype() {
			return getRuleContext(Tff_monotypeContext.class,0);
		}
		public Tf1_quantified_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tf1_quantified_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTf1_quantified_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTf1_quantified_type(this);
		}
	}

	public final Tf1_quantified_typeContext tf1_quantified_type() throws RecognitionException {
		Tf1_quantified_typeContext _localctx = new Tf1_quantified_typeContext(_ctx, getState());
		enterRule(_localctx, 198, RULE_tf1_quantified_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1115);
			match(TyForall);
			setState(1116);
			match(T__10);
			setState(1117);
			tff_variable_list();
			setState(1118);
			match(T__11);
			setState(1119);
			match(T__12);
			setState(1120);
			tff_monotype();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_monotypeContext extends ParserRuleContext {
		public Tff_atomic_typeContext tff_atomic_type() {
			return getRuleContext(Tff_atomic_typeContext.class,0);
		}
		public Tff_mapping_typeContext tff_mapping_type() {
			return getRuleContext(Tff_mapping_typeContext.class,0);
		}
		public Tf1_quantified_typeContext tf1_quantified_type() {
			return getRuleContext(Tf1_quantified_typeContext.class,0);
		}
		public Tff_monotypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_monotype; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_monotype(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_monotype(this);
		}
	}

	public final Tff_monotypeContext tff_monotype() throws RecognitionException {
		Tff_monotypeContext _localctx = new Tff_monotypeContext(_ctx, getState());
		enterRule(_localctx, 200, RULE_tff_monotype);
		try {
			setState(1128);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,71,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1122);
				tff_atomic_type();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1123);
				match(T__8);
				setState(1124);
				tff_mapping_type();
				setState(1125);
				match(T__9);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1127);
				tf1_quantified_type();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_unitary_typeContext extends ParserRuleContext {
		public Tff_atomic_typeContext tff_atomic_type() {
			return getRuleContext(Tff_atomic_typeContext.class,0);
		}
		public Tff_xprod_typeContext tff_xprod_type() {
			return getRuleContext(Tff_xprod_typeContext.class,0);
		}
		public Tff_unitary_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_unitary_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_unitary_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_unitary_type(this);
		}
	}

	public final Tff_unitary_typeContext tff_unitary_type() throws RecognitionException {
		Tff_unitary_typeContext _localctx = new Tff_unitary_typeContext(_ctx, getState());
		enterRule(_localctx, 202, RULE_tff_unitary_type);
		try {
			setState(1135);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,72,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1130);
				tff_atomic_type();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1131);
				match(T__8);
				setState(1132);
				tff_xprod_type(0);
				setState(1133);
				match(T__9);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_atomic_typeContext extends ParserRuleContext {
		public Type_constantContext type_constant() {
			return getRuleContext(Type_constantContext.class,0);
		}
		public Defined_typeContext defined_type() {
			return getRuleContext(Defined_typeContext.class,0);
		}
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Type_functorContext type_functor() {
			return getRuleContext(Type_functorContext.class,0);
		}
		public Tff_type_argumentsContext tff_type_arguments() {
			return getRuleContext(Tff_type_argumentsContext.class,0);
		}
		public Tff_atomic_typeContext tff_atomic_type() {
			return getRuleContext(Tff_atomic_typeContext.class,0);
		}
		public Txf_tuple_typeContext txf_tuple_type() {
			return getRuleContext(Txf_tuple_typeContext.class,0);
		}
		public Tff_atomic_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_atomic_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_atomic_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_atomic_type(this);
		}
	}

	public final Tff_atomic_typeContext tff_atomic_type() throws RecognitionException {
		Tff_atomic_typeContext _localctx = new Tff_atomic_typeContext(_ctx, getState());
		enterRule(_localctx, 204, RULE_tff_atomic_type);
		try {
			setState(1150);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,73,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1137);
				type_constant();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1138);
				defined_type();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1139);
				variable();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1140);
				type_functor();
				setState(1141);
				match(T__8);
				setState(1142);
				tff_type_arguments();
				setState(1143);
				match(T__9);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(1145);
				match(T__8);
				setState(1146);
				tff_atomic_type();
				setState(1147);
				match(T__9);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(1149);
				txf_tuple_type();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_type_argumentsContext extends ParserRuleContext {
		public Tff_atomic_typeContext tff_atomic_type() {
			return getRuleContext(Tff_atomic_typeContext.class,0);
		}
		public Tff_type_argumentsContext tff_type_arguments() {
			return getRuleContext(Tff_type_argumentsContext.class,0);
		}
		public Tff_type_argumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_type_arguments; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_type_arguments(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_type_arguments(this);
		}
	}

	public final Tff_type_argumentsContext tff_type_arguments() throws RecognitionException {
		Tff_type_argumentsContext _localctx = new Tff_type_argumentsContext(_ctx, getState());
		enterRule(_localctx, 206, RULE_tff_type_arguments);
		try {
			setState(1157);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,74,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1152);
				tff_atomic_type();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1153);
				tff_atomic_type();
				setState(1154);
				match(T__1);
				setState(1155);
				tff_type_arguments();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_mapping_typeContext extends ParserRuleContext {
		public Tff_unitary_typeContext tff_unitary_type() {
			return getRuleContext(Tff_unitary_typeContext.class,0);
		}
		public TerminalNode Arrow() { return getToken(tptp_v7_0_0_0Parser.Arrow, 0); }
		public Tff_atomic_typeContext tff_atomic_type() {
			return getRuleContext(Tff_atomic_typeContext.class,0);
		}
		public Tff_mapping_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_mapping_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_mapping_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_mapping_type(this);
		}
	}

	public final Tff_mapping_typeContext tff_mapping_type() throws RecognitionException {
		Tff_mapping_typeContext _localctx = new Tff_mapping_typeContext(_ctx, getState());
		enterRule(_localctx, 208, RULE_tff_mapping_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1159);
			tff_unitary_type();
			setState(1160);
			match(Arrow);
			setState(1161);
			tff_atomic_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_xprod_typeContext extends ParserRuleContext {
		public Tff_unitary_typeContext tff_unitary_type() {
			return getRuleContext(Tff_unitary_typeContext.class,0);
		}
		public TerminalNode Star() { return getToken(tptp_v7_0_0_0Parser.Star, 0); }
		public Tff_atomic_typeContext tff_atomic_type() {
			return getRuleContext(Tff_atomic_typeContext.class,0);
		}
		public Tff_xprod_typeContext tff_xprod_type() {
			return getRuleContext(Tff_xprod_typeContext.class,0);
		}
		public Tff_xprod_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_xprod_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_xprod_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_xprod_type(this);
		}
	}

	public final Tff_xprod_typeContext tff_xprod_type() throws RecognitionException {
		return tff_xprod_type(0);
	}

	private Tff_xprod_typeContext tff_xprod_type(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Tff_xprod_typeContext _localctx = new Tff_xprod_typeContext(_ctx, _parentState);
		Tff_xprod_typeContext _prevctx = _localctx;
		int _startState = 210;
		enterRecursionRule(_localctx, 210, RULE_tff_xprod_type, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(1164);
			tff_unitary_type();
			setState(1165);
			match(Star);
			setState(1166);
			tff_atomic_type();
			}
			_ctx.stop = _input.LT(-1);
			setState(1173);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,75,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Tff_xprod_typeContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_tff_xprod_type);
					setState(1168);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(1169);
					match(Star);
					setState(1170);
					tff_atomic_type();
					}
					} 
				}
				setState(1175);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,75,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Txf_tuple_typeContext extends ParserRuleContext {
		public Tff_type_listContext tff_type_list() {
			return getRuleContext(Tff_type_listContext.class,0);
		}
		public Txf_tuple_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_tuple_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_tuple_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_tuple_type(this);
		}
	}

	public final Txf_tuple_typeContext txf_tuple_type() throws RecognitionException {
		Txf_tuple_typeContext _localctx = new Txf_tuple_typeContext(_ctx, getState());
		enterRule(_localctx, 212, RULE_txf_tuple_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1176);
			match(T__10);
			setState(1177);
			tff_type_list();
			setState(1178);
			match(T__11);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_type_listContext extends ParserRuleContext {
		public Tff_top_level_typeContext tff_top_level_type() {
			return getRuleContext(Tff_top_level_typeContext.class,0);
		}
		public Tff_type_listContext tff_type_list() {
			return getRuleContext(Tff_type_listContext.class,0);
		}
		public Tff_type_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_type_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_type_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_type_list(this);
		}
	}

	public final Tff_type_listContext tff_type_list() throws RecognitionException {
		Tff_type_listContext _localctx = new Tff_type_listContext(_ctx, getState());
		enterRule(_localctx, 214, RULE_tff_type_list);
		try {
			setState(1185);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,76,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1180);
				tff_top_level_type();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1181);
				tff_top_level_type();
				setState(1182);
				match(T__1);
				setState(1183);
				tff_type_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tff_subtypeContext extends ParserRuleContext {
		public Untyped_atomContext untyped_atom() {
			return getRuleContext(Untyped_atomContext.class,0);
		}
		public TerminalNode Subtype_sign() { return getToken(tptp_v7_0_0_0Parser.Subtype_sign, 0); }
		public AtomContext atom() {
			return getRuleContext(AtomContext.class,0);
		}
		public Tff_subtypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tff_subtype; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTff_subtype(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTff_subtype(this);
		}
	}

	public final Tff_subtypeContext tff_subtype() throws RecognitionException {
		Tff_subtypeContext _localctx = new Tff_subtypeContext(_ctx, getState());
		enterRule(_localctx, 216, RULE_tff_subtype);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1187);
			untyped_atom();
			setState(1188);
			match(Subtype_sign);
			setState(1189);
			atom();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_definitionContext extends ParserRuleContext {
		public Tff_atomic_formulaContext tff_atomic_formula() {
			return getRuleContext(Tff_atomic_formulaContext.class,0);
		}
		public TerminalNode Identical() { return getToken(tptp_v7_0_0_0Parser.Identical, 0); }
		public Tff_termContext tff_term() {
			return getRuleContext(Tff_termContext.class,0);
		}
		public Txf_definitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_definition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_definition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_definition(this);
		}
	}

	public final Txf_definitionContext txf_definition() throws RecognitionException {
		Txf_definitionContext _localctx = new Txf_definitionContext(_ctx, getState());
		enterRule(_localctx, 218, RULE_txf_definition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1191);
			tff_atomic_formula();
			setState(1192);
			match(Identical);
			setState(1193);
			tff_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Txf_sequentContext extends ParserRuleContext {
		public List<Txf_tupleContext> txf_tuple() {
			return getRuleContexts(Txf_tupleContext.class);
		}
		public Txf_tupleContext txf_tuple(int i) {
			return getRuleContext(Txf_tupleContext.class,i);
		}
		public TerminalNode Gentzen_arrow() { return getToken(tptp_v7_0_0_0Parser.Gentzen_arrow, 0); }
		public Txf_sequentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_txf_sequent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTxf_sequent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTxf_sequent(this);
		}
	}

	public final Txf_sequentContext txf_sequent() throws RecognitionException {
		Txf_sequentContext _localctx = new Txf_sequentContext(_ctx, getState());
		enterRule(_localctx, 220, RULE_txf_sequent);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1195);
			txf_tuple();
			setState(1196);
			match(Gentzen_arrow);
			setState(1197);
			txf_tuple();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Ntf_connectiveContext extends ParserRuleContext {
		public Ntf_short_connectiveContext ntf_short_connective() {
			return getRuleContext(Ntf_short_connectiveContext.class,0);
		}
		public Ntf_long_connectiveContext ntf_long_connective() {
			return getRuleContext(Ntf_long_connectiveContext.class,0);
		}
		public Ntf_connectiveContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ntf_connective; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNtf_connective(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNtf_connective(this);
		}
	}

	public final Ntf_connectiveContext ntf_connective() throws RecognitionException {
		Ntf_connectiveContext _localctx = new Ntf_connectiveContext(_ctx, getState());
		enterRule(_localctx, 222, RULE_ntf_connective);
		try {
			setState(1201);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,77,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1199);
				ntf_short_connective();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1200);
				ntf_long_connective();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Ntf_short_connectiveContext extends ParserRuleContext {
		public Ntf_indexContext ntf_index() {
			return getRuleContext(Ntf_indexContext.class,0);
		}
		public TerminalNode Arrow() { return getToken(tptp_v7_0_0_0Parser.Arrow, 0); }
		public Ntf_short_connectiveContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ntf_short_connective; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNtf_short_connective(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNtf_short_connective(this);
		}
	}

	public final Ntf_short_connectiveContext ntf_short_connective() throws RecognitionException {
		Ntf_short_connectiveContext _localctx = new Ntf_short_connectiveContext(_ctx, getState());
		enterRule(_localctx, 224, RULE_ntf_short_connective);
		try {
			setState(1218);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__15:
				enterOuterAlt(_localctx, 1);
				{
				setState(1203);
				match(T__15);
				}
				break;
			case T__16:
				enterOuterAlt(_localctx, 2);
				{
				setState(1204);
				match(T__16);
				}
				break;
			case T__17:
				enterOuterAlt(_localctx, 3);
				{
				setState(1205);
				match(T__17);
				}
				break;
			case T__10:
				enterOuterAlt(_localctx, 4);
				{
				setState(1206);
				match(T__10);
				setState(1207);
				ntf_index();
				setState(1208);
				match(T__11);
				}
				break;
			case T__18:
				enterOuterAlt(_localctx, 5);
				{
				setState(1210);
				match(T__18);
				setState(1211);
				ntf_index();
				setState(1212);
				match(Arrow);
				}
				break;
			case T__19:
				enterOuterAlt(_localctx, 6);
				{
				setState(1214);
				match(T__19);
				setState(1215);
				ntf_index();
				setState(1216);
				match(T__20);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Ntf_long_connectiveContext extends ParserRuleContext {
		public Ntf_connective_nameContext ntf_connective_name() {
			return getRuleContext(Ntf_connective_nameContext.class,0);
		}
		public Ntf_parameter_listContext ntf_parameter_list() {
			return getRuleContext(Ntf_parameter_listContext.class,0);
		}
		public Ntf_long_connectiveContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ntf_long_connective; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNtf_long_connective(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNtf_long_connective(this);
		}
	}

	public final Ntf_long_connectiveContext ntf_long_connective() throws RecognitionException {
		Ntf_long_connectiveContext _localctx = new Ntf_long_connectiveContext(_ctx, getState());
		enterRule(_localctx, 226, RULE_ntf_long_connective);
		try {
			setState(1230);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,79,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1220);
				match(T__19);
				setState(1221);
				ntf_connective_name();
				setState(1222);
				match(T__20);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1224);
				match(T__19);
				setState(1225);
				ntf_connective_name();
				setState(1226);
				match(T__8);
				setState(1227);
				ntf_parameter_list();
				setState(1228);
				match(T__21);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Ntf_connective_nameContext extends ParserRuleContext {
		public Def_or_sys_constantContext def_or_sys_constant() {
			return getRuleContext(Def_or_sys_constantContext.class,0);
		}
		public Ntf_connective_nameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ntf_connective_name; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNtf_connective_name(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNtf_connective_name(this);
		}
	}

	public final Ntf_connective_nameContext ntf_connective_name() throws RecognitionException {
		Ntf_connective_nameContext _localctx = new Ntf_connective_nameContext(_ctx, getState());
		enterRule(_localctx, 228, RULE_ntf_connective_name);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1232);
			def_or_sys_constant();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Ntf_parameter_listContext extends ParserRuleContext {
		public Ntf_parameterContext ntf_parameter() {
			return getRuleContext(Ntf_parameterContext.class,0);
		}
		public Ntf_parameter_listContext ntf_parameter_list() {
			return getRuleContext(Ntf_parameter_listContext.class,0);
		}
		public Ntf_parameter_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ntf_parameter_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNtf_parameter_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNtf_parameter_list(this);
		}
	}

	public final Ntf_parameter_listContext ntf_parameter_list() throws RecognitionException {
		Ntf_parameter_listContext _localctx = new Ntf_parameter_listContext(_ctx, getState());
		enterRule(_localctx, 230, RULE_ntf_parameter_list);
		try {
			setState(1239);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,80,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1234);
				ntf_parameter();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1235);
				ntf_parameter();
				setState(1236);
				match(T__1);
				setState(1237);
				ntf_parameter_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Ntf_parameterContext extends ParserRuleContext {
		public Ntf_indexContext ntf_index() {
			return getRuleContext(Ntf_indexContext.class,0);
		}
		public Ntf_key_pairContext ntf_key_pair() {
			return getRuleContext(Ntf_key_pairContext.class,0);
		}
		public Ntf_parameterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ntf_parameter; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNtf_parameter(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNtf_parameter(this);
		}
	}

	public final Ntf_parameterContext ntf_parameter() throws RecognitionException {
		Ntf_parameterContext _localctx = new Ntf_parameterContext(_ctx, getState());
		enterRule(_localctx, 232, RULE_ntf_parameter);
		try {
			setState(1243);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Hash:
				enterOuterAlt(_localctx, 1);
				{
				setState(1241);
				ntf_index();
				}
				break;
			case Dollar_word:
			case Dollar_dollar_word:
				enterOuterAlt(_localctx, 2);
				{
				setState(1242);
				ntf_key_pair();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Ntf_indexContext extends ParserRuleContext {
		public TerminalNode Hash() { return getToken(tptp_v7_0_0_0Parser.Hash, 0); }
		public Tff_unitary_termContext tff_unitary_term() {
			return getRuleContext(Tff_unitary_termContext.class,0);
		}
		public Ntf_indexContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ntf_index; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNtf_index(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNtf_index(this);
		}
	}

	public final Ntf_indexContext ntf_index() throws RecognitionException {
		Ntf_indexContext _localctx = new Ntf_indexContext(_ctx, getState());
		enterRule(_localctx, 234, RULE_ntf_index);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1245);
			match(Hash);
			setState(1246);
			tff_unitary_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Ntf_key_pairContext extends ParserRuleContext {
		public Def_or_sys_constantContext def_or_sys_constant() {
			return getRuleContext(Def_or_sys_constantContext.class,0);
		}
		public TerminalNode Assignment() { return getToken(tptp_v7_0_0_0Parser.Assignment, 0); }
		public Tff_unitary_termContext tff_unitary_term() {
			return getRuleContext(Tff_unitary_termContext.class,0);
		}
		public Ntf_key_pairContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ntf_key_pair; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNtf_key_pair(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNtf_key_pair(this);
		}
	}

	public final Ntf_key_pairContext ntf_key_pair() throws RecognitionException {
		Ntf_key_pairContext _localctx = new Ntf_key_pairContext(_ctx, getState());
		enterRule(_localctx, 236, RULE_ntf_key_pair);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1248);
			def_or_sys_constant();
			setState(1249);
			match(Assignment);
			setState(1250);
			tff_unitary_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Logic_defn_ruleContext extends ParserRuleContext {
		public Logic_defn_LHSContext logic_defn_LHS() {
			return getRuleContext(Logic_defn_LHSContext.class,0);
		}
		public TerminalNode Identical() { return getToken(tptp_v7_0_0_0Parser.Identical, 0); }
		public Logic_defn_RHSContext logic_defn_RHS() {
			return getRuleContext(Logic_defn_RHSContext.class,0);
		}
		public Logic_defn_ruleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logic_defn_rule; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterLogic_defn_rule(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitLogic_defn_rule(this);
		}
	}

	public final Logic_defn_ruleContext logic_defn_rule() throws RecognitionException {
		Logic_defn_ruleContext _localctx = new Logic_defn_ruleContext(_ctx, getState());
		enterRule(_localctx, 238, RULE_logic_defn_rule);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1252);
			logic_defn_LHS();
			setState(1253);
			match(Identical);
			setState(1254);
			logic_defn_RHS();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Logic_defn_LHSContext extends ParserRuleContext {
		public Defined_constantContext defined_constant() {
			return getRuleContext(Defined_constantContext.class,0);
		}
		public Logic_defn_LHSContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logic_defn_LHS; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterLogic_defn_LHS(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitLogic_defn_LHS(this);
		}
	}

	public final Logic_defn_LHSContext logic_defn_LHS() throws RecognitionException {
		Logic_defn_LHSContext _localctx = new Logic_defn_LHSContext(_ctx, getState());
		enterRule(_localctx, 240, RULE_logic_defn_LHS);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1256);
			defined_constant();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Logic_defn_RHSContext extends ParserRuleContext {
		public Defined_constantContext defined_constant() {
			return getRuleContext(Defined_constantContext.class,0);
		}
		public Txf_tupleContext txf_tuple() {
			return getRuleContext(Txf_tupleContext.class,0);
		}
		public Logic_defn_RHSContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logic_defn_RHS; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterLogic_defn_RHS(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitLogic_defn_RHS(this);
		}
	}

	public final Logic_defn_RHSContext logic_defn_RHS() throws RecognitionException {
		Logic_defn_RHSContext _localctx = new Logic_defn_RHSContext(_ctx, getState());
		enterRule(_localctx, 242, RULE_logic_defn_RHS);
		try {
			setState(1260);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Dollar_word:
				enterOuterAlt(_localctx, 1);
				{
				setState(1258);
				defined_constant();
				}
				break;
			case T__10:
			case T__14:
				enterOuterAlt(_localctx, 2);
				{
				setState(1259);
				txf_tuple();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tcf_formulaContext extends ParserRuleContext {
		public Tcf_logic_formulaContext tcf_logic_formula() {
			return getRuleContext(Tcf_logic_formulaContext.class,0);
		}
		public Tff_atom_typingContext tff_atom_typing() {
			return getRuleContext(Tff_atom_typingContext.class,0);
		}
		public Tcf_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tcf_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTcf_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTcf_formula(this);
		}
	}

	public final Tcf_formulaContext tcf_formula() throws RecognitionException {
		Tcf_formulaContext _localctx = new Tcf_formulaContext(_ctx, getState());
		enterRule(_localctx, 244, RULE_tcf_formula);
		try {
			setState(1264);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,83,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1262);
				tcf_logic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1263);
				tff_atom_typing();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tcf_logic_formulaContext extends ParserRuleContext {
		public Tcf_quantified_formulaContext tcf_quantified_formula() {
			return getRuleContext(Tcf_quantified_formulaContext.class,0);
		}
		public Cnf_formulaContext cnf_formula() {
			return getRuleContext(Cnf_formulaContext.class,0);
		}
		public Tcf_logic_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tcf_logic_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTcf_logic_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTcf_logic_formula(this);
		}
	}

	public final Tcf_logic_formulaContext tcf_logic_formula() throws RecognitionException {
		Tcf_logic_formulaContext _localctx = new Tcf_logic_formulaContext(_ctx, getState());
		enterRule(_localctx, 246, RULE_tcf_logic_formula);
		try {
			setState(1268);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Forall:
				enterOuterAlt(_localctx, 1);
				{
				setState(1266);
				tcf_quantified_formula();
				}
				break;
			case T__8:
			case Not:
			case Real:
			case Rational:
			case Integer:
			case Dollar_word:
			case Dollar_dollar_word:
			case Upper_word:
			case Lower_word:
			case Single_quoted:
			case Distinct_object:
				enterOuterAlt(_localctx, 2);
				{
				setState(1267);
				cnf_formula();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tcf_quantified_formulaContext extends ParserRuleContext {
		public TerminalNode Forall() { return getToken(tptp_v7_0_0_0Parser.Forall, 0); }
		public Tff_variable_listContext tff_variable_list() {
			return getRuleContext(Tff_variable_listContext.class,0);
		}
		public Tcf_logic_formulaContext tcf_logic_formula() {
			return getRuleContext(Tcf_logic_formulaContext.class,0);
		}
		public Tcf_quantified_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tcf_quantified_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTcf_quantified_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTcf_quantified_formula(this);
		}
	}

	public final Tcf_quantified_formulaContext tcf_quantified_formula() throws RecognitionException {
		Tcf_quantified_formulaContext _localctx = new Tcf_quantified_formulaContext(_ctx, getState());
		enterRule(_localctx, 248, RULE_tcf_quantified_formula);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1270);
			match(Forall);
			setState(1271);
			match(T__10);
			setState(1272);
			tff_variable_list();
			setState(1273);
			match(T__11);
			setState(1274);
			match(T__12);
			setState(1275);
			tcf_logic_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_formulaContext extends ParserRuleContext {
		public Fof_logic_formulaContext fof_logic_formula() {
			return getRuleContext(Fof_logic_formulaContext.class,0);
		}
		public Fof_sequentContext fof_sequent() {
			return getRuleContext(Fof_sequentContext.class,0);
		}
		public Fof_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_formula(this);
		}
	}

	public final Fof_formulaContext fof_formula() throws RecognitionException {
		Fof_formulaContext _localctx = new Fof_formulaContext(_ctx, getState());
		enterRule(_localctx, 250, RULE_fof_formula);
		try {
			setState(1279);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,85,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1277);
				fof_logic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1278);
				fof_sequent();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_logic_formulaContext extends ParserRuleContext {
		public Fof_binary_formulaContext fof_binary_formula() {
			return getRuleContext(Fof_binary_formulaContext.class,0);
		}
		public Fof_unary_formulaContext fof_unary_formula() {
			return getRuleContext(Fof_unary_formulaContext.class,0);
		}
		public Fof_unitary_formulaContext fof_unitary_formula() {
			return getRuleContext(Fof_unitary_formulaContext.class,0);
		}
		public Fof_logic_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_logic_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_logic_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_logic_formula(this);
		}
	}

	public final Fof_logic_formulaContext fof_logic_formula() throws RecognitionException {
		Fof_logic_formulaContext _localctx = new Fof_logic_formulaContext(_ctx, getState());
		enterRule(_localctx, 252, RULE_fof_logic_formula);
		try {
			setState(1284);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,86,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1281);
				fof_binary_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1282);
				fof_unary_formula();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1283);
				fof_unitary_formula();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_binary_formulaContext extends ParserRuleContext {
		public Fof_binary_nonassocContext fof_binary_nonassoc() {
			return getRuleContext(Fof_binary_nonassocContext.class,0);
		}
		public Fof_binary_assocContext fof_binary_assoc() {
			return getRuleContext(Fof_binary_assocContext.class,0);
		}
		public Fof_binary_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_binary_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_binary_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_binary_formula(this);
		}
	}

	public final Fof_binary_formulaContext fof_binary_formula() throws RecognitionException {
		Fof_binary_formulaContext _localctx = new Fof_binary_formulaContext(_ctx, getState());
		enterRule(_localctx, 254, RULE_fof_binary_formula);
		try {
			setState(1288);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,87,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1286);
				fof_binary_nonassoc();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1287);
				fof_binary_assoc();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_binary_nonassocContext extends ParserRuleContext {
		public List<Fof_unit_formulaContext> fof_unit_formula() {
			return getRuleContexts(Fof_unit_formulaContext.class);
		}
		public Fof_unit_formulaContext fof_unit_formula(int i) {
			return getRuleContext(Fof_unit_formulaContext.class,i);
		}
		public Nonassoc_connectiveContext nonassoc_connective() {
			return getRuleContext(Nonassoc_connectiveContext.class,0);
		}
		public Fof_binary_nonassocContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_binary_nonassoc; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_binary_nonassoc(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_binary_nonassoc(this);
		}
	}

	public final Fof_binary_nonassocContext fof_binary_nonassoc() throws RecognitionException {
		Fof_binary_nonassocContext _localctx = new Fof_binary_nonassocContext(_ctx, getState());
		enterRule(_localctx, 256, RULE_fof_binary_nonassoc);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1290);
			fof_unit_formula();
			setState(1291);
			nonassoc_connective();
			setState(1292);
			fof_unit_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_binary_assocContext extends ParserRuleContext {
		public Fof_or_formulaContext fof_or_formula() {
			return getRuleContext(Fof_or_formulaContext.class,0);
		}
		public Fof_and_formulaContext fof_and_formula() {
			return getRuleContext(Fof_and_formulaContext.class,0);
		}
		public Fof_binary_assocContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_binary_assoc; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_binary_assoc(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_binary_assoc(this);
		}
	}

	public final Fof_binary_assocContext fof_binary_assoc() throws RecognitionException {
		Fof_binary_assocContext _localctx = new Fof_binary_assocContext(_ctx, getState());
		enterRule(_localctx, 258, RULE_fof_binary_assoc);
		try {
			setState(1296);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,88,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1294);
				fof_or_formula(0);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1295);
				fof_and_formula(0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_or_formulaContext extends ParserRuleContext {
		public List<Fof_unit_formulaContext> fof_unit_formula() {
			return getRuleContexts(Fof_unit_formulaContext.class);
		}
		public Fof_unit_formulaContext fof_unit_formula(int i) {
			return getRuleContext(Fof_unit_formulaContext.class,i);
		}
		public TerminalNode Or() { return getToken(tptp_v7_0_0_0Parser.Or, 0); }
		public Fof_or_formulaContext fof_or_formula() {
			return getRuleContext(Fof_or_formulaContext.class,0);
		}
		public Fof_or_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_or_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_or_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_or_formula(this);
		}
	}

	public final Fof_or_formulaContext fof_or_formula() throws RecognitionException {
		return fof_or_formula(0);
	}

	private Fof_or_formulaContext fof_or_formula(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Fof_or_formulaContext _localctx = new Fof_or_formulaContext(_ctx, _parentState);
		Fof_or_formulaContext _prevctx = _localctx;
		int _startState = 260;
		enterRecursionRule(_localctx, 260, RULE_fof_or_formula, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(1299);
			fof_unit_formula();
			setState(1300);
			match(Or);
			setState(1301);
			fof_unit_formula();
			}
			_ctx.stop = _input.LT(-1);
			setState(1308);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,89,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Fof_or_formulaContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_fof_or_formula);
					setState(1303);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(1304);
					match(Or);
					setState(1305);
					fof_unit_formula();
					}
					} 
				}
				setState(1310);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,89,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Fof_and_formulaContext extends ParserRuleContext {
		public List<Fof_unit_formulaContext> fof_unit_formula() {
			return getRuleContexts(Fof_unit_formulaContext.class);
		}
		public Fof_unit_formulaContext fof_unit_formula(int i) {
			return getRuleContext(Fof_unit_formulaContext.class,i);
		}
		public TerminalNode And() { return getToken(tptp_v7_0_0_0Parser.And, 0); }
		public Fof_and_formulaContext fof_and_formula() {
			return getRuleContext(Fof_and_formulaContext.class,0);
		}
		public Fof_and_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_and_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_and_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_and_formula(this);
		}
	}

	public final Fof_and_formulaContext fof_and_formula() throws RecognitionException {
		return fof_and_formula(0);
	}

	private Fof_and_formulaContext fof_and_formula(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Fof_and_formulaContext _localctx = new Fof_and_formulaContext(_ctx, _parentState);
		Fof_and_formulaContext _prevctx = _localctx;
		int _startState = 262;
		enterRecursionRule(_localctx, 262, RULE_fof_and_formula, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(1312);
			fof_unit_formula();
			setState(1313);
			match(And);
			setState(1314);
			fof_unit_formula();
			}
			_ctx.stop = _input.LT(-1);
			setState(1321);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,90,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Fof_and_formulaContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_fof_and_formula);
					setState(1316);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(1317);
					match(And);
					setState(1318);
					fof_unit_formula();
					}
					} 
				}
				setState(1323);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,90,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Fof_unary_formulaContext extends ParserRuleContext {
		public Unary_connectiveContext unary_connective() {
			return getRuleContext(Unary_connectiveContext.class,0);
		}
		public Fof_unit_formulaContext fof_unit_formula() {
			return getRuleContext(Fof_unit_formulaContext.class,0);
		}
		public Fof_infix_unaryContext fof_infix_unary() {
			return getRuleContext(Fof_infix_unaryContext.class,0);
		}
		public Fof_unary_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_unary_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_unary_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_unary_formula(this);
		}
	}

	public final Fof_unary_formulaContext fof_unary_formula() throws RecognitionException {
		Fof_unary_formulaContext _localctx = new Fof_unary_formulaContext(_ctx, getState());
		enterRule(_localctx, 264, RULE_fof_unary_formula);
		try {
			setState(1328);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Not:
				enterOuterAlt(_localctx, 1);
				{
				setState(1324);
				unary_connective();
				setState(1325);
				fof_unit_formula();
				}
				break;
			case Real:
			case Rational:
			case Integer:
			case Dollar_word:
			case Dollar_dollar_word:
			case Upper_word:
			case Lower_word:
			case Single_quoted:
			case Distinct_object:
				enterOuterAlt(_localctx, 2);
				{
				setState(1327);
				fof_infix_unary();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_infix_unaryContext extends ParserRuleContext {
		public List<Fof_termContext> fof_term() {
			return getRuleContexts(Fof_termContext.class);
		}
		public Fof_termContext fof_term(int i) {
			return getRuleContext(Fof_termContext.class,i);
		}
		public TerminalNode Infix_inequality() { return getToken(tptp_v7_0_0_0Parser.Infix_inequality, 0); }
		public Fof_infix_unaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_infix_unary; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_infix_unary(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_infix_unary(this);
		}
	}

	public final Fof_infix_unaryContext fof_infix_unary() throws RecognitionException {
		Fof_infix_unaryContext _localctx = new Fof_infix_unaryContext(_ctx, getState());
		enterRule(_localctx, 266, RULE_fof_infix_unary);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1330);
			fof_term();
			setState(1331);
			match(Infix_inequality);
			setState(1332);
			fof_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_unit_formulaContext extends ParserRuleContext {
		public Fof_unitary_formulaContext fof_unitary_formula() {
			return getRuleContext(Fof_unitary_formulaContext.class,0);
		}
		public Fof_unary_formulaContext fof_unary_formula() {
			return getRuleContext(Fof_unary_formulaContext.class,0);
		}
		public Fof_unit_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_unit_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_unit_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_unit_formula(this);
		}
	}

	public final Fof_unit_formulaContext fof_unit_formula() throws RecognitionException {
		Fof_unit_formulaContext _localctx = new Fof_unit_formulaContext(_ctx, getState());
		enterRule(_localctx, 268, RULE_fof_unit_formula);
		try {
			setState(1336);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,92,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1334);
				fof_unitary_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1335);
				fof_unary_formula();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_unitary_formulaContext extends ParserRuleContext {
		public Fof_quantified_formulaContext fof_quantified_formula() {
			return getRuleContext(Fof_quantified_formulaContext.class,0);
		}
		public Fof_atomic_formulaContext fof_atomic_formula() {
			return getRuleContext(Fof_atomic_formulaContext.class,0);
		}
		public Fof_logic_formulaContext fof_logic_formula() {
			return getRuleContext(Fof_logic_formulaContext.class,0);
		}
		public Fof_unitary_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_unitary_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_unitary_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_unitary_formula(this);
		}
	}

	public final Fof_unitary_formulaContext fof_unitary_formula() throws RecognitionException {
		Fof_unitary_formulaContext _localctx = new Fof_unitary_formulaContext(_ctx, getState());
		enterRule(_localctx, 270, RULE_fof_unitary_formula);
		try {
			setState(1344);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Forall:
			case Exists:
				enterOuterAlt(_localctx, 1);
				{
				setState(1338);
				fof_quantified_formula();
				}
				break;
			case Real:
			case Rational:
			case Integer:
			case Dollar_word:
			case Dollar_dollar_word:
			case Upper_word:
			case Lower_word:
			case Single_quoted:
			case Distinct_object:
				enterOuterAlt(_localctx, 2);
				{
				setState(1339);
				fof_atomic_formula();
				}
				break;
			case T__8:
				enterOuterAlt(_localctx, 3);
				{
				setState(1340);
				match(T__8);
				setState(1341);
				fof_logic_formula();
				setState(1342);
				match(T__9);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_quantified_formulaContext extends ParserRuleContext {
		public Fof_quantifierContext fof_quantifier() {
			return getRuleContext(Fof_quantifierContext.class,0);
		}
		public Fof_variable_listContext fof_variable_list() {
			return getRuleContext(Fof_variable_listContext.class,0);
		}
		public Fof_unit_formulaContext fof_unit_formula() {
			return getRuleContext(Fof_unit_formulaContext.class,0);
		}
		public Fof_quantified_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_quantified_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_quantified_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_quantified_formula(this);
		}
	}

	public final Fof_quantified_formulaContext fof_quantified_formula() throws RecognitionException {
		Fof_quantified_formulaContext _localctx = new Fof_quantified_formulaContext(_ctx, getState());
		enterRule(_localctx, 272, RULE_fof_quantified_formula);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1346);
			fof_quantifier();
			setState(1347);
			match(T__10);
			setState(1348);
			fof_variable_list();
			setState(1349);
			match(T__11);
			setState(1350);
			match(T__12);
			setState(1351);
			fof_unit_formula();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_variable_listContext extends ParserRuleContext {
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Fof_variable_listContext fof_variable_list() {
			return getRuleContext(Fof_variable_listContext.class,0);
		}
		public Fof_variable_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_variable_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_variable_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_variable_list(this);
		}
	}

	public final Fof_variable_listContext fof_variable_list() throws RecognitionException {
		Fof_variable_listContext _localctx = new Fof_variable_listContext(_ctx, getState());
		enterRule(_localctx, 274, RULE_fof_variable_list);
		try {
			setState(1358);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,94,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1353);
				variable();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1354);
				variable();
				setState(1355);
				match(T__1);
				setState(1356);
				fof_variable_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_atomic_formulaContext extends ParserRuleContext {
		public Fof_plain_atomic_formulaContext fof_plain_atomic_formula() {
			return getRuleContext(Fof_plain_atomic_formulaContext.class,0);
		}
		public Fof_defined_atomic_formulaContext fof_defined_atomic_formula() {
			return getRuleContext(Fof_defined_atomic_formulaContext.class,0);
		}
		public Fof_system_atomic_formulaContext fof_system_atomic_formula() {
			return getRuleContext(Fof_system_atomic_formulaContext.class,0);
		}
		public Fof_atomic_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_atomic_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_atomic_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_atomic_formula(this);
		}
	}

	public final Fof_atomic_formulaContext fof_atomic_formula() throws RecognitionException {
		Fof_atomic_formulaContext _localctx = new Fof_atomic_formulaContext(_ctx, getState());
		enterRule(_localctx, 276, RULE_fof_atomic_formula);
		try {
			setState(1363);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,95,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1360);
				fof_plain_atomic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1361);
				fof_defined_atomic_formula();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1362);
				fof_system_atomic_formula();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_plain_atomic_formulaContext extends ParserRuleContext {
		public Fof_plain_termContext fof_plain_term() {
			return getRuleContext(Fof_plain_termContext.class,0);
		}
		public Fof_plain_atomic_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_plain_atomic_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_plain_atomic_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_plain_atomic_formula(this);
		}
	}

	public final Fof_plain_atomic_formulaContext fof_plain_atomic_formula() throws RecognitionException {
		Fof_plain_atomic_formulaContext _localctx = new Fof_plain_atomic_formulaContext(_ctx, getState());
		enterRule(_localctx, 278, RULE_fof_plain_atomic_formula);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1365);
			fof_plain_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_defined_atomic_formulaContext extends ParserRuleContext {
		public Fof_defined_plain_formulaContext fof_defined_plain_formula() {
			return getRuleContext(Fof_defined_plain_formulaContext.class,0);
		}
		public Fof_defined_infix_formulaContext fof_defined_infix_formula() {
			return getRuleContext(Fof_defined_infix_formulaContext.class,0);
		}
		public Fof_defined_atomic_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_defined_atomic_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_defined_atomic_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_defined_atomic_formula(this);
		}
	}

	public final Fof_defined_atomic_formulaContext fof_defined_atomic_formula() throws RecognitionException {
		Fof_defined_atomic_formulaContext _localctx = new Fof_defined_atomic_formulaContext(_ctx, getState());
		enterRule(_localctx, 280, RULE_fof_defined_atomic_formula);
		try {
			setState(1369);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,96,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1367);
				fof_defined_plain_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1368);
				fof_defined_infix_formula();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_defined_plain_formulaContext extends ParserRuleContext {
		public Fof_defined_plain_termContext fof_defined_plain_term() {
			return getRuleContext(Fof_defined_plain_termContext.class,0);
		}
		public Fof_defined_plain_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_defined_plain_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_defined_plain_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_defined_plain_formula(this);
		}
	}

	public final Fof_defined_plain_formulaContext fof_defined_plain_formula() throws RecognitionException {
		Fof_defined_plain_formulaContext _localctx = new Fof_defined_plain_formulaContext(_ctx, getState());
		enterRule(_localctx, 282, RULE_fof_defined_plain_formula);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1371);
			fof_defined_plain_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_defined_infix_formulaContext extends ParserRuleContext {
		public List<Fof_termContext> fof_term() {
			return getRuleContexts(Fof_termContext.class);
		}
		public Fof_termContext fof_term(int i) {
			return getRuleContext(Fof_termContext.class,i);
		}
		public Defined_infix_predContext defined_infix_pred() {
			return getRuleContext(Defined_infix_predContext.class,0);
		}
		public Fof_defined_infix_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_defined_infix_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_defined_infix_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_defined_infix_formula(this);
		}
	}

	public final Fof_defined_infix_formulaContext fof_defined_infix_formula() throws RecognitionException {
		Fof_defined_infix_formulaContext _localctx = new Fof_defined_infix_formulaContext(_ctx, getState());
		enterRule(_localctx, 284, RULE_fof_defined_infix_formula);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1373);
			fof_term();
			setState(1374);
			defined_infix_pred();
			setState(1375);
			fof_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_system_atomic_formulaContext extends ParserRuleContext {
		public Fof_system_termContext fof_system_term() {
			return getRuleContext(Fof_system_termContext.class,0);
		}
		public Fof_system_atomic_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_system_atomic_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_system_atomic_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_system_atomic_formula(this);
		}
	}

	public final Fof_system_atomic_formulaContext fof_system_atomic_formula() throws RecognitionException {
		Fof_system_atomic_formulaContext _localctx = new Fof_system_atomic_formulaContext(_ctx, getState());
		enterRule(_localctx, 286, RULE_fof_system_atomic_formula);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1377);
			fof_system_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_plain_termContext extends ParserRuleContext {
		public ConstantContext constant() {
			return getRuleContext(ConstantContext.class,0);
		}
		public FunctorContext functor() {
			return getRuleContext(FunctorContext.class,0);
		}
		public Fof_argumentsContext fof_arguments() {
			return getRuleContext(Fof_argumentsContext.class,0);
		}
		public Fof_plain_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_plain_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_plain_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_plain_term(this);
		}
	}

	public final Fof_plain_termContext fof_plain_term() throws RecognitionException {
		Fof_plain_termContext _localctx = new Fof_plain_termContext(_ctx, getState());
		enterRule(_localctx, 288, RULE_fof_plain_term);
		try {
			setState(1385);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,97,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1379);
				constant();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1380);
				functor();
				setState(1381);
				match(T__8);
				setState(1382);
				fof_arguments();
				setState(1383);
				match(T__9);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_defined_termContext extends ParserRuleContext {
		public Defined_termContext defined_term() {
			return getRuleContext(Defined_termContext.class,0);
		}
		public Fof_defined_atomic_termContext fof_defined_atomic_term() {
			return getRuleContext(Fof_defined_atomic_termContext.class,0);
		}
		public Fof_defined_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_defined_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_defined_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_defined_term(this);
		}
	}

	public final Fof_defined_termContext fof_defined_term() throws RecognitionException {
		Fof_defined_termContext _localctx = new Fof_defined_termContext(_ctx, getState());
		enterRule(_localctx, 290, RULE_fof_defined_term);
		try {
			setState(1389);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Real:
			case Rational:
			case Integer:
			case Distinct_object:
				enterOuterAlt(_localctx, 1);
				{
				setState(1387);
				defined_term();
				}
				break;
			case Dollar_word:
				enterOuterAlt(_localctx, 2);
				{
				setState(1388);
				fof_defined_atomic_term();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_defined_atomic_termContext extends ParserRuleContext {
		public Fof_defined_plain_termContext fof_defined_plain_term() {
			return getRuleContext(Fof_defined_plain_termContext.class,0);
		}
		public Fof_defined_atomic_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_defined_atomic_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_defined_atomic_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_defined_atomic_term(this);
		}
	}

	public final Fof_defined_atomic_termContext fof_defined_atomic_term() throws RecognitionException {
		Fof_defined_atomic_termContext _localctx = new Fof_defined_atomic_termContext(_ctx, getState());
		enterRule(_localctx, 292, RULE_fof_defined_atomic_term);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1391);
			fof_defined_plain_term();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_defined_plain_termContext extends ParserRuleContext {
		public Defined_constantContext defined_constant() {
			return getRuleContext(Defined_constantContext.class,0);
		}
		public Defined_functorContext defined_functor() {
			return getRuleContext(Defined_functorContext.class,0);
		}
		public Fof_argumentsContext fof_arguments() {
			return getRuleContext(Fof_argumentsContext.class,0);
		}
		public Fof_defined_plain_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_defined_plain_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_defined_plain_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_defined_plain_term(this);
		}
	}

	public final Fof_defined_plain_termContext fof_defined_plain_term() throws RecognitionException {
		Fof_defined_plain_termContext _localctx = new Fof_defined_plain_termContext(_ctx, getState());
		enterRule(_localctx, 294, RULE_fof_defined_plain_term);
		try {
			setState(1399);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,99,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1393);
				defined_constant();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1394);
				defined_functor();
				setState(1395);
				match(T__8);
				setState(1396);
				fof_arguments();
				setState(1397);
				match(T__9);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_system_termContext extends ParserRuleContext {
		public System_constantContext system_constant() {
			return getRuleContext(System_constantContext.class,0);
		}
		public System_functorContext system_functor() {
			return getRuleContext(System_functorContext.class,0);
		}
		public Fof_argumentsContext fof_arguments() {
			return getRuleContext(Fof_argumentsContext.class,0);
		}
		public Fof_system_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_system_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_system_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_system_term(this);
		}
	}

	public final Fof_system_termContext fof_system_term() throws RecognitionException {
		Fof_system_termContext _localctx = new Fof_system_termContext(_ctx, getState());
		enterRule(_localctx, 296, RULE_fof_system_term);
		try {
			setState(1407);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,100,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1401);
				system_constant();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1402);
				system_functor();
				setState(1403);
				match(T__8);
				setState(1404);
				fof_arguments();
				setState(1405);
				match(T__9);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_argumentsContext extends ParserRuleContext {
		public Fof_termContext fof_term() {
			return getRuleContext(Fof_termContext.class,0);
		}
		public Fof_argumentsContext fof_arguments() {
			return getRuleContext(Fof_argumentsContext.class,0);
		}
		public Fof_argumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_arguments; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_arguments(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_arguments(this);
		}
	}

	public final Fof_argumentsContext fof_arguments() throws RecognitionException {
		Fof_argumentsContext _localctx = new Fof_argumentsContext(_ctx, getState());
		enterRule(_localctx, 298, RULE_fof_arguments);
		try {
			setState(1414);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,101,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1409);
				fof_term();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1410);
				fof_term();
				setState(1411);
				match(T__1);
				setState(1412);
				fof_arguments();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_termContext extends ParserRuleContext {
		public Fof_function_termContext fof_function_term() {
			return getRuleContext(Fof_function_termContext.class,0);
		}
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Fof_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_term(this);
		}
	}

	public final Fof_termContext fof_term() throws RecognitionException {
		Fof_termContext _localctx = new Fof_termContext(_ctx, getState());
		enterRule(_localctx, 300, RULE_fof_term);
		try {
			setState(1418);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Real:
			case Rational:
			case Integer:
			case Dollar_word:
			case Dollar_dollar_word:
			case Lower_word:
			case Single_quoted:
			case Distinct_object:
				enterOuterAlt(_localctx, 1);
				{
				setState(1416);
				fof_function_term();
				}
				break;
			case Upper_word:
				enterOuterAlt(_localctx, 2);
				{
				setState(1417);
				variable();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_function_termContext extends ParserRuleContext {
		public Fof_plain_termContext fof_plain_term() {
			return getRuleContext(Fof_plain_termContext.class,0);
		}
		public Fof_defined_termContext fof_defined_term() {
			return getRuleContext(Fof_defined_termContext.class,0);
		}
		public Fof_system_termContext fof_system_term() {
			return getRuleContext(Fof_system_termContext.class,0);
		}
		public Fof_function_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_function_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_function_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_function_term(this);
		}
	}

	public final Fof_function_termContext fof_function_term() throws RecognitionException {
		Fof_function_termContext _localctx = new Fof_function_termContext(_ctx, getState());
		enterRule(_localctx, 302, RULE_fof_function_term);
		try {
			setState(1423);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(1420);
				fof_plain_term();
				}
				break;
			case Real:
			case Rational:
			case Integer:
			case Dollar_word:
			case Distinct_object:
				enterOuterAlt(_localctx, 2);
				{
				setState(1421);
				fof_defined_term();
				}
				break;
			case Dollar_dollar_word:
				enterOuterAlt(_localctx, 3);
				{
				setState(1422);
				fof_system_term();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_sequentContext extends ParserRuleContext {
		public List<Fof_formula_tupleContext> fof_formula_tuple() {
			return getRuleContexts(Fof_formula_tupleContext.class);
		}
		public Fof_formula_tupleContext fof_formula_tuple(int i) {
			return getRuleContext(Fof_formula_tupleContext.class,i);
		}
		public TerminalNode Gentzen_arrow() { return getToken(tptp_v7_0_0_0Parser.Gentzen_arrow, 0); }
		public Fof_sequentContext fof_sequent() {
			return getRuleContext(Fof_sequentContext.class,0);
		}
		public Fof_sequentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_sequent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_sequent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_sequent(this);
		}
	}

	public final Fof_sequentContext fof_sequent() throws RecognitionException {
		Fof_sequentContext _localctx = new Fof_sequentContext(_ctx, getState());
		enterRule(_localctx, 304, RULE_fof_sequent);
		try {
			setState(1433);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__19:
			case T__22:
				enterOuterAlt(_localctx, 1);
				{
				setState(1425);
				fof_formula_tuple();
				setState(1426);
				match(Gentzen_arrow);
				setState(1427);
				fof_formula_tuple();
				}
				break;
			case T__8:
				enterOuterAlt(_localctx, 2);
				{
				setState(1429);
				match(T__8);
				setState(1430);
				fof_sequent();
				setState(1431);
				match(T__9);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_formula_tupleContext extends ParserRuleContext {
		public Fof_formula_tuple_listContext fof_formula_tuple_list() {
			return getRuleContext(Fof_formula_tuple_listContext.class,0);
		}
		public Fof_formula_tupleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_formula_tuple; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_formula_tuple(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_formula_tuple(this);
		}
	}

	public final Fof_formula_tupleContext fof_formula_tuple() throws RecognitionException {
		Fof_formula_tupleContext _localctx = new Fof_formula_tupleContext(_ctx, getState());
		enterRule(_localctx, 306, RULE_fof_formula_tuple);
		try {
			setState(1440);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__22:
				enterOuterAlt(_localctx, 1);
				{
				setState(1435);
				match(T__22);
				}
				break;
			case T__19:
				enterOuterAlt(_localctx, 2);
				{
				setState(1436);
				match(T__19);
				setState(1437);
				fof_formula_tuple_list();
				setState(1438);
				match(T__20);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_formula_tuple_listContext extends ParserRuleContext {
		public Fof_logic_formulaContext fof_logic_formula() {
			return getRuleContext(Fof_logic_formulaContext.class,0);
		}
		public Fof_formula_tuple_listContext fof_formula_tuple_list() {
			return getRuleContext(Fof_formula_tuple_listContext.class,0);
		}
		public Fof_formula_tuple_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_formula_tuple_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_formula_tuple_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_formula_tuple_list(this);
		}
	}

	public final Fof_formula_tuple_listContext fof_formula_tuple_list() throws RecognitionException {
		Fof_formula_tuple_listContext _localctx = new Fof_formula_tuple_listContext(_ctx, getState());
		enterRule(_localctx, 308, RULE_fof_formula_tuple_list);
		try {
			setState(1447);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,106,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1442);
				fof_logic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1443);
				fof_logic_formula();
				setState(1444);
				match(T__1);
				setState(1445);
				fof_formula_tuple_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Cnf_formulaContext extends ParserRuleContext {
		public Cnf_disjunctionContext cnf_disjunction() {
			return getRuleContext(Cnf_disjunctionContext.class,0);
		}
		public Cnf_formulaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cnf_formula; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterCnf_formula(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitCnf_formula(this);
		}
	}

	public final Cnf_formulaContext cnf_formula() throws RecognitionException {
		Cnf_formulaContext _localctx = new Cnf_formulaContext(_ctx, getState());
		enterRule(_localctx, 310, RULE_cnf_formula);
		try {
			setState(1454);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Not:
			case Real:
			case Rational:
			case Integer:
			case Dollar_word:
			case Dollar_dollar_word:
			case Upper_word:
			case Lower_word:
			case Single_quoted:
			case Distinct_object:
				enterOuterAlt(_localctx, 1);
				{
				setState(1449);
				cnf_disjunction(0);
				}
				break;
			case T__8:
				enterOuterAlt(_localctx, 2);
				{
				setState(1450);
				match(T__8);
				setState(1451);
				cnf_disjunction(0);
				setState(1452);
				match(T__9);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Cnf_disjunctionContext extends ParserRuleContext {
		public Cnf_literalContext cnf_literal() {
			return getRuleContext(Cnf_literalContext.class,0);
		}
		public Cnf_disjunctionContext cnf_disjunction() {
			return getRuleContext(Cnf_disjunctionContext.class,0);
		}
		public TerminalNode Or() { return getToken(tptp_v7_0_0_0Parser.Or, 0); }
		public Cnf_disjunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cnf_disjunction; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterCnf_disjunction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitCnf_disjunction(this);
		}
	}

	public final Cnf_disjunctionContext cnf_disjunction() throws RecognitionException {
		return cnf_disjunction(0);
	}

	private Cnf_disjunctionContext cnf_disjunction(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Cnf_disjunctionContext _localctx = new Cnf_disjunctionContext(_ctx, _parentState);
		Cnf_disjunctionContext _prevctx = _localctx;
		int _startState = 312;
		enterRecursionRule(_localctx, 312, RULE_cnf_disjunction, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(1457);
			cnf_literal();
			}
			_ctx.stop = _input.LT(-1);
			setState(1464);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,108,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Cnf_disjunctionContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_cnf_disjunction);
					setState(1459);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(1460);
					match(Or);
					setState(1461);
					cnf_literal();
					}
					} 
				}
				setState(1466);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,108,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Cnf_literalContext extends ParserRuleContext {
		public Fof_atomic_formulaContext fof_atomic_formula() {
			return getRuleContext(Fof_atomic_formulaContext.class,0);
		}
		public TerminalNode Not() { return getToken(tptp_v7_0_0_0Parser.Not, 0); }
		public Fof_infix_unaryContext fof_infix_unary() {
			return getRuleContext(Fof_infix_unaryContext.class,0);
		}
		public Cnf_literalContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cnf_literal; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterCnf_literal(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitCnf_literal(this);
		}
	}

	public final Cnf_literalContext cnf_literal() throws RecognitionException {
		Cnf_literalContext _localctx = new Cnf_literalContext(_ctx, getState());
		enterRule(_localctx, 314, RULE_cnf_literal);
		try {
			setState(1476);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,109,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1467);
				fof_atomic_formula();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1468);
				match(Not);
				setState(1469);
				fof_atomic_formula();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1470);
				match(Not);
				setState(1471);
				match(T__8);
				setState(1472);
				fof_atomic_formula();
				setState(1473);
				match(T__9);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1475);
				fof_infix_unary();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Thf_quantifierContext extends ParserRuleContext {
		public Fof_quantifierContext fof_quantifier() {
			return getRuleContext(Fof_quantifierContext.class,0);
		}
		public Th0_quantifierContext th0_quantifier() {
			return getRuleContext(Th0_quantifierContext.class,0);
		}
		public Th1_quantifierContext th1_quantifier() {
			return getRuleContext(Th1_quantifierContext.class,0);
		}
		public Thf_quantifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_thf_quantifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterThf_quantifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitThf_quantifier(this);
		}
	}

	public final Thf_quantifierContext thf_quantifier() throws RecognitionException {
		Thf_quantifierContext _localctx = new Thf_quantifierContext(_ctx, getState());
		enterRule(_localctx, 316, RULE_thf_quantifier);
		try {
			setState(1481);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Forall:
			case Exists:
				enterOuterAlt(_localctx, 1);
				{
				setState(1478);
				fof_quantifier();
				}
				break;
			case Lambda:
			case Choice:
			case Description:
				enterOuterAlt(_localctx, 2);
				{
				setState(1479);
				th0_quantifier();
				}
				break;
			case TyForall:
			case TyExists:
				enterOuterAlt(_localctx, 3);
				{
				setState(1480);
				th1_quantifier();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Th1_quantifierContext extends ParserRuleContext {
		public TerminalNode TyForall() { return getToken(tptp_v7_0_0_0Parser.TyForall, 0); }
		public TerminalNode TyExists() { return getToken(tptp_v7_0_0_0Parser.TyExists, 0); }
		public Th1_quantifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_th1_quantifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTh1_quantifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTh1_quantifier(this);
		}
	}

	public final Th1_quantifierContext th1_quantifier() throws RecognitionException {
		Th1_quantifierContext _localctx = new Th1_quantifierContext(_ctx, getState());
		enterRule(_localctx, 318, RULE_th1_quantifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1483);
			_la = _input.LA(1);
			if ( !(_la==TyForall || _la==TyExists) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Th0_quantifierContext extends ParserRuleContext {
		public TerminalNode Lambda() { return getToken(tptp_v7_0_0_0Parser.Lambda, 0); }
		public TerminalNode Choice() { return getToken(tptp_v7_0_0_0Parser.Choice, 0); }
		public TerminalNode Description() { return getToken(tptp_v7_0_0_0Parser.Description, 0); }
		public Th0_quantifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_th0_quantifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTh0_quantifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTh0_quantifier(this);
		}
	}

	public final Th0_quantifierContext th0_quantifier() throws RecognitionException {
		Th0_quantifierContext _localctx = new Th0_quantifierContext(_ctx, getState());
		enterRule(_localctx, 320, RULE_th0_quantifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1485);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Lambda) | (1L << Choice) | (1L << Description))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fof_quantifierContext extends ParserRuleContext {
		public TerminalNode Forall() { return getToken(tptp_v7_0_0_0Parser.Forall, 0); }
		public TerminalNode Exists() { return getToken(tptp_v7_0_0_0Parser.Exists, 0); }
		public Fof_quantifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fof_quantifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFof_quantifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFof_quantifier(this);
		}
	}

	public final Fof_quantifierContext fof_quantifier() throws RecognitionException {
		Fof_quantifierContext _localctx = new Fof_quantifierContext(_ctx, getState());
		enterRule(_localctx, 322, RULE_fof_quantifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1487);
			_la = _input.LA(1);
			if ( !(_la==Forall || _la==Exists) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Nonassoc_connectiveContext extends ParserRuleContext {
		public TerminalNode Iff() { return getToken(tptp_v7_0_0_0Parser.Iff, 0); }
		public TerminalNode Impl() { return getToken(tptp_v7_0_0_0Parser.Impl, 0); }
		public TerminalNode If() { return getToken(tptp_v7_0_0_0Parser.If, 0); }
		public TerminalNode Niff() { return getToken(tptp_v7_0_0_0Parser.Niff, 0); }
		public TerminalNode Nor() { return getToken(tptp_v7_0_0_0Parser.Nor, 0); }
		public TerminalNode Nand() { return getToken(tptp_v7_0_0_0Parser.Nand, 0); }
		public Nonassoc_connectiveContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nonassoc_connective; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNonassoc_connective(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNonassoc_connective(this);
		}
	}

	public final Nonassoc_connectiveContext nonassoc_connective() throws RecognitionException {
		Nonassoc_connectiveContext _localctx = new Nonassoc_connectiveContext(_ctx, getState());
		enterRule(_localctx, 324, RULE_nonassoc_connective);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1489);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Iff) | (1L << Impl) | (1L << If) | (1L << Niff) | (1L << Nor) | (1L << Nand))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Assoc_connectiveContext extends ParserRuleContext {
		public TerminalNode Or() { return getToken(tptp_v7_0_0_0Parser.Or, 0); }
		public TerminalNode And() { return getToken(tptp_v7_0_0_0Parser.And, 0); }
		public Assoc_connectiveContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assoc_connective; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterAssoc_connective(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitAssoc_connective(this);
		}
	}

	public final Assoc_connectiveContext assoc_connective() throws RecognitionException {
		Assoc_connectiveContext _localctx = new Assoc_connectiveContext(_ctx, getState());
		enterRule(_localctx, 326, RULE_assoc_connective);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1491);
			_la = _input.LA(1);
			if ( !(_la==Or || _la==And) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Unary_connectiveContext extends ParserRuleContext {
		public TerminalNode Not() { return getToken(tptp_v7_0_0_0Parser.Not, 0); }
		public Unary_connectiveContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unary_connective; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterUnary_connective(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitUnary_connective(this);
		}
	}

	public final Unary_connectiveContext unary_connective() throws RecognitionException {
		Unary_connectiveContext _localctx = new Unary_connectiveContext(_ctx, getState());
		enterRule(_localctx, 328, RULE_unary_connective);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1493);
			match(Not);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Type_constantContext extends ParserRuleContext {
		public Type_functorContext type_functor() {
			return getRuleContext(Type_functorContext.class,0);
		}
		public Type_constantContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_constant; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterType_constant(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitType_constant(this);
		}
	}

	public final Type_constantContext type_constant() throws RecognitionException {
		Type_constantContext _localctx = new Type_constantContext(_ctx, getState());
		enterRule(_localctx, 330, RULE_type_constant);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1495);
			type_functor();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Type_functorContext extends ParserRuleContext {
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public Type_functorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_functor; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterType_functor(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitType_functor(this);
		}
	}

	public final Type_functorContext type_functor() throws RecognitionException {
		Type_functorContext _localctx = new Type_functorContext(_ctx, getState());
		enterRule(_localctx, 332, RULE_type_functor);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1497);
			atomic_word();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Defined_typeContext extends ParserRuleContext {
		public TerminalNode Dollar_word() { return getToken(tptp_v7_0_0_0Parser.Dollar_word, 0); }
		public Defined_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_defined_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterDefined_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitDefined_type(this);
		}
	}

	public final Defined_typeContext defined_type() throws RecognitionException {
		Defined_typeContext _localctx = new Defined_typeContext(_ctx, getState());
		enterRule(_localctx, 334, RULE_defined_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1499);
			match(Dollar_word);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class System_typeContext extends ParserRuleContext {
		public Atomic_system_wordContext atomic_system_word() {
			return getRuleContext(Atomic_system_wordContext.class,0);
		}
		public System_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_system_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterSystem_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitSystem_type(this);
		}
	}

	public final System_typeContext system_type() throws RecognitionException {
		System_typeContext _localctx = new System_typeContext(_ctx, getState());
		enterRule(_localctx, 336, RULE_system_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1501);
			atomic_system_word();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AtomContext extends ParserRuleContext {
		public Untyped_atomContext untyped_atom() {
			return getRuleContext(Untyped_atomContext.class,0);
		}
		public Defined_constantContext defined_constant() {
			return getRuleContext(Defined_constantContext.class,0);
		}
		public AtomContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atom; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterAtom(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitAtom(this);
		}
	}

	public final AtomContext atom() throws RecognitionException {
		AtomContext _localctx = new AtomContext(_ctx, getState());
		enterRule(_localctx, 338, RULE_atom);
		try {
			setState(1505);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Dollar_dollar_word:
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(1503);
				untyped_atom();
				}
				break;
			case Dollar_word:
				enterOuterAlt(_localctx, 2);
				{
				setState(1504);
				defined_constant();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Untyped_atomContext extends ParserRuleContext {
		public ConstantContext constant() {
			return getRuleContext(ConstantContext.class,0);
		}
		public System_constantContext system_constant() {
			return getRuleContext(System_constantContext.class,0);
		}
		public Untyped_atomContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_untyped_atom; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterUntyped_atom(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitUntyped_atom(this);
		}
	}

	public final Untyped_atomContext untyped_atom() throws RecognitionException {
		Untyped_atomContext _localctx = new Untyped_atomContext(_ctx, getState());
		enterRule(_localctx, 340, RULE_untyped_atom);
		try {
			setState(1509);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(1507);
				constant();
				}
				break;
			case Dollar_dollar_word:
				enterOuterAlt(_localctx, 2);
				{
				setState(1508);
				system_constant();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Defined_propositionContext extends ParserRuleContext {
		public TerminalNode Dollar_word() { return getToken(tptp_v7_0_0_0Parser.Dollar_word, 0); }
		public Defined_propositionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_defined_proposition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterDefined_proposition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitDefined_proposition(this);
		}
	}

	public final Defined_propositionContext defined_proposition() throws RecognitionException {
		Defined_propositionContext _localctx = new Defined_propositionContext(_ctx, getState());
		enterRule(_localctx, 342, RULE_defined_proposition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1511);
			match(Dollar_word);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Defined_predicateContext extends ParserRuleContext {
		public TerminalNode Dollar_word() { return getToken(tptp_v7_0_0_0Parser.Dollar_word, 0); }
		public Defined_predicateContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_defined_predicate; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterDefined_predicate(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitDefined_predicate(this);
		}
	}

	public final Defined_predicateContext defined_predicate() throws RecognitionException {
		Defined_predicateContext _localctx = new Defined_predicateContext(_ctx, getState());
		enterRule(_localctx, 344, RULE_defined_predicate);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1513);
			match(Dollar_word);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Defined_infix_predContext extends ParserRuleContext {
		public TerminalNode Infix_equality() { return getToken(tptp_v7_0_0_0Parser.Infix_equality, 0); }
		public TerminalNode Assignment() { return getToken(tptp_v7_0_0_0Parser.Assignment, 0); }
		public Defined_infix_predContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_defined_infix_pred; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterDefined_infix_pred(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitDefined_infix_pred(this);
		}
	}

	public final Defined_infix_predContext defined_infix_pred() throws RecognitionException {
		Defined_infix_predContext _localctx = new Defined_infix_predContext(_ctx, getState());
		enterRule(_localctx, 346, RULE_defined_infix_pred);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1515);
			_la = _input.LA(1);
			if ( !(_la==Infix_equality || _la==Assignment) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ConstantContext extends ParserRuleContext {
		public FunctorContext functor() {
			return getRuleContext(FunctorContext.class,0);
		}
		public ConstantContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constant; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterConstant(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitConstant(this);
		}
	}

	public final ConstantContext constant() throws RecognitionException {
		ConstantContext _localctx = new ConstantContext(_ctx, getState());
		enterRule(_localctx, 348, RULE_constant);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1517);
			functor();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctorContext extends ParserRuleContext {
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public FunctorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functor; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFunctor(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFunctor(this);
		}
	}

	public final FunctorContext functor() throws RecognitionException {
		FunctorContext _localctx = new FunctorContext(_ctx, getState());
		enterRule(_localctx, 350, RULE_functor);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1519);
			atomic_word();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Defined_constantContext extends ParserRuleContext {
		public Defined_functorContext defined_functor() {
			return getRuleContext(Defined_functorContext.class,0);
		}
		public Defined_constantContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_defined_constant; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterDefined_constant(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitDefined_constant(this);
		}
	}

	public final Defined_constantContext defined_constant() throws RecognitionException {
		Defined_constantContext _localctx = new Defined_constantContext(_ctx, getState());
		enterRule(_localctx, 352, RULE_defined_constant);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1521);
			defined_functor();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Defined_functorContext extends ParserRuleContext {
		public Atomic_defined_wordContext atomic_defined_word() {
			return getRuleContext(Atomic_defined_wordContext.class,0);
		}
		public Defined_functorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_defined_functor; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterDefined_functor(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitDefined_functor(this);
		}
	}

	public final Defined_functorContext defined_functor() throws RecognitionException {
		Defined_functorContext _localctx = new Defined_functorContext(_ctx, getState());
		enterRule(_localctx, 354, RULE_defined_functor);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1523);
			atomic_defined_word();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class System_constantContext extends ParserRuleContext {
		public System_functorContext system_functor() {
			return getRuleContext(System_functorContext.class,0);
		}
		public System_constantContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_system_constant; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterSystem_constant(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitSystem_constant(this);
		}
	}

	public final System_constantContext system_constant() throws RecognitionException {
		System_constantContext _localctx = new System_constantContext(_ctx, getState());
		enterRule(_localctx, 356, RULE_system_constant);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1525);
			system_functor();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class System_functorContext extends ParserRuleContext {
		public Atomic_system_wordContext atomic_system_word() {
			return getRuleContext(Atomic_system_wordContext.class,0);
		}
		public System_functorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_system_functor; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterSystem_functor(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitSystem_functor(this);
		}
	}

	public final System_functorContext system_functor() throws RecognitionException {
		System_functorContext _localctx = new System_functorContext(_ctx, getState());
		enterRule(_localctx, 358, RULE_system_functor);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1527);
			atomic_system_word();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Def_or_sys_constantContext extends ParserRuleContext {
		public Defined_constantContext defined_constant() {
			return getRuleContext(Defined_constantContext.class,0);
		}
		public System_constantContext system_constant() {
			return getRuleContext(System_constantContext.class,0);
		}
		public Def_or_sys_constantContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_def_or_sys_constant; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterDef_or_sys_constant(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitDef_or_sys_constant(this);
		}
	}

	public final Def_or_sys_constantContext def_or_sys_constant() throws RecognitionException {
		Def_or_sys_constantContext _localctx = new Def_or_sys_constantContext(_ctx, getState());
		enterRule(_localctx, 360, RULE_def_or_sys_constant);
		try {
			setState(1531);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Dollar_word:
				enterOuterAlt(_localctx, 1);
				{
				setState(1529);
				defined_constant();
				}
				break;
			case Dollar_dollar_word:
				enterOuterAlt(_localctx, 2);
				{
				setState(1530);
				system_constant();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Th1_defined_termContext extends ParserRuleContext {
		public TerminalNode ForallComb() { return getToken(tptp_v7_0_0_0Parser.ForallComb, 0); }
		public TerminalNode ExistsComb() { return getToken(tptp_v7_0_0_0Parser.ExistsComb, 0); }
		public TerminalNode ChoiceComb() { return getToken(tptp_v7_0_0_0Parser.ChoiceComb, 0); }
		public TerminalNode DescriptionComb() { return getToken(tptp_v7_0_0_0Parser.DescriptionComb, 0); }
		public TerminalNode EqComb() { return getToken(tptp_v7_0_0_0Parser.EqComb, 0); }
		public Th1_defined_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_th1_defined_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTh1_defined_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTh1_defined_term(this);
		}
	}

	public final Th1_defined_termContext th1_defined_term() throws RecognitionException {
		Th1_defined_termContext _localctx = new Th1_defined_termContext(_ctx, getState());
		enterRule(_localctx, 362, RULE_th1_defined_term);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1533);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ForallComb) | (1L << ExistsComb) | (1L << ChoiceComb) | (1L << DescriptionComb) | (1L << EqComb))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Defined_termContext extends ParserRuleContext {
		public NumberContext number() {
			return getRuleContext(NumberContext.class,0);
		}
		public TerminalNode Distinct_object() { return getToken(tptp_v7_0_0_0Parser.Distinct_object, 0); }
		public Defined_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_defined_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterDefined_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitDefined_term(this);
		}
	}

	public final Defined_termContext defined_term() throws RecognitionException {
		Defined_termContext _localctx = new Defined_termContext(_ctx, getState());
		enterRule(_localctx, 364, RULE_defined_term);
		try {
			setState(1537);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Real:
			case Rational:
			case Integer:
				enterOuterAlt(_localctx, 1);
				{
				setState(1535);
				number();
				}
				break;
			case Distinct_object:
				enterOuterAlt(_localctx, 2);
				{
				setState(1536);
				match(Distinct_object);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VariableContext extends ParserRuleContext {
		public TerminalNode Upper_word() { return getToken(tptp_v7_0_0_0Parser.Upper_word, 0); }
		public VariableContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variable; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterVariable(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitVariable(this);
		}
	}

	public final VariableContext variable() throws RecognitionException {
		VariableContext _localctx = new VariableContext(_ctx, getState());
		enterRule(_localctx, 366, RULE_variable);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1539);
			match(Upper_word);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SourceContext extends ParserRuleContext {
		public Dag_sourceContext dag_source() {
			return getRuleContext(Dag_sourceContext.class,0);
		}
		public Internal_sourceContext internal_source() {
			return getRuleContext(Internal_sourceContext.class,0);
		}
		public External_sourceContext external_source() {
			return getRuleContext(External_sourceContext.class,0);
		}
		public TerminalNode Lower_word() { return getToken(tptp_v7_0_0_0Parser.Lower_word, 0); }
		public SourcesContext sources() {
			return getRuleContext(SourcesContext.class,0);
		}
		public SourceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_source; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterSource(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitSource(this);
		}
	}

	public final SourceContext source() throws RecognitionException {
		SourceContext _localctx = new SourceContext(_ctx, getState());
		enterRule(_localctx, 368, RULE_source);
		try {
			setState(1549);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,115,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1541);
				dag_source();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1542);
				internal_source();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1543);
				external_source();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1544);
				match(Lower_word);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(1545);
				match(T__10);
				setState(1546);
				sources();
				setState(1547);
				match(T__11);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SourcesContext extends ParserRuleContext {
		public List<SourceContext> source() {
			return getRuleContexts(SourceContext.class);
		}
		public SourceContext source(int i) {
			return getRuleContext(SourceContext.class,i);
		}
		public SourcesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sources; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterSources(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitSources(this);
		}
	}

	public final SourcesContext sources() throws RecognitionException {
		SourcesContext _localctx = new SourcesContext(_ctx, getState());
		enterRule(_localctx, 370, RULE_sources);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1551);
			source();
			setState(1556);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(1552);
				match(T__1);
				setState(1553);
				source();
				}
				}
				setState(1558);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Dag_sourceContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public Inference_recordContext inference_record() {
			return getRuleContext(Inference_recordContext.class,0);
		}
		public Dag_sourceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_dag_source; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterDag_source(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitDag_source(this);
		}
	}

	public final Dag_sourceContext dag_source() throws RecognitionException {
		Dag_sourceContext _localctx = new Dag_sourceContext(_ctx, getState());
		enterRule(_localctx, 372, RULE_dag_source);
		try {
			setState(1561);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Integer:
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(1559);
				name();
				}
				break;
			case T__23:
				enterOuterAlt(_localctx, 2);
				{
				setState(1560);
				inference_record();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Inference_recordContext extends ParserRuleContext {
		public Inference_ruleContext inference_rule() {
			return getRuleContext(Inference_ruleContext.class,0);
		}
		public Useful_infoContext useful_info() {
			return getRuleContext(Useful_infoContext.class,0);
		}
		public Inference_parentsContext inference_parents() {
			return getRuleContext(Inference_parentsContext.class,0);
		}
		public Inference_recordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inference_record; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterInference_record(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitInference_record(this);
		}
	}

	public final Inference_recordContext inference_record() throws RecognitionException {
		Inference_recordContext _localctx = new Inference_recordContext(_ctx, getState());
		enterRule(_localctx, 374, RULE_inference_record);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1563);
			match(T__23);
			setState(1564);
			inference_rule();
			setState(1565);
			match(T__1);
			setState(1566);
			useful_info();
			setState(1567);
			match(T__1);
			setState(1568);
			inference_parents();
			setState(1569);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Inference_ruleContext extends ParserRuleContext {
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public Inference_ruleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inference_rule; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterInference_rule(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitInference_rule(this);
		}
	}

	public final Inference_ruleContext inference_rule() throws RecognitionException {
		Inference_ruleContext _localctx = new Inference_ruleContext(_ctx, getState());
		enterRule(_localctx, 376, RULE_inference_rule);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1571);
			atomic_word();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Inference_parentsContext extends ParserRuleContext {
		public Parent_listContext parent_list() {
			return getRuleContext(Parent_listContext.class,0);
		}
		public Inference_parentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inference_parents; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterInference_parents(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitInference_parents(this);
		}
	}

	public final Inference_parentsContext inference_parents() throws RecognitionException {
		Inference_parentsContext _localctx = new Inference_parentsContext(_ctx, getState());
		enterRule(_localctx, 378, RULE_inference_parents);
		try {
			setState(1578);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__14:
				enterOuterAlt(_localctx, 1);
				{
				setState(1573);
				match(T__14);
				}
				break;
			case T__10:
				enterOuterAlt(_localctx, 2);
				{
				setState(1574);
				match(T__10);
				setState(1575);
				parent_list();
				setState(1576);
				match(T__11);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Parent_listContext extends ParserRuleContext {
		public List<Parent_infoContext> parent_info() {
			return getRuleContexts(Parent_infoContext.class);
		}
		public Parent_infoContext parent_info(int i) {
			return getRuleContext(Parent_infoContext.class,i);
		}
		public Parent_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parent_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterParent_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitParent_list(this);
		}
	}

	public final Parent_listContext parent_list() throws RecognitionException {
		Parent_listContext _localctx = new Parent_listContext(_ctx, getState());
		enterRule(_localctx, 380, RULE_parent_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1580);
			parent_info();
			setState(1585);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(1581);
				match(T__1);
				setState(1582);
				parent_info();
				}
				}
				setState(1587);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Parent_infoContext extends ParserRuleContext {
		public SourceContext source() {
			return getRuleContext(SourceContext.class,0);
		}
		public Parent_detailsContext parent_details() {
			return getRuleContext(Parent_detailsContext.class,0);
		}
		public Parent_infoContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parent_info; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterParent_info(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitParent_info(this);
		}
	}

	public final Parent_infoContext parent_info() throws RecognitionException {
		Parent_infoContext _localctx = new Parent_infoContext(_ctx, getState());
		enterRule(_localctx, 382, RULE_parent_info);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1588);
			source();
			setState(1590);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__12) {
				{
				setState(1589);
				parent_details();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Parent_detailsContext extends ParserRuleContext {
		public General_listContext general_list() {
			return getRuleContext(General_listContext.class,0);
		}
		public Parent_detailsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parent_details; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterParent_details(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitParent_details(this);
		}
	}

	public final Parent_detailsContext parent_details() throws RecognitionException {
		Parent_detailsContext _localctx = new Parent_detailsContext(_ctx, getState());
		enterRule(_localctx, 384, RULE_parent_details);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1592);
			match(T__12);
			setState(1593);
			general_list();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Internal_sourceContext extends ParserRuleContext {
		public Intro_typeContext intro_type() {
			return getRuleContext(Intro_typeContext.class,0);
		}
		public Optional_infoContext optional_info() {
			return getRuleContext(Optional_infoContext.class,0);
		}
		public Internal_sourceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_internal_source; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterInternal_source(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitInternal_source(this);
		}
	}

	public final Internal_sourceContext internal_source() throws RecognitionException {
		Internal_sourceContext _localctx = new Internal_sourceContext(_ctx, getState());
		enterRule(_localctx, 386, RULE_internal_source);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1595);
			match(T__24);
			setState(1596);
			intro_type();
			setState(1598);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(1597);
				optional_info();
				}
			}

			setState(1600);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Intro_typeContext extends ParserRuleContext {
		public TerminalNode Lower_word() { return getToken(tptp_v7_0_0_0Parser.Lower_word, 0); }
		public Intro_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_intro_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterIntro_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitIntro_type(this);
		}
	}

	public final Intro_typeContext intro_type() throws RecognitionException {
		Intro_typeContext _localctx = new Intro_typeContext(_ctx, getState());
		enterRule(_localctx, 388, RULE_intro_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1602);
			match(Lower_word);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class External_sourceContext extends ParserRuleContext {
		public File_sourceContext file_source() {
			return getRuleContext(File_sourceContext.class,0);
		}
		public TheoryContext theory() {
			return getRuleContext(TheoryContext.class,0);
		}
		public Creator_sourceContext creator_source() {
			return getRuleContext(Creator_sourceContext.class,0);
		}
		public External_sourceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_external_source; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterExternal_source(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitExternal_source(this);
		}
	}

	public final External_sourceContext external_source() throws RecognitionException {
		External_sourceContext _localctx = new External_sourceContext(_ctx, getState());
		enterRule(_localctx, 390, RULE_external_source);
		try {
			setState(1607);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__25:
				enterOuterAlt(_localctx, 1);
				{
				setState(1604);
				file_source();
				}
				break;
			case T__26:
				enterOuterAlt(_localctx, 2);
				{
				setState(1605);
				theory();
				}
				break;
			case T__27:
				enterOuterAlt(_localctx, 3);
				{
				setState(1606);
				creator_source();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class File_sourceContext extends ParserRuleContext {
		public File_nameContext file_name() {
			return getRuleContext(File_nameContext.class,0);
		}
		public File_infoContext file_info() {
			return getRuleContext(File_infoContext.class,0);
		}
		public File_sourceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_file_source; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFile_source(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFile_source(this);
		}
	}

	public final File_sourceContext file_source() throws RecognitionException {
		File_sourceContext _localctx = new File_sourceContext(_ctx, getState());
		enterRule(_localctx, 392, RULE_file_source);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1609);
			match(T__25);
			setState(1610);
			file_name();
			setState(1612);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(1611);
				file_info();
				}
			}

			setState(1614);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class File_infoContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public File_infoContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_file_info; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFile_info(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFile_info(this);
		}
	}

	public final File_infoContext file_info() throws RecognitionException {
		File_infoContext _localctx = new File_infoContext(_ctx, getState());
		enterRule(_localctx, 394, RULE_file_info);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1616);
			match(T__1);
			setState(1617);
			name();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TheoryContext extends ParserRuleContext {
		public Theory_nameContext theory_name() {
			return getRuleContext(Theory_nameContext.class,0);
		}
		public Optional_infoContext optional_info() {
			return getRuleContext(Optional_infoContext.class,0);
		}
		public TheoryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_theory; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTheory(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTheory(this);
		}
	}

	public final TheoryContext theory() throws RecognitionException {
		TheoryContext _localctx = new TheoryContext(_ctx, getState());
		enterRule(_localctx, 396, RULE_theory);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1619);
			match(T__26);
			setState(1620);
			theory_name();
			setState(1622);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(1621);
				optional_info();
				}
			}

			setState(1624);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Theory_nameContext extends ParserRuleContext {
		public TerminalNode Lower_word() { return getToken(tptp_v7_0_0_0Parser.Lower_word, 0); }
		public Theory_nameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_theory_name; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterTheory_name(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitTheory_name(this);
		}
	}

	public final Theory_nameContext theory_name() throws RecognitionException {
		Theory_nameContext _localctx = new Theory_nameContext(_ctx, getState());
		enterRule(_localctx, 398, RULE_theory_name);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1626);
			match(Lower_word);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Creator_sourceContext extends ParserRuleContext {
		public Creator_nameContext creator_name() {
			return getRuleContext(Creator_nameContext.class,0);
		}
		public Optional_infoContext optional_info() {
			return getRuleContext(Optional_infoContext.class,0);
		}
		public Creator_sourceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_creator_source; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterCreator_source(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitCreator_source(this);
		}
	}

	public final Creator_sourceContext creator_source() throws RecognitionException {
		Creator_sourceContext _localctx = new Creator_sourceContext(_ctx, getState());
		enterRule(_localctx, 400, RULE_creator_source);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1628);
			match(T__27);
			setState(1629);
			creator_name();
			setState(1631);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(1630);
				optional_info();
				}
			}

			setState(1633);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Creator_nameContext extends ParserRuleContext {
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public Creator_nameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_creator_name; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterCreator_name(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitCreator_name(this);
		}
	}

	public final Creator_nameContext creator_name() throws RecognitionException {
		Creator_nameContext _localctx = new Creator_nameContext(_ctx, getState());
		enterRule(_localctx, 402, RULE_creator_name);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1635);
			atomic_word();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Optional_infoContext extends ParserRuleContext {
		public Useful_infoContext useful_info() {
			return getRuleContext(Useful_infoContext.class,0);
		}
		public Optional_infoContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_optional_info; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterOptional_info(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitOptional_info(this);
		}
	}

	public final Optional_infoContext optional_info() throws RecognitionException {
		Optional_infoContext _localctx = new Optional_infoContext(_ctx, getState());
		enterRule(_localctx, 404, RULE_optional_info);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1637);
			match(T__1);
			setState(1638);
			useful_info();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Useful_infoContext extends ParserRuleContext {
		public Info_itemsContext info_items() {
			return getRuleContext(Info_itemsContext.class,0);
		}
		public General_listContext general_list() {
			return getRuleContext(General_listContext.class,0);
		}
		public Useful_infoContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_useful_info; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterUseful_info(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitUseful_info(this);
		}
	}

	public final Useful_infoContext useful_info() throws RecognitionException {
		Useful_infoContext _localctx = new Useful_infoContext(_ctx, getState());
		enterRule(_localctx, 406, RULE_useful_info);
		try {
			setState(1646);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,126,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1640);
				match(T__14);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1641);
				match(T__10);
				setState(1642);
				info_items();
				setState(1643);
				match(T__11);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1645);
				general_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Info_itemsContext extends ParserRuleContext {
		public List<Info_itemContext> info_item() {
			return getRuleContexts(Info_itemContext.class);
		}
		public Info_itemContext info_item(int i) {
			return getRuleContext(Info_itemContext.class,i);
		}
		public Info_itemsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_info_items; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterInfo_items(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitInfo_items(this);
		}
	}

	public final Info_itemsContext info_items() throws RecognitionException {
		Info_itemsContext _localctx = new Info_itemsContext(_ctx, getState());
		enterRule(_localctx, 408, RULE_info_items);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1648);
			info_item();
			setState(1653);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(1649);
				match(T__1);
				setState(1650);
				info_item();
				}
				}
				setState(1655);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Info_itemContext extends ParserRuleContext {
		public Formula_itemContext formula_item() {
			return getRuleContext(Formula_itemContext.class,0);
		}
		public Inference_itemContext inference_item() {
			return getRuleContext(Inference_itemContext.class,0);
		}
		public General_functionContext general_function() {
			return getRuleContext(General_functionContext.class,0);
		}
		public Info_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_info_item; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterInfo_item(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitInfo_item(this);
		}
	}

	public final Info_itemContext info_item() throws RecognitionException {
		Info_itemContext _localctx = new Info_itemContext(_ctx, getState());
		enterRule(_localctx, 410, RULE_info_item);
		try {
			setState(1659);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,128,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1656);
				formula_item();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1657);
				inference_item();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1658);
				general_function();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Formula_itemContext extends ParserRuleContext {
		public Description_itemContext description_item() {
			return getRuleContext(Description_itemContext.class,0);
		}
		public Iquote_itemContext iquote_item() {
			return getRuleContext(Iquote_itemContext.class,0);
		}
		public Formula_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_formula_item; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFormula_item(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFormula_item(this);
		}
	}

	public final Formula_itemContext formula_item() throws RecognitionException {
		Formula_itemContext _localctx = new Formula_itemContext(_ctx, getState());
		enterRule(_localctx, 412, RULE_formula_item);
		try {
			setState(1663);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__28:
				enterOuterAlt(_localctx, 1);
				{
				setState(1661);
				description_item();
				}
				break;
			case T__29:
				enterOuterAlt(_localctx, 2);
				{
				setState(1662);
				iquote_item();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Description_itemContext extends ParserRuleContext {
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public Description_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_description_item; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterDescription_item(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitDescription_item(this);
		}
	}

	public final Description_itemContext description_item() throws RecognitionException {
		Description_itemContext _localctx = new Description_itemContext(_ctx, getState());
		enterRule(_localctx, 414, RULE_description_item);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1665);
			match(T__28);
			setState(1666);
			atomic_word();
			setState(1667);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Iquote_itemContext extends ParserRuleContext {
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public Iquote_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_iquote_item; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterIquote_item(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitIquote_item(this);
		}
	}

	public final Iquote_itemContext iquote_item() throws RecognitionException {
		Iquote_itemContext _localctx = new Iquote_itemContext(_ctx, getState());
		enterRule(_localctx, 416, RULE_iquote_item);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1669);
			match(T__29);
			setState(1670);
			atomic_word();
			setState(1671);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Inference_itemContext extends ParserRuleContext {
		public Inference_statusContext inference_status() {
			return getRuleContext(Inference_statusContext.class,0);
		}
		public Assumptions_recordContext assumptions_record() {
			return getRuleContext(Assumptions_recordContext.class,0);
		}
		public New_symbol_recordContext new_symbol_record() {
			return getRuleContext(New_symbol_recordContext.class,0);
		}
		public RefutationContext refutation() {
			return getRuleContext(RefutationContext.class,0);
		}
		public Inference_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inference_item; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterInference_item(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitInference_item(this);
		}
	}

	public final Inference_itemContext inference_item() throws RecognitionException {
		Inference_itemContext _localctx = new Inference_itemContext(_ctx, getState());
		enterRule(_localctx, 418, RULE_inference_item);
		try {
			setState(1677);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__30:
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(1673);
				inference_status();
				}
				break;
			case T__31:
				enterOuterAlt(_localctx, 2);
				{
				setState(1674);
				assumptions_record();
				}
				break;
			case T__33:
				enterOuterAlt(_localctx, 3);
				{
				setState(1675);
				new_symbol_record();
				}
				break;
			case T__32:
				enterOuterAlt(_localctx, 4);
				{
				setState(1676);
				refutation();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Inference_statusContext extends ParserRuleContext {
		public Status_valueContext status_value() {
			return getRuleContext(Status_valueContext.class,0);
		}
		public Inference_infoContext inference_info() {
			return getRuleContext(Inference_infoContext.class,0);
		}
		public Inference_statusContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inference_status; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterInference_status(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitInference_status(this);
		}
	}

	public final Inference_statusContext inference_status() throws RecognitionException {
		Inference_statusContext _localctx = new Inference_statusContext(_ctx, getState());
		enterRule(_localctx, 420, RULE_inference_status);
		try {
			setState(1684);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__30:
				enterOuterAlt(_localctx, 1);
				{
				setState(1679);
				match(T__30);
				setState(1680);
				status_value();
				setState(1681);
				match(T__9);
				}
				break;
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 2);
				{
				setState(1683);
				inference_info();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Status_valueContext extends ParserRuleContext {
		public TerminalNode Lower_word() { return getToken(tptp_v7_0_0_0Parser.Lower_word, 0); }
		public Status_valueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_status_value; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterStatus_value(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitStatus_value(this);
		}
	}

	public final Status_valueContext status_value() throws RecognitionException {
		Status_valueContext _localctx = new Status_valueContext(_ctx, getState());
		enterRule(_localctx, 422, RULE_status_value);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1686);
			match(Lower_word);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Inference_infoContext extends ParserRuleContext {
		public Inference_ruleContext inference_rule() {
			return getRuleContext(Inference_ruleContext.class,0);
		}
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public General_listContext general_list() {
			return getRuleContext(General_listContext.class,0);
		}
		public Inference_infoContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inference_info; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterInference_info(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitInference_info(this);
		}
	}

	public final Inference_infoContext inference_info() throws RecognitionException {
		Inference_infoContext _localctx = new Inference_infoContext(_ctx, getState());
		enterRule(_localctx, 424, RULE_inference_info);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1688);
			inference_rule();
			setState(1689);
			match(T__8);
			setState(1690);
			atomic_word();
			setState(1691);
			match(T__1);
			setState(1692);
			general_list();
			setState(1693);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Assumptions_recordContext extends ParserRuleContext {
		public Name_listContext name_list() {
			return getRuleContext(Name_listContext.class,0);
		}
		public Assumptions_recordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assumptions_record; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterAssumptions_record(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitAssumptions_record(this);
		}
	}

	public final Assumptions_recordContext assumptions_record() throws RecognitionException {
		Assumptions_recordContext _localctx = new Assumptions_recordContext(_ctx, getState());
		enterRule(_localctx, 426, RULE_assumptions_record);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1695);
			match(T__31);
			setState(1696);
			match(T__10);
			setState(1697);
			name_list();
			setState(1698);
			match(T__11);
			setState(1699);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class RefutationContext extends ParserRuleContext {
		public File_sourceContext file_source() {
			return getRuleContext(File_sourceContext.class,0);
		}
		public RefutationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_refutation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterRefutation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitRefutation(this);
		}
	}

	public final RefutationContext refutation() throws RecognitionException {
		RefutationContext _localctx = new RefutationContext(_ctx, getState());
		enterRule(_localctx, 428, RULE_refutation);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1701);
			match(T__32);
			setState(1702);
			file_source();
			setState(1703);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class New_symbol_recordContext extends ParserRuleContext {
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public New_symbol_listContext new_symbol_list() {
			return getRuleContext(New_symbol_listContext.class,0);
		}
		public New_symbol_recordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_new_symbol_record; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNew_symbol_record(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNew_symbol_record(this);
		}
	}

	public final New_symbol_recordContext new_symbol_record() throws RecognitionException {
		New_symbol_recordContext _localctx = new New_symbol_recordContext(_ctx, getState());
		enterRule(_localctx, 430, RULE_new_symbol_record);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1705);
			match(T__33);
			setState(1706);
			atomic_word();
			setState(1707);
			match(T__1);
			setState(1708);
			match(T__10);
			setState(1709);
			new_symbol_list();
			setState(1710);
			match(T__11);
			setState(1711);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class New_symbol_listContext extends ParserRuleContext {
		public List<Principal_symbolContext> principal_symbol() {
			return getRuleContexts(Principal_symbolContext.class);
		}
		public Principal_symbolContext principal_symbol(int i) {
			return getRuleContext(Principal_symbolContext.class,i);
		}
		public New_symbol_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_new_symbol_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNew_symbol_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNew_symbol_list(this);
		}
	}

	public final New_symbol_listContext new_symbol_list() throws RecognitionException {
		New_symbol_listContext _localctx = new New_symbol_listContext(_ctx, getState());
		enterRule(_localctx, 432, RULE_new_symbol_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1713);
			principal_symbol();
			setState(1718);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(1714);
				match(T__1);
				setState(1715);
				principal_symbol();
				}
				}
				setState(1720);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Principal_symbolContext extends ParserRuleContext {
		public FunctorContext functor() {
			return getRuleContext(FunctorContext.class,0);
		}
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public Principal_symbolContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_principal_symbol; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterPrincipal_symbol(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitPrincipal_symbol(this);
		}
	}

	public final Principal_symbolContext principal_symbol() throws RecognitionException {
		Principal_symbolContext _localctx = new Principal_symbolContext(_ctx, getState());
		enterRule(_localctx, 434, RULE_principal_symbol);
		try {
			setState(1723);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(1721);
				functor();
				}
				break;
			case Upper_word:
				enterOuterAlt(_localctx, 2);
				{
				setState(1722);
				variable();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IncludeContext extends ParserRuleContext {
		public File_nameContext file_name() {
			return getRuleContext(File_nameContext.class,0);
		}
		public Formula_selectionContext formula_selection() {
			return getRuleContext(Formula_selectionContext.class,0);
		}
		public IncludeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_include; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterInclude(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitInclude(this);
		}
	}

	public final IncludeContext include() throws RecognitionException {
		IncludeContext _localctx = new IncludeContext(_ctx, getState());
		enterRule(_localctx, 436, RULE_include);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1725);
			match(T__34);
			setState(1726);
			file_name();
			setState(1728);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(1727);
				formula_selection();
				}
			}

			setState(1730);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Formula_selectionContext extends ParserRuleContext {
		public Name_listContext name_list() {
			return getRuleContext(Name_listContext.class,0);
		}
		public Formula_selectionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_formula_selection; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFormula_selection(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFormula_selection(this);
		}
	}

	public final Formula_selectionContext formula_selection() throws RecognitionException {
		Formula_selectionContext _localctx = new Formula_selectionContext(_ctx, getState());
		enterRule(_localctx, 438, RULE_formula_selection);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1732);
			match(T__1);
			setState(1733);
			match(T__10);
			setState(1734);
			name_list();
			setState(1735);
			match(T__11);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Name_listContext extends ParserRuleContext {
		public List<NameContext> name() {
			return getRuleContexts(NameContext.class);
		}
		public NameContext name(int i) {
			return getRuleContext(NameContext.class,i);
		}
		public Name_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_name_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterName_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitName_list(this);
		}
	}

	public final Name_listContext name_list() throws RecognitionException {
		Name_listContext _localctx = new Name_listContext(_ctx, getState());
		enterRule(_localctx, 440, RULE_name_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1737);
			name();
			setState(1742);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(1738);
				match(T__1);
				setState(1739);
				name();
				}
				}
				setState(1744);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class General_termContext extends ParserRuleContext {
		public General_dataContext general_data() {
			return getRuleContext(General_dataContext.class,0);
		}
		public General_termContext general_term() {
			return getRuleContext(General_termContext.class,0);
		}
		public General_listContext general_list() {
			return getRuleContext(General_listContext.class,0);
		}
		public General_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_general_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterGeneral_term(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitGeneral_term(this);
		}
	}

	public final General_termContext general_term() throws RecognitionException {
		General_termContext _localctx = new General_termContext(_ctx, getState());
		enterRule(_localctx, 442, RULE_general_term);
		try {
			setState(1751);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,136,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1745);
				general_data();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1746);
				general_data();
				setState(1747);
				match(T__12);
				setState(1748);
				general_term();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1750);
				general_list();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class General_dataContext extends ParserRuleContext {
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public General_functionContext general_function() {
			return getRuleContext(General_functionContext.class,0);
		}
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public NumberContext number() {
			return getRuleContext(NumberContext.class,0);
		}
		public TerminalNode Distinct_object() { return getToken(tptp_v7_0_0_0Parser.Distinct_object, 0); }
		public Formula_dataContext formula_data() {
			return getRuleContext(Formula_dataContext.class,0);
		}
		public General_dataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_general_data; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterGeneral_data(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitGeneral_data(this);
		}
	}

	public final General_dataContext general_data() throws RecognitionException {
		General_dataContext _localctx = new General_dataContext(_ctx, getState());
		enterRule(_localctx, 444, RULE_general_data);
		try {
			setState(1759);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,137,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1753);
				atomic_word();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1754);
				general_function();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1755);
				variable();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1756);
				number();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(1757);
				match(Distinct_object);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(1758);
				formula_data();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class General_functionContext extends ParserRuleContext {
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public General_termsContext general_terms() {
			return getRuleContext(General_termsContext.class,0);
		}
		public General_functionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_general_function; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterGeneral_function(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitGeneral_function(this);
		}
	}

	public final General_functionContext general_function() throws RecognitionException {
		General_functionContext _localctx = new General_functionContext(_ctx, getState());
		enterRule(_localctx, 446, RULE_general_function);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1761);
			atomic_word();
			setState(1762);
			match(T__8);
			setState(1763);
			general_terms();
			setState(1764);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Formula_dataContext extends ParserRuleContext {
		public Thf_formulaContext thf_formula() {
			return getRuleContext(Thf_formulaContext.class,0);
		}
		public Tff_formulaContext tff_formula() {
			return getRuleContext(Tff_formulaContext.class,0);
		}
		public Fof_formulaContext fof_formula() {
			return getRuleContext(Fof_formulaContext.class,0);
		}
		public Cnf_formulaContext cnf_formula() {
			return getRuleContext(Cnf_formulaContext.class,0);
		}
		public Fof_termContext fof_term() {
			return getRuleContext(Fof_termContext.class,0);
		}
		public Formula_dataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_formula_data; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFormula_data(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFormula_data(this);
		}
	}

	public final Formula_dataContext formula_data() throws RecognitionException {
		Formula_dataContext _localctx = new Formula_dataContext(_ctx, getState());
		enterRule(_localctx, 448, RULE_formula_data);
		try {
			setState(1786);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__35:
				enterOuterAlt(_localctx, 1);
				{
				setState(1766);
				match(T__35);
				setState(1767);
				thf_formula();
				setState(1768);
				match(T__9);
				}
				break;
			case T__36:
				enterOuterAlt(_localctx, 2);
				{
				setState(1770);
				match(T__36);
				setState(1771);
				tff_formula();
				setState(1772);
				match(T__9);
				}
				break;
			case T__37:
				enterOuterAlt(_localctx, 3);
				{
				setState(1774);
				match(T__37);
				setState(1775);
				fof_formula();
				setState(1776);
				match(T__9);
				}
				break;
			case T__38:
				enterOuterAlt(_localctx, 4);
				{
				setState(1778);
				match(T__38);
				setState(1779);
				cnf_formula();
				setState(1780);
				match(T__9);
				}
				break;
			case T__39:
				enterOuterAlt(_localctx, 5);
				{
				setState(1782);
				match(T__39);
				setState(1783);
				fof_term();
				setState(1784);
				match(T__9);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class General_listContext extends ParserRuleContext {
		public General_termsContext general_terms() {
			return getRuleContext(General_termsContext.class,0);
		}
		public General_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_general_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterGeneral_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitGeneral_list(this);
		}
	}

	public final General_listContext general_list() throws RecognitionException {
		General_listContext _localctx = new General_listContext(_ctx, getState());
		enterRule(_localctx, 450, RULE_general_list);
		try {
			setState(1793);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__14:
				enterOuterAlt(_localctx, 1);
				{
				setState(1788);
				match(T__14);
				}
				break;
			case T__10:
				enterOuterAlt(_localctx, 2);
				{
				setState(1789);
				match(T__10);
				setState(1790);
				general_terms();
				setState(1791);
				match(T__11);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class General_termsContext extends ParserRuleContext {
		public List<General_termContext> general_term() {
			return getRuleContexts(General_termContext.class);
		}
		public General_termContext general_term(int i) {
			return getRuleContext(General_termContext.class,i);
		}
		public General_termsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_general_terms; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterGeneral_terms(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitGeneral_terms(this);
		}
	}

	public final General_termsContext general_terms() throws RecognitionException {
		General_termsContext _localctx = new General_termsContext(_ctx, getState());
		enterRule(_localctx, 452, RULE_general_terms);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1795);
			general_term();
			setState(1800);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(1796);
				match(T__1);
				setState(1797);
				general_term();
				}
				}
				setState(1802);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NameContext extends ParserRuleContext {
		public Atomic_wordContext atomic_word() {
			return getRuleContext(Atomic_wordContext.class,0);
		}
		public TerminalNode Integer() { return getToken(tptp_v7_0_0_0Parser.Integer, 0); }
		public NameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_name; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterName(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitName(this);
		}
	}

	public final NameContext name() throws RecognitionException {
		NameContext _localctx = new NameContext(_ctx, getState());
		enterRule(_localctx, 454, RULE_name);
		try {
			setState(1805);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Lower_word:
			case Single_quoted:
				enterOuterAlt(_localctx, 1);
				{
				setState(1803);
				atomic_word();
				}
				break;
			case Integer:
				enterOuterAlt(_localctx, 2);
				{
				setState(1804);
				match(Integer);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Atomic_wordContext extends ParserRuleContext {
		public TerminalNode Lower_word() { return getToken(tptp_v7_0_0_0Parser.Lower_word, 0); }
		public TerminalNode Single_quoted() { return getToken(tptp_v7_0_0_0Parser.Single_quoted, 0); }
		public Atomic_wordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atomic_word; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterAtomic_word(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitAtomic_word(this);
		}
	}

	public final Atomic_wordContext atomic_word() throws RecognitionException {
		Atomic_wordContext _localctx = new Atomic_wordContext(_ctx, getState());
		enterRule(_localctx, 456, RULE_atomic_word);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1807);
			_la = _input.LA(1);
			if ( !(_la==Lower_word || _la==Single_quoted) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Atomic_defined_wordContext extends ParserRuleContext {
		public TerminalNode Dollar_word() { return getToken(tptp_v7_0_0_0Parser.Dollar_word, 0); }
		public Atomic_defined_wordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atomic_defined_word; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterAtomic_defined_word(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitAtomic_defined_word(this);
		}
	}

	public final Atomic_defined_wordContext atomic_defined_word() throws RecognitionException {
		Atomic_defined_wordContext _localctx = new Atomic_defined_wordContext(_ctx, getState());
		enterRule(_localctx, 458, RULE_atomic_defined_word);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1809);
			match(Dollar_word);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Atomic_system_wordContext extends ParserRuleContext {
		public TerminalNode Dollar_dollar_word() { return getToken(tptp_v7_0_0_0Parser.Dollar_dollar_word, 0); }
		public Atomic_system_wordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atomic_system_word; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterAtomic_system_word(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitAtomic_system_word(this);
		}
	}

	public final Atomic_system_wordContext atomic_system_word() throws RecognitionException {
		Atomic_system_wordContext _localctx = new Atomic_system_wordContext(_ctx, getState());
		enterRule(_localctx, 460, RULE_atomic_system_word);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1811);
			match(Dollar_dollar_word);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NumberContext extends ParserRuleContext {
		public TerminalNode Integer() { return getToken(tptp_v7_0_0_0Parser.Integer, 0); }
		public TerminalNode Rational() { return getToken(tptp_v7_0_0_0Parser.Rational, 0); }
		public TerminalNode Real() { return getToken(tptp_v7_0_0_0Parser.Real, 0); }
		public NumberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_number; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterNumber(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitNumber(this);
		}
	}

	public final NumberContext number() throws RecognitionException {
		NumberContext _localctx = new NumberContext(_ctx, getState());
		enterRule(_localctx, 462, RULE_number);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1813);
			_la = _input.LA(1);
			if ( !(((((_la - 73)) & ~0x3f) == 0 && ((1L << (_la - 73)) & ((1L << (Real - 73)) | (1L << (Rational - 73)) | (1L << (Integer - 73)))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class File_nameContext extends ParserRuleContext {
		public TerminalNode Single_quoted() { return getToken(tptp_v7_0_0_0Parser.Single_quoted, 0); }
		public File_nameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_file_name; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).enterFile_name(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof tptp_v7_0_0_0Listener ) ((tptp_v7_0_0_0Listener)listener).exitFile_name(this);
		}
	}

	public final File_nameContext file_name() throws RecognitionException {
		File_nameContext _localctx = new File_nameContext(_ctx, getState());
		enterRule(_localctx, 464, RULE_file_name);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1815);
			match(Single_quoted);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 17:
			return thf_or_formula_sempred((Thf_or_formulaContext)_localctx, predIndex);
		case 18:
			return thf_and_formula_sempred((Thf_and_formulaContext)_localctx, predIndex);
		case 19:
			return thf_apply_formula_sempred((Thf_apply_formulaContext)_localctx, predIndex);
		case 55:
			return thf_xprod_type_sempred((Thf_xprod_typeContext)_localctx, predIndex);
		case 56:
			return thf_union_type_sempred((Thf_union_typeContext)_localctx, predIndex);
		case 65:
			return tff_or_formula_sempred((Tff_or_formulaContext)_localctx, predIndex);
		case 66:
			return tff_and_formula_sempred((Tff_and_formulaContext)_localctx, predIndex);
		case 105:
			return tff_xprod_type_sempred((Tff_xprod_typeContext)_localctx, predIndex);
		case 130:
			return fof_or_formula_sempred((Fof_or_formulaContext)_localctx, predIndex);
		case 131:
			return fof_and_formula_sempred((Fof_and_formulaContext)_localctx, predIndex);
		case 156:
			return cnf_disjunction_sempred((Cnf_disjunctionContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean thf_or_formula_sempred(Thf_or_formulaContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean thf_and_formula_sempred(Thf_and_formulaContext _localctx, int predIndex) {
		switch (predIndex) {
		case 1:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean thf_apply_formula_sempred(Thf_apply_formulaContext _localctx, int predIndex) {
		switch (predIndex) {
		case 2:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean thf_xprod_type_sempred(Thf_xprod_typeContext _localctx, int predIndex) {
		switch (predIndex) {
		case 3:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean thf_union_type_sempred(Thf_union_typeContext _localctx, int predIndex) {
		switch (predIndex) {
		case 4:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean tff_or_formula_sempred(Tff_or_formulaContext _localctx, int predIndex) {
		switch (predIndex) {
		case 5:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean tff_and_formula_sempred(Tff_and_formulaContext _localctx, int predIndex) {
		switch (predIndex) {
		case 6:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean tff_xprod_type_sempred(Tff_xprod_typeContext _localctx, int predIndex) {
		switch (predIndex) {
		case 7:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean fof_or_formula_sempred(Fof_or_formulaContext _localctx, int predIndex) {
		switch (predIndex) {
		case 8:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean fof_and_formula_sempred(Fof_and_formulaContext _localctx, int predIndex) {
		switch (predIndex) {
		case 9:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean cnf_disjunction_sempred(Cnf_disjunctionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 10:
			return precpred(_ctx, 1);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001b\u071a\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007\u0018"+
		"\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002\u001b\u0007\u001b"+
		"\u0002\u001c\u0007\u001c\u0002\u001d\u0007\u001d\u0002\u001e\u0007\u001e"+
		"\u0002\u001f\u0007\u001f\u0002 \u0007 \u0002!\u0007!\u0002\"\u0007\"\u0002"+
		"#\u0007#\u0002$\u0007$\u0002%\u0007%\u0002&\u0007&\u0002\'\u0007\'\u0002"+
		"(\u0007(\u0002)\u0007)\u0002*\u0007*\u0002+\u0007+\u0002,\u0007,\u0002"+
		"-\u0007-\u0002.\u0007.\u0002/\u0007/\u00020\u00070\u00021\u00071\u0002"+
		"2\u00072\u00023\u00073\u00024\u00074\u00025\u00075\u00026\u00076\u0002"+
		"7\u00077\u00028\u00078\u00029\u00079\u0002:\u0007:\u0002;\u0007;\u0002"+
		"<\u0007<\u0002=\u0007=\u0002>\u0007>\u0002?\u0007?\u0002@\u0007@\u0002"+
		"A\u0007A\u0002B\u0007B\u0002C\u0007C\u0002D\u0007D\u0002E\u0007E\u0002"+
		"F\u0007F\u0002G\u0007G\u0002H\u0007H\u0002I\u0007I\u0002J\u0007J\u0002"+
		"K\u0007K\u0002L\u0007L\u0002M\u0007M\u0002N\u0007N\u0002O\u0007O\u0002"+
		"P\u0007P\u0002Q\u0007Q\u0002R\u0007R\u0002S\u0007S\u0002T\u0007T\u0002"+
		"U\u0007U\u0002V\u0007V\u0002W\u0007W\u0002X\u0007X\u0002Y\u0007Y\u0002"+
		"Z\u0007Z\u0002[\u0007[\u0002\\\u0007\\\u0002]\u0007]\u0002^\u0007^\u0002"+
		"_\u0007_\u0002`\u0007`\u0002a\u0007a\u0002b\u0007b\u0002c\u0007c\u0002"+
		"d\u0007d\u0002e\u0007e\u0002f\u0007f\u0002g\u0007g\u0002h\u0007h\u0002"+
		"i\u0007i\u0002j\u0007j\u0002k\u0007k\u0002l\u0007l\u0002m\u0007m\u0002"+
		"n\u0007n\u0002o\u0007o\u0002p\u0007p\u0002q\u0007q\u0002r\u0007r\u0002"+
		"s\u0007s\u0002t\u0007t\u0002u\u0007u\u0002v\u0007v\u0002w\u0007w\u0002"+
		"x\u0007x\u0002y\u0007y\u0002z\u0007z\u0002{\u0007{\u0002|\u0007|\u0002"+
		"}\u0007}\u0002~\u0007~\u0002\u007f\u0007\u007f\u0002\u0080\u0007\u0080"+
		"\u0002\u0081\u0007\u0081\u0002\u0082\u0007\u0082\u0002\u0083\u0007\u0083"+
		"\u0002\u0084\u0007\u0084\u0002\u0085\u0007\u0085\u0002\u0086\u0007\u0086"+
		"\u0002\u0087\u0007\u0087\u0002\u0088\u0007\u0088\u0002\u0089\u0007\u0089"+
		"\u0002\u008a\u0007\u008a\u0002\u008b\u0007\u008b\u0002\u008c\u0007\u008c"+
		"\u0002\u008d\u0007\u008d\u0002\u008e\u0007\u008e\u0002\u008f\u0007\u008f"+
		"\u0002\u0090\u0007\u0090\u0002\u0091\u0007\u0091\u0002\u0092\u0007\u0092"+
		"\u0002\u0093\u0007\u0093\u0002\u0094\u0007\u0094\u0002\u0095\u0007\u0095"+
		"\u0002\u0096\u0007\u0096\u0002\u0097\u0007\u0097\u0002\u0098\u0007\u0098"+
		"\u0002\u0099\u0007\u0099\u0002\u009a\u0007\u009a\u0002\u009b\u0007\u009b"+
		"\u0002\u009c\u0007\u009c\u0002\u009d\u0007\u009d\u0002\u009e\u0007\u009e"+
		"\u0002\u009f\u0007\u009f\u0002\u00a0\u0007\u00a0\u0002\u00a1\u0007\u00a1"+
		"\u0002\u00a2\u0007\u00a2\u0002\u00a3\u0007\u00a3\u0002\u00a4\u0007\u00a4"+
		"\u0002\u00a5\u0007\u00a5\u0002\u00a6\u0007\u00a6\u0002\u00a7\u0007\u00a7"+
		"\u0002\u00a8\u0007\u00a8\u0002\u00a9\u0007\u00a9\u0002\u00aa\u0007\u00aa"+
		"\u0002\u00ab\u0007\u00ab\u0002\u00ac\u0007\u00ac\u0002\u00ad\u0007\u00ad"+
		"\u0002\u00ae\u0007\u00ae\u0002\u00af\u0007\u00af\u0002\u00b0\u0007\u00b0"+
		"\u0002\u00b1\u0007\u00b1\u0002\u00b2\u0007\u00b2\u0002\u00b3\u0007\u00b3"+
		"\u0002\u00b4\u0007\u00b4\u0002\u00b5\u0007\u00b5\u0002\u00b6\u0007\u00b6"+
		"\u0002\u00b7\u0007\u00b7\u0002\u00b8\u0007\u00b8\u0002\u00b9\u0007\u00b9"+
		"\u0002\u00ba\u0007\u00ba\u0002\u00bb\u0007\u00bb\u0002\u00bc\u0007\u00bc"+
		"\u0002\u00bd\u0007\u00bd\u0002\u00be\u0007\u00be\u0002\u00bf\u0007\u00bf"+
		"\u0002\u00c0\u0007\u00c0\u0002\u00c1\u0007\u00c1\u0002\u00c2\u0007\u00c2"+
		"\u0002\u00c3\u0007\u00c3\u0002\u00c4\u0007\u00c4\u0002\u00c5\u0007\u00c5"+
		"\u0002\u00c6\u0007\u00c6\u0002\u00c7\u0007\u00c7\u0002\u00c8\u0007\u00c8"+
		"\u0002\u00c9\u0007\u00c9\u0002\u00ca\u0007\u00ca\u0002\u00cb\u0007\u00cb"+
		"\u0002\u00cc\u0007\u00cc\u0002\u00cd\u0007\u00cd\u0002\u00ce\u0007\u00ce"+
		"\u0002\u00cf\u0007\u00cf\u0002\u00d0\u0007\u00d0\u0002\u00d1\u0007\u00d1"+
		"\u0002\u00d2\u0007\u00d2\u0002\u00d3\u0007\u00d3\u0002\u00d4\u0007\u00d4"+
		"\u0002\u00d5\u0007\u00d5\u0002\u00d6\u0007\u00d6\u0002\u00d7\u0007\u00d7"+
		"\u0002\u00d8\u0007\u00d8\u0002\u00d9\u0007\u00d9\u0002\u00da\u0007\u00da"+
		"\u0002\u00db\u0007\u00db\u0002\u00dc\u0007\u00dc\u0002\u00dd\u0007\u00dd"+
		"\u0002\u00de\u0007\u00de\u0002\u00df\u0007\u00df\u0002\u00e0\u0007\u00e0"+
		"\u0002\u00e1\u0007\u00e1\u0002\u00e2\u0007\u00e2\u0002\u00e3\u0007\u00e3"+
		"\u0002\u00e4\u0007\u00e4\u0002\u00e5\u0007\u00e5\u0002\u00e6\u0007\u00e6"+
		"\u0002\u00e7\u0007\u00e7\u0002\u00e8\u0007\u00e8\u0001\u0000\u0005\u0000"+
		"\u01d4\b\u0000\n\u0000\f\u0000\u01d7\t\u0000\u0001\u0000\u0001\u0000\u0001"+
		"\u0001\u0001\u0001\u0003\u0001\u01dd\b\u0001\u0001\u0002\u0001\u0002\u0001"+
		"\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0003\u0002\u01e5\b\u0002\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0003\u0003\u01ee\b\u0003\u0001\u0003\u0001\u0003\u0001\u0004\u0001"+
		"\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0003\u0005\u01fb\b\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001"+
		"\u0006\u0003\u0006\u0206\b\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001"+
		"\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0003"+
		"\u0007\u0211\b\u0007\u0001\u0007\u0001\u0007\u0001\b\u0001\b\u0001\b\u0001"+
		"\b\u0001\b\u0001\b\u0001\b\u0003\b\u021c\b\b\u0001\b\u0001\b\u0001\t\u0001"+
		"\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0003\t\u0227\b\t\u0001\t\u0001"+
		"\t\u0001\n\u0001\n\u0001\n\u0003\n\u022e\b\n\u0001\u000b\u0001\u000b\u0001"+
		"\f\u0001\f\u0001\f\u0003\f\u0235\b\f\u0001\r\u0001\r\u0001\r\u0001\r\u0001"+
		"\r\u0001\r\u0003\r\u023d\b\r\u0001\u000e\u0001\u000e\u0001\u000e\u0003"+
		"\u000e\u0242\b\u000e\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0001"+
		"\u0010\u0001\u0010\u0001\u0010\u0003\u0010\u024b\b\u0010\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001"+
		"\u0011\u0005\u0011\u0255\b\u0011\n\u0011\f\u0011\u0258\t\u0011\u0001\u0012"+
		"\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012"+
		"\u0001\u0012\u0005\u0012\u0262\b\u0012\n\u0012\f\u0012\u0265\t\u0012\u0001"+
		"\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001"+
		"\u0013\u0001\u0013\u0005\u0013\u026f\b\u0013\n\u0013\f\u0013\u0272\t\u0013"+
		"\u0001\u0014\u0001\u0014\u0003\u0014\u0276\b\u0014\u0001\u0015\u0001\u0015"+
		"\u0003\u0015\u027a\b\u0015\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0016\u0003\u0016\u0283\b\u0016\u0001\u0017"+
		"\u0001\u0017\u0001\u0017\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018"+
		"\u0001\u0018\u0001\u0018\u0001\u0019\u0001\u0019\u0001\u0019\u0005\u0019"+
		"\u0291\b\u0019\n\u0019\f\u0019\u0294\t\u0019\u0001\u001a\u0001\u001a\u0003"+
		"\u001a\u0298\b\u001a\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b\u0001"+
		"\u001c\u0001\u001c\u0003\u001c\u02a0\b\u001c\u0001\u001d\u0001\u001d\u0001"+
		"\u001d\u0001\u001e\u0001\u001e\u0001\u001e\u0001\u001e\u0001\u001f\u0001"+
		"\u001f\u0001\u001f\u0001\u001f\u0003\u001f\u02ad\b\u001f\u0001 \u0001"+
		" \u0003 \u02b1\b \u0001!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001"+
		"!\u0003!\u02bb\b!\u0001\"\u0001\"\u0003\"\u02bf\b\"\u0001#\u0001#\u0001"+
		"#\u0001#\u0001$\u0001$\u0001%\u0001%\u0001%\u0001%\u0001%\u0001%\u0001"+
		"%\u0001%\u0001&\u0001&\u0001&\u0001&\u0001&\u0003&\u02d4\b&\u0001\'\u0001"+
		"\'\u0001\'\u0001\'\u0001\'\u0003\'\u02db\b\'\u0001(\u0001(\u0001(\u0001"+
		"(\u0001(\u0003(\u02e2\b(\u0001)\u0001)\u0001)\u0001)\u0001*\u0001*\u0001"+
		"*\u0001*\u0001*\u0003*\u02ed\b*\u0001+\u0001+\u0001+\u0001+\u0001+\u0001"+
		"+\u0003+\u02f5\b+\u0001,\u0001,\u0001,\u0001,\u0001,\u0003,\u02fc\b,\u0001"+
		"-\u0001-\u0001-\u0001-\u0001-\u0003-\u0303\b-\u0001.\u0001.\u0001.\u0001"+
		".\u0001.\u0001.\u0001.\u0001.\u0001.\u0001.\u0001.\u0001.\u0001.\u0001"+
		".\u0001.\u0003.\u0314\b.\u0001/\u0001/\u00010\u00010\u00010\u00010\u0001"+
		"0\u00030\u031d\b0\u00011\u00011\u00011\u00011\u00011\u00011\u00011\u0001"+
		"1\u00031\u0327\b1\u00012\u00012\u00012\u00032\u032c\b2\u00013\u00013\u0001"+
		"4\u00014\u00015\u00015\u00015\u00035\u0335\b5\u00016\u00016\u00016\u0001"+
		"6\u00016\u00016\u00016\u00016\u00036\u033f\b6\u00017\u00017\u00017\u0001"+
		"7\u00017\u00017\u00017\u00017\u00057\u0349\b7\n7\f7\u034c\t7\u00018\u0001"+
		"8\u00018\u00018\u00018\u00018\u00018\u00018\u00058\u0356\b8\n8\f8\u0359"+
		"\t8\u00019\u00019\u00019\u00019\u0001:\u0001:\u0001:\u0001:\u0001;\u0001"+
		";\u0001;\u0001;\u0001<\u0001<\u0001<\u0003<\u036a\b<\u0001=\u0001=\u0001"+
		"=\u0001=\u0001=\u0001=\u0003=\u0372\b=\u0001>\u0001>\u0003>\u0376\b>\u0001"+
		"?\u0001?\u0001?\u0001?\u0001@\u0001@\u0003@\u037e\b@\u0001A\u0001A\u0001"+
		"A\u0001A\u0001A\u0001A\u0001A\u0001A\u0005A\u0388\bA\nA\fA\u038b\tA\u0001"+
		"B\u0001B\u0001B\u0001B\u0001B\u0001B\u0001B\u0001B\u0005B\u0395\bB\nB"+
		"\fB\u0398\tB\u0001C\u0001C\u0001C\u0003C\u039d\bC\u0001D\u0001D\u0003"+
		"D\u03a1\bD\u0001E\u0001E\u0001E\u0001E\u0001E\u0001E\u0001E\u0003E\u03aa"+
		"\bE\u0001F\u0001F\u0001G\u0001G\u0001G\u0001G\u0001G\u0001G\u0001G\u0001"+
		"H\u0001H\u0001H\u0001H\u0001H\u0003H\u03ba\bH\u0001I\u0001I\u0003I\u03be"+
		"\bI\u0001J\u0001J\u0001J\u0001J\u0001K\u0001K\u0003K\u03c6\bK\u0001L\u0001"+
		"L\u0001L\u0001M\u0001M\u0001M\u0001M\u0001N\u0001N\u0001N\u0003N\u03d2"+
		"\bN\u0001O\u0001O\u0001O\u0001O\u0001O\u0001O\u0003O\u03da\bO\u0001P\u0001"+
		"P\u0003P\u03de\bP\u0001Q\u0001Q\u0001Q\u0001Q\u0001Q\u0001Q\u0001Q\u0001"+
		"Q\u0003Q\u03e8\bQ\u0001R\u0001R\u0001R\u0001R\u0001S\u0001S\u0001S\u0001"+
		"S\u0001S\u0001S\u0003S\u03f4\bS\u0001T\u0001T\u0001T\u0001T\u0001T\u0001"+
		"T\u0001T\u0001T\u0001U\u0001U\u0001U\u0001U\u0001U\u0003U\u0403\bU\u0001"+
		"V\u0001V\u0001V\u0001V\u0001V\u0003V\u040a\bV\u0001W\u0001W\u0001W\u0001"+
		"W\u0001W\u0003W\u0411\bW\u0001X\u0001X\u0001X\u0001X\u0001Y\u0001Y\u0003"+
		"Y\u0419\bY\u0001Z\u0001Z\u0001Z\u0001Z\u0001Z\u0003Z\u0420\bZ\u0001[\u0001"+
		"[\u0001[\u0001[\u0001[\u0001[\u0001\\\u0001\\\u0001\\\u0001\\\u0003\\"+
		"\u042c\b\\\u0001]\u0001]\u0001]\u0001]\u0001]\u0001]\u0001]\u0001]\u0003"+
		"]\u0436\b]\u0001^\u0001^\u0001^\u0001^\u0001^\u0003^\u043d\b^\u0001_\u0001"+
		"_\u0001_\u0001_\u0001_\u0003_\u0444\b_\u0001`\u0001`\u0001`\u0001`\u0001"+
		"`\u0001`\u0001`\u0001`\u0003`\u044e\b`\u0001a\u0001a\u0003a\u0452\ba\u0001"+
		"b\u0001b\u0001b\u0001b\u0001b\u0001b\u0003b\u045a\bb\u0001c\u0001c\u0001"+
		"c\u0001c\u0001c\u0001c\u0001c\u0001d\u0001d\u0001d\u0001d\u0001d\u0001"+
		"d\u0003d\u0469\bd\u0001e\u0001e\u0001e\u0001e\u0001e\u0003e\u0470\be\u0001"+
		"f\u0001f\u0001f\u0001f\u0001f\u0001f\u0001f\u0001f\u0001f\u0001f\u0001"+
		"f\u0001f\u0001f\u0003f\u047f\bf\u0001g\u0001g\u0001g\u0001g\u0001g\u0003"+
		"g\u0486\bg\u0001h\u0001h\u0001h\u0001h\u0001i\u0001i\u0001i\u0001i\u0001"+
		"i\u0001i\u0001i\u0001i\u0005i\u0494\bi\ni\fi\u0497\ti\u0001j\u0001j\u0001"+
		"j\u0001j\u0001k\u0001k\u0001k\u0001k\u0001k\u0003k\u04a2\bk\u0001l\u0001"+
		"l\u0001l\u0001l\u0001m\u0001m\u0001m\u0001m\u0001n\u0001n\u0001n\u0001"+
		"n\u0001o\u0001o\u0003o\u04b2\bo\u0001p\u0001p\u0001p\u0001p\u0001p\u0001"+
		"p\u0001p\u0001p\u0001p\u0001p\u0001p\u0001p\u0001p\u0001p\u0001p\u0003"+
		"p\u04c3\bp\u0001q\u0001q\u0001q\u0001q\u0001q\u0001q\u0001q\u0001q\u0001"+
		"q\u0001q\u0003q\u04cf\bq\u0001r\u0001r\u0001s\u0001s\u0001s\u0001s\u0001"+
		"s\u0003s\u04d8\bs\u0001t\u0001t\u0003t\u04dc\bt\u0001u\u0001u\u0001u\u0001"+
		"v\u0001v\u0001v\u0001v\u0001w\u0001w\u0001w\u0001w\u0001x\u0001x\u0001"+
		"y\u0001y\u0003y\u04ed\by\u0001z\u0001z\u0003z\u04f1\bz\u0001{\u0001{\u0003"+
		"{\u04f5\b{\u0001|\u0001|\u0001|\u0001|\u0001|\u0001|\u0001|\u0001}\u0001"+
		"}\u0003}\u0500\b}\u0001~\u0001~\u0001~\u0003~\u0505\b~\u0001\u007f\u0001"+
		"\u007f\u0003\u007f\u0509\b\u007f\u0001\u0080\u0001\u0080\u0001\u0080\u0001"+
		"\u0080\u0001\u0081\u0001\u0081\u0003\u0081\u0511\b\u0081\u0001\u0082\u0001"+
		"\u0082\u0001\u0082\u0001\u0082\u0001\u0082\u0001\u0082\u0001\u0082\u0001"+
		"\u0082\u0005\u0082\u051b\b\u0082\n\u0082\f\u0082\u051e\t\u0082\u0001\u0083"+
		"\u0001\u0083\u0001\u0083\u0001\u0083\u0001\u0083\u0001\u0083\u0001\u0083"+
		"\u0001\u0083\u0005\u0083\u0528\b\u0083\n\u0083\f\u0083\u052b\t\u0083\u0001"+
		"\u0084\u0001\u0084\u0001\u0084\u0001\u0084\u0003\u0084\u0531\b\u0084\u0001"+
		"\u0085\u0001\u0085\u0001\u0085\u0001\u0085\u0001\u0086\u0001\u0086\u0003"+
		"\u0086\u0539\b\u0086\u0001\u0087\u0001\u0087\u0001\u0087\u0001\u0087\u0001"+
		"\u0087\u0001\u0087\u0003\u0087\u0541\b\u0087\u0001\u0088\u0001\u0088\u0001"+
		"\u0088\u0001\u0088\u0001\u0088\u0001\u0088\u0001\u0088\u0001\u0089\u0001"+
		"\u0089\u0001\u0089\u0001\u0089\u0001\u0089\u0003\u0089\u054f\b\u0089\u0001"+
		"\u008a\u0001\u008a\u0001\u008a\u0003\u008a\u0554\b\u008a\u0001\u008b\u0001"+
		"\u008b\u0001\u008c\u0001\u008c\u0003\u008c\u055a\b\u008c\u0001\u008d\u0001"+
		"\u008d\u0001\u008e\u0001\u008e\u0001\u008e\u0001\u008e\u0001\u008f\u0001"+
		"\u008f\u0001\u0090\u0001\u0090\u0001\u0090\u0001\u0090\u0001\u0090\u0001"+
		"\u0090\u0003\u0090\u056a\b\u0090\u0001\u0091\u0001\u0091\u0003\u0091\u056e"+
		"\b\u0091\u0001\u0092\u0001\u0092\u0001\u0093\u0001\u0093\u0001\u0093\u0001"+
		"\u0093\u0001\u0093\u0001\u0093\u0003\u0093\u0578\b\u0093\u0001\u0094\u0001"+
		"\u0094\u0001\u0094\u0001\u0094\u0001\u0094\u0001\u0094\u0003\u0094\u0580"+
		"\b\u0094\u0001\u0095\u0001\u0095\u0001\u0095\u0001\u0095\u0001\u0095\u0003"+
		"\u0095\u0587\b\u0095\u0001\u0096\u0001\u0096\u0003\u0096\u058b\b\u0096"+
		"\u0001\u0097\u0001\u0097\u0001\u0097\u0003\u0097\u0590\b\u0097\u0001\u0098"+
		"\u0001\u0098\u0001\u0098\u0001\u0098\u0001\u0098\u0001\u0098\u0001\u0098"+
		"\u0001\u0098\u0003\u0098\u059a\b\u0098\u0001\u0099\u0001\u0099\u0001\u0099"+
		"\u0001\u0099\u0001\u0099\u0003\u0099\u05a1\b\u0099\u0001\u009a\u0001\u009a"+
		"\u0001\u009a\u0001\u009a\u0001\u009a\u0003\u009a\u05a8\b\u009a\u0001\u009b"+
		"\u0001\u009b\u0001\u009b\u0001\u009b\u0001\u009b\u0003\u009b\u05af\b\u009b"+
		"\u0001\u009c\u0001\u009c\u0001\u009c\u0001\u009c\u0001\u009c\u0001\u009c"+
		"\u0005\u009c\u05b7\b\u009c\n\u009c\f\u009c\u05ba\t\u009c\u0001\u009d\u0001"+
		"\u009d\u0001\u009d\u0001\u009d\u0001\u009d\u0001\u009d\u0001\u009d\u0001"+
		"\u009d\u0001\u009d\u0003\u009d\u05c5\b\u009d\u0001\u009e\u0001\u009e\u0001"+
		"\u009e\u0003\u009e\u05ca\b\u009e\u0001\u009f\u0001\u009f\u0001\u00a0\u0001"+
		"\u00a0\u0001\u00a1\u0001\u00a1\u0001\u00a2\u0001\u00a2\u0001\u00a3\u0001"+
		"\u00a3\u0001\u00a4\u0001\u00a4\u0001\u00a5\u0001\u00a5\u0001\u00a6\u0001"+
		"\u00a6\u0001\u00a7\u0001\u00a7\u0001\u00a8\u0001\u00a8\u0001\u00a9\u0001"+
		"\u00a9\u0003\u00a9\u05e2\b\u00a9\u0001\u00aa\u0001\u00aa\u0003\u00aa\u05e6"+
		"\b\u00aa\u0001\u00ab\u0001\u00ab\u0001\u00ac\u0001\u00ac\u0001\u00ad\u0001"+
		"\u00ad\u0001\u00ae\u0001\u00ae\u0001\u00af\u0001\u00af\u0001\u00b0\u0001"+
		"\u00b0\u0001\u00b1\u0001\u00b1\u0001\u00b2\u0001\u00b2\u0001\u00b3\u0001"+
		"\u00b3\u0001\u00b4\u0001\u00b4\u0003\u00b4\u05fc\b\u00b4\u0001\u00b5\u0001"+
		"\u00b5\u0001\u00b6\u0001\u00b6\u0003\u00b6\u0602\b\u00b6\u0001\u00b7\u0001"+
		"\u00b7\u0001\u00b8\u0001\u00b8\u0001\u00b8\u0001\u00b8\u0001\u00b8\u0001"+
		"\u00b8\u0001\u00b8\u0001\u00b8\u0003\u00b8\u060e\b\u00b8\u0001\u00b9\u0001"+
		"\u00b9\u0001\u00b9\u0005\u00b9\u0613\b\u00b9\n\u00b9\f\u00b9\u0616\t\u00b9"+
		"\u0001\u00ba\u0001\u00ba\u0003\u00ba\u061a\b\u00ba\u0001\u00bb\u0001\u00bb"+
		"\u0001\u00bb\u0001\u00bb\u0001\u00bb\u0001\u00bb\u0001\u00bb\u0001\u00bb"+
		"\u0001\u00bc\u0001\u00bc\u0001\u00bd\u0001\u00bd\u0001\u00bd\u0001\u00bd"+
		"\u0001\u00bd\u0003\u00bd\u062b\b\u00bd\u0001\u00be\u0001\u00be\u0001\u00be"+
		"\u0005\u00be\u0630\b\u00be\n\u00be\f\u00be\u0633\t\u00be\u0001\u00bf\u0001"+
		"\u00bf\u0003\u00bf\u0637\b\u00bf\u0001\u00c0\u0001\u00c0\u0001\u00c0\u0001"+
		"\u00c1\u0001\u00c1\u0001\u00c1\u0003\u00c1\u063f\b\u00c1\u0001\u00c1\u0001"+
		"\u00c1\u0001\u00c2\u0001\u00c2\u0001\u00c3\u0001\u00c3\u0001\u00c3\u0003"+
		"\u00c3\u0648\b\u00c3\u0001\u00c4\u0001\u00c4\u0001\u00c4\u0003\u00c4\u064d"+
		"\b\u00c4\u0001\u00c4\u0001\u00c4\u0001\u00c5\u0001\u00c5\u0001\u00c5\u0001"+
		"\u00c6\u0001\u00c6\u0001\u00c6\u0003\u00c6\u0657\b\u00c6\u0001\u00c6\u0001"+
		"\u00c6\u0001\u00c7\u0001\u00c7\u0001\u00c8\u0001\u00c8\u0001\u00c8\u0003"+
		"\u00c8\u0660\b\u00c8\u0001\u00c8\u0001\u00c8\u0001\u00c9\u0001\u00c9\u0001"+
		"\u00ca\u0001\u00ca\u0001\u00ca\u0001\u00cb\u0001\u00cb\u0001\u00cb\u0001"+
		"\u00cb\u0001\u00cb\u0001\u00cb\u0003\u00cb\u066f\b\u00cb\u0001\u00cc\u0001"+
		"\u00cc\u0001\u00cc\u0005\u00cc\u0674\b\u00cc\n\u00cc\f\u00cc\u0677\t\u00cc"+
		"\u0001\u00cd\u0001\u00cd\u0001\u00cd\u0003\u00cd\u067c\b\u00cd\u0001\u00ce"+
		"\u0001\u00ce\u0003\u00ce\u0680\b\u00ce\u0001\u00cf\u0001\u00cf\u0001\u00cf"+
		"\u0001\u00cf\u0001\u00d0\u0001\u00d0\u0001\u00d0\u0001\u00d0\u0001\u00d1"+
		"\u0001\u00d1\u0001\u00d1\u0001\u00d1\u0003\u00d1\u068e\b\u00d1\u0001\u00d2"+
		"\u0001\u00d2\u0001\u00d2\u0001\u00d2\u0001\u00d2\u0003\u00d2\u0695\b\u00d2"+
		"\u0001\u00d3\u0001\u00d3\u0001\u00d4\u0001\u00d4\u0001\u00d4\u0001\u00d4"+
		"\u0001\u00d4\u0001\u00d4\u0001\u00d4\u0001\u00d5\u0001\u00d5\u0001\u00d5"+
		"\u0001\u00d5\u0001\u00d5\u0001\u00d5\u0001\u00d6\u0001\u00d6\u0001\u00d6"+
		"\u0001\u00d6\u0001\u00d7\u0001\u00d7\u0001\u00d7\u0001\u00d7\u0001\u00d7"+
		"\u0001\u00d7\u0001\u00d7\u0001\u00d7\u0001\u00d8\u0001\u00d8\u0001\u00d8"+
		"\u0005\u00d8\u06b5\b\u00d8\n\u00d8\f\u00d8\u06b8\t\u00d8\u0001\u00d9\u0001"+
		"\u00d9\u0003\u00d9\u06bc\b\u00d9\u0001\u00da\u0001\u00da\u0001\u00da\u0003"+
		"\u00da\u06c1\b\u00da\u0001\u00da\u0001\u00da\u0001\u00db\u0001\u00db\u0001"+
		"\u00db\u0001\u00db\u0001\u00db\u0001\u00dc\u0001\u00dc\u0001\u00dc\u0005"+
		"\u00dc\u06cd\b\u00dc\n\u00dc\f\u00dc\u06d0\t\u00dc\u0001\u00dd\u0001\u00dd"+
		"\u0001\u00dd\u0001\u00dd\u0001\u00dd\u0001\u00dd\u0003\u00dd\u06d8\b\u00dd"+
		"\u0001\u00de\u0001\u00de\u0001\u00de\u0001\u00de\u0001\u00de\u0001\u00de"+
		"\u0003\u00de\u06e0\b\u00de\u0001\u00df\u0001\u00df\u0001\u00df\u0001\u00df"+
		"\u0001\u00df\u0001\u00e0\u0001\u00e0\u0001\u00e0\u0001\u00e0\u0001\u00e0"+
		"\u0001\u00e0\u0001\u00e0\u0001\u00e0\u0001\u00e0\u0001\u00e0\u0001\u00e0"+
		"\u0001\u00e0\u0001\u00e0\u0001\u00e0\u0001\u00e0\u0001\u00e0\u0001\u00e0"+
		"\u0001\u00e0\u0001\u00e0\u0001\u00e0\u0003\u00e0\u06fb\b\u00e0\u0001\u00e1"+
		"\u0001\u00e1\u0001\u00e1\u0001\u00e1\u0001\u00e1\u0003\u00e1\u0702\b\u00e1"+
		"\u0001\u00e2\u0001\u00e2\u0001\u00e2\u0005\u00e2\u0707\b\u00e2\n\u00e2"+
		"\f\u00e2\u070a\t\u00e2\u0001\u00e3\u0001\u00e3\u0003\u00e3\u070e\b\u00e3"+
		"\u0001\u00e4\u0001\u00e4\u0001\u00e5\u0001\u00e5\u0001\u00e6\u0001\u00e6"+
		"\u0001\u00e7\u0001\u00e7\u0001\u00e8\u0001\u00e8\u0001\u00e8\u0000\u000b"+
		"\"$&np\u0082\u0084\u00d2\u0104\u0106\u0138\u00e9\u0000\u0002\u0004\u0006"+
		"\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018\u001a\u001c\u001e \"$&(*,."+
		"02468:<>@BDFHJLNPRTVXZ\\^`bdfhjlnprtvxz|~\u0080\u0082\u0084\u0086\u0088"+
		"\u008a\u008c\u008e\u0090\u0092\u0094\u0096\u0098\u009a\u009c\u009e\u00a0"+
		"\u00a2\u00a4\u00a6\u00a8\u00aa\u00ac\u00ae\u00b0\u00b2\u00b4\u00b6\u00b8"+
		"\u00ba\u00bc\u00be\u00c0\u00c2\u00c4\u00c6\u00c8\u00ca\u00cc\u00ce\u00d0"+
		"\u00d2\u00d4\u00d6\u00d8\u00da\u00dc\u00de\u00e0\u00e2\u00e4\u00e6\u00e8"+
		"\u00ea\u00ec\u00ee\u00f0\u00f2\u00f4\u00f6\u00f8\u00fa\u00fc\u00fe\u0100"+
		"\u0102\u0104\u0106\u0108\u010a\u010c\u010e\u0110\u0112\u0114\u0116\u0118"+
		"\u011a\u011c\u011e\u0120\u0122\u0124\u0126\u0128\u012a\u012c\u012e\u0130"+
		"\u0132\u0134\u0136\u0138\u013a\u013c\u013e\u0140\u0142\u0144\u0146\u0148"+
		"\u014a\u014c\u014e\u0150\u0152\u0154\u0156\u0158\u015a\u015c\u015e\u0160"+
		"\u0162\u0164\u0166\u0168\u016a\u016c\u016e\u0170\u0172\u0174\u0176\u0178"+
		"\u017a\u017c\u017e\u0180\u0182\u0184\u0186\u0188\u018a\u018c\u018e\u0190"+
		"\u0192\u0194\u0196\u0198\u019a\u019c\u019e\u01a0\u01a2\u01a4\u01a6\u01a8"+
		"\u01aa\u01ac\u01ae\u01b0\u01b2\u01b4\u01b6\u01b8\u01ba\u01bc\u01be\u01c0"+
		"\u01c2\u01c4\u01c6\u01c8\u01ca\u01cc\u01ce\u01d0\u0000\t\u0002\u00003"+
		"388\u0003\u0000::<<>>\u0002\u00006699\u0001\u0000+0\u0001\u0000)*\u0002"+
		"\u000055AA\u0005\u00002277;;==??\u0001\u0000]^\u0003\u0000IILLOO\u0708"+
		"\u0000\u01d5\u0001\u0000\u0000\u0000\u0002\u01dc\u0001\u0000\u0000\u0000"+
		"\u0004\u01e4\u0001\u0000\u0000\u0000\u0006\u01e6\u0001\u0000\u0000\u0000"+
		"\b\u01f1\u0001\u0000\u0000\u0000\n\u01f3\u0001\u0000\u0000\u0000\f\u01fe"+
		"\u0001\u0000\u0000\u0000\u000e\u0209\u0001\u0000\u0000\u0000\u0010\u0214"+
		"\u0001\u0000\u0000\u0000\u0012\u021f\u0001\u0000\u0000\u0000\u0014\u022a"+
		"\u0001\u0000\u0000\u0000\u0016\u022f\u0001\u0000\u0000\u0000\u0018\u0234"+
		"\u0001\u0000\u0000\u0000\u001a\u023c\u0001\u0000\u0000\u0000\u001c\u0241"+
		"\u0001\u0000\u0000\u0000\u001e\u0243\u0001\u0000\u0000\u0000 \u024a\u0001"+
		"\u0000\u0000\u0000\"\u024c\u0001\u0000\u0000\u0000$\u0259\u0001\u0000"+
		"\u0000\u0000&\u0266\u0001\u0000\u0000\u0000(\u0275\u0001\u0000\u0000\u0000"+
		"*\u0279\u0001\u0000\u0000\u0000,\u0282\u0001\u0000\u0000\u0000.\u0284"+
		"\u0001\u0000\u0000\u00000\u0287\u0001\u0000\u0000\u00002\u028d\u0001\u0000"+
		"\u0000\u00004\u0297\u0001\u0000\u0000\u00006\u0299\u0001\u0000\u0000\u0000"+
		"8\u029f\u0001\u0000\u0000\u0000:\u02a1\u0001\u0000\u0000\u0000<\u02a4"+
		"\u0001\u0000\u0000\u0000>\u02ac\u0001\u0000\u0000\u0000@\u02b0\u0001\u0000"+
		"\u0000\u0000B\u02ba\u0001\u0000\u0000\u0000D\u02be\u0001\u0000\u0000\u0000"+
		"F\u02c0\u0001\u0000\u0000\u0000H\u02c4\u0001\u0000\u0000\u0000J\u02c6"+
		"\u0001\u0000\u0000\u0000L\u02d3\u0001\u0000\u0000\u0000N\u02da\u0001\u0000"+
		"\u0000\u0000P\u02e1\u0001\u0000\u0000\u0000R\u02e3\u0001\u0000\u0000\u0000"+
		"T\u02ec\u0001\u0000\u0000\u0000V\u02f4\u0001\u0000\u0000\u0000X\u02fb"+
		"\u0001\u0000\u0000\u0000Z\u0302\u0001\u0000\u0000\u0000\\\u0313\u0001"+
		"\u0000\u0000\u0000^\u0315\u0001\u0000\u0000\u0000`\u031c\u0001\u0000\u0000"+
		"\u0000b\u0326\u0001\u0000\u0000\u0000d\u032b\u0001\u0000\u0000\u0000f"+
		"\u032d\u0001\u0000\u0000\u0000h\u032f\u0001\u0000\u0000\u0000j\u0334\u0001"+
		"\u0000\u0000\u0000l\u033e\u0001\u0000\u0000\u0000n\u0340\u0001\u0000\u0000"+
		"\u0000p\u034d\u0001\u0000\u0000\u0000r\u035a\u0001\u0000\u0000\u0000t"+
		"\u035e\u0001\u0000\u0000\u0000v\u0362\u0001\u0000\u0000\u0000x\u0369\u0001"+
		"\u0000\u0000\u0000z\u0371\u0001\u0000\u0000\u0000|\u0375\u0001\u0000\u0000"+
		"\u0000~\u0377\u0001\u0000\u0000\u0000\u0080\u037d\u0001\u0000\u0000\u0000"+
		"\u0082\u037f\u0001\u0000\u0000\u0000\u0084\u038c\u0001\u0000\u0000\u0000"+
		"\u0086\u039c\u0001\u0000\u0000\u0000\u0088\u03a0\u0001\u0000\u0000\u0000"+
		"\u008a\u03a9\u0001\u0000\u0000\u0000\u008c\u03ab\u0001\u0000\u0000\u0000"+
		"\u008e\u03ad\u0001\u0000\u0000\u0000\u0090\u03b9\u0001\u0000\u0000\u0000"+
		"\u0092\u03bd\u0001\u0000\u0000\u0000\u0094\u03bf\u0001\u0000\u0000\u0000"+
		"\u0096\u03c5\u0001\u0000\u0000\u0000\u0098\u03c7\u0001\u0000\u0000\u0000"+
		"\u009a\u03ca\u0001\u0000\u0000\u0000\u009c\u03d1\u0001\u0000\u0000\u0000"+
		"\u009e\u03d9\u0001\u0000\u0000\u0000\u00a0\u03dd\u0001\u0000\u0000\u0000"+
		"\u00a2\u03e7\u0001\u0000\u0000\u0000\u00a4\u03e9\u0001\u0000\u0000\u0000"+
		"\u00a6\u03f3\u0001\u0000\u0000\u0000\u00a8\u03f5\u0001\u0000\u0000\u0000"+
		"\u00aa\u0402\u0001\u0000\u0000\u0000\u00ac\u0409\u0001\u0000\u0000\u0000"+
		"\u00ae\u0410\u0001\u0000\u0000\u0000\u00b0\u0412\u0001\u0000\u0000\u0000"+
		"\u00b2\u0418\u0001\u0000\u0000\u0000\u00b4\u041f\u0001\u0000\u0000\u0000"+
		"\u00b6\u0421\u0001\u0000\u0000\u0000\u00b8\u042b\u0001\u0000\u0000\u0000"+
		"\u00ba\u0435\u0001\u0000\u0000\u0000\u00bc\u043c\u0001\u0000\u0000\u0000"+
		"\u00be\u0443\u0001\u0000\u0000\u0000\u00c0\u044d\u0001\u0000\u0000\u0000"+
		"\u00c2\u0451\u0001\u0000\u0000\u0000\u00c4\u0459\u0001\u0000\u0000\u0000"+
		"\u00c6\u045b\u0001\u0000\u0000\u0000\u00c8\u0468\u0001\u0000\u0000\u0000"+
		"\u00ca\u046f\u0001\u0000\u0000\u0000\u00cc\u047e\u0001\u0000\u0000\u0000"+
		"\u00ce\u0485\u0001\u0000\u0000\u0000\u00d0\u0487\u0001\u0000\u0000\u0000"+
		"\u00d2\u048b\u0001\u0000\u0000\u0000\u00d4\u0498\u0001\u0000\u0000\u0000"+
		"\u00d6\u04a1\u0001\u0000\u0000\u0000\u00d8\u04a3\u0001\u0000\u0000\u0000"+
		"\u00da\u04a7\u0001\u0000\u0000\u0000\u00dc\u04ab\u0001\u0000\u0000\u0000"+
		"\u00de\u04b1\u0001\u0000\u0000\u0000\u00e0\u04c2\u0001\u0000\u0000\u0000"+
		"\u00e2\u04ce\u0001\u0000\u0000\u0000\u00e4\u04d0\u0001\u0000\u0000\u0000"+
		"\u00e6\u04d7\u0001\u0000\u0000\u0000\u00e8\u04db\u0001\u0000\u0000\u0000"+
		"\u00ea\u04dd\u0001\u0000\u0000\u0000\u00ec\u04e0\u0001\u0000\u0000\u0000"+
		"\u00ee\u04e4\u0001\u0000\u0000\u0000\u00f0\u04e8\u0001\u0000\u0000\u0000"+
		"\u00f2\u04ec\u0001\u0000\u0000\u0000\u00f4\u04f0\u0001\u0000\u0000\u0000"+
		"\u00f6\u04f4\u0001\u0000\u0000\u0000\u00f8\u04f6\u0001\u0000\u0000\u0000"+
		"\u00fa\u04ff\u0001\u0000\u0000\u0000\u00fc\u0504\u0001\u0000\u0000\u0000"+
		"\u00fe\u0508\u0001\u0000\u0000\u0000\u0100\u050a\u0001\u0000\u0000\u0000"+
		"\u0102\u0510\u0001\u0000\u0000\u0000\u0104\u0512\u0001\u0000\u0000\u0000"+
		"\u0106\u051f\u0001\u0000\u0000\u0000\u0108\u0530\u0001\u0000\u0000\u0000"+
		"\u010a\u0532\u0001\u0000\u0000\u0000\u010c\u0538\u0001\u0000\u0000\u0000"+
		"\u010e\u0540\u0001\u0000\u0000\u0000\u0110\u0542\u0001\u0000\u0000\u0000"+
		"\u0112\u054e\u0001\u0000\u0000\u0000\u0114\u0553\u0001\u0000\u0000\u0000"+
		"\u0116\u0555\u0001\u0000\u0000\u0000\u0118\u0559\u0001\u0000\u0000\u0000"+
		"\u011a\u055b\u0001\u0000\u0000\u0000\u011c\u055d\u0001\u0000\u0000\u0000"+
		"\u011e\u0561\u0001\u0000\u0000\u0000\u0120\u0569\u0001\u0000\u0000\u0000"+
		"\u0122\u056d\u0001\u0000\u0000\u0000\u0124\u056f\u0001\u0000\u0000\u0000"+
		"\u0126\u0577\u0001\u0000\u0000\u0000\u0128\u057f\u0001\u0000\u0000\u0000"+
		"\u012a\u0586\u0001\u0000\u0000\u0000\u012c\u058a\u0001\u0000\u0000\u0000"+
		"\u012e\u058f\u0001\u0000\u0000\u0000\u0130\u0599\u0001\u0000\u0000\u0000"+
		"\u0132\u05a0\u0001\u0000\u0000\u0000\u0134\u05a7\u0001\u0000\u0000\u0000"+
		"\u0136\u05ae\u0001\u0000\u0000\u0000\u0138\u05b0\u0001\u0000\u0000\u0000"+
		"\u013a\u05c4\u0001\u0000\u0000\u0000\u013c\u05c9\u0001\u0000\u0000\u0000"+
		"\u013e\u05cb\u0001\u0000\u0000\u0000\u0140\u05cd\u0001\u0000\u0000\u0000"+
		"\u0142\u05cf\u0001\u0000\u0000\u0000\u0144\u05d1\u0001\u0000\u0000\u0000"+
		"\u0146\u05d3\u0001\u0000\u0000\u0000\u0148\u05d5\u0001\u0000\u0000\u0000"+
		"\u014a\u05d7\u0001\u0000\u0000\u0000\u014c\u05d9\u0001\u0000\u0000\u0000"+
		"\u014e\u05db\u0001\u0000\u0000\u0000\u0150\u05dd\u0001\u0000\u0000\u0000"+
		"\u0152\u05e1\u0001\u0000\u0000\u0000\u0154\u05e5\u0001\u0000\u0000\u0000"+
		"\u0156\u05e7\u0001\u0000\u0000\u0000\u0158\u05e9\u0001\u0000\u0000\u0000"+
		"\u015a\u05eb\u0001\u0000\u0000\u0000\u015c\u05ed\u0001\u0000\u0000\u0000"+
		"\u015e\u05ef\u0001\u0000\u0000\u0000\u0160\u05f1\u0001\u0000\u0000\u0000"+
		"\u0162\u05f3\u0001\u0000\u0000\u0000\u0164\u05f5\u0001\u0000\u0000\u0000"+
		"\u0166\u05f7\u0001\u0000\u0000\u0000\u0168\u05fb\u0001\u0000\u0000\u0000"+
		"\u016a\u05fd\u0001\u0000\u0000\u0000\u016c\u0601\u0001\u0000\u0000\u0000"+
		"\u016e\u0603\u0001\u0000\u0000\u0000\u0170\u060d\u0001\u0000\u0000\u0000"+
		"\u0172\u060f\u0001\u0000\u0000\u0000\u0174\u0619\u0001\u0000\u0000\u0000"+
		"\u0176\u061b\u0001\u0000\u0000\u0000\u0178\u0623\u0001\u0000\u0000\u0000"+
		"\u017a\u062a\u0001\u0000\u0000\u0000\u017c\u062c\u0001\u0000\u0000\u0000"+
		"\u017e\u0634\u0001\u0000\u0000\u0000\u0180\u0638\u0001\u0000\u0000\u0000"+
		"\u0182\u063b\u0001\u0000\u0000\u0000\u0184\u0642\u0001\u0000\u0000\u0000"+
		"\u0186\u0647\u0001\u0000\u0000\u0000\u0188\u0649\u0001\u0000\u0000\u0000"+
		"\u018a\u0650\u0001\u0000\u0000\u0000\u018c\u0653\u0001\u0000\u0000\u0000"+
		"\u018e\u065a\u0001\u0000\u0000\u0000\u0190\u065c\u0001\u0000\u0000\u0000"+
		"\u0192\u0663\u0001\u0000\u0000\u0000\u0194\u0665\u0001\u0000\u0000\u0000"+
		"\u0196\u066e\u0001\u0000\u0000\u0000\u0198\u0670\u0001\u0000\u0000\u0000"+
		"\u019a\u067b\u0001\u0000\u0000\u0000\u019c\u067f\u0001\u0000\u0000\u0000"+
		"\u019e\u0681\u0001\u0000\u0000\u0000\u01a0\u0685\u0001\u0000\u0000\u0000"+
		"\u01a2\u068d\u0001\u0000\u0000\u0000\u01a4\u0694\u0001\u0000\u0000\u0000"+
		"\u01a6\u0696\u0001\u0000\u0000\u0000\u01a8\u0698\u0001\u0000\u0000\u0000"+
		"\u01aa\u069f\u0001\u0000\u0000\u0000\u01ac\u06a5\u0001\u0000\u0000\u0000"+
		"\u01ae\u06a9\u0001\u0000\u0000\u0000\u01b0\u06b1\u0001\u0000\u0000\u0000"+
		"\u01b2\u06bb\u0001\u0000\u0000\u0000\u01b4\u06bd\u0001\u0000\u0000\u0000"+
		"\u01b6\u06c4\u0001\u0000\u0000\u0000\u01b8\u06c9\u0001\u0000\u0000\u0000"+
		"\u01ba\u06d7\u0001\u0000\u0000\u0000\u01bc\u06df\u0001\u0000\u0000\u0000"+
		"\u01be\u06e1\u0001\u0000\u0000\u0000\u01c0\u06fa\u0001\u0000\u0000\u0000"+
		"\u01c2\u0701\u0001\u0000\u0000\u0000\u01c4\u0703\u0001\u0000\u0000\u0000"+
		"\u01c6\u070d\u0001\u0000\u0000\u0000\u01c8\u070f\u0001\u0000\u0000\u0000"+
		"\u01ca\u0711\u0001\u0000\u0000\u0000\u01cc\u0713\u0001\u0000\u0000\u0000"+
		"\u01ce\u0715\u0001\u0000\u0000\u0000\u01d0\u0717\u0001\u0000\u0000\u0000"+
		"\u01d2\u01d4\u0003\u0002\u0001\u0000\u01d3\u01d2\u0001\u0000\u0000\u0000"+
		"\u01d4\u01d7\u0001\u0000\u0000\u0000\u01d5\u01d3\u0001\u0000\u0000\u0000"+
		"\u01d5\u01d6\u0001\u0000\u0000\u0000\u01d6\u01d8\u0001\u0000\u0000\u0000"+
		"\u01d7\u01d5\u0001\u0000\u0000\u0000\u01d8\u01d9\u0005\u0000\u0000\u0001"+
		"\u01d9\u0001\u0001\u0000\u0000\u0000\u01da\u01dd\u0003\u0004\u0002\u0000"+
		"\u01db\u01dd\u0003\u01b4\u00da\u0000\u01dc\u01da\u0001\u0000\u0000\u0000"+
		"\u01dc\u01db\u0001\u0000\u0000\u0000\u01dd\u0003\u0001\u0000\u0000\u0000"+
		"\u01de\u01e5\u0003\n\u0005\u0000\u01df\u01e5\u0003\f\u0006\u0000\u01e0"+
		"\u01e5\u0003\u000e\u0007\u0000\u01e1\u01e5\u0003\u0010\b\u0000\u01e2\u01e5"+
		"\u0003\u0012\t\u0000\u01e3\u01e5\u0003\u0006\u0003\u0000\u01e4\u01de\u0001"+
		"\u0000\u0000\u0000\u01e4\u01df\u0001\u0000\u0000\u0000\u01e4\u01e0\u0001"+
		"\u0000\u0000\u0000\u01e4\u01e1\u0001\u0000\u0000\u0000\u01e4\u01e2\u0001"+
		"\u0000\u0000\u0000\u01e4\u01e3\u0001\u0000\u0000\u0000\u01e5\u0005\u0001"+
		"\u0000\u0000\u0000\u01e6\u01e7\u0005\u0001\u0000\u0000\u01e7\u01e8\u0003"+
		"\u01c6\u00e3\u0000\u01e8\u01e9\u0005\u0002\u0000\u0000\u01e9\u01ea\u0003"+
		"\u0016\u000b\u0000\u01ea\u01eb\u0005\u0002\u0000\u0000\u01eb\u01ed\u0003"+
		"\b\u0004\u0000\u01ec\u01ee\u0003\u0014\n\u0000\u01ed\u01ec\u0001\u0000"+
		"\u0000\u0000\u01ed\u01ee\u0001\u0000\u0000\u0000\u01ee\u01ef\u0001\u0000"+
		"\u0000\u0000\u01ef\u01f0\u0005\u0003\u0000\u0000\u01f0\u0007\u0001\u0000"+
		"\u0000\u0000\u01f1\u01f2\u0003\u00fa}\u0000\u01f2\t\u0001\u0000\u0000"+
		"\u0000\u01f3\u01f4\u0005\u0004\u0000\u0000\u01f4\u01f5\u0003\u01c6\u00e3"+
		"\u0000\u01f5\u01f6\u0005\u0002\u0000\u0000\u01f6\u01f7\u0003\u0016\u000b"+
		"\u0000\u01f7\u01f8\u0005\u0002\u0000\u0000\u01f8\u01fa\u0003\u0018\f\u0000"+
		"\u01f9\u01fb\u0003\u0014\n\u0000\u01fa\u01f9\u0001\u0000\u0000\u0000\u01fa"+
		"\u01fb\u0001\u0000\u0000\u0000\u01fb\u01fc\u0001\u0000\u0000\u0000\u01fc"+
		"\u01fd\u0005\u0003\u0000\u0000\u01fd\u000b\u0001\u0000\u0000\u0000\u01fe"+
		"\u01ff\u0005\u0005\u0000\u0000\u01ff\u0200\u0003\u01c6\u00e3\u0000\u0200"+
		"\u0201\u0005\u0002\u0000\u0000\u0201\u0202\u0003\u0016\u000b\u0000\u0202"+
		"\u0203\u0005\u0002\u0000\u0000\u0203\u0205\u0003x<\u0000\u0204\u0206\u0003"+
		"\u0014\n\u0000\u0205\u0204\u0001\u0000\u0000\u0000\u0205\u0206\u0001\u0000"+
		"\u0000\u0000\u0206\u0207\u0001\u0000\u0000\u0000\u0207\u0208\u0005\u0003"+
		"\u0000\u0000\u0208\r\u0001\u0000\u0000\u0000\u0209\u020a\u0005\u0006\u0000"+
		"\u0000\u020a\u020b\u0003\u01c6\u00e3\u0000\u020b\u020c\u0005\u0002\u0000"+
		"\u0000\u020c\u020d\u0003\u0016\u000b\u0000\u020d\u020e\u0005\u0002\u0000"+
		"\u0000\u020e\u0210\u0003\u00f4z\u0000\u020f\u0211\u0003\u0014\n\u0000"+
		"\u0210\u020f\u0001\u0000\u0000\u0000\u0210\u0211\u0001\u0000\u0000\u0000"+
		"\u0211\u0212\u0001\u0000\u0000\u0000\u0212\u0213\u0005\u0003\u0000\u0000"+
		"\u0213\u000f\u0001\u0000\u0000\u0000\u0214\u0215\u0005\u0007\u0000\u0000"+
		"\u0215\u0216\u0003\u01c6\u00e3\u0000\u0216\u0217\u0005\u0002\u0000\u0000"+
		"\u0217\u0218\u0003\u0016\u000b\u0000\u0218\u0219\u0005\u0002\u0000\u0000"+
		"\u0219\u021b\u0003\u00fa}\u0000\u021a\u021c\u0003\u0014\n\u0000\u021b"+
		"\u021a\u0001\u0000\u0000\u0000\u021b\u021c\u0001\u0000\u0000\u0000\u021c"+
		"\u021d\u0001\u0000\u0000\u0000\u021d\u021e\u0005\u0003\u0000\u0000\u021e"+
		"\u0011\u0001\u0000\u0000\u0000\u021f\u0220\u0005\b\u0000\u0000\u0220\u0221"+
		"\u0003\u01c6\u00e3\u0000\u0221\u0222\u0005\u0002\u0000\u0000\u0222\u0223"+
		"\u0003\u0016\u000b\u0000\u0223\u0224\u0005\u0002\u0000\u0000\u0224\u0226"+
		"\u0003\u0136\u009b\u0000\u0225\u0227\u0003\u0014\n\u0000\u0226\u0225\u0001"+
		"\u0000\u0000\u0000\u0226\u0227\u0001\u0000\u0000\u0000\u0227\u0228\u0001"+
		"\u0000\u0000\u0000\u0228\u0229\u0005\u0003\u0000\u0000\u0229\u0013\u0001"+
		"\u0000\u0000\u0000\u022a\u022b\u0005\u0002\u0000\u0000\u022b\u022d\u0003"+
		"\u0170\u00b8\u0000\u022c\u022e\u0003\u0194\u00ca\u0000\u022d\u022c\u0001"+
		"\u0000\u0000\u0000\u022d\u022e\u0001\u0000\u0000\u0000\u022e\u0015\u0001"+
		"\u0000\u0000\u0000\u022f\u0230\u0005]\u0000\u0000\u0230\u0017\u0001\u0000"+
		"\u0000\u0000\u0231\u0235\u0003\u001a\r\u0000\u0232\u0235\u0003b1\u0000"+
		"\u0233\u0235\u0003r9\u0000\u0234\u0231\u0001\u0000\u0000\u0000\u0234\u0232"+
		"\u0001\u0000\u0000\u0000\u0234\u0233\u0001\u0000\u0000\u0000\u0235\u0019"+
		"\u0001\u0000\u0000\u0000\u0236\u023d\u0003,\u0016\u0000\u0237\u023d\u0003"+
		"8\u001c\u0000\u0238\u023d\u0003\u001c\u000e\u0000\u0239\u023d\u0003F#"+
		"\u0000\u023a\u023d\u0003t:\u0000\u023b\u023d\u0003v;\u0000\u023c\u0236"+
		"\u0001\u0000\u0000\u0000\u023c\u0237\u0001\u0000\u0000\u0000\u023c\u0238"+
		"\u0001\u0000\u0000\u0000\u023c\u0239\u0001\u0000\u0000\u0000\u023c\u023a"+
		"\u0001\u0000\u0000\u0000\u023c\u023b\u0001\u0000\u0000\u0000\u023d\u001b"+
		"\u0001\u0000\u0000\u0000\u023e\u0242\u0003\u001e\u000f\u0000\u023f\u0242"+
		"\u0003 \u0010\u0000\u0240\u0242\u0003j5\u0000\u0241\u023e\u0001\u0000"+
		"\u0000\u0000\u0241\u023f\u0001\u0000\u0000\u0000\u0241\u0240\u0001\u0000"+
		"\u0000\u0000\u0242\u001d\u0001\u0000\u0000\u0000\u0243\u0244\u0003(\u0014"+
		"\u0000\u0244\u0245\u0003\u0144\u00a2\u0000\u0245\u0246\u0003(\u0014\u0000"+
		"\u0246\u001f\u0001\u0000\u0000\u0000\u0247\u024b\u0003\"\u0011\u0000\u0248"+
		"\u024b\u0003$\u0012\u0000\u0249\u024b\u0003&\u0013\u0000\u024a\u0247\u0001"+
		"\u0000\u0000\u0000\u024a\u0248\u0001\u0000\u0000\u0000\u024a\u0249\u0001"+
		"\u0000\u0000\u0000\u024b!\u0001\u0000\u0000\u0000\u024c\u024d\u0006\u0011"+
		"\uffff\uffff\u0000\u024d\u024e\u0003(\u0014\u0000\u024e\u024f\u0005)\u0000"+
		"\u0000\u024f\u0250\u0003(\u0014\u0000\u0250\u0256\u0001\u0000\u0000\u0000"+
		"\u0251\u0252\n\u0001\u0000\u0000\u0252\u0253\u0005)\u0000\u0000\u0253"+
		"\u0255\u0003(\u0014\u0000\u0254\u0251\u0001\u0000\u0000\u0000\u0255\u0258"+
		"\u0001\u0000\u0000\u0000\u0256\u0254\u0001\u0000\u0000\u0000\u0256\u0257"+
		"\u0001\u0000\u0000\u0000\u0257#\u0001\u0000\u0000\u0000\u0258\u0256\u0001"+
		"\u0000\u0000\u0000\u0259\u025a\u0006\u0012\uffff\uffff\u0000\u025a\u025b"+
		"\u0003(\u0014\u0000\u025b\u025c\u0005*\u0000\u0000\u025c\u025d\u0003("+
		"\u0014\u0000\u025d\u0263\u0001\u0000\u0000\u0000\u025e\u025f\n\u0001\u0000"+
		"\u0000\u025f\u0260\u0005*\u0000\u0000\u0260\u0262\u0003(\u0014\u0000\u0261"+
		"\u025e\u0001\u0000\u0000\u0000\u0262\u0265\u0001\u0000\u0000\u0000\u0263"+
		"\u0261\u0001\u0000\u0000\u0000\u0263\u0264\u0001\u0000\u0000\u0000\u0264"+
		"%\u0001\u0000\u0000\u0000\u0265\u0263\u0001\u0000\u0000\u0000\u0266\u0267"+
		"\u0006\u0013\uffff\uffff\u0000\u0267\u0268\u0003(\u0014\u0000\u0268\u0269"+
		"\u0005@\u0000\u0000\u0269\u026a\u0003(\u0014\u0000\u026a\u0270\u0001\u0000"+
		"\u0000\u0000\u026b\u026c\n\u0001\u0000\u0000\u026c\u026d\u0005@\u0000"+
		"\u0000\u026d\u026f\u0003(\u0014\u0000\u026e\u026b\u0001\u0000\u0000\u0000"+
		"\u026f\u0272\u0001\u0000\u0000\u0000\u0270\u026e\u0001\u0000\u0000\u0000"+
		"\u0270\u0271\u0001\u0000\u0000\u0000\u0271\'\u0001\u0000\u0000\u0000\u0272"+
		"\u0270\u0001\u0000\u0000\u0000\u0273\u0276\u0003,\u0016\u0000\u0274\u0276"+
		"\u00038\u001c\u0000\u0275\u0273\u0001\u0000\u0000\u0000\u0275\u0274\u0001"+
		"\u0000\u0000\u0000\u0276)\u0001\u0000\u0000\u0000\u0277\u027a\u0003,\u0016"+
		"\u0000\u0278\u027a\u0003:\u001d\u0000\u0279\u0277\u0001\u0000\u0000\u0000"+
		"\u0279\u0278\u0001\u0000\u0000\u0000\u027a+\u0001\u0000\u0000\u0000\u027b"+
		"\u0283\u0003.\u0017\u0000\u027c\u0283\u0003>\u001f\u0000\u027d\u0283\u0003"+
		"\u016e\u00b7\u0000\u027e\u027f\u0005\t\u0000\u0000\u027f\u0280\u0003\u001a"+
		"\r\u0000\u0280\u0281\u0005\n\u0000\u0000\u0281\u0283\u0001\u0000\u0000"+
		"\u0000\u0282\u027b\u0001\u0000\u0000\u0000\u0282\u027c\u0001\u0000\u0000"+
		"\u0000\u0282\u027d\u0001\u0000\u0000\u0000\u0282\u027e\u0001\u0000\u0000"+
		"\u0000\u0283-\u0001\u0000\u0000\u0000\u0284\u0285\u00030\u0018\u0000\u0285"+
		"\u0286\u0003,\u0016\u0000\u0286/\u0001\u0000\u0000\u0000\u0287\u0288\u0003"+
		"\u013c\u009e\u0000\u0288\u0289\u0005\u000b\u0000\u0000\u0289\u028a\u0003"+
		"2\u0019\u0000\u028a\u028b\u0005\f\u0000\u0000\u028b\u028c\u0005\r\u0000"+
		"\u0000\u028c1\u0001\u0000\u0000\u0000\u028d\u0292\u00034\u001a\u0000\u028e"+
		"\u028f\u0005\u0002\u0000\u0000\u028f\u0291\u00034\u001a\u0000\u0290\u028e"+
		"\u0001\u0000\u0000\u0000\u0291\u0294\u0001\u0000\u0000\u0000\u0292\u0290"+
		"\u0001\u0000\u0000\u0000\u0292\u0293\u0001\u0000\u0000\u0000\u02933\u0001"+
		"\u0000\u0000\u0000\u0294\u0292\u0001\u0000\u0000\u0000\u0295\u0298\u0003"+
		"6\u001b\u0000\u0296\u0298\u0003\u016e\u00b7\u0000\u0297\u0295\u0001\u0000"+
		"\u0000\u0000\u0297\u0296\u0001\u0000\u0000\u0000\u02985\u0001\u0000\u0000"+
		"\u0000\u0299\u029a\u0003\u016e\u00b7\u0000\u029a\u029b\u0005\r\u0000\u0000"+
		"\u029b\u029c\u0003d2\u0000\u029c7\u0001\u0000\u0000\u0000\u029d\u02a0"+
		"\u0003:\u001d\u0000\u029e\u02a0\u0003<\u001e\u0000\u029f\u029d\u0001\u0000"+
		"\u0000\u0000\u029f\u029e\u0001\u0000\u0000\u0000\u02a09\u0001\u0000\u0000"+
		"\u0000\u02a1\u02a2\u0003\u0148\u00a4\u0000\u02a2\u02a3\u0003*\u0015\u0000"+
		"\u02a3;\u0001\u0000\u0000\u0000\u02a4\u02a5\u0003V+\u0000\u02a5\u02a6"+
		"\u00054\u0000\u0000\u02a6\u02a7\u0003V+\u0000\u02a7=\u0001\u0000\u0000"+
		"\u0000\u02a8\u02ad\u0003@ \u0000\u02a9\u02ad\u0003B!\u0000\u02aa\u02ad"+
		"\u0003H$\u0000\u02ab\u02ad\u0003\\.\u0000\u02ac\u02a8\u0001\u0000\u0000"+
		"\u0000\u02ac\u02a9\u0001\u0000\u0000\u0000\u02ac\u02aa\u0001\u0000\u0000"+
		"\u0000\u02ac\u02ab\u0001\u0000\u0000\u0000\u02ad?\u0001\u0000\u0000\u0000"+
		"\u02ae\u02b1\u0003\u015c\u00ae\u0000\u02af\u02b1\u0003Z-\u0000\u02b0\u02ae"+
		"\u0001\u0000\u0000\u0000\u02b0\u02af\u0001\u0000\u0000\u0000\u02b1A\u0001"+
		"\u0000\u0000\u0000\u02b2\u02bb\u0003\u0160\u00b0\u0000\u02b3\u02bb\u0003"+
		"D\"\u0000\u02b4\u02b5\u0005\t\u0000\u0000\u02b5\u02b6\u0003X,\u0000\u02b6"+
		"\u02b7\u0005\n\u0000\u0000\u02b7\u02bb\u0001\u0000\u0000\u0000\u02b8\u02bb"+
		"\u0003\u00deo\u0000\u02b9\u02bb\u0003J%\u0000\u02ba\u02b2\u0001\u0000"+
		"\u0000\u0000\u02ba\u02b3\u0001\u0000\u0000\u0000\u02ba\u02b4\u0001\u0000"+
		"\u0000\u0000\u02ba\u02b8\u0001\u0000\u0000\u0000\u02ba\u02b9\u0001\u0000"+
		"\u0000\u0000\u02bbC\u0001\u0000\u0000\u0000\u02bc\u02bf\u0003\u016c\u00b6"+
		"\u0000\u02bd\u02bf\u0003\u016a\u00b5\u0000\u02be\u02bc\u0001\u0000\u0000"+
		"\u0000\u02be\u02bd\u0001\u0000\u0000\u0000\u02bfE\u0001\u0000\u0000\u0000"+
		"\u02c0\u02c1\u0003V+\u0000\u02c1\u02c2\u0003\u015a\u00ad\u0000\u02c2\u02c3"+
		"\u0003V+\u0000\u02c3G\u0001\u0000\u0000\u0000\u02c4\u02c5\u0003\u0164"+
		"\u00b2\u0000\u02c5I\u0001\u0000\u0000\u0000\u02c6\u02c7\u0005\u000e\u0000"+
		"\u0000\u02c7\u02c8\u0003L&\u0000\u02c8\u02c9\u0005\u0002\u0000\u0000\u02c9"+
		"\u02ca\u0003P(\u0000\u02ca\u02cb\u0005\u0002\u0000\u0000\u02cb\u02cc\u0003"+
		"\u001a\r\u0000\u02cc\u02cd\u0005\n\u0000\u0000\u02cdK\u0001\u0000\u0000"+
		"\u0000\u02ce\u02d4\u0003b1\u0000\u02cf\u02d0\u0005\u000b\u0000\u0000\u02d0"+
		"\u02d1\u0003N\'\u0000\u02d1\u02d2\u0005\f\u0000\u0000\u02d2\u02d4\u0001"+
		"\u0000\u0000\u0000\u02d3\u02ce\u0001\u0000\u0000\u0000\u02d3\u02cf\u0001"+
		"\u0000\u0000\u0000\u02d4M\u0001\u0000\u0000\u0000\u02d5\u02db\u0003b1"+
		"\u0000\u02d6\u02d7\u0003b1\u0000\u02d7\u02d8\u0005\u0002\u0000\u0000\u02d8"+
		"\u02d9\u0003N\'\u0000\u02d9\u02db\u0001\u0000\u0000\u0000\u02da\u02d5"+
		"\u0001\u0000\u0000\u0000\u02da\u02d6\u0001\u0000\u0000\u0000\u02dbO\u0001"+
		"\u0000\u0000\u0000\u02dc\u02e2\u0003R)\u0000\u02dd\u02de\u0005\u000b\u0000"+
		"\u0000\u02de\u02df\u0003T*\u0000\u02df\u02e0\u0005\f\u0000\u0000\u02e0"+
		"\u02e2\u0001\u0000\u0000\u0000\u02e1\u02dc\u0001\u0000\u0000\u0000\u02e1"+
		"\u02dd\u0001\u0000\u0000\u0000\u02e2Q\u0001\u0000\u0000\u0000\u02e3\u02e4"+
		"\u0003\u001a\r\u0000\u02e4\u02e5\u0005A\u0000\u0000\u02e5\u02e6\u0003"+
		"\u001a\r\u0000\u02e6S\u0001\u0000\u0000\u0000\u02e7\u02ed\u0003R)\u0000"+
		"\u02e8\u02e9\u0003R)\u0000\u02e9\u02ea\u0005\u0002\u0000\u0000\u02ea\u02eb"+
		"\u0003T*\u0000\u02eb\u02ed\u0001\u0000\u0000\u0000\u02ec\u02e7\u0001\u0000"+
		"\u0000\u0000\u02ec\u02e8\u0001\u0000\u0000\u0000\u02edU\u0001\u0000\u0000"+
		"\u0000\u02ee\u02f5\u0003>\u001f\u0000\u02ef\u02f5\u0003\u016e\u00b7\u0000"+
		"\u02f0\u02f1\u0005\t\u0000\u0000\u02f1\u02f2\u0003\u001a\r\u0000\u02f2"+
		"\u02f3\u0005\n\u0000\u0000\u02f3\u02f5\u0001\u0000\u0000\u0000\u02f4\u02ee"+
		"\u0001\u0000\u0000\u0000\u02f4\u02ef\u0001\u0000\u0000\u0000\u02f4\u02f0"+
		"\u0001\u0000\u0000\u0000\u02f5W\u0001\u0000\u0000\u0000\u02f6\u02fc\u0003"+
		"\u0144\u00a2\u0000\u02f7\u02fc\u0003\u0146\u00a3\u0000\u02f8\u02fc\u0005"+
		"5\u0000\u0000\u02f9\u02fc\u00054\u0000\u0000\u02fa\u02fc\u0003\u0148\u00a4"+
		"\u0000\u02fb\u02f6\u0001\u0000\u0000\u0000\u02fb\u02f7\u0001\u0000\u0000"+
		"\u0000\u02fb\u02f8\u0001\u0000\u0000\u0000\u02fb\u02f9\u0001\u0000\u0000"+
		"\u0000\u02fb\u02fa\u0001\u0000\u0000\u0000\u02fcY\u0001\u0000\u0000\u0000"+
		"\u02fd\u0303\u0005\u000f\u0000\u0000\u02fe\u02ff\u0005\u000b\u0000\u0000"+
		"\u02ff\u0300\u0003`0\u0000\u0300\u0301\u0005\f\u0000\u0000\u0301\u0303"+
		"\u0001\u0000\u0000\u0000\u0302\u02fd\u0001\u0000\u0000\u0000\u0302\u02fe"+
		"\u0001\u0000\u0000\u0000\u0303[\u0001\u0000\u0000\u0000\u0304\u0305\u0003"+
		"\u015e\u00af\u0000\u0305\u0306\u0005\t\u0000\u0000\u0306\u0307\u0003^"+
		"/\u0000\u0307\u0308\u0005\n\u0000\u0000\u0308\u0314\u0001\u0000\u0000"+
		"\u0000\u0309\u030a\u0003\u0162\u00b1\u0000\u030a\u030b\u0005\t\u0000\u0000"+
		"\u030b\u030c\u0003^/\u0000\u030c\u030d\u0005\n\u0000\u0000\u030d\u0314"+
		"\u0001\u0000\u0000\u0000\u030e\u030f\u0003\u0166\u00b3\u0000\u030f\u0310"+
		"\u0005\t\u0000\u0000\u0310\u0311\u0003^/\u0000\u0311\u0312\u0005\n\u0000"+
		"\u0000\u0312\u0314\u0001\u0000\u0000\u0000\u0313\u0304\u0001\u0000\u0000"+
		"\u0000\u0313\u0309\u0001\u0000\u0000\u0000\u0313\u030e\u0001\u0000\u0000"+
		"\u0000\u0314]\u0001\u0000\u0000\u0000\u0315\u0316\u0003`0\u0000\u0316"+
		"_\u0001\u0000\u0000\u0000\u0317\u031d\u0003\u001a\r\u0000\u0318\u0319"+
		"\u0003\u001a\r\u0000\u0319\u031a\u0005\u0002\u0000\u0000\u031a\u031b\u0003"+
		"`0\u0000\u031b\u031d\u0001\u0000\u0000\u0000\u031c\u0317\u0001\u0000\u0000"+
		"\u0000\u031c\u0318\u0001\u0000\u0000\u0000\u031da\u0001\u0000\u0000\u0000"+
		"\u031e\u031f\u0003\u0154\u00aa\u0000\u031f\u0320\u0005\r\u0000\u0000\u0320"+
		"\u0321\u0003d2\u0000\u0321\u0327\u0001\u0000\u0000\u0000\u0322\u0323\u0005"+
		"\t\u0000\u0000\u0323\u0324\u0003b1\u0000\u0324\u0325\u0005\n\u0000\u0000"+
		"\u0325\u0327\u0001\u0000\u0000\u0000\u0326\u031e\u0001\u0000\u0000\u0000"+
		"\u0326\u0322\u0001\u0000\u0000\u0000\u0327c\u0001\u0000\u0000\u0000\u0328"+
		"\u032c\u0003f3\u0000\u0329\u032c\u0003l6\u0000\u032a\u032c\u0003h4\u0000"+
		"\u032b\u0328\u0001\u0000\u0000\u0000\u032b\u0329\u0001\u0000\u0000\u0000"+
		"\u032b\u032a\u0001\u0000\u0000\u0000\u032ce\u0001\u0000\u0000\u0000\u032d"+
		"\u032e\u0003,\u0016\u0000\u032eg\u0001\u0000\u0000\u0000\u032f\u0330\u0003"+
		"&\u0013\u0000\u0330i\u0001\u0000\u0000\u0000\u0331\u0335\u0003l6\u0000"+
		"\u0332\u0335\u0003n7\u0000\u0333\u0335\u0003p8\u0000\u0334\u0331\u0001"+
		"\u0000\u0000\u0000\u0334\u0332\u0001\u0000\u0000\u0000\u0334\u0333\u0001"+
		"\u0000\u0000\u0000\u0335k\u0001\u0000\u0000\u0000\u0336\u0337\u0003f3"+
		"\u0000\u0337\u0338\u0005C\u0000\u0000\u0338\u0339\u0003f3\u0000\u0339"+
		"\u033f\u0001\u0000\u0000\u0000\u033a\u033b\u0003f3\u0000\u033b\u033c\u0005"+
		"C\u0000\u0000\u033c\u033d\u0003l6\u0000\u033d\u033f\u0001\u0000\u0000"+
		"\u0000\u033e\u0336\u0001\u0000\u0000\u0000\u033e\u033a\u0001\u0000\u0000"+
		"\u0000\u033fm\u0001\u0000\u0000\u0000\u0340\u0341\u00067\uffff\uffff\u0000"+
		"\u0341\u0342\u0003f3\u0000\u0342\u0343\u0005D\u0000\u0000\u0343\u0344"+
		"\u0003f3\u0000\u0344\u034a\u0001\u0000\u0000\u0000\u0345\u0346\n\u0001"+
		"\u0000\u0000\u0346\u0347\u0005D\u0000\u0000\u0347\u0349\u0003f3\u0000"+
		"\u0348\u0345\u0001\u0000\u0000\u0000\u0349\u034c\u0001\u0000\u0000\u0000"+
		"\u034a\u0348\u0001\u0000\u0000\u0000\u034a\u034b\u0001\u0000\u0000\u0000"+
		"\u034bo\u0001\u0000\u0000\u0000\u034c\u034a\u0001\u0000\u0000\u0000\u034d"+
		"\u034e\u00068\uffff\uffff\u0000\u034e\u034f\u0003f3\u0000\u034f\u0350"+
		"\u0005E\u0000\u0000\u0350\u0351\u0003f3\u0000\u0351\u0357\u0001\u0000"+
		"\u0000\u0000\u0352\u0353\n\u0001\u0000\u0000\u0353\u0354\u0005E\u0000"+
		"\u0000\u0354\u0356\u0003f3\u0000\u0355\u0352\u0001\u0000\u0000\u0000\u0356"+
		"\u0359\u0001\u0000\u0000\u0000\u0357\u0355\u0001\u0000\u0000\u0000\u0357"+
		"\u0358\u0001\u0000\u0000\u0000\u0358q\u0001\u0000\u0000\u0000\u0359\u0357"+
		"\u0001\u0000\u0000\u0000\u035a\u035b\u0003\u0154\u00aa\u0000\u035b\u035c"+
		"\u0005G\u0000\u0000\u035c\u035d\u0003\u0152\u00a9\u0000\u035ds\u0001\u0000"+
		"\u0000\u0000\u035e\u035f\u0003>\u001f\u0000\u035f\u0360\u0005B\u0000\u0000"+
		"\u0360\u0361\u0003\u001a\r\u0000\u0361u\u0001\u0000\u0000\u0000\u0362"+
		"\u0363\u0003Z-\u0000\u0363\u0364\u0005H\u0000\u0000\u0364\u0365\u0003"+
		"Z-\u0000\u0365w\u0001\u0000\u0000\u0000\u0366\u036a\u0003z=\u0000\u0367"+
		"\u036a\u0003\u00c0`\u0000\u0368\u036a\u0003\u00d8l\u0000\u0369\u0366\u0001"+
		"\u0000\u0000\u0000\u0369\u0367\u0001\u0000\u0000\u0000\u0369\u0368\u0001"+
		"\u0000\u0000\u0000\u036ay\u0001\u0000\u0000\u0000\u036b\u0372\u0003\u008a"+
		"E\u0000\u036c\u0372\u0003\u0096K\u0000\u036d\u0372\u0003|>\u0000\u036e"+
		"\u0372\u0003\u00a4R\u0000\u036f\u0372\u0003\u00dam\u0000\u0370\u0372\u0003"+
		"\u00dcn\u0000\u0371\u036b\u0001\u0000\u0000\u0000\u0371\u036c\u0001\u0000"+
		"\u0000\u0000\u0371\u036d\u0001\u0000\u0000\u0000\u0371\u036e\u0001\u0000"+
		"\u0000\u0000\u0371\u036f\u0001\u0000\u0000\u0000\u0371\u0370\u0001\u0000"+
		"\u0000\u0000\u0372{\u0001\u0000\u0000\u0000\u0373\u0376\u0003~?\u0000"+
		"\u0374\u0376\u0003\u0080@\u0000\u0375\u0373\u0001\u0000\u0000\u0000\u0375"+
		"\u0374\u0001\u0000\u0000\u0000\u0376}\u0001\u0000\u0000\u0000\u0377\u0378"+
		"\u0003\u0086C\u0000\u0378\u0379\u0003\u0144\u00a2\u0000\u0379\u037a\u0003"+
		"\u0086C\u0000\u037a\u007f\u0001\u0000\u0000\u0000\u037b\u037e\u0003\u0082"+
		"A\u0000\u037c\u037e\u0003\u0084B\u0000\u037d\u037b\u0001\u0000\u0000\u0000"+
		"\u037d\u037c\u0001\u0000\u0000\u0000\u037e\u0081\u0001\u0000\u0000\u0000"+
		"\u037f\u0380\u0006A\uffff\uffff\u0000\u0380\u0381\u0003\u0086C\u0000\u0381"+
		"\u0382\u0005)\u0000\u0000\u0382\u0383\u0003\u0086C\u0000\u0383\u0389\u0001"+
		"\u0000\u0000\u0000\u0384\u0385\n\u0001\u0000\u0000\u0385\u0386\u0005)"+
		"\u0000\u0000\u0386\u0388\u0003\u0086C\u0000\u0387\u0384\u0001\u0000\u0000"+
		"\u0000\u0388\u038b\u0001\u0000\u0000\u0000\u0389\u0387\u0001\u0000\u0000"+
		"\u0000\u0389\u038a\u0001\u0000\u0000\u0000\u038a\u0083\u0001\u0000\u0000"+
		"\u0000\u038b\u0389\u0001\u0000\u0000\u0000\u038c\u038d\u0006B\uffff\uffff"+
		"\u0000\u038d\u038e\u0003\u0086C\u0000\u038e\u038f\u0005*\u0000\u0000\u038f"+
		"\u0390\u0003\u0086C\u0000\u0390\u0396\u0001\u0000\u0000\u0000\u0391\u0392"+
		"\n\u0001\u0000\u0000\u0392\u0393\u0005*\u0000\u0000\u0393\u0395\u0003"+
		"\u0086C\u0000\u0394\u0391\u0001\u0000\u0000\u0000\u0395\u0398\u0001\u0000"+
		"\u0000\u0000\u0396\u0394\u0001\u0000\u0000\u0000\u0396\u0397\u0001\u0000"+
		"\u0000\u0000\u0397\u0085\u0001\u0000\u0000\u0000\u0398\u0396\u0001\u0000"+
		"\u0000\u0000\u0399\u039d\u0003\u008aE\u0000\u039a\u039d\u0003\u0096K\u0000"+
		"\u039b\u039d\u0003\u00a4R\u0000\u039c\u0399\u0001\u0000\u0000\u0000\u039c"+
		"\u039a\u0001\u0000\u0000\u0000\u039c\u039b\u0001\u0000\u0000\u0000\u039d"+
		"\u0087\u0001\u0000\u0000\u0000\u039e\u03a1\u0003\u008aE\u0000\u039f\u03a1"+
		"\u0003\u0098L\u0000\u03a0\u039e\u0001\u0000\u0000\u0000\u03a0\u039f\u0001"+
		"\u0000\u0000\u0000\u03a1\u0089\u0001\u0000\u0000\u0000\u03a2\u03aa\u0003"+
		"\u008eG\u0000\u03a3\u03aa\u0003\u009cN\u0000\u03a4\u03aa\u0003\u008cF"+
		"\u0000\u03a5\u03a6\u0005\t\u0000\u0000\u03a6\u03a7\u0003z=\u0000\u03a7"+
		"\u03a8\u0005\n\u0000\u0000\u03a8\u03aa\u0001\u0000\u0000\u0000\u03a9\u03a2"+
		"\u0001\u0000\u0000\u0000\u03a9\u03a3\u0001\u0000\u0000\u0000\u03a9\u03a4"+
		"\u0001\u0000\u0000\u0000\u03a9\u03a5\u0001\u0000\u0000\u0000\u03aa\u008b"+
		"\u0001\u0000\u0000\u0000\u03ab\u03ac\u0003\u016e\u00b7\u0000\u03ac\u008d"+
		"\u0001\u0000\u0000\u0000\u03ad\u03ae\u0003\u0142\u00a1\u0000\u03ae\u03af"+
		"\u0005\u000b\u0000\u0000\u03af\u03b0\u0003\u0090H\u0000\u03b0\u03b1\u0005"+
		"\f\u0000\u0000\u03b1\u03b2\u0005\r\u0000\u0000\u03b2\u03b3\u0003\u0086"+
		"C\u0000\u03b3\u008f\u0001\u0000\u0000\u0000\u03b4\u03ba\u0003\u0092I\u0000"+
		"\u03b5\u03b6\u0003\u0092I\u0000\u03b6\u03b7\u0005\u0002\u0000\u0000\u03b7"+
		"\u03b8\u0003\u0090H\u0000\u03b8\u03ba\u0001\u0000\u0000\u0000\u03b9\u03b4"+
		"\u0001\u0000\u0000\u0000\u03b9\u03b5\u0001\u0000\u0000\u0000\u03ba\u0091"+
		"\u0001\u0000\u0000\u0000\u03bb\u03be\u0003\u0094J\u0000\u03bc\u03be\u0003"+
		"\u016e\u00b7\u0000\u03bd\u03bb\u0001\u0000\u0000\u0000\u03bd\u03bc\u0001"+
		"\u0000\u0000\u0000\u03be\u0093\u0001\u0000\u0000\u0000\u03bf\u03c0\u0003"+
		"\u016e\u00b7\u0000\u03c0\u03c1\u0005\r\u0000\u0000\u03c1\u03c2\u0003\u00cc"+
		"f\u0000\u03c2\u0095\u0001\u0000\u0000\u0000\u03c3\u03c6\u0003\u0098L\u0000"+
		"\u03c4\u03c6\u0003\u009aM\u0000\u03c5\u03c3\u0001\u0000\u0000\u0000\u03c5"+
		"\u03c4\u0001\u0000\u0000\u0000\u03c6\u0097\u0001\u0000\u0000\u0000\u03c7"+
		"\u03c8\u0003\u0148\u00a4\u0000\u03c8\u03c9\u0003\u0088D\u0000\u03c9\u0099"+
		"\u0001\u0000\u0000\u0000\u03ca\u03cb\u0003\u00ba]\u0000\u03cb\u03cc\u0005"+
		"4\u0000\u0000\u03cc\u03cd\u0003\u00ba]\u0000\u03cd\u009b\u0001\u0000\u0000"+
		"\u0000\u03ce\u03d2\u0003\u009eO\u0000\u03cf\u03d2\u0003\u00a0P\u0000\u03d0"+
		"\u03d2\u0003\u00a6S\u0000\u03d1\u03ce\u0001\u0000\u0000\u0000\u03d1\u03cf"+
		"\u0001\u0000\u0000\u0000\u03d1\u03d0\u0001\u0000\u0000\u0000\u03d2\u009d"+
		"\u0001\u0000\u0000\u0000\u03d3\u03da\u0003\u015c\u00ae\u0000\u03d4\u03d5"+
		"\u0003\u015e\u00af\u0000\u03d5\u03d6\u0005\t\u0000\u0000\u03d6\u03d7\u0003"+
		"\u00be_\u0000\u03d7\u03d8\u0005\n\u0000\u0000\u03d8\u03da\u0001\u0000"+
		"\u0000\u0000\u03d9\u03d3\u0001\u0000\u0000\u0000\u03d9\u03d4\u0001\u0000"+
		"\u0000\u0000\u03da\u009f\u0001\u0000\u0000\u0000\u03db\u03de\u0003\u00a2"+
		"Q\u0000\u03dc\u03de\u0003\u00deo\u0000\u03dd\u03db\u0001\u0000\u0000\u0000"+
		"\u03dd\u03dc\u0001\u0000\u0000\u0000\u03de\u00a1\u0001\u0000\u0000\u0000"+
		"\u03df\u03e8\u0003\u0160\u00b0\u0000\u03e0\u03e1\u0003\u0162\u00b1\u0000"+
		"\u03e1\u03e2\u0005\t\u0000\u0000\u03e2\u03e3\u0003\u00be_\u0000\u03e3"+
		"\u03e4\u0005\n\u0000\u0000\u03e4\u03e8\u0001\u0000\u0000\u0000\u03e5\u03e8"+
		"\u0003\u00b6[\u0000\u03e6\u03e8\u0003\u00a8T\u0000\u03e7\u03df\u0001\u0000"+
		"\u0000\u0000\u03e7\u03e0\u0001\u0000\u0000\u0000\u03e7\u03e5\u0001\u0000"+
		"\u0000\u0000\u03e7\u03e6\u0001\u0000\u0000\u0000\u03e8\u00a3\u0001\u0000"+
		"\u0000\u0000\u03e9\u03ea\u0003\u00ba]\u0000\u03ea\u03eb\u0003\u015a\u00ad"+
		"\u0000\u03eb\u03ec\u0003\u00ba]\u0000\u03ec\u00a5\u0001\u0000\u0000\u0000"+
		"\u03ed\u03f4\u0003\u0164\u00b2\u0000\u03ee\u03ef\u0003\u0166\u00b3\u0000"+
		"\u03ef\u03f0\u0005\t\u0000\u0000\u03f0\u03f1\u0003\u00be_\u0000\u03f1"+
		"\u03f2\u0005\n\u0000\u0000\u03f2\u03f4\u0001\u0000\u0000\u0000\u03f3\u03ed"+
		"\u0001\u0000\u0000\u0000\u03f3\u03ee\u0001\u0000\u0000\u0000\u03f4\u00a7"+
		"\u0001\u0000\u0000\u0000\u03f5\u03f6\u0005\u000e\u0000\u0000\u03f6\u03f7"+
		"\u0003\u00aaU\u0000\u03f7\u03f8\u0005\u0002\u0000\u0000\u03f8\u03f9\u0003"+
		"\u00aeW\u0000\u03f9\u03fa\u0005\u0002\u0000\u0000\u03fa\u03fb\u0003\u00b8"+
		"\\\u0000\u03fb\u03fc\u0005\n\u0000\u0000\u03fc\u00a9\u0001\u0000\u0000"+
		"\u0000\u03fd\u0403\u0003\u00c0`\u0000\u03fe\u03ff\u0005\u000b\u0000\u0000"+
		"\u03ff\u0400\u0003\u00acV\u0000\u0400\u0401\u0005\f\u0000\u0000\u0401"+
		"\u0403\u0001\u0000\u0000\u0000\u0402\u03fd\u0001\u0000\u0000\u0000\u0402"+
		"\u03fe\u0001\u0000\u0000\u0000\u0403\u00ab\u0001\u0000\u0000\u0000\u0404"+
		"\u040a\u0003\u00c0`\u0000\u0405\u0406\u0003\u00c0`\u0000\u0406\u0407\u0005"+
		"\u0002\u0000\u0000\u0407\u0408\u0003\u00acV\u0000\u0408\u040a\u0001\u0000"+
		"\u0000\u0000\u0409\u0404\u0001\u0000\u0000\u0000\u0409\u0405\u0001\u0000"+
		"\u0000\u0000\u040a\u00ad\u0001\u0000\u0000\u0000\u040b\u0411\u0003\u00b0"+
		"X\u0000\u040c\u040d\u0005\u000b\u0000\u0000\u040d\u040e\u0003\u00b4Z\u0000"+
		"\u040e\u040f\u0005\f\u0000\u0000\u040f\u0411\u0001\u0000\u0000\u0000\u0410"+
		"\u040b\u0001\u0000\u0000\u0000\u0410\u040c\u0001\u0000\u0000\u0000\u0411"+
		"\u00af\u0001\u0000\u0000\u0000\u0412\u0413\u0003\u00b2Y\u0000\u0413\u0414"+
		"\u0005A\u0000\u0000\u0414\u0415\u0003\u00b8\\\u0000\u0415\u00b1\u0001"+
		"\u0000\u0000\u0000\u0416\u0419\u0003\u009eO\u0000\u0417\u0419\u0003\u00bc"+
		"^\u0000\u0418\u0416\u0001\u0000\u0000\u0000\u0418\u0417\u0001\u0000\u0000"+
		"\u0000\u0419\u00b3\u0001\u0000\u0000\u0000\u041a\u0420\u0003\u00b0X\u0000"+
		"\u041b\u041c\u0003\u00b0X\u0000\u041c\u041d\u0005\u0002\u0000\u0000\u041d"+
		"\u041e\u0003\u00b4Z\u0000\u041e\u0420\u0001\u0000\u0000\u0000\u041f\u041a"+
		"\u0001\u0000\u0000\u0000\u041f\u041b\u0001\u0000\u0000\u0000\u0420\u00b5"+
		"\u0001\u0000\u0000\u0000\u0421\u0422\u0003\u00deo\u0000\u0422\u0423\u0005"+
		"@\u0000\u0000\u0423\u0424\u0005\t\u0000\u0000\u0424\u0425\u0003\u00be"+
		"_\u0000\u0425\u0426\u0005\n\u0000\u0000\u0426\u00b7\u0001\u0000\u0000"+
		"\u0000\u0427\u042c\u0003z=\u0000\u0428\u042c\u0003\u016c\u00b6\u0000\u0429"+
		"\u042c\u0003\u00bc^\u0000\u042a\u042c\u0003\u00ecv\u0000\u042b\u0427\u0001"+
		"\u0000\u0000\u0000\u042b\u0428\u0001\u0000\u0000\u0000\u042b\u0429\u0001"+
		"\u0000\u0000\u0000\u042b\u042a\u0001\u0000\u0000\u0000\u042c\u00b9\u0001"+
		"\u0000\u0000\u0000\u042d\u0436\u0003\u009cN\u0000\u042e\u0436\u0003\u016c"+
		"\u00b6\u0000\u042f\u0436\u0003\u00bc^\u0000\u0430\u0436\u0003\u016e\u00b7"+
		"\u0000\u0431\u0432\u0005\t\u0000\u0000\u0432\u0433\u0003z=\u0000\u0433"+
		"\u0434\u0005\n\u0000\u0000\u0434\u0436\u0001\u0000\u0000\u0000\u0435\u042d"+
		"\u0001\u0000\u0000\u0000\u0435\u042e\u0001\u0000\u0000\u0000\u0435\u042f"+
		"\u0001\u0000\u0000\u0000\u0435\u0430\u0001\u0000\u0000\u0000\u0435\u0431"+
		"\u0001\u0000\u0000\u0000\u0436\u00bb\u0001\u0000\u0000\u0000\u0437\u043d"+
		"\u0005\u000f\u0000\u0000\u0438\u0439\u0005\u000b\u0000\u0000\u0439\u043a"+
		"\u0003\u00be_\u0000\u043a\u043b\u0005\f\u0000\u0000\u043b\u043d\u0001"+
		"\u0000\u0000\u0000\u043c\u0437\u0001\u0000\u0000\u0000\u043c\u0438\u0001"+
		"\u0000\u0000\u0000\u043d\u00bd\u0001\u0000\u0000\u0000\u043e\u0444\u0003"+
		"\u00b8\\\u0000\u043f\u0440\u0003\u00b8\\\u0000\u0440\u0441\u0005\u0002"+
		"\u0000\u0000\u0441\u0442\u0003\u00be_\u0000\u0442\u0444\u0001\u0000\u0000"+
		"\u0000\u0443\u043e\u0001\u0000\u0000\u0000\u0443\u043f\u0001\u0000\u0000"+
		"\u0000\u0444\u00bf\u0001\u0000\u0000\u0000\u0445\u0446\u0003\u0154\u00aa"+
		"\u0000\u0446\u0447\u0005\r\u0000\u0000\u0447\u0448\u0003\u00c2a\u0000"+
		"\u0448\u044e\u0001\u0000\u0000\u0000\u0449\u044a\u0005\t\u0000\u0000\u044a"+
		"\u044b\u0003\u00c0`\u0000\u044b\u044c\u0005\n\u0000\u0000\u044c\u044e"+
		"\u0001\u0000\u0000\u0000\u044d\u0445\u0001\u0000\u0000\u0000\u044d\u0449"+
		"\u0001\u0000\u0000\u0000\u044e\u00c1\u0001\u0000\u0000\u0000\u044f\u0452"+
		"\u0003\u00ccf\u0000\u0450\u0452\u0003\u00c4b\u0000\u0451\u044f\u0001\u0000"+
		"\u0000\u0000\u0451\u0450\u0001\u0000\u0000\u0000\u0452\u00c3\u0001\u0000"+
		"\u0000\u0000\u0453\u045a\u0003\u00d0h\u0000\u0454\u045a\u0001\u0000\u0000"+
		"\u0000\u0455\u0456\u0005\t\u0000\u0000\u0456\u0457\u0003\u00c4b\u0000"+
		"\u0457\u0458\u0005\n\u0000\u0000\u0458\u045a\u0001\u0000\u0000\u0000\u0459"+
		"\u0453\u0001\u0000\u0000\u0000\u0459\u0454\u0001\u0000\u0000\u0000\u0459"+
		"\u0455\u0001\u0000\u0000\u0000\u045a\u00c5\u0001\u0000\u0000\u0000\u045b"+
		"\u045c\u00053\u0000\u0000\u045c\u045d\u0005\u000b\u0000\u0000\u045d\u045e"+
		"\u0003\u0090H\u0000\u045e\u045f\u0005\f\u0000\u0000\u045f\u0460\u0005"+
		"\r\u0000\u0000\u0460\u0461\u0003\u00c8d\u0000\u0461\u00c7\u0001\u0000"+
		"\u0000\u0000\u0462\u0469\u0003\u00ccf\u0000\u0463\u0464\u0005\t\u0000"+
		"\u0000\u0464\u0465\u0003\u00d0h\u0000\u0465\u0466\u0005\n\u0000\u0000"+
		"\u0466\u0469\u0001\u0000\u0000\u0000\u0467\u0469\u0003\u00c6c\u0000\u0468"+
		"\u0462\u0001\u0000\u0000\u0000\u0468\u0463\u0001\u0000\u0000\u0000\u0468"+
		"\u0467\u0001\u0000\u0000\u0000\u0469\u00c9\u0001\u0000\u0000\u0000\u046a"+
		"\u0470\u0003\u00ccf\u0000\u046b\u046c\u0005\t\u0000\u0000\u046c\u046d"+
		"\u0003\u00d2i\u0000\u046d\u046e\u0005\n\u0000\u0000\u046e\u0470\u0001"+
		"\u0000\u0000\u0000\u046f\u046a\u0001\u0000\u0000\u0000\u046f\u046b\u0001"+
		"\u0000\u0000\u0000\u0470\u00cb\u0001\u0000\u0000\u0000\u0471\u047f\u0003"+
		"\u014a\u00a5\u0000\u0472\u047f\u0003\u014e\u00a7\u0000\u0473\u047f\u0003"+
		"\u016e\u00b7\u0000\u0474\u0475\u0003\u014c\u00a6\u0000\u0475\u0476\u0005"+
		"\t\u0000\u0000\u0476\u0477\u0003\u00ceg\u0000\u0477\u0478\u0005\n\u0000"+
		"\u0000\u0478\u047f\u0001\u0000\u0000\u0000\u0479\u047a\u0005\t\u0000\u0000"+
		"\u047a\u047b\u0003\u00ccf\u0000\u047b\u047c\u0005\n\u0000\u0000\u047c"+
		"\u047f\u0001\u0000\u0000\u0000\u047d\u047f\u0003\u00d4j\u0000\u047e\u0471"+
		"\u0001\u0000\u0000\u0000\u047e\u0472\u0001\u0000\u0000\u0000\u047e\u0473"+
		"\u0001\u0000\u0000\u0000\u047e\u0474\u0001\u0000\u0000\u0000\u047e\u0479"+
		"\u0001\u0000\u0000\u0000\u047e\u047d\u0001\u0000\u0000\u0000\u047f\u00cd"+
		"\u0001\u0000\u0000\u0000\u0480\u0486\u0003\u00ccf\u0000\u0481\u0482\u0003"+
		"\u00ccf\u0000\u0482\u0483\u0005\u0002\u0000\u0000\u0483\u0484\u0003\u00ce"+
		"g\u0000\u0484\u0486\u0001\u0000\u0000\u0000\u0485\u0480\u0001\u0000\u0000"+
		"\u0000\u0485\u0481\u0001\u0000\u0000\u0000\u0486\u00cf\u0001\u0000\u0000"+
		"\u0000\u0487\u0488\u0003\u00cae\u0000\u0488\u0489\u0005C\u0000\u0000\u0489"+
		"\u048a\u0003\u00ccf\u0000\u048a\u00d1\u0001\u0000\u0000\u0000\u048b\u048c"+
		"\u0006i\uffff\uffff\u0000\u048c\u048d\u0003\u00cae\u0000\u048d\u048e\u0005"+
		"D\u0000\u0000\u048e\u048f\u0003\u00ccf\u0000\u048f\u0495\u0001\u0000\u0000"+
		"\u0000\u0490\u0491\n\u0001\u0000\u0000\u0491\u0492\u0005D\u0000\u0000"+
		"\u0492\u0494\u0003\u00ccf\u0000\u0493\u0490\u0001\u0000\u0000\u0000\u0494"+
		"\u0497\u0001\u0000\u0000\u0000\u0495\u0493\u0001\u0000\u0000\u0000\u0495"+
		"\u0496\u0001\u0000\u0000\u0000\u0496\u00d3\u0001\u0000\u0000\u0000\u0497"+
		"\u0495\u0001\u0000\u0000\u0000\u0498\u0499\u0005\u000b\u0000\u0000\u0499"+
		"\u049a\u0003\u00d6k\u0000\u049a\u049b\u0005\f\u0000\u0000\u049b\u00d5"+
		"\u0001\u0000\u0000\u0000\u049c\u04a2\u0003\u00c2a\u0000\u049d\u049e\u0003"+
		"\u00c2a\u0000\u049e\u049f\u0005\u0002\u0000\u0000\u049f\u04a0\u0003\u00d6"+
		"k\u0000\u04a0\u04a2\u0001\u0000\u0000\u0000\u04a1\u049c\u0001\u0000\u0000"+
		"\u0000\u04a1\u049d\u0001\u0000\u0000\u0000\u04a2\u00d7\u0001\u0000\u0000"+
		"\u0000\u04a3\u04a4\u0003\u0154\u00aa\u0000\u04a4\u04a5\u0005G\u0000\u0000"+
		"\u04a5\u04a6\u0003\u0152\u00a9\u0000\u04a6\u00d9\u0001\u0000\u0000\u0000"+
		"\u04a7\u04a8\u0003\u009cN\u0000\u04a8\u04a9\u0005B\u0000\u0000\u04a9\u04aa"+
		"\u0003\u00b8\\\u0000\u04aa\u00db\u0001\u0000\u0000\u0000\u04ab\u04ac\u0003"+
		"\u00bc^\u0000\u04ac\u04ad\u0005H\u0000\u0000\u04ad\u04ae\u0003\u00bc^"+
		"\u0000\u04ae\u00dd\u0001\u0000\u0000\u0000\u04af\u04b2\u0003\u00e0p\u0000"+
		"\u04b0\u04b2\u0003\u00e2q\u0000\u04b1\u04af\u0001\u0000\u0000\u0000\u04b1"+
		"\u04b0\u0001\u0000\u0000\u0000\u04b2\u00df\u0001\u0000\u0000\u0000\u04b3"+
		"\u04c3\u0005\u0010\u0000\u0000\u04b4\u04c3\u0005\u0011\u0000\u0000\u04b5"+
		"\u04c3\u0005\u0012\u0000\u0000\u04b6\u04b7\u0005\u000b\u0000\u0000\u04b7"+
		"\u04b8\u0003\u00eau\u0000\u04b8\u04b9\u0005\f\u0000\u0000\u04b9\u04c3"+
		"\u0001\u0000\u0000\u0000\u04ba\u04bb\u0005\u0013\u0000\u0000\u04bb\u04bc"+
		"\u0003\u00eau\u0000\u04bc\u04bd\u0005C\u0000\u0000\u04bd\u04c3\u0001\u0000"+
		"\u0000\u0000\u04be\u04bf\u0005\u0014\u0000\u0000\u04bf\u04c0\u0003\u00ea"+
		"u\u0000\u04c0\u04c1\u0005\u0015\u0000\u0000\u04c1\u04c3\u0001\u0000\u0000"+
		"\u0000\u04c2\u04b3\u0001\u0000\u0000\u0000\u04c2\u04b4\u0001\u0000\u0000"+
		"\u0000\u04c2\u04b5\u0001\u0000\u0000\u0000\u04c2\u04b6\u0001\u0000\u0000"+
		"\u0000\u04c2\u04ba\u0001\u0000\u0000\u0000\u04c2\u04be\u0001\u0000\u0000"+
		"\u0000\u04c3\u00e1\u0001\u0000\u0000\u0000\u04c4\u04c5\u0005\u0014\u0000"+
		"\u0000\u04c5\u04c6\u0003\u00e4r\u0000\u04c6\u04c7\u0005\u0015\u0000\u0000"+
		"\u04c7\u04cf\u0001\u0000\u0000\u0000\u04c8\u04c9\u0005\u0014\u0000\u0000"+
		"\u04c9\u04ca\u0003\u00e4r\u0000\u04ca\u04cb\u0005\t\u0000\u0000\u04cb"+
		"\u04cc\u0003\u00e6s\u0000\u04cc\u04cd\u0005\u0016\u0000\u0000\u04cd\u04cf"+
		"\u0001\u0000\u0000\u0000\u04ce\u04c4\u0001\u0000\u0000\u0000\u04ce\u04c8"+
		"\u0001\u0000\u0000\u0000\u04cf\u00e3\u0001\u0000\u0000\u0000\u04d0\u04d1"+
		"\u0003\u0168\u00b4\u0000\u04d1\u00e5\u0001\u0000\u0000\u0000\u04d2\u04d8"+
		"\u0003\u00e8t\u0000\u04d3\u04d4\u0003\u00e8t\u0000\u04d4\u04d5\u0005\u0002"+
		"\u0000\u0000\u04d5\u04d6\u0003\u00e6s\u0000\u04d6\u04d8\u0001\u0000\u0000"+
		"\u0000\u04d7\u04d2\u0001\u0000\u0000\u0000\u04d7\u04d3\u0001\u0000\u0000"+
		"\u0000\u04d8\u00e7\u0001\u0000\u0000\u0000\u04d9\u04dc\u0003\u00eau\u0000"+
		"\u04da\u04dc\u0003\u00ecv\u0000\u04db\u04d9\u0001\u0000\u0000\u0000\u04db"+
		"\u04da\u0001\u0000\u0000\u0000\u04dc\u00e9\u0001\u0000\u0000\u0000\u04dd"+
		"\u04de\u0005F\u0000\u0000\u04de\u04df\u0003\u00ba]\u0000\u04df\u00eb\u0001"+
		"\u0000\u0000\u0000\u04e0\u04e1\u0003\u0168\u00b4\u0000\u04e1\u04e2\u0005"+
		"A\u0000\u0000\u04e2\u04e3\u0003\u00ba]\u0000\u04e3\u00ed\u0001\u0000\u0000"+
		"\u0000\u04e4\u04e5\u0003\u00f0x\u0000\u04e5\u04e6\u0005B\u0000\u0000\u04e6"+
		"\u04e7\u0003\u00f2y\u0000\u04e7\u00ef\u0001\u0000\u0000\u0000\u04e8\u04e9"+
		"\u0003\u0160\u00b0\u0000\u04e9\u00f1\u0001\u0000\u0000\u0000\u04ea\u04ed"+
		"\u0003\u0160\u00b0\u0000\u04eb\u04ed\u0003\u00bc^\u0000\u04ec\u04ea\u0001"+
		"\u0000\u0000\u0000\u04ec\u04eb\u0001\u0000\u0000\u0000\u04ed\u00f3\u0001"+
		"\u0000\u0000\u0000\u04ee\u04f1\u0003\u00f6{\u0000\u04ef\u04f1\u0003\u00c0"+
		"`\u0000\u04f0\u04ee\u0001\u0000\u0000\u0000\u04f0\u04ef\u0001\u0000\u0000"+
		"\u0000\u04f1\u00f5\u0001\u0000\u0000\u0000\u04f2\u04f5\u0003\u00f8|\u0000"+
		"\u04f3\u04f5\u0003\u0136\u009b\u0000\u04f4\u04f2\u0001\u0000\u0000\u0000"+
		"\u04f4\u04f3\u0001\u0000\u0000\u0000\u04f5\u00f7\u0001\u0000\u0000\u0000"+
		"\u04f6\u04f7\u00056\u0000\u0000\u04f7\u04f8\u0005\u000b\u0000\u0000\u04f8"+
		"\u04f9\u0003\u0090H\u0000\u04f9\u04fa\u0005\f\u0000\u0000\u04fa\u04fb"+
		"\u0005\r\u0000\u0000\u04fb\u04fc\u0003\u00f6{\u0000\u04fc\u00f9\u0001"+
		"\u0000\u0000\u0000\u04fd\u0500\u0003\u00fc~\u0000\u04fe\u0500\u0003\u0130"+
		"\u0098\u0000\u04ff\u04fd\u0001\u0000\u0000\u0000\u04ff\u04fe\u0001\u0000"+
		"\u0000\u0000\u0500\u00fb\u0001\u0000\u0000\u0000\u0501\u0505\u0003\u00fe"+
		"\u007f\u0000\u0502\u0505\u0003\u0108\u0084\u0000\u0503\u0505\u0003\u010e"+
		"\u0087\u0000\u0504\u0501\u0001\u0000\u0000\u0000\u0504\u0502\u0001\u0000"+
		"\u0000\u0000\u0504\u0503\u0001\u0000\u0000\u0000\u0505\u00fd\u0001\u0000"+
		"\u0000\u0000\u0506\u0509\u0003\u0100\u0080\u0000\u0507\u0509\u0003\u0102"+
		"\u0081\u0000\u0508\u0506\u0001\u0000\u0000\u0000\u0508\u0507\u0001\u0000"+
		"\u0000\u0000\u0509\u00ff\u0001\u0000\u0000\u0000\u050a\u050b\u0003\u010c"+
		"\u0086\u0000\u050b\u050c\u0003\u0144\u00a2\u0000\u050c\u050d\u0003\u010c"+
		"\u0086\u0000\u050d\u0101\u0001\u0000\u0000\u0000\u050e\u0511\u0003\u0104"+
		"\u0082\u0000\u050f\u0511\u0003\u0106\u0083\u0000\u0510\u050e\u0001\u0000"+
		"\u0000\u0000\u0510\u050f\u0001\u0000\u0000\u0000\u0511\u0103\u0001\u0000"+
		"\u0000\u0000\u0512\u0513\u0006\u0082\uffff\uffff\u0000\u0513\u0514\u0003"+
		"\u010c\u0086\u0000\u0514\u0515\u0005)\u0000\u0000\u0515\u0516\u0003\u010c"+
		"\u0086\u0000\u0516\u051c\u0001\u0000\u0000\u0000\u0517\u0518\n\u0001\u0000"+
		"\u0000\u0518\u0519\u0005)\u0000\u0000\u0519\u051b\u0003\u010c\u0086\u0000"+
		"\u051a\u0517\u0001\u0000\u0000\u0000\u051b\u051e\u0001\u0000\u0000\u0000"+
		"\u051c\u051a\u0001\u0000\u0000\u0000\u051c\u051d\u0001\u0000\u0000\u0000"+
		"\u051d\u0105\u0001\u0000\u0000\u0000\u051e\u051c\u0001\u0000\u0000\u0000"+
		"\u051f\u0520\u0006\u0083\uffff\uffff\u0000\u0520\u0521\u0003\u010c\u0086"+
		"\u0000\u0521\u0522\u0005*\u0000\u0000\u0522\u0523\u0003\u010c\u0086\u0000"+
		"\u0523\u0529\u0001\u0000\u0000\u0000\u0524\u0525\n\u0001\u0000\u0000\u0525"+
		"\u0526\u0005*\u0000\u0000\u0526\u0528\u0003\u010c\u0086\u0000\u0527\u0524"+
		"\u0001\u0000\u0000\u0000\u0528\u052b\u0001\u0000\u0000\u0000\u0529\u0527"+
		"\u0001\u0000\u0000\u0000\u0529\u052a\u0001\u0000\u0000\u0000\u052a\u0107"+
		"\u0001\u0000\u0000\u0000\u052b\u0529\u0001\u0000\u0000\u0000\u052c\u052d"+
		"\u0003\u0148\u00a4\u0000\u052d\u052e\u0003\u010c\u0086\u0000\u052e\u0531"+
		"\u0001\u0000\u0000\u0000\u052f\u0531\u0003\u010a\u0085\u0000\u0530\u052c"+
		"\u0001\u0000\u0000\u0000\u0530\u052f\u0001\u0000\u0000\u0000\u0531\u0109"+
		"\u0001\u0000\u0000\u0000\u0532\u0533\u0003\u012c\u0096\u0000\u0533\u0534"+
		"\u00054\u0000\u0000\u0534\u0535\u0003\u012c\u0096\u0000\u0535\u010b\u0001"+
		"\u0000\u0000\u0000\u0536\u0539\u0003\u010e\u0087\u0000\u0537\u0539\u0003"+
		"\u0108\u0084\u0000\u0538\u0536\u0001\u0000\u0000\u0000\u0538\u0537\u0001"+
		"\u0000\u0000\u0000\u0539\u010d\u0001\u0000\u0000\u0000\u053a\u0541\u0003"+
		"\u0110\u0088\u0000\u053b\u0541\u0003\u0114\u008a\u0000\u053c\u053d\u0005"+
		"\t\u0000\u0000\u053d\u053e\u0003\u00fc~\u0000\u053e\u053f\u0005\n\u0000"+
		"\u0000\u053f\u0541\u0001\u0000\u0000\u0000\u0540\u053a\u0001\u0000\u0000"+
		"\u0000\u0540\u053b\u0001\u0000\u0000\u0000\u0540\u053c\u0001\u0000\u0000"+
		"\u0000\u0541\u010f\u0001\u0000\u0000\u0000\u0542\u0543\u0003\u0142\u00a1"+
		"\u0000\u0543\u0544\u0005\u000b\u0000\u0000\u0544\u0545\u0003\u0112\u0089"+
		"\u0000\u0545\u0546\u0005\f\u0000\u0000\u0546\u0547\u0005\r\u0000\u0000"+
		"\u0547\u0548\u0003\u010c\u0086\u0000\u0548\u0111\u0001\u0000\u0000\u0000"+
		"\u0549\u054f\u0003\u016e\u00b7\u0000\u054a\u054b\u0003\u016e\u00b7\u0000"+
		"\u054b\u054c\u0005\u0002\u0000\u0000\u054c\u054d\u0003\u0112\u0089\u0000"+
		"\u054d\u054f\u0001\u0000\u0000\u0000\u054e\u0549\u0001\u0000\u0000\u0000"+
		"\u054e\u054a\u0001\u0000\u0000\u0000\u054f\u0113\u0001\u0000\u0000\u0000"+
		"\u0550\u0554\u0003\u0116\u008b\u0000\u0551\u0554\u0003\u0118\u008c\u0000"+
		"\u0552\u0554\u0003\u011e\u008f\u0000\u0553\u0550\u0001\u0000\u0000\u0000"+
		"\u0553\u0551\u0001\u0000\u0000\u0000\u0553\u0552\u0001\u0000\u0000\u0000"+
		"\u0554\u0115\u0001\u0000\u0000\u0000\u0555\u0556\u0003\u0120\u0090\u0000"+
		"\u0556\u0117\u0001\u0000\u0000\u0000\u0557\u055a\u0003\u011a\u008d\u0000"+
		"\u0558\u055a\u0003\u011c\u008e\u0000\u0559\u0557\u0001\u0000\u0000\u0000"+
		"\u0559\u0558\u0001\u0000\u0000\u0000\u055a\u0119\u0001\u0000\u0000\u0000"+
		"\u055b\u055c\u0003\u0126\u0093\u0000\u055c\u011b\u0001\u0000\u0000\u0000"+
		"\u055d\u055e\u0003\u012c\u0096\u0000\u055e\u055f\u0003\u015a\u00ad\u0000"+
		"\u055f\u0560\u0003\u012c\u0096\u0000\u0560\u011d\u0001\u0000\u0000\u0000"+
		"\u0561\u0562\u0003\u0128\u0094\u0000\u0562\u011f\u0001\u0000\u0000\u0000"+
		"\u0563\u056a\u0003\u015c\u00ae\u0000\u0564\u0565\u0003\u015e\u00af\u0000"+
		"\u0565\u0566\u0005\t\u0000\u0000\u0566\u0567\u0003\u012a\u0095\u0000\u0567"+
		"\u0568\u0005\n\u0000\u0000\u0568\u056a\u0001\u0000\u0000\u0000\u0569\u0563"+
		"\u0001\u0000\u0000\u0000\u0569\u0564\u0001\u0000\u0000\u0000\u056a\u0121"+
		"\u0001\u0000\u0000\u0000\u056b\u056e\u0003\u016c\u00b6\u0000\u056c\u056e"+
		"\u0003\u0124\u0092\u0000\u056d\u056b\u0001\u0000\u0000\u0000\u056d\u056c"+
		"\u0001\u0000\u0000\u0000\u056e\u0123\u0001\u0000\u0000\u0000\u056f\u0570"+
		"\u0003\u0126\u0093\u0000\u0570\u0125\u0001\u0000\u0000\u0000\u0571\u0578"+
		"\u0003\u0160\u00b0\u0000\u0572\u0573\u0003\u0162\u00b1\u0000\u0573\u0574"+
		"\u0005\t\u0000\u0000\u0574\u0575\u0003\u012a\u0095\u0000\u0575\u0576\u0005"+
		"\n\u0000\u0000\u0576\u0578\u0001\u0000\u0000\u0000\u0577\u0571\u0001\u0000"+
		"\u0000\u0000\u0577\u0572\u0001\u0000\u0000\u0000\u0578\u0127\u0001\u0000"+
		"\u0000\u0000\u0579\u0580\u0003\u0164\u00b2\u0000\u057a\u057b\u0003\u0166"+
		"\u00b3\u0000\u057b\u057c\u0005\t\u0000\u0000\u057c\u057d\u0003\u012a\u0095"+
		"\u0000\u057d\u057e\u0005\n\u0000\u0000\u057e\u0580\u0001\u0000\u0000\u0000"+
		"\u057f\u0579\u0001\u0000\u0000\u0000\u057f\u057a\u0001\u0000\u0000\u0000"+
		"\u0580\u0129\u0001\u0000\u0000\u0000\u0581\u0587\u0003\u012c\u0096\u0000"+
		"\u0582\u0583\u0003\u012c\u0096\u0000\u0583\u0584\u0005\u0002\u0000\u0000"+
		"\u0584\u0585\u0003\u012a\u0095\u0000\u0585\u0587\u0001\u0000\u0000\u0000"+
		"\u0586\u0581\u0001\u0000\u0000\u0000\u0586\u0582\u0001\u0000\u0000\u0000"+
		"\u0587\u012b\u0001\u0000\u0000\u0000\u0588\u058b\u0003\u012e\u0097\u0000"+
		"\u0589\u058b\u0003\u016e\u00b7\u0000\u058a\u0588\u0001\u0000\u0000\u0000"+
		"\u058a\u0589\u0001\u0000\u0000\u0000\u058b\u012d\u0001\u0000\u0000\u0000"+
		"\u058c\u0590\u0003\u0120\u0090\u0000\u058d\u0590\u0003\u0122\u0091\u0000"+
		"\u058e\u0590\u0003\u0128\u0094\u0000\u058f\u058c\u0001\u0000\u0000\u0000"+
		"\u058f\u058d\u0001\u0000\u0000\u0000\u058f\u058e\u0001\u0000\u0000\u0000"+
		"\u0590\u012f\u0001\u0000\u0000\u0000\u0591\u0592\u0003\u0132\u0099\u0000"+
		"\u0592\u0593\u0005H\u0000\u0000\u0593\u0594\u0003\u0132\u0099\u0000\u0594"+
		"\u059a\u0001\u0000\u0000\u0000\u0595\u0596\u0005\t\u0000\u0000\u0596\u0597"+
		"\u0003\u0130\u0098\u0000\u0597\u0598\u0005\n\u0000\u0000\u0598\u059a\u0001"+
		"\u0000\u0000\u0000\u0599\u0591\u0001\u0000\u0000\u0000\u0599\u0595\u0001"+
		"\u0000\u0000\u0000\u059a\u0131\u0001\u0000\u0000\u0000\u059b\u05a1\u0005"+
		"\u0017\u0000\u0000\u059c\u059d\u0005\u0014\u0000\u0000\u059d\u059e\u0003"+
		"\u0134\u009a\u0000\u059e\u059f\u0005\u0015\u0000\u0000\u059f\u05a1\u0001"+
		"\u0000\u0000\u0000\u05a0\u059b\u0001\u0000\u0000\u0000\u05a0\u059c\u0001"+
		"\u0000\u0000\u0000\u05a1\u0133\u0001\u0000\u0000\u0000\u05a2\u05a8\u0003"+
		"\u00fc~\u0000\u05a3\u05a4\u0003\u00fc~\u0000\u05a4\u05a5\u0005\u0002\u0000"+
		"\u0000\u05a5\u05a6\u0003\u0134\u009a\u0000\u05a6\u05a8\u0001\u0000\u0000"+
		"\u0000\u05a7\u05a2\u0001\u0000\u0000\u0000\u05a7\u05a3\u0001\u0000\u0000"+
		"\u0000\u05a8\u0135\u0001\u0000\u0000\u0000\u05a9\u05af\u0003\u0138\u009c"+
		"\u0000\u05aa\u05ab\u0005\t\u0000\u0000\u05ab\u05ac\u0003\u0138\u009c\u0000"+
		"\u05ac\u05ad\u0005\n\u0000\u0000\u05ad\u05af\u0001\u0000\u0000\u0000\u05ae"+
		"\u05a9\u0001\u0000\u0000\u0000\u05ae\u05aa\u0001\u0000\u0000\u0000\u05af"+
		"\u0137\u0001\u0000\u0000\u0000\u05b0\u05b1\u0006\u009c\uffff\uffff\u0000"+
		"\u05b1\u05b2\u0003\u013a\u009d\u0000\u05b2\u05b8\u0001\u0000\u0000\u0000"+
		"\u05b3\u05b4\n\u0001\u0000\u0000\u05b4\u05b5\u0005)\u0000\u0000\u05b5"+
		"\u05b7\u0003\u013a\u009d\u0000\u05b6\u05b3\u0001\u0000\u0000\u0000\u05b7"+
		"\u05ba\u0001\u0000\u0000\u0000\u05b8\u05b6\u0001\u0000\u0000\u0000\u05b8"+
		"\u05b9\u0001\u0000\u0000\u0000\u05b9\u0139\u0001\u0000\u0000\u0000\u05ba"+
		"\u05b8\u0001\u0000\u0000\u0000\u05bb\u05c5\u0003\u0114\u008a\u0000\u05bc"+
		"\u05bd\u00051\u0000\u0000\u05bd\u05c5\u0003\u0114\u008a\u0000\u05be\u05bf"+
		"\u00051\u0000\u0000\u05bf\u05c0\u0005\t\u0000\u0000\u05c0\u05c1\u0003"+
		"\u0114\u008a\u0000\u05c1\u05c2\u0005\n\u0000\u0000\u05c2\u05c5\u0001\u0000"+
		"\u0000\u0000\u05c3\u05c5\u0003\u010a\u0085\u0000\u05c4\u05bb\u0001\u0000"+
		"\u0000\u0000\u05c4\u05bc\u0001\u0000\u0000\u0000\u05c4\u05be\u0001\u0000"+
		"\u0000\u0000\u05c4\u05c3\u0001\u0000\u0000\u0000\u05c5\u013b\u0001\u0000"+
		"\u0000\u0000\u05c6\u05ca\u0003\u0142\u00a1\u0000\u05c7\u05ca\u0003\u0140"+
		"\u00a0\u0000\u05c8\u05ca\u0003\u013e\u009f\u0000\u05c9\u05c6\u0001\u0000"+
		"\u0000\u0000\u05c9\u05c7\u0001\u0000\u0000\u0000\u05c9\u05c8\u0001\u0000"+
		"\u0000\u0000\u05ca\u013d\u0001\u0000\u0000\u0000\u05cb\u05cc\u0007\u0000"+
		"\u0000\u0000\u05cc\u013f\u0001\u0000\u0000\u0000\u05cd\u05ce\u0007\u0001"+
		"\u0000\u0000\u05ce\u0141\u0001\u0000\u0000\u0000\u05cf\u05d0\u0007\u0002"+
		"\u0000\u0000\u05d0\u0143\u0001\u0000\u0000\u0000\u05d1\u05d2\u0007\u0003"+
		"\u0000\u0000\u05d2\u0145\u0001\u0000\u0000\u0000\u05d3\u05d4\u0007\u0004"+
		"\u0000\u0000\u05d4\u0147\u0001\u0000\u0000\u0000\u05d5\u05d6\u00051\u0000"+
		"\u0000\u05d6\u0149\u0001\u0000\u0000\u0000\u05d7\u05d8\u0003\u014c\u00a6"+
		"\u0000\u05d8\u014b\u0001\u0000\u0000\u0000\u05d9\u05da\u0003\u01c8\u00e4"+
		"\u0000\u05da\u014d\u0001\u0000\u0000\u0000\u05db\u05dc\u0005Z\u0000\u0000"+
		"\u05dc\u014f\u0001\u0000\u0000\u0000\u05dd\u05de\u0003\u01cc\u00e6\u0000"+
		"\u05de\u0151\u0001\u0000\u0000\u0000\u05df\u05e2\u0003\u0154\u00aa\u0000"+
		"\u05e0\u05e2\u0003\u0160\u00b0\u0000\u05e1\u05df\u0001\u0000\u0000\u0000"+
		"\u05e1\u05e0\u0001\u0000\u0000\u0000\u05e2\u0153\u0001\u0000\u0000\u0000"+
		"\u05e3\u05e6\u0003\u015c\u00ae\u0000\u05e4\u05e6\u0003\u0164\u00b2\u0000"+
		"\u05e5\u05e3\u0001\u0000\u0000\u0000\u05e5\u05e4\u0001\u0000\u0000\u0000"+
		"\u05e6\u0155\u0001\u0000\u0000\u0000\u05e7\u05e8\u0005Z\u0000\u0000\u05e8"+
		"\u0157\u0001\u0000\u0000\u0000\u05e9\u05ea\u0005Z\u0000\u0000\u05ea\u0159"+
		"\u0001\u0000\u0000\u0000\u05eb\u05ec\u0007\u0005\u0000\u0000\u05ec\u015b"+
		"\u0001\u0000\u0000\u0000\u05ed\u05ee\u0003\u015e\u00af\u0000\u05ee\u015d"+
		"\u0001\u0000\u0000\u0000\u05ef\u05f0\u0003\u01c8\u00e4\u0000\u05f0\u015f"+
		"\u0001\u0000\u0000\u0000\u05f1\u05f2\u0003\u0162\u00b1\u0000\u05f2\u0161"+
		"\u0001\u0000\u0000\u0000\u05f3\u05f4\u0003\u01ca\u00e5\u0000\u05f4\u0163"+
		"\u0001\u0000\u0000\u0000\u05f5\u05f6\u0003\u0166\u00b3\u0000\u05f6\u0165"+
		"\u0001\u0000\u0000\u0000\u05f7\u05f8\u0003\u01cc\u00e6\u0000\u05f8\u0167"+
		"\u0001\u0000\u0000\u0000\u05f9\u05fc\u0003\u0160\u00b0\u0000\u05fa\u05fc"+
		"\u0003\u0164\u00b2\u0000\u05fb\u05f9\u0001\u0000\u0000\u0000\u05fb\u05fa"+
		"\u0001\u0000\u0000\u0000\u05fc\u0169\u0001\u0000\u0000\u0000\u05fd\u05fe"+
		"\u0007\u0006\u0000\u0000\u05fe\u016b\u0001\u0000\u0000\u0000\u05ff\u0602"+
		"\u0003\u01ce\u00e7\u0000\u0600\u0602\u0005_\u0000\u0000\u0601\u05ff\u0001"+
		"\u0000\u0000\u0000\u0601\u0600\u0001\u0000\u0000\u0000\u0602\u016d\u0001"+
		"\u0000\u0000\u0000\u0603\u0604\u0005\\\u0000\u0000\u0604\u016f\u0001\u0000"+
		"\u0000\u0000\u0605\u060e\u0003\u0174\u00ba\u0000\u0606\u060e\u0003\u0182"+
		"\u00c1\u0000\u0607\u060e\u0003\u0186\u00c3\u0000\u0608\u060e\u0005]\u0000"+
		"\u0000\u0609\u060a\u0005\u000b\u0000\u0000\u060a\u060b\u0003\u0172\u00b9"+
		"\u0000\u060b\u060c\u0005\f\u0000\u0000\u060c\u060e\u0001\u0000\u0000\u0000"+
		"\u060d\u0605\u0001\u0000\u0000\u0000\u060d\u0606\u0001\u0000\u0000\u0000"+
		"\u060d\u0607\u0001\u0000\u0000\u0000\u060d\u0608\u0001\u0000\u0000\u0000"+
		"\u060d\u0609\u0001\u0000\u0000\u0000\u060e\u0171\u0001\u0000\u0000\u0000"+
		"\u060f\u0614\u0003\u0170\u00b8\u0000\u0610\u0611\u0005\u0002\u0000\u0000"+
		"\u0611\u0613\u0003\u0170\u00b8\u0000\u0612\u0610\u0001\u0000\u0000\u0000"+
		"\u0613\u0616\u0001\u0000\u0000\u0000\u0614\u0612\u0001\u0000\u0000\u0000"+
		"\u0614\u0615\u0001\u0000\u0000\u0000\u0615\u0173\u0001\u0000\u0000\u0000"+
		"\u0616\u0614\u0001\u0000\u0000\u0000\u0617\u061a\u0003\u01c6\u00e3\u0000"+
		"\u0618\u061a\u0003\u0176\u00bb\u0000\u0619\u0617\u0001\u0000\u0000\u0000"+
		"\u0619\u0618\u0001\u0000\u0000\u0000\u061a\u0175\u0001\u0000\u0000\u0000"+
		"\u061b\u061c\u0005\u0018\u0000\u0000\u061c\u061d\u0003\u0178\u00bc\u0000"+
		"\u061d\u061e\u0005\u0002\u0000\u0000\u061e\u061f\u0003\u0196\u00cb\u0000"+
		"\u061f\u0620\u0005\u0002\u0000\u0000\u0620\u0621\u0003\u017a\u00bd\u0000"+
		"\u0621\u0622\u0005\n\u0000\u0000\u0622\u0177\u0001\u0000\u0000\u0000\u0623"+
		"\u0624\u0003\u01c8\u00e4\u0000\u0624\u0179\u0001\u0000\u0000\u0000\u0625"+
		"\u062b\u0005\u000f\u0000\u0000\u0626\u0627\u0005\u000b\u0000\u0000\u0627"+
		"\u0628\u0003\u017c\u00be\u0000\u0628\u0629\u0005\f\u0000\u0000\u0629\u062b"+
		"\u0001\u0000\u0000\u0000\u062a\u0625\u0001\u0000\u0000\u0000\u062a\u0626"+
		"\u0001\u0000\u0000\u0000\u062b\u017b\u0001\u0000\u0000\u0000\u062c\u0631"+
		"\u0003\u017e\u00bf\u0000\u062d\u062e\u0005\u0002\u0000\u0000\u062e\u0630"+
		"\u0003\u017e\u00bf\u0000\u062f\u062d\u0001\u0000\u0000\u0000\u0630\u0633"+
		"\u0001\u0000\u0000\u0000\u0631\u062f\u0001\u0000\u0000\u0000\u0631\u0632"+
		"\u0001\u0000\u0000\u0000\u0632\u017d\u0001\u0000\u0000\u0000\u0633\u0631"+
		"\u0001\u0000\u0000\u0000\u0634\u0636\u0003\u0170\u00b8\u0000\u0635\u0637"+
		"\u0003\u0180\u00c0\u0000\u0636\u0635\u0001\u0000\u0000\u0000\u0636\u0637"+
		"\u0001\u0000\u0000\u0000\u0637\u017f\u0001\u0000\u0000\u0000\u0638\u0639"+
		"\u0005\r\u0000\u0000\u0639\u063a\u0003\u01c2\u00e1\u0000\u063a\u0181\u0001"+
		"\u0000\u0000\u0000\u063b\u063c\u0005\u0019\u0000\u0000\u063c\u063e\u0003"+
		"\u0184\u00c2\u0000\u063d\u063f\u0003\u0194\u00ca\u0000\u063e\u063d\u0001"+
		"\u0000\u0000\u0000\u063e\u063f\u0001\u0000\u0000\u0000\u063f\u0640\u0001"+
		"\u0000\u0000\u0000\u0640\u0641\u0005\n\u0000\u0000\u0641\u0183\u0001\u0000"+
		"\u0000\u0000\u0642\u0643\u0005]\u0000\u0000\u0643\u0185\u0001\u0000\u0000"+
		"\u0000\u0644\u0648\u0003\u0188\u00c4\u0000\u0645\u0648\u0003\u018c\u00c6"+
		"\u0000\u0646\u0648\u0003\u0190\u00c8\u0000\u0647\u0644\u0001\u0000\u0000"+
		"\u0000\u0647\u0645\u0001\u0000\u0000\u0000\u0647\u0646\u0001\u0000\u0000"+
		"\u0000\u0648\u0187\u0001\u0000\u0000\u0000\u0649\u064a\u0005\u001a\u0000"+
		"\u0000\u064a\u064c\u0003\u01d0\u00e8\u0000\u064b\u064d\u0003\u018a\u00c5"+
		"\u0000\u064c\u064b\u0001\u0000\u0000\u0000\u064c\u064d\u0001\u0000\u0000"+
		"\u0000\u064d\u064e\u0001\u0000\u0000\u0000\u064e\u064f\u0005\n\u0000\u0000"+
		"\u064f\u0189\u0001\u0000\u0000\u0000\u0650\u0651\u0005\u0002\u0000\u0000"+
		"\u0651\u0652\u0003\u01c6\u00e3\u0000\u0652\u018b\u0001\u0000\u0000\u0000"+
		"\u0653\u0654\u0005\u001b\u0000\u0000\u0654\u0656\u0003\u018e\u00c7\u0000"+
		"\u0655\u0657\u0003\u0194\u00ca\u0000\u0656\u0655\u0001\u0000\u0000\u0000"+
		"\u0656\u0657\u0001\u0000\u0000\u0000\u0657\u0658\u0001\u0000\u0000\u0000"+
		"\u0658\u0659\u0005\n\u0000\u0000\u0659\u018d\u0001\u0000\u0000\u0000\u065a"+
		"\u065b\u0005]\u0000\u0000\u065b\u018f\u0001\u0000\u0000\u0000\u065c\u065d"+
		"\u0005\u001c\u0000\u0000\u065d\u065f\u0003\u0192\u00c9\u0000\u065e\u0660"+
		"\u0003\u0194\u00ca\u0000\u065f\u065e\u0001\u0000\u0000\u0000\u065f\u0660"+
		"\u0001\u0000\u0000\u0000\u0660\u0661\u0001\u0000\u0000\u0000\u0661\u0662"+
		"\u0005\n\u0000\u0000\u0662\u0191\u0001\u0000\u0000\u0000\u0663\u0664\u0003"+
		"\u01c8\u00e4\u0000\u0664\u0193\u0001\u0000\u0000\u0000\u0665\u0666\u0005"+
		"\u0002\u0000\u0000\u0666\u0667\u0003\u0196\u00cb\u0000\u0667\u0195\u0001"+
		"\u0000\u0000\u0000\u0668\u066f\u0005\u000f\u0000\u0000\u0669\u066a\u0005"+
		"\u000b\u0000\u0000\u066a\u066b\u0003\u0198\u00cc\u0000\u066b\u066c\u0005"+
		"\f\u0000\u0000\u066c\u066f\u0001\u0000\u0000\u0000\u066d\u066f\u0003\u01c2"+
		"\u00e1\u0000\u066e\u0668\u0001\u0000\u0000\u0000\u066e\u0669\u0001\u0000"+
		"\u0000\u0000\u066e\u066d\u0001\u0000\u0000\u0000\u066f\u0197\u0001\u0000"+
		"\u0000\u0000\u0670\u0675\u0003\u019a\u00cd\u0000\u0671\u0672\u0005\u0002"+
		"\u0000\u0000\u0672\u0674\u0003\u019a\u00cd\u0000\u0673\u0671\u0001\u0000"+
		"\u0000\u0000\u0674\u0677\u0001\u0000\u0000\u0000\u0675\u0673\u0001\u0000"+
		"\u0000\u0000\u0675\u0676\u0001\u0000\u0000\u0000\u0676\u0199\u0001\u0000"+
		"\u0000\u0000\u0677\u0675\u0001\u0000\u0000\u0000\u0678\u067c\u0003\u019c"+
		"\u00ce\u0000\u0679\u067c\u0003\u01a2\u00d1\u0000\u067a\u067c\u0003\u01be"+
		"\u00df\u0000\u067b\u0678\u0001\u0000\u0000\u0000\u067b\u0679\u0001\u0000"+
		"\u0000\u0000\u067b\u067a\u0001\u0000\u0000\u0000\u067c\u019b\u0001\u0000"+
		"\u0000\u0000\u067d\u0680\u0003\u019e\u00cf\u0000\u067e\u0680\u0003\u01a0"+
		"\u00d0\u0000\u067f\u067d\u0001\u0000\u0000\u0000\u067f\u067e\u0001\u0000"+
		"\u0000\u0000\u0680\u019d\u0001\u0000\u0000\u0000\u0681\u0682\u0005\u001d"+
		"\u0000\u0000\u0682\u0683\u0003\u01c8\u00e4\u0000\u0683\u0684\u0005\n\u0000"+
		"\u0000\u0684\u019f\u0001\u0000\u0000\u0000\u0685\u0686\u0005\u001e\u0000"+
		"\u0000\u0686\u0687\u0003\u01c8\u00e4\u0000\u0687\u0688\u0005\n\u0000\u0000"+
		"\u0688\u01a1\u0001\u0000\u0000\u0000\u0689\u068e\u0003\u01a4\u00d2\u0000"+
		"\u068a\u068e\u0003\u01aa\u00d5\u0000\u068b\u068e\u0003\u01ae\u00d7\u0000"+
		"\u068c\u068e\u0003\u01ac\u00d6\u0000\u068d\u0689\u0001\u0000\u0000\u0000"+
		"\u068d\u068a\u0001\u0000\u0000\u0000\u068d\u068b\u0001\u0000\u0000\u0000"+
		"\u068d\u068c\u0001\u0000\u0000\u0000\u068e\u01a3\u0001\u0000\u0000\u0000"+
		"\u068f\u0690\u0005\u001f\u0000\u0000\u0690\u0691\u0003\u01a6\u00d3\u0000"+
		"\u0691\u0692\u0005\n\u0000\u0000\u0692\u0695\u0001\u0000\u0000\u0000\u0693"+
		"\u0695\u0003\u01a8\u00d4\u0000\u0694\u068f\u0001\u0000\u0000\u0000\u0694"+
		"\u0693\u0001\u0000\u0000\u0000\u0695\u01a5\u0001\u0000\u0000\u0000\u0696"+
		"\u0697\u0005]\u0000\u0000\u0697\u01a7\u0001\u0000\u0000\u0000\u0698\u0699"+
		"\u0003\u0178\u00bc\u0000\u0699\u069a\u0005\t\u0000\u0000\u069a\u069b\u0003"+
		"\u01c8\u00e4\u0000\u069b\u069c\u0005\u0002\u0000\u0000\u069c\u069d\u0003"+
		"\u01c2\u00e1\u0000\u069d\u069e\u0005\n\u0000\u0000\u069e\u01a9\u0001\u0000"+
		"\u0000\u0000\u069f\u06a0\u0005 \u0000\u0000\u06a0\u06a1\u0005\u000b\u0000"+
		"\u0000\u06a1\u06a2\u0003\u01b8\u00dc\u0000\u06a2\u06a3\u0005\f\u0000\u0000"+
		"\u06a3\u06a4\u0005\n\u0000\u0000\u06a4\u01ab\u0001\u0000\u0000\u0000\u06a5"+
		"\u06a6\u0005!\u0000\u0000\u06a6\u06a7\u0003\u0188\u00c4\u0000\u06a7\u06a8"+
		"\u0005\n\u0000\u0000\u06a8\u01ad\u0001\u0000\u0000\u0000\u06a9\u06aa\u0005"+
		"\"\u0000\u0000\u06aa\u06ab\u0003\u01c8\u00e4\u0000\u06ab\u06ac\u0005\u0002"+
		"\u0000\u0000\u06ac\u06ad\u0005\u000b\u0000\u0000\u06ad\u06ae\u0003\u01b0"+
		"\u00d8\u0000\u06ae\u06af\u0005\f\u0000\u0000\u06af\u06b0\u0005\n\u0000"+
		"\u0000\u06b0\u01af\u0001\u0000\u0000\u0000\u06b1\u06b6\u0003\u01b2\u00d9"+
		"\u0000\u06b2\u06b3\u0005\u0002\u0000\u0000\u06b3\u06b5\u0003\u01b2\u00d9"+
		"\u0000\u06b4\u06b2\u0001\u0000\u0000\u0000\u06b5\u06b8\u0001\u0000\u0000"+
		"\u0000\u06b6\u06b4\u0001\u0000\u0000\u0000\u06b6\u06b7\u0001\u0000\u0000"+
		"\u0000\u06b7\u01b1\u0001\u0000\u0000\u0000\u06b8\u06b6\u0001\u0000\u0000"+
		"\u0000\u06b9\u06bc\u0003\u015e\u00af\u0000\u06ba\u06bc\u0003\u016e\u00b7"+
		"\u0000\u06bb\u06b9\u0001\u0000\u0000\u0000\u06bb\u06ba\u0001\u0000\u0000"+
		"\u0000\u06bc\u01b3\u0001\u0000\u0000\u0000\u06bd\u06be\u0005#\u0000\u0000"+
		"\u06be\u06c0\u0003\u01d0\u00e8\u0000\u06bf\u06c1\u0003\u01b6\u00db\u0000"+
		"\u06c0\u06bf\u0001\u0000\u0000\u0000\u06c0\u06c1\u0001\u0000\u0000\u0000"+
		"\u06c1\u06c2\u0001\u0000\u0000\u0000\u06c2\u06c3\u0005\u0003\u0000\u0000"+
		"\u06c3\u01b5\u0001\u0000\u0000\u0000\u06c4\u06c5\u0005\u0002\u0000\u0000"+
		"\u06c5\u06c6\u0005\u000b\u0000\u0000\u06c6\u06c7\u0003\u01b8\u00dc\u0000"+
		"\u06c7\u06c8\u0005\f\u0000\u0000\u06c8\u01b7\u0001\u0000\u0000\u0000\u06c9"+
		"\u06ce\u0003\u01c6\u00e3\u0000\u06ca\u06cb\u0005\u0002\u0000\u0000\u06cb"+
		"\u06cd\u0003\u01c6\u00e3\u0000\u06cc\u06ca\u0001\u0000\u0000\u0000\u06cd"+
		"\u06d0\u0001\u0000\u0000\u0000\u06ce\u06cc\u0001\u0000\u0000\u0000\u06ce"+
		"\u06cf\u0001\u0000\u0000\u0000\u06cf\u01b9\u0001\u0000\u0000\u0000\u06d0"+
		"\u06ce\u0001\u0000\u0000\u0000\u06d1\u06d8\u0003\u01bc\u00de\u0000\u06d2"+
		"\u06d3\u0003\u01bc\u00de\u0000\u06d3\u06d4\u0005\r\u0000\u0000\u06d4\u06d5"+
		"\u0003\u01ba\u00dd\u0000\u06d5\u06d8\u0001\u0000\u0000\u0000\u06d6\u06d8"+
		"\u0003\u01c2\u00e1\u0000\u06d7\u06d1\u0001\u0000\u0000\u0000\u06d7\u06d2"+
		"\u0001\u0000\u0000\u0000\u06d7\u06d6\u0001\u0000\u0000\u0000\u06d8\u01bb"+
		"\u0001\u0000\u0000\u0000\u06d9\u06e0\u0003\u01c8\u00e4\u0000\u06da\u06e0"+
		"\u0003\u01be\u00df\u0000\u06db\u06e0\u0003\u016e\u00b7\u0000\u06dc\u06e0"+
		"\u0003\u01ce\u00e7\u0000\u06dd\u06e0\u0005_\u0000\u0000\u06de\u06e0\u0003"+
		"\u01c0\u00e0\u0000\u06df\u06d9\u0001\u0000\u0000\u0000\u06df\u06da\u0001"+
		"\u0000\u0000\u0000\u06df\u06db\u0001\u0000\u0000\u0000\u06df\u06dc\u0001"+
		"\u0000\u0000\u0000\u06df\u06dd\u0001\u0000\u0000\u0000\u06df\u06de\u0001"+
		"\u0000\u0000\u0000\u06e0\u01bd\u0001\u0000\u0000\u0000\u06e1\u06e2\u0003"+
		"\u01c8\u00e4\u0000\u06e2\u06e3\u0005\t\u0000\u0000\u06e3\u06e4\u0003\u01c4"+
		"\u00e2\u0000\u06e4\u06e5\u0005\n\u0000\u0000\u06e5\u01bf\u0001\u0000\u0000"+
		"\u0000\u06e6\u06e7\u0005$\u0000\u0000\u06e7\u06e8\u0003\u0018\f\u0000"+
		"\u06e8\u06e9\u0005\n\u0000\u0000\u06e9\u06fb\u0001\u0000\u0000\u0000\u06ea"+
		"\u06eb\u0005%\u0000\u0000\u06eb\u06ec\u0003x<\u0000\u06ec\u06ed\u0005"+
		"\n\u0000\u0000\u06ed\u06fb\u0001\u0000\u0000\u0000\u06ee\u06ef\u0005&"+
		"\u0000\u0000\u06ef\u06f0\u0003\u00fa}\u0000\u06f0\u06f1\u0005\n\u0000"+
		"\u0000\u06f1\u06fb\u0001\u0000\u0000\u0000\u06f2\u06f3\u0005\'\u0000\u0000"+
		"\u06f3\u06f4\u0003\u0136\u009b\u0000\u06f4\u06f5\u0005\n\u0000\u0000\u06f5"+
		"\u06fb\u0001\u0000\u0000\u0000\u06f6\u06f7\u0005(\u0000\u0000\u06f7\u06f8"+
		"\u0003\u012c\u0096\u0000\u06f8\u06f9\u0005\n\u0000\u0000\u06f9\u06fb\u0001"+
		"\u0000\u0000\u0000\u06fa\u06e6\u0001\u0000\u0000\u0000\u06fa\u06ea\u0001"+
		"\u0000\u0000\u0000\u06fa\u06ee\u0001\u0000\u0000\u0000\u06fa\u06f2\u0001"+
		"\u0000\u0000\u0000\u06fa\u06f6\u0001\u0000\u0000\u0000\u06fb\u01c1\u0001"+
		"\u0000\u0000\u0000\u06fc\u0702\u0005\u000f\u0000\u0000\u06fd\u06fe\u0005"+
		"\u000b\u0000\u0000\u06fe\u06ff\u0003\u01c4\u00e2\u0000\u06ff\u0700\u0005"+
		"\f\u0000\u0000\u0700\u0702\u0001\u0000\u0000\u0000\u0701\u06fc\u0001\u0000"+
		"\u0000\u0000\u0701\u06fd\u0001\u0000\u0000\u0000\u0702\u01c3\u0001\u0000"+
		"\u0000\u0000\u0703\u0708\u0003\u01ba\u00dd\u0000\u0704\u0705\u0005\u0002"+
		"\u0000\u0000\u0705\u0707\u0003\u01ba\u00dd\u0000\u0706\u0704\u0001\u0000"+
		"\u0000\u0000\u0707\u070a\u0001\u0000\u0000\u0000\u0708\u0706\u0001\u0000"+
		"\u0000\u0000\u0708\u0709\u0001\u0000\u0000\u0000\u0709\u01c5\u0001\u0000"+
		"\u0000\u0000\u070a\u0708\u0001\u0000\u0000\u0000\u070b\u070e\u0003\u01c8"+
		"\u00e4\u0000\u070c\u070e\u0005O\u0000\u0000\u070d\u070b\u0001\u0000\u0000"+
		"\u0000\u070d\u070c\u0001\u0000\u0000\u0000\u070e\u01c7\u0001\u0000\u0000"+
		"\u0000\u070f\u0710\u0007\u0007\u0000\u0000\u0710\u01c9\u0001\u0000\u0000"+
		"\u0000\u0711\u0712\u0005Z\u0000\u0000\u0712\u01cb\u0001\u0000\u0000\u0000"+
		"\u0713\u0714\u0005[\u0000\u0000\u0714\u01cd\u0001\u0000\u0000\u0000\u0715"+
		"\u0716\u0007\b\u0000\u0000\u0716\u01cf\u0001\u0000\u0000\u0000\u0717\u0718"+
		"\u0005^\u0000\u0000\u0718\u01d1\u0001\u0000\u0000\u0000\u008e\u01d5\u01dc"+
		"\u01e4\u01ed\u01fa\u0205\u0210\u021b\u0226\u022d\u0234\u023c\u0241\u024a"+
		"\u0256\u0263\u0270\u0275\u0279\u0282\u0292\u0297\u029f\u02ac\u02b0\u02ba"+
		"\u02be\u02d3\u02da\u02e1\u02ec\u02f4\u02fb\u0302\u0313\u031c\u0326\u032b"+
		"\u0334\u033e\u034a\u0357\u0369\u0371\u0375\u037d\u0389\u0396\u039c\u03a0"+
		"\u03a9\u03b9\u03bd\u03c5\u03d1\u03d9\u03dd\u03e7\u03f3\u0402\u0409\u0410"+
		"\u0418\u041f\u042b\u0435\u043c\u0443\u044d\u0451\u0459\u0468\u046f\u047e"+
		"\u0485\u0495\u04a1\u04b1\u04c2\u04ce\u04d7\u04db\u04ec\u04f0\u04f4\u04ff"+
		"\u0504\u0508\u0510\u051c\u0529\u0530\u0538\u0540\u054e\u0553\u0559\u0569"+
		"\u056d\u0577\u057f\u0586\u058a\u058f\u0599\u05a0\u05a7\u05ae\u05b8\u05c4"+
		"\u05c9\u05e1\u05e5\u05fb\u0601\u060d\u0614\u0619\u062a\u0631\u0636\u063e"+
		"\u0647\u064c\u0656\u065f\u066e\u0675\u067b\u067f\u068d\u0694\u06b6\u06bb"+
		"\u06c0\u06ce\u06d7\u06df\u06fa\u0701\u0708\u070d";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}