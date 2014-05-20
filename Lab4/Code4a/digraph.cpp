/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    Queue<int> Q;
    
    for (int i=1; i<=size; i++){
        dist[i] = INFINITY;
        path[i] = 0;
    }
    
    dist[s] = 0;
    Q.enqueue(s);
    
    while(!Q.isEmpty()) {
        int v = Q.getFront();
        Q.dequeue();
        
        // for each edge at vertex v
        for(Node *u = array[v].getFirst(); u!=nullptr ; u = array[v].getNext()) {
            // if we have not visited
            if(dist[u->vertex] == INFINITY) {
                // update distance and path
                dist[u->vertex] = dist[v]+1;
                path[u->vertex] = v;
                // enqueue this vertex
                Q.enqueue(u->vertex);
            }
            
        }
        
        
    }

}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
    // for all the verticies
    for (int i=1; i<=size; i++){
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }
    
    dist[s] = 0;
    done[s] = true; // have visitied this node
    
    int v = s;
    
    bool loop = true;
    
    while (loop) { // while the whole list is not done
        
        // update the distance of each vertex that are connected to v if better path..
        for (Node *u = array[v].getFirst(); u!=nullptr ; u = array[v].getNext()) {
            if(!done[u->vertex] && dist[u->vertex] > dist[v] + u->weight ) {
                dist[u->vertex] = dist[v] + u->weight;
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
        
        if(dist[v] == INFINITY ) break; // exit loop if the smallest is INFINTY, hav
                                    // not found a path then......
        done[v]=true;
        
    }
    
    
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
    if(path[t]!=0) { // if we have not reached the end..
        printPath(path[t]);
    }
    
    cout << " " << t;

}
