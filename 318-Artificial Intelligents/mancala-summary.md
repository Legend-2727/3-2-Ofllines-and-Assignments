# Mancala Game & Adversarial Search Algorithms

## Core Concept
Mancala is a two-player strategy game implemented using adversarial search algorithms, primarily minimax with alpha-beta pruning. The game involves distributing stones across bins with the goal of capturing more stones than the opponent.

## Game Structure
- Board Layout: 6 bins per player + 1 storage bin (Mancala) each
- Initial State: 4 stones in each bin, empty storage bins
- Objective: Collect the most stones in your storage bin

## Core Algorithms

### 1. Minimax Algorithm
- Type: Adversarial search algorithm
- Purpose: Find the optimal move by minimizing opponent's maximum gain
- Process:
  - MAX player tries to maximize score
  - MIN player tries to minimize score
  - Alternates between levels

### 2. Alpha-Beta Pruning
- Enhancement to minimax
- Eliminates branches that won't influence final decision
- Components:
  - Alpha: Best value MAX can guarantee
  - Beta: Best value MIN can guarantee
  - Prunes when beta ≤ alpha

## Heuristic Functions
Four main heuristics with increasing complexity:

### Heuristic-1 (Basic)
```
evaluation = stones_in_my_storage - stones_in_opponents_storage
```

### Heuristic-2 (Position Based)
```
evaluation = W1 * (stones_in_my_storage - stones_in_opponents_storage) + 
            W2 * (stones_on_my_side - stones_on_opponents_side)
```

### Heuristic-3 (Movement Based)
```
evaluation = W1 * (stones_in_my_storage - stones_in_opponents_storage) +
            W2 * (stones_on_my_side - stones_on_opponents_side) +
            W3 * (additional_move_earned)
```

### Heuristic-4 (Comprehensive)
```
evaluation = W1 * (stones_in_my_storage - stones_in_opponents_storage) +
            W2 * (stones_on_my_side - stones_on_opponents_side) +
            W3 * (additional_move_earned) +
            W4 * (stones_captured)
```

## Strategic Factors to Consider
1. Position Analysis:
   - First valid move location
   - Stone distribution
   - Proximity to storage

2. Game State Evaluation:
   - Current lead/deficit
   - Progress toward winning
   - Opponent's progress
   - Stone distribution on both sides

3. Special Moves:
   - Extra move potential
   - Capture opportunities
   - Overflow prevention

## Implementation Considerations

### 1. Search Strategy Options:
- Basic Minimax with alpha-beta pruning
- Iterative deepening search
- Variable depth limits
- Move ordering optimization

### 2. Performance Factors:
- Branching factor
- Search depth
- Pruning efficiency
- Heuristic computation cost

## Sample Exam Questions

### Theoretical Understanding:
1. How does alpha-beta pruning improve upon basic minimax?
2. Why is move ordering important for alpha-beta pruning efficiency?
3. Compare and contrast the four heuristic functions provided.

### Algorithm Analysis:
1. What's the time complexity with and without alpha-beta pruning?
2. How does the branching factor affect search depth choices?
3. Why might iterative deepening be useful in Mancala?

### Heuristic Design:
1. Why might Heuristic-4 perform better than Heuristic-1?
2. How would you choose weights (W1, W2, etc.) for the heuristics?
3. Design a new heuristic incorporating additional strategic factors.

### Implementation:
1. How would you implement move generation efficiently?
2. What data structure best represents the game state?
3. How would you handle the special case of extra moves?

### Strategy Questions:
1. Why is the first valid move position strategically important?
2. How does stone proximity to storage affect strategy?
3. When is capturing stones more valuable than earning extra moves?

## Critical Points to Remember

1. Algorithm Efficiency:
   - Proper alpha-beta implementation is crucial
   - Move ordering significantly affects pruning
   - Balance between search depth and time constraints

2. Heuristic Design:
   - More complex isn't always better
   - Weights need careful tuning
   - Consider computation cost vs. accuracy

3. Game-Specific Knowledge:
   - Understanding special moves
   - Recognizing winning patterns
   - Strategic position evaluation

4. Testing Considerations:
   - Computer vs. computer trials
   - Win-loss ratio analysis
   - Performance metrics tracking
