/*


Copyright 2017 Hegyi Vilmos

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


*/

#include <iostream>
#include <conio.h>
#include <windows.h>

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection(char key);
void clearScreen();
void generateFood();

char getMapValue(int value);

//Map size (dimensions)
const int mapwidth = 20;
const int mapheight = 35;

const int size = mapwidth * mapheight;

//The tile values for the map
int map[size];

//Snake head details
int headxpos;
int headypos;
int direction;

//Initial amount of food the snake has (length of body)
int food = 3;

//Determine if game is running
bool running;

int main()
{
    run();

    return 0;
}

//Main game function
void run()
{
    //Initialize the map
    initMap();
    running = true;
    while (running)
    {
        //If a key is pressed
        if (kbhit())
        {
            //Change to direction determined by key pressed
            changeDirection(getch());
            if (GetAsyncKeyState(VK_UP)) direction = 0;
            if (GetAsyncKeyState(VK_RIGHT)) direction = 1;
            if (GetAsyncKeyState(VK_DOWN)) direction = 2;
            if (GetAsyncKeyState(VK_LEFT)) direction = 3;
        }
        //Update the map
        update();

        //Clear the screen
        clearScreen();

        //Print the map
        printMap();

        //wait for 0.5 seconds
        _sleep(100);
    }

    //Print out game over text
    std::cout << std::endl << std::endl << "\t\t---\tGame Over!\t---" << std::endl << "\t\tYour score is: " << food;

    //Stop console from closing instantly
    std::cin.ignore();
}

//Change snake direction from input
void changeDirection(char key)
{
    /*
       W
     A + D
       S

       1
     4 + 2
       3
    */
    switch(key)
    {
    case 'w':
        if (direction != 2) direction = 0;
        break;
    case 'd':
        if (direction != 3) direction = 1;
        break;
    case 's':
        if (direction != 4) direction = 2;
        break;
    case 'a':
        if (direction != 5) direction = 3;
        break;
    }
}

//Move snake head to the new location
void move(int dx, int dy)
{
    //determine new head position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    //Check if there is food at the location
    if (map[newx + newy * mapwidth] == -2)
    {
        //Increase food value (body length)
        food++;

        //Generate new food on map
        generateFood();
    }

    //Check if location is free
    else if (map[newx + newy * mapwidth] != 0)
    {
        running = false;
    }

    //Move head to new location
    headxpos = newx;
    headypos = newy;
    map[headxpos + headypos * mapwidth] = food + 1;
}

//Clear screen
void clearScreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

//Generate new food on the map
void generateFood()
{
    int x = 0;
    int y = 0;
    do
    {
        //Generate random x and y values within the map
        x = rand() % (mapwidth - 2) + 1;
        y = rand() % (mapheight - 2) + 1;

        //If location is not free try again
    }while (map[x + y * mapwidth] != 0);

    //Place new food
    map[x + y * mapwidth] = -2;
}

//Update the map
void update()
{
    //Move in direction indicated by input
    switch (direction)
    {
        case 0: move(-1, 0);
            break;
        case 1: move(0, 1);
            break;
        case 2: move(1, 0);
            break;
        case 3: move(0, -1);
            break;
    }

    //Reduce snake values on map by 1
    for (int i = 0; i < size; i++)
    {
        if (map[i] > 0) map[i]--;
    }
}

//Initialize map
void initMap()
{
    //Place the initial head location in middle of map
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    map[headxpos + headypos * mapwidth] = 1;

    //Place top and bottom walls
    for (int x = 0; x < mapwidth; ++x)
    {
        map[x] = -1;
        map[x + (mapheight -1) * mapwidth] = -1;
    }

    //Places left and right walls
    for (int y = 0; y < mapheight; y++)
    {
        map[0 + y * mapwidth] = -1;
        map[(mapwidth - 1) + y * mapwidth] = -1;
    }

    //Generate first food
    generateFood();
}

//Print map to the console
void printMap()
{
    for (int x = 0; x < mapwidth; ++x)
    {
        for(int y = 0; y < mapheight; ++y)
        {
            //Prints the value at current x,y location
            std::cout << getMapValue(map[x + y * mapwidth]);
        }
        //Ends the line for next x value
        std::cout << std::endl;
    }
}

//Return graphical character for display from map value
char getMapValue(int value)
{
    //Return a part of snake body
    if (value > 0) return 'o';

    switch (value)
    {
        //Return wall
    case -1: return 'X';
        //Return food
    case -2: return 'O';
    }
}
