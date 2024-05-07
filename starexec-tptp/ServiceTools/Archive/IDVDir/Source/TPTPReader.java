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
import java.net.*;
import java.util.regex.*;
import tptp_parser.*;
import ClientHttpRequest.*;
//*****************************************************************************

/*********************
 * ProofReader Class
 *    Reads a Proof in tptp format
 *    Converts to a graph
 *********************/
public class TPTPReader {

  /* remove leading whitespace */
  public static String ltrim(String source) {
    return source.replaceAll("^\\s+", "");
  }
  
  /* remove trailing whitespace */
  public static String rtrim(String source) {
    return source.replaceAll("\\s+$", "");
  }
  
  /* replace multiple whitespaces between words with single blank */
  public static String itrim(String source) {
    return source.replaceAll("\\b\\s{2,}\\b", " ");
  }
  
  /* remove all superfluous whitespaces in source string */
  public static String trim(String source) {
    return itrim(ltrim(rtrim(source)));
  }
  
  public static String lrtrim(String source){
    return ltrim(rtrim(source));
  }

  public static final int TPTP_EOL_DELIMETER = '\\'; //delimeter for new line is backslash '\\'

  private static void gatherParents (SimpleTptpParserOutput.Source source, Vector<String> parents) {
//DEBUG System.out.println("gatherParents for ===" + source + "====");
    String sourceInfo;
    int comma;
    String pstring;

    sourceInfo = source.toString();
//----pparent([...]) overrides logical parents
    if (sourceInfo.matches(".*pparent\\(\\[.*\\]\\).*")) {
        sourceInfo = sourceInfo.substring(sourceInfo.indexOf("pparent([")+9);
        sourceInfo = sourceInfo.substring(0,sourceInfo.indexOf("])"));
//DEBUG System.out.println("pparents are " + sourceInfo);
        while ((comma = sourceInfo.indexOf(',')) >= 0) {
            pstring = sourceInfo.substring(0,sourceInfo.indexOf(','));
//DEBUG System.out.println("adding pparent " + pstring);
            parents.add(pstring);
            sourceInfo = sourceInfo.substring(sourceInfo.indexOf(',')+1);
        }
        parents.add(sourceInfo);
//DEBUG System.out.println("adding last pparent " + sourceInfo);
    } else {
      for (SimpleTptpParserOutput.ParentInfo p : ((SimpleTptpParserOutput.Source.Inference)source).getParentInfoList()) {
//DEBUG System.out.println("consider parent ===" + p + "===");
        SimpleTptpParserOutput.Source psource = p.getSource();
        if (psource.getKind() == SimpleTptpParserOutput.Source.Kind.Inference) {
          gatherParents(psource, parents);
        } else {
          pstring = psource.toString();
//DEBUG System.out.println("psource is ===" + pstring + "===");
          if (!(psource.toString().contains("(") && psource.toString().contains(")"))) {
//DEBUG System.out.println("adding parent ===" + pstring + "===");
            parents.add(pstring);
          }
        } 
      }
    }
  }

  public static IDGraph readTPTP (Reader in, BufferedReader coord, IDV idv)
    throws Exception {
    BufferedReader bin = new BufferedReader(in);
    //    System.out.println("IN: " + bin.readLine());
    return readTPTP(bin, coord, idv);    
  }
  public static IDGraph readTPTP(BufferedReader in, BufferedReader coord, IDV idv)
    throws Exception {
    //    System.out.println("BIN: " + in.readLine());
    // TptpParser variables
    TptpLexer lexer = new TptpLexer(in);
    TptpParser parser = new TptpParser(lexer);
    SimpleTptpParserOutput outputManager = new SimpleTptpParserOutput();

    // IDV variables
    IDGraph g = null;    
    Vector<Formula> formulas = new Vector();
    Hashtable ftable = new Hashtable();

    int f_count = 0;
//DEBUG System.out.println("start loop");
    // Parse each formula at a time
    for (SimpleTptpParserOutput.TopLevelItem item = 
           (SimpleTptpParserOutput.TopLevelItem)parser.topLevelItem(outputManager);
         item != null;
         item = (SimpleTptpParserOutput.TopLevelItem)parser.topLevelItem(outputManager)) {
//DEBUG System.out.println("loop count: " + f_count);
      String format = "";
      String name = "";
      String type = "";
      String formula = "";
      SimpleTptpParserOutput.Formula.Kind kind = null;
      SimpleTptpParserOutput.ThfFormula.Kind thfKind = null;
      SimpleTptpParserOutput.Annotations annotations = null;
      SimpleTptpParserOutput.Source source = null;
      Iterable<SimpleTptpParserOutput.InfoItem> usefulList = null;
      String sourceInfo = "";
      //String annotationInfo = "";
      Vector parents = new Vector();
      boolean equality = false;
      boolean theorem = true;
      boolean split = false;
      boolean falseclause = false;
      boolean assumption = false;
      double interesting_value = -2;
      boolean verified = false;
      
      String regex;
      Pattern pattern;
      Matcher matcher;

//DEBUG System.out.println("loop count: " + f_count);
//DEBUG System.out.println("------------");
      //System.out.println(item.toString());
      
      if (item.getKind() == 
SimpleTptpParserOutput.TopLevelItem.Kind.ThfFormula) {
        format = "thf";
        SimpleTptpParserOutput.AnnotatedThfFormula AF = ((SimpleTptpParserOutput.AnnotatedThfFormula)item);
        name = AF.getName();
//----Unstructured hack to ignore type declarations
        if (AF.getRole() == TptpParserOutput.FormulaRole.Type) {
//DEBUG System.out.println("ignoring\n" + AF.toString());
            continue;
        } else {
            type = AF.getRole().toString();
        }
        thfKind = AF.getFormula().getKind();
        if (thfKind == SimpleTptpParserOutput.ThfFormula.Kind.Binary) {
          formula = AF.getFormula().toString(6);
        } else {
          formula = AF.getFormula().toString(4);
        }
        annotations = AF.getAnnotations();          
//DEBUG System.out.println(AF.toString());
      } else if (item.getKind() == 
SimpleTptpParserOutput.TopLevelItem.Kind.Formula) {
        format = "fof";
        SimpleTptpParserOutput.AnnotatedFormula AF = ((SimpleTptpParserOutput.AnnotatedFormula)item);
        name = AF.getName();
        type = AF.getRole().toString();
        kind = AF.getFormula().getKind();
        if (kind == SimpleTptpParserOutput.Formula.Kind.Binary) {
          formula = AF.getFormula().toString(6);
        } else {
          formula = AF.getFormula().toString(4);
        }
        annotations = AF.getAnnotations();          
        //        System.out.println(AF.toString());
      } else if (item.getKind() == 
SimpleTptpParserOutput.TopLevelItem.Kind.Clause) {
        format = "cnf";
        SimpleTptpParserOutput.AnnotatedClause AC = ((SimpleTptpParserOutput.AnnotatedClause)item);
        name = AC.getName();
        type = AC.getRole().toString();
        formula = AC.getClause().toString(6);
        annotations = AC.getAnnotations();
        //        System.out.println(AC.toString());
      } else {
        throw(new Exception("Unknown TPTP formula type"));
      }
      if (formula.equals("$false"))
        falseclause = true;
      if (annotations != null) {
        // deal with source part of annotations
        source = annotations.getSource();        
        sourceInfo = source.toString(4);
        // if sourceinfo contains the regex status(...) and its not status(thm), then not a theorem
        regex = "status\\(([^t]|t[^h]|th[^m]).{0,2}\\)";
        pattern = Pattern.compile(regex);
        matcher = pattern.matcher(sourceInfo);
        if (matcher.find()) {
          theorem = false;
//DEBUG System.out.println("SUCCESS!!! Found non theorem status!!!");
        }
        //if (sourceInfo.contains(Formula.FORMULA_STATUS_THM)) 
        //  theorem = true;            
        if (sourceInfo.contains(Formula.FORMULA_THEORY_EQUALITY))
          equality = true;
        if (source.getKind() == SimpleTptpParserOutput.Source.Kind.Inference) {
          Iterable<SimpleTptpParserOutput.InfoItem> infoList = ((SimpleTptpParserOutput.Source.Inference)source).getUsefulInfo();
          if (infoList != null) {
            for (SimpleTptpParserOutput.InfoItem info : infoList) {
              String infoString = info.toString(4);
              if (infoString.matches(".*\\([a-z][a-z]*_split,.*") ||
infoString.matches(".*\\(split,.*")) {
                split = true;
              }
              // if non-empty list of assumption, then this formula an assumption
              regex = "assumptions\\(\\[.+\\]\\)";
              pattern = Pattern.compile(regex);
              matcher = pattern.matcher(infoString);
              if (matcher.find()) {
                System.out.println("this is assumption: " + name);
                assumption = true;
              }
            }
          }
          gatherParents(source,parents);
//DEBUG System.out.println("formula ===" + formula + "===");
//DEBUG for (Object s : parents) {
//DEBUG System.out.println("---" + s + "---");
//DEBUG }
        } else {
          if (!sourceInfo.contains("(") && !sourceInfo.contains(")")) {
            //            System.out.println("weird parent");
            parents.add(sourceInfo);
            sourceInfo = "  " + sourceInfo;
          }
        }
        // deal with usefulInfo part of annotations
        usefulList = annotations.usefulInfo();
        if (usefulList != null) {
          for (SimpleTptpParserOutput.InfoItem info : usefulList) {
            String usefulInfo = info.toString();
            if (usefulInfo.contains("interesting(")) {
              if (info.getKind() == SimpleTptpParserOutput.InfoItem.Kind.GeneralFunction) {
                SimpleTptpParserOutput.GeneralTerm term = ((SimpleTptpParserOutput.InfoItem.GeneralFunction)info).getGeneralFunction();
                interesting_value = Double.parseDouble(((LinkedList)term.getArguments()).get(0).toString());
                if (interesting_value < 0)
                  interesting_value = 0;         
              }
            }    
            if (usefulInfo.contains("verified(thm)")) {
              verified = true;
            }
          }
        }    
      }
      //      System.out.println("parents size: " + parents.size());
      Formula f = new Formula(name, 
                              format, 
                              type, 
                              formula, 
                              //annotationInfo, 
                              kind,
                              source,
                              usefulList,
                              parents, 
                              equality, 
                              theorem, 
                              split, 
                              falseclause, 
                              assumption,
                              interesting_value, 
                              verified, 
                              formulas, 
                              ftable);
      formulas.add(f);
      ftable.put(name, new Integer(f_count++));
//DEBUG System.out.println("...next...");        
    }    
    System.out.println("Done reading");

    // check to make sure all parents are valid, if not valid, remove
    

    // add ancestor lists to all formulas
    for (Formula f : formulas) {
      f.setAncestor();
    }
    //    System.out.println("set ancestor done");
    // set split parents
    for (Formula f : formulas) {
      f.setSplitParent();
    }
    //    System.out.println("set split parent done");
    // buffer names for centering
    for (Formula f : formulas) {
      f.bufferName();
    }
    //System.out.println("buffer name done");
    if (idv.applet != null) {
      idv.applet.showStatus("Done processing formulas, creating graph, one moment please...");
    }
    System.out.println("Done parsing, create graph");
    return new IDGraph(formulas, ftable, coord, idv);
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


  public static boolean readAgint (String derivation, Vector formulas,  Hashtable ftable, IDV idv)
  throws Exception {  

    Hashtable<String,Object> URLParameters = new Hashtable<String,Object>();

    URLParameters.put("NoHTML",new Integer(1));
    URLParameters.put("QuietFlag","-q4");
    URLParameters.put("X2TPTP","-S");
    
    URLParameters.put("System___System","AGInTRater---0.0");
    URLParameters.put("TimeLimit___TimeLimit",100);
    URLParameters.put("ProblemSource","FORMULAE");
    URLParameters.put("FORMULAEProblem",derivation);
    URLParameters.put("SubmitButton","RunSelectedSystems");

    System.out.println("derivation: " + derivation);

    try {
      idv.textField.setText("Computing interesting ratings.  One moment please...");
      BufferedReader response = new BufferedReader(new InputStreamReader(ClientHttpRequest.post(new URL(IDV.SystemOnTPTPFormReplyURL),URLParameters)));
      TptpLexer lexer = new TptpLexer(response);
      TptpParser parser = new TptpParser(lexer);
      SimpleTptpParserOutput outputManager = new SimpleTptpParserOutput();
      //System.out.println("TPTPParser completed, extract interestingness");
      // Parse each formula at a time
      int i = 0;
      for (SimpleTptpParserOutput.TopLevelItem item = 
             (SimpleTptpParserOutput.TopLevelItem)parser.topLevelItem(outputManager);
           item != null;
           item = (SimpleTptpParserOutput.TopLevelItem)parser.topLevelItem(outputManager)) {
        String name = "";
        SimpleTptpParserOutput.Annotations annotations = null;
        double interesting_value = 0;
        Iterable<SimpleTptpParserOutput.InfoItem> usefulList = null;
      
        if (item.getKind() == SimpleTptpParserOutput.TopLevelItem.Kind.Formula) {
          SimpleTptpParserOutput.AnnotatedFormula AF = ((SimpleTptpParserOutput.AnnotatedFormula)item);
          name = AF.getName();
          annotations = AF.getAnnotations();          
        } else {
          SimpleTptpParserOutput.AnnotatedClause AC = ((SimpleTptpParserOutput.AnnotatedClause)item);
          name = AC.getName();
          annotations = AC.getAnnotations();
        }
        if (annotations != null) {
          usefulList = annotations.usefulInfo();
          if (usefulList != null) {
            for (SimpleTptpParserOutput.InfoItem info : usefulList) {
              String usefulInfo = info.toString();
              if (usefulInfo.contains("interesting(")) {
                if (info.getKind() == SimpleTptpParserOutput.InfoItem.Kind.GeneralFunction) {
                  SimpleTptpParserOutput.GeneralTerm term = ((SimpleTptpParserOutput.InfoItem.GeneralFunction)info).getGeneralFunction();
                  interesting_value = Double.parseDouble(((LinkedList)term.getArguments()).get(0).toString());
                  if (interesting_value < 0) {
                    interesting_value = 0;
                  }
                }
              }
            }
            Integer loc = (Integer)ftable.get(name);
            Formula f = (Formula)formulas.elementAt(loc.intValue());
            f.setInteresting(interesting_value);
            f.setUsefulInfo((LinkedList)usefulList);
          }
        }
      }
      idv.textField.setText("Interesting ratings computed.");
    } catch (Exception ioe) {
      System.err.println("Exception: " + ioe.getMessage());
    }

    return true;
  }

}
