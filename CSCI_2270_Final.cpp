//David Kleckner
//CSCI 2270 Data Structures and Algorithms
//Spring 2015
//Instructor: Hoenigman
//CSCI 2270 Final Project

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "Graph.h"
using namespace std;

void PrintMenu()
{
    cout << "======Main Menu====="<<endl;
    cout << "1. Print Districts and Cities with airports" << endl;
    cout << "2. Find Districts" << endl;
    cout << "3. Find shortest path (ground transport only)" << endl;
    cout << "4. Find shortest distance(ground transport only)" << endl;
    cout << "5. Find shortest path" << endl;
    cout << "6. Find shortest distance" << endl;
    cout << "7. Build Airport"<< endl;
    cout << "8. Destroy Airport" << endl;
    cout << "9. Quit" << endl;
}

int main()
{
	Graph Map;
	ifstream inFile;
	string city1;
	string Userinput;
	string city2;
	string line;
	string parts;
    string city;
    int distance;
    bool first = true;
    string List[20];
    inFile.open("zombieCities.txt");
	if(inFile.fail())
    {
        cout << "The file was not opened successfully" << endl;
    }
    else
    {
        while(getline(inFile, line))
        {
            int x = 0;
            istringstream ss(line);
            while(getline(ss, parts, ','))
            {
                if(parts != "cities" && first == true)
                {
                   Map.addVertex(parts);
                   List[x] = parts;
                }
                else if(x == 0 && first != true)
                {
                    city = parts;
                }
                else if(!first)
                {
                    distance = stoi(parts);
                    if(distance != -1)
                        Map.addEdge(city, List[x], distance);
                }
                x++;
            }
            first = false;
        }
        inFile.close();
    }
	int i = 0;
	int input = 0;
	while(input != 9)
	{
		PrintMenu();
		getline(cin, Userinput);
        input = stoi(Userinput);
		switch(input)
		{
			case(1):
			{
			    Map.displayEdges();
				break;
			}
			case(2):
			{
                Map.setFalse();
			    Map.findDistrict();
                break;
			}
			case(3):
			{
			    Map.setFalse();
			    cout << "Enter a starting city:" << endl;
                getline(cin, city1);
                cout << "Enter an ending city:" << endl;
                getline(cin, city2);
                Map.shortestGroundPath(city1, city2);
				break;
			}
			case(4):
			{
			    Map.setFalse();
			    cout << "Enter a starting city:" << endl;
                getline(cin, city1);
                cout << "Enter an ending city:" << endl;
                getline(cin, city2);
                Map.shortestGroundDistance(city1, city2);
				break;
			}
			case(5):
			{
			    Map.setFalse();
			    cout << "Enter a starting city:" << endl;
                getline(cin, city1);
                cout << "Enter an ending city:" << endl;
                getline(cin, city2);
                Map.shortestPath(city1, city2);
				break;
			}
			case(6):
			{
			    Map.setFalse();
			    cout << "Enter a starting city:" << endl;
                getline(cin, city1);
                cout << "Enter an ending city:" << endl;
                getline(cin, city2);
                Map.shortestDistance(city1, city2);
				break;
			}
			case(7):
			{
			    cout << "Enter a city:" << endl;
                getline(cin, city1);
                Map.addAirport(city1);
				break;
			}
			case(8):
			{
			    cout << "Enter a city:" << endl;
                getline(cin, city1);
                Map.deleteAirport(city1);
				break;
			}
			case(9):
			{
				cout << "Goodbye!" << endl;
				break;
			}
		}
	}

}
