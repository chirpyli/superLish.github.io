### AVL树
在二叉查找树的相关操作中，例如，插入、查找、删除、最大值、最小值等的时间复杂度为`O(h)`，为了避免算法的最坏情况，我们应当使二叉树平衡，以降低树的高度。DSW算法能够实现树的平衡，但有其局限性，只能做全局的平衡，当节点又有变化时，需要重新进行平衡（这个平衡的过程代价较大，等于是一整颗树都参与了平衡过程）。有没有更好的办法呢？AVL树就是其中一种。

AVL树是一种自平衡二叉查找树，其要求每个节点左右子树的高度差最大为1。下图所示是一颗AVL树，可以看到，AVL树不保证得到的树是完全平衡树。        
![image](https://upload.wikimedia.org/wikipedia/commons/thumb/f/fd/AVL_Tree_Example.gif/220px-AVL_Tree_Example.gif)

这里需要定义平衡因子，即右子树的高度减去左子树的高度。其实现思路，是在进行插入或删除节点时探测有没有发生不平衡，如果发生了不平衡，进行旋转操作使树平衡。关键有2点，一、探测到发生了不平衡，二、进行旋转使树重新平衡。

### AVL树的实现
#### 平衡因子
按照AVL树的定义，AVL树的平衡因子只能是0，+1，-1这三个值，如果在插入或删除一个节点时发现某个节点的平衡因子不是上面的三个值之一，那一定是发生了不平衡，这是就要通过旋转使树重新平衡。

#### 旋转
在DSW算法中，使用了旋转使树重新平衡，AVL树中也是使用旋转使树重新平衡，所不同的是AVL树中增加了平衡因子，能实时进行自平衡。定义旋转操作如下：

左旋转和右旋转
```
T1, T2 and T3 are subtrees of the tree 
rooted with y (on the left side) or x (on 
the right side)           
     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3
Keys in both of the above trees follow the 
following order 
 keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
So BST property is not violated anywhere.
```

#### 插入
在插入一个节点时，我们可以分析出只有下面4种情况会使树失去平衡，情况如下：

**a) Left Left Case**
```
T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
```

**b) Left Right Case**
```
     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2
```

**c) Right Right Case**
```
  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
```

**d) Right Left Case**
```
   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4
```
针对这4种情况，通过旋转操作可以使树重新平衡。

#### 删除
删除与插入相似，最后也是上面的4种情况会失去平衡，详细过程见代码[avltree.h](./avltree.h)。


### AVL树扩展
AVL树定义其左右子树高度差为1，可以对AVL树进行扩展，即，可以定义其高度差>1，这样的好处是减少了插入删除时的旋转操作，坏处就是树的高度有可能会增加，可以根据实际情况选择合适的高度差去构造AVL树。

---

>参考资料：      
[AVL Tree | Set 1 (Insertion)](https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)    
[AVL Tree | Set 2 (Deletion)](https://www.geeksforgeeks.org/avl-tree-set-2-deletion/)        
