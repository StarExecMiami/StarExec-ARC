import java.io.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.font.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class ATPToolBar {
  public static final String

    TK_GO_IMG = "GoCanes.jpg",
    TK_GO_TEXT = "GO",
    TK_GO_ALT = "GO",
    GO_CMD = "GOCANES",

    TK_ERASE_IMG = "Eraser.png",
    TK_ERASE_TEXT = "Reset all verified formulae",
    TK_ERASE_ALT = "ERASE",
    ERASE_CMD = "ERASE",

    TK_GDV_TRUE_IMG = "GDV-on.png",
    TK_GDV_FALSE_IMG = "GDV-off.png",
    TK_GDV_TEXT = "GDV for verification",
    TK_GDV_ALT = "GDV",
    GDV_CMD = "GDV",

    TK_TREE_IMG = "PalmTree.jpg",
    TK_TREE_TEXT = "New IDV Window",
    TK_TREE_ALT = "Click for New IDV Window",
    TREE_CMD = "TREE";

  JComboBox ATPComboBox    = null;
  JTextField TimeField     = null;
  JToggleButton GDVTButton = null;
  JToolBar ToolBar         = null;
  
  ATPToolBar () {
  }

  public static ATPToolBar createATPToolBar (Vector ATPList,
                                             JComboBox ATPComboBox, 
                                             JTextField TimeField,
                                             ActionListener listener) {
    
    ATPToolBar atptoolbar = new ATPToolBar();

    // build tool bar
    JToolBar tools = new JToolBar("Tool Bar");
    tools.setFloatable(false);

    // add atp list
    ATPComboBox = new JComboBox(ATPList);
    Dimension d = ATPComboBox.getPreferredSize();
    d.width = 300;
    ATPComboBox.setPreferredSize(d);
    ATPComboBox.setMaximumSize(ATPComboBox.getPreferredSize());
    ATPComboBox.setMinimumSize(ATPComboBox.getPreferredSize());
    ATPComboBox.invalidate();    
    if (ATPComboBox.getItemCount() > 6) {
      ATPComboBox.setSelectedIndex(6);
    }
    ATPComboBox.addActionListener(listener);
    ATPComboBox.setToolTipText("Select system from list");
    tools.add(ATPComboBox);
    tools.addSeparator();
    
    // add time limit box
    TimeField = new JTextField("300");    
    TimeField.setEditable(true);
    d.width = 50;
    TimeField.setPreferredSize(d);
    TimeField.setMaximumSize(TimeField.getPreferredSize());
    TimeField.setMinimumSize(TimeField.getPreferredSize());
    TimeField.invalidate();    
    TimeField.setToolTipText("Input Time Limit for selected system");
    tools.add(TimeField);
    tools.addSeparator();

    // add GDV button
    JToggleButton tbutton = GraphManTools.
      makeToggleButton(TK_GDV_FALSE_IMG, TK_GDV_TRUE_IMG, TK_GDV_TEXT,
                       TK_GDV_ALT, GDV_CMD, true, listener);
    tools.add(tbutton);

    // add go button
    JButton button = GraphManTools.makeActionButton(TK_GO_IMG, TK_GO_TEXT,
                                                    TK_GO_ALT, GO_CMD, listener);
    tools.add(button);

    // add erase button
    button = GraphManTools.makeActionButton(TK_ERASE_IMG, TK_ERASE_TEXT,
                                            TK_ERASE_ALT, ERASE_CMD, listener);
    tools.add(button);

    atptoolbar.ATPComboBox = ATPComboBox;
    atptoolbar.TimeField = TimeField;
    atptoolbar.GDVTButton = tbutton;
    atptoolbar.ToolBar = tools;

    return atptoolbar;
  }
}


