#!/bin/awk -f
function CleanAddedLine(Accumulated) {

    do {
#DEBUG print "??" Accumulated "??";
        Substitutions = 0;
#----CNF: Extra ()s around clause
        Substitutions += \
sub(/LPAREN \( +<RPAREN ) +</,"",Accumulated);
#----CNF: Remove extra ()s around cnf_formulae
        Substitutions += \
sub(/LPAREN \( +<<cnf_formula> +<<fof_unitary_formula> +<RPAREN ) +</,"",Accumulated);
#----FOF: Remove extra ()s around formulae
        Substitutions += \
sub(/LPAREN \( +<<fof_logic_formula> +<<fof_unitary_formula> +<RPAREN ) +</,"",Accumulated);
#----FOF: Remove extra ()s around negated equalities
        Substitutions += \
sub(/<fof_unitary_formula> +<LPAREN \( +<<fof_logic_formula> +<RPAREN ) +</,"",Accumulated);
#----FOF: Removed nested ()s in associative formulae
        Substitutions += \
sub(/LPAREN \( +<<fof_logic_formula> +<<fof_unitary_formula> +<<fof_unit_formula> +<<fof_unitary_formula> +<LPAREN \( +<<fof_logic_formula> +<<fof_binary_formula> +<<fof_binary_assoc> +<RPAREN ) +<RPAREN ) +</,"",Accumulated);
#----FOF: Remove excess brackets in associative binary formulae
        Substitutions += \
sub(/LPAREN \( +<<fof_logic_formula> +<<fof_unitary_formula> +<<fof_unit_formula> +<<fof_unitary_formula> +<LPAREN \( +<<fof_logic_formula> +<<fof_binary_formula> +<<fof_binary_assoc> +<RPAREN ) +<<fof_unit_formula> +<<fof_unitary_formula> +<LPAREN \( +<<fof_logic_formula> +<<fof_binary_formula> +<<fof_binary_assoc> +<RPAREN ) +<RPAREN ) +</,"",Accumulated);
#----FOF: Added brackets around inequalities, diff gets confused
        Substitutions += \
sub(/<fof_unitary_formula> +<LPAREN \( +<<fof_logic_formula> +< +>  <fof_unitary_formula> +>  LPAREN \( +>  <fof_logic_formula>/,"",Accumulated);
#----TFF: Remove extra ()s around types
        Substitutions += \
sub(/LPAREN \( +<<tff_atom_typing> +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/LPAREN \( +<<tff_atom_typing> +<LPAREN \( +<<tff_non_atomic_type> +<RPAREN ) +<RPAREN ) +</,"",Accumulated);
#----TFF: Remove extra ()s around formulae
        Substitutions += \
sub(/LPAREN \( +<<tff_logic_formula> +<<tff_unitary_formula> +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/<tff_unitary_formula> +<LPAREN \( +<<tff_logic_formula> +<RPAREN ) +</,"",Accumulated);
#----TFF: Add needed ()s around boolean variables
        Substitutions += \
sub(/ +>  LPAREN \( +>  <tff_logic_formula> +>  <tff_unitary_formula> +>  <tfx_unitary_formula> +>  RPAREN )/,"",Accumulated);
        Substitutions += \
sub(/ +>  LPAREN \( +>  <tff_logic_formula> +>  <tff_unitary_formula> +>  RPAREN )/,"",Accumulated);
        Substitutions += \
sub(/ +>  <tff_unitary_formula> +>  LPAREN \( +>  <tff_logic_formula> +>  RPAREN )/,"",Accumulated);
#----TFF: Add needed ()s around quantified equations
        Substitutions += \
sub(/ +>  <tff_unitary_formula> +>  LPAREN \( +>  <tff_logic_formula> +>  RPAREN )/,"",Accumulated);

#----THF: Remove extra ()s around types
        Substitutions += \
sub(/LPAREN \( +<<thf_atom_typing> +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/LPAREN \( +<<thf_atom_typing> +<<thf_unitary_type> +<<thf_unitary_formula> +<LPAREN \( +<<thf_logic_formula> +<<thf_binary_formula> +<<thf_binary_type> +<RPAREN ) +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/<thf_unitary_type> +<<thf_unitary_formula> +<LPAREN \( +<<thf_logic_formula> +<<thf_binary_formula> +<<thf_binary_type> +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/LPAREN \( +<<thf_logic_formula> +<<thf_binary_formula> +<<thf_binary_type> +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/LPAREN \( +<<thf_logic_formula> +<<thf_unitary_formula> +<<thf_unitary_type> +<<thf_unitary_formula> +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/LPAREN \( +<<thf_logic_formula> +<<thf_unitary_formula> +<<thf_unitary_type> +<<thf_unitary_formula> +<<thf_unitary_type> +<<thf_unitary_formula> +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/<thf_unitary_type> +\|  <thf_apply_type><thf_unitary_formula> +<LPAREN \( +<<thf_logic_formula> +<<thf_binary_formula> +<<thf_binary_assoc> +<RPAREN ) +</,"",Accumulated);

#----THF: Remove extra ()s around formulae
        Substitutions += \
sub(/LPAREN \( +<<thf_logic_formula> +<<thf_unitary_formula> +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/<thf_unitary_formula> +<LPAREN \( +<<thf_logic_formula> +<<thf_unary_formula> +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/<thf_unitary_formula> +<LPAREN \( +<<thf_logic_formula> +<RPAREN ) +</,"",Accumulated);
        Substitutions += \
sub(/LPAREN \( +<<thf_logic_formula> +<<thf_unary_formula> +<<thf_unitary_formula> +<RPAREN ) +</,"",Accumulated);
#----THF: Remove extra ()s around negated formulae
        Substitutions += \
sub(/LPAREN \( +<<thf_logic_formula> +<<thf_unitary_formula> +<<thf_unitary_formula> +<RPAREN ) +</,"",Accumulated);

#----THF: Add needed ()s around boolean variables
        Substitutions += \
sub(/ +>  LPAREN \( +>  <thf_logic_formula> +>  <thf_unitary_formula> +>  RPAREN )/,"",Accumulated);
#----THF: Add needed ()s around equations
        Substitutions += \
sub(/ +>  RPAREN ) +>  <thf_unitary_formula> +>  LPAREN \( +>  <thf_logic_formula>/,"",Accumulated);
#----THF: Add needed ()s around $ite arguments
        Substitutions += \
sub(/ +>  <thf_unitary_formula> +>  LPAREN \( +>  <thf_logic_formula> +>  RPAREN )/,"",Accumulated);

#DEBUG print "!!" Accumulated "!!";
    } while (Substitutions > 0);
    return(Accumulated);
}

#----Too subtle for diff to remove the context
function CleanLostContext(Accumulated) {

    do {
        Substitutions = 0;
        Substitutions += \
sub(/LPAREN \( +<<thf_logic_formula> +<<thf_unitary_formula> +< +>  <thf_unitary_formula> +>  LPAREN \( +>  <thf_logic_formula>/,"",Accumulated);
        Substitutions += \
sub(/<tff_unitary_formula> +<LPAREN \( +<<tff_logic_formula> +< +>  <tff_unitary_formula> +>  LPAREN \( +>  <tff_logic_formula>/,"",Accumulated);
        Substitutions += \
sub(/LPAREN \( +<<tff_logic_formula> +<<tff_unitary_formula> +< +>  <tff_unitary_formula> +>  LPAREN \( +>  <tff_logic_formula>/,"",Accumulated);
        Substitutions += \
sub(/LPAREN \( +<<thf_logic_formula> +<<thf_unitary_formula> +< +>  LPAREN \( +>  <thf_logic_formula> +>  <thf_unitary_formula>/,"",Accumulated);
    } while (Substitutions > 0);
    return(Accumulated);
}

BEGIN {
    Accumulator = "";
}

{
    Accumulator = Accumulator $0;
    Accumulator = CleanAddedLine(Accumulator);
}
END {
    Accumulator = CleanLostContext(Accumulator);
    Accumulator = CleanAddedLine(Accumulator);
    Accumulator = CleanLostContext(Accumulator);
    if (Accumulator != "") {
        print "::" Accumulator "::";
    }
}
