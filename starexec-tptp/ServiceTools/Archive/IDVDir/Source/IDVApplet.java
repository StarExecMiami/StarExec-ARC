//import netscape.javascript.*;
import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.net.*;

/**
 * Generic applet application.  A small front-end is needed to get around the
 * problem of no multiple inheritance.  This class should be subclassed to 
 * choose the proper editor and converter or to add additional functionality.
 *
 */


public class IDVApplet extends JApplet {
  JTextArea textField;
  IDV win;

  public void init(){

    int TPTPIndex;
    String tptpPart;
    String tptp;
    String url = getParameter("URL");
    String coord = getParameter("COORD");
    String coord_url = getParameter("COORD_URL");

    tptp=getParameter("TPTP");

    if (tptp == null) {
        TPTPIndex = 1;
        tptp = "";
        tptpPart = getParameter("TPTP" + TPTPIndex);
        while (tptpPart != null) {
//DEBUG System.out.println("New part ===" + tptpPart + "====");
            tptp += tptpPart + "\n\n";
            TPTPIndex++;
            tptpPart = getParameter("TPTP" + TPTPIndex);
        }
        if (tptp.equals("")) {
            tptp=null;
        }
    }

    System.out.println("TPTP: " + tptp);
    System.out.println("URL: " + url);

    textField = new JTextArea();
    getContentPane().setLayout(new BorderLayout());
    getContentPane().add("Center",textField);
    //textField.setText("One moment please.  Loading IDV (Interactive Derivation Viewer)...\n");
    /*
    try {
      getAppletContext().showDocument(new URL("."), "popup");
      System.out.println("url call open new window");
    } catch (Exception e) {
      System.out.println("trouble opening page: " + e);
    }
    */
    win = new IDV(this, null, true);
    WindowListener wl = new WindowAdapter() {
        public void windowClosing(WindowEvent e) {
          System.out.println("Exiting");
          textField.setText("Thanks for using IDV (Interactive Derivation Viewer)!\n");
          textField.setText("If you still see this window, close manually please!\n");
          closePage();
        }
        public void windowOpened(WindowEvent e) {
          System.out.println("Window opened: " + e.paramString());
          //show the window
          win.fitToWindowHeight();
          //win.setSize(win.gridScreen.getWidth(),win.getSize().height);
          win.show();
        }
        public void windowIconified(WindowEvent e) {
          //System.out.println("Window iconified" + e.paramString());
          //textField.setText("IDV is currently minimized.\n");
        }
        public void windowDeiconified(WindowEvent e) {
          //System.out.println("Window deiconified" + e.paramString());
        }
        public void windowActivated(WindowEvent e) {
          //System.out.println("Window activated" + e.paramString());
        }
        public void windowDeactivated(WindowEvent e) {
          //System.out.println("Window deactivated" + e.paramString());
        }
      };
    BufferedReader tptpReader = null;
    BufferedReader coordReader = null;
    try {
      if (tptp != null) {      
        tptpReader = new BufferedReader(new StringReader(tptp));
      } else if (url != null) {
        tptpReader = new BufferedReader(new InputStreamReader((new URL(url)).openStream()));
      } else {
        System.out.println("No TPTP formulae or URL");
      }
      //      System.out.println(tptpReader.readLine());
    } catch (Exception e) {
      JOptionPane.showMessageDialog (this,
                                     "Unable to process tptp/url from applet tag parameters:\n" +
                                     e.toString(),
                                     "Param Parsing Error",
                                     JOptionPane.ERROR_MESSAGE);
    }
    try {
      if (coord_url != null) {
        coordReader = new BufferedReader(new InputStreamReader((new URL(coord_url)).openStream()));
      }
      if (coord != null) {
        coordReader = new BufferedReader(new StringReader(coord));
      }
    } catch (Exception e) {
      JOptionPane.showMessageDialog (this,
                                     "Unable to process coord/coord_url from applet tag parameters:\n" +
                                     e.toString(),
                                     "Param Parsing Error",
                                     JOptionPane.ERROR_MESSAGE);
    }
    win.addWindowListener(wl);
    System.out.println("Load reader");
    win.loadReader(tptpReader, coordReader);
    textField.append("Loading derivation");
    this.setVisible(false);
    win.setVisible(true);
    win.show();
    /*
    if (tptp != null) {
      win.loadString(tptp, coord, coord_url);
      textField.append("Loading from parameter 'TPTP'\n");
      this.setVisible(false);
    } else {
      textField.append("Loading from parameter 'URL'\n");
      win.loadURL(url, coord, coord_url);
      win.validate();
      this.setVisible(false);
    }
    */
    //getContentPane().setVisible(false);
    //getContentPane().setVisible(false);
  }

  public void closePage () {
    try {
      getAppletContext().showDocument(new URL("javascript:window.close()"));
      //getAppletContext().showDocument(new URL("javascript:window.write(\"f\")"));
    }
    catch (Exception ee) {
      System.out.println("Trouble closing page: " + ee);
    }
  }

}
