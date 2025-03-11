# Traveling Salesman Problem & Local Search Algorithms

## Core Concept
The TSP aims to find the shortest possible route visiting each city exactly once and returning to the starting city, given:
- Complete graph
- Edge weights = Euclidean distances
- All vertices must be visited exactly once

## Search Paradigms

### 1. Constructive Search Methods
Build solutions from scratch by adding components incrementally.

#### A. Nearest Neighbor Heuristic (NNH)
```pseudocode
NearestNeighbor(Graph G):
    tour = []
    current = random_vertex(G)
    unvisited = G.vertices - {current}
    
    while unvisited not empty:
        next = find_nearest_unvisited(current, unvisited)
        tour.append(next)
        current = next
        unvisited.remove(next)
    
    tour.append(tour[0])  // Return to start
    return tour
```

#### B. Insertion Heuristics

1. Nearest Insertion
```pseudocode
NearestInsertion(Graph G):
    tour = [random_vertex(G)]
    while |tour| < |G.vertices|:
        nearest = find_nearest_vertex_to_tour(G, tour)
        best_pos = find_best_insertion_position(tour, nearest)
        tour.insert(best_pos, nearest)
    return tour
```

2. Cheapest Insertion
```pseudocode
CheapestInsertion(Graph G):
    tour = [random_vertex(G)]
    while |tour| < |G.vertices|:
        (vertex, position) = find_cheapest_insertion(G, tour)
        tour.insert(position, vertex)
    return tour
```

3. Farthest Insertion
```pseudocode
FarthestInsertion(Graph G):
    tour = [random_vertex(G)]
    while |tour| < |G.vertices|:
        farthest = find_farthest_vertex_from_tour(G, tour)
        best_pos = find_best_insertion_position(tour, farthest)
        tour.insert(best_pos, farthest)
    return tour
```

#### C. Greedy Heuristic
```pseudocode
GreedyHeuristic(Graph G):
    edges = sort_edges_by_weight(G)
    solution = []
    
    for edge in edges:
        if valid_addition(edge, solution):
            // Checks degree ≤ 2 and no early cycles
            solution.append(edge)
    
    return solution
```

### 2. Perturbative Search Methods
Improve existing solutions through local modifications.

#### A. 2-opt
```pseudocode
TwoOpt(Tour tour):
    improved = true
    while improved:
        improved = false
        for i in range(0, n-2):
            for j in range(i+2, n):
                if cost_decreases_after_2opt(tour, i, j):
                    tour = apply_2opt(tour, i, j)
                    improved = true
    return tour
```

#### B. 3-opt
```pseudocode
ThreeOpt(Tour tour):
    improved = true
    while improved:
        improved = false
        for i,j,k combinations:
            if cost_decreases_after_3opt(tour, i, j, k):
                tour = apply_3opt(tour, i, j, k)
                improved = true
    return tour
```

#### C. Node Shift
```pseudocode
NodeShift(Tour tour):
    improved = true
    while improved:
        improved = false
        for node in tour:
            for position in range(len(tour)):
                if cost_improves_after_shift(tour, node, position):
                    tour = shift_node(tour, node, position)
                    improved = true
    return tour
```

#### D. Node Swap
```pseudocode
NodeSwap(Tour tour):
    improved = true
    while improved:
        improved = false
        for i in range(len(tour)):
            for j in range(i+1, len(tour)):
                if cost_improves_after_swap(tour, i, j):
                    tour = swap_nodes(tour, i, j)
                    improved = true
    return tour
```

## Key Implementation Considerations

### 1. Semi-Greedy Variations
For constructive methods:
- Consider top-k candidates instead of best one
- Randomly select from these candidates
- Examples:
  - Top-3 nearest neighbors in NNH
  - Top-5 insertion positions in insertion heuristics

### 2. Speed-up Techniques
For perturbative methods:
- Fixed-radius near neighbor search
- Candidate lists
- Early termination conditions
- Efficient data structures for tour representation

### 3. Solution Quality vs. Time
- Construction heuristics: Faster but lower quality
- Perturbative methods: Better quality but more time
- Hybrid approaches: Use construction for initial solution, then improve with perturbation

### 4. Critical Implementation Details
1. Distance Calculation:
   - Efficient Euclidean distance computation
   - Distance matrix caching

2. Tour Validation:
   - Degree constraints (max 2)
   - Complete cycle
   - All vertices included

3. Memory Management:
   - Efficient tour representation
   - Avoiding redundant calculations
   - Caching intermediate results
