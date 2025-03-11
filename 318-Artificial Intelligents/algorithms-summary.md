# Core Algorithms & Time Complexities

## 1. N-Puzzle A* Search
```pseudocode
A_Star(initial_state, goal_state):
    open_list = PriorityQueue()
    closed_list = Set()
    
    open_list.add(initial_state, priority=0)
    
    while not open_list.empty():
        current = open_list.pop()
        
        if current == goal_state:
            return reconstruct_path(current)
            
        closed_list.add(current)
        
        for neighbor in get_neighbors(current):
            if neighbor in closed_list:
                continue
                
            g_score = current.g + 1
            h_score = calculate_heuristic(neighbor, goal_state)
            f_score = g_score + h_score
            
            if neighbor not in open_list or g_score < neighbor.g:
                neighbor.g = g_score
                neighbor.parent = current
                open_list.add(neighbor, priority=f_score)
                
    return None
```

## 2. Mancala with Minimax and Alpha-Beta
```pseudocode
AlphaBeta(state, depth, alpha, beta, maximizing_player):
    if depth == 0 or is_terminal(state):
        return evaluate_position(state)
        
    if maximizing_player:
        max_eval = -infinity
        for move in get_valid_moves(state):
            eval = AlphaBeta(make_move(state, move), depth-1, alpha, beta, false)
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval
    else:
        min_eval = infinity
        for move in get_valid_moves(state):
            eval = AlphaBeta(make_move(state, move), depth-1, alpha, beta, true)
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval
```

## Time Complexities

### 1. N-Puzzle
- A* Search: O(b^d) where b is branching factor and d is solution depth
  - With Manhattan Distance: O(n² × 4^n)
  - With Hamming Distance: O(n² × 4^n)
- Checking Solvability: O(n²)
- Getting Neighbors: O(1)
- Heuristic Calculation:
  - Manhattan Distance: O(n)
  - Hamming Distance: O(n)

### 2. Mancala
- Minimax without α-β: O(b^d) where b is valid moves and d is depth
- Minimax with α-β: O(b^(d/2)) average case
- Heuristic Evaluation: O(1)
- Move Generation: O(1)
- Board State Update: O(1)

### 3. Decision Tree
- Training (without randomization):
  - Best case: O(n × d) where n is samples and d is features
  - Average case: O(n × d × log n)
  - Worst case: O(n × d × n)
  
- Information Gain Calculation: O(n)
- Gini Impurity Calculation: O(n)
- Prediction: O(h) where h is tree height
- Random Selection from Top 3: Additional O(d log d) for sorting attributes

### Auxiliary Operations
- Priority Queue Operations: O(log n)
- Set Operations: O(1) average case
- Hash Table Lookups: O(1) average case

### Space Complexities
1. N-Puzzle:
   - O(b^d) for storing nodes
   - O(n²) for state representation

2. Mancala:
   - O(b×d) for game tree
   - O(1) for board state

3. Decision Tree:
   - O(n) for balanced tree
   - O(n²) worst case for skewed tree

Note: 
- n = problem size (grid size for puzzle, number of samples for decision tree)
- b = branching factor
- d = depth/levels
- h = tree height
