#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/* take one board and clone it*/
void copy_board(int copy[][4], int orignal[][4])
{
  for (int x = 0; x < 4; x++)
  {
    for (int y = 0; y < 4; y++)
    {
      copy[x][y]  = orignal[x][y];
    }
  }
}

/*  check if the table is merge able  */
bool checkMerge(int board[][4], int y1, int x1, int y2, int x2)
{
  if (board[x1][y1] != 0)
  {
    if (board[x2][y2] != 0)
    {
      if (board[x1][y1] == board[x2][y2]) {return true; }
      else{ return false; }
    }
  }
  return false;
}

/* merge numbers together*/
void merge(int board[][4], int y1, int x1, int y2, int x2)
{
  if (checkMerge(board, y1, x1, y2, x2))
  {
    board[x1][y1] = board[x1][y1] * 2;
    board[x2][y2] = 0;
  }
}

/*check if the table is shift or not*/
bool is_shift_yet(int before_shift[][4], int after_shift[][4] )
{
  for (int x = 0; x <4; x++)
    for (int y = 0; y <4; y++)
    {
      if (after_shift[x][y] != before_shift[x][y])
      {
        return true;
      }
    }
  return false;
}

/* shift up*/
void shiftUp(int board[][4])
{
  for (int i = 1; i < 5; i++)
  {
    for (int x = 0; x < 4; x++)
    {
      for (int y = 1; y < 4; y++)
      {
        if (board[x][y] != 0)
        {
          if (board[x][y - 1] == 0)
          {
            board[x][y - 1] = board[x][y];
            board[x][y] = 0;
          }
        }
      }
    }
  }
}

/*move up*/
void moveUp(int board[][4])
{
  shiftUp(board);
  for (int x = 0; x < 4; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      merge(board, y, x, y + 1, x);
    }
  }
  shiftUp(board);
}

/*shift left*/
void shiftLeft(int board[][4])
{
  for (int i = 1; i < 5; i++)
  {
    for (int y = 0; y < 4; y++)
    {
      for (int x = 1; x < 4; x++)
      {
        if (board[x][y] != 0)
        {
          if (board[x - 1][y] == 0)
          {
            board[x - 1][y] = board[x][y];
            board[x][y] = 0;
          }
        }
      }
    }
  }
}

/*move left*/
void moveLeft(int board[][4])
{
  shiftLeft(board);
  for (int y = 0; y < 4; y++)
  {
    for (int x = 0; x < 3; x++)
    {
      merge(board, y, x, y, x + 1);
    }
  }
  shiftLeft(board);
}

void shiftDown(int board[][4])
{
  for (int i = 1; i < 5; i++)
  {
    for (int x = 0; x < 4; x++)
    {
      for (int y = 2; y > -1; y--)
      {
        if (board[x][y] != 0)
        {
          if (board[x][y + 1] == 0)
          {
            board[x][y + 1] = board[x][y];
            board[x][y] = 0;
          }
        }
      }
    }
  }
}

void moveDown(int board[][4])
{
  shiftDown(board);
  for (int x = 0; x < 4; x++)
  {
    for (int y = 3; y > 0; y--)
    {
      merge(board, y, x, y - 1, x);
    }
  }
  shiftDown(board);
}


void shiftRight(int board[][4])
{
  for (int i = 1; i < 5; i++)
  {
    for (int y = 0; y < 4; y++)
    {
      for (int x = 2; x > -1; x--)

      {
        if (board[x][y] != 0)
        {
          if (board[x + 1][y] == 0)
          {
            board[x + 1][y] = board[x][y];
            board[x][y] = 0;
          }
        }
      }
    }
  }
}


void moveRight(int board[][4])
{
  shiftRight(board);
  for (int y = 0; y < 4; y++)
  {
    for (int x = 3; x > 0; x--)
    {
      merge(board, y, x, y, x - 1);
    }
  }
  shiftRight(board);
}

/*rando function*/
int randomNum(int min, int max){  return rand() % max + min;}

/*spawn number on the table*/
void spawnNum(int board[][4])
{
  int y, x;
  int twoFour = randomNum(1, 11);
  bool is_spawn_num = false;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if(board[i][j] == 0)
        is_spawn_num = true;

  while (is_spawn_num == true)
  {
    y = randomNum(0, 4);
    x = randomNum(0, 4);
    if (board[x][y] == 0){ break; }
  }
  if (is_spawn_num == true)
  {
    if (twoFour < 10) { board[x][y] = 2; }
    else {   board[x][y] = 4; }
  }
}

/*print out board*/
void displayBoard(int board[][4])
{
  cout << string(50, '\n');
  cout << "_____________________________";
  for (int i = 0; i < 4; i++)
  {
    cout<< endl;
    cout << "|      |      |      |      |" <<endl;
    for (int j = 0; j < 4; j++)
    {
      cout << "|" ;
      if (board[j][i]  == 0)
        cout <<"  "<<" "<<"   ";
      else if (board[j][i] == 2)
        cout <<"  "<<"\033[1;30m"<<board[j][i]<<"\033[0m" <<"   ";
      else if (board[j][i] == 4)
        cout <<"  "<<board[j][i]<<"   ";
      else if (board[j][i] == 8)
        cout <<"  "<<"\033[1;31m"<<board[j][i]<<"\033[0m" <<"   ";
      else if (board[j][i]  == 16)
        cout <<"  " <<"\033[1;31m"<<board[j][i]<<"\033[0m" <<"  ";
      else if (board[j][i]  == 32)
        cout <<"  " <<"\033[1;32m"<<board[j][i]<<"\033[0m" <<"  ";
      else if (board[j][i]  == 64)
        cout <<"  " <<"\033[1;32m"<<board[j][i]<<"\033[0m" <<"  ";
      else if (board[j][i]  == 128)
        cout <<" " <<"\033[1;33m"<<board[j][i]<<"\033[0m" <<"  ";
      else if (board[j][i]  == 256)
        cout <<" " <<"\033[1;33m"<<board[j][i]<<"\033[0m" <<"  ";
      else if (board[j][i]  == 512)
        cout <<" " <<"\033[1;34m"<<board[j][i]<<"\033[0m" <<"  ";
      else if (board[j][i]  == 1024)
        cout <<" " <<"\033[1;34m"<<board[j][i]<<"\033[0m" <<" ";
      else if (board[j][i]  == 2048)
        cout <<" " <<"\033[1;35m"<<board[j][i]<<"\033[0m" <<" ";
      else if (board[j][i]  == 4096)
        cout <<" " <<"\033[1;35m"<<board[j][i]<<"\033[0m" <<" ";
      else if (board[j][i]  == 8192)
        cout <<" " <<"\033[1;35m"<<board[j][i]<<"\033[0m" <<" ";
      else if (board[j][i]  == 16384)
        cout <<" " <<"\033[1;35m"<<board[j][i]<<"\033[0m" <<"";
    }
    cout << "|" << endl;
    cout << "|______|______|______|______|";
  }
  cout <<endl;
  cout <<endl;

}

/*check if game over*/
bool game_over(int board[][4])
{
  for (int x = 0; x < 4; x++)
  {
    for (int y = 0; y < 4; y++)
    {
      if(board[x][y] == 0) {return false;}
    }
  }

  int board_tmp[4][4];
  copy_board(board_tmp,board);
  moveUp(board_tmp);
  if(is_shift_yet(board,board_tmp)== true)
    return false;
  copy_board(board_tmp,board);
  moveLeft(board_tmp);
  if(is_shift_yet(board,board_tmp)== true)
    return false;
  copy_board(board_tmp,board);
  moveDown(board_tmp);
  if(is_shift_yet(board,board_tmp)== true)
    return false;
  copy_board(board_tmp,board);
  moveRight(board_tmp);
  if(is_shift_yet(board,board_tmp)== true)
    return false;

  return true;
}

/*check win condition
need more work*/
bool game_win(int board[][4])
{
  for (int x = 0; x < 4; x++)
  {
    for (int y = 0; y < 4; y++)
    {
      if (board[x][y] == 2048)
        return true;
    }
  }
  return false;
}

int game_start_choice()
{
  int choice;
  cout << "2048 Game" << endl;
  cout << "1. New game" << endl;
  cout << "2. Load game" << endl;
  cout << "3. Quit" << endl;
  cin >> choice;
  return choice;
}

/*save game into a file*/
void save(int old_board[][4], int board[][4])
{
  ofstream myfile ("save.txt");
  if (myfile.is_open())
  {
    for (int i =0 ; i < 4 ; i++)
    {
      for (int j =0 ; j < 4; j++ )
      {
        myfile << board[i][j] << endl;
      }
    }
    for (int i =0 ; i < 4 ; i++)
    {
      for (int j =0 ; j < 4; j++ )
      {
        myfile << old_board[i][j] << endl;
      }
    }
    myfile.close();
  }
}
/*load game from file*/
void load(int old_board[][4], int board[][4])
{
  string line;
  ifstream myfile ("save.txt");
  if (myfile.is_open())
  {
      for (int i =0 ; i < 4 ; i++)
      {
        for (int j =0 ; j < 4; j++ )
        {
          getline (myfile,line);
          board[i][j] = stoi(line);
        }
      }
      for (int i =0 ; i < 4 ; i++)
      {
        for (int j =0 ; j < 4; j++ )
        {
          getline (myfile,line);
          old_board[i][j] = stoi(line);
        }
      }
    myfile.close();
  }
  else
    cout << "There is no save game";
}

/*run game*/
int main()
{
  int choice;
  string move;
  bool is_shift = false;
  bool playing = true;
  int game_board[4][4]; // game board
  int is_shift_board[4][4]; // checking if shift is valid
  int old_game_board[4][4]; // old game board for undo
  int undo_game_board[4][4]; // undo

  srand (time(0));

  choice = game_start_choice();

  if (choice == 1){
    // init board
    for (int x = 0; x < 4; x++){
      for (int y = 0; y < 4; y++){
        game_board[x][y] = 0;
      }
    }
    spawnNum(game_board);
    spawnNum(game_board);
    copy_board(old_game_board,game_board);
    copy_board(undo_game_board,old_game_board);
  }
  if (choice == 2)  {    load(old_game_board,game_board);  }
  else if (choice == 3)
  {
    cout << "See you later" << endl;
    return 0;
  }


  while (playing )
  {
    if (is_shift == true){
      copy_board(is_shift_board, game_board);
    }

    is_shift = false;
    displayBoard(game_board);
    if (game_win(game_board) == true)
      cout << "YOU WIN"<<endl;
    playing = !(game_over(game_board));

    cout << "('w' 'a' 's' 'd' 'quit'): ";
    cin >> move;
    if(move != "u" )
    {
        copy_board(old_game_board,game_board);
    }
    if (move == "w")         {moveUp(game_board);}
    else if (move == "a")    {moveLeft(game_board);}
    else if (move == "s")    {moveDown(game_board);}
    else if (move == "d")    {moveRight(game_board);}
    else if (move == "u")    {copy_board(game_board,undo_game_board);}
    else if (move == "quit") {break;}

    if (move != "u")
    {
    is_shift = is_shift_yet(is_shift_board,game_board);
    if (is_shift == true){
      copy_board(undo_game_board,old_game_board);
      spawnNum(game_board);
    }
    save(old_game_board, game_board);
    }
  }
  cout << "YOU LOSE"<<endl;
  return 0;
}
