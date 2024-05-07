
import java.util.*;
import java.io.*;

public class GravityForce {
  double dx, dy;

  GravityForce (double _dx, double _dy) { dx = _dx; dy = _dy; }
  double getX() { return dx; }
  double getY() { return dy; }  
  double length() { return Math.sqrt(dx * dx + dy * dy); }
}
