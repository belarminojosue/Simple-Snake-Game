#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

bool gameOver;
const int width = 20; 
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[1000];
int nTail = 0;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup() {
  gameOver = false;
  dir = STOP;
  x = width/2;
  y = height/2;
  fruitX = (int)rand() % width;
  fruitY = (int)rand() % height;
  score = 0;
}

void Draw() {
  system("cls");

  for (int i = 0; i < width+2; i++)
    std::cout << "#";
  std::cout << std::endl;

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (j==0)
        std::cout << "#";

      if (i == y && j == x)
        std::cout << "O";
      else if (i == fruitY && j ==fruitX)
        std::cout << "F";
      else
      {
        bool print = false;
        for (int k = 0; k < nTail; k++)
        {
          if (tailX[k] == j && tailY[k] == i )
          {
            std::cout << "o";
            print = true;
          }
        }
        if (!print)
            std::cout << " ";
      }
      if (j==width-1)
        std::cout << "#" << std::endl;
    }
  }

  for (int i = 0; i < width+2; i++)
    std::cout << "#";
  
  std::cout << std::endl;
  std::cout << "Score: " << score << std::endl;
}

void Input() {
  if (_kbhit())
  {
    switch (_getch())
    {
    case 'a':
      if (dir != RIGHT)
        dir = LEFT;
      break;
    case 'd':
      if (dir != LEFT)
        dir = RIGHT;
      break;
    case 'w':
      if (dir != DOWN)
        dir = UP;
      break;
    case 's':
      if (dir != UP)
        dir = DOWN;
      break;
    case 'x':
      dir = STOP;
      break;
    }
  }
}

void Logic() {
  for (int i = nTail; i > 0; i--)
  {
    tailX[i] = tailX[i-1];
    tailY[i] = tailY[i-1];
  }
  tailX[0] = x;
  tailY[0] = y;
  switch (dir)
  {
    case LEFT:
      x--;
      break;
    case RIGHT:
      x++;
      break;
    case UP:
      y--;
      break;
    case DOWN:
      y++;
      break;
  }
  if (x > width-1 || x < 0 || y > height-1 || y < 0)
    gameOver = true;

  for (int i = 0; i < nTail; i++) {
    if (tailX[i] == x && tailY[i] == y)
      gameOver = true;
  }
  if (x == fruitX && y == fruitY)
  {
    srand(time(0));
    score += 1;
    fruitX = (int)rand() % width;
    fruitY = (int)rand() % height;
    nTail++;
  }
}

int main() {
  Setup();
  while (!gameOver)
  {
    Draw();
    Input();
    if (dir != STOP)
      Logic();
    Sleep(20);
  }
  return 0;
}