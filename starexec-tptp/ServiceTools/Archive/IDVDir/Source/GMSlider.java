/********************************
 Christian Duncan
 Adds a more descriptive oriented JSlider
 As nob slides value changes below
 In addition, this value does not need to grow
 linearly.   A function is provided to the
 class that allows the value to change in many ways.
*********************************/

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.text.*;

public class GMSlider extends JPanel
    implements ChangeListener {
    public static final int HORIZONTAL = JSlider.HORIZONTAL;
    public static final int VERTICAL = JSlider.VERTICAL;
    public JSlider slider;
    public JLabel valueLabel;
    public Function func;
    public ChangeListener listener;
    public String gmName;
    public GMSlider(int orientation, int min, int max, int val,
		    Function _func) {
	func = _func;
	setLayout(new BoxLayout(this,BoxLayout.Y_AXIS));

	slider = new JSlider(orientation, min, max, val);
	slider.addChangeListener(this);
	valueLabel = new JLabel();
	setNumericLabel();

	add(slider);
	add(valueLabel);
    }

  public void setGMName (String name) { gmName = name; }
  public String getGMName () { return gmName; }

    public void setName(String name) {
      //super.setName(name);
      super.setName("");
      setNumericLabel();
    }

    public void addChangeListener(ChangeListener l) { 
	listener = l;
    }

    public double getValue() {
	if (func != null) { 
	    return func.f(slider.getMinimum(), 
			  slider.getMaximum(), 
			  slider.getValue());
	} else {
	    return slider.getValue();
	}
    }

    public boolean getValueIsAdjusting() {
	return slider.getValueIsAdjusting();
    }

    public void stateChanged(ChangeEvent e) {
	// Set the label
	setNumericLabel();

	// Create new ChangeEvent
	listener.stateChanged(new ChangeEvent(this));
    }

    /**
       Set the label associated with 
       this particular GMSlider
       Value is based on the result of
       a call to the associated Function
    **/
    private void setNumericLabel() {
	double compVal = getValue();
	NumberFormat formatter = NumberFormat.getNumberInstance();
	valueLabel.setText(getName() + formatter.format(compVal));
    }

    public static class Function { 
	double f(int min, int max, int val) { return val; }
    }
}

