//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   IDNode - Interactive Derivation Node
*/
//*****************************************************************************
import java.util.*;
import java.io.*;
//*****************************************************************************
public class IDNode extends Node {

  public static final String
    FORMULA_FORMAT_FOF = "fof",
    FORMULA_FORMAT_CNF = "cnf",

    FORMULA_TYPE_INITIAL = "initial",
    FORMULA_TYPE_AXIOM   = "axiom",
    FORMULA_TYPE_PLAIN   = "plain",
    FORMULA_TYPE_CONJ    = "conjecture",
    FORMULA_TYPE_NEG_CONJ_D = "negatedconjecturederived",
    FORMULA_TYPE_NEG_CONJ   = "negatedconjecture",
    FORMULA_TYPE_FALSE   = "false",
    FORMULA_TYPE_HYP     = "hypothesis",
    FORMULA_TYPE_LEMMA   = "lemma";
  
  Color fofColor = Color.black;
  Color cnfColor = Color.orange;

  private IDGraph g;      // the idgraph itself
  private Formula f;      // formula of this idnode
  private IDV     idv;    // viewer
  private int     rank;   // rank in derivation tree


  // non virtual node constructor
  public IDNode (int _id, Formula _f, ProofGraph _g) {
    //boolean virtual = false;
    super(_id, false, _g.gridScreen);
    f = _f;
    g = _g;
    rank = _f.getDepth();
  }
  // virtual node constructor
  public IDNode (int _id, int _rank, ProofGraph _g) {
    //boolean virtual = true;
    super(_id, true, _g.gridScreen);
    f = null;
    g = _g;
  }

  /* Accessor methods */
  public int getRank () { return rank; }
  public Formula getFormula () { return f; }

  //Formula accessor method for extended class ProofNode
  abstract Formula getFormula ();  

  public void setPolygon () {
    Formula f = getFormula();
    if (sp != null) {
      //set polygon based on formula type
      if (f.getType().equals(FORMULA_TYPE_AXIOM) || 
          f.getType().equals(FORMULA_TYPE_INITIAL)) {
        setAxiomNode();      
      } else if (f.getType().equals(FORMULA_TYPE_CONJ)) {
        setConjectureNode();
      } else if (f.getType().equals(FORMULA_TYPE_NEG_CONJ) ||
                 f.getType().equals(FORMULA_TYPE_NEG_CONJ_D)) {
        setNegatedConjectureNode();
      } else if (f.getType().equals(FORMULA_TYPE_FALSE)) {
        setFalseNode();
      } else {
        setPlainNode();
      }
    }
  }

  public void paint (Graphics2D g) {
    if (virtual) { return; }  //don't draw virtual nodes

    Formula f = getFormula();
    if (f == null) {
      System.out.println("no formula"); //problem
      System.exit(-1);
      //g.drawString(getName(), (int)x + 5, (int)y + 5);
      return;
    }

    //get color
    if (f.getFormat().equals(FORMULA_FORMAT_CNF)) {
      //color blue
      sp.setColor(cnfColor);              
    }
    else if (f.getFormat().equals(FORMULA_FORMAT_FOF)) {
      //color green
      sp.setColor(fofColor);              
    }
    else {
      System.out.println("Format not found, failure");  //only two formats atm
      System.exit(-1); 
    }
    sp.paint(g);
    if (f.equality) {
      //draw little circle on top of node
      g.fillOval((int)x - scale/4, (int)y - scale - scale/2, scale/2, scale/2);
    }
  }
  
  private void setAxiomNode () {
    //upside down triangle
    /*
          ----
          \  /
           \/
           x, y (0,0)
           -50,-50, +50,-50, 0,50

    /*
    if (sp.npoints != 4) {
      System.out.println("Should have only 4 points, instead, # points: " + sp.npoints);
      System.exit(-1);
    }
    */
    int dx = (int)x;
    int dy = (int)y;
    sp.reset();   //alternative is use invalidate() and set 3 points manually
    sp.addPoint(dx - scale, dy - scale);
    sp.addPoint(dx + scale, dy - scale);
    sp.addPoint(dx        , dy + scale);
  }

  private void setPlainNode () {
    //regular circle
    int dx = (int)x;
    int dy = (int)y;
    sp.reset();
    /*
FOR(i=0;i<NUM_LINES;i++){
	xcoord = l * cos(i*2*PI/NUM_LINES);
	ycoord = l * sin(i*2*PI/NUM_LINES);	
    */
    for (int i = 0; i < 20; i++) {
      sp.addPoint((int)(scale * Math.cos(i*2*Math.PI/20) + dx),
             (int)(scale * Math.sin(i*2*Math.PI/20) + dy));
    }
  }

  private void setConjectureNode () {
    //draw house
    /*      /\
           /  \
           |  | 
            --
           50,50 50,0 0,-50 -50,0, -50,50
    */
    sp.reset();
    int dx = (int)x;
    int dy = (int)y;
    sp.addPoint(dx + scale, dy + scale);
    sp.addPoint(dx + scale, dy        );
    sp.addPoint(dx        , dy - scale);
    sp.addPoint(dx - scale, dy        );
    sp.addPoint(dx - scale, dy + scale);
  }

  private void setNegatedConjectureNode () {
    //draw upsidedown house
    /*      --
           |  |
           \  / 
            \/
           -50,-50 -50,0 0,50, 50,0, 50,-50
    */
    sp.reset();
    int dx = (int)x;
    int dy = (int)y;
    sp.addPoint(dx - scale, dy - scale);
    sp.addPoint(dx - scale, dy        );
    sp.addPoint(dx        , dy + scale);
    sp.addPoint(dx + scale, dy        );
    sp.addPoint(dx + scale, dy - scale);
  }

  private void setFalseNode () {
    //draw rectangle
    /*      --
           |  |
           |  |
            --
           -50,-50 -50,50 50,50, 50,-50
    */
    sp.reset();
    int dx = (int)x;
    int dy = (int)y;
    sp.addPoint(dx - scale, dy - scale);
    sp.addPoint(dx - scale, dy + scale);
    sp.addPoint(dx + scale, dy + scale);
    sp.addPoint(dx + scale, dy - scale);
  }

  private void setHypothesisNode () {
    //draw upside down trapezoid
  }

  private void setLemmaNode () {
    //draw hexagon
  }


  

}
