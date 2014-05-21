/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    // *** TODO ***
    // hmm, behöver väl detta??
    int  *dist = new int [size + 1];
    int  *path = new int [size + 1];
    bool *done = new bool [size + 1];
    
    
    // for all the verticies
    for (int i=1; i<=size; i++){
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }
    
    int s=1; // hmm, har ju inte source in nu. kanske bara kan välja den första?
    
    dist[s] = 0;
    done[s] = true; // have visitied this node
    
    int v = s;
    
    bool loop = true;
    while (loop) { // while the whole list is not done
        
        // update the distance of each vertex that are connected to v if better path..
        for (Node *u = array[v].getFirst(); u!=nullptr ; u = array[v].getNext()) {
            if(!done[u->vertex] && dist[u->vertex] > u->weight ) {
                dist[u->vertex] = u->weight;
                path[u->vertex] = v;
            }
        }
        
        // v will find the undone vertex
        int smallest = INFINITY; // just make it large!!!!
        for (int i=1; i<=size; i++){
            if(!done[i] && dist[i] <= smallest) {
                smallest = dist[i];
                v=i;
            }
        }
        
        // while we have not visited all the vertices. CHANGE to something better..
        loop = false;
        for (int i=1; i<=size;i++) {
            if(!done[i]) {
                loop=true;
                break;
            }
        }
        
        if(dist[v] == INFINITY ) break; // exit loop if the smallest is INFINTY, have
                                    // not found a path then......
        done[v]=true;
        
    }

    
    // should print out the edges of a minimum spanning for the
        //current graph along with the corresponding total weight
    int total_weight=0;
    for(int v=2; v<=size; ++v){ // since the source is 1
        cout << " (" << setw(2) << v
        << ", " << setw(2) << path[v] << ") ";
        total_weight += dist[v]; 
    }
    
    cout << endl << "Total weight of the graph: " << total_weight << endl;
    
    // deallocate memory
    delete[] dist;
    delete[] path;
    delete[] done;
    
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    Heap<Edge> h;   // min-heap by edge cost
    DSets d(size);  // create with size = number of nodes
    
    // insert the edges in the heap. ! ARE we doing right???
    for (int v=1; v<=size; ++v) {
        // go trough all the vertex v and check which vertex u they are connected to..
        for(Node *u = array[v].getFirst(); u != nullptr; u=array[v].getNext()){
            if(u->vertex > v) {
                h.insert(Edge(v, u->vertex, u->weight));
            }
        }
    }
    
    int counter = 0;
    int total_weight = 0;
    
    while (counter < size - 1 ) { //h.empty() instead???
        Edge e = h.deleteMin();
        int v = e.tail, u = e.head;
        
        if (d.find(v) != d.find(u)) {
            // cout
            cout << " (" << setw(2) << v
            << ", " << setw(2) << u << ") ";
            total_weight += e.weight;
            
            // merge two different trees
            d.join(d.find(u), d.find(v));
            counter++;
        }
    }
    
    cout << endl << "Total weight of the graph: " << total_weight << endl;
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
