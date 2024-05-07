import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

/**
 * Generic applet application.  A small front-end is needed to get around the
 * problem of no multiple inheritance.  This class should be subclassed to 
 * choose the proper editor and converter or to add additional functionality.
 *
 */

import javax.swing.*;

public class IDVStringApplet extends JApplet {
  IDV win;
  
  public void init(){
    String in = getParameter("TPTP");
    
    //System.out.println("Hi there: " + in);
    
    win = new IDV();
    win.loadString(in);
    win.setVisible(true);
  }
}
