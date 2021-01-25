#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <map>
#include <cstddef>
#include <string>
#include <utility>
#include <algorithm>
#include <limits>
#include <exception>
#include <stdexcept>


// include more libraries here if you need to

using namespace std; // the standard namespace are here just in case.

/*
	the vertex class
*/
template <typename T>
class vertex {

public:
    int id;
    T weight;

    vertex(int v_id, T v_weight) : id(v_id), weight(v_weight) {}

};


/*
	the graph class
*/
template <typename T>
class directed_graph {

private:

    //Data structures used for graph
    unordered_map<int, T> vertice_list; //Elements contain VERTEX ID and WEIGHT
    unordered_map<int, unordered_map<int, T>> edges_list;//Elements contain edge's  SRC ID, (DST ID, EDGE WEIGHT)
 
public:
        
        typedef typename std::unordered_map<int, T>::iterator v_it;  
        typedef typename std::unordered_map<int, unordered_map<int, T>>::iterator e_it;  
        
        v_it v_begin(){
            return vertice_list.begin();
        }
        v_it v_end(){
            return vertice_list.end();
        }
        e_it n_begin(int& u_id){
            return edges_list.at(u_id).begin();
        }
        e_it n_end(int& u_id){
            return edges_list.at(u_id).end();
        }
                
        directed_graph(); //A constructor for directed_graph. The graph should start empty.
	~directed_graph(); //A destructor. Depending on how you do things, this may not be necessary.
        
        unordered_map<int, T> neighbour_edge(int); // Return directed edges leading out of vertex to anotherm with the edge weight
        
        int index_of(int); //Return index of vector element given vertex id
        
	bool contains(const int&); //Returns true if the graph contains the given vertex_id, false otherwise.
	bool adjacent(const int&, const int&); //Returns true if the first vertex is adjacent to the second, false otherwise.

	void add_vertex(const vertex<T>&); //Adds the passed in vertex to the graph (with no edges).
	void add_edge(const int&, const int&, const T&); //Adds a weighted edge from the first vertex to the second.

	void remove_vertex(const int&); //Removes the given vertex. Should also clear any incident edges.
	void remove_edge(const int&, const int&); //Removes the edge between the two vertices, if it exists.

	size_t in_degree(const int&); //Returns number of edges coming in to a vertex.
	size_t out_degree(const int&); //Returns the number of edges leaving a vertex.
	size_t degree(const int&); //Returns the degree of the vertex (both in edges and out edges).

	size_t num_vertices(); //Returns the total number of vertices in the graph.
	size_t num_edges(); //Returns the total number of edges in the graph.

	vector<vertex<T>> get_vertices(); //Returns a vector containing all the vertices.
	vector<vertex<T>> get_neighbours(const int&); //Returns a vector containing all the vertices reachable from the given vertex. The vertex is not considered a neighbour of itself.
	vector<vertex<T>> get_second_order_neighbours(const int&); // Returns a vector containing all the second_order_neighbours (i.e., neighbours of neighbours) of the given vertex.
															  // A vector cannot be considered a second_order_neighbor of itself.
	bool reachable(int, int); //Returns true if the second vertex is reachable from the first (can you follow a path of out-edges to get from the first to the second?). Returns false otherwise.
	bool contain_cycles(); // Return true if the graph contains cycles (there is a path from any vertices directly/indirectly to itself), false otherwise.

	vector<vertex<T>> depth_first(int); //Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex.
	vector<vertex<T>> breadth_first(const int&); //Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex.

	directed_graph<T> out_tree(int); //Returns a spanning tree of the graph starting at the given vertex using the out-edges. This means every vertex in the tree is reachable from the root.

	vector<vertex<T>> pre_order_traversal(const int&, directed_graph<T>&); // returns the vertices in the visiting order of a pre-order traversal of the minimum spanning tree starting at the given vertex.
	vector<vertex<T>> in_order_traversal(const int&, directed_graph<T>&); // returns the vertices in the visiting order of an in-order traversal of the minimum spanning tree starting at the given vertex.
	vector<vertex<T>> post_order_traversal(const int&, directed_graph<T>&); // returns the vertices in ther visitig order of a post-order traversal of the minimum spanning tree starting at the given vertex.

	vector<vertex<T>> significance_sorting(); // Return a vector containing a sorted list of the vertices in descending order of their significance (using individual vector weights).
        bool in_list(const int&, vector<vertex<T>>&); //Returns boolean on whether a vertex is in a vector given it's ID
        
};

// Define all your methods down here (or move them up into the header, but be careful you don't double up). If you want to move this into another file, you can, but you should #include the file here.
// Although these are just the same names copied from above, you may find a few more clues in the full method headers.
// Note also that C++ is sensitive to the order you declare and define things in - you have to have it available before you use it.


template <typename T>
directed_graph<T>::directed_graph() {
    
}

template <typename T>
directed_graph<T>::~directed_graph() {
}

template <typename T>
unordered_map<int, T> directed_graph<T>::neighbour_edge(int u_id) {
    return edges_list[u_id];
}

template <typename T>
int directed_graph<T>::index_of(int u_id) {
    int index = 0;
    for (auto& z : get_vertices()) {
        if (z.id == u_id) break;
        index++;
    }
    return index;
}

template <typename T>
bool directed_graph<T>::contains(const int& u_id) { 

	if(vertice_list.find(u_id) != vertice_list.end()){ // u_id is found in vertex_weights's keys
		return true; 
	}
        
	return false;

}

template <typename T>
bool directed_graph<T>::in_list(const int& new_id, vector<vertex<T>>& v_list) {
    
    for (auto& x : v_list) {    //loops through all elements of vector and checks if entered id
        if (new_id == x.id){    //matches any vertex id in vector
            return true;
        }
    }
    
    return false;
} 


template <typename T>
bool directed_graph<T>::adjacent(const int& u_id, const int& v_id) { //checks if vertex has an edge leading
    if (contains(u_id) && contains(v_id)){                           //to the neighbour
	for (auto& x : edges_list[u_id]) {
            if (x.first == v_id) {
                return true;
            }
	}
    }
    
    return false;
}

template <typename T>
void directed_graph<T>::add_vertex(const vertex<T>& u) {

    if(!contains(u.id)){
        vertice_list.insert({u.id, u.weight});      // step 1: add the new vertex to vertice_list
        edges_list[u.id] = unordered_map<int, T>(); // step 2: add an entry for this vertex in adj_list but add no edge
    }    
        
}

template <typename T>
void directed_graph<T>::add_edge(const int& u_id, const int& v_id, const T& e_weight) {

	if(contains(u_id) && contains(v_id)){                        // Step 1: make sure both vertices are in the graph
	    if(edges_list[u_id].find(v_id)==edges_list[u_id].end()){ // Step 2: make sure the edge is not already in the graph
                edges_list[u_id].insert({v_id, e_weight});           // Step 3: add this edge to adj_list
	    }
	}

}

template <typename T>
void directed_graph<T>::remove_vertex(const int& u_id) {
	vertice_list.erase(u_id);     // step 1: remove the vertex from all_vertices
	edges_list.erase(u_id);       // step 2: remove all edges starting from this vertex
	for (auto& x: edges_list){    // Step 3: iterate adj_list to remove all edges ending at this vertex
            x.second.erase(u_id);
	}
}

template <typename T>
void directed_graph<T>::remove_edge(const int& u_id, const int& v_id) {

    if(contains(u_id) && contains(v_id)) {  // step 1:Makes sure vertices are in graph
        edges_list[u_id].erase(v_id);       // step 2:Removes the edge from edges_list
    } 

}

template <typename T>
size_t directed_graph<T>::in_degree(const int& u_id) { 

    int count = 0;                                   
    for (auto x : vertice_list) {                    // step 1: for each vertex
        count += edges_list.at(x.first).count(u_id); // step 2: add number of elements in edges_list
    }                                                //         where destination vertex of edge is equal to u_id     
    
    return count;
}

template <typename T>
size_t directed_graph<T>::out_degree(const int& u_id) {
    return edges_list.at(u_id).size(); //return the size of the edges_list where source vertex is u_id
}

template <typename T>
size_t directed_graph<T>::degree(const int& u_id) { 
    return in_degree(u_id) + out_degree(u_id); //Adds all in and out degrees of a vertex by reusing out_degree() & in_degree()
}                                              


template <typename T>
size_t directed_graph<T>::num_vertices() { 
    return vertice_list.size();        //returns size of the vertice_list = number of vertices
}

template <typename T>
size_t directed_graph<T>::num_edges() { 
	
    int count = 0;

    for (auto x : edges_list) {   // step 1: For each edge
        count += x.second.size(); // step 2: ACCESS SECOND VALUE OF PAIR = MAP, CHECK THAT 
    }                             //MAP'S SIZE AND ADD TO COUNT

    return count;
}

template <typename T>
vector<vertex<T>> directed_graph<T>::get_vertices() { 

    vector<vertex<T>> v;  //Stores vertices to return

    for(auto x: vertice_list){                     // step 1: iterate through vertices in vertice_list 
	v.push_back(vertex<T>(x.first, x.second)); // step 2: add new vertices with map key and value of vertices_list for each vertex_id into v
    }

    return v;  // return a vector of the vertex classes for all vertex_ids
}

template <typename T>
vector<vertex<T>> directed_graph<T>::get_neighbours(const int& u_id) { 
	
    vector<vertex<T>> v;       //Stores vertices to return
    
    if (contains(u_id)){                                            // Step 1: make sure the vertex is in the graph
	for (auto x: edges_list[u_id]){                             // Step 2: find all edges starting from the vertex of u_id
       	    v.push_back(vertex<T>(x.first, vertice_list[x.first])); // Step 3: add the end_node of each edge to the result
	}
    }

return v;
}

template <typename T>
vector<vertex<T>> directed_graph<T>::get_second_order_neighbours(const int& u_id) { 

    vector<vertex<T>> fon_v = get_neighbours(u_id);             //Creates vector of initial neighbours of vertex u_id
    vector<vertex<T>> son_v;                                    //Vector of second order neighbours
    
    if (contains (u_id)) {                                      // step 1: Check if graph contains vertex                                
        for (auto& x : fon_v) {                                 // step 2: iterate through each first order neighbour  
            vector<vertex<T>> temp_v = get_neighbours(x.id);    // step 3: for each first order neighbour, retrieve their neighbours (second order)
            for (auto& y : temp_v) {                            // step 4: iterate through each second order neighbour
                if (!in_list(y.id, son_v) && y.id != u_id){     // step 5: If the second order neighbour is not the starting vertex,
                    son_v.push_back(vertex<T>(y.id, y.weight)); //         it is added to second order neighbours vector
                }
            }
        }
    }
    
    return son_v;                                               
}

template <typename T>
bool directed_graph<T>::reachable(int u_id, int v_id) { 
    vector<vertex<T>> dfs_list = depth_first(u_id);  // step 1: Use DFS to return a vector containing all vertices reachable from a starting vertex
                                                     //         and store it in a vector
    return in_list(v_id, dfs_list);                  // step 2: use boolean function in_list() to determine if the entered vertex is within the DFS vector
}

template <typename T>
bool directed_graph<T>::contain_cycles() { 

    bool cycles = false; 
    
    for (auto& x : vertice_list) {     //A modified DFS for every vertex in graph which doesn't mark starting vertex initially
        vector<vertex<T>> visit_order; //Stores nodes visited in modified DFS 
        stack<int> unprocessed;        // nodes that need to be proccessed 
        vector<vertex<T>> visited;     //Vector containing visited vertices
        int first_removal = true;      //For each DFS, first_removal is used to remove starting vertex from visited before being set to false
        unprocessed.push(x.first);

        while (!unprocessed.empty()) { //Process here is almost identical to a normal DFS/BFS
            auto n = unprocessed.top();                  
            unprocessed.pop();                           
            vector<vertex<T>> temp_v = get_neighbours(n);
            if (!in_list(n,visited)) {                               
                visited.push_back(vertex<T>(n, vertice_list[n]));      
                visit_order.push_back(vertex<T>(n, vertice_list[n]));
                if (first_removal) {                               //Modified portion of the DFS/BFS
                    visit_order.erase(visit_order.begin());        //where the initial entry to visit_order & visited
                    visited.erase(visited.begin());                //is erased so that the starting vertex may be visited
                    first_removal = false;                         //a second time if edges lead back to it
                }                                                  
                for (auto& y : temp_v){            
                    if (!in_list(y.id,visited)) {
                        unprocessed.push(y.id);
                    }
                }
            }
        }
        if (in_list(x.first, visit_order)) {  //If resulting DFS contains the starting vertex,
            cycles = true;                    //it means there is a path leading back to start vertex, a cycle exists
        }
    }
    
    return cycles; 
}

template <typename T>
vector<vertex<T>> directed_graph<T>::depth_first(int u_id) {
    vector<vertex<T>> visit_order; //Order of visited vertices using DFS
    stack<int> unprocessed;        //nodes that need to be processed 
    vector<vertex<T>> visited;     //A vertex vector storing vertices that have been traversed

    unprocessed.push(u_id);

    while (!unprocessed.empty()) {
        auto n = unprocessed.top();                               // n  = last element that was added to stack 
        unprocessed.pop();                                        // remove from unprocessed stack
        if (!in_list(n,visited)) {                                // if vertex n is not in vector visited vertices
            visited.push_back(vertex<T>(n, vertice_list[n]));     // add that vertex to the visited vector 
            visit_order.push_back(vertex<T>(n, vertice_list[n])); // then add vertex to visit_order
            for (auto& x : edges_list[n]){                        // return neighbours of traversed vertex
                if (!in_list(x.first,visited)) {                  // check if neighbour has been visited
                    unprocessed.push(x.first);                    // add untraversed neighbours of current vertex to unprocessed
                }
            }
        }
    }
    return visit_order; 
}

template <typename T>
vector<vertex<T>> directed_graph<T>::breadth_first(const int& u_id) { 
    vector<vertex<T>> visit_order;//Order of visited vertices using BFS
    queue<int> unprocessed;       //nodes that need to be processed 
    vector<vertex<T>> visited;    //A vertex vector storing vertices that have been traversed
    
    unprocessed.push(u_id);
    
    
    
    while (!unprocessed.empty()) {
        auto n = unprocessed.front();                            // n  = last element that was added to stack 
        unprocessed.pop();                                       // remove from unprocessed queue
        if (!in_list(n,visited)) {                               // if vertex n is not in vector visited vertices 
            visited.push_back(vertex<T>(n, vertice_list[n]));    // add that vertex to the visited vector 
            visit_order.push_back(vertex<T>(n, vertice_list[n]));// then add vertex to visit_order
            for (auto& x : edges_list[n]){                       // return neighbours of traversed vertex
                if (!in_list(x.first,visited)) {                 // check id neighbour has been visited
                    unprocessed.push(x.first);                   //add untraversed neighbours of current vertex to unprocessed
                }
            }
        }
    }
    return visit_order;
}

template <typename T> 
directed_graph<T> directed_graph<T>::out_tree(int u_id) {   // returns a spanning tree, NOT minimum spanning tree     
    directed_graph<T> tree;                                 // The tree to return
    vector<vertex<T>> graph_vertices = get_vertices();      // Adds all vertices from graph (assuming connected graph) to tree    
    for (auto& x : graph_vertices) {
        tree.add_vertex(x);
    }

    vector<vertex<T>> visited;  //A vertex vector storing vertices that have been traversed
    queue<int> unprocessed;     //nodes that need to be processed
    unprocessed.push(u_id);                           
    
    while (!unprocessed.empty()){            
        auto n = unprocessed.front();
        unprocessed.pop();
        if (!tree.in_list(n, visited)) {                      
            visited.push_back(vertex<T>(n, vertice_list[n]));                //If a vertice is not visited, add it to visited
        }
        for (auto& x : edges_list[n]) {                                      // For each neighbour of current node
            if ( !in_list(x.first,visited)) {                                // If it has not been visited
                tree.add_edge(n, x.first, 0);                                // Add an edge to that neighbour
                visited.push_back(vertex<T>(x.first, vertice_list[x.first]));// and add the neighbour to visited
                unprocessed.push(x.first);                                   // repeat process for neighbour
            }
        }
        
        
    } 
    
    return tree; 
}

template <typename T>
vector<vertex<T>> directed_graph<T>::pre_order_traversal(const int& u_id, directed_graph<T>& st) {
    return st.depth_first(u_id); //Reuses depth_first() function on the MST as results are the same as a pre-order traversal
}
template <typename T>//Attempted, not working
vector<vertex<T>> directed_graph<T>::in_order_traversal(const int& u_id, directed_graph<T>& st) {
 
    stack<vertex<T>> visit_order; //Order of visited vertices using DFS
    vector<vertex<T>> visited;    //A vertex vector storing vertices that have been traversed
    int n = u_id; 
    
    while (st.get_neighbours(n).size() == 0 or !visit_order.empty()) {       // while vertex u_id has no neighbours
        for (auto& x : st.edges_list[n]){                                    
            if (st.get_neighbours(n).size() == 0 && st.in_list(n, visited)){                       
                visit_order.push(vertex<T>(n, vertice_list[n]));                                  
                if (n != x.first) {
                    n = x.first;            
                } 
            } else {                       
                    n = visit_order.top().id;
                    visit_order.pop();
                    visited.push_back(vertex<T>(n, vertice_list[n]));
                    n = x.first;
            }
        }
    }
 
    return visited; 
}

template <typename T>//Ran out of time to implement
vector<vertex<T>> directed_graph<T>::post_order_traversal(const int& u_id, directed_graph<T>& mst) { return vector<vertex<T>>(); }

template <typename T>// Sorts vertex by their weights in descending order
vector<vertex<T>> directed_graph<T>::significance_sorting() { 

    vector<vertex<T>> v = get_vertices();    // Stores vertexes to be sorted    
    vector<vertex<T>> sorted;                // Stores vertices in descending order by weights
    vector<vertex<T>> checked;               // Marks vertices that have been added to sorted vector
    int max_id;                              // Identifies the vector with highest weight in each loop below
    T max_weight = 0;                        // The value of vector with highest weight
    
    while (checked.size() != vertice_list.size()) {                  // Loop continues until all vertices have been placed in the sorted vector
        max_weight = 0;                                              // Step 1: resets/sets the maximum value of all unchecked vertices
        for (auto& x : v) {                                          // step 2: Iterates through all vertices in v
            if (x.weight >= max_weight && !in_list(x.id, checked)) { // Step 3: Checks if vertice has a weight higher than max & that the vertice has not already been sorted
                max_weight = x.weight;                               // Step 4: Set the weight and id of the maximum vertex
                max_id = x.id;
            }
        }                                                     // by the end of the for-loop, max_id & max_weight will be for the vertice with the highest weight or significance
        checked.push_back(vertex<T>(max_id, max_weight));     //  Step 5:the vertice with the highest significance for this iteration is added to checked,
        sorted.push_back(vertex<T>(max_id, max_weight));      //         and added to the sorted vector before repeating
    }                                                         // Step 6: Loop restarts until all vertices checked

    return sorted;
}



#endif
