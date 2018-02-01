
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


#include <stdio.h>

struct AdjListNode {
    int dest;
    double weight;
    AdjListNode *next;
};

using namespace std;

class Weighted_graph {
    private:
        static const double INF;
        int num_nodes;
        int num_edges;

        // Do not implement these functions!
        // By making these private and not implementing them, any attempt
        // to make copies or assignments will result in errors
        Weighted_graph( Weighted_graph const & );
        Weighted_graph &operator=( Weighted_graph );

        // your choice
        AdjListNode **adjList;

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
    // adjList points to an array of pointers of type AdjListNode*
    adjList = new AdjListNode*[n];
}

Weighted_graph::~Weighted_graph() {
    clear_edges();
    delete [] adjList;
    num_nodes = 0;
}

int Weighted_graph::degree(int u) const {
    if (u < 0 || u > num_nodes-1) {
        throw illegal_argument();
    }
    int degrees = 0;
    AdjListNode *trav = adjList[u];
    while (trav != NULL) {
        degrees++;
        trav = trav->next;
    }

    return degrees;
}

int Weighted_graph::edge_count() const { return num_edges; }

bool Weighted_graph::erase_edge(int i, int j) {
    if ((i < 0 || i > num_nodes-1) || (j < 0 || j > num_nodes-1)) {
        throw illegal_argument();
    }   
    if (i == j) { return true; }

    if (adjList[i] == NULL || adjList[j] == NULL) { return false; }

    AdjListNode *trav_I = adjList[i];
    AdjListNode *trav_J = adjList[j];
    bool isJFound = false;
    bool isIFound = false;
    while (trav_I != NULL) {
        if (j == trav_I->dest) { isJFound = true; break; }
        trav_I = trav_I->next;
    }
    while (trav_J != NULL) {
        if (i == trav_J->dest) { isIFound = true; break; }
        trav_J = trav_J->next;
    }
    if ((isJFound == false) || (isIFound == false)) { return false; }
                        /*  VALIDATION CHECKING END   */

                        /*  DELETE I-J   */
    trav_I = adjList[i];    // reset position to the head
    trav_J = adjList[j];
    // 1. delete at the head
    if ((j == trav_I->dest) && (trav_I->next == NULL)) {
        delete trav_I;
        adjList[i] = NULL;
        num_edges--;
    }
    // 2. delete at the middle
    else if (trav_I->next != NULL) {
        while (trav_I && trav_I->next != NULL) {
            if ((j == trav_I->next->dest) && (trav_I->next->next != NULL)) {
                AdjListNode *doomed = trav_I->next;
                trav_I->next = trav_I->next->next;
                delete doomed;
                num_edges--;
                break;
            }
            trav_I = trav_I->next;
        }
    }
    // 3. delete at the tail
    trav_I = adjList[i];
    while (trav_I && trav_I->next != NULL) {
        if ((j == trav_I->next->dest) && (trav_I->next->next == NULL)) {
            AdjListNode *doomed = trav_I->next;
            trav_I->next = NULL;
            delete doomed;
            num_edges--;
            break;
        }
        trav_I = trav_I->next;
    }
                        /*  DELETE J-I   */
    if ((i == trav_J->dest) && (trav_J->next == NULL)) {
        delete trav_J;
        adjList[j] = NULL;
    }
    else if (trav_J->next != NULL) {
        while (trav_J && trav_J->next != NULL) {
            if ((i == trav_J->next->dest) && (trav_J->next->next != NULL)) {
                AdjListNode *doomed = trav_J->next;
                trav_J->next = trav_J->next->next;
                delete doomed;
                break;
            }
            trav_J = trav_J->next;
        }
    }

    trav_J = adjList[j];
    while (trav_J && trav_J->next != NULL) {
        if ((i == trav_J->next->dest) && (trav_J->next->next == NULL)) {
            AdjListNode *doomed = trav_J->next;
            trav_J->next = NULL;
            break;
        }
        trav_J = trav_J->next;
    }

    cout << "\nTest-printing" << endl;
    for (int i = 0; i < num_nodes; i++) {
        cout << i << ": ";
        AdjListNode *temp = adjList[i];
        while (temp) {
            cout << temp->dest << "(w: " << temp->weight << ")->";
            temp = temp->next;
        }
        cout << "GROUND." << endl;
    }
    return true;
}

void Weighted_graph::clear_edges() {

    for (int i = 0; i < num_nodes; i++) {
        if (adjList[i] != NULL) {
            AdjListNode *curr = adjList[i];
            while (curr != NULL) {
                AdjListNode *prev = curr;
                curr = curr->next;
                delete prev;
            }
            adjList[i] = NULL;
        }
    }

    cout << "\nTest-printing" << endl;
    for (int i = 0; i < num_nodes; i++) {
        cout << i << ": ";
        AdjListNode *temp = adjList[i];
        while (temp) {
            cout << temp->dest << "(w: " << temp->weight << ")->";
            temp = temp->next;
        }
        cout << "GROUND." << endl;
    }
    num_edges = 0;
    return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    if ((i < 0 || i > num_nodes-1) || (j < 0 || j > num_nodes-1) || (d <= 0)) {
        throw illegal_argument();
    }
    if (i == j) { return false; }
    cout << "\n\t~~~~~~~~~Insert Edge: " << i << "-" << j << ", " << d << endl;

    if (adjList[i] == NULL) {
        AdjListNode *new_I = new AdjListNode;
        new_I->dest = j;
        new_I->weight = d;
        new_I->next = NULL;
        adjList[i] = new_I;
        num_edges++;
    } else {
        AdjListNode *trav_I = adjList[i];
        AdjListNode *last_I = adjList[i];
        // check if the node is already exist, if so, update the weight; otherwise,
        // add to the end
        bool isFound = false;
        while (trav_I != NULL) {
            // Find the repeated edge, now update its weight
            // cout << "j: " << j << ", next node is: " << trav_I->dest << endl;
            if (j == trav_I->dest) {
                trav_I->weight = d;
                isFound = true;
                break;
            }
            trav_I = trav_I->next;
            if (last_I->next != NULL) { last_I = last_I->next; }
        }
        // Notice that trav_I is null here! So can't use it!
        if (isFound == false) {
            AdjListNode *newNode = new AdjListNode;
            newNode->dest = j;
            newNode->weight = d;
            newNode->next = NULL;
            last_I->next = newNode;
            num_edges++;
        }
    }

    if (adjList[j] == NULL) {
        AdjListNode *new_J = new AdjListNode;
        new_J->dest = i;
        new_J->weight = d;
        new_J->next = NULL;
        adjList[j] = new_J;
    } else {
        AdjListNode *trav_J = adjList[j];
        AdjListNode *last_J = adjList[j];
        bool isFound = false;
        while (trav_J != NULL) {
            if (i == trav_J->dest) {
                trav_J->weight = d;
                isFound = true;
                break;
            }
            trav_J = trav_J->next;
            if (last_J->next != NULL) { last_J = last_J->next; }
        }
        if (isFound == false) {
            AdjListNode *newNode = new AdjListNode;
            newNode->dest = i;
            newNode->weight = d;
            newNode->next = NULL;
            last_J->next = newNode;
        }
    }

    cout << "\nTest-printing" << endl;
    for (int i = 0; i < num_nodes; i++) {
        cout << i << ": ";
        AdjListNode *temp = adjList[i];
        while (temp) {
            cout << temp->dest << "(w: " << temp->weight << ")->";
            temp = temp->next;
        }
        cout << "GROUND." << endl;
    }
    return true;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    // if (num_edges == 0) { return std::pair<double, int>(0.0, 0); }

    Disjoint_set MST(num_nodes);

    // 1. store unique edges edges
    double weights[num_edges][3];
    int counter = 0;
    for (int i = 0; i < num_nodes; i++) {     
        if (adjList[i] != NULL) {
            AdjListNode *temp = adjList[i];
            while (temp != NULL) {
                bool isSameEdge = false;
                for (int j = 0; j < counter; j++) {
                    if (temp->weight == weights[j][2]) {
                        if ((temp->dest == weights[j][0]) && (i == weights[j][1])) {
                            isSameEdge = true;
                        }
                    }
                }
                if (isSameEdge == false) {                
                    weights[counter][0] = i;            // first node
                    weights[counter][1] = temp->dest;   // second node
                    weights[counter][2] = temp->weight;
                    counter++;
                }
                temp = temp->next;
            }
        }
    }

    cout << "hallelujah" << endl;
    for (int i = 0; i < counter; i++) {
        for (int j = 0; j < 3; j++) {
            cout << weights[i][j] << " ";
        }
        cout << endl;
    }

    double totalWeights = 0.0;
    int testedEdges = 0;
    while (MST.num_sets() != 1 && testedEdges < num_edges) {
        // Find the smallest weight on adjacent nodes
        double tempWeight = INF;
        int tempIdx = 0;
        for(int i = 0; i < num_edges; i++) {
            if(weights[i][2] < tempWeight) {
                tempWeight = weights[i][2];
                tempIdx = i;
                // cout << "i = " << i << ", temp_weight = " << tempWeight << endl;
            }
        }

        int u = weights[tempIdx][0];
        int v = weights[tempIdx][1];

        cout << "(u,v) = (" << u << ", " << v << "). weight: " << weights[tempIdx][2] << endl;
        if (MST.find_set(u) != MST.find_set(v)) {
            // cout << "______________INSIDE______________" << endl;
            MST.union_sets(u, v);
            totalWeights += weights[tempIdx][2];
        }
        weights[tempIdx][2] = INF;

        testedEdges++;
        // cout << "tested edges: " << testedEdges << endl;
    }



    return std::pair<double, int>( totalWeights, testedEdges );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
    return out;
}
#endif
