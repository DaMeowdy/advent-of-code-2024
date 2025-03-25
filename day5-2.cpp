#include <regex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class MadisRegexTomfoolery
{
    public:
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
    bool MatchesRegex(string& text, regex& pattern)
    {
        try
        {
            return regex_match(text, pattern);
        }
        catch(const std::regex_error& e)
        {
            return false;
        }
        return false;
    }
};
class Solution
{
    public:
    vector<pair<int,int>> PAGERULES;
    vector<vector<int>> UPDATES;
    string pageRulesPattern = "^[0-9]{1,3}\\|[0-9]{1,3}$";
    string pagesPattern = "^\\d+(,\\d+)*$";
    string numberPattern = "[0-9]{1,3}";
    int Solve(string path)
    {
        setup(path);
        int result = 0; 
        for(int i = 0; i<this->UPDATES.size();++i)
        {
            if(!ValidatePages(this->UPDATES[i]))
            {
                vector<int> correctedReport = CorrectUpdate(this->UPDATES[i]);
                int middleNumber = getMiddleNumber(correctedReport);
                result = result + correctedReport[middleNumber];
            }
        }
        return result;
    }
    bool ValidatePages(vector<int> update)
    {
        for(pair<int,int> rule: this->PAGERULES)
        {
            int firstRule = rule.first;
            int secondRule = rule.second;
            auto begin = update.begin();
            auto end = update.end();
            auto firstRuleIterator = find(begin, end ,firstRule);
            auto secondRuleIterator = find(begin, end, secondRule);
            if((firstRuleIterator== end)||(secondRuleIterator==end))
            {
                continue;
            }
            int left = distance(begin, firstRuleIterator);
            int right = distance(begin, secondRuleIterator);
            if(left > right)
            {
                return false;
            }
            
        }
        return true;
    }
    int getMiddleNumber(vector<int> update)
    {
        int index = update.size()/2;
        return index;
    }
    vector<int> CorrectUpdate(vector<int> update)
    {
        int index = 0;
        while(index < this->PAGERULES.size())
        {
            pair<int,int> rule = this->PAGERULES[index];
            auto begin = update.begin();
            auto end = update.end();
            auto firstRuleIterator = find(begin, end ,rule.first);
            auto secondRuleIterator = find(begin, end, rule.second);
            if((firstRuleIterator== end)||(secondRuleIterator==end))
            {
                index = index + 1;
                continue;
            }
            int left = distance(begin, firstRuleIterator);
            int right = distance(begin, secondRuleIterator);
            if(left < right)
            {
                index = index + 1;
                continue;
            }
            int swapSpace = update[left];
            update[left] = update[right];
            update[right] = swapSpace;

            index = 0;
            
        }
        return update;
    }
    private:
    void setup(string path)
    {
        ifstream infile( path);
        string line;
        MadisRegexTomfoolery regexlib;
        while(getline(infile, line))
        {
            regex pageRulesPatternRegex(this->pageRulesPattern);
            regex pagesPatternRegex(pagesPattern);
            regex numberPatternRegex(numberPattern);
            if(regexlib.MatchesRegex(line, pageRulesPatternRegex))
            {
                vector<string> matches = regexlib.GetAllRegexMatches(line, numberPatternRegex);
                int first = stoi(matches.at(0));
                int second = stoi(matches.at(1));
                pair<int, int> pushToRules = {first,second};
                this->PAGERULES.push_back(pushToRules);
            } else if (regexlib.MatchesRegex(line, pagesPatternRegex))
            {
                vector<string> matches = regexlib.GetAllRegexMatches(line,numberPatternRegex);
                vector<int> pages;
                for(string item: matches)
                {
                    pages.push_back(stoi(item));
                }
                UPDATES.push_back(pages);
            }
            else
            {
                continue;
            }
        }
        infile.close();
    }

};

int main()
{
    Solution solutionClass;
    int result = solutionClass.Solve("input.txt");
    cout << "input : " << result <<endl;
    return 0;
}