#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> split(string line, char* delimiter)
{
    vector<int> returnValue = {};
    char * parsed;
    int length = line.length();
    char linechararray[length + 1];
    strcpy(linechararray, line.c_str());
    parsed = strtok(linechararray,delimiter);
    while (parsed != NULL)
    {
        returnValue.push_back(stoi(parsed));
        parsed = strtok(NULL, " ");
    }
    return returnValue;

}

int main()
{
    vector<int> left;
    vector<int> right;
    vector<int> distances;

    string Line; 
    ifstream probleminput("input.txt");
    while(getline(probleminput, Line))
    {
        vector<int> split_and_parsed = split(Line, " ");
        left.push_back(split_and_parsed.at(0));
        right.push_back(split_and_parsed.at(1));
    }
    stable_sort(left.begin(), left.end());
    stable_sort(right.begin(), right.end());
    int length = left.size();
    for(int i = 0; i < length;i++)
    {
        int currentLeft = left.at(i);
        int currentRight = right.at(i);
        int distanceToPush = 0;
        if(currentLeft < currentRight)
        {
            distanceToPush = currentRight - currentLeft;
            distances.push_back(distanceToPush);
        } else if (currentRight < currentLeft)
        {
            distanceToPush = currentLeft - currentRight;
            distances.push_back(distanceToPush);
        }
    }
    int totalDistances = 0;
    for(int distance: distances)
    {
        totalDistances = totalDistances + distance;
    }
    cout << totalDistances;
    return 0;
}