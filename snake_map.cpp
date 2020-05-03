//'The Gambling Snake'
//CPSC 254
//Da Hang        dhang0129@gmail.com
//Xinxue Wang    xinxue0209@csu.fullerton.edu
//Juheng Mo      henrymo@csu.fullerton.edu
#include "snake_map.h"
#include <pthread.h>
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include "macros.h"
#include "snake.h"

using namespace std;


SnakeMap::SnakeMap(Snake *snake)
{
    this->snake = snake;
    clear_map(this->map_array);
    srand(time(NULL));
    update_snake_food(true);
    update_apples(true);
}


//updating the map with '.'

void SnakeMap::redraw(void) 
{
    clear_map(this->map_array);
    for (int i = 0; i < MAP_END; i++)//traverse every point on the map
    {
        cout << endl;
    }
    update_score();
    update_speed();
    vector<pair<int, int>> snake_parts = snake->snake_parts;
    //drawing the snake
    for (int i = 0; i < snake_parts.size(); i++)
    {
        pair<int, int> tmp = snake_parts[i];
        map_array[tmp.first][tmp.second] = SNAKE_CHAR;
    }

    update_snake_head(map_array, snake);
    update_snake_food(false);
    update_apples(false);

    map_array[snake_food.first][snake_food.second] = SNAKE_FOOD_CHAR;

    // draw apples
    //pushed the (x,y) to the temp apple vector
    for (int i = 0; i < apples.size(); i++)
    {
        pair<int, int> tmp = apples[i];
        map_array[tmp.first][tmp.second] = APPLE_CHAR;
    }
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            cout << map_array[i][j] << " ";
        }
        cout << endl;
    }
}

//it will generate the (x, y) for the food. Length and width are represented in the array form.
//check the point of food is already taken or not
void SnakeMap::update_snake_food(bool force_update)
{
    if (snake->food_eaten || force_update)
    {
        while (true)
        {
            int random_i = rand() % MAP_WIDTH;
            int random_j = rand() % MAP_HEIGHT;
            if (map_array[random_i][random_j] == MAP_CHAR)
            {
                snake_food = make_pair(random_i, random_j);
                snake->set_snake_food(snake_food);
                snake->food_eaten = false; //flag, when food is not eaten, used in later bool expression
                break;
            }
        }
    }
}

//it will generate the (x, y) for the apple. Length and width are represented in the array form.
void SnakeMap::update_apples(bool force_update)
{
    if (snake->apple_eaten || force_update)
    {
        apples.clear();
        int random = rand() % 3 + 1;//generating any number of apple between 1-3
        for (int i = 0; i < random; i++) {
            while (true)
            {
                int random_i = rand() % MAP_WIDTH;
                int random_j = rand() % MAP_HEIGHT;
                //check if the point is available, if it's a regular dot, if yes, then push the apple location in. 
                //the coordinate is represented as (random_i, random_j)
                if (map_array[random_i][random_j] == MAP_CHAR)
                {
                    apples.push_back(make_pair(random_i, random_j));
                    break;
                }
            }
        }
        snake->set_apples(apples);
        snake->apple_eaten = false; //flag, when apple is not eaten, used in later bool expression
    }
}

//reset the map to the map character

void clear_map(char map_array[MAP_HEIGHT][MAP_WIDTH]) 
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            map_array[i][j] = MAP_CHAR;
        }
    }
}


//updating the location of the snake head

void update_snake_head(char map_array[MAP_HEIGHT][MAP_WIDTH], Snake *snake)
{
    char snake_head_char = SNAKE_CHAR;
    enum Direction direction = snake->get_direction();
    switch (direction)
    {
    case West:
        snake_head_char = SNAKE_HEAD_WEST;
        break;
    case North:
        snake_head_char = SNAKE_HEAD_NORTH;
        break;
    case East:
        snake_head_char = SNAKE_HEAD_EAST;
        break;
    case South:
        snake_head_char = SNAKE_HEAD_SOUTH;
        break;
    }
    pair<int, int> snake_head = snake->snake_head;
    map_array[snake_head.first][snake_head.second] = snake_head_char;
}

//update the score simultaneosly

void SnakeMap::update_score(void)
{
    cout << "Score:" << snake->length << endl;
}

//update the speed simultaneosly

void SnakeMap::update_speed(void)
{
    cout << "Speed:" << snake->pause_length/1000 << " milliseconds" << endl;
}
