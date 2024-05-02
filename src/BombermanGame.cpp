#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <deque>
#include <cstring>
#include <string>
#include <iostream>
#include <deque>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <map>
#include <list>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'bomberMan' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING_ARRAY grid
 */

#ifdef OTHERS_SOLUTION
std::vector<std::string> bomberMan(int n, std::vector<std::string> grid)
{
  auto blowTargets = [](std::vector<std::string> const& targets)
    {
      auto rows = targets.size();
      auto columns = targets.front().size();
      // This mixes the step where we plant bombs in the whole grid 
      // and then we blow up the previous bombs...
      std::vector<std::string> ret(targets.size(), std::string(columns, 'O'));

      for (int r = 0; r < rows; ++r)
      {
        for (int j = 0; j < columns; ++j)
        {
          if (targets[r][j] != 'O')
            continue;
          ret[r][j] = '.';
          if (j > 0)
            ret[r][j - 1] = '.'; // LEFT
          if (j + 1 < columns)
            ret[r][j + 1] = '.'; // RIGHT
          if (r > 0)
            ret[r - 1][j] = '.'; // UP
          if (r + 1 < rows)
            ret[r + 1][j] = '.'; // DOWN
        }
      }
      return ret;
    };

  if (n < 3)
    return grid;

  if (n % 2 == 0) // On even seconds, the entire grid is filled with bombs.
  {
    return std::vector<std::string>(grid.size(), std::string(grid.front().size(), 'O'));
  }

  if (n % 4 == 3)
    return blowTargets(grid);

  return blowTargets(blowTargets(grid));
}
#else

vector<string> bomberMan(int n, vector<string> grid) {
    const size_t szRow = grid.size();
    const size_t szColumn = grid.front().size();
    const auto ForEachM = 
        [&] (auto&& lambda) {
            for (int i(0); i < szRow; i++) {
                for (int j(0); j < szColumn; j++) {
                    lambda(i, j);
                }
            }
        };

    if (n == 1) {
        return grid;
    } else if (n % 2 == 0) {
        ForEachM([&] (int i, int j) {
            grid[i][j] = 'O';
        });
        return grid;
    }

    n %= 4;
    if (n == 0) n = 4;
    else if (n == 1) n = 5;
    
    vector vvGrid(szRow, vector<int>(szColumn, -2));

    ForEachM([&] (int i, int j) {
        if (grid[i][j] == 'O') {
            vvGrid[i][j] = 0;
        }
    });

    for (int iSec(1); iSec <= n; iSec++) {
        if (iSec % 2 == 0) {
            ForEachM([&] (int i, int j) {
                if (vvGrid[i][j] < 0) vvGrid[i][j] = iSec;
            });
        } else {
            ForEachM([&] (int i, int j) {
                if (vvGrid[i][j] >= 0 && iSec - vvGrid[i][j] == 3) {
                    vvGrid[i][j] = -1; // marked as on-grid-explosion
                }
            });
            ForEachM([&] (int i, int j) {
                if (vvGrid[i][j] > 0) {
                    if (i > 0 && vvGrid[i - 1][j] == -1) {
                        vvGrid[i][j] = -2;
                    } else if (i < szRow - 1 && vvGrid[i + 1][j] == -1) {
                        vvGrid[i][j] = -2;
                    } else if (j > 0 && vvGrid[i][j - 1] == -1) {
                        vvGrid[i][j] = -2;
                    } else if (j < szColumn - 1 && vvGrid[i][j + 1] == -1) {
                        vvGrid[i][j] = -2;
                    }
                }
            });
        }
    }

    ForEachM([&] (int i, int j) {
        if (vvGrid[i][j] < 0) grid[i][j] = '.';
        else grid[i][j] = 'O';
    });

    return grid;
}
#endif

int main()
{
    // freopen("output.txt", "w", stdout);

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int r = stoi(first_multiple_input[0]);

    int c = stoi(first_multiple_input[1]);

    int n = stoi(first_multiple_input[2]);

    vector<string> grid(r);

    for (int i = 0; i < r; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = bomberMan(n, grid);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    return s;
}

string rtrim(const string &str) {
    string s(str);

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
