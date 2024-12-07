#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <algorithm>
#include <cmath>
#include <random>
#include <iomanip>

// Structure to represent each car instance
struct CarInstance {
    std::string buying;
    std::string maint;
    std::string doors;
    std::string persons;
    std::string lug_boot;
    std::string safety;
    std::string classLabel;

    CarInstance(std::string b, std::string m, std::string d, std::string p, std::string l, std::string s, std::string c)
        : buying(b), maint(m), doors(d), persons(p), lug_boot(l), safety(s), classLabel(c) {}
};

// Structure to represent decision tree nodes
struct DecisionNode {
    std::string attribute; // Attribute to split on
    std::map<std::string, std::shared_ptr<DecisionNode>> children; // Child nodes
    std::string classLabel; // If leaf node

    // Constructor for internal node
    DecisionNode(const std::string& attr) : attribute(attr), classLabel("") {}

    // Constructor for leaf node
    DecisionNode(const std::string& label, bool isLeaf) : attribute(""), classLabel(label) {}
    
    bool isLeaf() const {
        return !classLabel.empty();
    }
};

// Function to load data from file
std::vector<CarInstance> loadData(const std::string& filename) {
    std::vector<CarInstance> data;
    std::ifstream infile(filename);
    std::string line;

    while (std::getline(infile, line)) {
        if(line.empty()) continue; // Skip empty lines
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 7) continue; // Ensure correct number of attributes

        data.emplace_back(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6]);
    }

    infile.close();
    return data;
}

// Function to count class labels
//end criteria konta kotogula ase
std::unordered_map<std::string, int> countClasses(const std::vector<CarInstance>& data) {
    std::unordered_map<std::string, int> classCounts;
    for (const auto& instance : data) {
        classCounts[instance.classLabel]++;
    }
    return classCounts;
}

// Function to get unique values for an attribute
//ekta atribute er koyta unique values thakte pare seita
std::vector<std::string> getUniqueValues(const std::vector<CarInstance>& data, const std::string& attribute) {
    std::unordered_map<std::string, bool> uniqueMap;
    std::vector<std::string> uniqueValues;
    for (const auto& instance : data) {
        std::string value;
        if (attribute == "buying") value = instance.buying;
        else if (attribute == "maint") value = instance.maint;
        else if (attribute == "doors") value = instance.doors;
        else if (attribute == "persons") value = instance.persons;
        else if (attribute == "lug_boot") value = instance.lug_boot;
        else if (attribute == "safety") value = instance.safety;
        if (!uniqueMap[value]) {
            uniqueMap[value] = true;
            uniqueValues.push_back(value);
        }
    }
    return uniqueValues;
}

// Function to calculate entropy
double calculateEntropy(const std::vector<CarInstance>& data) {
    auto classCounts = countClasses(data);
    double entropy = 0.0;
    int total = data.size();

    for (const auto& pair : classCounts) {
        double p = static_cast<double>(pair.second) / total;
        if (p > 0)
            entropy -= p * (std::log(p) / std::log(2));
    }
    return entropy;
}

// Function to calculate Information Gain
double calculateInformationGain(const std::vector<CarInstance>& data, const std::string& attribute) {
    double totalEntropy = calculateEntropy(data);
    auto subsets = std::unordered_map<std::string, std::vector<CarInstance>>();

    // Split data based on attribute values
    for (const auto& instance : data) {
        std::string value;
        if (attribute == "buying") value = instance.buying;
        else if (attribute == "maint") value = instance.maint;
        else if (attribute == "doors") value = instance.doors;
        else if (attribute == "persons") value = instance.persons;
        else if (attribute == "lug_boot") value = instance.lug_boot;
        else if (attribute == "safety") value = instance.safety;

        subsets[value].push_back(instance);
    }

    // Calculate weighted entropy
    double weightedEntropy = 0.0;
    int total = data.size();
    for (const auto& pair : subsets) {
        double subsetEntropy = calculateEntropy(pair.second);
        weightedEntropy += (static_cast<double>(pair.second.size()) / total) * subsetEntropy;
    }

    return totalEntropy - weightedEntropy;
}

// Function to calculate Gini Impurity
double calculateGini(const std::vector<CarInstance>& data) {
    auto classCounts = countClasses(data);
    double gini = 1.0;
    int total = data.size();

    for (const auto& pair : classCounts) {
        double p = static_cast<double>(pair.second) / total;
        gini -= p * p;
    }

    return gini;
}

// Function to calculate Gini Gain
double calculateGiniGain(const std::vector<CarInstance>& data, const std::string& attribute) {
    double totalGini = calculateGini(data);
    auto subsets = std::unordered_map<std::string, std::vector<CarInstance>>();

    // Split data based on attribute values
    for (const auto& instance : data) {
        std::string value;
        if (attribute == "buying") value = instance.buying;
        else if (attribute == "maint") value = instance.maint;
        else if (attribute == "doors") value = instance.doors;
        else if (attribute == "persons") value = instance.persons;
        else if (attribute == "lug_boot") value = instance.lug_boot;
        else if (attribute == "safety") value = instance.safety;

        subsets[value].push_back(instance);
    }

    // Calculate weighted Gini
    double weightedGini = 0.0;
    int total = data.size();
    for (const auto& pair : subsets) {
        double subsetGini = calculateGini(pair.second);
        weightedGini += (static_cast<double>(pair.second.size()) / total) * subsetGini;
    }

    return totalGini - weightedGini;
}

// Function to select the best attribute based on the selection criterion
std::string selectBestAttribute(const std::vector<CarInstance>& data, const std::vector<std::string>& attributes, const std::string& criterion) {
    double bestGain = -std::numeric_limits<double>::infinity();
    std::string bestAttribute = "";

    for (const auto& attribute : attributes) {
        double gain;
        if (criterion == "information_gain") {
            gain = calculateInformationGain(data, attribute);
        }
        else if (criterion == "gini_impurity") {
            gain = calculateGiniGain(data, attribute);
        }
        else {
            std::cerr << "Unknown selection criterion: " << criterion << std::endl;
            exit(1);
        }

        if (gain > bestGain) {
            bestGain = gain;
            bestAttribute = attribute;
        }
    }

    return bestAttribute;
}

// Function to get the majority class in the dataset
// leaf class value te konta sb cheye beshi ase mane unacc beshi naki acc 
std::string majorityClass(const std::vector<CarInstance>& data) {
    auto classCounts = countClasses(data);
    std::string majority;
    int maxCount = -1;
    for (const auto& pair : classCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            majority = pair.first;
        }
    }
    return majority;
}

// Recursive function to build the decision tree
std::shared_ptr<DecisionNode> buildDecisionTree(const std::vector<CarInstance>& data, std::vector<std::string> attributes, const std::string& criterion) {
    // If all instances have the same class, return a leaf node
    auto classCounts = countClasses(data);
    if (classCounts.size() == 1) {
        return std::make_shared<DecisionNode>(classCounts.begin()->first, true);
    }

    // If no attributes left, return a leaf node with the majority class
    if (attributes.empty()) {
        return std::make_shared<DecisionNode>(majorityClass(data), true);
    }

    // Select the best attribute
    std::string bestAttribute = selectBestAttribute(data, attributes, criterion);
    if (bestAttribute.empty()) {
        // In case no attribute provides any gain, return majority class
        return std::make_shared<DecisionNode>(majorityClass(data), true);
    }

    // Create the root node for this subtree
    auto root = std::make_shared<DecisionNode>(bestAttribute);

    // Get unique values of the best attribute
    auto uniqueValues = getUniqueValues(data, bestAttribute);

    // For each unique value, create a subtree
    for (const auto& value : uniqueValues) {
        // Split the data
        std::vector<CarInstance> subset;
        for (const auto& instance : data) {
            std::string instanceValue;
            if (bestAttribute == "buying") instanceValue = instance.buying;
            else if (bestAttribute == "maint") instanceValue = instance.maint;
            else if (bestAttribute == "doors") instanceValue = instance.doors;
            else if (bestAttribute == "persons") instanceValue = instance.persons;
            else if (bestAttribute == "lug_boot") instanceValue = instance.lug_boot;
            else if (bestAttribute == "safety") instanceValue = instance.safety;

            if (instanceValue == value) {
                subset.push_back(instance);
            }
        }

        if (subset.empty()) {
            // If subset is empty, attach a leaf node with majority class
            root->children[value] = std::make_shared<DecisionNode>(majorityClass(data), true);
        }
        else {
            // Remove the used attribute for the subtree
            std::vector<std::string> remainingAttributes = attributes;
            remainingAttributes.erase(std::remove(remainingAttributes.begin(), remainingAttributes.end(), bestAttribute), remainingAttributes.end());

            // Recursively build the subtree
            root->children[value] = buildDecisionTree(subset, remainingAttributes, criterion);
        }
    }

    return root;
}

// Function to get top N attributes based on gain
std::vector<std::pair<std::string, double>> getTopAttributes(const std::vector<CarInstance>& data, const std::vector<std::string>& attributes, const std::string& criterion, int topN = 3) {
    std::vector<std::pair<std::string, double>> attributeGains;

    for (const auto& attribute : attributes) {
        double gain;
        if (criterion == "information_gain") {
            gain = calculateInformationGain(data, attribute);
        }
        else if (criterion == "gini_impurity") {
            gain = calculateGiniGain(data, attribute);
        }
        else {
            std::cerr << "Unknown selection criterion: " << criterion << std::endl;
            exit(1);
        }
        attributeGains.emplace_back(attribute, gain);
    }

    // Sort attributes based on gain in descending order
    std::sort(attributeGains.begin(), attributeGains.end(),
        [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) -> bool {
            return a.second > b.second;
        });

    // Select top N
    if (attributeGains.size() < topN) topN = attributeGains.size();
    std::vector<std::pair<std::string, double>> topAttributes(attributeGains.begin(), attributeGains.begin() + topN);
    return topAttributes;
}

// Function to select a random attribute from top three
std::shared_ptr<DecisionNode> buildDecisionTreeRandomTop3(const std::vector<CarInstance>& data, std::vector<std::string> attributes, const std::string& criterion) {
    // If all instances have the same class, return a leaf node
    auto classCounts = countClasses(data);
    if (classCounts.size() == 1) {
        //pure
        return std::make_shared<DecisionNode>(classCounts.begin()->first, true);
    }

    // If no attributes left, return a leaf node with the majority class
    if (attributes.empty()) {
        //spilt korar kono attribute nai
        return std::make_shared<DecisionNode>(majorityClass(data), true);
    }

    // Get top three attributes
    auto topAttributes = getTopAttributes(data, attributes, criterion, 3);
    if (topAttributes.empty()) {
        //necessary na may be
        return std::make_shared<DecisionNode>(majorityClass(data), true);
    }

    // Randomly select one attribute from the top three
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, topAttributes.size() - 1);
    int selectedIdx = dis(gen);
    std::string selectedAttribute = topAttributes[selectedIdx].first;

    // Create the root node for this subtree
    auto root = std::make_shared<DecisionNode>(selectedAttribute);

    // Get unique values of the selected attribute
    auto uniqueValues = getUniqueValues(data, selectedAttribute);

    // For each unique value, create a subtree
    for (const auto& value : uniqueValues) {
        // Split the data
        std::vector<CarInstance> subset;
        for (const auto& instance : data) {
            std::string instanceValue;
            if (selectedAttribute == "buying") instanceValue = instance.buying;
            else if (selectedAttribute == "maint") instanceValue = instance.maint;
            else if (selectedAttribute == "doors") instanceValue = instance.doors;
            else if (selectedAttribute == "persons") instanceValue = instance.persons;
            else if (selectedAttribute == "lug_boot") instanceValue = instance.lug_boot;
            else if (selectedAttribute == "safety") instanceValue = instance.safety;

            if (instanceValue == value) {
                subset.push_back(instance);
            }
        }

        if (subset.empty()) {
            // If subset is empty, attach a leaf node with majority class
            root->children[value] = std::make_shared<DecisionNode>(majorityClass(data), true);
        }
        else {
            // Remove the used attribute for the subtree
            std::vector<std::string> remainingAttributes = attributes;
            remainingAttributes.erase(std::remove(remainingAttributes.begin(), remainingAttributes.end(), selectedAttribute), remainingAttributes.end());

            // Recursively build the subtree
            root->children[value] = buildDecisionTreeRandomTop3(subset, remainingAttributes, criterion);
        }
    }

    return root;
}

// Function to split data into training and testing sets
void trainTestSplit(const std::vector<CarInstance>& data, std::vector<CarInstance>& train, std::vector<CarInstance>& test, double trainRatio = 0.8) {
    std::vector<CarInstance> shuffled = data;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffled.begin(), shuffled.end(), g);

    size_t trainSize = static_cast<size_t>(trainRatio * shuffled.size());
    train.assign(shuffled.begin(), shuffled.begin() + trainSize);
    test.assign(shuffled.begin() + trainSize, shuffled.end());
}

// Function to predict the class label for an instance using the decision tree
std::string predict(const std::shared_ptr<DecisionNode>& node, const CarInstance& instance) {
    if (node->isLeaf()) {
        return node->classLabel;
    }

    std::string attributeValue;
    if (node->attribute == "buying") attributeValue = instance.buying;
    else if (node->attribute == "maint") attributeValue = instance.maint;
    else if (node->attribute == "doors") attributeValue = instance.doors;
    else if (node->attribute == "persons") attributeValue = instance.persons;
    else if (node->attribute == "lug_boot") attributeValue = instance.lug_boot;
    else if (node->attribute == "safety") attributeValue = instance.safety;
    else {
        std::cerr << "Unknown attribute: " << node->attribute << std::endl;
        return "";
    }

    // If the attribute value is not present in the children, return majority class at this node
    if (node->children.find(attributeValue) == node->children.end()) {
        // Optionally, you could implement majority class at each node
        // For simplicity, return a default class (e.g., majority class of training data)
        return "unacc"; // Placeholder
    }

    return predict(node->children[attributeValue], instance);
}

// Function to calculate accuracy of the decision tree on test data
double calculateAccuracy(const std::shared_ptr<DecisionNode>& tree, const std::vector<CarInstance>& testData) {
    int correct = 0;
    for (const auto& instance : testData) {
        std::string predicted = predict(tree, instance);
        if (predicted == instance.classLabel) {
            correct++;
        }
    }
    return (static_cast<double>(correct) / testData.size()) * 100.0;
}

int main() {
    // Load the dataset
    std::vector<CarInstance> dataset = loadData("../car evaluation dataset/car.data");
    std::cout << "Total instances loaded: " << dataset.size() << std::endl;

    // Define attributes
    std::vector<std::string> attributes = {"buying", "maint", "doors", "persons", "lug_boot", "safety"};

    // Define selection criteria
    std::vector<std::string> criteria = {"information_gain", "gini_impurity"};

    // Initialize variables to store cumulative accuracies
    std::unordered_map<std::string, double> cumulativeAccuraciesBest;
    std::unordered_map<std::string, double> cumulativeAccuraciesRandom;
    cumulativeAccuraciesBest["information_gain"] = 0.0;
    cumulativeAccuraciesBest["gini_impurity"] = 0.0;
    cumulativeAccuraciesRandom["information_gain"] = 0.0;
    cumulativeAccuraciesRandom["gini_impurity"] = 0.0;

    int runs = 20;

    for (int i = 0; i < runs; ++i) {
        std::vector<CarInstance> train, test;
        trainTestSplit(dataset, train, test, 0.8);

        for (const auto& criterion : criteria) {
            // Always select the best attribute
            auto treeBest = buildDecisionTree(train, attributes, criterion);
            double accuracyBest = calculateAccuracy(treeBest, test);
            cumulativeAccuraciesBest[criterion] += accuracyBest;

            // Select randomly from top three attributes
            auto treeRandom = buildDecisionTreeRandomTop3(train, attributes, criterion);
            double accuracyRandom = calculateAccuracy(treeRandom, test);
            cumulativeAccuraciesRandom[criterion] += accuracyRandom;
        }
    }

    // Calculate average accuracies
    std::cout << "\nAverage accuracy over " << runs << " runs\n";
    std::cout << "---------------------------------------------------------------\n";
    std::cout << std::left << std::setw(50) << "Attribute selection strategy" 
              << std::setw(20) << "Information gain" 
              << std::setw(20) << "Gini Impurity" << "\n";
    std::cout << "---------------------------------------------------------------\n";

    // Always select the best attribute
    std::cout << std::left << std::setw(50) << "Always select the best attribute";
    for (const auto& criterion : criteria) {
        double average = cumulativeAccuraciesBest[criterion] / runs;
        std::cout << std::fixed << std::setprecision(2) << std::setw(20) << average;
    }
    std::cout << "\n";

    // Select randomly from top three attributes
    std::cout << std::left << std::setw(50) << "Select one randomly from the top three attributes";
    for (const auto& criterion : criteria) {
        double average = cumulativeAccuraciesRandom[criterion] / runs;
        std::cout << std::fixed << std::setprecision(2) << std::setw(20) << average;
    }
    std::cout << "\n";

    std::cout << "---------------------------------------------------------------\n";

    return 0;
}
