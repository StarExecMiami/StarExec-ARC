//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   IDVHelp - Interactive Derivation Viewer Help Menu
*/
//*****************************************************************************
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.SpringLayout;
import java.text.SimpleDateFormat;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.awt.image.*;
import java.util.*;
import java.io.*;
import java.net.*;
//*****************************************************************************

public class IDVHelp {
  public static final String
    
    ASSUMPTION_STAR_IMG = "AssumptionStar.GIF",
    DEFINITION_GOBLET_IMG = "DefinitionGoblet.GIF",
    INTRODUCED_TRIANGLE_IMG = "IntroducedTriangle.GIF",
    AXIOM_TRIANGLE_IMG = "AxiomTriangle.GIF",
    BULB_OFF_IMG = "BulbOff.GIF",
    BULB_ON_IMG = "BulbOn.GIF",
    CAT_EVIL_IMG = "CatEvil.GIF",
    CAT_GOOD_IMG = "CatGood.GIF",
    CHECK_OFF_IMG = "CheckOff.GIF",
    CHECK_ON_IMG = "CheckOn.GIF",
    CONJECTURE_HOUSE_IMG = "ConjectureHouse.GIF",
    EQUALS_CIRCLE_IMG = "EqualsCircle.GIF",
    ERASE_IMG = "Eraser.png",
    FALSE_SQUARE_IMG = "FalseSquare.GIF",
    FLAG_OFF_IMG = "FlagOff.GIF",
    FLAG_ON_IMG = "FlagOn.GIF",
    GDV_OFF_IMG = "GDVOff.GIF",
    GDV_ON_IMG = "GDVOn.GIF",
    GO_CANES_IMG = "GoCanes.GIF",
    HELP_IMG = "Help.GIF",
    LEMMA_DIAMOND_IMG = "LemmaDiamond.GIF",
    MAGNIFY_HEIGHT_IMG = "MagnifyHeight.GIF",
    MAGNIFY_MINUS_IMG = "MagnifyMinus.GIF",
    MAGNIFY_PLUS_IMG = "MagnifyPlus.GIF",
    MAGNIFY_WIDTH_IMG = "MagnifyWidth.GIF",
    NEGATED_CONJECTURE_HOUSE_IMG = "NegatedConjectureHouse.GIF",
    PALM_TREE_IMG = "PalmTree.GIF",
    PLAIN_CIRCLE_IMG = "PlainCircle.GIF",
    PROTECTION_OFF_IMG = "ProtectionOff.GIF",
    PROTECTION_ON_IMG = "ProtectionOn.GIF",
    RED_CIRCLE_IMG = "RedCircle.GIF",
    RED_LINE_OFF_IMG = "RedlineOff.GIF",
    RED_LINE_ON_IMG = "RedlineOn.GIF",
    REDO_IMG = "Redo.GIF",
    REDRAW_IMG = "Redraw.GIF",
    RED_TRIANGLE_IMG = "RedTriangle.GIF",
    SLIDER_IMG = "Slider.GIF",
    SUPERMAN_IMG = "Superman.GIF",
    THEOREM_HEXAGON_IMG = "TheoremHexagon.GIF",
    UNDO_IMG = "Undo.GIF";

  public static JFrame createAboutWindow (final IDVApplet applet) {
    JFrame aboutWindow = new JFrame("About IDV");
    String text = "";
    JEditorPane jep = new JEditorPane();
    JScrollPane sjep = new JScrollPane(jep);
    jep.setEditable(false);
    jep.setContentType("text/html");                            
    aboutWindow.setSize(450,280);
    aboutWindow.getContentPane().add(sjep, BorderLayout.CENTER);

    SimpleDateFormat sdf = new SimpleDateFormat("yyyy.MM.d");
    Calendar cal = Calendar.getInstance();

    text += "<HTML>\n";
    text += "<HEAD>\n";
    text += "<TITLE>IDV Help</TITLE>\n";
    text += "</HEAD>\n";
    text += "<BODY ALIGN=JUSTIFY>\n";
    text += "<hr>\n";
    text += "IDV - Interactive Derivation Verifier - Version." + sdf.format(cal.getTime()) + ": (<a href=\"http://www.cs.miami.edu/students/strac/projects/IDV/\">Project Homepage</a>)" + "<br>\n";
    text += "<p>\n";
    text += "Created by Steven C. Trac (<a href=\"http://www.cs.miami.edu/students/strac/\">Homepage</a>)" + "<br>\n";   
    text += "An ARTist project out of the University of Miami, FL" + "<br>\n";
    text += "Project Supervisor: Dr. Geoff Sutcliffe (<a href=\"http://www.cs.miami.edu/~geoff/\">Homepage</a>)" + "<br>\n";
    text += "Build on to GraphMan by Dr. Christian Duncan (<a href=\"http://www.cs.miami.edu/~duncan/\">Homepage</a>)" + "<br>\n";
    text += "<p>\n";
    text += "Thanks to Dr. Andrei Tchaltsev for his TPTP parser: (<a href=\"http://www.freewebs.com/andrei_ch/\">Homepage</a>)" + "<br>\n";
    text += "Thanks to the devx.com website for providing a POST requests solution from Java: (<a href=\"http://www.devx.com/Java/Article/17679/0/page/3\">Link</a>)" + "<br>\n";
    text += "The following help menu, written by Dr. Geoff Sutcliffe, also can be found here: <a href=\"http://www.cs.miami.edu/~tptp/IDVHelp/\">IDV Help </a><br>";
    text += "<hr>";
    text += "<p>";
    text += "Help Menu: <br>";

    text += "<UL>";
    text += "<LI> Seeing";
    text += "     <UL>";
    text += "     <LI> Shapes";
    text += "          <UL>";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(CONJECTURE_HOUSE_IMG) + "' ALT='ConjectureHouse'>";
    text += "               &nbsp;Conjecture";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(NEGATED_CONJECTURE_HOUSE_IMG) + "' ALT='NegatedConjectureHouse'>";
    text += "               &nbsp;Negated conjecture";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(DEFINITION_GOBLET_IMG) + "' ALT='DefinitionGoblet'>";
    text += "               &nbsp;Definition";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(AXIOM_TRIANGLE_IMG) + "' ALT='AxiomTriangle'>";
    text += "               &nbsp;Axiom";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(ASSUMPTION_STAR_IMG) + "' ALT='AssumptionStar'>";
    text += "               &nbsp;Assumption";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(INTRODUCED_TRIANGLE_IMG) + "' ALT='IntroducedTriangle'>";
    text += "               &nbsp;Introduced formula";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(PLAIN_CIRCLE_IMG) + "' ALT='PlainCircle'>";
    text += "               &nbsp;Plain";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(LEMMA_DIAMOND_IMG) + "' ALT='LemmaDiamond'>";
    text += "               &nbsp;Lemma";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(THEOREM_HEXAGON_IMG) + "' ALT='TheoremHexagon'>";
    text += "               &nbsp;Theorem";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(FALSE_SQUARE_IMG) + "' ALT='FalseSquare'>";
    text += "               <TT>$false</TT>";
    text += "          </UL>";
    text += "     <LI> Colors";
    text += "          <UL>";
    text += "          <LI> Cyan outline:";
    text += "               THF";
    text += "          <LI> Black outline:";
    text += "               FOF";
    text += "          <LI> Red outline:";
    text += "               CNF";
    text += "          </UL>";
    text += "     <LI> Inference tags";
    text += "          <UL>";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(EQUALS_CIRCLE_IMG) + "' ALT='EqualsCircle'>";
    text += "               &nbsp;Equality reasoning";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(RED_CIRCLE_IMG) + "' ALT='RedCircle'>";
    text += "               &nbsp;Non-logical consequence";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(RED_TRIANGLE_IMG) + "' ALT='RedTriangle'>";
    text += "               &nbsp;Split";
    text += "          </UL>";
    text += "     </UL>";
    text += "<P>";
    text += "<LI> Focussing";
    text += "     <UL>";
    text += "     <LI> Mouse over:";
    text += "          Colors the ancestors and descendants";
    text += "     <LI> Left click:";
    text += "          Popup inference formulae window ";
    text += "          <UL>";
    text += "          <LI> Verification control panel - see below";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(PALM_TREE_IMG) + "' ALT='PalmTree'>";
    text += "               &nbsp;Open SystemOnTSTP window with verification proof";
    text += "          </UL>";
    text += "     <LI> Control left click:";
    text += "          IDV for this node and its parents";
    text += "     <LI> Shift control left click:";
    text += "          IDV for this node and its ancestors";
    text += "     <LI> Control right click:";
    text += "          IDV for this node and its children and their parents";
    text += "     <LI> Shift control right click:";
    text += "          IDV for this node and its descendants and their parents";
    text += "     </UL>";
    text += "<P>";
    text += "<LI> Zooming";
    text += "     <UL>";
    text += "     <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(MAGNIFY_PLUS_IMG) + "' ALT='MagnifyPlus'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(MAGNIFY_MINUS_IMG) + "' ALT='MagnifyMinus'>";
    text += "          &nbsp;Zoom in/out 50%";
    text += "     <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(MAGNIFY_HEIGHT_IMG) + "' ALT='MagnifyHeight'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(MAGNIFY_WIDTH_IMG) + "' ALT='MagnifyWidth'>";
    text += "          &nbsp;Fit image to pane height/width";
    text += "     </UL>";
    text += "<P>";
    text += "<LI> Verifying";
    text += "     <UL>";
    text += "     <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(CHECK_OFF_IMG) + "' ALT='CheckOff'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(CHECK_ON_IMG) + "' ALT='CheckOn'>";
    text += "          &nbsp;Hide/display ticks on verified nodes";
    text += "     <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(FLAG_OFF_IMG) + "' ALT='FlagOff'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(FLAG_ON_IMG) + "' ALT='FlagOn'>";
    text += "          &nbsp;Start/stop verification process";
    text += "          <UL>";
    text += "          <LI> System pull down:";
    text += "               Trusted system for verification";
    text += "          <LI> Time limit:";
    text += "               Time limit in seconds for verifying (? each step of overall ?)";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(GDV_ON_IMG) + "' ALT='GDVOn'>";
    text += "               <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(GDV_OFF_IMG) + "' ALT='GDVOff'>";
    text += "               &nbsp;Verification controlled by GDV/IDV";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(GO_CANES_IMG) + "' ALT='GoCanes'>";
    text += "               &nbsp;Start verification process";
    text += "          <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(ERASE_IMG) + "' ALT='Erase'>";
    text += "               &nbsp;Reset verified formulae";
    text += "          </UL>";
    text += "     </UL>";
    text += "<P>";
    text += "<LI> Limiting";
    text += "     <UL>";
    text += "     <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(CAT_EVIL_IMG) + "' ALT='CatEvil'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(CAT_GOOD_IMG) + "' ALT='CatGood'>";
    text += "          &nbsp;Display/hide nodes that are not logical consequences of axioms";
    text += "     <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(RED_LINE_ON_IMG) + "' ALT='RedlineOn'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(RED_LINE_OFF_IMG) + "' ALT='RedlineOff'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(SLIDER_IMG) + "' ALT='Slider'>";
    text += "          &nbsp;Enable/disable redline slider,";
    text += "          raise/lower redline to hide nodes above redline";
    text += "     <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(BULB_OFF_IMG) + "' ALT='BulbOff'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(BULB_ON_IMG) + "' ALT='BulbOn'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(SLIDER_IMG) + "' ALT='Slider'>";
    text += "          &nbsp;Disable/ensable interestingness slider,";
    text += "          raise/lower interestingness threshold to hide less interesting nodes<BR>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(PROTECTION_ON_IMG) + "' ALT='ProtectionOn'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(PROTECTION_OFF_IMG) + "' ALT='ProtectionOff'>";
    text += "          &nbsp;Protect/unprotect leaves from being hidden<BR>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(REDRAW_IMG) + "' ALT='Redraw'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(UNDO_IMG) + "' ALT='Undo'>";
    text += "          <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(REDO_IMG) + "' ALT='Redo'>";
    text += "          &nbsp;Redraw derivation with only visible nodes (? does this apply to redline ?),";
    text += "          undo/redo redrawing to previous interestingness level";
    text += "     </UL>";
    text += "<P>";
    text += "<LI> Recursing";
    text += "     <UL>";
    text += "     <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(SUPERMAN_IMG) + "' ALT='Superman'>";
    text += "          &nbsp;Open SystemOnTSTP window with currently displayed nodes' formulae";
    text += "     </UL>";
    text += "<P>";
    text += "<LI> Helping";
    text += "     <UL>";
    text += "     <LI> <IMG HEIGHT='25' WIDTH='25' SRC='" + GraphManTools.getImageURL(HELP_IMG) + "' ALT='Help'>";
    text += "          &nbsp;Help";
    text += "     </UL>";
    text += "</UL>";
    text += "<P>";
    text += "<HR><!------------------------------------------------------------------------>";
    text += "</BODY>\n";
    text += "</HTML>\n";

    //jep.setText(text); 
//DEBUG System.out.println(text);

    jep.addHyperlinkListener(new HyperlinkListener() {
        public void hyperlinkUpdate(HyperlinkEvent event) {
          if (event.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {
            System.out.println("URL clicked: " + event.getURL());
            if (applet != null) {
              applet.getAppletContext().showDocument(event.getURL(),"_blank");
            }
          }
        }
      });

    return aboutWindow;
  }
}
