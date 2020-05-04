#include <iostream>
#include <vector>
#include <list>
#include <utility>          //  std::pair<>
#include <cmath>            //  std::floor
#include <fstream>          //  read file
#include <cstdlib>
#include <string>
using namespace std;

using std::cout;
using std::cin;
using std::endl;


struct HeapNode
{
    int key, element;
    HeapNode():key(0),element(0) {};
    HeapNode(int key, int element):key(key),element(element) {};
};
class BinaryHeap
{
private:
    std::vector<HeapNode> heap;
    void swap(struct HeapNode &p1, struct HeapNode &p2);
    int FindPosition(int node);
    int GetParentNode(int node)
    {
        return std::floor(node/2);
    };
public:
    BinaryHeap()
    {
        heap.resize(1);
    };
    BinaryHeap(int n)
    {
        heap.resize(n + 1);          // vertex and distance
    }
    // Min-Priority Queue
    void MinHeapify(int node, int length);
    void BuildMinHeap(std::vector<int> array);
    void DecreaseKey(int node, int newKey);
    int ExtractMin();                               // return heap[1] and sw//int Minimum(){return heap[1].element;};         // return heap[1]
    bool IsHeapEmpty(){ return (heap.size()<=1); };

};

int BinaryHeap::FindPosition(int node)
{

    int idx = 0;
    for (int i = 1; i < heap.size(); i++)
    {
        if (heap[i].element == node)
        {
            idx = i;
        }
    }
    return idx;
}

void BinaryHeap::DecreaseKey(int node, int newKey)
{

    int index_node = FindPosition(node);
    if (newKey >= heap[index_node].key)
    {
        std::cout << "new key is not smaller than current key\n";
        return;
    }
    heap[index_node].key = newKey;
    // check new subtree satisfy Min Heap
    while (index_node > 1 && heap[GetParentNode(index_node)].key > heap[index_node].key)
    {
        swap(heap[index_node], heap[GetParentNode(index_node)]);
        index_node = GetParentNode(index_node);
    }
}
void BinaryHeap::swap(struct HeapNode &p1, struct HeapNode &p2)
{

    struct HeapNode temp = p1;
    p1 = p2;
    p2 = temp;
}
int BinaryHeap::ExtractMin()
{

    if (IsHeapEmpty())
    {
        std::cout << "heap is empty\n";
        return -1;
    }
    int min = heap[1].element;
    // delete the first element/vertex
    heap[1] = heap[heap.size()-1];            // swap last and first
    heap.erase(heap.begin()+heap.size()-1);   // delete last
    MinHeapify(1, (int)heap.size());

    return min;       // return the smallest
}
void BinaryHeap::BuildMinHeap(std::vector<int> array)
{

    // put array in heap
    for (int i = 0; i < array.size(); i++)
    {
        heap[i + 1].element = i;                 // array[]-idx as element
        heap[i + 1].key = array[i];              // array[]value as key
    }
    for (int i = (int)heap.size()/2; i >= 1 ; i--)
    {
        MinHeapify(i, (int)heap.size()-1);     // -1,because  to store value
    }
}
void BinaryHeap::MinHeapify(int node, int length)
{

    int left = 2*node,          // get left child
        right = 2*node + 1,     //  get right child
        smallest;

    if (left <= length && heap[left].key < heap[node].key)
        smallest = left;
    else
        smallest = node;

    if (right <= length && heap[right].key < heap[smallest].key)
        smallest = right;

    if (smallest != node)
    {
        swap(heap[smallest], heap[node]);
        MinHeapify(smallest, length);
    }
}

/* Prim's Algorithm */

static const int maxDistance = 100;

class Graph_MST
{
private:
    int num_vertex;
    std::vector<std::list<std::pair<int,int> > > AdjList;
    std::vector<int> predecessor, distance;
    std::vector<bool> visited;
    void InitializeSingleSource(int Start);

public:
    Graph_MST():num_vertex(0) {};
    Graph_MST(int n):num_vertex(n)
    {
        AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void Prim_MinQueue(int Start);

    friend class BinaryHeap;
};

void Graph_MST::InitializeSingleSource(int Start)
{

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++)
    {
        distance[i] = maxDistance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;      // vertex distance became 0 so that  ExtractMin go to start
}

void Graph_MST::Prim_MinQueue(int Start)
{

    InitializeSingleSource(Start);

    BinaryHeap minQueue(num_vertex);
    minQueue.BuildMinHeap(distance);      // use minQueue to handle distance[]

    visited.resize(num_vertex, false);    // initializa visited[] as {0,0,0,...,0}

    while (!minQueue.IsHeapEmpty())
    {
        int u = minQueue.ExtractMin();
        visited[u] = true;
        for (std::list<std::pair<int, int> >::iterator itr = AdjList[u].begin();
                itr != AdjList[u].end(); itr++)
        {
            if (visited[(*itr).first] == false && (*itr).second < distance[(*itr).first])
            {

                distance[(*itr).first] = (*itr).second;
                predecessor[(*itr).first] = u;
                minQueue.DecreaseKey((*itr).first, distance[(*itr).first]);
            }
        }
    }

    /*   print result   */
    int total=0;
    /*cout  << "v1" << " - " <<  "v2"<< " : weight\n";*/
    int i = (Start+1)%num_vertex;
    while (i != Start)
    {
        /*cout << predecessor[i]+1 << " - " << i+1
        << " : "   << distance[i] <<"\n";*/
        total+=distance[i];
        i = (++i)%num_vertex;
    }
    cout<< "The least value to waste: "<<total<<endl;
}

void Graph_MST::AddEdge(int from, int to, int weight)
{

    AdjList[from].push_back(std::make_pair(to,weight));
}


int main()
{
    char filename[10];
    cout<<"Enter the file name:"<<endl;
    cin>>filename;
    //char filename[]="product.txt";
    fstream fp;
    char line[128];
    int block=0;
    string tem;
    string object[50];
    int length[50];
    fp.open(filename, ios::in);
    while(!fp)
    {
        cout<<"Fail to open file: "<<filename<<endl;
        cout<<"Enter the file name:"<<endl;
        cin>>filename;
        fp.open(filename, ios::in);
    }
    //cout<<"File Descriptor: "<<fp<<endl;
    fp.getline(line, sizeof(line), '\n');
    tem.assign(line);
    block=atoi (tem.c_str());
    if(block>20||block<1)
    {
        cout<<"Wrong input in block number!\nFailed."<<endl;
        return 0;
    }
    //cout<<block<<endl;
    for (int i=0; i<block; i++)
    {
        fp.getline(line, sizeof(line), ' ');
        tem.assign(line);
        object[i]=tem;
        //cout<<object[i]<<endl;
        fp.getline(line, sizeof(line), '\n');
        tem.assign(line);
        length[i]=atoi (tem.c_str());
        //cout<<length[i]<<endl;
    }
    int vertex=0,edge=0;
    int edge_blo=0;
    fp.getline(line, sizeof(line), ' ');
    tem.assign(line);
    vertex=atoi (tem.c_str());
    if(vertex>20||vertex<1)
    {
        cout<<"Wrong input in vertex!\nFailed."<<endl;
        return 0;
    }
    //cout<<vertex<<endl;
    Graph_MST g6(vertex);
    fp.getline(line, sizeof(line), '\n');
    tem.assign(line);
    edge=atoi (tem.c_str());
    if(edge>30||edge<1)
    {
        cout<<"Wrong input in edge!\nFailed."<<endl;
        return 0;
    }
    //cout<<edge<<endl;
    int v1,v2,val=0;
    string obj;
    for (int i=0; i<edge; i++)
    {
        fp.getline(line, sizeof(line), ' ');
        tem.assign(line);
        v1=atoi (tem.c_str());
        //cout<<v1<<endl;
        fp.getline(line, sizeof(line), ' ');
        tem.assign(line);
        v2=atoi (tem.c_str());
        //cout<<v2<<endl;
        fp.getline(line, sizeof(line), '\n');
        tem.assign(line);
        obj=tem;
        //cout<<obj<<endl;
        for(int i=0; i<obj.size(); i++) //cout<<obj[i]<<endl;
            edge_blo=(obj.size()+1)/3;
        //cout<<edge_blo<<endl;
        for (int i=0; i<edge_blo; i++)
        {
            for(int j=0; j<block; j++)
            {
                if(obj[0+3*i]==object[j][0])
                {
                    val+=length[j]*(obj[1+3*i]-'0');
                }
            }
        }
        //cout<<val<<endl;
        g6.AddEdge(v1-1,v2-1,val);
        g6.AddEdge(v2-1,v1-1,val);
        val=0;
    }
    fp.close();

    //cout << "MST -\n";
    g6.Prim_MinQueue(0);

    return 0;
}

