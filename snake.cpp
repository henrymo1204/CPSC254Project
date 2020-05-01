#include "snake.h"
#include <pthread.h>
#include <iostream>
#include <vector>
#include <utility>
#include "snake_map.h"
#include "macros.h"

using namespace std;

void *input_thread_work(void *arg)
{
    struct Snake *snake = (struct Snake *)arg;
    while (true)
    {
        enum Direction direction = get_input();
        snake->update_next_direction(direction);
    }
}

Snake::Snake(void)
{
    direction = East;
    next_direction = direction;
    food_eaten = false;
    is_dead = false;
    length = INITIAL_SNAKE_LENGTH;
    clear_snake_world();
    initialize_snake();
    sem_init(&snake_sema, 0, 1);
    pthread_create(&input_thread, NULL, input_thread_work, this);
    pause_length = PAUSE_LENGTH;
}

void Snake::update_direction(enum Direction direction)
{
    sem_wait(&this->snake_sema);
    switch (direction)
    {
    case West:
        if (this->direction != East)
        {
            this->direction = direction;
        }
        break;
    case North:
        if (this->direction != South)
        {
            this->direction = direction;
        }
        break;
    case East:
        if (this->direction != West)
        {
            this->direction = direction;
        }
        break;
    case South:
        if (this->direction != North)
        {
            this->direction = direction;
        }
        break;
    }
    sem_post(&this->snake_sema);
}

void Snake::update_next_direction(enum Direction direction)
{
    this->next_direction = direction;
}

enum Direction Snake::get_direction(void)
{
    enum Direction result = East;
    sem_wait(&this->snake_sema);
    result = this->direction;
    sem_post(&this->snake_sema);
    return result;
}

void Snake::validate_direction(void)
{
    if (next_direction != Error)
    {
        update_direction(next_direction);
    }
}

void Snake::update_movement(void)
{
    pair<int, int> movement_part;
    enum Direction direction = get_direction();
    switch (direction)
    {
    case West:
        movement_part = make_pair(snake_head.first, snake_head.second - 1);
        break;
    case North:
        movement_part = make_pair(snake_head.first - 1, snake_head.second);
        break;
    case East:
        movement_part = make_pair(snake_head.first, snake_head.second + 1);
        break;
    case South:
        movement_part = make_pair(snake_head.first + 1, snake_head.second);
        break;
    }
    snake_head = movement_part;
    snake_parts.push_back(movement_part);//push the new head location to the end of the vector

    for (int i = 0; i < apples.size(); i++) {
        pair<int, int> apple = apples[i];
        apple_eaten = snake_head.first == apple.first && snake_head.second == apple.second;
        if (apple_eaten){
            break;
        }
    }

    food_eaten = snake_head.first == snake_food.first && snake_head.second == snake_food.second;
    if (food_eaten)//if foot is eaten
    {
        length++;//increase score
    }
    else if(apple_eaten){//if apple is eaten
        // TODO: after eating an apple
        // change speed
        random = rand() % 4;
        if (random == 0) {//increase speed
            pause_length = pause_length - 1000 * 10;//decrease the time for the console to update
            pair<int, int> tail = snake_parts.front();
            snake_world_array[tail.first][tail.second]--;
            snake_parts.erase(snake_parts.begin());//pop the tail location from the beginning of the vector
        } else if (random == 1){//decrease speed
            pause_length = pause_length + 1000 * 10;//increase the time for the console to update
            pair<int, int> tail = snake_parts.front();
            snake_world_array[tail.first][tail.second]--;
            snake_parts.erase(snake_parts.begin());//pop the tail location from the beginning of the vector
        } else if (random == 2){//increase length
            int n = rand() % 5 + 1;
            if (n == 1){
                length++;
            }
            else{
                length = length + n;
                for (int i = 0; i < n - 1; i++){//insert new tail location to the begining of the vector using for loop
                    pair<int, int> tail = snake_parts.front();
                    snake_world_array[tail.first][tail.second]++;
                    snake_parts.insert(snake_parts.begin(), tail);
                }
            }
        } else{//decrease length
            int n = rand() % 5 + 1;
            length = length - n;
            if(length < 1){//if snake length is less than 1, the snake dies
                is_dead = true;
            }
            else{
              for (int i = 0; i < n + 1; i++){//pop tail location from the beginning of the vector using for loop
                  pair<int, int> tail = snake_parts.front();
                  snake_world_array[tail.first][tail.second]--;
                  snake_parts.erase(snake_parts.begin());
              }
            }
        }
    }
    else//if food and apple not eaten
    {
        pair<int, int> tail = snake_parts.front();
        snake_world_array[tail.first][tail.second]--;//update the snake world array
        snake_parts.erase(snake_parts.begin());//pop tail location from the beginning of the vector
    }
    int head_value = ++snake_world_array[snake_head.first][snake_head.second];
    if (head_value > 1)
    {
        is_dead = true;
    }
}

void Snake::set_snake_food(pair<int, int> snake_food)
{
    this->snake_food = snake_food;
}

void Snake::set_apples(vector<pair<int, int>> apples)
{
    this->apples = apples;
}

void Snake::clear_snake_world(void)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            snake_world_array[i][j] = 0;
        }
    }
}

void Snake::initialize_snake(void)
{
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; i++)
    {
        pair<int, int> snake_part = make_pair(MAP_HEIGHT / 2, MAP_WIDTH / 2 - (INITIAL_SNAKE_LENGTH / 2) + i);
        snake_parts.push_back(snake_part);
        snake_world_array[snake_part.first][snake_part.second] = 1;
    }
    snake_head = snake_parts[snake_parts.size() - 1];
}

int Snake::return_speed(void)
{
    return pause_length;
}
