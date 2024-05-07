//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   OSTree - Ordered Statistics Tree
*/
//*****************************************************************************
import java.util.*;
import java.io.*;
import javax.swing.*;
import java.awt.*;
//*****************************************************************************
public class OSTree<E> {
  private Comparator<E> compare;

  private enum RBColor { RED, BLACK };
  public class Node {
    E data;
    RBColor color;
    int size;

    Node left;
    Node right;
    Node parent;

    Node (E data, RBColor color) {
      this.data = data;
      this.color = color;
      left = null;
      right = null;
      parent = null;
    }      
    void show () {
      System.out.println(data);
    }
    void updateSize () {
      size = 1;
      if (left != null)
        size += left.size;
      if (right != null)
        size += right.size;
    }
  }

  private Node root;

  public OSTree (Comparator<E> compare) {
    this.compare = compare;
    root = null;
  }


  private void leftRotate (Node x) {
    Node y;
    
    y = x.right;
    x.right = y.left;
    if (y.left != null) {
      y.left.parent = x;
    }
    y.parent = x.parent;
    if (x.parent == null) {
      root = y;
    } else {
      if (x == x.parent.left) {
        x.parent.left = y;
      } else {
        x.parent.right = y;
      }
    }
    y.left = x;
    x.parent = y;
    y.size = x.size;
    x.updateSize();
  }
  private void rightRotate (Node y) {
    Node x;

    x = y.left;
    y.left = x.right;
    if (x.right != null) {
      x.right.parent = y;
    }
    x.parent = y.parent;
    if (y.parent == null) {
      root = x;
    } else {
      if (y == y.parent.left) {
      y.parent.left = x;
      } else {
        y.parent.right = x;
      }
    }
    x.right = y;
    y.parent = x;
    x.size = y.size;
    y.updateSize();
  }
  private void insertHelp (Node z) {
    Node x;
    Node y;
    
    z.left = z.right = null;
    
    y = null;
    x = root;
    while (x != null) {
      x.size = x.size + 1;
      y = x;
      if (compare.compare(z.data, x.data) == -1) {
        x = x.left;
      } else {
        x = x.right;
      }
    }
    z.parent = y;
    if (y == null) {
      root = z;
    } else {
      if (compare.compare(z.data, y.data) == -1) {
        y.left = z;     
      } else {
        y.right = z;
      }
    }
    z.size = 1;
  }
  private int sizeOf (Node node) {
    if (node == null)
      return 0;
    return node.size;
  }
  private RBColor colorOf (Node node) {
    if (node == null) 
      return RBColor.BLACK;
    return node.color;
  }
  private void setColor (Node node, RBColor color) {
    if (node == null)
      return;
    node.color = color;
  }
  
  //private void removeHelp (Node x) {}    
  //public void remove (E data) {}
  //private Node getPredecessorOf (Node x) {}
  //private Node getSuccessorOf (Node x) {}
  //private Node find (E data, Node x) {}
  public Node insert (E data) {
    Node y;
    Node x;
    Node newNode = new Node(data, RBColor.RED);
    x = newNode;
    insertHelp(x);
    
    while (x != root && colorOf(x.parent) == RBColor.RED) {
      if (x.parent == x.parent.parent.left) {
        y = x.parent.parent.right;
        if (colorOf(y) == RBColor.RED) {
          
          /*
           * case 1: x's uncle is red: recolor
           *          (Cb)                     x(Cr)     
           *         /   \     	              /   \     
           *      (Br)     (Dr)	           (Bb)     (Db)
           *      / \     / \     ===>      / \     / \  
           *   x(Ar) 'c  'd  'e	         (Ar) 'c  'd  'e
           *    / \            	         / \            
           *  'a  'b           	       'a  'b           
           */          
          setColor(x.parent, RBColor.BLACK);
          setColor(y, RBColor.BLACK);
          setColor(x.parent.parent, RBColor.RED);
          x = x.parent.parent;
        } else {
          if (x == x.parent.right) {
            // case 2: x is a right child: rotate to get to case 3
            x = x.parent;
            leftRotate(x);
            // now x is a left child
          }
          // case 3: x is a left child: recolor and rotate grandparent
          setColor(x.parent, RBColor.BLACK);
          setColor(x.parent.parent, RBColor.RED);
          rightRotate(x.parent.parent);
        }
      } else {
      // Right case: x's parent is a right child	
      // symmetric with left case
        y = x.parent.parent.left;
        if (colorOf(y) == RBColor.RED) {
          // case 1: x's uncle is red: recolor
          setColor(x.parent, RBColor.BLACK);
          setColor(y,RBColor.BLACK);
          setColor(x.parent.parent, RBColor.RED);
          x = x.parent.parent;
        } else {
          if (x == x.parent.left) {
            // case 2: x is a left child: rotate to get to case 3
            x = x.parent;
            rightRotate(x);
            // now x is a right child
          }
          // case 3: x is a right child: recolor and rotate grandparent
          setColor(x.parent, RBColor.BLACK);
          setColor(x.parent.parent, RBColor.RED);
          leftRotate(x.parent.parent);
        }
      }
    }
    setColor(root, RBColor.BLACK);
    return newNode;    
  }
  private void showTree (Node node) {
    if (node != null) {
      showTree(node.left);
      node.show();
      showTree(node.right);
    }
  }
  public void showTree () {
    showTree(root);
  }

  public Node select (int i) {
    return select(root, i);
  }
  public Node select (Node x, int i) {
    int r = sizeOf(x.left) + 1;
    if (i == r) {
      return x;
    } else if (i < r) {
      return select(x.left, i);
    } else {
      return select(x.right, i - r);
    }
  }
  int rank (Node x) {
    int r = sizeOf(x.left) + 1;
    Node y = x;
    while (y != root) {
      if (y == y.parent.right)
        r += sizeOf(y.parent.left) + 1;
      y = y.parent;
    }
    return r;
  }
  
}
