#include<bits/stdc++.h>
#include "Car.cpp"
// #include "../../dbg.h" 
using namespace std;

random_device rd;
mt19937 gen(rd());
class DecisionNode{
    public:
    string selectAttribute;
    bool isLeaf;
    unordered_map<string,DecisionNode*> children;
    string max_class_value;
    unordered_map<string,int> class_value_count;

    DecisionNode(string attribute,bool leaf){
        selectAttribute = attribute;
        isLeaf = leaf;
        max_class_value="";
    }
    string get_random_class() const {
        if(class_value_count.empty()){
            return "";
        }

        int total = 0;
        for(auto &pair : class_value_count){
            total += pair.second;
        }

        if(total == 0){
            return "";
        }

        // Use a static generator with a fixed seed for reproducibility
        static mt19937 g3(42); // Fixed seed
        uniform_int_distribution<> dis(1, total);
        int rand_num = dis(g3);

        int cumulative = 0;
        for(auto &pair : class_value_count){
            cumulative += pair.second;
            if(rand_num <= cumulative){
                return pair.first;
            }
        }

        return "";
    }
    string get_max_class_value(){
        if(class_value_count.size()==1)
            return max_class_value;
        string temp = get_random_class();
        if(temp!=""){
            max_class_value=temp;
        }
        return max_class_value;
    }
};

unordered_map<string,int> get_class_value_count(vector<Car> &cars){
    unordered_map<string,int> class_value_count;
    for (auto &car : cars) {
        class_value_count[car.attributes["acceptancy"]]++;
    }
    return class_value_count;
}

double getEntropy(vector<Car> &cars){
    double entropy = 0.0;
    int total = cars.size();
    unordered_map<string,int> class_value_count=get_class_value_count(cars);
    for(auto &cv : class_value_count){
        double p = (double)cv.second/total;
        entropy += -p*log2(p);
    }
    return entropy;
}

double get_info_gain(vector<Car> &cars,string attribute,double totalEntropy){
    
    unordered_map<string,vector<Car>> car_subset;
    for (auto& car : cars) {
        std::string value;
        value=car.attributes[attribute];
        car_subset[value].push_back(car);
    }  
    double weighted_entropy=0.0;
    for(auto &cv : car_subset){
        double p = (double)cv.second.size()/cars.size();
        double subset_entropy = getEntropy(cv.second);
        weighted_entropy += p*subset_entropy;
    }
    return totalEntropy - weighted_entropy;
}

double calculate_gini(vector<Car> &cars){
    auto classCounts = get_class_value_count(cars);
    double gini = 1.0;
    int total = cars.size();
    for (auto& pair : classCounts) {
        double p = (double)(pair.second) / total;
        gini -= p * p;
    }
    return gini;
}
double get_gini_gain(vector<Car> &cars,string attribute,double totalGini){
    unordered_map<string,vector<Car>> car_subset;
    for (auto& car : cars) {
        std::string value;
        value=car.attributes[attribute];
        car_subset[value].push_back(car);
    }  
    double weighted_gini=0.0;
    for(auto &cv : car_subset){
        double p = (double)cv.second.size()/cars.size();
        double subset_gini = calculate_gini(cv.second);
        weighted_gini += p*subset_gini;
    }
    return totalGini - weighted_gini;
}

string selectTopBestAttribute(vector<Car> &cars,string criteria,vector<string> &attributes,int top){
    top--;
    set<pair<double,string>> topAttributes;
    // string best_attribute;
    for (auto &attribute : attributes) {
        if(attribute != "acceptancy"){
            if(criteria == "information_gain")
                topAttributes.insert({get_info_gain(cars, attribute, 
                    getEntropy(cars)),attribute});
            else if (criteria == "gini_impurity")
                topAttributes.insert({get_gini_gain(cars, attribute, 
                    calculate_gini(cars)),attribute});
            else{
                cout<<"Invalid criteria"<<endl;
                exit(1);
            }
        }
    }
    int range = min(top,(int)topAttributes.size()-1);
    uniform_int_distribution<> dis(0, range);
    int selectedIdx = dis(gen);
    // dbg(selectedIdx);
    auto it = topAttributes.rbegin();
    advance(it, selectedIdx);

    string selectedAttribute = it->second;
    // dbg(topAttributes,selectedAttribute);
    return selectedAttribute;
}

string get_max_acceptancy(unordered_map<string,int> &class_values){
    int max_acceptancy = 0;
    string max_attr;
    for(auto &cv:class_values){
        int acceptancy = cv.second;
        if(acceptancy > max_acceptancy){
            max_acceptancy = acceptancy;
            max_attr = cv.first;
        }
    }
    return max_attr;
}

vector<string> get_unique_valuesOfAttribute(vector<Car> & cars,string attribute){
    vector<string> unique_values;
    unordered_map<string,bool> checked;
    for(auto &c : cars){
        if(!checked[c.attributes[attribute]]){
            unique_values.push_back(c.attributes[attribute]);
            checked[c.attributes[attribute]]=true;
        }
    }
    return unique_values;
}

DecisionNode* buildDecisionTree(vector<Car> &cars, vector<string> &attributes,string criteria,int top=1){
    if(cars.empty()){
        DecisionNode* leaf = new DecisionNode("", true);
        leaf->max_class_value = "unacc"; 
        return leaf;
    }
    auto class_values = get_class_value_count(cars);
    // dbg("here");
    // dbg(attributes);
    // dbg(class_values);
    if(class_values.size()==1){
        DecisionNode* leaf = new DecisionNode("",1);
        leaf->class_value_count = class_values;
        leaf->max_class_value=class_values.begin()->first;
        // dbg(leaf->max_class_value);
        return leaf;
    }
    if(attributes.size()==1){
        DecisionNode* leaf = new DecisionNode("",1);
        leaf->max_class_value=get_max_acceptancy(class_values);
        leaf->class_value_count=class_values;
        // dbg(leaf->max_class_value);
        return leaf;
    }
    string top_attribute = selectTopBestAttribute(cars,criteria,attributes,top);

    DecisionNode *root = new DecisionNode(top_attribute,0);
    vector<string> unique_values=get_unique_valuesOfAttribute(cars,top_attribute);
    vector<string> reducedAttributes = attributes;
    // dbg(reducedAttributes);
    reducedAttributes.erase(remove(reducedAttributes.begin(),reducedAttributes.end(),top_attribute),reducedAttributes.end());
    // dbg(reducedAttributes);
    for(auto uv : unique_values){
        vector<Car> subset_cars;
        for(auto &c : cars){
            if(c.attributes[top_attribute]==uv){
                subset_cars.push_back(c);
            }
        }
        DecisionNode *node = buildDecisionTree(subset_cars,reducedAttributes,criteria,top);
        root->children[uv]=node;
    }
    return root;
}

string predict(DecisionNode *node, Car car){
    if(node->isLeaf){
        return node->get_max_class_value();
        // return node->max_class_value;
    }
    string attrValue = car.attributes[node->selectAttribute];
    auto it = node->children.find(attrValue);
    if(it != node->children.end()){
        return predict(it->second, car);
    }
    else{
        return node->max_class_value;
    }
}


double calculateAccuracy(DecisionNode *root,vector<Car> &testCars){
    int correct = 0 ;
    for(auto &c : testCars){
        string prediction = predict(root,c);
        if(prediction==c.attributes["acceptancy"]){
            correct++;
        }
    }
    // dbg(correct);
    double accuracy = ((double) correct/testCars.size())*100;
    return accuracy;
}
