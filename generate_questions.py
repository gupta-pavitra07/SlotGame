import json

questions = [
    {"q": "What is the time complexity of Binary Search?", "opts": ["O(N)", "O(log N)", "O(N^2)", "O(1)"], "ans": 1},
    {"q": "Which data structure follows LIFO?", "opts": ["Queue", "Tree", "Stack", "Graph"], "ans": 2},
    {"q": "Which data structure follows FIFO?", "opts": ["Queue", "Stack", "Tree", "Graph"], "ans": 0},
    {"q": "What is the worst-case time complexity of Quick Sort?", "opts": ["O(N log N)", "O(N)", "O(N^2)", "O(1)"], "ans": 2},
    {"q": "What is the best-case time complexity of Merge Sort?", "opts": ["O(N log N)", "O(N)", "O(N^2)", "O(1)"], "ans": 0},
    {"q": "Which algorithm is used for finding the shortest path in a weighted graph?", "opts": ["Dijkstra's", "Kruskal's", "Prim's", "DFS"], "ans": 0},
    {"q": "Which algorithm finds the Minimum Spanning Tree?", "opts": ["Dijkstra's", "Kruskal's", "Bellman-Ford", "Floyd-Warshall"], "ans": 1},
    {"q": "What is the maximum number of children in a Binary Tree node?", "opts": ["1", "2", "3", "Unlimited"], "ans": 1},
    {"q": "What traversal visits Left, Root, Right?", "opts": ["Pre-order", "In-order", "Post-order", "Level-order"], "ans": 1},
    {"q": "What traversal visits Root, Left, Right?", "opts": ["Pre-order", "In-order", "Post-order", "Level-order"], "ans": 0},
    {"q": "What traversal visits Left, Right, Root?", "opts": ["Pre-order", "In-order", "Post-order", "Level-order"], "ans": 2},
    {"q": "What is the time complexity of accessing an element in an array?", "opts": ["O(N)", "O(log N)", "O(1)", "O(N^2)"], "ans": 2},
    {"q": "Which sorting algorithm is most efficient for nearly sorted data?", "opts": ["Quick Sort", "Merge Sort", "Insertion Sort", "Selection Sort"], "ans": 2},
    {"q": "What data structure is used to implement recursion?", "opts": ["Queue", "Stack", "Tree", "Heap"], "ans": 1},
    {"q": "What data structure is used in Breadth-First Search (BFS)?", "opts": ["Stack", "Queue", "Tree", "Heap"], "ans": 1},
    {"q": "What data structure is used in Depth-First Search (DFS)?", "opts": ["Stack", "Queue", "Tree", "Heap"], "ans": 0},
    {"q": "Which of these is a greedy algorithm?", "opts": ["0/1 Knapsack", "Fractional Knapsack", "Fibonacci", "Matrix Chain Multiplication"], "ans": 1},
    {"q": "Which of these uses Dynamic Programming?", "opts": ["Fractional Knapsack", "Dijkstra's", "0/1 Knapsack", "Kruskal's"], "ans": 2},
    {"q": "What is the space complexity of an adjacency matrix for V vertices?", "opts": ["O(V)", "O(V^2)", "O(E)", "O(V+E)"], "ans": 1},
    {"q": "What is the space complexity of an adjacency list for V vertices, E edges?", "opts": ["O(V^2)", "O(V+E)", "O(E)", "O(V)"], "ans": 1},
    {"q": "What is a complete binary tree?", "opts": ["All levels filled except possibly the last", "All leaves at the same level", "Every node has 2 children", "A degenerate tree"], "ans": 0},
    {"q": "What is the height of a balanced binary search tree with N nodes?", "opts": ["O(N)", "O(1)", "O(log N)", "O(N log N)"], "ans": 2},
    {"q": "Which data structure is best for implementing a priority queue?", "opts": ["Array", "Linked List", "Heap", "Stack"], "ans": 2},
    {"q": "What is the time complexity to insert into a Max Heap?", "opts": ["O(1)", "O(N)", "O(log N)", "O(N log N)"], "ans": 2},
    {"q": "What is the time complexity of Heap Sort?", "opts": ["O(N)", "O(N log N)", "O(N^2)", "O(log N)"], "ans": 1},
    {"q": "Which algorithm is used for string matching?", "opts": ["KMP", "Dijkstra", "Kruskal", "Prim"], "ans": 0},
    {"q": "In hashing, what handles collisions?", "opts": ["Chaining", "Linear Probing", "Both A and B", "None"], "ans": 2},
    {"q": "What is the typical time complexity for Hash Table lookup?", "opts": ["O(1)", "O(N)", "O(log N)", "O(N^2)"], "ans": 0},
    {"q": "Which of these is a divide and conquer algorithm?", "opts": ["Merge Sort", "Bubble Sort", "Insertion Sort", "Selection Sort"], "ans": 0},
    {"q": "What is the base case of a recursive function?", "opts": ["The recursive call", "The condition that stops recursion", "The initial input", "An infinite loop"], "ans": 1},
    {"q": "Which sorting algorithm compares adjacent elements and swaps them if they are in the wrong order?", "opts": ["Merge Sort", "Quick Sort", "Bubble Sort", "Insertion Sort"], "ans": 2},
    {"q": "What is an AVL tree?", "opts": ["A B-tree", "A completely unbalanced tree", "A self-balancing Binary Search Tree", "A spanning tree"], "ans": 2},
    {"q": "In an AVL tree, what is the maximum allowed difference in height between left and right subtrees?", "opts": ["0", "1", "2", "3"], "ans": 1},
    {"q": "Which color is NOT used in a Red-Black tree?", "opts": ["Red", "Black", "Blue", "None of the above"], "ans": 2},
    {"q": "What algorithm solves the Tower of Hanoi problem optimally?", "opts": ["Dynamic Programming", "Greedy", "Divide and Conquer (Recursion)", "Backtracking"], "ans": 2},
    {"q": "Which algorithm solves the N-Queens problem?", "opts": ["Dynamic Programming", "Greedy", "Divide and Conquer", "Backtracking"], "ans": 3},
    {"q": "What is a cycle in a graph?", "opts": ["A path that starts and ends at the same vertex", "A disconnected component", "A tree", "A straight line"], "ans": 0},
    {"q": "Which graph algorithm detects cycles in a directed graph?", "opts": ["BFS", "DFS", "Dijkstra", "Prim"], "ans": 1},
    {"q": "What is the Bellman-Ford algorithm used for?", "opts": ["Minimum Spanning Tree", "Maximum Flow", "Shortest Path with negative edges", "Topological Sort"], "ans": 2},
    {"q": "Which sorting algorithm is stable?", "opts": ["Quick Sort", "Heap Sort", "Merge Sort", "Selection Sort"], "ans": 2},
    {"q": "What is the time complexity of deleting from a doubly linked list if the node is known?", "opts": ["O(N)", "O(1)", "O(log N)", "O(N^2)"], "ans": 1},
    {"q": "Which search algorithm requires the array to be sorted?", "opts": ["Linear Search", "Binary Search", "DFS", "BFS"], "ans": 1},
    {"q": "What does a topological sort apply to?", "opts": ["Undirected graphs", "Trees only", "Directed Acyclic Graphs (DAGs)", "Cyclic graphs"], "ans": 2},
    {"q": "What is the time complexity of topological sorting?", "opts": ["O(V+E)", "O(V^2)", "O(E log V)", "O(1)"], "ans": 0},
    {"q": "What is the degree of a vertex?", "opts": ["Its value", "The number of edges connected to it", "Its distance from root", "Its color"], "ans": 1},
    {"q": "Which algorithmic paradigm is Floyd-Warshall?", "opts": ["Greedy", "Dynamic Programming", "Divide and Conquer", "Backtracking"], "ans": 1},
    {"q": "What is the time complexity of Floyd-Warshall?", "opts": ["O(V)", "O(V^2)", "O(V^3)", "O(E log V)"], "ans": 2},
    {"q": "What defines an Eulerian path?", "opts": ["Visits every vertex exactly once", "Visits every edge exactly once", "Shortest path", "Maximum flow"], "ans": 1},
    {"q": "What defines a Hamiltonian path?", "opts": ["Visits every vertex exactly once", "Visits every edge exactly once", "Shortest path", "Maximum flow"], "ans": 0},
    {"q": "What is the Master Theorem used for?", "opts": ["Solving recurrences", "Sorting arrays", "Finding shortest paths", "Graph coloring"], "ans": 0}
]

with open('questions.h', 'w') as f:
    f.write("#ifndef QUESTIONS_H\n#define QUESTIONS_H\n\n#include <vector>\n#include <string>\n\n")
    f.write("struct Question {\n    std::string text;\n    std::vector<std::string> options;\n    int correctIndex;\n};\n\n")
    f.write("inline std::vector<Question> get50Questions() {\n    return {\n")
    for q in questions:
        f.write(f'        {{"{q["q"]}", {{"{q["opts"][0]}", "{q["opts"][1]}", "{q["opts"][2]}", "{q["opts"][3]}"}}, {q["ans"]}}},\n')
    f.write("    };\n}\n\n#endif\n")

