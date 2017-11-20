/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  y433wu @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

class Weighted_graph {
	private:
		static const double INF;
		double** graph;             // adjacency matrix
		int num_nodes;
		int num_edges;
		
		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {

    if (n < 0) {
        throw illegal_argument();
    }

    num_nodes = n;
    num_edges = 0;

    graph = new double *[n];        // row
    for (int i = 0; i < n; i++) {
        graph[i] = new double[n];   // column
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = INF;
        }
    }
    // cout << "test-3: " << INF << endl;
}

Weighted_graph::~Weighted_graph() {
    
    for (int i = 0; i < num_nodes; i++) {
        delete [] graph[i];
    }
    delete [] graph;
    num_nodes = 0;
}

int Weighted_graph::degree(int u) const {
    // Returns the degree of the vertex n. Throw an illegal_argument exception if the argument does
    // not corerespond to an existing vertex
    
    if (u < 0 || u > num_nodes-1) {
        throw illegal_argument();
    }

    int degrees = 0;
    for (int i = 0; i < num_nodes; i++) {
        if (graph[u][i] != INF) {
            degrees++;
        }
    }

	return degrees;

}

int Weighted_graph::edge_count() const {
    // Returns the number of edges in the graph
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
    // If an edge between nodes i and j exists, remove the edge
    // If i == j, returns true; if no edge esists, return false
    // If i and/or j are outside the range of [0, n-1], throw an illegal_argument exception
 
    if ((i < 0 || i > num_nodes-1) || (j < 0 || j > num_nodes-1)) {
        throw illegal_argument();
    }   

    if (i == j) {
        return true;
    }

    if (graph[i][j] == INF) {
        return false;
    }

    graph[i][j] = INF;
    graph[j][i] = INF;

    num_edges--;

	return true;
}

void Weighted_graph::clear_edges() {
    // Removes all edges from the graph
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            graph[i][j] = INF;
        }
    }
    num_edges = 0;
	return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    // If i == j, and they are in the graph, return false
    // If i != j,
    //      add a new edge Eij
    //      or, if the edge Eij exists, update the weight and return true

    // Validation input checking
    if ((i < 0 || i > num_nodes-1) || (j < 0 || j > num_nodes-1) || (d <= 0)) {
        throw illegal_argument();
    }

    if (i == j){
        return false;
    }
    
    // Only when the edges is not connected, we increment the num of edges
    if (graph[i][j] == INF) {
        num_edges++;
    }

    graph[i][j] = d;
    graph[j][i] = d;

    // cout << "\ni = " << i << ", j = " << j << ", i-j = " << d << ", edges = " << num_edges << endl;

	return true;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    /*
    Requirements: Uses Kruskal's algorithm to find the MST
    Returns the weight of the MST and the number of edges that were tested for adding into the MST
    Use Disjoint sets to ensure the MST is valid (ie, no loops in the tree)
    */
    
    // std::cout << "\n==== pair func got called ====" << std::endl;

    if (num_edges == 0) {
        return std::pair<double, int>(0.0, 0);
    }

    Disjoint_set MST(num_nodes);
    double totalWeights = 0.0;
    int testedEdges = 0;

    // Sort the edges in non-decreasing order
    double weights[num_edges][3];
    int counter = 0;
    for (int i = 0; i < num_nodes; i++) {
        for (int j = i+1; j < num_nodes; j++) {
            if (graph[i][j] != INF) {
                // cout << "\ncounter: " << counter << endl;
                // cout << "(i,j) = (" << i << ", " << j << "). weight: " << graph[i][j] << endl;
                weights[counter][0] = graph[i][j];  // store weight
                weights[counter][1] = i;            // store first node
                weights[counter][2] = j;            // store second node
                counter++;
            }

        }
    }

    // cout << "Building the MST!!!!!!!!!!!!!!!!!!!!! " << num_edges << endl;
    while (MST.num_sets() != 1 && testedEdges < num_edges) {
        // Find the smallest weight on adjacent nodes
        double tempWeight = INF;
        int tempIdx = 0;
        for(int i = 0; i < num_edges; i++) {
            if(weights[i][0] < tempWeight) {
                tempWeight = weights[i][0];
                tempIdx = i;
                // cout << "i = " << i << ", temp_weight = " << tempWeight << endl;
            }
        }

        int u = weights[tempIdx][1];
        int v = weights[tempIdx][2];

        // cout << "(u,v) = (" << u << ", " << v << "). weight: " << weights[tempIdx][0] << endl;
        if (MST.find_set(u) != MST.find_set(v)) {
            // cout << "______________INSIDE______________" << endl;
            MST.union_sets(u, v);
            totalWeights += weights[tempIdx][0];
        }
        weights[tempIdx][0] = INF;

        testedEdges++;
        // cout << "tested edges: " << testedEdges << endl;
    }

	return std::pair<double, int>(totalWeights, testedEdges);
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

#endif