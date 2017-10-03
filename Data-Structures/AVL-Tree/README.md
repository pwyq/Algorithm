### AVL Trees

An `AVL Tree` is another balanced binary search tree. Named after **A**delson-**V**elskii and **L**andis, they were the first dynamically balanced trees to be proposed.
They are not perfectly balanced (like red-black trees), but pairs of sub-trees differ in height by
at most 1.
(i.e., The height of the left and right subtrees can **differ at most 1**.)


Height of subtree: Max number to a leaf
Height of an empty subtree: -1
Height of one node: 0

#### Algorithms

##### Running Time  
search: O(logn)  
Addition, Deletion: O(logn)
Single rotation: O(1)

##### Insertion Algorithm
1. Insert the new keys as a new leaf just as in ordinary BST
2. Trace the path **from the new leaf towards the root**.
    - For each node `x` encountered, check if heights of left(x) and right(x) differ by at most 1
    - If yes, proceed to parent(x)
    - If not, restructure by doing either a **single rotation** or a **double rotation**.
3. Once we perform a rotation at a node `x`, we will not need to perform any rotation at any
   ancestor of `x`.

##### Rotations

```
Left-Rotate(T,x) {
    y = x.right         // set y
    x.right = y.left    // turn y's left subtree into x's right subtree
    if y.left != T.nil
        y.left.p = x    // if y's left subtree is not empty, let x be the parent of y's left subtree
    y.p = x.p           // link x's parent to y
    if x.p == T.nil
        T.root = y      // if x does not have a parent (i.e., x is the root), then reset T's root to
        y
    elseif x == x.p.left
        x.p.left = y
    else x.p.right = y
    y.left = x          // put x on y's left
    x.p = y
}
```

#### Side Notes

#### Readings

#### References
- CLRS (Introduction to Algorithm, 3rd)
- ECE 250 Course Slides
- [AVL Trees][https://www.cs.auckland.ac.nz/software/AlgAnim/AVL.html]
