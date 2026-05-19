# 📚 Data Structures Study Notes — CS214

> This is a personal study repo where I analyze code from sections, labs, and assignments.
> Each file includes code analysis, explanatory comments, and Time & Space Complexity breakdowns.

---

## 🗂️ Repository Structure

```
Data Structures/
│
├── linked list.cpp          — Singly & Doubly Linked Lists (template + iterator)
├── stack.cpp                — Stack via Array & Linked List + extra applications
├── Queue.cpp                — Queue via Circular Array & Linked List
├── heap.cpp                 — Max Heap + Priority Queue
├── BST.cpp                  — Binary Search Tree
├── AVL.cpp                  — AVL Self-Balancing Tree
├── sorting.cpp              — All sorting algorithms
├── searching algos.cpp      — Linear & Binary Search + encode/decode app
├── task queue & stack.cpp   — Combined task using Queue & Stack
│
├── Ass1 problems/           — Assignment 1
│   ├── Round Robin Scheduler.cpp
│   ├── BinarySearch at RotatedSortedArray.cpp
│   ├── Bitonic Array.cpp
│   ├── Complexity Analysis.cpp
│   ├── StackQ1.cpp
│   └── StackQ2.cpp
│
└── Ass2 problems/           — Assignment 2
    ├── Smart Library Book Management System.cpp
    └── Emergency Room Priority System.cpp
```

---

## 🔗 Linked List — `linked list.cpp`

### Core Idea
Built the Linked List using full OOP with **Inheritance** and **Templates**, meaning the class works with any data type, not just `int`.

### Classes Overview

| Class | Description |
|---|---|
| `Node<T>` | Basic node with `value` and `next` |
| `DNode<T>` | Doubly linked node with `value`, `next`, and `back` |
| `linkedList<T>` | Abstract base class — contains `copyList`, `destroy`, and iterator support |
| `llIterator<T>` | Custom iterator with `*`, `++`, `==`, `!=` operator overloading |
| `unordered<T>` | Concrete unordered singly linked list |
| `ordered<T>` | Concrete ordered list — auto-sorted on every insert |
| `doublyLinkedList<T>` | Doubly linked list with forward and backward traversal |

---

### ⏱️ Complexity Analysis

#### `unordered<T>`
| Operation | Time | Space | Why? |
|---|---|---|---|
| `insertFirst` | O(1) | O(1) | Only updates the `first` pointer |
| `insertLast` | O(1) | O(1) | We already hold a `last` pointer |
| `insertAtPos(pos)` | O(n) | O(1) | Must traverse to reach position |
| `deleteNode` | O(n) | O(1) | Searches for the node first |
| `search` | O(n) | O(1) | Worst case: checks every node |
| `reverse` | O(n) | O(1) | Walks all nodes and flips links |

#### `ordered<T>`
| Operation | Time | Space | Why? |
|---|---|---|---|
| `insert` | O(n) | O(1) | Searches for the correct sorted position |
| `search` | O(n) | O(1) | Stops early when a value >= target is found |
| `deleteNode` | O(n) | O(1) | Traverses to find the target node |

#### `doublyLinkedList<T>`
| Operation | Time | Space |
|---|---|---|
| `insertFirst` / `insertLast` | O(1) | O(1) |
| `insertAtPos` | O(n) | O(1) |
| `deleteNode` | O(n) | O(1) |
| `display` / `reverse` | O(n) | O(1) |

> **Note:** Doubly linked list makes deletion easier because the `back` pointer gives direct access to the previous node — no need for a `trailCurrent` like in singly linked lists.

---

### 📌 Key Takeaways from This Code

- Abstract functions in the base class (`insertFirst`, `insertLast`, `deleteNode`, `search`) force each subclass to provide its own implementation.
- `copyList` performs a **deep copy** — it creates brand new nodes, not just copies of pointers.
- The custom Iterator uses operator overloading so it can be used like STL iterators.

---

## 📦 Stack — `stack.cpp`

### What's Inside?

**1. `Stack` — Linked List-Based**
- Dynamic size, no overflow possible
- Operations: `push()`, `pop()`, `getTop()`, `display()`

**2. `IntStack` — Array-Based**
- Fixed size, faster memory access
- Operations: `push()`, `pop(int&)`, `peek()`, `count()`, `search()`, `clear()`, `displayBottom()`

### ⏱️ Complexity Analysis

| Operation | Time | Space | Why? |
|---|---|---|---|
| `push` | O(1) | O(1) | Just increments `top` |
| `pop` | O(1) | O(1) | Just decrements `top` |
| `peek` | O(1) | O(1) | Direct access to `stackArray[top]` |
| `search` | O(n) | O(1) | Worst case: checks every element |
| `count` | O(1) | O(1) | Returns `top + 1` directly |

> **Overall Space Complexity:** O(n) — allocates space for the maximum number of elements upfront.

---

### 🎯 Stack Applications in This File

#### 1. Bracket Matching — Balanced Parentheses Check
```
"({[]})"  → balanced ✅
"({[})"   → not balanced ❌
```
**Idea:** Push every opening bracket. When a closing bracket is encountered, if it doesn't match the top → not balanced.
- **Time:** O(n) — visits each character once
- **Space:** O(n) — worst case: all characters are opening brackets

#### 2. Big Integer Addition
**Idea:** Push each digit of both numbers onto separate stacks, then pop and add digit by digit with carry, right to left.
- **Time:** O(max(n, m)) — where n, m are the lengths of the two numbers
- **Space:** O(n + m) — for the three stacks used

#### 3. Postfix Expression Evaluator
```
"23+4*" = (2+3)*4 = 20
```
**Idea:** If it's a digit → push. If it's an operator → pop two, compute, push the result.
- **Time:** O(n)
- **Space:** O(n)

---

## 📬 Queue — `Queue.cpp`

### What's Inside?

**1. `IntQueue` — Circular Array Queue**
- Uses a circular array with `front`, `rear`, and `count`
- Solves the wasted space problem of a normal linear array queue

**2. `linkedQueue<T>` — Generic Linked Queue**
- Dynamic size, works with any type via templates

### ⏱️ Complexity Analysis

| Operation | Time | Space | Why? |
|---|---|---|---|
| `enqueue` | O(1) | O(1) | Computes `(rear+1) % size` |
| `dequeue` | O(1) | O(1) | Computes `(front+1) % size` |
| `peekFront` / `peekRear` | O(1) | O(1) | Direct index access |
| `displayMiddle` | O(1) | O(1) | `(front + count/2) % size` |
| `search` | O(n) | O(1) | Full traversal in worst case |
| `searchIndex` | O(n) | O(1) | Same as search but returns index |

> **Why use a Circular Array?**
> In a normal queue, repeated dequeues shift `front` forward and waste the space at the beginning of the array. The circular approach recycles that space using modulo arithmetic.

---

## 🔺 Heap — `heap.cpp`

### Core Idea
A Max Heap is a **complete binary tree stored in an array**.
- Every parent is always greater than its children
- The root is always the maximum element

**Index Relationships:**
```
parent(i)     = (i - 1) / 2
leftChild(i)  = 2i + 1
rightChild(i) = 2i + 2
```

### ⏱️ Complexity Analysis

| Operation | Time | Space | Why? |
|---|---|---|---|
| `insert` | O(log n) | O(1) | Heapify up until root |
| `deleteRoot` | O(log n) | O(1) | Heapify down until leaf |
| `getMax` | O(1) | O(1) | Root is always max |
| `increaseKey` | O(log n) | O(1) | Heapify up after update |
| `buildMaxHeap` | O(n) | O(1) | Calls heapify from n/2-1 down to 0 |
| `heapSort` | O(n log n) | O(1) | n deleteRoot operations |

> **Why is `buildMaxHeap` O(n) and not O(n log n)?**
> Most nodes are near the bottom and only need small heapify operations. The mathematical sum of all these small operations converges to O(n).

---

### Priority Queue — Two Implementations Compared

| | Linked List | Heap |
|---|---|---|
| `push` | O(n) | O(log n) |
| `pop` | O(1) | O(log n) |
| Best for | Small data or rare pushes | Large data, general use |

---

## 🌳 BST — `BST.cpp`

### Core Idea
- Elements smaller than root go left
- Elements larger than root go right
- Result: `inorder` traversal always returns sorted output

### ⏱️ Complexity Analysis

> **h = tree height**
> Balanced case: h = O(log n) ✅
> Worst case (sorted input): h = O(n) ❌

| Operation | Time | Space |
|---|---|---|
| `insert` | O(h) | O(h) stack |
| `deleteNode` | O(h) | O(h) stack |
| `search` (recursive) | O(h) | O(h) |
| `search` (iterative) | O(h) | O(1) |
| `minValue` / `maxValue` | O(h) | O(1) |
| `successor` | O(h) | O(1) |
| `height` | O(n) | O(h) |
| `countNodes` / `countLeaves` | O(n) | O(h) |
| `inorder` / `preorder` / `postorder` | O(n) | O(h) |
| `bfs` | O(n) | O(n) — due to queue |

---

### Delete Cases in BST
1. **No children** → Delete directly
2. **One child** → Replace node with its child
3. **Two children** → Replace with inorder successor (smallest node in the right subtree), then delete that successor

---

## ⚖️ AVL Tree — `AVL.cpp`

### How It Differs from BST
The AVL tree rebalances itself after every insert or delete to keep the height at O(log n) — unlike BST which can become skewed (like a linked list) when sorted data is inserted.

### Balance Factor
```
BF = height(left subtree) - height(right subtree)
```
- BF between -1 and 1 → balanced ✅
- BF > 1 or BF < -1 → rotation needed

### Rotation Types

| Case | Fix |
|---|---|
| LL (BF > 1, left-heavy) | Right Rotation |
| RR (BF < -1, right-heavy) | Left Rotation |
| LR (BF > 1, left child is right-heavy) | Left then Right |
| RL (BF < -1, right child is left-heavy) | Right then Left |

### ⏱️ Complexity Analysis

| Operation | Time | Space |
|---|---|---|
| `insert` | O(log n) | O(log n) |
| `deleteNode` | O(log n) | O(log n) |
| `search` | O(log n) | O(log n) |
| DFS traversals | O(n) | O(log n) |
| BFS | O(n) | O(n) |

> The guaranteed O(log n) is the core reason AVL outperforms BST in worst-case scenarios.

---

## 🔃 Sorting Algorithms — `sorting.cpp`

### Comparison Table

| Algorithm | Best | Average | Worst | Space | Stable? |
|---|---|---|---|---|---|
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | ✅ |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | ❌ |
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | ✅ |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | ✅ |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | ❌ |
| Counting Sort | O(n+k) | O(n+k) | O(n+k) | O(k) | ✅ |
| Radix Sort | O(d·(n+k)) | O(d·(n+k)) | O(d·(n+k)) | O(n+k) | ✅ |
| Bucket Sort | O(n+k) | O(n+k) | O(n²) | O(n) | ✅ |

> **k** = value range, **d** = number of digits in the largest element

---

### Important Notes

- **Insertion Sort** is best when data is nearly sorted (Best = O(n))
- **Quick Sort** degrades to O(n²) when the pivot is always the smallest or largest (e.g., already-sorted input)
- **Merge Sort** guarantees O(n log n) always, but needs extra O(n) space
- **Counting / Radix / Bucket** are not comparison-based, so they break the O(n log n) lower bound

All comparison-based sorts are implemented as **generic templates** using `template <class T>`.

---

## 🔍 Searching Algorithms — `searching algos.cpp`

### Linear Search
- Scans from start to end
- **Time:** O(n) | **Space:** O(1)
- Used in `decode()` — searches for a symbol in column 1 of the lookup table

### Binary Search
- Requires sorted data
- Halves the search range each step
- **Time:** O(log n) | **Space:** O(1)
- Used in `encode()` — searches for a character in column 0 of the lookup table

### Encode / Decode Application
A lookup table maps characters to symbols:
```
'a' → '#'   'c' → '@'   'e' → '%'   ...
```
- **Encode:** Given a character → Binary Search returns its symbol
- **Decode:** Given a symbol → Linear Search returns the original character

> **Why Binary Search for encode and Linear for decode?**
> Column 0 (characters) is sorted alphabetically, so Binary Search works.
> Column 1 (symbols) is not sorted, so Linear Search is the only option.

---

## 📝 Assignment 1 — `Ass1 problems/`

### Round Robin Scheduler

**Problem:** Simulate CPU scheduling using Round Robin with different arrival times.

**Classes:**

`Process` — stores:
- `id`, `arrival_time`, `burst_time`
- `remaining_time` — how much CPU time is left
- `completion_time`, `turnaround_time`, `waiting_time`

`RoundRobinScheduler` — manages:
- `quantum` — allowed time slice per process
- `ready_queue` — queue of process indices
- `in_queue[]` — tracks which processes have already been added

**Steps:**
1. Sort processes by `arrival_time` using MergeSort — O(n log n)
2. Add all processes that arrived at t=0 to the queue
3. Each iteration: run the current process for `min(quantum, remaining_time)`
4. Add any newly arrived processes during that run time
5. If process finished → calculate CT, TAT, WT
6. If process still has remaining time → push it back to the queue

**⏱️ Complexity:**
| Part | Time | Space |
|---|---|---|
| Sorting (MergeSort) | O(n log n) | O(n) |
| Scheduling loop | O(n × max_BT / quantum) | O(n) |
| `enqueueArrivals` (inside loop) | O(n) per call | O(1) |

**Metrics:**
```
TAT = CT - AT        (Turnaround Time)
WT  = TAT - BT       (Waiting Time)
AWT = sum(WT) / n    (Average Waiting Time)
```

---

## 📝 Assignment 2 — `Ass2 problems/`

### Smart Library Book Management System

**Problem:** Compare BST and AVL performance for managing a book catalog.

**`Book` struct:** `id`, `title`, `author`

**Goal:** Prove that AVL outperforms BST when data is inserted in sorted order.

**Results:**
| Case | BST Height | AVL Height |
|---|---|---|
| Random Insertion (20 books) | ~8 | ~4 |
| Sorted Insertion (20 books) | **19 (worst case!)** | **4 (still balanced!)** |

> With sorted insertion, BST degenerates into a linked list — every node goes to the right, making operations O(n).
> AVL rebalances after every insert and stays O(log n).

**Extra AVL Features Implemented:**
- `displayRange(low, high)` — print all books with IDs in a given range
- `findClosestID(target)` — find the book whose ID is closest to a target value

---

## 🧠 Key Concepts That Appear Throughout the Code

| Concept | Where It Appears |
|---|---|
| **Templates** | linked list, queue, stack |
| **Inheritance** | `unordered` and `ordered` inherit from `linkedList` |
| **Abstract Functions** | `search`, `insertFirst`, `insertLast`, `deleteNode` in `linkedList` |
| **Deep Copy** | `copyList()` in linked list |
| **Recursion** | BST, AVL, Merge Sort, Postfix evaluator |
| **Divide & Conquer** | Merge Sort, Quick Sort, Binary Search |
| **Memory Management** | `delete` and `delete[]` in every data structure |

---

> *Personal study notes — updated continuously with every new section and assignment.* 🎓
