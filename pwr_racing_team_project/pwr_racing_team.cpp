#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
using namespace std;
struct vertex{
    int nr;
    double cost;
};
struct checkbox
{
    double value;
    bool calc;
};
checkbox ifcalculated[13];
const int junctions = 15;
const double big_enough=10000.0; //przypisuje stalej liczbe, która na pewno bedzie wieksza od tych napotkanych w problemie
double dstance[16]={0.0};
double lowest_travel_cost(vector<vertex>G[],char station,char destination)
{
//    cout<<"Wyswietlenie tablicy dstance[] przed wyzerowaniem: "<<endl;
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
//    cout<<endl<<"Poczatek: "<<s<<endl<<"Koniec: "<<d;
     for(int i=1;i<=junctions;i++)//ustawienie wartosci poczatkowych dstance[]
    {
        dstance[i]=big_enough;
    }dstance[s]=0;

//        cout<<"Wyswietlenie tablicy dstance[]PO wyzerowaniu: "<<endl;
//    for(int i=1; i<=junctions; i++)
//    {
//        cout<<i<<": "<<dstance[i]<<endl;
//    }
//    cout<<endl<<endl;

    int u=0; //v=0
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
    int multichar=(int(station)%64)*(int(destination)%64);//wyznaczam unikalne miejsce w tablicy ifcalculated dla kazdej kombinacji 2 elementów zbioru {A,B,C,D}
    switch(multichar)
    {
    case (int('A')%64)*(int('B')%64):
        ifcalculated[(int('A')%64) * (int('B')%64)].calc=true;//jesli trasa A->B = B<-A zostala wyliczona zapisuje jej wartosc w ifcalculated i oznaczam ze ta trasa jest juz
		    						//obliczona
        ifcalculated[(int('A')%64) * (int('B')%64)].value=dstance[d];
        break;
    case (int('A')%64)*(int('C')%64):
        ifcalculated[(int('A')%64) * (int('C')%64)].calc=true;
        ifcalculated[(int('A')%64) * (int('C')%64)].value=dstance[d];
        break;
    case (int('A')%64)*(int('D')%64):
        ifcalculated[(int('A')%64) * (int('D')%64)].calc=true;
        ifcalculated[(int('A')%64) * (int('D')%64)].value=dstance[d];
        break;
    case (int('B')%64)*(int('C')%64):
        ifcalculated[(int('B')%64) * (int('C')%64)].calc=true;
        ifcalculated[(int('B')%64) * (int('C')%64)].value=dstance[d];
        break;
    case (int('B')%64)*(int('D')%64):
        ifcalculated[(int('B')%64) * (int('D')%64)].calc=true;
        ifcalculated[(int('B')%64) * (int('D')%64)].value=dstance[d];
        break;
    case (int('C')%64)*(int('D')%64):
        ifcalculated[(int('C')%64) * (int('D')%64)].calc=true;
        ifcalculated[(int('C')%64) * (int('D')%64)].value=dstance[d];
        break;

}
return dstance[d];
}
int main()
{
        for(int i=0;i<13;i++)//jeszcze zadna droga nie zostala obliczona
    {
       ifcalculated[i].calc=false;
    }
    double r,g,b;
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
//    for(int i=1;i<16;i++) //wypis listy sasiedztwa z kosztem
//    {
//        cout<<i<<":";
//        for (int j=0;j<G[i].size();j++)
//        {
//            cout<<"sasiad nr: "<<G[i][j].nr<<" z kosztem "<<G[i][j].cost<<" ";
//        }
//        cout<<endl;
//    }
    double wynik=0.0;
    cin>>station;
    for(int i=0; i<n-1; i++)
    {
        cin>>destination;
        int z;
        z=(int(station)%64)*(int(destination)%64);
//       cout<<i+1<<" stacja: "<<station<<endl<<i+1<<" cel: "<<destination<<endl;
        if( ifcalculated[z].calc) //sprawdzam czy dana trasa byla juz liczona
            wynik+=ifcalculated[z].value; //jesli tak przypisuje ja do wyniku i unikam ponownego uruchamiania funkcji
        else
            wynik+=lowest_travel_cost(G, station, destination);
        station=destination;

    }cout<<wynik<<endl;

return 0;
}
