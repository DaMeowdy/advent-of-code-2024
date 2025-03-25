#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> input_file_line_parser(string FileLine, char* delimiter)
{
    vector<int> returnValue = {};
    char * parsed;
    int lineLength = FileLine.length();
    int length = lineLength + 1;
    char linechararray[length];
    strcpy(linechararray, FileLine.c_str());
    parsed = strtok(linechararray,delimiter);
    while (parsed != NULL)
    {
        returnValue.push_back(stoi(parsed));
        parsed = strtok(NULL, " ");
    }
    return returnValue;

}
bool isSafeV2(vector<int>* report)
{
    bool* ascending = new bool(true);
    bool* descending = new bool(true);
    // pointer of current value report[i]
    int* current =0;
    // pointer of next value report[i+1]
    int* next = 0;
    int* diffPtr;
    int diff = 0;
    for(int i =0;i<report->size()-1;i++)
    {
        // evil int to int pointer hack
        current = &(*report)[i];
        next = &(*report)[i+1];
        diff = abs(*current - *next);
        diffPtr = &diff;
        if(*diffPtr < 1 || *diffPtr > 3)
        {
            return false;
        }
        if(*current<*next)
        {
            *descending = false;
        }
        if(*current>*next)
        {
            *ascending = false;
        }
        
    };
    if((*descending==true&&*ascending==false)||(*ascending==true&&*descending==false))
    {
        return  true;
    }
    if(*ascending==true&&*descending==true)
    {
        return false;
    } 
    return false;
}
bool isSafePart2(vector<int>* report)
{
    // Avoiding shooting myself in the foot by dereferncing a nullptr
    if(report==nullptr||report->empty())
    {
        return false;
    }
    if(isSafeV2(report))
    {
        return true;
    }
    for(int i = 0; i<report->size();i++)
    {
        vector<int> modifiedVector = *report; // new vector is a the old vector dereference
        modifiedVector.erase(modifiedVector.begin()+i);
        
        if(isSafeV2(&modifiedVector)) // passes reference to the new vector to is safe
        {
            return true;
        }
    }
    return false;
}


int main()
{
    // sorry rick I got bored and inebriated and taught myself pointers :3c  
    vector<vector<int>> FileData;
    vector<int> row;
    string temp;
    ifstream infile("input.txt");
    int safe_reports = 0;
    while(getline(infile,temp) )
    {
        row = input_file_line_parser(temp, " ");
        FileData.push_back(row);
    };
    for(vector<int> report: FileData)
    {
        // woag pointer to the report's memory address
        if(isSafePart2(&report))
        {
            safe_reports = safe_reports + 1;
        }
    }
    cout << "Safe Reports : " << safe_reports << endl;
    return 1;
} 