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
    int length = FileLine.length();
    char linechararray[length + 1];
    strcpy(linechararray, FileLine.c_str());
    parsed = strtok(linechararray,delimiter);
    while (parsed != NULL)
    {
        returnValue.push_back(stoi(parsed));
        parsed = strtok(NULL, " ");
    }
    return returnValue;

}
bool IsSafe(vector<int> Report)
{
    int size = (int) Report.size();
    bool ascending = true;
    bool descending = true;
    for(int i =0;i<size-1;i++)
    {
        
        if(abs(Report[i] - Report[i+1])<1||abs(Report[i] - Report[i+1])>3)
        {
            return false;
        }
        if(Report[i]<Report[i+1])
        {
            descending = false;
        }
        if(Report[i]>Report[i+1])
        {
            ascending = false;
        }
        
    };
    if(ascending==true&&descending==false)
    {
        return true;
    }
    if(descending==true&&ascending==false)
    {
        return true;
    }
    if(ascending==true&&descending==true)
    {
        return false;
    } 
    return false;
};


int main()
{
    vector<vector<int>> FileData;
    vector<int> row;
    string temp;
    ifstream infile("input.txt");
    int safe_reports = 0;
    while(getline(infile,temp) )
    {
        row = input_file_line_parser(temp, " ");
        for(int item: row)
        {
        }
        FileData.push_back(row);
    };
    for(vector<int> report: FileData)
    {
        if(IsSafe(report))
        {
            safe_reports = safe_reports + 1;
        }
    }
    cout << "Safe Reports : " << safe_reports << endl;
    return 1;
};