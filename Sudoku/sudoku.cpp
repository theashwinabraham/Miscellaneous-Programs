/*
* AUTHOR: ASHWIN ABRAHAM
*/

/*
This program prints a possible solution to a Sudoku puzzle (this need not necessarily be the only solution)
If there are no solutions, it prints "No solutions"
To enter the puzzle, enter the numbers in each row one by one from top to bottom and replace the unknown numbers with 0
*/

#include <iostream>
#include <set>
#include <array>
#include <cassert>


//Inputs puzzle
//To enter the puzzle, enter the numbers in each row one by one and replace the unknown numbers with 0
void input(std::array<std::array<std::set<int>, 9>, 9>& arr)
{
    for(int i = 0; i<9; ++i)
    {
        for(int j = 0; j<9; ++j)
        {
            int x;
            std::cin >> x;
            if(x == 0) arr[i][j] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            else arr[i][j] = {x};
        }
    }
}

//Prints the Sudoku Puzzle
void print(const std::array<std::array<std::set<int>, 9>, 9>& arr)
{
    std::cout << '\n';
    for(int i = 0; i<9; ++i)
    {
        for(int j = 0; j<9; ++j)
        {
            if(arr[i][j].size() == 1) std::cout << *arr[i][j].begin() << (j==8? '\n':' ');
            else std::cout << 0 << (j==8? '\n':' ');
        }
    }
}

//Checks whether the sudoku is valid
bool check(const std::array<std::array<std::set<int>, 9>, 9>& arr)
{
    for(int i = 0; i<9; ++i)
    {
        std::multiset<int> row, col;
        for(int j = 0; j<9; ++j)
        {
            if(arr[i][j].size() == 1) row.insert(*arr[i][j].begin());
            if(arr[j][i].size() == 1) col.insert(*arr[j][i].begin());
        }
        for(int p = 1; p<=9; ++p)
        {
            if(row.count(p) > 1) return false;
            if(col.count(p) > 1) return false;
        }
    }
    for(int i = 0; i<3; ++i)
    {
        for(int j = 0; j<3; ++j)
        {
            std::multiset<int> box;
            for(int p = 0; p<3; ++p)
            {
                for(int q = 0; q<3; ++q)
                {
                    if(arr[3*i + p][3*j + q].size() == 1) box.insert(*arr[3*i + p][3*j + q].begin());
                }
            }
            for(int c = 1; c<=9; ++c)
            {
                if(box.count(c) > 1) return false;
            }
        }
    }
    return true;
}


//Solves the sudoku without making assumptions
bool first_round(std::array<std::array<std::set<int>, 9>, 9>& arr)
{
    if(!check(arr)) return false;
    for(int i = 0; i<9; ++i)
    {
        for(int j = 0; j<9; ++j)
        {
            int size = arr[i][j].size();
            if(arr[i][j].size() > 1)
            {
                for(int p = 0; p<9; ++p)
                {
                    if(p!=j && arr[i][p].size() == 1) arr[i][j].erase(*arr[i][p].begin());
                }
            }
            if(arr[i][j].size() > 1)
            {
                for(int p = 0; p<9; ++p)
                {
                    if(p!=i && arr[p][j].size() == 1) arr[i][j].erase(*arr[p][j].begin());
                }
            }
            if(arr[i][j].size() > 1)
            {
                for(int p = 0; p<3; ++p)
                {
                    for(int q = 0; q<3; ++q)
                    {
                        if(!(3*(i/3) + p == i && 3*(j/3) + q == j) && arr[3*(i/3) + p][3*(j/3) + q].size() == 1) 
                            arr[i][j].erase(*arr[3*(i/3) + p][3*(j/3) + q].begin());
                    }
                }
            }
            if(arr[i][j].size() == 0) return false;
            if(size>1 && arr[i][j].size() == 1) first_round(arr);
        }
    }
    return true;
}

//Solves the sudoku
bool solve(std::array<std::array<std::set<int>, 9>, 9>& arr)
{
    if(!first_round(arr)) return false;
    for(int i = 0; i<9; ++i)
    {
        for(int j = 0; j<9; ++j)
        {
            while(arr[i][j].size() != 1)
            {
                if(arr[i][j].size() == 0) return false;
                std::array<std::array<std::set<int>, 9>, 9> guess = arr;
                guess[i][j] = {*arr[i][j].begin()};
                if(solve(guess) && check(guess))
                {
                    arr = guess;
                    return true;
                }
                else
                {
                    arr[i][j].erase(*arr[i][j].begin());
                }
            }
        }
    }
    return true;
}


int main()
{
    std::array<std::array<std::set<int>, 9>, 9> arr;
    input(arr);
    if(solve(arr) && check(arr)) print(arr);
    else std::cout << "\nNo solutions\n";
    return 0;
}
