
import java.lang.Object;
import java.awt.*;
import java.util.*;

public class BezierChain {

  public Vector curves;

  void add (BezierCurve c) {
    curves.add(c);
  }
  int size () { return curves.size(); }
  BezierCurve get (int i) { return (BezierCurve)curves.elementAt(i); }
  Vector getCurves () { return curves; }
  void clear () { curves.clear(); }
  
  public void straightenChain (Vector points) {
    // look at first point and last point and get that vector
    // for each point from the first to the last
    // let a be a point, and b be the next point
    // if vector (b - a) and (last - a) is too far apart, throw b away
    Point last = (Point)points.elementAt(points.size()-1);
    for (int i = 0; i < points.size() - 2; i++) {
      Point a = (Point)points.elementAt(i);
      Point b = (Point)points.elementAt(i+1);
      Point v1 = new Point(b.x - a.x, b.y - a.y);
      Point v2 = new Point(last.x - a.x, last.y - a.y);     
      double d1 = a.distance(b);
      double d2 = a.distance(last);
      double t1 = (v1.x * v2.x + v1.y * v2.y) / (d1 * d2);
      double angle = Math.acos(t1);
      /*
      System.out.println("a(" + a.x + ", " + a.y + ")");
      System.out.println("b(" + b.x + ", " + b.y + ")");
      System.out.println("last(" + last.x + ", " + last.y + ")");
      System.out.println("v1(" + v1.x + ", " + v1.y + ")");
      System.out.println("v2(" + v2.x + ", " + v2.y + ")");
      System.out.println("d1: " + d1);
      System.out.println("d2: " + d2);
      double num = v1.x * v2.x + v1.y * v2.y;
      System.out.println("num: " + num);
      double den = d1 * d2;
      System.out.println("den: " + den);
      System.out.println("t1: " + t1);
      System.out.println("angle: " + angle);
      */
      if (angle > 1) {
        points.remove(i+1);
        i--;
      }
    }
  }

  public BezierChain (Node a, Node b, Vector points) {
    double a_before = ((IDNode)a).getRank() * IDGraph.YSPLIT;
    double a_after = a.getY();
    double b_before = ((IDNode)b).getRank() * IDGraph.YSPLIT;
    double b_after = b.getY();
    for (int i = 0; i < points.size(); i++) {
      Point p = (Point)points.elementAt(i);
      double t = (p.y - b_before) / (a_before - b_before);
      p.y = (int)((1 - t) * b_after + t * a_after);
    }
    
    curves = new Vector();

    straightenChain(points);
    
    //take begin, end, and two middle points
    if (points.size() < 2) {
      System.out.print("not enough points, only: " + points.size());
      //System.exit(0);
    }
    
    if (points.size() == 2) {
      Point p1 = (Point)points.elementAt(0);
      Point p2 = (Point)points.elementAt(1);
      Point p3 = new Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
      points.add(1, p3);
    }

    Point p[] = new Point[4];
    
    //points > 4
    //for every 4 points, add point 3.5 between 3 and 4
    //then let 3.5 be start of next 4 points, with 4 as 2nd point
    //(for smoothness)
    while (points.size() > 4) {
      
      if (points.size() == 5) {
        //interpolate a new point between front and end
        //remove point 4
        //interpolate between 3 and 5
        points.remove(3);
        Point i3 = (Point)points.elementAt(2);
        Point i5 = (Point)points.elementAt(3);
        int y = (int)((i3.y + i5.y)/2);
        int ix1 = i3.x;
        int ix2 = i5.x;
        if (Math.abs(ix1 - ix2) < IDGraph.YSPLIT) {
          int avg = (ix1 + ix2) / 2;
          ix1 = avg;
          ix2 = avg;
        }
        points.add(3,new Point(ix1, y - 1));
        points.add(4,new Point(ix2, y + 1));
      }
      
      //remove first 3 points
      Point p1 = (Point)points.remove(0);
      Point p2 = (Point)points.remove(0);
      Point p3 = (Point)points.remove(0);
      Point next = (Point)points.elementAt(0);
      Point p4 = new Point((int)((p3.x + next.x) / 2),(int)((p3.y + next.y) / 2));
      points.add(0,p4); // add new point to front 
      
      // add curve
      add(new BezierCurve(p1, p2, p3, p4));
    }
    
    if (points.size() < 4) {
      p[0] = (Point)points.elementAt(0);
      p[3] = (Point)points.elementAt(2);
      int y = (int)((p[0].getY() + p[3].getY()) / 2.0);
      p[1] = new Point((int)p[0].getX(),y-10);
      p[2] = new Point((int)p[3].getX(),y+10);
      add(new BezierCurve(p[0], p[1], p[2], p[3]));
    } else if (points.size() == 4) {
      for (int i = 0; i < 4; i++) {
        p[i] = (Point)points.elementAt(i);
      }
      add(new BezierCurve(p[0], p[1], p[2], p[3]));
    } else {
      System.out.println("error in bezier curve");
      System.exit(0);
    }
  }

  /*
  void show () {
    for (int i = 0; i < curves.size(); i++) {
      BezierCurve c = (BezierCurve)curves.elementAt(i);
      System.out.println("Curve: ");
      for (int j = 0; j < 4; j++) {
        System.out.println(" p[" + j + "]: " + c.p[j].x + ", " + c.p[j].y);
      }
    }
  }
  */
}

