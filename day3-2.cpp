#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class DayThreeTaskTwoSolution
{
    public: 
    DayThreeTaskTwoSolution()
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
    vector<string> GetAllRegexMatches(string text, regex pattern)
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
    vector<string> SplitRegex(string text, regex pattern)
    {
        vector<string> splits;
        sregex_token_iterator begin(text.begin(),text.end(),pattern,-1);
        sregex_token_iterator end;
        for (auto i = begin; i != end; i++)
        {
            splits.push_back(*i);
        }
        return splits;
    }
    int solve(string path)
    {
        string FileData = ReadAllFileData(path);
        int result = 0;
        regex command_regex("do\\(\\)|don\\'t\\(\\)|mul\\([0-9]{1,3},[0-9]{1,3}\\)");
        regex number_in_command_regex("[0-9]{1,3}");
        // logic 
        // split regex on dont
        vector<string> SplitOnDont = this->GetAllRegexMatches(FileData, command_regex);
        bool isDoing = true;
        for(string str: SplitOnDont)
        {
            if(isDoing)
            {
                if(str.find("mul") != string::npos)
                {
                    vector<string> numbers = this->GetAllRegexMatches(str, number_in_command_regex);
                    int num1 = stoi(numbers.at(0));
                    int num2 = stoi(numbers.at(1));
                    result = result + num1 * num2;
                }
                if(str.find("don't()")!= string::npos)
                {
                    isDoing = false;
                }
            }
            if(str.find("do()")!= string::npos)
            {
                isDoing = true;
            }
        }
        

        return result;
    }
};
int main()
{
    DayThreeTaskTwoSolution solution;
    int aoca = solution.solve("input.txt");
    int test = solution.solve("test_input_t2.txt");
    string isCorrect = (aoca == 93465710 )?"Answer is correct" : "Answer is incorrect";
    cout << "Advent of code answer : " << aoca << endl << isCorrect << endl;
    cout << "Test Case : " << test << endl << (test==48?"Answer is correct":"Answer is incorrect");

}
