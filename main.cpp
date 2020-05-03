#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unistd.h>
#include <bits/stdc++.h>
#include "input.h"
#include "snake.h"
#include "snake_map.h"
#include <utility>
#include "macros.h"

using namespace std;

Snake snake;
SnakeMap snake_map(&snake);

//flush input buffer if there is any 
void initialize()
{
    input_init();
    input_enter_off();
}

//bool expression to determind if the program will exit
//The program will exit when the length of the snake is 0, or the any part of the snake hit the 'border' of the map
bool is_game_end()
{
    bool result = false;
    pair<int, int> snake_head = snake.snake_head;
    if (snake_head.first < 0 || snake_head.first >= MAP_WIDTH || snake_head.second < 0 || snake_head.second >= MAP_HEIGHT)
    {
        result = true;
    }
    if (snake.is_dead)
    {
        result = true;
    }
    return result;
}

//the screen will show "GAME IS OVER' will the program exit
void game_over()
{
    cout << "GAME IS OVER" << endl;
}

/*the program will lauch and execute below in order:
1)follow the movement direction as the user entered
2)run a pre-check to see if the snake is dead already, and exit game accordingly
3)update the map to its default 20*20 plane
4)set snake to default speed
5)check till the user enters a valid direction*/

void start_game()
{
    while (true)
    {
        snake.update_movement();
        if (is_game_end())
        {
            game_over();
            break;
        }
        snake_map.redraw();

        usleep(snake.return_speed());

        snake.validate_direction();
    }
}

int main()
{
    initialize();
    start_game();
    return 0;
}
