1) Build the graph of interest and declare an int name NUM_NODES. NUM_NODES
   is initially 0. Each time a unique node is inserted, increment NUM_NODES.
   Building the graph runs in O(|V| + |E|) time, where V and E are the set
   of vertices and edges, respectively. Arbitrarily select a node in the graph
   to perform a BFS on the entire graph. Selecting the node is O(1) cost.
   Each time a node is marked as "processed" in the BFS algorithm,
   decrement NUM_NODES. The cost of a BFS is O(|V| + |E|). The decrement is
   O(1). If NUM_NODES is not 0 by the end of the BFS, graph is not connected.
   Checking if NUM_NODES is 0 is O(1). Total runtime is O(|V| + |E|).

2) Build the graph of interest and keep a record of the created nodes inside a
   data structure, such as a stack. This will be O(|V| + |E|) runtime. Next,
   in a while loop, iterate through the nodes (if using a stack, pop the nodes
   one by one). If the node's "processed" flag is currently true, do nothing
   and continue to the next node. If it is false, however, call the BFS function
   on that node, which is O(|V| + |E|) runtime for each BFS call. After calling
   BFS each time, increment a local variable NUM_CONNECTED (which is to be
   initialized as 0 before the while loop starts) by 1. After the while loop
   breaks, this local variable should have the number of connected components
   in the graph. The runtime of this algorithm is O(|V|^2 + |V|*|E|), since
   the worst case scenario you call the BFS function a |V| number of times
   (in the case none of the nodes are connected to each other).

3) Build the graph of interest and declare an int name NUM_NODES. NUM_NODES
   is initially 0. Each time a unique node is inserted, increment NUM_NODES.
   Building the graph runs in O(|V| + |E|) time, where V and E are the set
   of vertices and edges, respectively. Then, start a BFS call on Kevin Bacon.
   In the BFS, since the graph is unweighted in this problem, each time you
   visit a node, it will be distance of prev node + 1. However, you would not
   push if the node is 7 or greater away from Kevin Bacon, or if the node has
   been already processed. Every time you visit a node, you decrement NUM_NODES
   by 1. Once we are done with the BFS function, check if NUM_NODES is 0 again
   or not. If it is not, then the Six Degrees of Kevin Bacon is a myth.
   Otherwise, it seems to be true (lord help us). In the worst case,
   runtime is O(|V| + |E|).