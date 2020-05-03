//'The Gambling Snake'
//CPSC 254
//Da Hang        dhang0129@gmail.com
//Xinxue Wang    xinxue0209@csu.fullerton.edu
//Juheng Mo      henrymo@csu.fullerton.edu

#ifndef _macros_h
#define _macros_h

//the map will appear as a 20*20 dotted plane 
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define MAP_CHAR '.'
#define MAP_END 30

//drawing the shape of the snake
#define SNAKE_CHAR 'O'
#define SNAKE_HEAD_WEST '>'
#define SNAKE_HEAD_NORTH 'v'
#define SNAKE_HEAD_EAST '<'
#define SNAKE_HEAD_SOUTH '^'

//symbol '*' is used to represnt food
#define SNAKE_FOOD_CHAR '*'
//symbol '&' is used to represnt apple
#define APPLE_CHAR '&'

//default snake length is 3
#define INITIAL_SNAKE_LENGTH 3

//defualt pause_length is 1000 * 200
//it will determine how fast the snake moves
#define PAUSE_LENGTH 1000 * 200

#endif
