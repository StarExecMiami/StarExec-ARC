// Christian Duncan
// GraphGenerator Class
//    for GD2004, Graph Drawing Contest

// package GD4;

import java.util.*;

/*********************
 * GraphGenerator Class
 *    Provides several methods to generate random graphs
 *          Currently, we want one that is dense and
 *          connected and high potential for crossings...
 *********************/
public abstract class GraphGenerator {
    static {
	ran = new Random();  // So there is at least a default one!
    }

    private static int minValue = 0;
    private static int maxValue = 1000;
    private static Random ran;

    // Generate a random tree
    public static Graph generateRandomTree(int nodes) {
	ran = new Random();  // Maybe specify seed?
	DenseGraph g = new DenseGraph(nodes);  // Yes, a sparse graph would be better!
	

	// First, we want to create all of the nodes
	createNodes(g, nodes);
	
	// Now, we create a random tree on this graph
	randTree(g, nodes);

	return g;
    }

    /**
     * Generate a union of multiple random trees
     *     nodes:     number of nodes to create
     *     numTrees:  number of random trees to create on these nodes
     *     returns:   A (Dense) Graph formed by union of these trees
     **/
    public static Graph generateMultipleRandomTrees(int nodes, int numTrees) {
	ran = new Random();  // Maybe specify see?
	DenseGraph g = new DenseGraph(nodes);

	// First, we create the nodes
	createNodes(g, nodes);

	// And then the numTree different trees
	for (; numTrees > 0; numTrees--)
	    randTree(g, nodes);
	    
	return g;
    }

    // Create nodes at random locations
    private static void createNodes(Graph g, int nodes) {
	int i;
	for (i = 0; i < nodes; i++) {
	    g.addNode(randLocation(minValue, maxValue), 
		      randLocation(minValue, maxValue));
	}
    }

    /**************************************
     *  Create a random tree from the nodes
     *  Algorithm:
     *       First we create a random ordering of the nodes
     *       Next we add each node (in this order) one at a time
     *         connecting the node (randomly) to one of the previously added nodes
     *       Not 100% - but should generate all trees with equal prob.
     *          Will mean some nodes have greater chance of larger degrees
     *          But each node has equal chance of being one of these...
     **************************************/
    private static void randTree(Graph g, int nodes) {
	int[] order = randArray(nodes);  // The ordering of the nodes
	int i;
	for (i = 1; i < nodes; i++) {
	    // For each node, pick its incident edge
	    int adjNode = ran.nextInt(i);  // 0 to i-1
	    g.addEdge(order[i], order[adjNode]);  // Note: use order to get node index
	}
    }

    // Create a random permutation of numbers 0 to n-1
    public static int[] randArray(int n) {
	int[] ans = new int[n];
	int i;
	for (i = 0; i < n; i++) ans[i] = i;  // Initialize 0, 1, 2, ...
	for (i = n-1; i > 0; i--) {
	    int j = ran.nextInt(i+1); // Pick a rand index (0 to i)
	    int t = ans[j];           // And swap...
	    ans[j] = ans[i];
	    ans[i] = t;
	}
	return ans;
    }

    // Generate a random double value
    //        Within the range: [min, max)
    private static double randLocation(double min, double max) {
	return (ran.nextDouble() + min) * (max - min);
    }

    // Generate a random int value
    //        Within the range: [min, max)
    private static int randLocation(int min, int max) {
	return (ran.nextInt(max-min) + min);
    }
}
