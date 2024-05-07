//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   IDV - Interactive Derivation Viewer
*/
//*****************************************************************************
/*****
 * Build on to GraphMan by Dr. Christian Duncan (Thanks!)
 ****/
//*****************************************************************************
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.event.*;
import java.net.URL;
import java.io.*;
import java.util.*;
import java.io.StreamTokenizer;
import java.net.*;
//*****************************************************************************

public class IDV extends JFrame
  implements ActionListener, ChangeListener {
   public static final String
       IMG_PATH = "images/",
       DEFAULT_FILE_PATH = "/home/duncan/projects/GD2004/GraphMan",
       TK_TITLE = "Tool Kit",                   // Toolkit info, actions, commands, etc...
       
   // File Load and Save Commands
       TK_UNDO_IMG = "undo.png",
       TK_UNDO_TEXT = "Undo last Spring Embedder Action",
       TK_UNDO_ALT = "Undo",
       UNDO_CMD = "Undo",
       TK_FILESAVE_IMG = "filesave.png",
       TK_FILESAVE_TEXT = "Save the Graph",
       TK_FILESAVE_ALT = "Save",
       FILESAVE_CMD = "Save",
       TK_FILELOAD_IMG = "fileopen.png",
       TK_FILELOAD_TEXT = "Load the Graph",
       TK_FILELOAD_ALT = "Load",
       FILELOAD_CMD = "Load",
       
   // Zoom In and Out, etc...
       TK_ZOOMIN_IMG = "viewmag+.png",
       TK_ZOOMIN_TEXT = "Zoom In",
       TK_ZOOMIN_ALT = "ZoomIn",
       ZOOMIN_CMD = "Zoom In",
       TK_ZOOMOUT_IMG = "viewmag-.png",
       TK_ZOOMOUT_TEXT = "Zoom Out",
       TK_ZOOMOUT_ALT = "ZoomOut",
       ZOOMOUT_CMD = "Zoom Out",
       /*
         // TK_ZOOM100_IMG = "Zoom100.jpg",
         TK_ZOOM100_IMG = "viewmag+.png",
         TK_ZOOM100_TEXT = "100% viewing",
         TK_ZOOM100_ALT = "1:1",
         ZOOM100_CMD = "No Zoom (1:1)",
       */
       TK_FIT_TO_WINDOW_IMG = "viewmag.png",
       TK_FIT_TO_WINDOW_TEXT = "Fit graph to Window",
       TK_FIT_TO_WINDOW_ALT = "Fit",
       FIT_TO_WINDOW_CMD = "Zoom To Fit",
       
       TK_CROSSING_TITLE = "Crossing Kit",
       TK_CROSSTRACKER_IMG = null,
       TK_CROSSTRACKER_TEXT = "Track Crossings (Real-Time, disable for speed)",
       TK_CROSSTRACKER_ALT = "Crossings",
       CROSSTRACKER_CMD = "CrossTracker",
       
       TK_SPRING_EMBEDDER_IMG = "springembedder.png",
       TK_SPRING_EMBEDDER_TEXT = "Open Spring Embedder Window",
       TK_SPRING_EMBEDDER_ALT = "Spring Embedder",
       SPRING_EMBEDDER_CMD = "SpEmbedder",
       
   // And quit
       QUIT_CMD = "Quit";

  /****** GUI Material ******/
  GraphPanel     gridScreen;          // The graph panel stores the graph
  SpringEmbedder springEmbedderWindow;
  JScrollPane    scroller;
  JTextArea      textField;
  JFrame         textWindow;
  JTextArea      textWindowField;
    
   // Main entry point for the program
   public static void main (String args[]) {
     IDV win = new IDV();

      win.setVisible(true);
      if (args.length > 0) {
	  // First argument is name of graph file
	  //    Maybe more features added later
	  win.loadFile(new File(args[0]));
      }
   }

   /***************************
      * The constructor.
      * Main job: Coordinate the initial layout
      *           by creating buttons, menubars, etc.
      ***************************/
   public IDV() {
      super();    // Not really necessary (default action)
      //setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);

      setTitle ("GraphProofTree");
      this.setSize(800,600);

      makePanel();

      // Create a simple window listener for exiting
      this.addWindowListener(new WindowAdapter() {
         public void windowClosing(WindowEvent e) {
         }
      });
   }

   /********************************
      * Makes the Main Panel
      *    Creates the main items for the panel
      ********************************/
   void makePanel() {
      // JFrame's have a Container (pane)
      // to where all other Components are added.
      JButton button;
      Container pane = this.getContentPane();
      pane.setLayout(new BorderLayout());  // Main Panel has BorderLayout

      // Create the main Grid Screen
      gridScreen = new GraphPanel();
      scroller = new JScrollPane(gridScreen);

      // Create the SpringEmbedder Window (linked to gridScreen)
      springEmbedderWindow = new SpringEmbedder(gridScreen);

      // Set up the toolbar
      JToolBar tools = new JToolBar(TK_TITLE);

      // Add Zoom In Button
      button = GraphManTools.
	  makeActionButton(TK_ZOOMIN_IMG, TK_ZOOMIN_TEXT,
			   TK_ZOOMIN_ALT, ZOOMIN_CMD, this);
      tools.add(button);
      
      // Add Fit To Window Height Button
      button = GraphManTools.
	  makeActionButton(TK_FIT_TO_WINDOW_IMG, TK_FIT_TO_WINDOW_TEXT,
			   TK_FIT_TO_WINDOW_ALT, FIT_TO_WINDOW_CMD, this);
      tools.add(button);

      // Add Zoom Out Button
      button = GraphManTools.
	  makeActionButton(TK_ZOOMOUT_IMG, TK_ZOOMOUT_TEXT,
			   TK_ZOOMOUT_ALT, ZOOMOUT_CMD, this);
      tools.add(button);

      tools.addSeparator();

      // Add Spring Embedder Button
      button = GraphManTools.
	  makeActionButton(TK_SPRING_EMBEDDER_IMG, TK_SPRING_EMBEDDER_TEXT,
			   TK_SPRING_EMBEDDER_ALT, SPRING_EMBEDDER_CMD,
			   this);
      tools.add(button);

      // Add Spin Box for text field
      SpinnerNumberModel model = new SpinnerNumberModel(5,1,15,1);
      JSpinner spin = new JSpinner(model);
      spin.setName("ProofWindow");
      spin.setToolTipText("TIP");
      spin.addChangeListener(this);
      tools.addSeparator();
      tools.add(spin);
      tools.addSeparator(new Dimension(1000,16));

      //pane.add(tools, BorderLayout.PAGE_START);
      tools.setFloatable(false);
      pane.add(tools, BorderLayout.NORTH);
      pane.add(scroller, BorderLayout.CENTER);
      //pane.add(gridScreen, BorderLayout.CENTER);

      textField = new JTextArea("",5,10);
      textField.setEditable(false);
      //JScrollPane scrollField = new JScrollPane(textField);
      textField.setText("Highlight a formula to display.");
      //pane.add(scrollField, BorderLayout.SOUTH);
      pane.add(textField, BorderLayout.SOUTH);

   }


  /********************************
   * stateChanged
   *     A state changed (of a Spinner)
   ********************************/
  public void stateChanged(ChangeEvent e) {
    System.out.println("state change");
    JSpinner source = (JSpinner) e.getSource();
    if (source.getName() == "ProofWindow") {
      int val = ((Integer)source.getValue()).intValue();
      textField.setRows(val);
      invalidate();
    } else {
      System.err.println("Error: Did you forget to catch a spinner?");
    }
  }




  /********************************
   * actionPerformed
   *     An Action was selected.   Deal with it!
   ********************************/
  public void actionPerformed(ActionEvent e) {
    String actionMessage = e.getActionCommand();
    
    // Use == instead of .equals for speed (are SAME string constants!)
    if (actionMessage == FILELOAD_CMD) {
      // Load (from Menu Bar)
      loadFile();
    } 
    else if (actionMessage == ZOOMIN_CMD) {
      zoomIn();
    } else if (actionMessage == ZOOMOUT_CMD) {
      zoomOut();
    } else if (actionMessage == FIT_TO_WINDOW_CMD) {
      fitToWindow();
    } else if (actionMessage == SPRING_EMBEDDER_CMD) {
      springEmbedderWindow.setVisible(true);
    } else if (actionMessage == UNDO_CMD) {
      if (!gridScreen.undoEmpty()) {
        gridScreen.undo();
      } else {
        beep();
      }
    } else if (actionMessage.equals(QUIT_CMD)) {
      if (JOptionPane.showConfirmDialog(null,"Are you sure ?")==JOptionPane.YES_OPTION) {
        setVisible(false);
        dispose();
      }
    }
    System.out.println("done with action performer");
  }
  

    /**
       A rudimentary way to make a little beep.
    **/
    void beep() { 
	System.out.print("\07"); System.out.flush();
    }

   /**
      GUI to load a graph from file
   **/
   void loadFile() {
      JFileChooser open = new JFileChooser(DEFAULT_FILE_PATH);  // Use current directory location
      if (open.showOpenDialog(this) != JFileChooser.APPROVE_OPTION)
         return;  // Cancelled or Error occurred

      loadFile(open.getSelectedFile());
   }

   void loadFile(File f) {
      // Try to open the selected file
      FileReader file;
      try {
	  file = new FileReader(f);
      } catch (Exception err) {
	  JOptionPane.showMessageDialog (this,
					 "Unable to Open specified File. " +
					 "Make sure that the file exists\n" +
					 "and that you have enough permissions to " +
					 "read the file.",
					 "File Load Error",
					 JOptionPane.ERROR_MESSAGE);
	  return;
      }

      try {
        //Graph gr = GraphReader.readGD4(file);
        Graph gr = TPTPReader.readTPTP(file, this);
        gridScreen.setGraph(gr);
        gridScreen.clearUndoInfo();  // New file!
        invalidate();
      } catch (Exception e) {
         JOptionPane.showMessageDialog (this,
                                        "Unable to Read specified File. Reason given:\n" +
                                        e.getMessage(),
                                        "File Load Error",
                                        JOptionPane.ERROR_MESSAGE);
      }

      // Close it no matter what...
      try { file.close(); } catch (Exception e) { }
   }

  public static void test (Reader in) {
    StreamTokenizer tok = new StreamTokenizer(in);
    try {
      tok.nextToken();
    }
    catch (IOException e) {}
    System.out.println("tester next tok proof reader: " + tok.toString());
  }

  

  void loadString(String in) {

     textField.setText("loading string");
      // Try to open the selected file
      StringReader reader;
      reader = new StringReader(in);

      try {
        Graph gr = TPTPReader.readTPTP(reader, this);
        gridScreen.setGraph(gr);
        gridScreen.clearUndoInfo();  // New graph!
        invalidate();
        System.out.println("Loading this string: \n" + in);
        textField.setText("loading string completedd \n");
        textField.append("num nodes" + gr.numNodes());
        textField.append("num nodes" + gr.numEdges());
      } catch (Exception e) {
         JOptionPane.showMessageDialog (this,
                                        "Unable to Process Input String. Reason given:\n" +
                                        e.getMessage(),
                                        "Param Parsing Error",
                                        JOptionPane.ERROR_MESSAGE);
      }
   }


  void loadURL(String in) {

    try {
    URL url = new URL(in);
    BufferedReader bin = new BufferedReader(new InputStreamReader(url.openStream()));
        System.out.println("Loading this URL: \n" + in);
        System.out.println("yea4");
        Graph gr = TPTPReader.readTPTP(bin, this);
        System.out.println("yea1");
        gridScreen.setGraph(gr);
        System.out.println("yea2");
        gridScreen.clearUndoInfo();  // New graph!
        System.out.println("yea3");
        gridScreen.fitToWindow();


        System.out.println("Loading this url: \n" + in);
        textField.setText("loading url completedd \n");
        textField.append("num nodes" + gr.numNodes());
        textField.append("num nodes" + gr.numEdges());

      } catch (Exception e) {
         JOptionPane.showMessageDialog (this,
                                        "Unable to Process Input URL. Reason given:\n" +
                                        e.getMessage(),
                                        "Param Parsing Error",
                                        JOptionPane.ERROR_MESSAGE);
      }
   }

   /**
      * zoomIn()
    * Zoom the graph in a click
    **/
   void zoomIn() {
      gridScreen.zoomIn();
   }

   /**
      * zoomOut()
    * Zoom the graph out a click
    **/
   void zoomOut() {
      gridScreen.zoomOut();
   }

   /**
      * zoom100()
    * Set zoom level to 100%
    **/
   void zoom100() {
      gridScreen.setZoomLevel(1.0);
   }

   /**
      * fitToWindow()
    *      Compute best zoom level for fitting to window
    **/
   void fitToWindow() {
       gridScreen.fitToWindow();
   }

}

