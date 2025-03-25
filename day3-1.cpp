#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class DayThreeTaskOneSolution
{
    public: 
    DayThreeTaskOneSolution()
    {
    }
    string ReadAllFileData(string path)
    {
        
        vector<string> FileData;
        string temp;
        
        ifstream infile(path);
        while(getline(infile, temp))
        {
            auto lineBuffer = temp;
            FileData.push_back(lineBuffer);
        }
        string fileDataStr;
        for (string line : FileData) 
        {
            fileDataStr = fileDataStr.append(line);
        }
        infile.close();
        return fileDataStr;
    }
    vector<string> GetAllMatches(string text, regex pattern)
    {
        vector<string> matches;
        sregex_iterator begin = sregex_iterator(text.begin(), text.end(), pattern);
        sregex_iterator end = sregex_iterator();
        
        for(sregex_iterator i = begin; i != end; i++)
        {
            matches.push_back((*i).str());
        }
        return matches;
    }
    int solve(string path)
    {
        string fileData = ReadAllFileData(path);
        regex FirstREGEX("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
        regex SecondREGEX("[0-9]{1,3}");
        int result =0;
        
        vector<string> AllMulCommands = GetAllMatches(fileData, FirstREGEX);
        

        vector<string> numbers;
        for(string command: AllMulCommands)
        {
            numbers = GetAllMatches(command, SecondREGEX);
            result = result + stoi(numbers.at(0)) * stoi(numbers.at(1));   
        }
        return result;
    }
    
};
int main()
{
    DayThreeTaskOneSolution solution;
    int aoca = solution.solve("input.txt");
    int test = solution.solve("test_input_t1.txt");
    string isCorrect = (aoca == 166630675)?"Answer is correct" : "Answer is incorrect";
    cout << "Advent of code answer : " << aoca << endl << isCorrect << endl;
    cout << "Test Case : " << test << endl << (test==161?"Answer is correct":"Answer is incorrect");
}
