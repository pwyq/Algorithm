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
Tree traversal: &#920;(n)  
min, max, predecessor, successor: O(1)

##### BST Minimum/Maximum
> Find the min/max key in a tree rooted at x
- Running time O(h) (proportional to the height of the tree)

```
TreeMin(x)
    while x.left() != NIL do
        x <- x.left()
    return x
```

##### BST Successor
Given `x`, find the node with the smallest key that greater than `x.key()`

Case I - Right Subtree of `x` is non-empty  
    Successor is the leftmost node in the right subtree (the minimum value in its right tree)  
    This can be done by returning TreeMin(x.right())

Case II - Right Subtree of `x` is empty
    Successor is the lowest ancestor of `x` whose left child is also an ancestor of `x`

**BST Successor Pseudocode**
```
TreeSuccessor(x)  
    if x.right() != NIL  
        then return TreeMin(x.right())  
    y <- x.parent()  
    while y != NIL and x = y.right()  
        x <- y  
        y <- y.parent()  
    return y
```

#### Pseudocode for BST Search

> Recursive version - divide-and-conquer algorithm
```
Search(T, k)
    if T = NIL then return NIL
    if k = T.key() then return T
    if k < T.key()
        then return Search(T.left(),k)
        else return Search(T.right(),k)
```

> Iterative version
```
Search(T, k)
    x <- T
    while x != NIL and k != x.key() do
        if k < x.key()
            then x <- x.left()
            else x <- x.right()
    return x
```

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

##### Application of the Tree Traversal

- Keys in the BST can be printed using "tree walks/traversal"
- Keys of each node printed between keys in the left and right subtreen ~ `inorder tree traversal`
- [Divide-and-conquer algorithm][1]
- Prints elements in increasing order
- Running time: &#920;(n) [since it must visit every node (best and worst case)]

```
InorderTreeWalk(x)
    if x != NIL then
        InorderTreeWalk(x.left())
        print x.key()
        InorderTreeWalk(x.right())
```

##### BST Sorting
> Use `TreeInsert` and `InorderTreeWalk` to sort a list of n elements
```
TreeSort(A)
    T <- NIL
    for i = 1 to n
        TreeInsert(T, BinTree(A[i]))
    InorderTreeWalk(T)
```

##### BST Deletion
**case 1**  
If `x` has no children - just remove `x`  
**case 2**  
If `x` has exactly one child, then to delete `x`, simply make `x.parent()` point to that child  
**case 3**  
If x has two children, then to delete it we have to  
    - find its successor (or predecessor) y  
    - remove y (note that y has at most one child - why?)

##### BST Delete Pseudocode
```
TreeDelete(T,z)
if z.left() = NIL or z.right() = NIL
    then y <- z
    else y<- TreeSuccessor(z)
if y.left() != NIL
    then x <- y.left()
    else x <- y.right()
if x != NIL
    then x.setParent(y.parent())
if y.parent() = NIL
    then T <- x
    else if y = y.parent().left()
        then y.parent().setLeft(x)
        else y.parent().setRight(x)
if y != z
    then z.setKey(y.key())  // copy y's data into z
return y
```

#### Side Notes

#### Readings

#### References
- ECE 250 course slides
- Wikipedia

[1]: https://en.wikipedia.org/wiki/Divide_and_conquer_algorithm
