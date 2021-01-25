#include "directed_graph.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <array>
#include <deque>
#include <map>
#include <string>

using namespace std;
/*
 * Computes the shortest distance from u to v in graph g.
 * The shortest path corresponds to a sequence of vertices starting from u and ends at v,
 * which has the smallest total weight of edges among all possible paths from u to v.
 */
template <typename T> //Using custom main.cpp, shortest path = 1 0 3 6, Using same code in netbeans 11.1 provides 1 4 4 5 4 4 5 6
vector<vertex<T>> shortest_path(directed_graph<T>& g, int u_id, int v_id) {
   
    vector<vertex<T>> shortest_path;                // Stores ordered vector of path with minimum distance to destination vertex
    vector<vertex<T>> visited;                      // Stores vertices that have been visited
    stack<vertex<T>> reverse_path;                  // Stores vertices which gives reverse path 
    unordered_map<int, pair<int, T>> min_distance;  // Map storing distance from start vertex to vertex ID of key value,
                                                    // map also stores preceding vertex to achieve shortest distance

    min_distance.insert({u_id, {0 ,0}});            // Insert start node with 0 & preceding vertex 0 to min_distance
    for (auto& x : g.get_vertices()){                       
        if (x.id != u_id)min_distance.insert({x.id,{0 ,99999}}); // Initialise the rest of the shortest distances to start node with VERY HIGH VALUE and preceding vertex 0
    }
    
    int start_index = g.index_of(u_id);                               // Retrieve index of start vertex within vector
    vertex<T> current = g.get_vertices().at(start_index);             // Retrieve vector element at starting vertex index
    if (g.reachable(u_id,v_id)){
        while (visited.size() != g.get_vertices().size()) {               // Step 1: While not all vertices are visited
            unordered_map<int, T> n_edge = g.neighbour_edge(current.id);  //         Return map of neighbouring edges and weights of current vertex
            for (auto& x : n_edge) {                                      //         and loop through each edge
                if (min_distance[x.first].second > min_distance[current.id].second+x.second) { // Step 2: Make sure if distance map of neighbour is greater than distance to current vertex + edge weight
                    min_distance[x.first].second = min_distance[current.id].second+x.second;   //         Update distance map to keep smallest distance     
                    min_distance[x.first].first = current.id;                                  //         And store the preceding vertex
                }   
            }           
            visited.push_back(current);    // Add current vertex to visited

            int min_weight = 99999;        // Use high value for loop below    
            for (auto& y : min_distance) {                                           // Step 3: loop through each distance map element 
                if (y.second.second <= min_weight && !g.in_list(y.first,visited) ) { //         comparing distances to unvisited vertice with min_weight variable
                    min_weight = y.second.second;                                    //         setting min_weight to next smallest distance
                    current = g.get_vertices().at(g.index_of(y.first));              //         and the next vertex to visit
                }
            } // At this point, min_distance will be a complete distance map
        }     // from starting vertex to every other vertex in graph
           
        reverse_path = shortest_path_helper(g, v_id, u_id, min_distance, reverse_path); // Step 4: Generate vertice (except first vertex) for reverse_path stack using completed distance map
        reverse_path.push(g.get_vertices().at(g.index_of(u_id)));                       //         Add start vertex to top of stack
        while (!reverse_path.empty()) {                                                 //         Begin adding vertices to shortes_path in order
            if (!g.in_list(reverse_path.top().id, shortest_path)) {                     //         Add vertice from top of reverse_path stack wjile removing duplicates
                shortest_path.push_back(reverse_path.top());
            }
            reverse_path.pop(); // Pop vertex froms stack
        }           
    } else {
        shortest_path.push_back(current); // If destination vertex not reachable then only add star vertex
    }  

    return shortest_path; // Return ordered shortest path
}

template <typename T> //Helper function using preceding vertices in distance map to generate ordered stack starting with destination on bottom
stack<vertex<T>> shortest_path_helper(directed_graph<T>& g, int& v_id, int& u_id, unordered_map<int, pair<int, T>>& min_distance, stack<vertex<T>>& r) {
  
    int next = v_id;      // Store destination ID
    for (auto& x : min_distance) {                               // Step 1: Loop through distance map
        if (x.first == next && next != u_id) {                   //         and look for element with next variable as key
            r.push(g.get_vertices().at(g.index_of(next)));       // Step 2: add corresponding vertex to stack
            next = x.second.first;                               //         set next vertex in distance map to look for as preceding vertex
            shortest_path_helper(g, next, u_id, min_distance, r);// Step 3: recursively repeat process
        }
    }

    return r; // Returns the stack
}

/*
 * Computes the strongly connected components of the graph.
 * A strongly connected component is a subset of the vertices
 * such that for every pair u, v of vertices in the subset,
 * v is reachable from u and u is reachable from v.
 */

template <typename T>
vector<vector<vertex<T>>> strongly_connected_components(directed_graph<T> g) {
  
    unordered_map<int, int> dfn;       // The order in which nodes are searched during depth-first search traversal
    unordered_map<int, int> low;       // Stores lowest dfn value that vertex can reach with unused edge
    int dfn_cnt = 0;
    stack<vertex<T>> s;
    set<int> in_s;                     // a set for checking if a node is in stack s
    vector<vector<vertex<T>>> all_scc; // Vector of storing all SCCs
    
    for (auto& x : g.get_vertices()) {
        if (dfn.count(x.id) == 0) {    // check if x unvisited
            tarjan(x.id, dfn, low, dfn_cnt, s, in_s, all_scc, g); // use tarjan algorithm to find and add SCCs in graph 
        }
    }
    
  return all_scc;
}

template <typename T> // Uses Tarjan's Algorithm as helper function of strongly_connected_compnents
void tarjan(int u, unordered_map<int, int>& dfn, unordered_map<int, int>& low,
            int& dfn_cnt, stack<vertex<T>>& s, set<int>& in_s, 
            vector<vector<vertex<T>>>& all_scc, directed_graph<T>& g) {
    
    low[u] = dfn[u] = ++dfn_cnt;                              // Initialise dfn & low
    s.push(g.get_vertices().at(g.index_of(u)));               // Add u to stack 
    in_s.insert(u);                                           // Mark as visited        
    unordered_map<int, T> neighbour = g.neighbour_edge(u);        
    for (auto& x : neighbour) {                                      // Return and loop through neighbouring edges of u
        if (dfn.count(x.first) == 0) {                               // Case 1: x unvisited
            tarjan(x.first, dfn, low, dfn_cnt, s, in_s, all_scc, g); // Recur for x
            low[u] = min(low[u], low[x.first]);                      // Retrospective
        } else if (in_s.find(x.first) != in_s.end()) {               // Case2: v visited & in stack
            low[u] = min(low[u], dfn[x.first]);                      // Updates low 
        }
    }
    if (dfn[u] == low[u]) {          // If u is root of SCC
        vector<vertex<T>> scc;       // Create an SCC
        while (s.top().id != u) {    // Add all vertices above u in stack
            scc.push_back(s.top());
            in_s.erase(s.top().id);
            s.pop();
        }
        scc.push_back(s.top());      // Add u to stack
        in_s.erase(s.top().id);     
        s.pop();
        all_scc.push_back(scc);      // Add SCC to resulting SCCs in graph
    }
}

/*
 * Computes a topological ordering of the vertices.
 * For every vertex u in the order, and any of its
 * neighbours v, v appears later in the order than u.
 * You will be given a DAG as the argument.
 */
template <typename T> //Uses a Depth-First Topological Sort
vector<vertex<T>> topological_sort(directed_graph<T>& g) { 
 
    vector<vertex<T>> sorted_vertices;             // Stores vertices in topological order
    stack<vertex<T>> s;                            // Stores vertices to process
    vector<vertex<T>> visited;                     // Stores visited vertices
    vector<vertex<T>> vertices = g.get_vertices(); // Stores all vertices in graph
    
    for (auto& x : vertices){           // Step 1: Loop through all graph vertices
        if (!g.in_list(x.id,visited)){  //         Setting unvisited vertices
            vertex<T> v = x;            //         as next vertice to visit,
            visit(v, visited, s, g);    // Step 2: Use helper function to add vertice to stack         
        }
    }
    
    while(!s.empty()){
        sorted_vertices.push_back(s.top()); // Step 3: Add vertices from stack to sorted vertices
        s.pop();                            //         Then pop stack
    }

    return sorted_vertices; // Returns vertices in topological order
}

template <typename T> // Helper function for topological sort which recursively visits vertices
void visit(vertex<T> vert, vector<vertex<T>>& visited, stack<vertex<T>>& s, directed_graph<T> g) {
    
    visited.push_back(vert);  // Mark vertex as visited
    vector<vertex<T>> v_neighbours = g.get_neighbours(vert.id);
    for (auto& x : v_neighbours){      // Loop through neighbours of current vertex
        if(!g.in_list(x.id,visited)){  // And if it is not visited
            visit(x, visited, s, g);   // Perform a recursion
        }
    }
    s.push(vert); // Adds vertex to stack used to produce final result
}
/*
 * Computes the lowest cost-per-person for delivery over the graph.
 * u is the source vertex, which send deliveries to all other vertices.
 * vertices denote cities; vertex weights denote cities' population;
 * edge weights denote the fixed delivery cost between cities, which is irrelevant to 
 * the amount of goods being delivered. 
 */
template <typename T>
T low_cost_delivery(directed_graph<T> g, int u_id) { 
  
    T total_pop;    // Stores total 'population'(weight) of each vertex
    T lowest_cost;  // Stores total 'cost'(weight) of each edge
    unordered_map<int, unordered_map<int, bool>> used_edges;    // Map to check if edge has already been used to prevent duplicate weight addition
    unordered_map<int, T> adj_edges;                            // Map used to store adjacent edges of each vertex in shortest path
    vector<vertex<T>> min_path;                                 // Stores vertices of shortest path to each city from given vertex
    vector<vertex<T>> vertices = g.get_vertices();              // Stores all vertices in graph
    vector<vertex<T>> visited;                                  // Stores visited vertices

    for (auto& x : vertices) {                  // Step 1: For each vertice
        total_pop += x.weight;                  //         Add its 'population' to total_pop  
        min_path = shortest_path(g, u_id, x.id);//         And get the shortest path to it from starting vertex
        for (auto& y : min_path) {              // Step 2: For each vertice in shortest path
            adj_edges = g.neighbour_edge(y.id); //         Get its adjacent edges
            for (auto& z : adj_edges) {                                               // Step 3: For each edge
                if (                                                                  //         Ensure that it connects the vertices for the shortest path,
                    used_edges[y.id][z.first] == false && !g.in_list(z.first,visited) //         It's weight hasn't already been added to lowest_cost total,
                    && g.in_list(z.first,min_path) && z.first!= u_id && y.id!=x.id    //         And it doesn't connect to either the starting,  
                    ) {                                                               //         or a previously visited shortest path vertex
                    used_edges[y.id][z.first] == true;                                // Step 4: Set an edge as used (it's weight is in the total),
                    visited.push_back(g.get_vertices().at(g.index_of(z.first)));      //         Add connected vertices to visited vector 
                    lowest_cost += z.second;                                          //         Add the connecting edge's weight to total
                }
            }
        }
    }

    T avg_cpp = lowest_cost/total_pop; // Step 5: Calculate average 'delivery' cost per 'person'
  
    return avg_cpp;
}
