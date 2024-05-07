/***********************************
 * GraphManTools
 * Represents a collection of useful tools
 * for the GraphMan classes...
 ***********************************/
// package GD4;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;
import java.awt.image.*;
import java.net.URL;
import java.io.*;

public class GraphManTools {
  public static final String
    IMG_PATH = "images/";

  public static URL getImageURL (String img) {
    String imgFileName = IMG_PATH+img;
    ClassLoader cl = GraphManTools.class.getClassLoader();
    URL imageURL = cl.getResource(imgFileName);
    if (imageURL == null) {
      System.err.println("Warning: Resource not found: " + imgFileName);
    } 
    return imageURL;
  }
     
  /********************************
   * makeActionButton
   *    Creates an Action Button from the given parameters
   ********************************/
  public static JButton makeActionButton(String img, String tipText, 
                                         String alt, String cmd, 
                                         ActionListener list) {
    JButton button = new JButton();
    
    button.setActionCommand(cmd);
    button.setToolTipText(tipText);
    button.addActionListener(list);
    // button.setText(alt);
    // button.setVerticalTextPosition(SwingConstants.BOTTOM);
    // button.setHorizontalTextPosition(SwingConstants.CENTER);
    
    //Look for the image.  (None yet so we'll ignore
    URL imageURL = GraphManTools.getImageURL(img);
    if (imageURL != null) {                      //image found
      button.setIcon(new ImageIcon(imageURL, alt));
    } else {                                     //no image found
      button.setText(alt);
    }
    
    Dimension d = new Dimension(25, 25);
    button.setPreferredSize(d);
    button.setMinimumSize(d);
    button.setMaximumSize(d);

    return button;
  }
  
  /********************************
   * makeCheckBox
   *    Creates a JCheckBox given the following parameters
   ********************************/

  public static JCheckBox makeCheckBox(String img, 
                                       String tipText, 
                                       String alt, 
                                       ItemListener list) {
    JCheckBox checkbox = new JCheckBox("", false);
    checkbox.setToolTipText(tipText);
    checkbox.addItemListener(list);
    
    //Look for the image.  (None yet so we'll ignore
    if (!img.equals("")) {
      URL imageURL = GraphManTools.getImageURL(img);
      System.out.println("image url: " + imageURL);
      String label = "<html><img src=" + imageURL + "></html>";    
      // Add the icon
      checkbox.setText(label);
      /*
      Dimension d = checkbox.getPreferredSize();
      d.width = 45;
      checkbox.setPreferredSize(d);
      checkbox.setMaximumSize(checkbox.getPreferredSize());
      checkbox.setMinimumSize(checkbox.getPreferredSize());
      */
    }

    Dimension d = new Dimension(50, 25);
    checkbox.setPreferredSize(d);
    checkbox.setMinimumSize(d);
    checkbox.setMaximumSize(d);

    return checkbox;
  }
  
  /********************************
   * makeToggleButton
   *    Creates a Toggle Button from the given parameters
   ********************************/
  public static JToggleButton makeToggleButton(String img, 
                                               String tipText, 
                                               String alt, String cmd,
                                               boolean isSelected,
                                               ActionListener list) {
    return makeToggleButton(img, null, tipText, alt, cmd, 
                            isSelected, list);
  }
  
  public static JToggleButton makeToggleButton(String img, 
                                               String imgSelected,
                                               String tipText, 
                                               String alt, String cmd,
                                               boolean isSelected,
                                               ActionListener list) {
    JToggleButton button = new JToggleButton();
    
    button.setActionCommand(cmd);
    button.setToolTipText(tipText);
    button.addActionListener(list);
    button.setSelected(isSelected);
    //    button.setText(alt);
    button.setVerticalTextPosition(SwingConstants.BOTTOM);
    button.setHorizontalTextPosition(SwingConstants.CENTER);
    
    if (img != null) {
      URL imageURL = GraphManTools.getImageURL(img);
      if (imageURL != null) {                      //image found
        button.setIcon(new ImageIcon(imageURL, alt));
      }
    }
    
    if (imgSelected != null) {
      //Look for the image.
      URL imageURL = GraphManTools.getImageURL(imgSelected);
      if (imageURL != null) {                      //image found
        button.setSelectedIcon(new ImageIcon(imageURL, alt));
      } 
    }
    
    Dimension d = new Dimension(25, 25);
    button.setPreferredSize(d);
    button.setMinimumSize(d);
    button.setMaximumSize(d);

    return button;
  }
  
  public static JSlider makeSlider(String name, String tipText, ChangeListener listener,
                                   int min, int max, int val) {
    JSlider slider = new JSlider(JSlider.HORIZONTAL, min, max, val);
    slider.setName(name);
    slider.setToolTipText(tipText);
    slider.addChangeListener(listener);
    return slider;
  }
  
  public static GMSlider makeGMSlider(String name, String tipText,
                                      ChangeListener listener,
                                      GMSlider.Function func,
                                      int min, int max, int val) {
    GMSlider slider = new GMSlider(GMSlider.HORIZONTAL, min, max, val,
                                   func);
    slider.setName(name);
    slider.setGMName(name);
    slider.setToolTipText(tipText);
    slider.addChangeListener(listener);

    Dimension d = new Dimension(100, 30);
    slider.slider.setFont(new Font("Courier", Font.PLAIN, 100));
    slider.setPreferredSize(d);
    slider.setMinimumSize(slider.getPreferredSize());
    slider.setMaximumSize(slider.getPreferredSize());

    return slider;
  }
}
