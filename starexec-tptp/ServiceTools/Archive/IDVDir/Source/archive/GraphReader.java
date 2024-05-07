// Christian Duncan
// GraphReader Class
//    for GD2004, Graph Drawing Contest

// package GD4;

import java.io.*;

/*********************
 * GraphReader Class
 *    Reads a Graph in various formats
 *    Currently only GD4 format works
 *********************/
public class GraphReader {
    public static Graph readGD4(Reader in) throws IOException {
	BufferedReader bin = new BufferedReader(in);
	return readGD4(bin);
    }

    /***************************
     * Read GD4 format input into Graph
     *   Very simple format
     *   Looks like:
     *       # Comments
     *       N         # Number of nodes edges
     *       X0 Y0     # Location of node0
     *       Xi Yi     # Location of nodei
     *       Xn-1 Yn-1 # Location of node(n-1)
     *       A0 B0     # Edge 0 is from node A0 to node B0 (indices)
     *       A1 B1     # Edge 1 is from node A1 to node B1 (indices)
     *       Aj Bj     # Edge j is from node Aj to node Bj
     *       ... until EOF ...
     ***************************/
    public static Graph readGD4(BufferedReader in) throws IOException {
	Graph g = null;
	int n, i, j;

	// Establish the tokenizer to parse the file
	StreamTokenizer tok = new StreamTokenizer(in);
	tok.commentChar('#');
	tok.parseNumbers();
	tok.eolIsSignificant(false);   // End-of-line is just another token

	/** Now parse every token **/

	// Get N and E
	if (tok.nextToken() != StreamTokenizer.TT_NUMBER) {
	    throw new IOException("Expected numeric value for N.\n" +
				  tok.toString());
	}
	n = (int) tok.nval;
	
	g = new DenseGraph(n);  // We will create a DenseGraph to store data...

	// Read in N nodes (as X, Y values)
	for (i = 0; i < n; i++) {
	    double x, y;
	    if (tok.nextToken() != StreamTokenizer.TT_NUMBER) {
		throw new IOException("Expected numeric value for X.\n" +
				      tok.toString());
	    }
	    x = tok.nval;
	    if (tok.nextToken() != StreamTokenizer.TT_NUMBER) {
		throw new IOException("Expected numeric value for Y.\n" +
				      tok.toString());
	    }
	    y = tok.nval;

	    g.addNode(x, y);
	}

	// Read in all edges (as node pairs: A B) until EOF (on a start node)
	while (tok.nextToken() != StreamTokenizer.TT_EOF) {
	    int a, b;
	    String strA, strB;

	    if (tok.ttype != StreamTokenizer.TT_NUMBER) {
		throw new IOException("Expected numeric value for edge start node.\n" +
				      tok.toString());
	    }
	    a = (int) tok.nval;
	    strA = tok.toString();

	    if (tok.nextToken() != StreamTokenizer.TT_NUMBER) {
		throw new IOException("Expected numeric value for edge end node.\n" +
				      tok.toString());
	    }
	    b = (int) tok.nval;
	    strB = tok.toString();

	    if (g.addEdge(a, b) == false) {
		// Not added successfully (not much help as a message!)
		throw new IOException("Edge given is not valid!\n" + 
				      "Start: " + strA + " --> " + 
				      "End: " + strB);
	    }
	}

	return g;
    }
}
