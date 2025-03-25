#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    // This populates our lists 
    int leftItem;
    int rightItem;
    vector<int> left;
    vector<int> right;
    ifstream infile("input.txt");
    while (infile >> leftItem >> rightItem)
    {
        left.push_back(leftItem);
        right.push_back(rightItem);
    };
    // Generate frequency map
    unordered_map<int,int> frequency_map;
    for(int leftItem: left)
    {
        if(find(begin(right), end(right), leftItem) != end(right))
        {
            frequency_map[leftItem] = 1;
        } else {
            frequency_map[leftItem] = 0;
        }
    };
    for(int rightItem: right)
    {
        if(find(begin(left),end(left),rightItem) != end(left))
        {
            frequency_map[rightItem] = frequency_map[rightItem]+1;
        } 
    };
    for (pair<const int, int> items: frequency_map)
    {
        if(frequency_map[items.first]!=0)
        {
            frequency_map[items.first] = frequency_map[items.first] -1;
        };
    }
    int similarityScore = 0;
    for(int leftItem: left)
    {
        similarityScore = similarityScore + (leftItem * frequency_map[leftItem]);
    }
    cout << similarityScore;
    return 1;
}