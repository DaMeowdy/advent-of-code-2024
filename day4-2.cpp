#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Solution
{
    public:
    vector<vector<char>> Data;
    int height;
    int width;
    
    bool IsColumnOutOfBounds(const int& row, const int& column)
    {
        bool columnConditions = column < 0 || column >= this->width;
        
        return columnConditions;
    }
    bool IsRowOutOfBounds(const int& row, const int& column)
    {
        bool rowConditions  = row < 0  || row >= this->height;
        return rowConditions;
    }
    int Solve(string path)
    {
        int result = 0; 
        setup(path);
        for(int i = 0; i<this->height; ++i)
        {
            for(int j = 0; j<this->width; ++j)
            {
                // if(horizontalSearch(j,i))
                // {
                //     result = result+1;
                // }
                // if(verticalSearch(j,i))
                // {
                //     result = result+1;
                // }
                // if(rightDiagonalSearch(j,i))
                // {
                //     result = result+1;
                // }
                // if(leftDiagonalSearch(j, i))
                // {
                //     result = result+1;
                // }
                if(findMASX(j,i))
                {
                    result = result +1;
                }
            }
        }
        
        return result;
    }
    bool horizontalSearch(int x, int y)
    {
        vector<char> characterBuffer;
        string templateString = "XMAS";
        string reversedTemplate = templateString;
        reverse(reversedTemplate.begin(), reversedTemplate.end());
        int length = (int) templateString.length();
        for(int i = 0;i<length; ++i )
        {
            if(!IsColumnOutOfBounds(y, x+i))
            {
                characterBuffer.push_back(this->Data[y][x+i]);
            }
            else{
            }

        }
        string line(characterBuffer.begin(), characterBuffer.end());
        if(line == templateString || line == reversedTemplate)
        {
            return true ;
        }
        else
        {
            return false;
        }
    }
    bool verticalSearch(int x, int y)
    {
        vector<char> characterBuffer;
        string templateString = "XMAS";
        string reversedTemplate = templateString;
        reverse(reversedTemplate.begin(), reversedTemplate.end());
        int length = (int) templateString.length();
        for(int i = 0;i<length; ++i )
        {
            if(!IsRowOutOfBounds(y+i, x))
            {
                characterBuffer.push_back(this->Data[y+i][x]);
            }
            else{
            }
        }
        string line(characterBuffer.begin(), characterBuffer.end());
        if(line == templateString || line == reversedTemplate)
        {
            // cout << line << endl;
            return true ;
        }
        else
        {
            return false;
        }
    }
    bool rightDiagonalSearch(int x, int y)
    {
        vector<char> characterBuffer;
        string templateString = "XMAS";
        string reversedTemplate = templateString;
        reverse(reversedTemplate.begin(), reversedTemplate.end());
        int length = (int) templateString.length();
        for(int i = 0;i<length; ++i )
        {
            if(!(IsRowOutOfBounds(y+i, x+i)||IsColumnOutOfBounds(y+i,x+i)))
            {
                characterBuffer.push_back(this->Data[y+i][x+i]);
            }
            else{
            }
        }
        string line(characterBuffer.begin(), characterBuffer.end());
        if(line == templateString || line == reversedTemplate)
        {
            // cout << line << endl;
            return true ;
        }
        else
        {
            return false;
        }
    }
    bool leftDiagonalSearch(int x, int y)
    {
        vector<char> characterBuffer;
        string templateString = "XMAS";
        string reversedTemplate = templateString;
        reverse(reversedTemplate.begin(), reversedTemplate.end());
        int length = (int) templateString.length();
        for(int i = 0;i<length; ++i )
        {
            int nextX = x-i;
            int nextY = y+i;
            if(!(IsRowOutOfBounds(nextY, nextX)||IsColumnOutOfBounds(nextY,nextX)))
            {
                characterBuffer.push_back(this->Data[nextY][nextX]);
            }
            else{
                break;
            }

        }
        string line(characterBuffer.begin(), characterBuffer.end());
        if(line == templateString || line == reversedTemplate)
        {
            cout << line << endl;
            return true ;
        }
        else
        {
            return false;
        }
    }
    bool findMASX(int x, int y)
    {
        vector<char> RLDiagonal;
        vector<char> LRDiagonal;
        if(this->Data[y][x]=='A')
        {
            if((IsRowOutOfBounds(y-1, x-1) || IsColumnOutOfBounds(y-1, x-1) ||
            IsRowOutOfBounds(y+1, x+1) || IsColumnOutOfBounds(y+1, x+1) ||
            IsRowOutOfBounds(y-1, x+1) || IsColumnOutOfBounds(y-1, x+1) ||
            IsRowOutOfBounds(y+1, x-1) || IsColumnOutOfBounds(y+1, x-1)))
            {
                return false;
            }
            RLDiagonal.push_back(this->Data[y-1][x+1]);
            RLDiagonal.push_back(this->Data[y][x]);
            RLDiagonal.push_back(this->Data[y+1][x-1]);
            LRDiagonal.push_back(this->Data[y-1][x-1]);
            LRDiagonal.push_back(this->Data[y][x]);
            LRDiagonal.push_back(this->Data[y+1][x+1]);
            string LR(LRDiagonal.begin(),LRDiagonal.end());
            string RL(RLDiagonal.begin(), RLDiagonal.end());
            if((LR=="MAS"||LR=="SAM")&&(RL=="MAS"||RL=="SAM"))
            {
                return true;
            }
            return false;
        }
        return false;
    }
    // void PrintVector()
    // {
    //     for(vector<char> line: this->Data)
    //     {
    //         string temp(line.begin(), line.end());
    //         cout << temp << endl;
    //     }
    // }
    private:
    void setup(string path)
    {
        ifstream infile( path);
        string line;
        while(infile >> line)
        {
            vector<char> row;
            for(char c: line)
            {
                row.push_back(c);
            }
            this->Data.push_back(row);
        }
        this->height = (int) this->Data.size();
        this->width = (int) this->Data[0].size();
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