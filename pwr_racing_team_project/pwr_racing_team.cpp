#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
using namespace std;
struct vertex{
    int nr;
    float cost;
};
int testi=0;
const int junctions = 15;
const float big_enough=10000.0; //przypisujê sta³ej liczbê, która na pewno bêdzie wiêksza od tych napotkanych w problemie
float dstance[16]={0.0};
float lowest_travel_cost(vector<vertex>G[],char station,char destination)
{
//    cout<<"Wyœwietlenie tablicy dstance[] przed wyzerowaniem: "<<endl;
//    for(int i=1; i<=junctions; i++)
//    {
//        cout<<i<<": "<<dstance[i]<<endl;
//    }
//    cout<<endl<<endl;
//      for(int i=1; i<=junctions; i++)
//    {
//        cout<<i<<": "<<visited[i]<<endl;
//    }
    int s=0,d=0;
    switch (station){
        case 'A':
            s=2;
            break;
        case 'B':
            s=3;
            break;
        case 'C':
            s=8;
            break;
        case 'D':
            s=14;
            break;

    }

    switch (destination){
        case 'A':
            d=2;
            break;
        case 'B':
            d=3;
            break;
        case 'C':
            d=8;
            break;
        case 'D':
            d=14;
            break;
    }
//    cout<<endl<<"Pocz¹tek: "<<s<<endl<<"Koniec: "<<d;
     for(int i=1;i<=junctions;i++)//ustawienie wartosci pocz¹tkowych dstance[]
    {
        dstance[i]=big_enough;
    }dstance[s]=0;

//        cout<<"Wyœwietlenie tablicy dstance[]PO wyzerowaniu: "<<endl;
//    for(int i=1; i<=junctions; i++)
//    {
//        cout<<i<<": "<<dstance[i]<<endl;
//    }
//    cout<<endl<<endl;

    int u=0, v=0;
    queue<vertex>Q;
    u=s;
    bool first_enter=true;
    while(!Q.empty()||first_enter) //algorytm dijkstra
    {
        if(first_enter)first_enter=false;
        else
            {u=Q.front().nr;
            Q.pop();}
        for(int i=0; i<G[u].size();i++ )
        {
            {
                if(dstance[u]+G[u][i].cost < dstance[G[u][i].nr])
                   {
                    dstance[G[u][i].nr]=dstance[u]+G[u][i].cost;
                    Q.push(G[u][i]);
                   }
            }
        }
    }
//    cout<<"Wyœwietlenie tablicy dstance[]"<<endl;
//    for(int i=1; i<=junctions; i++)
//    {
//        cout<<i<<": "<<dstance[i]<<endl;
//    }
    return dstance[d];

}

int main()
{
    float r,g,b;
    int n;
    vertex x,y;
    char station, destination, color;
    ifstream graf;
    graf.open("mapa_drog.txt");
    vector<vertex>G[20];
    cin>>r>>g>>b;
    cin>>n;
    while(!graf.eof())// nasza jezdnia jest grafem nieksierowanym
    {
        graf>>x.nr>>y.nr>>color;
        if(color=='r')
        {
            y.cost=r;
            x.cost=r;
        }else if(color=='g')
            {
                y.cost=g;
                x.cost=g;
            }else
                {
                    y.cost=b;
                    x.cost=b;
                }
        G[x.nr].push_back(y);
		G[y.nr].push_back(x);
    }
//    for(int i=1;i<16;i++) //wypis listy s¹siedztwa z kosztem
//    {
//        cout<<i<<":";
//        for (int j=0;j<G[i].size();j++)
//        {
//            cout<<"sasiad nr: "<<G[i][j].nr<<" z kosztem "<<G[i][j].cost<<" ";
//        }
//        cout<<endl;
//    }
    float wynik=0.0;
    cin>>station;
    for(int i=0; i<n-1; i++)
    {
        cin>>destination;
//       cout<<i+1<<" stacja: "<<station<<endl<<i+1<<" cel: "<<destination<<endl;
       float test=lowest_travel_cost(G, station, destination);
//       cout<<i<<": "<<test<<endl;
       wynik+=test;
        station=destination;

    }cout<<wynik<<endl;


}
