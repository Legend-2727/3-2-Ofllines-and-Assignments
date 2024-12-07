#include<bits/stdc++.h>
// #include<sstream>
// #include "../../dbg.h"
#include "decision_tree.cpp"
using namespace std;

random_device rd2;
mt19937 g(rd2());
void printAll(vector<Car> &cars){
    for(auto c : cars){
        c.printDetails();
    }
}
void readFromFile(vector<Car> &cars,string &filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Error: unable to open file " << filename << endl;
        exit(1);
    }
    string line;
    while(getline(file,line)){
        if(line.empty())
            continue;
        string buy,maint,doors,persons,lug_boot,safety,accpetancy;
        stringstream ss(line);
        getline(ss,buy,',');
        getline(ss,maint,',');
        getline(ss,doors,',');
        getline(ss,persons,',');
        getline(ss,lug_boot,',');
        getline(ss,safety,',');
        getline(ss,accpetancy);
        
        Car newCar(buy,maint,doors,persons,lug_boot,safety,accpetancy);
        cars.emplace_back(newCar);
        // newCar.printDetails();
    }
    file.close();
}
void trainTestSplit(vector<Car> &cars,vector<Car>& train,
                        vector<Car>& test, double trainRatio = 0.8) {
    // vector<Car> cars = data;
    // random_device rd;
    // mt19937 g(rd());
    shuffle(cars.begin(), cars.end(),g);

    size_t trainSize = static_cast<size_t>(trainRatio * cars.size());
    train.assign(cars.begin(), cars.begin() + trainSize);
    test.assign(cars.begin() + trainSize, cars.end());
}
int main() {
    vector<Car> cars;
    string filname = "../car evaluation dataset/car.data";
    readFromFile(cars,filname);
    cout << "Total instances loaded: " << cars.size() << endl;

    vector<string> criteria = {
            "information_gain",
            "gini_impurity"
        };

    unordered_map<string, double> cumulativeAccuraciesBest;
    unordered_map<string, double> cumulativeAccuraciesRandom;
    cumulativeAccuraciesBest["information_gain"] = 0.0;
    cumulativeAccuraciesBest["gini_impurity"] = 0.0;
    cumulativeAccuraciesRandom["information_gain"] = 0.0;
    cumulativeAccuraciesRandom["gini_impurity"] = 0.0;

    vector<string> attributes;
    for(auto m : cars[0].attributes){
        if(m.first!="acceptancy"){
            attributes.push_back(m.first);
        }
    }
    // dbg(attributes);

    int runs = 20;

    for (int i = 0; i < runs; ++i) {
        vector<Car> train, test;
        trainTestSplit(cars, train, test, 0.8);
        // dbg(train.size(),test.size(),cars.size());
        // printAll(cars);
        // cout<<test.size()<<endl;
        // printAll(test);

        // cout<<train.size()<<"train\n\n\n\n\n";
        // printAll(train);
        for (const auto& criterion : criteria) {
            // dbg(attributes.size());
            auto treeBest = buildDecisionTree(train, attributes, criterion);
            // dbg("hello");
            double accuracyBest = calculateAccuracy(treeBest, test);
            cumulativeAccuraciesBest[criterion] += accuracyBest;

            auto treeRandom = buildDecisionTree(train, attributes, criterion,3);
            double accuracyRandom = calculateAccuracy(treeRandom, test);
            cumulativeAccuraciesRandom[criterion] += accuracyRandom;
        }
    }

    cout << "\nAverage accuracy over " << runs << " runs\n";
    cout << "---------------------------------------------------------------------------------\n";
    cout << left << setw(50) << "Attribute selection strategy" 
            << setw(20) << "Information gain" 
            << "Gini impurity" << "\n";
    cout << "---------------------------------------------------------------------------------\n";

    // Always select the best attribute
    cout << left << setw(55) << "Always select the best attribute";
    for (const auto& criterion : criteria) {
        double average = cumulativeAccuraciesBest[criterion] / runs;
        cout << fixed << setprecision(2) << setw(20) << average;
    }
    cout << "\n";

    // Select randomly from top three attributes
    cout << left << setw(55) << "Select one randomly from the top three attributes";
    for (const auto& criterion : criteria) {
        double average = cumulativeAccuraciesRandom[criterion] / runs;
        cout << fixed << setprecision(2) << setw(20) << average;
    }
    cout << "\n";

    cout << "----------------------------------------------------------------------------------\n";

    return 0;
}
