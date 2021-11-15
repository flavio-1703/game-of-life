#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define WIDTH  10
#define HEIGHT 10

#define DEAD_ASCII  "\u25a1"
#define ALIVE_ASCII "\u25A0"
#define DEAD  0
#define ALIVE 1

// FUNCS
void delay(uint32_t secs);
void print_grid(uint32_t grid[][HEIGHT]);
void game(uint32_t grid[][HEIGHT]);
uint32_t count_neighbors(uint32_t grid[][HEIGHT], uint32_t x, uint32_t y);

int main(void) {
  // INIT GRID
  uint32_t grid[WIDTH][HEIGHT] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  
  while (1) {
    system("clear");
    print_grid(grid);
    game(grid);
    delay(1);
  }  

  return 0;
}

// DELAY TIME
void delay(uint32_t secs) {
  uint32_t ret_time = time(0) + secs;
  while (time(0) < ret_time);  
}

// PRINT ARRAY
void print_grid(uint32_t grid[][HEIGHT]) {
  for (uint32_t i = 0; i < WIDTH; i++){
    for (uint32_t j = 0; j < HEIGHT; j++) {
      if (grid[i][j] == ALIVE)
        printf("%s", ALIVE_ASCII);
      else
        printf("%s", DEAD_ASCII);
      printf("%s", "  ");
    }
    printf("%s", "\n");
  }   
}

// RETURNS THE NUMBER OF NEIGHBORS
uint32_t count_neighbors(uint32_t grid[][HEIGHT], uint32_t x, uint32_t y) {
  uint32_t sum = 0;
  for (int32_t i = -1; i < 2; i++){
    for (int32_t j = -1; j < 2; j++) {
      uint32_t col = (x + i + WIDTH) % WIDTH;
      uint32_t row = (y + j + HEIGHT) % HEIGHT;
      sum += grid[col][row];
    }
  } 
  sum -= grid[x][y];
  return sum;
}

// APPLY GAME RULES
void game(uint32_t grid[][HEIGHT]) {
  uint32_t next[WIDTH][HEIGHT];
  //COMPUTE NEXT GEN
  for (uint32_t i = 0; i < WIDTH; i++){
    for (uint32_t j = 0; j < HEIGHT; j++) {
      uint32_t state = grid[i][j];
      //CHECK IF THE CELL IS ON THE EDGE 
      uint32_t neighbors = count_neighbors(grid, i, j);
      //RULES
      if (state == DEAD && neighbors == 3) 
        next[i][j] = ALIVE;
      else if (state == ALIVE && (neighbors < 2 || neighbors > 3)) 
        next[i][j] = DEAD;
      else 
        next[i][j] = state;
    }
  } 
  memcpy(grid, next, HEIGHT * WIDTH * sizeof(uint32_t));
}

