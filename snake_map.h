#ifndef _snake_map_h
#define _snake_map_h

#include "snake.h"
#include "macros.h"

class SnakeMap
{
public:
  SnakeMap(Snake *snake);
  void redraw();
  pair<int, int> snake_food;
  vector<pair<int, int>> apples;
  void update_snake_food(bool force_update);
  void update_apples(bool force_update);
  void update_score();
  void update_speed();
private:
  char map_array[MAP_HEIGHT][MAP_WIDTH];
  Snake *snake;
};

void clear_map(char map_array[MAP_HEIGHT][MAP_WIDTH]);
void update_snake_head(char map_array[MAP_HEIGHT][MAP_WIDTH], Snake *snake);

#endif
