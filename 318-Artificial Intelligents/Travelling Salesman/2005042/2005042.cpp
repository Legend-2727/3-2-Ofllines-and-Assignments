#include<bits/stdtr1c++.h>

// #include "../..///dbg.h"

using namespace std;
using namespace std::chrono;

struct City {
    // public:
    // int id;
    double x;
    double y;
};
// vector<City> cities;

vector<City> readTspFile(const string& f) {
    vector<City> c;
    ifstream file(f);
    string line;
    bool coord_section = false;
    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << f << endl;
        return c;
    }
    // //dbg("here");
    while (getline(file, line)) {
        // cout<<line<<endl;
        if (line.find("DIMENSION: ") != string::npos || line.find("DIMENSION : ") != string::npos) {
            int n = stoi(line.substr(line.find(": ") + 1));
            // //dbg(n);

            c.resize(n);
        }
        if (line.find("NODE_COORD_SECTION") != string::npos) {
            coord_section = true;
            continue;
        }
        if (line == "EOF") break;

        if (coord_section) {
            stringstream ss(line);
            int id;
            double x, y;
            ss >> id >> x >> y;

            c[id - 1].x = x;
            c[id - 1].y = y;
            // //dbg(id,x,y);
        }
    }
    file.close();
    return c;
}

double distance(City c1, City c2) {
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

void printCities(vector<City>& cities) {
    // cout<<"here\n\n\n\n\n\n";
    for (int i = 0;i < cities.size();i++) {
        cout << i << " " << cities[i].x << " " << cities[i].y << endl;
    }
}
void printRoute(const list<int>& route, vector<City>& cities) {
    double dist = 0;
    int first = -2, next = -1;
    cout << "Route: ";
    for (auto itr = route.begin(); itr != route.end(); ++itr) {
        cout << *(itr)+1 << " ";
        first = next;
        next = *itr;
        if (first >= 0) {
            // //dbg(first,next);
            dist += distance(cities[first], cities[next]);
        }

    }
    cout << endl;
    cout << "Total Distance : " << dist << endl;
}
void printRoute2(const vector<int>& route, vector<City>& cities) {
    double dist = 0;
    int first = -2, next = -1;
    cout << "Route: ";
    for (auto it : route) {
        cout << it+1 << " ";
        first = next;
        next = it;
        if (first >= 0) {
            // //dbg(first,next);
            dist += distance(cities[first], cities[next]);
        }

    }
    cout << endl;
    cout << "Total Distance : " << dist << endl;
}
double init_distance1(list<int>& tour,vector<City> &cities) {
    double dist = 0;
    int first = -2, next = -1;
    for (auto itr = tour.begin(); itr != tour.end(); ++itr) {
        first = next;
        next = *itr;
        if (first >= 0) {
            // //dbg(first,next);
            dist += distance(cities[first], cities[next]);
        }

    }
    return dist;
}
class ConstructiveMethods {
public:
    vector<City> cities;
    ConstructiveMethods(vector<City>& c) {
        cities = c;
    }

    list<int> cheapestInsertion(int k = 3) {
        list<int> route;
        // int current_dist=0;
        int n = cities.size();
        if (n == 0) {
            cout << "no cities\n";
            return route;
        }
        route.push_back(0);
        if (n == 1) {
            return route;
        }
        route.push_back(1);
        route.push_back(0);

        // if(n==2){
        //     return route;
        // }
        // srand(time(0));
        // int k =3;
        vector<bool> visited(n, 0);
        visited[0] = 1;
        visited[1] = 1;
        set<pair<double, pair<int, int>>> cheap_position;

        while (route.size() != (n + 1)) {
            // int minDist = INT_MAX;
            // int minIndex = -1;
            auto best_position = route.begin();
            for (int i = 0;i < n;i++) {
                if (!visited[i]) {
                    int index = 0;
                    for (auto itr = route.begin();next(itr) != route.end();++itr) {
                        int dist = distance(cities[*itr], cities[i]) +
                            distance(cities[i], cities[*next(itr)]) -
                            distance(cities[*itr], cities[*next(itr)]);
                        cheap_position.insert({ dist,{index,i} });
                        index++;
                    }
                }
            }

            k = min(k, (int)cheap_position.size());
            int random_index = rand() % k;
            auto it = cheap_position.begin();
            advance(it, random_index);
            int minIndex = it->second.second;
            int index = it->second.first;
            // auto best_position = route.begin();
            advance(best_position, index);
            route.insert(next(best_position), minIndex);
            // //dbg(route);
            visited[minIndex] = 1;
            cheap_position.clear();
        }
        return route;
    }

    list<int> NearestNeighbourHeuristic(int k = 3) {
        list<int> route;
        int n = cities.size();
        if (n == 0) {
            cout << "no cities\n";
            return route;
        }
        route.push_back(0);
        if (n == 1) {
            return route;
        }
        vector<bool> visited(n, 0);
        visited[0] = 1;
        // int k = 3;
        set<pair<double, int>> nearest_k;
        // srand(time(0));
        while (route.size() != (n)) {
            int last_city = route.back();
            for (int i = 0; i < n;i++) {
                if (!visited[i]) {
                    double dist = distance(cities[last_city], cities[i]);
                    nearest_k.insert(make_pair(dist, i));
                }
            }

            k = min(k, int(nearest_k.size()));
            int random_index = rand() % k;
            auto it = nearest_k.begin();
            advance(it, random_index);
            int next_city = it->second;
            // //dbg(next_city);
            route.push_back(next_city);
            // //dbg(route,nearest_k);
            nearest_k.clear();
            visited[next_city] = 1;
        }
        route.push_back(0);
        return route;
    }
    int find(int city, vector<int>& parent) {
        if (parent[city] != city)
            parent[city] = find(parent[city], parent);
        return parent[city];
    };
    bool form_cycle(int city1, int city2, vector<int>& parent) {
        int root1 = find(city1, parent);
        int root2 = find(city2, parent);
        if (root1 == root2)
            return true;
        parent[root1] = root2;
        return false;
    }
    list<int> GreedyHeuristic() {
        list<int> route;
        int n = cities.size();
        if (n == 0) {
            cout << "no cities\n";
            return route;
        }
        // route.push_back(0);
        if (n == 1) {
            return route;
        }
        set<pair<double, pair<int, int>>> sorted_edges;
        for (int i = 0;i < n - 1;i++) {
            for (int j = i + 1;j < n;j++) {
                double dist = distance(cities[i], cities[j]);
                sorted_edges.insert({ dist,{i,j} });
            }
        }
        vector<int> degree(n, 0);
        vector<int> parent(n);
        vector<vector<int>> tour(n);
        for (int i = 0;i < n;i++) {
            parent[i] = i;
        }
        int edge_count = 0;
        // //dbg(sorted_edges);
        for (auto it : sorted_edges) {
            int city1 = it.second.first;
            int city2 = it.second.second;
            if (degree[city1] < 2 && degree[city2] < 2 && !form_cycle(city1, city2, parent)) {
                // //dbg(city1, city2);
                tour[city1].push_back(city2);
                tour[city2].push_back(city1);
                degree[city1]++;
                degree[city2]++;
                edge_count++;
            }
            if (edge_count == n - 1) {
                vector<int> last_edge;
                for (int i = 0;i < n;i++) {
                    if (degree[i] == 1) {
                        last_edge.push_back(i);
                    }
                    if (last_edge.size() == 2) {
                        break;
                    }
                }
                // //dbg(last_edge);
                tour[last_edge[0]].push_back(last_edge[1]);
                tour[last_edge[1]].push_back(last_edge[0]);
                break;
            }
        }
        vector<int> visited(n, 0);
        int current_city = 0;
        while (route.size() < n) {
            route.push_back(current_city);
            visited[current_city] = 1;
            for (auto neighbour : tour[current_city]) {
                if (!visited[neighbour]) {
                    current_city = neighbour;
                    break;
                }
            }
        }
        route.push_back(0);
        return route;
    }
};

class PerturbativeMethods {
public:
    vector<City> cities;
    int size;
    PerturbativeMethods(vector<City>& c) {
        cities = c;
        size = c.size();
    }

    vector<vector<int>> find_neighbors(double radius) {
        int n = cities.size();
        vector<vector<int>> neighbors(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && distance(cities[i], cities[j]) <= radius) {
                    neighbors[i].push_back(j);
                }
            }
        }
        return neighbors;
    }
    vector<int> two_opt(list<int> &route,double radius=0) {
        // list<int> route;
        vector<int> initial_tour;
        int n = route.size();
        
        for (auto it : route) {
            initial_tour.push_back(it);
        }
        //dbg(initial_tour);
        // initial_tour.push_back(0);
        if (n == 0) {
            cout << "no cities\n";
            return initial_tour;
        }
        if (n == 1) {
            return initial_tour;
        }
        bool improved = true;
        double best_distance = tour_distance(initial_tour);
        while (improved) {
            improved = false;
            for (int i = 1;i < n-2;i++) {
                
                for (int j = i + 1;j < n-1;j++) {
                    
                    // if (radius != 0 && find(neighbours[c1].begin(), neighbours[c1].end(), c3) == neighbours[c1].end())
                    //     continue;
                    vector<int> new_tour = initial_tour;
                    reverse(new_tour.begin()+i,new_tour.begin()+j+1);
                    double new_dist = tour_distance(new_tour);
                    if(new_dist<best_distance){
                    // if (distance(cities[c1], cities[c3]) + distance(cities[c2], cities[c4])
                    //     < distance(cities[c1], cities[c2]) + distance(cities[c3], cities[c4])) {
                        improved = true;
                        // reverse(initial_tour.begin() + i + 1, initial_tour.begin() + j);
                        initial_tour = new_tour;
                        best_distance = new_dist;
                        // break;
                    }
                }
                // if(improved) break;
            }
        }
        // for (int i = 0;i <= n;i++) {
        //     route.push_back(initial_tour[i]);
        // }
        return initial_tour;
        // return route;
    }
    double tour_distance(vector<int>& tour) {
        double total_distance = 0;
        int n = tour.size();
        for (int i = 0; i < n - 1; i++) {
            total_distance += distance(cities[tour[i]], cities[tour[(i + 1)]]);
        }
        return total_distance;
    }
    
    vector<int> node_shift(list<int> &route) {
        vector<int> initial_tour;
        int n = route.size();
        for (auto it : route) {
            initial_tour.push_back(it);
        }
        //dbg(initial_tour);
        // initial_tour.push_back(0);
        if (n == 0) {
            cout << "no cities\n";
            return initial_tour;
        }
        if (n == 1) {
            return initial_tour;
        }

        bool improved = true;
        while (improved) {
            improved = false;
            for (int i = 1;i < n-1;i++) {
                for (int j = 1;j < n-1;j++) {
                    if (i == j)
                        continue;
                    int c = initial_tour[i];
                    // int c_prev = initial_tour[i - 1];
                    // int c_next = initial_tour[(i + 1) % n];
                    // int c_prev_new = initial_tour[j];
                    // int c_next_new = initial_tour[(j + 1) % n];
                    // double current_dist;
                    // double new_dist;
                    // if(j== i +1 ){
                    //     current_dist = distance(cities[c_prev], cities[c]) +
                    //                 distance(cities[c_prev_new], cities[c_next_new]);
                    //     new_dist = distance(cities[c_prev], cities[c_prev_new]) +
                    //             distance(cities[c], cities[c_next_new]);
                    // }
                    // else if(j == i - 1 ){
                    //     current_dist = distance(cities[c_prev], cities[c]) +
                    //         distance(cities[c_prev_new], cities[c_next_new]);
                    //     new_dist = distance(cities[c_prev], cities[c_next]) +
                    //         distance(cities[c_prev_new], cities[c]);
                    // }
                    vector<int> new_tour = initial_tour;
                    // else{
                    //     current_dist = distance(cities[c_prev], cities[c]) +
                    //                     distance(cities[c], cities[c_next]) +
                    //                     distance(cities[c_prev_new], cities[c_next_new]);
                    //     new_dist = distance(cities[c_prev], cities[c_next]) +
                    //                 distance(cities[c_prev_new], cities[c]) +
                    //                 distance(cities[c], cities[c_next_new]);
                    // }
                    new_tour.erase(new_tour.begin() + i);
                    new_tour.insert(new_tour.begin() + j, c);
                    // if (new_dist < current_dist) {
                    if(tour_distance(new_tour)<tour_distance(initial_tour)){
                        improved = true;
                        // initial_tour.erase(initial_tour.begin() + i);
                        // //dbg(initial_tour);
                        // initial_tour.insert(initial_tour.begin() + j, c);
                        initial_tour = new_tour;
                        // //dbg(c_prev,c,c_next,c_prev_new,c_next_new);
                        // //dbg(initial_tour);
                        // //dbg(tour_distance(initial_tour));
                    }
                }
            }
            // //dbg("here");
        }
        return initial_tour;
    }
    vector<int> node_swap(list<int> &route){
       vector<int> initial_tour;
        int n = route.size();
        for (auto it : route) {
            initial_tour.push_back(it);
        }
        //dbg(initial_tour);
        // initial_tour.push_back(0);
        if (n == 0) {
            cout << "no cities\n";
            return initial_tour;
        }
        if (n == 1) {
            return initial_tour;
        }
        bool improved = true;
        while (improved) {
            improved = false;
            for (int i = 1;i < n-1;i++) {
                for (int j = 1;j < n-1;j++) {
                    if (i == j)
                        continue;
                    // int c = initial_tour[i];
                    vector<int> new_tour = initial_tour;
                    
                    int temp = new_tour[i];
                    new_tour[i] = new_tour[j];
                    new_tour[j] = temp;

                    if(tour_distance(new_tour)<tour_distance(initial_tour)){
                        improved = true;
                        initial_tour = new_tour;
                    }
                }
            }
            // //dbg("here");
        }
        return initial_tour;
    }
    void runPerturbative(list<int> &route, string method_name, long long method_time, int method_cost, ostream &output) {
        vector<int> route2;

        // 2-opt
        auto start = high_resolution_clock::now();
        route2 = two_opt(route);
        auto end = high_resolution_clock::now();
        long long time_2opt = method_time + duration_cast<milliseconds>(end - start).count();
        int cost_2opt = tour_distance(route2);

        // Node Shift
        start = high_resolution_clock::now();
        route2 = node_shift(route);
        end = high_resolution_clock::now();
        long long time_node_shift = method_time + duration_cast<milliseconds>(end - start).count();
        int cost_node_shift = tour_distance(route2);

        // Node Swap
        start = high_resolution_clock::now();
        route2 = node_swap(route);
        end = high_resolution_clock::now();
        long long time_node_swap = method_time + duration_cast<milliseconds>(end - start).count();
        int cost_node_swap = tour_distance(route2);

        // Write results to the CSV output
        output << method_name << "," << method_time << "," << method_cost << ","
            << time_2opt << "," << cost_2opt << ","
            << time_node_shift << "," << cost_node_shift << ","
            << time_node_swap << "," << cost_node_swap << "\n";
}
};

int main() {
    freopen("../output.csv", "w", stdout);

    vector<string> filePaths = {
        "temp.tsp","berlin52.tsp", "bier127.tsp", "ch130.tsp", "eil51.tsp", "eil76.tsp",
        "eil101.tsp", "kroA100.tsp", "kroB100.tsp", "kroC100.tsp", "kroD100.tsp",
        "kroE100.tsp", "lin105.tsp", "pr76.tsp", "pr124.tsp", "pr144.tsp", 
        "rat99.tsp", "st70.tsp", "lin318.tsp", "a280.tsp", "ch150.tsp", "rat195.tsp"
    };
    vector<string> updatedFilePaths;

    for (const auto& file : filePaths) {
        updatedFilePaths.push_back("../tsp_files/" + file);
    }

    // Write the header to the CSV file
    cout << "File,Method,Method_Time (ms),Method_Cost,"
            "Method + 2-opt Time (ms),Method + 2-opt Cost,"
            "Method + Node Shift Time (ms),Method + Node Shift Cost,"
            "Method + Node Swap Time (ms),Method + Node Swap Cost\n";

    for (const auto& filename : updatedFilePaths) {
        vector<City> cities = readTspFile(filename); // Load the TSP file
        srand(time(0));

        ConstructiveMethods cnMethod(cities);
        PerturbativeMethods prtMethod(cities);

        // Process Cheapest Insertion
        auto start = high_resolution_clock::now();
        list<int> route = cnMethod.cheapestInsertion(1);
        auto end = high_resolution_clock::now();
        long long time_cheapest = duration_cast<milliseconds>(end - start).count();
        int cost_cheapest = init_distance1(route, cities);
        cout << filename << ",";
        prtMethod.runPerturbative(route, "Cheapest Insertion",  time_cheapest, cost_cheapest, cout);

        // Process Nearest Neighbour Heuristic
        start = high_resolution_clock::now();
        route = cnMethod.NearestNeighbourHeuristic(1);
        end = high_resolution_clock::now();
        long long time_nearest = duration_cast<milliseconds>(end - start).count();
        int cost_nearest = init_distance1(route, cities);
        cout << filename << ",";
        prtMethod.runPerturbative(route, "Nearest Neighbour Heuristic",  time_nearest, cost_nearest, cout);

        // Process Greedy Heuristic
        start = high_resolution_clock::now();
        route = cnMethod.GreedyHeuristic();
        end = high_resolution_clock::now();
        long long time_greedy = duration_cast<milliseconds>(end - start).count();
        int cost_greedy = init_distance1(route, cities);
        cout << filename << ",";
        prtMethod.runPerturbative(route, "Greedy Heuristic",  time_greedy, cost_greedy, cout);

        cout << "\n"; // Separate results for each file
    }

    return 0;
}