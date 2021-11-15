#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define WIDTH  40
#define HEIGHT 40

#define DEAD_ASCII  "\u25a1"
#define ALIVE_ASCII "\u25A0"
#define DEAD  0
#define ALIVE 1

//function deeclarations 
void delay( uint32_t milliseconds );
void print_grid( uint8_t grid[][HEIGHT] );
void game( uint8_t grid[][HEIGHT] );
uint8_t count_neighbors( uint8_t grid[][HEIGHT], uint32_t x, uint32_t y );
static void load_grid_from_file();

int 
main( void ) 
{
  //init the grid by reading from a file
  uint8_t grid[WIDTH][HEIGHT];
  load_grid_from_file(grid, "grid.txt");
  
  //main loop
  while (1) {
    system("clear");
    print_grid(grid);
    game(grid);
    delay(100);
  }  

  return 0;
}

static void 
load_grid_from_file( uint8_t grid[][HEIGHT],  const char * filename ) 
{
  FILE *file;
  char *line, *number;
  uint32_t i = 0, j;
  file = fopen(filename, "r");
  while (!feof(file)) {
    j = 0;
    fscanf(file, "%s", line);
    number = strtok(line, ",");
    
    while(number != NULL) {
      grid[i][j] = atoi(number);
      j++;
      number = strtok(NULL, ","); 
    }
    i++;
  }
  fclose(file);
}

void 
delay( uint32_t milliseconds )
{
    uint64_t pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

// PRINT ARRAY
void 
print_grid( uint8_t grid[][HEIGHT] ) 
{
  for (uint32_t i = 0; i < WIDTH; i++){
    for (uint32_t j = 0; j < HEIGHT; j++) {
      if (grid[i][j] == ALIVE)
        printf("%s", ALIVE_ASCII);
      else
        printf("%s", DEAD_ASCII);
      printf("%s", " ");
    }
    printf("%s", "\n");
  }   
}

//finds the number of neighbors
uint8_t 
count_neighbors( uint8_t grid[][HEIGHT], uint32_t x, uint32_t y ) {
  uint8_t sum = 0;
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

void 
game( uint8_t grid[][HEIGHT] ) {
  uint8_t next[WIDTH][HEIGHT];
  for (uint32_t i = 0; i < WIDTH; i++){
    for (uint32_t j = 0; j < HEIGHT; j++) {
      uint8_t state = grid[i][j];
      uint8_t neighbors = count_neighbors(grid, i, j);
      //apply the rules 
      if (state == DEAD && neighbors == 3) 
        next[i][j] = ALIVE;
      else if (state == ALIVE && (neighbors < 2 || neighbors > 3)) 
        next[i][j] = DEAD;
      else 
        next[i][j] = state;
    }
  } 
  memcpy(grid, next, HEIGHT * WIDTH * sizeof(uint8_t));
}

