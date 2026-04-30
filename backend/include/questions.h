#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <vector>
#include <string>

struct Question {
    string text;
    vector<string> options;
    int correctIndex;
};

inline std::vector<Question> get50Questions() {
    return {
        {"What is the time complexity of Binary Search?", {"O(N)", "O(log N)", "O(N^2)", "O(1)"}, 1},
        {"Which data structure follows LIFO?", {"Queue", "Tree", "Stack", "Graph"}, 2},
        {"Which data structure follows FIFO?", {"Queue", "Stack", "Tree", "Graph"}, 0},
        {"What is the worst-case time complexity of Quick Sort?", {"O(N log N)", "O(N)", "O(N^2)", "O(1)"}, 2},
        {"What is the best-case time complexity of Merge Sort?", {"O(N log N)", "O(N)", "O(N^2)", "O(1)"}, 0},
        {"Which algorithm is used for finding the shortest path in a weighted graph?", {"Dijkstra's", "Kruskal's", "Prim's", "DFS"}, 0},
        {"Which algorithm finds the Minimum Spanning Tree?", {"Dijkstra's", "Kruskal's", "Bellman-Ford", "Floyd-Warshall"}, 1},
        {"What is the maximum number of children in a Binary Tree node?", {"1", "2", "3", "Unlimited"}, 1},
        {"What traversal visits Left, Root, Right?", {"Pre-order", "In-order", "Post-order", "Level-order"}, 1},
        {"What traversal visits Root, Left, Right?", {"Pre-order", "In-order", "Post-order", "Level-order"}, 0},
        {"What traversal visits Left, Right, Root?", {"Pre-order", "In-order", "Post-order", "Level-order"}, 2},
        {"What is the time complexity of accessing an element in an array?", {"O(N)", "O(log N)", "O(1)", "O(N^2)"}, 2},
        {"Which sorting algorithm is most efficient for nearly sorted data?", {"Quick Sort", "Merge Sort", "Insertion Sort", "Selection Sort"}, 2},
        {"What data structure is used to implement recursion?", {"Queue", "Stack", "Tree", "Heap"}, 1},
        {"What data structure is used in Breadth-First Search (BFS)?", {"Stack", "Queue", "Tree", "Heap"}, 1},
        {"What data structure is used in Depth-First Search (DFS)?", {"Stack", "Queue", "Tree", "Heap"}, 0},
        {"Which of these is a greedy algorithm?", {"0/1 Knapsack", "Fractional Knapsack", "Fibonacci", "Matrix Chain Multiplication"}, 1},
        {"Which of these uses Dynamic Programming?", {"Fractional Knapsack", "Dijkstra's", "0/1 Knapsack", "Kruskal's"}, 2},
        {"What is the space complexity of an adjacency matrix for V vertices?", {"O(V)", "O(V^2)", "O(E)", "O(V+E)"}, 1},
        {"What is the space complexity of an adjacency list for V vertices, E edges?", {"O(V^2)", "O(V+E)", "O(E)", "O(V)"}, 1},
        {"What is a complete binary tree?", {"All levels filled except possibly the last", "All leaves at the same level", "Every node has 2 children", "A degenerate tree"}, 0},
        {"What is the height of a balanced binary search tree with N nodes?", {"O(N)", "O(1)", "O(log N)", "O(N log N)"}, 2},
        {"Which data structure is best for implementing a priority queue?", {"Array", "Linked List", "Heap", "Stack"}, 2},
        {"What is the time complexity to insert into a Max Heap?", {"O(1)", "O(N)", "O(log N)", "O(N log N)"}, 2},
        {"What is the time complexity of Heap Sort?", {"O(N)", "O(N log N)", "O(N^2)", "O(log N)"}, 1},
        {"Which algorithm is used for string matching?", {"KMP", "Dijkstra", "Kruskal", "Prim"}, 0},
        {"In hashing, what handles collisions?", {"Chaining", "Linear Probing", "Both A and B", "None"}, 2},
        {"What is the typical time complexity for Hash Table lookup?", {"O(1)", "O(N)", "O(log N)", "O(N^2)"}, 0},
        {"Which of these is a divide and conquer algorithm?", {"Merge Sort", "Bubble Sort", "Insertion Sort", "Selection Sort"}, 0},
        {"What is the base case of a recursive function?", {"The recursive call", "The condition that stops recursion", "The initial input", "An infinite loop"}, 1},
        {"Which sorting algorithm compares adjacent elements and swaps them if they are in the wrong order?", {"Merge Sort", "Quick Sort", "Bubble Sort", "Insertion Sort"}, 2},
        {"What is an AVL tree?", {"A B-tree", "A completely unbalanced tree", "A self-balancing Binary Search Tree", "A spanning tree"}, 2},
        {"In an AVL tree, what is the maximum allowed difference in height between left and right subtrees?", {"0", "1", "2", "3"}, 1},
        {"Which color is NOT used in a Red-Black tree?", {"Red", "Black", "Blue", "None of the above"}, 2},
        {"What algorithm solves the Tower of Hanoi problem optimally?", {"Dynamic Programming", "Greedy", "Divide and Conquer (Recursion)", "Backtracking"}, 2},
        {"Which algorithm solves the N-Queens problem?", {"Dynamic Programming", "Greedy", "Divide and Conquer", "Backtracking"}, 3},
        {"What is a cycle in a graph?", {"A path that starts and ends at the same vertex", "A disconnected component", "A tree", "A straight line"}, 0},
        {"Which graph algorithm detects cycles in a directed graph?", {"BFS", "DFS", "Dijkstra", "Prim"}, 1},
        {"What is the Bellman-Ford algorithm used for?", {"Minimum Spanning Tree", "Maximum Flow", "Shortest Path with negative edges", "Topological Sort"}, 2},
        {"Which sorting algorithm is stable?", {"Quick Sort", "Heap Sort", "Merge Sort", "Selection Sort"}, 2},
        {"What is the time complexity of deleting from a doubly linked list if the node is known?", {"O(N)", "O(1)", "O(log N)", "O(N^2)"}, 1},
        {"Which search algorithm requires the array to be sorted?", {"Linear Search", "Binary Search", "DFS", "BFS"}, 1},
        {"What does a topological sort apply to?", {"Undirected graphs", "Trees only", "Directed Acyclic Graphs (DAGs)", "Cyclic graphs"}, 2},
        {"What is the time complexity of topological sorting?", {"O(V+E)", "O(V^2)", "O(E log V)", "O(1)"}, 0},
        {"What is the degree of a vertex?", {"Its value", "The number of edges connected to it", "Its distance from root", "Its color"}, 1},
        {"Which algorithmic paradigm is Floyd-Warshall?", {"Greedy", "Dynamic Programming", "Divide and Conquer", "Backtracking"}, 1},
        {"What is the time complexity of Floyd-Warshall?", {"O(V)", "O(V^2)", "O(V^3)", "O(E log V)"}, 2},
        {"What defines an Eulerian path?", {"Visits every vertex exactly once", "Visits every edge exactly once", "Shortest path", "Maximum flow"}, 1},
        {"What defines a Hamiltonian path?", {"Visits every vertex exactly once", "Visits every edge exactly once", "Shortest path", "Maximum flow"}, 0},
        {"What is the Master Theorem used for?", {"Solving recurrences", "Sorting arrays", "Finding shortest paths", "Graph coloring"}, 0},
    };
}

#endif
