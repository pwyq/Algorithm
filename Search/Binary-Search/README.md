### Binary Search

#### Algorithms
A binary search tree is a binary tree T such that:  
- each internal node stores an item(`k`) of a dictionary
- keys stored at nodes in the **left** subtree are **less than or equal** to k
- keys stored at nodes in the **right** subtree are **greater than (or equal)** to k

> To find an element with key `k` in a tree T  
- compare `k` with `T.key()`
- if `k` < `T.key()`, search for `k` in `K.left()`
- otherwise, search for `k` in `T.right()`

##### Running Time
search: O(lgn)
insert, delete: O(n)
Tree traversal: \theta(n)
min, max, predecessor, successor: O(1)

##### BST Minimum/Maximum
> Find the min/max key in a tree rooted at x
- Running time O(h) (proportional to the height of the tree)

TreeMin(x)
    while x.left() != NIL do
        x <- x.left()
    return x

##### BST Successor
Given `x`, find the node with the smallest key that greater than `x.key()`

Case I - Right Subtree of `x` is non-empty  
    Successor is the leftmost node in the right subtree  
    This can be done by returning TreeMin(x.right())

Case II - Right Subtree of `x` is empty
    Successor is the lowest ancestor of `x` whose left child is also an ancestor of `x`

**BST Successor Pseudocode**  
TreeSuccessor(x)  
    if x.right() != NIL  
        then return TreeMin(x.right())  
    y <- x.parent()  
    while y != NIL and x = y.right()  
        x <- y  
        y <- y.parent()  
    return y

#### Pseudocode for BST Search

> Recursive version - divide-and-conquer algorithm
Search(T, k)
    if T = NIL then return NIL
    if k = T.key() then return T
    if k < T.key()
        then return Search(T.left(),k)
        else return Search(T.right(),k)

> Iterative version
Search(T, k)
    x <- T
    while x != NIL and k != x.key() do
        if k < x.key()
            then x <- x.left()
            else x <- x.right()
    return x

##### BST Insertion Pseudocode
> Basic Idea  
- take an element (tree) `z` (whose left and right children are NIL) and insert it into `T`
- find place in `T` where `z` belongs (as if searching for `z.key()`)
- add `z` there

```
TreeInsert(T, z)
y <- NIL
x <- T
while x != NIL
    y <- x
    if z.key() < x.key()
        then x <- x.left()
        else x <- x.right()
z.setParent(y)
if y != NIL
    then if z.key() < y.key()
        then y.setLeft(z)
        else y.setRight(z)
    else T <- z
```

#### Side Notes

#### Readings

#### References
- ECE 250 course slides
