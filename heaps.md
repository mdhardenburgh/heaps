# Intro to Heaps
From Algorithms by CLRS

A heap is a nearly complete binary tree and it is generally made out of an 
array or array-like structure with 2 attributes, array length and heap size.
The heap size is ≤ the size of the array. The root of the heap tree is at `A[1]`
if the array is 1-indexed.

To calculate the parent, left and right child
```
parent(i)
    return(i/2)

left(i)
    return 2i

right(i)
    return(2i+1)
```

There are two kinds of heaps, min-heaps and max-heaps. Max-heap: parent ≥ child,
largest value is at the root. Min-heap: parent ≤ child, and smallest value is at
the root. Heapsort uses max-heaps, while priority queues can use either
min-heaps or max-heaps.The height of a heap tree is `log n` and heap operations 
take `O(K log(n))` K is the height of the tree.

# Maintaining the Heap Property
The function `maxHeapify()` is used to maintain the max-heap property after an
operation is done to the heap. If the element of the parent is greater than the
child, the parent floats down the greater element until the element is greater
than the childern. This is done recursively. `A` is an array and `i` is an index
into that array. `minHeapify()` is similar, but inverted. `maxHeapify()` runs in
`O(log n)`

Given an array `A` and index `i`
```
maxHeapify(A, i)
    l = left(i)
    r = right(i)
    if l ≤ A.heapSize() && (A[l] > A[i])
        largest = l
    else
        largest = i
    if r ≤ A.heapSize() && (A[r] > A[largest])
        largest = r
    if largest ≠ i
        exchange(A[i], A[largest])
        maxHeapify(A, largest)
```

# Building a Heap
We build a max-heap by using `maxHeapify()` to convert the array A[1...n] into a
max-heap. The element then in the subarray A[(n/2)+1...n] are all the leaves of
the heap-tree, so each is 1-element heap, that then becomes part of the larger
heap after successive calls of `maxHeapify()`.

Given an array `A` ...
```
buildMaxHeap(A)
    A.heapSize = A.length()
    for(i = (A.length()/2); i > 1; i--)
        maxHeapify(A, i)
```

# Heapsort
Overall idea is that when starting with an already built heap, the root of the
heap-tree is already the largest. Decrement the heap size by one, call 
`maxHeapify()` to maintain the heap property and then the new root will be the 
largest in this new heap. Do this repeatedly until the heap size is none and 
the array will be sorted. Runtime is `O(n log(n))` because you are calling 
maxHeapify which has a runtime of `O(log n)`, n number of times.

Given an array to be sorted A...
```
heapsort(A)
    buildMaxHeap(A)
    for(i = A.length(); i > 2; i--)
        exchange(A[1], A[i])
        A.heapSize = A.heapSize - 1
        maxHeapify(A, 1)
```

# Priority Queues
Popular application of heaps is priority queues. A priority queue maintains a 
set of elements, S, each with an associated key. A max priority queue has the
following 4 operations: 
* `insert(S, x)`: Given the set S and the element x, inserts the element x into 
the set S.
* `maxinmum(S)`: Given the set S and the element x, returns the element x of the 
set S that has the largest key.
* `extractMax(S)`: Given the set S and the element x, removes the element x from 
the set S with the largest key and returns it.
* `increaseKey(S, x, k)`: Given the set S and the element x, increase the value
of x's key to the new value `k` which is assumed to be ≥ x's current key value

Min priority queues have similar operations.

Max priority queues are used in job or thread scheduling applications. Can also
be used in bus arbitration. Scheduler selects the next highest priority element 
with `extractMax()` and new jobs are added with `insert()`. Minimum priority
queues are used in event driven simulators, like verilog. 

`heapMaximum(A)` returns the first element in the array, which is the maximum by
definition of a max-heap. `extractMax(A)` completely removes the element from
the array that has the largest key from the heap. `heapIncreaseKey(A, i, key)`
updates the key of the heap element i. We first increase the key of `A[i]` then 
traverse the tree path from this node to the root, "upwards", to find a correct
place for this new key-element pair. As the path is traversed the child and
parent are compared and their keys swapped if the child's is larger. 
`maxHeapInsert(A, key)` inserts a new element-key pair. We first expand the
max-heap by adding a new leaf to the tree with key value -infinity, then call
`heapIncreaseKey()` to set this new node into its correct spot.

Given an array A...
```
heapMaximum(A) // O(1)
    return A[1] //rememeber CLRS arrays are 1-indexed

heapExtractMax(A) // O(log n)
    if A.heapSize() < 1
        reportError("heap underflow")
    max = A[1]
    A[1] = A[A.heapSize()]
    A.heapSize() = A.heapSize() - 1
    maxHeapify(A, 1)
    return max

heapIncreaseKey(A, i, key) // O(log n)
    if(key < A[i])
        reportError("new key is smaller than current key")
    A[i] = key
    while(i > 1 && A[parent(i)] < A[i])
        exchange(A[i], A[parent(i)])
        i = parent(i)

maxHeapInsert(A, key)
    A.heapSize++
    A[A.heapSize()] = -inf
    heapIncreaseKey(A, A.heapSize(), key)
```