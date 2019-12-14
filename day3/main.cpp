#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

int biggest(int a, int b)
{
    if(a>b) return a;
    return b;
}

int smallest(int a,int b)
{
    if(a<b) return a;
    return b;
}

struct Board
{
    int x0=0,x1=0,y0=0,y1=0;

    map<int,map<int,bool>> board;
    void mergeSizes(const Board & board)
    {
        print();
        x0=smallest(x0,board.x0);
        x1=biggest(x1,board.x1);
        y0=smallest(y0,board.y0);
        y1=biggest(y1,board.y1);
    }

    int getCenter(int a0, int a1)
    {
        return (a0+a1) / 2 ;
    }

public:
    int smallestManhattanDistanceFrom(int x, int y)
    {
        int comparingWithX, comparingWithY;
        long smallestDist=numeric_limits<long>::max();
        for (const auto & e : board)
        {
            comparingWithX=e.first;
            for(const auto & f : e.second)
            {
                comparingWithY=f.first;
                if(f.second)
                {
                    auto dist = abs(x-comparingWithX) + abs(y-comparingWithY);

                    if(dist < smallestDist)
                    {
                        smallestDist=dist;
                    }
                }
            }
        }
        return smallestDist;
    }

    void setPoint(int x, int y)
    {
        board[x][y] = true;
        if(x<x0) x0=x;
        if(x>x1) x1=x;
        if(y<y0) y0=y;
        if(y>y1) y1=y;
    }

    bool getPoint(int x, int y) const
    {
        try {
           return board.at(x).at(y);
        }
        catch (out_of_range) {
            return false;
        }
    }

    void intersect(const Board & board_to_interserct)
    {
        Board intersect;

        int x,y;
        for (const auto  e : board)
        {
            x=e.first;
            for(const auto & f : e.second)
            {
                y=f.first;
                if(!board_to_interserct.getPoint(x,y))
                {
                   board[x][y]=false;
                }
            }
        }
    }

    void print()
    {
        int x,y;
        for (auto e : board) {
            x = e.first;
            for (auto f : e.second) {
                y = f.first;
                if (f.second==true) cout << "(" << x << "," << y << ")" << endl;
            }
        }
        printCoords();
    }

    void printCoords()
    {
        cout
                << "x0:" << x0 << ", "
                << "x1:" << x1 << ", "
                << "y0:" << y0 << ", "
                << "y1:" << y1 << endl;
    }
};

class BoardManager
{
    vector<Board> boards;

    Board load_line(const string & line)
    {
        Board ret;
        stringstream ss(line);
        string pathInfo;
        char c;
        int x=0,y=0;
        while (ss >> c)
        {
            int xincrement, yincrement;
            if(c==',')
            {
                long steps = stol(string(pathInfo.begin()+1,pathInfo.end()));
                xincrement=get_xincrement_from_char(pathInfo[0]);
                yincrement=get_yincrement_from_char(pathInfo[0]);

                for (unsigned long i=0; i!=steps; ++i)
                {
                    x += xincrement;
                    y += yincrement;
                    ret.setPoint(x,y);
                }

                pathInfo="";
            }
            else
            {
                pathInfo+=c;
            }
        }
        return ret;
    }

    int get_xincrement_from_char(char c)
    {
        if(c=='U') return -1;
        if(c=='D') return 1;
        return 0;
    }

    int get_yincrement_from_char(char c)
    {
        if(c=='R') return  1;
        if(c=='L') return -1;
        return 0;
    }

public:

    bool load_paths(string filename)
    {
        fstream fs(filename);
        stringstream ss;
        int currentx=0,currenty=0;
        char c;
        string line;
        while(getline(fs,line))
        {
            boards.push_back(load_line(line));
        }

        return  true;
    }

    Board getIntersection()
    {
        if(boards.size()!=2) {
            cout << "The number of boards is different than 2, can't intersect." << endl;
            exit(1);
        }
        else {
            auto intersection = boards[0];
            intersection.intersect(boards[1]);
            return intersection;
        }
    }

};



int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        cout << "Please specify the a file with the list of paths" << endl;
        return 1;
    }
    BoardManager boardManager;
    boardManager.load_paths(argv[1]);
    auto intersection = boardManager.getIntersection();
    auto smallest = intersection.smallestManhattanDistanceFrom(0,0);
    cout << "Smallest manhattan distance: " << smallest << endl;
}
