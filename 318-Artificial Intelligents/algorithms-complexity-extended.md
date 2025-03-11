# Extended Complexity Analysis

## Optimization Considerations

### 1. N-Puzzle Optimizations
- Memory Complexity Trade-offs:
  - Hash table for closed list: O(n²) space, O(1) lookup
  - Binary heap for open list: O(n) space, O(log n) operations
  - Pattern databases: O(n!) space, O(1) lookup

- State Representation Impact:
  - Array representation: O(n²) space, O(1) access
  - Linear encoding: O(n) space, slower access
  - Bit manipulation: O(n²/w) space where w is word size

### 2. Mancala Optimizations
- Transposition Table:
  - Space: O(k) where k is table size
  - Lookup: O(1)
  - Benefit: Reduces effective branching factor

- Move Ordering Impact:
  - Best case: O(b^(d/4))
  - Average case: O(b^(d/2))
  - Worst case: O(b^d)

### 3. Decision Tree Optimizations
- Pre-sorting Data:
  - Time: O(n log n)
  - Benefit: Faster attribute selection

- Attribute List Caching:
  - Space: O(n × d)
  - Benefit: O(1) access to attribute values

## Advanced Complexity Considerations

### 1. N-Puzzle
- IDA* Variant:
  - Time: O(b^d)
  - Space: O(d)
  - Better memory efficiency than A*

### 2. Mancala
- Iterative Deepening:
  - Time: O(b^d + b^(d-1) + ... + b)
  - Space: O(d)
  - Complete search with limited memory

### 3. Decision Tree
- Pruning Impact:
  - Pre-pruning: Reduces time to O(n × log d)
  - Post-pruning: Additional O(n) for validation
  - Cross-validation: Multiplies time by k-folds

## Practical Performance Factors

### 1. Cache Performance
- N-Puzzle:
  - State representation affects cache hits
  - Locality of reference in heuristic calculation

- Mancala:
  - Board state fits in L1 cache
  - Move generation benefits from cache locality

- Decision Tree:
  - Attribute access patterns
  - Data layout impact on cache misses

### 2. Parallel Processing Potential
- N-Puzzle:
  - Node expansion: Embarrassingly parallel
  - Heuristic calculation: Vectorizable

- Mancala:
  - Move exploration: Tree-parallel
  - Evaluation: SIMD-friendly

- Decision Tree:
  - Attribute evaluation: Data-parallel
  - Node splitting: Task-parallel

### 3. Memory Hierarchy Impact
- L1 Cache Access: ~4 cycles
- L2 Cache Access: ~10 cycles
- L3 Cache Access: ~40 cycles
- Main Memory: ~200 cycles

## Optimization Guidelines

1. N-Puzzle:
   - Use pattern databases for small puzzles
   - Implement IDA* for large puzzles
   - Optimize state representation

2. Mancala:
   - Implement transposition tables
   - Use principal variation search
   - Optimize move ordering

3. Decision Tree:
   - Pre-sort numerical attributes
   - Use attribute lists
   - Implement early stopping

## Real-world Performance Expectations

1. N-Puzzle:
   - 3×3: Solvable in milliseconds
   - 4×4: Seconds to minutes
   - 5×5: Minutes to hours

2. Mancala:
   - Depth 8: Milliseconds
   - Depth 12: Seconds
   - Depth 16: Minutes

3. Decision Tree:
   - 1000 samples: Milliseconds
   - 100K samples: Seconds
   - 1M samples: Minutes

These complexity considerations help in:
- Choosing appropriate algorithms
- Setting depth/complexity limits
- Memory-performance trade-offs
- Hardware utilization optimization
