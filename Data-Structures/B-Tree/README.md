### B-Tree
In computer science, a B-tree is a self-balancing tree data structure that keeps data sorted and allows searches, sequential access, insertions, and deletions in logarithmic time. The B-tree is a generalization of a binary search tree in that a node can have more than two children (Comer 1979, p. 123).

#### Algorithms
Running time  
Search Time: O(log of base(# of key in one node) n)  

Every node must have [t-1, 2t-1] keys.  
Every internal node have [t, 2t] children.  

The root node has [0, 2t-1] keys.  
The root node has [0, 2t] children.  

#### Side Notes

#### Readings

#### References
- ECE 250 slides
- Wikipedia
