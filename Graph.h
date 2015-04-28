#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

struct QueueVertex
{
    int distance;
    std::vector<vertex> path;
};

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    std::string name;
    std::vector<adjVertex> adj;
    bool visited;
    bool airport;
    int distance;
    vertex *next;
    vertex *previous;
    int district = -1;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
        void setFalse();
        void findDistrict();
        void PrintPath(vertex *last, bool first);
        void PrintPathDist(vertex *last, bool first);
        int ClosestAirportDistance(vertex *v, bool first);
        int ClosestAirportPath(vertex *v, bool first);
        bool findAirport(int district, int district2);
        void addAirport(std::string city);
        void deleteAirport(std::string city);
        int shortestPath(vertex *start, vertex *last);
        int shortestDistance(vertex *start, vertex *last);
        void shortestGroundPath(std::string start, std::string last);
        void shortestGroundDistance(std:: string start, std::string last);
        void shortestPath(std::string start, std::string last);
        void shortestDistance(std:: string start, std::string last);
    protected:
    private:
        //vector<edge> edges;
        std::vector<vertex> vertices;

};

#endif // GRAPH_H
