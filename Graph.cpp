#include "Graph.h"
#include <vector>
#include <queue>
#include <iostream>
#include <limits>

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}
void Graph:: setFalse() //goes through all vertices and sets visited bool as false
{
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].visited = false;
    }
}

void Graph::addEdge(string v1, string v2, int weight) //same from assignment 8
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == v1)
        {
            bool found = false;
            for(int x = 0; x<vertices[i].adj.size();x++)
            {
                if(vertices[i].adj[x].v->name == v2)
                {
                    found = true;
                }
            }
            if(!found)
            {
                for(int j = 0; j < vertices.size(); j++)
                {
                    if(vertices[j].name == v2 && i != j)
                    {
                        adjVertex av;
                        av.v = &vertices[j];
                        av.weight = weight;
                        vertices[i].adj.push_back(av);
                        //another vertex for edge in other direction
                        adjVertex av2;
                        av2.v = &vertices[i];
                        av2.weight = weight;
                        vertices[j].adj.push_back(av2);
                    }
                }
            }
        }
    }
}

void Graph::addVertex(string n){ //same as assignment 8, except also declares bool airport as false
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            //cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.airport = false;
        vertices.push_back(v);
    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices and also includes whether city has an airport or not
    for(int i = 0; i < vertices.size(); i++)
        {
            cout<< vertices[i].district<< ":" <<vertices[i].name<<"-->";
            for(int j = 0; j < vertices[i].adj.size(); j++)
            {
                cout<<vertices[i].adj[j].v->name;
                if(j != vertices[i].adj.size()-1)
                    cout << "***";
            }
            cout<<endl;
            cout << "Airport: ";
            if(vertices[i].airport == false)
                cout << "No" << endl;
            else
                cout << "Yes" << endl;
        }
}

void Graph :: addAirport(string city){
    //searches for a vertices with the string name, if it finds a match it checks if the city already has an airport.
    //if it does, it will say that the city already has an airport, else it will change airport bool to true.
    vertex *temp = NULL;
    bool found = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == city)
        {
            temp = &vertices[i];
            found = true;
        }
    }
    if(found != true)
        cout << "City doesn't exist" << endl;
    else if(temp->airport == false)
    {
        temp->airport = true;
        cout << "Airport added to " << temp->name << endl;
    }
    else
        cout << "city already has an airport" << endl;
}

void Graph :: deleteAirport(string city){
    //searches for a vertices with the string name, if it finds a match it checks if the city already has an airport.
    //if it does, it will change airport bool to false. else it will say that the bool is already false
    vertex *temp = NULL;
    bool found = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == city)
        {
            temp = &vertices[i];
            found = true;
        }
    }
    if(found != true)
        cout << "City doesn't exist" << endl;
    else if(temp->airport == true)
    {
        temp->airport = false;
        cout << "Airport deleted from " << temp->name << endl;
    }
    else
        cout << "city doesn't have an airport" << endl;
}

void Graph :: findDistrict(){ //same as assignment 8
    queue <vertex *> newQ;
    int num = 0;
    for(int i = 0; i < vertices.size();i++)
    {
        if(vertices[i].district == -1)
            {
                num++;
                vertices[i].visited = true;
                vertices[i].district = num;
                newQ.push(&vertices[i]);
                while(newQ.empty() != true)
                {
                    vertex *vert = newQ.front();
                    newQ.pop();
                    for(int j = 0; j<vert->adj.size();j++)
                    {
                        if(vert->adj[j].v->visited == false)
                        {
                            newQ.push(vert->adj[j].v);
                            vert->adj[j].v->visited = true;
                            vert->adj[j].v->district = num;
                        }
                    }
                }
            }
    }
}

void Graph :: shortestGroundPath(string city1, string city2){ //same as assignment 8, since it is only for ground transport in district
    vertex *start = NULL;
    vertex *last = NULL;
    int distance = 0;
    bool found1 = false;
    bool found2 = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == city1)
        {
            start = &vertices[i];
            found1 = true;
        }
        else if(vertices[i].name == city2)
        {
            last = &vertices[i];
            found2 = true;
        }
    }
    if(found1 != true || found2 != true)
        cout << "One or more cities doesn't exist" << endl;
    else if(start->district != last->district && start->district != -1)
        cout << "No ground path between cities" << endl;
    else if(start->district == -1)
        cout << "Please identify the districts before checking distances" << endl;
    else
    {
        queue<QueueVertex> Q;
        QueueVertex qv;
        qv.distance = 0;
        qv.path.push_back(*start);
        Q.push(qv);
        while(!(Q.empty()))
        {
            qv = Q.front();
            Q.pop();
            for(int j = 0; j< qv.path.back().adj.size();j++)
            {
                if(qv.path.back().adj[j].v->visited == false)
                {
                    qv.path.back().adj[j].v->visited = true;
                    QueueVertex temp;
                    temp.path = qv.path;
                    temp.path.push_back(*qv.path.back().adj[j].v);
                    temp.distance = qv.distance +1;
                    if(qv.path.back().adj[j].v->name == last->name)
                    {
                        cout << temp.distance;
                        for(int i = 0; i<temp.path.size();i++)
                        {
                            cout << ","<< temp.path[i].name ;
                        }
                    }
                    else
                        {
                            Q.push(temp);
                        }
                }
            }
        }
        cout << endl;
    }
}

void Graph :: shortestGroundDistance(string city1, string city2){//same as assignment 8, since it is only for ground transport in district
    vertex *start = NULL;
    vertex *last = NULL;
    int INT_MAX = numeric_limits<int>::max();
    bool found1 = false;
    bool found2 = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].previous = NULL;
        vertices[i].distance = INT_MAX;
        if(vertices[i].name == city1)
        {
            start = &vertices[i];
            found1 = true;
            vertices[i].distance = 0;
        }
        else if(vertices[i].name == city2)
        {
            last = &vertices[i];
            found2 = true;
        }
    }
    if(found1 != true || found2 != true)
        cout << "One or more cities doesn't exist" << endl;
    else if(start->district != last->district && start->district != -1)
        cout << "No ground path between cities" << endl;
    else if(start->district == -1)
        cout << "Please identify the districts before checking distances" << endl;
    else
    {
        vector<vertex*> solved;
        start->visited = true;
        start->distance = 0;
        solved.push_back(start);
        int minDistance;
        int distance = 0;
        vertex *temp;
        while(last->visited == false)
        {
            minDistance = INT_MAX;
            for(int j = 0; j < solved.size(); j++)
            {
                for(int k = 0; k < solved[j]->adj.size();k++)
                {
                    if(solved[j]->adj[k].v->visited == false)
                    {
                        distance = solved[j]->distance + solved[j]->adj[k].weight;
                        if(distance < minDistance)
                        {
                            minDistance = distance;
                            temp = solved[j]->adj[k].v;
                            temp->previous = solved[j];
                        }
                    }
                }
            }
            solved.push_back(temp);
            temp->distance = minDistance;
            temp->visited = true;
        }
        vector<vertex*> path;
        while(temp->name != start->name)
        {
            path.push_back(temp);
            temp = temp->previous;
        }
        path.push_back(temp);
        int x = path.size();
        cout << minDistance;
        for(int i = x-1; i>0;i--)
        {
            cout << ","<< path[i]->name ;
        }
        cout << "," <<path[0]->name << endl;
    }
}

bool Graph :: findAirport(int district1, int district2){
    //for distances that requires flight, checks if both districts have an airport nearby,
    //if both districts have an airport, then function returns true, else returns false
    bool found1 = false;
    bool found2 = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].district == district1 && vertices[i].airport == true)
            found1 = true;
        else if(vertices[i].district == district2 && vertices[i].airport == true)
            found2 = true;
    }
    if(found1 == true && found2 == true)
        return true;
    else
        return false;
}

int Graph :: ClosestAirportDistance(vertex *start, bool first)
{//in my Shortest distance function, it goes through here twice, first to find the closest airport to the starting city,
    //then to find the closest airport to the destination city, the for loop goes through all of the airports in the district
    //(if the district has more than 1), and goes with the shortest distance, then prints out the path. first going from start
    //to airport, then printing them going backwards from airport to last city.
    vertex *temp;
    vertex *path;
    int mindistance = 0;
    int distance;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].district == start->district && vertices[i].airport == true)
        {
            temp = &vertices[i];
            vertices[i].distance = 0;
            distance =shortestDistance(start, temp);
            if(distance < mindistance || mindistance == 0)
            {
                mindistance = distance;
                path = temp;
            }
        }
    }
    PrintPathDist(path, first);
    return mindistance;
}

int Graph :: shortestDistance(vertex *start, vertex *last) //similar to shortest distance function, excepts returns a int
{
    int INT_MAX = numeric_limits<int>::max();
    vector<vertex*> solved;
    start->visited = true;
    start->distance = 0;
    solved.push_back(start);
    int minDistance;
    int distance = 0;
    vertex *temp;
    while(last->visited == false)
    {
        minDistance = INT_MAX;
        for(int j = 0; j < solved.size(); j++)
        {
            for(int k = 0; k < solved[j]->adj.size();k++)
            {
                if(solved[j]->adj[k].v->visited == false)
                {
                    distance = solved[j]->distance + solved[j]->adj[k].weight;
                    if(distance < minDistance)
                    {
                        minDistance = distance;
                        temp = solved[j]->adj[k].v;
                        temp->previous = solved[j];
                    }
                }
            }
        }
        solved.push_back(temp);
        temp->distance = minDistance;
        temp->visited = true;
    }
    vector<vertex*> path;
    while(temp->name != start->name)
    {
        path.push_back(temp);
        temp = temp->previous;
    }
    path.push_back(temp);
    int x = path.size();
    return minDistance;
}

void Graph :: PrintPath(vertex *last, bool first){
    //prints out the path, front to back if bool first is true, and backwards if first is false
    vector <string> path;
    if(first == true)
    {
        while(last->next != NULL)
        {
            path.push_back(last->name);
            last = last->previous;
        }
        for(int i = path.size()-1; i >= 0; i--)
        {
            cout << path[i] << ",";
        }
    }
    else
    {
        while(last->next != NULL)
        {
            cout << last->name << ",";
            last = last->previous;
        }
    }
}

void Graph :: PrintPathDist(vertex *last, bool first){
    //prints out the path, front to back if bool first is true, and backwards if first is false
    vector <string> path;
    if(first == true)
    {
        while(last != NULL)
        {
            path.push_back(last->name);
            last = last->previous;
        }
        for(int i = path.size()-1; i >= 0; i--)
        {
            cout << path[i] << ",";
        }
    }
    else
    {
        while(last != NULL)
        {
            cout << last->name << ",";
            last = last->previous;
        }
    }
}

int Graph :: ClosestAirportPath(vertex *start, bool first)
{
    //in my Shortest Path function, it goes through here twice, first to find the closest airport to the starting city,
    //then to find the closest airport to the destination city, the for loop goes through all of the airports in the district
    //(if the district has more than 1), and goes with the shortest path, then prints out the path. first going from start
    //to airport, then printing them going backwards from airport to last city.
    vertex *temp;
    vertex *path;
    int mindistance = 0;
    int distance;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].district == start->district && vertices[i].airport == true)
        {
            temp = &vertices[i];
            vertices[i].distance = 0;
            distance = shortestPath(start, temp);
            if(distance < mindistance || mindistance == 0)
            {
                mindistance = distance;
                path = temp;
            }
        }
    }
    PrintPath(path, first);
    return mindistance;
}

int Graph :: shortestPath(vertex *start, vertex *last) // similar to shortestPath() from assignment 8, but returns int
{
    queue<QueueVertex> Q;
    QueueVertex qv;
    qv.distance = 0;
    qv.path.push_back(*start);
    Q.push(qv);
    QueueVertex temp;
    while(!(Q.empty()))
    {
        qv = Q.front();
        Q.pop();
        for(int j = 0; j< qv.path.back().adj.size();j++)
        {
            if(qv.path.back().adj[j].v->visited == false)
            {
                qv.path.back().adj[j].v->visited = true;
                temp.path = qv.path;
                temp.path.push_back(*qv.path.back().adj[j].v);
                temp.distance = qv.distance +1;
                if(qv.path.back().adj[j].v->name != last->name)
                {
                    Q.push(temp);
                }
            }
        }
    }
    return temp.distance;
}

void Graph :: shortestPath(string city1, string city2)
{//same from assignment 8 if cities are in the same district, but if cities are in different districts, and both districts
//have airports, it will print the path with 1 flight.
    vertex *start = NULL;
    vertex *last = NULL;
    int distance = 0;
    bool found1 = false;
    bool found2 = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == city1)
        {
            start = &vertices[i];
            found1 = true;
        }
        else if(vertices[i].name == city2)
        {
            last = &vertices[i];
            found2 = true;
        }
    }
    if(found1 != true || found2 != true)
        cout << "One or more cities doesn't exist" << endl;
    else if(start->district != last->district && start->district != -1)
    {
        if(findAirport(start->district, last->district) == false)
            cout << "No airports connecting districts" << endl;
        else
        {
            bool first = true;
            int toAirport = 0;
            int Final = 0;
            int fromAirport = 0;
            cout << start->name << ",";
            if(start->airport != true)
            {
                toAirport = ClosestAirportPath(start, first);
                Final = (toAirport-1) + Final;

            }
            Final++;
            first = false;
            if(last->airport != true)
            {
                fromAirport = ClosestAirportPath(last, first);
                Final = fromAirport + Final;
            }
            cout << last->name << endl;
            cout << "With 1 flight the shortest path is : " << Final << endl;
        }
    }

    else if(start->district == -1)
        cout << "Please identify the districts before checking distances" << endl;
    else
    {
        queue<QueueVertex> Q;
        QueueVertex qv;
        qv.distance = 0;
        qv.path.push_back(*start);
        Q.push(qv);
        while(!(Q.empty()))
        {
            qv = Q.front();
            Q.pop();
            for(int j = 0; j< qv.path.back().adj.size();j++)
            {
                if(qv.path.back().adj[j].v->visited == false)
                {
                    qv.path.back().adj[j].v->visited = true;
                    QueueVertex temp;
                    temp.path = qv.path;
                    temp.path.push_back(*qv.path.back().adj[j].v);
                    temp.distance = qv.distance +1;
                    if(qv.path.back().adj[j].v->name == last->name)
                    {
                        cout << temp.distance;
                        for(int i = 0; i<temp.path.size();i++)
                        {
                            cout << ","<< temp.path[i].name ;
                        }
                    }
                    else
                        {
                            Q.push(temp);
                        }
                }
            }
        }
        cout << endl;
    }
}

void Graph :: shortestDistance(string city1, string city2)
{
    //same from assignment 8 if cities are in the same district, but if cities are in different districts, and both districts
    //have airports, it will print the path with 1 flight.
    vertex *start = NULL;
    vertex *last = NULL;
    int INT_MAX = numeric_limits<int>::max();
    bool found1 = false;
    bool found2 = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].previous = NULL;
        vertices[i].distance = INT_MAX;
        if(vertices[i].name == city1)
        {
            start = &vertices[i];
            found1 = true;
            vertices[i].distance = 0;
        }
        else if(vertices[i].name == city2)
        {
            last = &vertices[i];
            found2 = true;
        }
    }
    if(found1 != true || found2 != true)
        cout << "One or more cities doesn't exist" << endl;
    else if(start->district != last->district && start->district != -1)
    {
        if(findAirport(start->district, last->district) == false)
            cout << "No airports connecting districts" << endl;
        else
        {
            bool first = true;
            int toAirport = 0;
            int Final = 500;
            int fromAirport = 0;
            if(start->airport != true)
            {
                toAirport = ClosestAirportDistance(start, first);
                Final = toAirport + Final;
            }
            first = false;
            if(last->airport != true)
            {
                fromAirport = ClosestAirportDistance(last, first);
                Final = fromAirport + Final;
            }
            cout << endl;
            cout << "With 1 flight the shortest path is : " << Final << endl;
        }
    }
    else if(start->district == -1)
        cout << "Please identify the districts before checking distances" << endl;
    else
    {
        vector<vertex*> solved;
        start->visited = true;
        start->distance = 0;
        solved.push_back(start);
        int minDistance;
        int distance = 0;
        vertex *temp;
        while(last->visited == false)
        {
            minDistance = INT_MAX;
            for(int j = 0; j < solved.size(); j++)
            {
                for(int k = 0; k < solved[j]->adj.size();k++)
                {
                    if(solved[j]->adj[k].v->visited == false)
                    {
                        distance = solved[j]->distance + solved[j]->adj[k].weight;
                        if(distance < minDistance)
                        {
                            minDistance = distance;
                            temp = solved[j]->adj[k].v;
                            temp->previous = solved[j];
                        }
                    }
                }
            }
            solved.push_back(temp);
            temp->distance = minDistance;
            temp->visited = true;
        }
        vector<vertex*> path;
        while(temp->name != start->name)
        {
            path.push_back(temp);
            temp = temp->previous;
        }
        path.push_back(temp);
        int x = path.size();
        cout << minDistance;
        for(int i = x-1; i>0;i--)
        {
            cout << ","<< path[i]->name ;
        }
        cout << "," <<path[0]->name << endl;
    }
}
