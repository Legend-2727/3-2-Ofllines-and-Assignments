# AI Course Exam Preparation Guide

## Multiple Choice Questions

### N-Puzzle
1. **Q**: What determines the solvability of an N-puzzle with odd grid size?
   - a) Total number of inversions is even
   - b) Total number of inversions is odd
   - c) Position of blank space
   - d) Number of misplaced tiles
   **Answer**: a) Total number of inversions is even
   **Explanation**: For odd grid sizes, a puzzle is solvable if and only if the number of inversions is even.

2. **Q**: In A* search for N-puzzle, which heuristic is more efficient?
   - a) Hamming distance
   - b) Manhattan distance
   - c) Both are equally efficient
   - d) Depends on the puzzle size
   **Answer**: b) Manhattan distance
   **Explanation**: Manhattan distance provides a more accurate estimate of moves needed, leading to fewer node expansions.

### Mancala & Alpha-Beta Pruning
3. **Q**: What's the primary advantage of alpha-beta pruning over basic minimax?
   - a) Better move selection
   - b) Reduced search space
   - c) More accurate evaluation
   - d) Simpler implementation
   **Answer**: b) Reduced search space
   **Explanation**: Alpha-beta pruning eliminates branches that cannot influence the final decision.

4. **Q**: Which heuristic component is most crucial for Mancala evaluation?
   - a) Stones in storage
   - b) Captured stones
   - c) Extra moves earned
   - d) Stone distribution
   **Answer**: a) Stones in storage
   **Explanation**: Storage content directly relates to winning condition and score.

### Decision Trees
5. **Q**: When would Gini impurity be preferred over Information Gain?
   - a) With continuous attributes
   - b) With categorical attributes
   - c) With missing values
   - d) With balanced datasets
   **Answer**: a) With continuous attributes
   **Explanation**: Gini impurity is computationally simpler and works well with continuous attributes.

## Written Questions

### N-Puzzle
1. **Q**: Explain why Manhattan distance is admissible for N-puzzle and prove it never overestimates.

**Answer**:
- Manhattan distance is admissible because it counts minimum moves needed for each tile
- Each tile must move at least its Manhattan distance to reach goal position
- No tile can move diagonally, only horizontal/vertical
- Therefore:
  - Actual moves ≥ Manhattan distance
  - Never overestimates real cost
  - Sum of underestimates remains underestimate

2. **Q**: How does A* search differ from BFS in solving N-puzzle? Compare their space and time complexities.

**Answer**:
- BFS:
  - Explores all nodes at current depth
  - Space/Time complexity: O(b^d)
  - Complete but inefficient
- A*:
  - Uses heuristic to guide search
  - Complexity: O(b^d) worst case, but practically much better
  - More efficient with good heuristic
- Key differences:
  - Search strategy (informed vs uninformed)
  - Memory usage
  - Solution optimality guarantee

### Mancala
3. **Q**: Describe how move ordering affects alpha-beta pruning efficiency in Mancala. Provide examples.

**Answer**:
- Better move ordering leads to more pruning
- Best moves should be examined first:
  - Captures
  - Extra turns
  - Storage additions
- Impact on efficiency:
  - Best case: O(b^(d/2))
  - Worst case: O(b^d)
- Example scenarios:
  - Examining captures first
  - Prioritizing extra-turn moves
  - Looking at storage-adding moves

### Decision Trees
4. **Q**: Compare and contrast Information Gain and Gini impurity with mathematical proofs and practical implications.

**Answer**:
- Information Gain:
  - Based on entropy: -Σ(pi * log2(pi))
  - Measures reduction in uncertainty
  - Range: [0,1]
- Gini Impurity:
  - 1 - Σ(pi²)
  - Measures probability of incorrect classification
  - Range: [0,0.5]
- Practical differences:
  - Computational complexity
  - Behavior with outliers
  - Performance with continuous attributes

## Theory Application Questions

1. **Q**: Given a 3×3 puzzle state, show step by step:
   - Calculate Manhattan distance
   - Determine solvability
   - First two levels of A* search

2. **Q**: For a Mancala position:
   - Evaluate board state using different heuristics
   - Show alpha-beta pruning process
   - Explain move selection rationale

3. **Q**: With a small dataset:
   - Calculate Information Gain
   - Calculate Gini impurity
   - Compare split decisions

## Important Points to Remember

1. Algorithm Properties:
   - Completeness
   - Optimality
   - Time/Space complexity
   - Practical considerations

2. Implementation Details:
   - Data structures used
   - Optimization techniques
   - Edge cases handling

3. Comparison Points:
   - When to use which algorithm
   - Trade-offs involved
   - Performance characteristics

4. Mathematical Foundations:
   - Heuristic admissibility
   - Probability calculations
   - Complexity analysis

Remember to:
- Show your work in calculations
- Explain reasoning clearly
- Consider edge cases
- Mention practical implications
