public class BezierChain {

  public Vector curves;

  void add (BezierCurve c) {
    curves.add(c);
  }
  int size () { return curves.size(); }
  BezierCurve get (int i) { return (BezierCurve)curves.elementAt(i); }
  void clear () { curves.clear(); }
  
  public BezierChain (Vector points) {
    
    //take begin, end, and two middle points
    if (points.size() <= 2) {
      System.out.print("not enough points, only: " + points.size());
      System.exit(0);
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
        if (Math.abs(ix1 - ix2) < 200) {
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


}

