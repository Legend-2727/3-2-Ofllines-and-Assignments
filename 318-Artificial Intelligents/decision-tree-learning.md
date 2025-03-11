# Decision Tree Learning Algorithm Implementation Guide

## Core Concepts

### 1. Attribute Selection Measures

#### Information Gain
```
InfoGain(S, A) = Entropy(S) - Σ(|Sv|/|S| * Entropy(Sv))
where:
- S is the dataset
- A is the attribute
- Sv is the subset where attribute A has value v
- Entropy(S) = -Σ(pi * log2(pi))
```

#### Gini Impurity
```
Gini(S) = 1 - Σ(pi²)
where:
- pi is the probability of class i in dataset S
```

### 2. Core Algorithm Pseudocode

```pseudocode
DecisionTreeLearning(data, attributes, selection_criteria):
    # Base cases
    if all_same_class(data):
        return Leaf(data[0].class)
    if attributes.empty():
        return Leaf(majority_class(data))
        
    # Select best attribute based on criteria
    if selection_criteria == "information_gain":
        best_attribute = select_by_information_gain(data, attributes)
    else:
        best_attribute = select_by_gini_impurity(data, attributes)
        
    # Create node
    root = Node(best_attribute)
    
    # Recurse for each value of the attribute
    for each value in best_attribute.values:
        subset = get_subset(data, best_attribute, value)
        root.add_branch(value, 
            DecisionTreeLearning(subset, 
                               attributes - best_attribute, 
                               selection_criteria))
    
    return root
```

### 3. Random Selection from Top 3 Variant

```pseudocode
SelectAttributeFromTop3(data, attributes, selection_criteria):
    if selection_criteria == "information_gain":
        scores = [(attr, calculate_info_gain(data, attr)) 
                 for attr in attributes]
    else:
        scores = [(attr, calculate_gini(data, attr)) 
                 for attr in attributes]
    
    # Sort by score and get top 3
    top3 = sort_by_score(scores)[:3]
    
    # Randomly select one
    return random_choice(top3)
```

## Implementation Details

### 1. Data Management
```pseudocode
class DataSet:
    def split_train_test(data, train_ratio=0.8):
        shuffled = shuffle(data)
        split_point = int(len(data) * train_ratio)
        return data[:split_point], data[split_point:]
        
    def get_subset(data, attribute, value):
        return [row for row in data if row[attribute] == value]
```

### 2. Evaluation Metrics
```pseudocode
class Evaluator:
    def calculate_accuracy(tree, test_data):
        correct = 0
        for row in test_data:
            prediction = tree.predict(row)
            if prediction == row.class:
                correct += 1
        return correct / len(test_data)
        
    def run_experiment(data, runs=20):
        results = {
            'information_gain': [],
            'gini_impurity': []
        }
        
        for _ in range(runs):
            train, test = split_train_test(data)
            
            # Train and evaluate with both criteria
            for criteria in ['information_gain', 'gini_impurity']:
                tree = DecisionTreeLearning(train, attributes, criteria)
                accuracy = calculate_accuracy(tree, test)
                results[criteria].append(accuracy)
                
        return average_results(results)
```

### 3. Helper Functions

```pseudocode
def calculate_entropy(data):
    class_counts = count_classes(data)
    total = len(data)
    entropy = 0
    
    for count in class_counts:
        p = count / total
        entropy -= p * log2(p)
    
    return entropy

def calculate_gini(data):
    class_counts = count_classes(data)
    total = len(data)
    gini = 1
    
    for count in class_counts:
        p = count / total
        gini -= p * p
    
    return gini
```

## Experimental Setup

### 1. Main Experiment Flow
```pseudocode
def run_full_experiment():
    results = {
        'best_attribute': {
            'information_gain': [],
            'gini_impurity': []
        },
        'random_top3': {
            'information_gain': [],
            'gini_impurity': []
        }
    }
    
    for run in range(20):
        train_data, test_data = split_data(dataset)
        
        # Test all combinations
        for selection_method in ['best_attribute', 'random_top3']:
            for criteria in ['information_gain', 'gini_impurity']:
                tree = train_tree(train_data, selection_method, criteria)
                accuracy = test_tree(tree, test_data)
                results[selection_method][criteria].append(accuracy)
    
    return calculate_average_results(results)
```

### 2. Results Table Generation
```pseudocode
def generate_results_table(results):
    table = Table()
    table.add_header(["Strategy", "Information Gain", "Gini Impurity"])
    
    table.add_row([
        "Best Attribute",
        format_accuracy(results['best_attribute']['information_gain']),
        format_accuracy(results['best_attribute']['gini_impurity'])
    ])
    
    table.add_row([
        "Random Top 3",
        format_accuracy(results['random_top3']['information_gain']),
        format_accuracy(results['random_top3']['gini_impurity'])
    ])
    
    return table
```

## Key Points for Implementation

1. Attribute Selection:
   - Implement both information gain and Gini impurity
   - Maintain efficient calculation methods
   - Handle categorical and numerical attributes

2. Tree Construction:
   - Implement proper stopping criteria
   - Handle missing values if present
   - Maintain efficient recursion

3. Experimental Design:
   - Proper random splitting of data
   - Consistent evaluation metrics
   - Statistical significance of results

4. Performance Optimization:
   - Cache calculations where possible
   - Efficient data structure usage
   - Memory management for large datasets
