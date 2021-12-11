#include <cstdio>
#include <string>
#include <fstream>

#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10

int
index2DTo1D(int x, int y)
{
  return y * GRID_SIZE_X + x;
}

// Recursive function to increase energy and return the number
// of flashes it created
int
increase_energy(int* octopuses, int x, int y)
{

  int index = index2DTo1D(x, y);
  int result = 0;

  // if octopus is marked, it already flashed
  if (octopuses[index] == -1) {
    return result;
  }

  // Energy level is not high enough for flashing
  if (octopuses[index] != 9) {
    octopuses[index]++;
    return result;
  }

  // Flash
  result++;
  octopuses[index] = -1;

  for (int j = -1; j <= 1; j++) {
    for(int i = -1; i <= 1; i++) {
      if (i == 0 && j == 0) continue;
      int index_x = x + i;
      int index_y = y + j;

      // Edge cases
      if (index_x < 0) continue;
      if (index_y < 0) continue;
      if (index_x >= GRID_SIZE_X) continue;
      if (index_y >= GRID_SIZE_Y) continue;
      
      result += increase_energy(octopuses, index_x, index_y);
    }
  }

  return result;
}

int main(int argc, char** argv) {

  std::string filename = "input.txt";

  if (argc > 1) {
    filename = argv[1];
  }

  // Parse File
  std::string line;

  std::ifstream stream(filename, std::ifstream::in);

  if (!stream.is_open()) {
    fprintf(stderr, "Failed to open file");
    exit(1);
  }

  // Calculate space for and read in 100 octopuses
  const int GRID_SIZE = GRID_SIZE_X * GRID_SIZE_Y;

  int* octopuses = (int*)malloc(sizeof(int) * GRID_SIZE);
  int* octo_ptr = octopuses;

  while(getline(stream, line)) {

    for (char c : line) {
      octo_ptr[0] = (int)c - 48;
      octo_ptr++;
    }

  }

  // count steps in result
  int result = 0;

  // Simulate steps until all_flashed condition is true
  while(1) {
    result++;

    for(int j = 0; j < GRID_SIZE_Y; j++) {
      for(int i = 0; i < GRID_SIZE_X; i++) {
	increase_energy(octopuses, i, j);
      }
    }

    // Assume that all flashed first
    bool all_flashed = true;

    // Reset marked octopuses
    for(int i = 0; i < GRID_SIZE; i++) {
      if (octopuses[i] != -1) {
	all_flashed = false;
      } else {
	octopuses[i] = 0;
      }
    }

    if(all_flashed) break;

  }

  free(octopuses);

  printf("Success: %d\n", result);

  return 0;
}
