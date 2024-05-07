/*****************************************************************************
//*****************************************************************************
/*
  Steven Trac
  Formula Class
*/
//*****************************************************************************
import java.io.*;
import java.util.*;
import tptp_parser.*;
//*****************************************************************************

public class Formula {

  public static final String
    FORMULA_SOURCE_CREATOR = "superman",

    FORMULA_STATUS_THM = "status(thm)",
    FORMULA_STATUS_SAB = "status(sab)",
    FORMULA_STATUS_UNK = "status(unk)",
    FORMULA_THEORY_EQUALITY = "theory(equality)",

    FORMULA_FORMAT_THF = "thf",
    FORMULA_FORMAT_FOF = "fof",
    FORMULA_FORMAT_CNF = "cnf",

    FORMULA_TYPE_INITIAL = "initial",
    FORMULA_TYPE_AXIOM   = "axiom",
    FORMULA_TYPE_ASSUMPTION   = "assumption",
    FORMULA_TYPE_PLAIN   = "plain",
    FORMULA_TYPE_CONJ    = "conjecture",
    FORMULA_TYPE_NEG_CONJ_D = "negatedconjecturederived",
    FORMULA_TYPE_NEG_CONJ   = "negated_conjecture",
    FORMULA_TYPE_HYP     = "hypothesis",
    FORMULA_TYPE_THEOREM = "theorem",
    FORMULA_TYPE_LEMMA   = "lemma",
    FORMULA_TYPE_DEFINITION   = "definition",
    FORMULA_TYPE_TYPE   = "type";

  //variables
  private String name;               //name of formula
  private String unbuffedName;
  private String format;             //formula type: cnf or fof or thf
  private String type;               /*
                               axiom, 
                               plain, (derived)
                               conjecture,
                               negated_conjecture,
                               $false,
                               hypothesis,
                               lemma,
                             */
  private String formula;            //entire tptp formula

  private Vector parents;            //parent formulas of this formula
  private Vector ancestor;           //ancestor list of formula parents
  private int depth = -1;            //depth of formula in the proof tree
  private Vector formulas;           //list of formulas
  private Hashtable ftable;          //hashtable of formulas, hashing on 'name' of formula
  
  private boolean pinY = false;      //PIN Y OR NOT  (currently not used)
  private boolean equality = false;  //see if node had equality parent
  private boolean theorem = true;    //see if formula was a valid thm
  private boolean false_clause = false;     //false clause formula = $false

  private boolean split_child = false;  //im a split child, my parent is the split
  private boolean split_parent = false; //im a split parent, one of my children is the split 

  private double interesting_value;
  private boolean verified = false;
  private boolean assumption = false;
  //  private boolean alc = false; //axiom logical consequence

  //SimpleTptpParserOutput.Annotations annotation;
  private SimpleTptpParserOutput.Formula.Kind kind;
  private SimpleTptpParserOutput.Source source;  
  private String usefulInfo;

  //constructor
  public Formula (String name, 
                  String format, 
                  String type, 
                  String formula,
                  //SimpleTptpParserOutput.Annotations annotation, 
                  SimpleTptpParserOutput.Formula.Kind kind,
                  SimpleTptpParserOutput.Source source,
                  Iterable<SimpleTptpParserOutput.InfoItem> usefulList,
                  Vector parents, 
                  boolean equality, 
                  boolean theorem, 
                  boolean split, 
                  boolean false_clause,
                  boolean assumption,
                  double interesting_value, 
                  boolean verified, 
                  Vector formulas, 
                  Hashtable ftable) {
    this.unbuffedName = name;
    this.name     = name;
    this.format   = format;
    this.type     = type;
    this.formula  = formula;
    this.parents  = parents;
    this.equality = equality;
    this.interesting_value = interesting_value;
    this.verified = verified;
    this.formulas = formulas;
    this.ftable   = ftable;
    this.theorem  = theorem;
    this.false_clause = false_clause;
    this.assumption   = assumption;
    this.split_child  = split;
    ancestor = new Vector();
    //this.annotation = annotation;
    this.kind     = kind;
    this.source   = source;
    setUsefulInfo((LinkedList)usefulList);
  }


  /*
    1      ___1__
    11     __11__
    111    _111__
    1111   _1111_
    11111  _11111
  */
  
  public void bufferName () {
    int n = name.length();

    if (n >= 6) 
      return;

    if (n <= 0) {
      System.out.println("Name is less than 1 in length");
      System.exit(-1);
    }

    //name is less than 6 characters, add spaces for centering
    int s = 6 - n;
    int h = s / 2;
    String front = "";
    String back = "";
    for (int i = 0 ; i < s - h; i++) {
      front = front + "  ";
    }
    for (int i = 0; i < h; i++) {
      back = back + "  ";
    }
    name = front + name + back;
  }
  
  public String getUnbuffedName () { return unbuffedName; }
  public String getName () { return name; }
  public String getFormat () { return format; }
  public String getType () { return type; }
  public String getFormulaDump () { return getFormulaDump(""); }
  public String getFormulaDump (String indent) {  
    return getMutatedFormulaDump(indent, format, type, null);
  }
  public String getMutatedFormulaDump (String indent, String mutatedFormat, 
                                       String mutatedType, String mutatedSource) {
    String buf = "    ";
    String res = indent + mutatedFormat + "(" + unbuffedName + "," + mutatedType + ",";
    if (mutatedFormat.equals("cnf") || (kind != null && kind == SimpleTptpParserOutput.Formula.Kind.Binary)) {      
      res += "\n" + buf + "( ";
      res += formula;
      res += " )";
    } else {
      res += "(\n" + buf;
      res += formula;
      res += " )";
    }
    String sourceString = mutatedSource;
    if (sourceString == null) {
      if (source != null) {
        sourceString = source.toString();
      } else {
        sourceString = "";
      } 
    }
    if (sourceString.length() != 0) {
      res += ",\n" + indent + buf + sourceString;
    }
    if (usefulInfo.length() != 0) {
      res += ",\n" + indent + buf + usefulInfo;
    }
    res += ").";
    return res;
  }

  public SimpleTptpParserOutput.Source getSource () { return source; }
  public Vector getParents () { return parents; }
  public Vector getAncestors () { return ancestor; }
  public double getInteresting () { return interesting_value; }

  public boolean isInteresting (double threshhold) { return interesting_value >= threshhold; }
  public boolean isEquality () { return equality; }
  public boolean isTheorem () { return theorem; }
  public boolean isSplitChild () { return split_child; }
  public boolean isSplitParent () { return split_parent; }
  public boolean isFalseClause () { return false_clause; }
  public boolean isVerified () { return verified; }
  public boolean isAssumption () { return assumption || type.equals(Formula.FORMULA_TYPE_ASSUMPTION); }
  //  private boolean isALC () { return alc; }

  //  public void setALC (boolean flag) { alc = flag; }
  public void setInteresting (double i) { interesting_value = i; }
  //public void setAnnotation (String _annotation) { annotation = _annotation; }
  public void setUsefulInfo (LinkedList<SimpleTptpParserOutput.InfoItem> usefulList) {
    this.usefulInfo = "";
    if (usefulList != null) { 
      String res = "";
      res += "[";
      res += modifyUsefulTerm((usefulList.get(0)).toString());
      for (int n = 1; n < usefulList.size(); ++n) 
        res += "," + modifyUsefulTerm((usefulList.get(n)).toString());
      res += "]";
      this.usefulInfo = res;
    } else {
      this.usefulInfo = "";
    }    
  }
  private String modifyUsefulTerm (String unmodified) {
    String modified = "";
    //    if (unmodified.contains("interesting")) {
      for (int i = 0; i < unmodified.length(); i ++) {
        if (unmodified.charAt(i) != '+') modified += unmodified.charAt(i);
      }
      //    }
    return modified;
  }
  public void setAncestor () {    
    //for each parent, add this to the parent ancestor list
//DEBUG System.out.println("setting ancestors for : " + this.getName());
    for (int i = 0; i < parents.size(); i++) {
//DEBUG System.out.println("parent ===" + parents.elementAt(i).toString() + "===");
      Integer loc = (Integer)ftable.get((parents.elementAt(i)).toString());
      if (loc == null) 
        continue;
      Formula f = (Formula)formulas.elementAt(loc.intValue());
      if (f == null)
        continue;
      f.addAncestor(this);
    }      
  }
  private void addAncestor (Formula f) {
    ancestor.add(f.getName());
  }

  public int getDepth () { 
    if (!hasDepth())
      dfsDepth();
    return depth; 
  }
  public void dfsDepth () {
    if (!hasDepth()) {
//DEBUG System.out.println("need to do dfsDepth on f: " + getName());
      if (parents.isEmpty()) {
        depth = 0;
      } else {
        for (int i = 0; i < parents.size(); i++) {
//DEBUG System.out.println("look for parent " + i);
          if ((ftable.containsKey((parents.elementAt(i)).toString()))) {
            Integer loc = (Integer)ftable.get((parents.elementAt(i)).toString());
            Formula f = (Formula)formulas.elementAt(loc.intValue());
            int max = f.getDepth();
//DEBUG System.out.println("consider parent " + f.getName() + " with depth " + max);
            if (max > depth) {
              depth = max;
            }
          } else {
            parents.remove(i);
            i--;
          }
        }
        depth++;              
      }
    } else {
//DEBUG System.out.println("no need to do dfsDepth on f: " + getName());
    }
  }

  public void setDepth (int _depth) { depth = _depth; }
  private boolean hasDepth () { return depth > -1; }

  public int getNearestParent () {
    int max = -1;
    for (int i = 0; i < parents.size(); i++) {
      Integer loc = (Integer)ftable.get((parents.elementAt(i)).toString());
      int current = ((Formula)formulas.elementAt(loc.intValue())).depth;
      if (current > max) 
        max = current;
    }
    return max;
  }

  public int getNearestAncestor () {
    if (ancestor.size() > 0) {
      int min = ((Formula)ancestor.elementAt(0)).depth;
        for (int i = 1; i < ancestor.size(); i++) {
          int current = ((Formula)ancestor.elementAt(i)).depth;
          if (current < min) 
        min = current;
        }
      return min;
    } else {
      return 0;
    }
  }

  public void setSplitParent () {
    if (!(split_child && parents.size() == 1))
      return;
    
    for (int i = 0; i < parents.size(); i++) {
      Integer loc = (Integer)ftable.get((parents.elementAt(i)).toString());
      Formula f = (Formula)formulas.elementAt(loc.intValue());
      f.split_parent = true;
    }
  }
  
  public void show () {
    System.out.println("Formula: " + getName() + ", Depth: " + depth);
    for (int i = 0; i < parents.size(); i++) {
      Integer loc = (Integer)ftable.get((parents.elementAt(i)).toString());
      Formula f = (Formula)formulas.elementAt(loc.intValue());
      System.out.println(" Parent: " + f.getName() + ", Depth: " + f.depth);
    }
    for (int i = 1; i < ancestor.size(); i++) {
      Formula f = (Formula)ancestor.elementAt(i);
      System.out.println(" Ancestor: " + f.getName() + ", Depth: " + f.depth);
    }
  }

}

//*****************************************************************************
//*****************************************************************************
