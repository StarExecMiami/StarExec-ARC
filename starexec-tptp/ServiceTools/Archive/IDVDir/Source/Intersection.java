//
//  Intersection.java
//  GraphMan
//
//     Represents the intersection of two edges
//     For accuracy, edges that share start nodes
//     do NOT intersect
//     WARNING:
//         The method here is not ROBUST... so very close
//         intersections may be missed and near-hits may
//         be added.
//  Created by Christian Duncan on Sun Sep 12 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//

public class Intersection {
   private Edge a;    // The two edges
   private Edge b;    //   in questions
   private double x;  // X and Y location of intersection
   private double y;
   private boolean intersects; // Do they even intersect?

   /**
      * Intersection (Constructor)
    *   Store intersection of given two edges
    *   Also invokes computeIntersection method
    **/
   public Intersection(Edge _a, Edge _b) {
      a = _a;
      b = _b;
      computeIntersection();
   }

   /**
      * doesIntersect()
    *   Do the two edges intersect?
    **/
   public boolean doesIntersect() { return intersects; }

   /**
      * Return intersection of two LINES
    *   This may or may not be on the edges
    **/
   public double getX() { return x; }
   public double getY() { return y; }

   public void computeIntersection() {
      // Compute the vectors for each edge
      Node aStart = a.getStartNode();
      Node aEnd = a.getEndNode();
      Node bStart = b.getStartNode();
      Node bEnd = b.getEndNode();

      // Are any of the nodes the same?
      if (aStart == bStart || aStart == bEnd) {
         x = aStart.getX();
         y = bStart.getY();
         intersects = false;
         return;
      } else if (aEnd == bStart || aEnd == bEnd) {
         x = aEnd.getX();
         y = bEnd.getY();
         intersects = false;
         return;
      }
      
      // Compute vectors A, B, C(aStart-bStart)
      double adx = aEnd.getX() - aStart.getX();
      double ady = aEnd.getY() - aStart.getY();
      if (adx == 0 && ady == 0) {
         // 0 length edge!  What to do?  Intersection here
         intersects = true;
         x = aStart.getX();
         y = aStart.getY();
      }
      
      double bdx = bEnd.getX() - bStart.getX();
      double bdy = bEnd.getY() - bStart.getY();
      if (bdx == 0 && bdy == 0) {
         // 0 length edge!  What to do?  Intersection here
         intersects = true;
         x = bStart.getX();
         y = bStart.getY();
      }

      double cdx = aStart.getX() - bStart.getX();
      double cdy = aStart.getY() - bStart.getY();

      // Are they parallel
      double denom = bdx * ady - bdy * adx;
      double num = bdy * cdx - bdx * cdy;
      
      if (denom == 0) {
         // Parallel, co-incident lines?
         if (num != 0) {
            // Not co-incident
            intersects = false;
            x = aStart.getX(); y = aStart.getY(); // debugging!
         } else {
            // Co-incident lines, and the segments?
            double tbs, tbe;
            if (Math.abs(bdx) > Math.abs(bdy)) {
               // More horizontal, use that direction
               tbs = cdx / bdx;
               tbe = (aEnd.getX() - bStart.getX())/bdx;
            } else {
               // More vertical, use that direction
               tbs = cdy / bdy;
               tbe = (aEnd.getY() - bEnd.getY())/bdy;
            }
            if (tbs < 0) {
               if (tbe >= 0) {
                  // Intersects at least at Bstart
                  intersects = true;
                  x = bStart.getX(); y = bStart.getY();
               } else {
                  // Both endpoints of A lie on same side of B
                  intersects = false;
                  x = bStart.getX(); y = bStart.getY(); // more for debugging
               }
            } else if (tbs > 1) {
               if (tbe <= 1) {
                  // Intersects at least at Bend
                  intersects = true;
                  x = bEnd.getX(); y = bEnd.getY();
               } else {
                  // Both endpoints of A lie on same side of B
                  intersects = false;
                  x = bEnd.getY(); y = bEnd.getY(); // more for debugging
               }
            } else {
               // Intersects at least at aStart
               intersects = true;
               x = aStart.getX(); y = aStart.getY();
            }
         }
      } else {
         // Compute parametrically where intersection is on A and B
         double ta = num / denom;
	 double tb;
         if (Math.abs(bdx) > Math.abs(bdy)) {
            // More horizontal, use that direction
            tb = (cdx + adx * ta) / bdx;
         } else {
            tb = (cdy + ady * ta) / bdy;
         }

         // Compute intersection point (use ta)
         x = aStart.getX() + adx * ta;
         y = aStart.getY() + ady * ta;

         // Intersection of edges occurs iff ta and tb in [0,1]
         // NOTE: We count endpoint intersections
         //       UNLESS two nodes are shared in common
         intersects = (ta >= 0 && ta <= 1 && tb >= 0 && tb <= 1);
      }
   }
}
