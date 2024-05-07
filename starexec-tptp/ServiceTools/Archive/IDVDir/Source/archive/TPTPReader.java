//*****************************************************************************
//*****************************************************************************
/*
  Steven Trac
  Proof Reader
*/
//*****************************************************************************
/*****
 * Graph Proof Reader
 * Build on to GraphMan by Dr. Christian Duncan
 * Mimics GraphMan file: GraphReader.java
 ****/
//*****************************************************************************
import java.io.*;
import java.util.*;
import javax.swing.*;
//*****************************************************************************

/*********************
 * ProofReader Class
 *    Reads a Proof in tptp format
 *    Converts to a graph
 *********************/
public class TPTPReader {

  public static final int TPTP_EOL_DELIMETER = '\\'; //delimeter for new line is backslash '\\'

  public static Graph readTPTP (Reader in, IDV idv)
    throws IOException {
    BufferedReader bin = new BufferedReader(in);

    return readTPTP(bin, idv);
  }
  
  /***************************
   * Read tptp proof format input into Graph
   *   Very simple format
   *   Looks like:
   *       % Comments
   *       cnf(
   *         Formula #,      //Node name
   *         Formula Type,   //Output info, dump as String
   *         Formula,        //Output info, dump as entire String
   *         Parent Info,    //Used to connect nodes (Edges)
   *         Extra Info      //Output info, dump as entire String
   *         ).
   ***************************/

  public static Graph readTPTP(BufferedReader in, IDV idv)
    throws IOException {
    IDGraph g = null;
    int n, i, j;
    
    StreamTokenizer tok = new StreamTokenizer(in);

    tok.commentChar('%');
    tok.ordinaryChar(TPTP_EOL_DELIMETER);
    tok.ordinaryChar('.');
    tok.ordinaryChar('\'');
    tok.ordinaryChar('\n');
    tok.ordinaryChar('\r');
    tok.ordinaryChar(' ');
    tok.ordinaryChar('/');
    tok.ordinaryChar('-');
    tok.eolIsSignificant(true);   // End-of-line is important

    Vector formulas = new Vector();
    Hashtable ftable = new Hashtable();
    int f_count = 0;

    Random generator = new Random();

    /** Now parse every token **/
    int c_count = 0;                 //comma count
    int p_count = 0;                 //parenthesis count
    int b_count = 0;                 //bracket count

    String token = "";               //each token string
    String formula = "";             //entire formula dump
    String name = "";                //formula string name (should be number)
    String format = "";              //formula format (cnf, fof)
    String type = "";                //formula type
    String formula_only = "";        //just formula dump
    Vector parents = new Vector();   //parents of this formula

    boolean name_set = false;        //check if formula name is set
    boolean type_set = false;        //check if formula type is set
    boolean parent_check = false;    //check if at parent part of formula
    boolean has_parents = false;     //true if formula has parents
    boolean pass_parents = false;    //true if passed parents part of formula
    boolean inside_formula = false;  //true if inside formula
    boolean equality = false;        //true if resolved by equality

    while (tok.nextToken() != StreamTokenizer.TT_EOF) {
      //System.out.println("Working on formula #: " + f_count);
      //System.out.println(" String is: " + tok.toString());
      //if p_count == 1 && c_count == 0 => formula name
      if (p_count == 0 && tok.ttype == StreamTokenizer.TT_WORD) {
        format = tok.sval;
        if (tok.sval.equals("fof") || tok.sval.equals("cnf")) {
          
          //System.out.println("format is fof or cnf");
        }
        else {
          //System.out.println("format is unknown");
          //System.exit(-1);
        }
      }

      if (p_count == 1 && c_count == 0 && !name_set) {
        if (tok.ttype == StreamTokenizer.TT_NUMBER)
          name = String.valueOf((int)tok.nval);
        else if (tok.ttype == StreamTokenizer.TT_WORD) 
          name = tok.sval;
        else if (tok.sval != null)
          name = tok.sval;
        else 
          name = String.valueOf((char)tok.ttype);
        name_set = true;
      }

      if (p_count == 1 && c_count == 1 && !type_set &&
          tok.ttype == StreamTokenizer.TT_WORD) {
        type += tok.sval;
      }

      //not inside formula brackets, and 3rd comma, resides Parent info
      if (p_count == 1 && c_count == 3 && !pass_parents) {
        parent_check = true;
      }

      //see if axiom(from a file) or has parents(inference)
      if (parent_check && tok.sval != null && tok.sval.equals("inference")) {
        //System.out.println("has parents");
        has_parents = true;   //determined it has parents
        pass_parents = true;  //passed parent check
        parent_check = false; //dont check parents anymore
      }
      else if (parent_check && tok.sval != null && tok.sval.equals("file")) {
        //System.out.println("NO PARENTS");
        has_parents = false;  //this has no parents
        parent_check = false; //dont do check anymore
        pass_parents = true;  //passed parent check
      }
      else if (parent_check && tok.sval != null && !tok.sval.equals("file")) {
        //System.out.println("New parent: " + tok.sval);
        parents.add(tok.sval);
        parent_check = false;
        has_parents = false;
        pass_parents = true;
      }
      else if (parent_check && tok.ttype == StreamTokenizer.TT_NUMBER) {
        //System.out.println("New parent: " + tok.nval);
        parents.add(new Integer((int)tok.nval));
        parent_check = false;
        has_parents = false;
        pass_parents = true;
      }
      
      //if 2 more commas, and inside a bracket => parents info        
      //if (has_parents && c_count == 5 && b_count == 1) {
      if (has_parents && c_count == 5 && b_count > 0) {
        if (tok.ttype == StreamTokenizer.TT_NUMBER) {
          if (!parents.contains(new Integer((int)tok.nval)))
            parents.add(new Integer((int)tok.nval));
        }
        else if (tok.ttype == StreamTokenizer.TT_WORD && tok.sval.equals("equality")) {
          //Possible parent is equality theorem not a number
          //mark edges of this node
          // theory(equality)
          //System.out.println("Equality - woohoo");
          equality = true;
        }
      }

      /*
        formula type = fof,
                       cnf

        types = initial,
                derived,
                unknown,
                axiom,
                definition,
                knowledge,
                assumption,
                lemma,
                hypothesis,
                conjecture
       
         check <types>-type2 = types       //substatus

         inference(copy,[status(thm)],[86]),check for theory(equality)
      */



      
      if (p_count >= 2 && c_count == 2) {
        inside_formula = true;
      } else {
        inside_formula = false;
      }
      

      //add token to formula dump
      if (tok.ttype == StreamTokenizer.TT_NUMBER) {
        token = String.valueOf((int)tok.nval);
      } else if (tok.ttype == StreamTokenizer.TT_WORD) {
        token = tok.sval;
      } else if (tok.sval != null) {
        token = tok.sval;
      } else {
        //increment counters accordingly
        token = String.valueOf((char)tok.ttype);
        if (tok.ttype == '(') p_count++;
        if (tok.ttype == ')') p_count--;
        if (tok.ttype == '[') b_count++;
        if (tok.ttype == ']') b_count--;
        if (tok.ttype == ',' && 
            ((p_count < 2 && b_count == 0) ||
             (has_parents && b_count == 0))) {
          c_count++;
          //System.out.println(" comma ++" );          
        }        
        if (tok.ttype == TPTP_EOL_DELIMETER) { 
          token = (p_count == 0) ? "" : "\n";
        }
        if (p_count == 0 && tok.ttype == '\n') token = "";
      }
      formula = formula + token;
      //System.out.println("___");
      //System.out.println(" Formula: c:" + c_count + " p: " + p_count + ", b: " + b_count + ", FORMULA:" + formula);
      //System.out.println("___+++");
      if(inside_formula && p_count >= 2 && tok.ttype != ' ') {
        formula_only = formula_only + token;
        //System.out.println("Formula only: " + formula_only);
        inside_formula = false;
      }
      
      
      //end of formula, reset temp variables
      if (p_count == 0 && tok.ttype == '.') {
        
        //System.out.println("Formula only: -" + formula_only + "-");
        if (formula_only.equals("$false")) {
          type = "false";
        }
        
        //System.out.println(" Formula: " + formula);
        //System.out.println(" ---");
        //System.out.println(" Type: " + type);
        //System.out.println(" Equality? " + equality);
        if (parents.isEmpty()) {
          //System.out.println(" no parents");
        }
        for (j = 0; j < parents.size(); j++) {
          //System.out.println(" Parents: " + parents.elementAt(j).toString());
        }
        formulas.add(new Formula(name, format, type, formula, parents, equality, 
                                 formulas, ftable));
        //System.out.println(" Formula: c:" + c_count + " p: " + p_count + ", " + formula);
        //System.out.println(" Formula: " + formula);
        ftable.put(name, new Integer (f_count++));

        c_count = 0;              //comma count
        p_count = 0;              //parenthesis count
        b_count = 0;              //bracket count

        token = "";               //each token string
        formula = "";             //entire formula dump
        name = "";                //formula string name (should be number)
        format = "";              //formula format (cnf, fof)
        type = "";                //formula type
        formula_only = "";        //just formula dump
        parents = new Vector();   //parents of this formula
        
        name_set = false;         //check if formula name is set
        type_set = false;         //check if formula type is set
        parent_check = false;     //check if at parent part of formula
        has_parents = false;      //true if formula has parents
        pass_parents = false;     //true if passed parents part of formula
        inside_formula = false;   //true if inside formula
        equality = false;         //true if resolved by equality
      }      
    } // while loop

    return new IDGraph (formulas, ftable, idv);
  }
}
