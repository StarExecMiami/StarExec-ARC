import java.io.*;
import java.util.*;
import tptp_parser.*;

public class TPTP2SUMO {

  public static void printTPTP (String tptp) throws Exception {
    printTPTP(new BufferedReader(new StringReader(tptp)));
  }

  public static void printTPTP (BufferedReader reader) throws Exception {
    TptpLexer lexer = new TptpLexer(reader);
    TptpParser parser = new TptpParser(lexer);
    SimpleTptpParserOutput outputManager = new SimpleTptpParserOutput();
    Hashtable ftable = new Hashtable();
    Vector<SimpleTptpParserOutput.TopLevelItem> Items = new Vector();

    //----Start SUMO output
    System.out.printf("<queryResponse>\n");
    System.out.printf("  <answer result='yes' number='1'>\n");
    System.out.printf("    <proof>\n\n\n");

    for (SimpleTptpParserOutput.TopLevelItem item = 
           (SimpleTptpParserOutput.TopLevelItem)parser.topLevelItem(outputManager);
         item != null;
         item = (SimpleTptpParserOutput.TopLevelItem)parser.topLevelItem(outputManager)) {
      String name = "";
      ftable.put(name, item);
      Items.add(item);
    }

    for (SimpleTptpParserOutput.TopLevelItem item : Items) {
      //      printTPTPFormula(item, ftable);
    }

    //----End SUMO output
    System.out.printf("    </proof>\n");
    System.out.printf("  </answer>\n");
    System.out.printf("  <summary proofs='1'/>\n");
    System.out.printf("</queryResponse>\n");
  }

  private static void gatherParents (SimpleTptpParserOutput.Source source, Vector<String> parents) {
    for (SimpleTptpParserOutput.ParentInfo p : ((SimpleTptpParserOutput.Source.Inference)source).getParentInfoList()) {
      SimpleTptpParserOutput.Source psource = p.getSource();
      if (psource.getKind() == SimpleTptpParserOutput.Source.Kind.Inference) {
        gatherParents(psource, parents);
      } else if (!(p.toString()).contains("(") && !(p.toString()).contains(")")){
        parents.add(p.toString());
      }
    }
  }

  private static void printTPTPFormula (SimpleTptpParserOutput.TopLevelItem item) {
    int indent = 12;
    int indented = 0;
    Vector<String> parents = new Vector();
    
    System.out.printf("\n");
    System.out.printf("      <proofStep>\n");
    System.out.printf("        <premises>\n");
    //----Add parents info
    if (item.getKind() == SimpleTptpParserOutput.TopLevelItem.Kind.Formula) {
      SimpleTptpParserOutput.AnnotatedFormula AF = ((SimpleTptpParserOutput.AnnotatedFormula)item);
      gatherParents(AF.getAnnotations().getSource(),parents);
    } else if (item.getKind() == SimpleTptpParserOutput.TopLevelItem.Kind.Clause) {
      SimpleTptpParserOutput.AnnotatedClause AC = ((SimpleTptpParserOutput.AnnotatedClause)item);
      gatherParents(AC.getAnnotations().getSource(),parents);
    } else {
      System.out.println("Error: TPTP Formula syntax unknown for printing");
      return;
    }
    for (String parent : parents) {
      
    }
    System.out.printf("        </premises>\n");
    System.out.printf("        <conclusion>\n");
    String type = "";
    if (item.getKind() == SimpleTptpParserOutput.TopLevelItem.Kind.Formula) {
      SimpleTptpParserOutput.AnnotatedFormula AF = ((SimpleTptpParserOutput.AnnotatedFormula)item);
      type = "formula";
      System.out.printf("          <%s number='%s'>\n",type,AF.getName());
      printFormula(AF.getFormula(),indent,indented);
      System.out.printf("\n");
      System.out.printf("          </%s>\n",type);
    } else if (item.getKind() == SimpleTptpParserOutput.TopLevelItem.Kind.Clause) {
      SimpleTptpParserOutput.AnnotatedClause AC = ((SimpleTptpParserOutput.AnnotatedClause)item);
      type = "clause";
      System.out.printf("          <%s number='%s'>\n",type,AC.getName());
      printClause(AC.getClause(),indent,indented);
      System.out.printf("\n");
      System.out.printf("          </%s>\n",type);
    } else {
      System.out.println("Error: TPTP Formula syntax unknown for printing");
    }

    System.out.printf("        </conclusion>\n");
    System.out.printf("      </proofStep>\n");

  }

  private static void printIndent (int indent, int indented) {
    String res = "";
    for (int i = indented+1; i <= indent; i++) {
      res += " ";
    }
    System.out.printf(res);
  }

  private static void printTerm (SimpleTptpParserOutput.Formula.Atomic atom) {
    String res = "";
    LinkedList<SimpleTptpParserOutput.Term> arguments = (LinkedList)atom.getArguments();
    if (arguments != null) {
      res += "(";
    }
    res += atom.getPredicate();
    if (arguments != null) {
      for (int n = 0; n < arguments.size();  n++) {
        res += " " + arguments.get(n).toString();
      }
    }
    if (arguments != null) {
      res += ")";
    }
    System.out.printf(res);
  }

  private static void printConnective(SimpleTptpParserOutput.BinaryConnective connective) {
    switch (connective) {
    case And:
      System.out.printf("and");
      break;
    case Or:
      System.out.printf("or");
      break;
    case Equivalence: 
      System.out.printf("<=>");
      break;
    case Implication:
      System.out.printf("=>");
      break;
    case ReverseImplication:
      System.out.printf("<=");
      break;
    case Disequivalence:
      System.out.printf("not <=>");
      break;
    case NotOr:
      System.out.printf("not or");
      break;
    case NotAnd:
      System.out.printf("not and");
      break;
    default:
      System.out.println("Not a connective");
      break;
    }
  }

  private static void printQuantifier (SimpleTptpParserOutput.Quantifier quantifier) {
    switch (quantifier) {
    case ForAll:
      System.out.printf("forall");
      break;
    case Exists:
      System.out.printf("exists");
      break;
    default:
      System.out.println("Not a quantifier");
    }
  }

  private static boolean kifAssociative (SimpleTptpParserOutput.BinaryConnective connective) {
    switch (connective) {
    case And:
    case Or:
      return true;
    default:
      return false;
    }
  }

  private static void printFormula (SimpleTptpParserOutput.Formula formula, int indent, int indented) {
    switch(formula.getKind()) {
    case Atomic:
      printIndent(indent,indented);
      printTerm((SimpleTptpParserOutput.Formula.Atomic)formula);
      break;
    case Negation:
      printIndent(indent,indented);
      System.out.printf("(%s ","not");
      printFormula(((SimpleTptpParserOutput.Formula.Negation)formula).getArgument(),indent+4,indent+4);
      System.out.printf(")");
      break;
    case Binary:
      printIndent(indent,indented);
      System.out.printf("(");
      printConnective(((SimpleTptpParserOutput.Formula.Binary)formula).getConnective());
      System.out.printf(" ");
      printFormula(((SimpleTptpParserOutput.Formula.Binary)formula).getLhs(),indent+4,indent+4);
      System.out.printf("\n");
      while (kifAssociative(((SimpleTptpParserOutput.Formula.Binary)formula).getConnective()) &&
             ((SimpleTptpParserOutput.Formula.Binary)formula).getRhs().getKind() == SimpleTptpParserOutput.Formula.Kind.Binary &&
             ((SimpleTptpParserOutput.Formula.Binary)formula).getConnective() == 
               ((SimpleTptpParserOutput.Formula.Binary)((SimpleTptpParserOutput.Formula.Binary)formula).getRhs()).getConnective()) {
        formula = ((SimpleTptpParserOutput.Formula.Binary)formula).getRhs();
        printFormula(((SimpleTptpParserOutput.Formula.Binary)formula).getLhs(),indent+4,0);
        System.out.printf("\n");
      }
      printFormula(((SimpleTptpParserOutput.Formula.Binary)formula).getRhs(),indent+4,0);
      System.out.printf(")");
      break;
    case Quantified:
      printIndent(indent,indented);
      System.out.printf("(");
      printQuantifier(((SimpleTptpParserOutput.Formula.Quantified)formula).getQuantifier());
      System.out.printf(" (");
      System.out.printf("?%s",((SimpleTptpParserOutput.Formula.Quantified)formula).getVariable());
      while (((SimpleTptpParserOutput.Formula.Quantified)formula).getKind() == SimpleTptpParserOutput.Formula.Kind.Quantified &&
             ((SimpleTptpParserOutput.Formula.Quantified)formula).getMatrix().getKind() == SimpleTptpParserOutput.Formula.Kind.Quantified &&
             ((SimpleTptpParserOutput.Formula.Quantified)formula).getQuantifier() == 
               ((SimpleTptpParserOutput.Formula.Quantified)((SimpleTptpParserOutput.Formula.Quantified)formula).getMatrix()).getQuantifier()) {
        formula = ((SimpleTptpParserOutput.Formula.Quantified)formula).getMatrix();
        System.out.printf(" ?%s", ((SimpleTptpParserOutput.Formula.Quantified)formula).getVariable());
      }
      System.out.printf(") ");
      if (((SimpleTptpParserOutput.Formula.Quantified)formula).getMatrix().getKind() == SimpleTptpParserOutput.Formula.Kind.Negation ||
          ((SimpleTptpParserOutput.Formula.Quantified)formula).getMatrix().getKind() == SimpleTptpParserOutput.Formula.Kind.Atomic) {
        printFormula(((SimpleTptpParserOutput.Formula.Quantified)formula).getMatrix(),indent,indent);
      } else {
        System.out.printf("%s","\n");
        printFormula(((SimpleTptpParserOutput.Formula.Quantified)formula).getMatrix(),indent + 4,0);
      }
      System.out.printf(")");
      break;
    default:
      System.out.println("Error: TPTP Formula syntax unkown for printing");
      break;
    }
  }

  private static void printClause (SimpleTptpParserOutput.Clause clause, int indent, int indented) {    
    LinkedList<SimpleTptpParserOutput.Literal> literals = (LinkedList)clause.getLiterals();
    printIndent(indent,indented);
    if (literals == null) {
      System.out.printf("false\n");
      return;
    }   
    assert !literals.isEmpty();
    if (literals.size() == 1) {
      printLiteral(literals.get(0),indent,indent);
    } else {
      System.out.printf("(");
      printConnective(SimpleTptpParserOutput.BinaryConnective.Or);
      System.out.printf(" ");
      printLiteral(literals.get(0),indent,indent);
      for (int i = 1; i < literals.size(); i++) {
        System.out.printf("\n");
        printLiteral(literals.get(i),indent+4,0);
      }
      System.out.printf(")");
    }
  }

  private static void printLiteral (SimpleTptpParserOutput.Literal literal, int indent, int indented) {
    printIndent(indent,indented);
    if (literal.isPositive()) {
      printTerm((SimpleTptpParserOutput.Formula.Atomic)literal.getAtom());
    } else {
      System.out.printf("(not");
      printTerm((SimpleTptpParserOutput.Formula.Atomic)literal.getAtom());
      System.out.printf(")");
    }
  }

}
