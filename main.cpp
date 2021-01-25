#include "directed_graph.hpp" // contains two classes: vertex, directed_graph
#include "directed_graph_algorithms.cpp" // contains algorithms for directed graph

int main() {

	directed_graph<double> g1;



	vertex<double> A(0, 1000); 
	vertex<double> B(1, 450);
	vertex<double> C(2, 230);
	vertex<double> D(3, 730);
	vertex<double> E(4, 520);
	vertex<double> F(5, 150);
	vertex<double> G(6, 820);




	g1.add_vertex(A);
	g1.add_vertex(B);
	g1.add_vertex(C);
	g1.add_vertex(D);
	g1.add_vertex(E);
	g1.add_vertex(F);
	g1.add_vertex(G);


        	
        g1.add_edge(0, 1, 700); // A->B
	g1.add_edge(0, 2, 900);  // A->C
	g1.add_edge(0, 3, 5005);  // A-> D
	g1.add_edge(1, 0, 320); //B-> A->
	g1.add_edge(1, 4, 5674); // B->E
	g1.add_edge(3, 1, 1964); // D->B
	g1.add_edge(3, 6, 750); //D ->G
	g1.add_edge(4, 5, 501); //E->F
	g1.add_edge(4, 3, 1330); //E->D
	g1.add_edge(5, 4, 234); //F->E
	g1.add_edge(5, 6, 4400); //F->G
	g1.add_edge(6, 0, 1900);//G->A


        directed_graph<double> mst = g1.out_tree(0);
        
        cout << boolalpha;
	vector<vertex<double>> vertex_list = g1.get_vertices();
	cout << "all vertices: ";
	for (vertex<double> vt : vertex_list) {
	 	cout << "(" << vt.id << ", " << vt.weight << ") ";
	}
	cout << endl;
	vector<vertex<double>> vertex_list2 = mst.get_vertices();
	cout << "all vertices: ";
	for (vertex<double> vt : vertex_list2) {
	 	cout << "(" << vt.id << ", " << vt.weight << ") ";
	}
	cout << endl;
	cout << "all mst neighbours of 0: ";
	vector<vertex<double>> neighbour_list2 = mst.get_neighbours(0);
	for (vertex<double> nb : neighbour_list2) {
	 	cout << "(" << nb.id << ", " << nb.weight << ") ";
	}
        cout << endl;
	cout << "all mst neighbours of 1: ";
	vector<vertex<double>> neighbour_list10 = mst.get_neighbours(1);
	for (vertex<double> nb : neighbour_list10) {
	 	cout << "(" << nb.id << ", " << nb.weight << ") ";
	}
        cout << endl;
	cout << "all mst neighbours of 2: ";
	vector<vertex<double>> neighbour_list4 = mst.get_neighbours(2);
	for (vertex<double> nb : neighbour_list4) {
	 	cout << "(" << nb.id << ", " << nb.weight << ") ";
	}
        cout << endl;
	cout << "all mst neighbours of 3: ";
	vector<vertex<double>> neighbour_list5 = mst.get_neighbours(3);
	for (vertex<double> nb : neighbour_list5) {
	 	cout << "(" << nb.id << ", " << nb.weight << ") ";
	}
        cout << endl;
	cout << "all mst neighbours of 4: ";
	vector<vertex<double>> neighbour_list6 = mst.get_neighbours(4);
	for (vertex<double> nb : neighbour_list6) {
	 	cout << "(" << nb.id << ", " << nb.weight << ") ";
	}
        cout << endl;
	cout << "all mst neighbours of 5: ";
	vector<vertex<double>> neighbour_list7 = mst.get_neighbours(5);
	for (vertex<double> nb : neighbour_list7) {
	 	cout << "(" << nb.id << ", " << nb.weight << ") ";
	}
        cout << endl;
	cout << "all mst neighbours of 6: ";
	vector<vertex<double>> neighbour_list8 = mst.get_neighbours(6);
	for (vertex<double> nb : neighbour_list8) {
	 	cout << "(" << nb.id << ", " << nb.weight << ") ";
	}
        cout << endl;
 

        cout << "Number of vertices are: " << g1.num_vertices() << endl;
        cout << "edge exists between 0 and 1: " << g1.adjacent(0, 1) << endl;
        cout << "Number of edges are: " << g1.num_edges() << endl;
        cout << "Number of mst vertices are: " << mst.num_vertices() << endl;
        cout << "Number of mst edges are: " << mst.num_edges() << endl;
	cout << "all neighbours of A: ";
	vector<vertex<double>> neighbour_list = g1.get_neighbours(0);
	for (vertex<double> nb : neighbour_list) {
	 	cout << "(" << nb.id << ", " << nb.weight << ") ";
	}
        cout << endl << "all second order neighbours of A: ";
        vector<vertex<double>> second_neighbour_list = g1.get_second_order_neighbours(0);
	for (vertex<double> nb : second_neighbour_list) {
	 	cout << "(" << nb.id << ", " << nb.weight << ") ";
	}
      
        cout << endl;
        cout << "Edges leaving 0: " << g1.out_degree(0) << endl;
        cout << "Edges leaving mst 0: " << mst.out_degree(0) << endl;
        cout << "Edges entering 0: " << g1.in_degree(0) << endl;
        cout << "Number of edges at 0: " << g1.degree(0) << endl << endl;
    
        cout << "Is vertex 0 adjacent to vertex 1? " << g1.adjacent(0,1) << endl;
	cout << "Is vertex 3 adjacent to vertex 2? " << g1.adjacent(3,2) << endl;
        cout << "Is vertex 2 adjacent to vertex 0? " << g1.adjacent(2,0) << endl;
        cout << "Is vertex 0 adjacent to vertex 2? " << g1.adjacent(0,2) << endl;
        cout << "---bfs test---" << endl;
        vector<vertex<double>> bfs_list = g1.breadth_first(0);
        cout << "bfs staring from 0 is " << endl;
        for (vertex<double> dl : bfs_list) {
                cout << dl.id << "  ";
        }
        cout << endl;
        
            cout << "---dfs test---" << endl;
  vector<vertex<double>> dfs_list = g1.depth_first(0);
  cout << "Dfs staring from 0 is " << endl; 
  for (vertex<double> dl : dfs_list) {
         cout <<dl.id << "  ";
    }
     cout <<  endl << "Is vertex D reachable from vertex B? " << g1.reachable(1,3) << endl;
     cout << "Does the graphcontain cycles? " << g1.contain_cycles() << endl;
     vector<vertex<double>> sorted = g1.significance_sorting();
     cout << "Significance Soring results by vertex weight:" << endl;
     for (int i = 0; i < sorted.size(); i++){
	cout << "vertex ID: "<< sorted[i].id << ", weight: "<< sorted[i].weight <<endl;
    }
	cout << endl;
        
    vector<vertex<double>> topo_sort_list = topological_sort(g1);
        cout << "topological sort of graph is: " << endl;
        for (auto& dl : topo_sort_list) {
                cout << dl.id << "  ";
        }
        cout << endl;
  
        cout << endl;
    vector<vertex<double>> shortest = shortest_path(g1, 1, 6); //Should be outputting B->E->D->G (1, 4, 3, 6)
        cout << "Shortest path from B(1) to G(6) with lowest edge weight is: " << endl;
        for (auto& dl : shortest) {
                cout << dl.id << " -> ";
        }
        cout << "FINISHED" << endl;
 cout << endl;
    cout << "Strongly Connected Components" << endl;
 
    vector<vector<vertex<double>>> scc = strongly_connected_components(g1);
	double scc_n = 1;
    for (auto& vector : scc) {
		cout << "SCC " << scc_n << ": ";
		scc_n++;
        for (auto& vertex : vector) {
            cout << vertex.id  << " ";
        }
        cout << endl;
    }
	    cout << endl;
   
    cout << "Low cost delivery (average cost per person) from G "<< endl 
	<<"= (Lowest edge weight sum of all edges/Total vertice weight) "<< endl <<"= " << low_cost_delivery(g1, 6) << endl;
}