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
//*****************************************************************************

/*********************
 * ProofReader Class
 *    Reads a Proof in tptp format
 *    Converts to a graph
 *********************/
public class TPTPReader {

  public static final int TPTP_EOL_DELIMETER = '\\'; //delimeter for new line is backslash '\\'

  public static Graph readTPTP (Reader in, String coord, IDV idv)
    throws Exception {
    BufferedReader bin = new BufferedReader(in);

    return readTPTP(bin, coord, idv);    
  }

  private static void gatherParents (SimpleTptpParserOutput.Source source, Vector<String> parents) {
    for (SimpleTptpParserOutput.ParentInfo p : ((SimpleTptpParserOutput.Source.Inference)source).getParentInfoList()) {
      SimpleTptpParserOutput.Source psource = p.getSource();
      if (psource._kind == SimpleTptpParserOutput.Source.Kind.Inference) {
        gatherParents(psource, parents);
      } else if (!(p.toString()).contains("(") && !(p.toString()).contains(")")){
        parents.add(p.toString());
      }
    }
  }

  public static Graph readTPTP(BufferedReader in, String coord, IDV idv)
    throws Exception {

    // TptpParser variables
    TptpLexer lexer = new TptpLexer(in);
    TptpParser parser = new TptpParser(lexer);
    SimpleTptpParserOutput outputManager = new SimpleTptpParserOutput();

    // IDV variables
    IDGraph g = null;    
    Vector formulas = new Vector();
    Hashtable ftable = new Hashtable();

    int f_count = 0;

    // Parse each formula at a time
    for (SimpleTptpParserOutput.TopLevelItem item = 
           (SimpleTptpParserOutput.TopLevelItem)parser.topLevelItem(outputManager);
         item != null;
         item = (SimpleTptpParserOutput.TopLevelItem)parser.topLevelItem(outputManager)) {
      System.out.println("loop count: " + f_count);
      String format = "";
      String name = "";
      String type = "";
      String formula = "";
      SimpleTptpParserOutput.Annotations annotations = null;
      String sourceInfo = "";
      String annotationInfo = "";
      Vector parents = new Vector();
      boolean equality = false;
      boolean theorem = false;
      boolean split = false;
      boolean falseclause = false;
      double interesting_value = 0;
      boolean verified = false;
      
      //System.out.println("loop count: " + f_count);
      //System.out.println("------------");
      //System.out.println(item.toString());
      
      if (item.getKind() == SimpleTptpParserOutput.TopLevelItem.Kind.Formula) {
        format = "fof";
        SimpleTptpParserOutput.AnnotatedFormula AF = ((SimpleTptpParserOutput.AnnotatedFormula)item);
        //System.out.println(AF.toString());
        name = AF.getName();
        type = AF.getRole().toString();
        formula = AF.getFormula().toString("  ");
        annotations = AF.getAnnotations();          
      } else {
        format = "cnf";
        SimpleTptpParserOutput.AnnotatedClause AC = ((SimpleTptpParserOutput.AnnotatedClause)item);
        //System.out.println(AC.toString());
        name = AC.getName();
        type = AC.getRole().toString();
        formula = AC.getClause().toString("  ");
        annotations = AC.getAnnotations();
      }
      if (formula.equals("  $false"))
        falseclause = true;
      if (annotations != null) {
        annotationInfo = annotations.toString("  ");
        if (annotations.usefulInfo() != null) {
          for (SimpleTptpParserOutput.InfoItem info : annotations.usefulInfo()) {
            String infoString = info.toString("");
            if (infoString.contains("interesting(")) {
              if (info._kind == SimpleTptpParserOutput.InfoItem.Kind.GeneralFunction) {
                SimpleTptpParserOutput.GeneralTerm term = ((SimpleTptpParserOutput.InfoItem.GeneralFunction)info).getGeneralFunction();
                interesting_value = Double.parseDouble(((LinkedList)term.getArguments()).get(0).toString());
                if (interesting_value < 0)
                  interesting_value = 0;         
              }
            }    
            if (infoString.contains("verified(thm)")) {
              verified = true;
            }
          }
        }    
        SimpleTptpParserOutput.Source source = annotations.getSource();        
        sourceInfo = source.toString("  ");
        if (sourceInfo.contains("status(thm)")) 
          theorem = true;            
        if (sourceInfo.contains("theory(equality)"))
          equality = true;
        if (source._kind == SimpleTptpParserOutput.Source.Kind.Inference) {
          Iterable<SimpleTptpParserOutput.InfoItem> infoList = ((SimpleTptpParserOutput.Source.Inference)source).getUsefulInfo();
          if (infoList != null) {
            for (SimpleTptpParserOutput.InfoItem info : infoList) {
              String infoString = info.toString("");
              if (infoString.contains("_split")) {
                split = true;
              }
            }
          }
          gatherParents(source,parents);
        } else {
          if (!sourceInfo.contains("  ")) {
            //System.out.println("weird parent");
            parents.add(sourceInfo);
            sourceInfo = "  " + sourceInfo;
          }
        }
      }
      //System.out.println("name: " + name);
      //System.out.println("format: " + format);
      //System.out.println("type: " + type);
      //System.out.println("formula: " + formula);
      //System.out.println("annotation: " + annotationInfo);
      //   for (int j = 0; j < parents.size(); j++) {
      //  System.out.print("p : " + j + " " + (String)parents.elementAt(j));
      //}
      if (parents.size() == 0) {
        //System.out.println(" empty parents");
      }
      Formula f = new Formula(name, format, type, formula, annotationInfo, parents, 
                              equality, theorem, split, falseclause, interesting_value, 
                              verified, formulas, ftable);
      formulas.add(f);
      ftable.put(name, new Integer(f_count++));
      //System.out.println("...next...");        
    }    
    if (idv.applet != null) {
      idv.applet.showStatus("Done processing formulas, creating graph, one moment please...");
    }
    //System.out.println("Done parsing, create graph1");
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


  public static boolean readAgint (Vector axioms, Vector all, Vector formulas,  Hashtable ftable, IDV idv, boolean alc)
  throws Exception {  
    String Axioms = "", All = "";
    String derivation = "";

    // set up axiom string
    for (int i = 0; i < axioms.size(); i++) {
      String formula = ((IDNode)axioms.elementAt(i)).getFormula().getFormulaDump();
      Axioms += formula + "\n";
      //All += formula + "\n";
      derivation += formula + "\n";
    }

    // set up all string
    for (int i = 0; i < all.size(); i++) {
      String formula = ((IDNode)all.elementAt(i)).getFormula().getFormulaDump();
      All += formula + "\n";
      derivation += formula + "\n";
    }

    

    //System.out.println("Axioms set: \n" + Axioms);
    //System.out.println("All set: \n" + All);
    Hashtable<String,Object> URLParameters = new Hashtable<String,Object>();

    URLParameters.put("NoHTML",new Integer(1));
    URLParameters.put("QuietFlag","-q4");
    URLParameters.put("X2TPTP","-S");
    
    URLParameters.put("System___System","AGInTRater---0.0");
    URLParameters.put("TimeLimit___TimeLimit",100);
    URLParameters.put("ProblemSource","FORMULAE");
    URLParameters.put("FORMULAEProblem",derivation);
    URLParameters.put("SubmitButton","RunSelectedSystems");

    try {
      BufferedReader response = new BufferedReader(new InputStreamReader(ClientHttpRequest.post(new URL(IDV.SystemOnTPTPFormReplyURL),URLParameters)));
      String responseLine;
      while ((responseLine = response.readLine()) != null) {
        System.out.println(responseLine);
      }
      response.close();
    } catch (Exception ioe) {
      System.err.println("Exception: " + ioe.getMessage());
    }


    String in = "";

    try {
      URL url;
      URLConnection urlConn;
      DataOutputStream printout;
      DataInputStream input;
      
      // URL of CGI-Bin script.
      //url = new URL("http://lee.cs.miami.edu/cgi-bin-strac/AddInteresting.pl");
      url = new URL("http://www.cs.miami.edu/~tptp/cgi-bin/AGInT/AddInterestingNew.pl");
      //url = idv.URLs.AGInT_URL;
      //url = new URL(idv.URLs.AGInT_URL);
      //url = new URL("http://localhost:8080/cgi-bin-strac/AddInteresting.pl");
      
      
      // URL connection channel.
      urlConn = url.openConnection();
      
      // Let the run-time system (RTS) know that we want input.
      urlConn.setDoInput (true);
      
      // Let the RTS know that we want to do output.
      urlConn.setDoOutput (true);
      
      // No caching, we want the real thing.
      urlConn.setUseCaches (false);
      
      // Specify the content type.
      urlConn.setRequestProperty
        ("Content-Type", "application/x-www-form-urlencoded");
      
      // Send POST output.
      printout = new DataOutputStream (urlConn.getOutputStream ());
      
      String content =
        "Axioms=" + URLEncoder.encode (Axioms) +
        "&All=" + URLEncoder.encode (All);
      
      printout.writeBytes (content);
      printout.flush ();
      printout.close ();
      
      // Get response data.
      input = new DataInputStream (urlConn.getInputStream ());
      
      String str;
      //System.out.println("this is the data input stream");
      while (null != ((str = input.readLine()))) {
        //System.out.println (str);
        in += str;
      }
      //System.out.println("done reciving");
      input.close ();
      
    }
    catch (MalformedURLException me) {
      System.err.println("MalformedURLException: " + me);
    }
    catch (IOException ioe) {
      System.err.println("IOException: " + ioe.getMessage());
    }    
    
    StringReader reader = new StringReader(in);
    TptpLexer lexer = new TptpLexer(reader);
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
      String annotationInfo = "";
      double interesting_value = 0;
      
      //System.out.println("item: " + i++);
      //System.out.println(item.toString());

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
        annotationInfo = annotations.toString("  ");
        if (annotations.usefulInfo() != null) {
          for (SimpleTptpParserOutput.InfoItem info : annotations.usefulInfo()) {
            String infoString = info.toString("");
            if (infoString.contains("interesting(")) {
              //System.out.println("info string interesting: " + infoString);
              if (info._kind == SimpleTptpParserOutput.InfoItem.Kind.GeneralFunction) {
                //System.out.println("info string description: " + ((SimpleTptpParserOutput.InfoItem.GeneralFunction)info).getGeneralFunction());
                SimpleTptpParserOutput.GeneralTerm term = ((SimpleTptpParserOutput.InfoItem.GeneralFunction)info).getGeneralFunction();
                //System.out.println("its function: " + term.getFunction());
                //System.out.println("arguments: " + term.getArguments());
                interesting_value = Double.parseDouble(((LinkedList)term.getArguments()).get(0).toString());
                if (interesting_value < 0) {
                  interesting_value = 0;
                }
              }
              ////System.out.println("info string description: " + ((SimpleTptpParserOutput.InfoItem.Description)info).getDescription());
            }
          }
        }
      }
      Integer loc = (Integer)ftable.get(name);
      Formula f = (Formula)formulas.elementAt(loc.intValue());
      if ((alc && f.isALC()) || (!alc && !f.isALC())) {
        f.setInteresting(interesting_value);
        f.setAnnotation(annotationInfo);
      }
    }
    return true;
  }

}
