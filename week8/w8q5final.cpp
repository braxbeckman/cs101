#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> towers{{'A', 'B', 'C'}, {}, {}};
vector<int> example{};
int source, dest;

void display();
void selection();
bool move(int, int);
bool win();

int main()
{
  cout << "\033[H\033[2J\033[3J";
  while (!win())
  {
    display();
    selection();
    move(source, dest);
  }
  display();
  cout << "Congratulations! You beat the Tower of Hanoi!" << endl;
}

void display()
{
  cout << "T1: ";
  for (char i : towers[0])
    cout << i << "    ";
  cout << endl;

  cout << "T2: ";
  for (char i : towers[1])
    cout << i << "    ";
  cout << endl;

  cout << "T3: ";
  for (char i : towers[2])
    cout << i << "    ";
  cout << endl;
}

void selection()
{
  cout << "Please enter the source tower: ";
  cin >> source;
  while (cin.fail() || (source > 3 || source < 1))
  {
    while (cin.fail())
    {
      cin.clear();
      cin.ignore(1000, '\n');
    }
    cout << "Invalid input, please input a # 1-3: ";
    cin >> source;
  }

  cout << "Please enter the destination tower: ";
  cin >> dest;
  while (cin.fail() || (dest > 3 || dest < 1))
  {
    while (cin.fail())
    {
      cin.clear();
      cin.ignore(1000, '\n');
    }
    cout << "Invalid input, please input a # 1-3: ";
    cin >> dest;
  }
}

bool move(int source, int dest)
{
  --source;
  --dest;
  cout << "\033[H\033[2J\033[3J";

  if (towers[source].empty())
  {
    cout << "Can't take from an empty tower!" << endl;
    return false;
  }
  else if (source == dest)
  {
    cout << "Can't move a disk onto itself!" << endl;
    return false;
  }
  else if (!towers[dest].empty() && towers[source].back() < towers[dest].back())
  {
    cout << "Can't put a larger disk on a smaller disk!" << endl;
    return false;
  }
  else
  {
    towers[dest].push_back(towers[source].back());
    towers[source].pop_back();
    return true;
  }

  string example;
  example.
}

bool win()
{
  if (towers[0].size() == 0 && towers[1].size() == 0)
    return true;
  else
    return false;
}
