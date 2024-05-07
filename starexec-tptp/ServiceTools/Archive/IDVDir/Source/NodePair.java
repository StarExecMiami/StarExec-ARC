import java.util.HashMap;

class NodePair {
  Node a, b;
  int hash;

  NodePair (Node a, Node b) {
    if (a.getId() < b.getId()) {
      this.a = a;
      this.b = b;
    } else {
      this.a = b;
      this.b = a;
    }
    hash = 37 * this.a.hashCode() + this.b.hashCode();
  }

  public int hashCode () {
    return hash;
  }

  public boolean equals (Object obj) {
    NodePair that = (NodePair)obj;
    return (this.a == that.a) && (this.b == that.b);
  }
}
