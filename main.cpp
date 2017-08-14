#include <bits/stdc++.h>
#define NIL -1
#define White 1
#define Gray 2
#define Black 3
using namespace std;
class Graph{
    int V;
    list<int> *adj;
    vector<int> ord;
    void SCC_visit(int u, int disc[], int low[],stack<int> *st, bool stackMember[]);
    void dfs_visit(int u, int color[], int d[] ,int p[] ,int f[],queue<int> *q);
public:
    Graph(int V);
    void addEdge(int v, int w);
    void dfs();
    void SCC();
    bool insuffeceincy;
    bool incoherence;
};
Graph::Graph(int V){
    this->V = V;
    adj = new list<int>[V];
  //  ord = new vector<int>;
}
void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
}
void Graph::SCC_visit(int u, int disc[], int low[], stack<int> *st,bool stackMember[]){
    static int time = 0;
    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i){
        int v = *i;
        if (disc[v] == -1)
        {
            SCC_visit(v, disc, low, st, stackMember);
            low[u]  = min(low[u], low[v]);
        }
        else if (stackMember[v] == true)
            low[u]  = min(low[u], disc[v]);
    }
    int cnt=0;
    int w = 0;
    if (low[u] == disc[u])
    {
        while (st->top() != u)
        {
            w = (int) st->top();
       //     cout << w+1 << " ";
            cnt++;
            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();
        //cout << w+1<<"\n";
        //cout<<"->"<<cnt+1<<"\n";
        if(cnt>=1) incoherence=true;
        stackMember[w] = false;
        st->pop();
    }
}
void Graph::SCC()
{
    int *disc = new int[V];
    int *low = new int[V];
    bool *stackMember = new bool[V];
    stack<int> *st = new stack<int>();
    for (int i = 0; i < V; i++)
    {
        disc[i] = NIL;
        low[i] = NIL;
        stackMember[i] = false;
    }
    for (int i = 0; i < V; i++)
        if (disc[i] == NIL)
            SCC_visit(i, disc, low, st, stackMember);
}
void Graph::dfs(){
    int *color=new int[V];
    int *p=new int[V];
    int *d=new int[V];
    int *f=new int[V];
    queue<int>*q=new queue<int>();
    for(int i=0;i<V;i++){
        p[i]=NIL;
        color[i]=White;
    }
    for(int i=0;i<V;i++){
        if(color[i]==White) dfs_visit(i,color,d,p,f,q);
    }

    /*for(int i=0;i<V;i++){
        cout<<i+1<<" "<<p[i]+1<<" "<<d[i]<<" "<<f[i]<<"\n";
    }
    while(q->empty()!=true){
            cout<<q->top()<<" ";
            q->pop();
        }*/
    if(incoherence) cout<<"Incoerente"<<endl;
    else{
        int u;
        while(q->empty()!=true){
           // cout<<q->top()<<" ";
            u=q->front();
            q->pop();
            if(!q->empty() && (int)q->front()!= p[u-1]+1){
             //       cout<<"here "<<q->front()<<" "<<u<<" "<<p[u]<<endl;
               insuffeceincy=true;
            }
            ord.push_back(u);
        }
        if(insuffeceincy) cout<<"Insuficiente"<<endl;
        else{
            vector<int>::iterator x;
            for(x=ord.begin();x!=ord.end();++x){
                cout<<*x<<" ";
            }
            cout<<endl;
        }
    }
}
void Graph::dfs_visit(int u,int *color,int *d,int *p,int *f,queue<int>*q){
    static int time2 = 1;
    color[u]=Gray;
    d[u]=time2;
    time2++;
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i){
        int v = *i;
        if(color[v]==White){
            p[v]=u;
            dfs_visit(v,color,d,p,f,q);
        }
    }
    color[u]=Black;
    f[u]=time2;
    //if(!q->empty() && (int)q->top()!=p[u+1]+2){
      //  insuffeceincy=true;
//cout<<"here"<<" "<<q->top()<<p[u+1]+2<<endl;
    q->push(u+1);
    time2++;
}
int v,e,a,b;
int main(){
    cin>>v>>e;
    Graph G(v);
    G.incoherence=false;
    G.insuffeceincy=false;
    for(int i=0;i<e;i++){
        cin>>a>>b;
        G.addEdge(a-1,b-1);
    }
    G.SCC();
    G.dfs();

   // cout<<endl;
   // cout<<G.incoherence<<" "<<G.insuffeceincy<<endl;

   // if(G.incoherence){
   //     cout<<"Incoerente"<<endl;
   //     return 0;
   // }
   // if(G.insuffeceincy) cout<<"Insuficeinte"<<endl;
    return 0;
}
