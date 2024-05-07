import java.lang.Object;
import java.awt.*;
import java.util.*;

public class BezierCurve {
  
  public Point p[];
  
  public BezierCurve (Point p1, Point p2, Point p3, Point p4) {
    p = new Point[4];
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    p[3] = p4;
  }
}

