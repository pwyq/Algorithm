/**
 * File              : BST.cpp
 * Author            : Yanqing Wu <meet.yanqing.wu@gmail.com>
 * Date              : 11.10.2017
 * Last Modified Date: 31.10.2017
 * Last Modified By  : Yanqing Wu <meet.yanqing.wu@gmail.com>
 */
// Main structure credit to: https://gist.github.com/mgechev/5911348
//                           https://www.cprogramming.com/tutorial/lesson18.html
// An helpful site for visualization:
//                           https://www.cs.usfca.edu/~galles/visualization/BST.html
// Binary Search Tree implementation in C++

# include <iostream>
# include <math.h>

struct Node {
    int key_value;
    Node *left;
    Node *right;
    int count;

    Node(): count(0) {}
};

class BST {
    private:
        Node *root;
        void destroy_tree(Node *leaf);
        void insert(int key, Node *leaf);
        Node *search(int key, Node *leaf);

        void printHelper(Node *leaf) {
            if (leaf == NULL) {
                return;
            }
            printHelper(leaf->left);
            std::cout << leaf->key_value << ' ';
            printHelper(leaf->right);
        }

        Node* findParentNode(Node *leaf, int key) {
            // std::cout << "input leaf value: " << leaf->key_value << ", key value: " << key << std::endl;
            if (leaf == NULL) {
                // std::cout << "leaf is null" << std::endl;
                return NULL;
            }

            if ((leaf->left == NULL) && (leaf->right == NULL)) {
                // std::cout << "leaf's child is null" << std::endl;
                // std::cout << "current leaf value: " << leaf->key_value << std::endl;
                return NULL;
            }

            if ((leaf->left != NULL)&&(leaf->left->key_value == key) 
                || (leaf->right != NULL)&&(leaf->right->key_value == key)) {
                // std::cout << "find the parent" << std::endl;
                return leaf;
            }

            if (leaf->key_value > key) {
                return findParentNode(leaf->left, key);
            }

            if (leaf->key_value < key) {
                return findParentNode(leaf->right, key);
            }
        }

        // find successor of a node
        Node* TreeSuccessor(Node *leaf) {
            if (leaf->right != NULL) {
                return TreeMin(leaf->right);
            }
            Node *y = new Node();
            y = findParentNode(leaf->key_value);
            while (y != NULL && leaf == y->right) {
                leaf = y;   // let leaf point to y
                y = findParentNode(y->key_value);
            }
            return y;
        }

        // find predecessor of a node
        Node* TreePredecessor(Node *leaf) {
            if (leaf->left != NULL) {
                return TreeMax(leaf->left);
            }
            Node *y = new Node();
            y = findParentNode(leaf->key_value);
            while (y != NULL && leaf == y->left) {
                leaf = y;   // let leaf point to y
                y = findParentNode(y->key_value);
            }
            return y;
        }

        Node* TreeMin(Node *leaf) {
            while (leaf->left != NULL) {
                leaf = leaf->left;
            }
            return leaf;
        }

        Node* TreeMax(Node *leaf) {
            while (leaf->right != NULL) {
                leaf = leaf->right;
            }
            return leaf;
        }

        void GreenEdgeHelper(Node *leaf)
        {
            static int greenEdgeCount = 0;
            
            if (leaf->left == NULL && leaf->right == NULL) {
                leaf->count = 1;
                return;
            }

            if (leaf->left != NULL) {
                leaf->count += 1;
                GreenEdgeHelper(leaf->left);
            }
            if(leaf->right != NULL) {
                leaf->count += 1;
                GreenEdgeHelper(leaf->right);
            }

            // End setting counter.

            leaf->count = 1;    // reset
            if (leaf->left != NULL)
                leaf->count += leaf->left->count;
            if (leaf->right != NULL)
                leaf->count += leaf->right->count;

            if (leaf->count > 0 && leaf->left != NULL) {
                if (leaf->count >= 2*leaf->left->count) {
                    std::cout << "current node count: " << leaf->count << ", left-subtree count: " << leaf->left->count << std::endl;
                    greenEdgeCount += 1;
                }
            }
            if (leaf->count > 0 && leaf->right != NULL) {
                if (leaf->count >= 2*leaf->right->count) {
                    std::cout << "current node count: " << leaf->count << ", right-subtree count: " << leaf->right->count << std::endl;
                    greenEdgeCount += 1;
                }
            }
            std::cout << "Number of Green Edges: " << greenEdgeCount << std::endl;
            std::cout << "Go back to last level." << std::endl;
        }
        // {
        //     int greenEdgeCount = 0;

        //     if (leaf->left == NULL && leaf->right == NULL) {
        //         leaf->count = 1;
        //         return greenEdgeCount;
        //     }

        //     int count = 0;

        //     if (leaf->left != NULL && leaf->left->count == 0) {
        //         greenEdgeCount += GreenEdgeHelper(leaf->left);
        //     }
        //     count += leaf->count;

        //     if (leaf->right != NULL && leaf->right->count == 0) {
        //         greenEdgeCount += GreenEdgeHelper(leaf->right);
        //     }
        //     count += leaf->count;
        //     leaf->count = count;
        //     if (leaf->left != NULL) {
        //         if (leaf->count >= 2*leaf->left->count)
        //             std::cout << "curr: " << leaf->key_value << ", count: " << leaf->count << std::endl;
        //             std::cout << "left: " << leaf->left->key_value << ", count: " << leaf->left->count << std::endl << std::endl;
        //             greenEdgeCount += 1;
        //     }
        //     if (leaf->right != NULL) {
        //         if (leaf->count >= 2*leaf->right->count)
        //             std::cout << "curr: " << leaf->key_value << ", count: " << leaf->count << std::endl;
        //             std::cout << "right: " << leaf->right->key_value << ", count: " << leaf->right->count << std::endl << std::endl;
        //             greenEdgeCount += 1;
        //     }
        //     return greenEdgeCount;
        // }


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
    public:

        // constructor
        BST();

        // destructor
        ~BST();

        Node *getRoot() {
            return this->root;
        }

        // The public `insert` and `search` are designed to allow the user of the class
        // to use the class without dealing with the underlying design.
        void insert(int key);
        Node *search(int key);
        void destroy_tree();

        void GreenEdge(Node *leaf) {
            std::cout << "GreenEdge got called." << std::endl;
            GreenEdgeHelper(leaf);
            std::cout << "GreenEdge ended." << std::endl;
        }

        void print() {
            printHelper(this->root);
            std::cout << std::endl;
        }

        Node *findParentNode(int key) {
            return findParentNode(root, key);
        }


        Node* TreeSuccessor(int key) {
            return TreeSuccessor(search(key));
        }

        Node* TreePredecessor(int key) {
            return TreePredecessor(search(key));
        }

        void rangePrint(Node *leaf, int a, int b) {

            if (leaf == NULL) {
                return ;
            }
            if (a < leaf->key_value) {
                rangePrint(leaf->left, a, b);
            }
            if ((a <= leaf->key_value) && (b >= leaf->key_value)) {
                std::cout << leaf->key_value << ' ';
            }
            if (b > leaf->key_value) {
                rangePrint(leaf->right, a, b);
            }            
        }
};  // semicolon!

BST::BST() {
    root = NULL;
}

BST::~BST() {
    destroy_tree();
}

void BST::destroy_tree(Node *leaf) {
    // Delete from bottom up
    if (leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void BST::insert(int key, Node *leaf) {
    // TODO: when duplicated element is inserted, throw an error.
    if (key < leaf->key_value) {
        if (leaf->left != NULL) {
            insert(key, leaf->left);
        }
        else {
            leaf->left = new Node;
            leaf->left->key_value = key;
            leaf->left->left = NULL;
            leaf->left->right = NULL;

        }
    }
    else {
        if (leaf->right != NULL) {
            insert(key, leaf->right);
        }
        else {
            leaf->right = new Node;
            leaf->right->key_value = key;
            leaf->right->left = NULL;
            leaf->right->right = NULL;
        }
    }

}

Node *BST::search(int key, Node *leaf) {
    if(leaf != NULL) {
        if (key == leaf->key_value) {
            return leaf;
        }
        if (key < leaf->key_value) {
            return search(key, leaf->left);
        }
        else {
            return search(key, leaf->right);
        }
    }
    else
        return NULL;
}


// public version 
void BST::insert(int key) {
    if(root != NULL) {
        insert(key, root);
    }
    else {
        root = new Node;
        root->key_value = key;
        root->left = NULL;
        root->right = NULL;
    }
}

Node *BST::search(int key) {
    return search(key, root);
}

void BST::destroy_tree() {
    destroy_tree(root);
}

int main() {

    BST *mybst = new BST();

    mybst->insert(1);
    mybst->print();
    // A terrible way to initialize a tree; it's totally unbalanced. :)
    mybst->insert(2);
    mybst->insert(3);
    mybst->insert(4);
    mybst->insert(5);
    mybst->insert(6);
    mybst->insert(7);
    mybst->insert(8);
    mybst->insert(9);
    mybst->insert(11);
    mybst->insert(21);
    mybst->insert(22);
    mybst->insert(25);
    mybst->insert(12);
    mybst->insert(112);

    mybst->print();

    Node *testTree = new Node();
    testTree = mybst->search(11);
    mybst->rangePrint(testTree, 1, 25);
    
    std::cout << "---------------------------------1" << std::endl;
    if (testTree->left == NULL) {
        std::cout << "left child is null" << std::endl;
    }
    else if (testTree->right == NULL) {
        std::cout << "right child is null." << std::endl;
    }
    else {
        std::cout << testTree->left->key_value << " " 
        << testTree->key_value << " " 
        << testTree->right->key_value << std::endl;
    
    }

    // delete testTree;    // TODO: add Node destructor. This delete seems not working
                            // It worked. you delete 11 here!

    std::cout << "---------------------------------2" << std::endl;
    Node *mytree = new Node();
    mytree = mybst->getRoot();

    mybst->rangePrint(mytree, 3, 25);

    if (mytree->left == NULL) {
        std::cout << "left child is null" << std::endl;
    }
    else if (mytree->right == NULL) {
        std::cout << "right child is null." << std::endl;
    }
    else {
        std::cout << mytree->left->key_value << " " 
        << mytree->key_value << " " 
        << mytree->right->key_value << std::endl;
    
    }
    std::cout << "---------------------------------3" << std::endl;
    std::cout << "Parent of 25 should be 22: " << mybst->findParentNode(25)->key_value << std::endl;
    std::cout << "Parent of 8 should be 7: " << mybst->findParentNode(8)->key_value << std::endl;

    std::cout << "---------------------------------4" << std::endl;
    std::cout << "successor of 25 should be 112: " << mybst->TreeSuccessor(25)->key_value << std::endl;
    std::cout << "successor of 12 should be 21: " << mybst->TreeSuccessor(12)->key_value << std::endl;

    std::cout << "---------------------------------5" << std::endl;
    std::cout << "Predecessor of 25 should be 22: " << mybst->TreePredecessor(25)->key_value << std::endl;
    std::cout << "Predecessor of 12 should be 11: " << mybst->TreePredecessor(12)->key_value << std::endl;


    std::cout << "---------------------------------6" << std::endl;
    mybst->GreenEdge(mytree);


    BST *mybst2 = new BST();
    mybst2->insert(100);
    mybst2->insert(50);
    mybst2->insert(150);
    mybst2->insert(25);
    mybst2->insert(160);
    mybst2->insert(75);
    mybst2->insert(90);
    mybst2->insert(10);
    mybst2->insert(140);

    Node *mytree2 = new Node();
    mytree2 = mybst2->getRoot();
    mybst2->GreenEdge(mytree2);


    mybst->destroy_tree();
    return 0;
}
