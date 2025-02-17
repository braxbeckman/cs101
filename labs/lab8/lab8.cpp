/*
 Writen by Braxton Beckman on 2/15/23
 Week 8 Lab: Tic Tac Toe (Research)
 Using strftime() and escape sequences to create a playable TTT game with timestamps
 */


#include <cctype>
#include <fstream>
#include <iostream> //interpret cout<<
#include <stdlib.h>

using namespace std;

void title();              // declares function title()
string display(char[]);    // declares function display()
void choose(char[], char); // prompts the player for a choice, then updates the board with that choice
string getWinTime();
string logWin(char[]);
bool win(char[]);
void save(char[]);
bool saveExists();

bool replay{true};
bool svCont{false};
int nCounter{0};

// this will only flip between 0 and 1, indicating whether someone has won or not
int winStatus{0};

// this sets the charracter array that we will edit to place the Xs and Os

// initiates main function
int main()
{
  title();

  char choice{};
  if (saveExists() == true)
  {
    cout << "Would you like to continue a previous game?";
    cin >> choice;
  }
  if (tolower(choice) == 'y' && saveExists() == true)
  {
    svCont = true;
  }

  while (replay)
  {
    char box[9]{'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    if (svCont == true && saveExists())
    {
      svCont = false;
      ifstream readSave;
      readSave.open("./savefile.txt", ios::in);
      char tmp;
      for (int i = 0; i < 9; i++)
      {
        readSave >> tmp;
        box[i] = tmp;
        if (tmp == 'X' || tmp == 'O')
        {
          nCounter++;
        }
      }

      readSave.close();
    }


    {
      int counter{};
      counter = nCounter + 1;
      nCounter = 0;
      while (!win(box))
      {
        if (counter == 9)
        {
          cout << "It's a tie!";
        }


        cout << display(box) << endl;
        if (counter % 2 == 0)
        {
          choose(box, 'X');
        }
        else
        {
          choose(box, 'O');
        }

        counter++;
        if (counter == 9)
        {
          cout << "\033c"
               << "It's a tie!";
          break;
        }
        cout << "\033c"; // These escape sequences are sprinkled throughout the program, used to clear the screen and
                         // make things easier to see
      }
      ofstream writeWin;
      writeWin.open("./winlog.txt", ios::out);
      writeWin << getWinTime() << "\n//////////////////////////////\n"
               << logWin(box) << endl
               << display(box) << endl
               << endl;
      writeWin.close();
    }
    cout << display(box) << endl;

    char tmp{};
    cout << "\nWould you like to play again (Y to continue)? ";
    cin >> tmp;
    if (tolower(tmp == 'y'))
    {
      replay = true;
      cout << "\033c";
    }
    else
    {
      replay = false;
    }
  }

  ifstream TTTResults;
  TTTResults.open("./winlog.txt", ios::in);
  cout << "\033c"
       << "Let's take a look at the results!\n";
  string buffer;
  while (!TTTResults.eof())
  {
    getline(TTTResults, buffer);
    cout << buffer << endl;
  }
  TTTResults.close();
  return 0; // ends program
}


void title()
{
  // displays title information
  cout << "Written by Braxton Beckman on 4/29/24\nWeek 15 Lab Tic-Tac-To Project\nMade using commands strftime() and "
          "escape sequences "
          "allow the ability to record the time of a win and clear the terminal, allowing for easy viewing\n\n";
}


string display(char boxD[])
{
  string display{};
  cout << "\n";
  // Displays TTT Board

  display += "  ";
  display += boxD[0];
  display += "  |  ";
  display += boxD[1];
  display += "  |  ";
  display += boxD[2];
  display += "\n ---------------";
  display += "\n  ";
  display += boxD[3];
  display += "  |  ";
  display += boxD[4];
  display += "  |  ";
  display += boxD[5];
  display += "\n ---------------";
  display += "\n  ";
  display += boxD[6];
  display += "  |  ";
  display += boxD[7];
  display += "  |  ";
  display += boxD[8];

  return display;
}

/*void chooseX()
{
  int selection{}; // stores the users choice of box they'd like ot play

start:
  cout << "\n(X) Please select which square you'd like to play: ";
  cin >> selection;

  // checks it the box selected has already been played, and will prompt again until a fresh box is chosen
  if (box[selection - 1] == 'X' || box[selection - 1] == 'O')
  {
    cout << "Please select another square" << endl;
    goto start;
  }
  else
    box[selection - 1] = 'X';
}*/

void choose(char boxC[], char symbol)
{
  int selection{};

  while (true)
  {
    cout << "\n(" << symbol << ") Please select which square you'd like to play, or 99 to save and exit: ";
    cin >> selection;
    if (selection == 99)
    {
      cout << "\nSaved! Thank you for playing, and come back anytime!" << endl;
      save(boxC);
      exit(0);
    }
    else if (boxC[selection - 1] == 'X' || boxC[selection - 1] == 'O')
    {
      cout << "Please select another square" << endl;
      continue;
    }
    else
    {
      boxC[selection - 1] = symbol;
      break;
    }
  }
}

// A brute force approach to checking the win status, it checks for any rows, columns or diagonals that contain three of
// the same char
bool win(char box[])
{
  if ((box[0] == box[1]) && (box[0] == box[2]))
  {
    // winStatus = 1;
    if (box[0] == 'O')
      cout << "O has won! (Row 1)" << endl;
    else
      cout << "X has won! (Row 1)" << endl;
    return true;
  }
  else if ((box[3] == box[4]) && (box[3] == box[5]))
  {
    // winStatus = 1;
    if (box[3] == 'O')
      cout << "O has won! (Row 2)" << endl;
    else
      cout << "X has won! (Row 2)" << endl;
    return true;
  }
  else if ((box[6] == box[7]) && (box[6] == box[8]))
  {
    // winStatus = 1;
    if (box[6] == 'O')
      cout << "O has won! (Row 3)" << endl;
    else
      cout << "X has won! (Row 3)" << endl;
    return true;
  }
  else if ((box[0] == box[3]) && (box[0] == box[6]))
  {
    // winStatus = 1;
    if (box[0] == 'O')
      cout << "O has won! (Column 1)" << endl;
    else
      cout << "X has won! (Column 1)" << endl;
    return true;
  }
  else if ((box[1] == box[4]) && (box[1] == box[7]))
  {
    // winStatus = 1;
    if (box[1] == 'O')
      cout << "O has won! (Column 2)" << endl;
    else
      cout << "X has won! (Column 2)" << endl;
    return true;
  }
  else if ((box[2] == box[5]) && (box[2] == box[8]))
  {
    // winStatus = 1;
    if (box[2] == 'O')
      cout << "O has won! (Column 3)" << endl;
    else
      cout << "X has won! (Column 3)" << endl;
    return true;
  }
  else if ((box[0] == box[4]) && (box[0] == box[8]))
  {
    // winStatus = 1;
    if (box[0] == 'O')
      cout << "O has won! (Left-to-right Diagonal)" << endl;
    else
      cout << "X has won! (Left-to-right Diagonal)" << endl;
    return true;
  }
  else if ((box[2] == box[4]) && (box[2] == box[6]))
  {
    // winStatus = 1;
    if (box[2] == 'O')
      cout << "O has won! (Right-to-left Diagonal)" << endl;
    else
      cout << "X has won! (Right-to-left Diagonal)" << endl;
    return true;
  }
  else
  {
    return false;
  }
}


string logWin(char box[])
{
  if ((box[0] == box[1]) && (box[0] == box[2]))
  {
    if (box[0] == 'O')
      return "O has won! (Row 1)";
    else
      return "X has won! (Row 1)";
  }
  else if ((box[3] == box[4]) && (box[3] == box[5]))
  {
    if (box[3] == 'O')
      return "O has won! (Row 2)";
    else
      return "X has won! (Row 2)";
  }
  else if ((box[6] == box[7]) && (box[6] == box[8]))
  {
    if (box[6] == 'O')
      return "O has won! (Row 3)";
    else
      return "X has won! (Row 3)";
  }
  else if ((box[0] == box[3]) && (box[0] == box[6]))
  {
    if (box[0] == 'O')
      return "O has won! (Column 1)";
    else
      return "X has won! (Column 1)";
  }
  else if ((box[1] == box[4]) && (box[1] == box[7]))
  {
    if (box[1] == 'O')
      return "O has won! (Column 2)";
    else
      return "X has won! (Column 2)";
  }
  else if ((box[2] == box[5]) && (box[2] == box[8]))
  {
    if (box[2] == 'O')
      return "O has won! (Column 3)";
    else
      return "X has won! (Column 3)";
  }
  else if ((box[0] == box[4]) && (box[0] == box[8]))
  {
    if (box[0] == 'O')
      return "O has won! (Left-to-right Diagonal)";
    else
      return "X has won! (Left-to-right Diagonal)";
  }
  else if ((box[2] == box[4]) && (box[2] == box[6]))
  {
    if (box[2] == 'O')
      return "O has won! (Right-to-left Diagonal)";
    else
      return "X has won! (Right-to-left Diagonal)";
  }
  else
    return "It's a tie!";
}

string getWinTime()
{
  char buffer[80];

  time_t currentTime{time(0)};
  struct tm *timeinfo = localtime(&currentTime);

  strftime(buffer, sizeof(buffer), "%B %d, %Y; %H:%M:%S", timeinfo);

  return buffer;
}

void save(char box[])
{
  ofstream saveStream;
  saveStream.open("./savefile.txt", ios::out);

  char *savePtr;
  savePtr = box;
  for (int i = 0; i < 9; i++)
  {
    saveStream << *savePtr << " ";
    savePtr++;
  }

  saveStream.close();
}

bool saveExists()
{
  bool result;
  fstream check;
  check.open("./savefile.txt");
  if (check.fail())
  {
    result = false;
  }
  else
  {
    result = true;
  }
  return result;
}
