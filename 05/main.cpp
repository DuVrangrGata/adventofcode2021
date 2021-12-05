#include <cstdio>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

struct instruction {
  int x1;
  int y1;
  int x2;
  int y2;
};

int
parse_int_and_eat_characters_to_delim(std::string& to_parse, char delim)
{
    size_t pos = to_parse.find(delim);

    int result = std::stoi(to_parse.substr(0, pos));

    to_parse.erase(0, pos + 1);

    return result; 
}

void
increment_value_in_2D_array(int* mem, int x, int max_x, int y)
{
  mem[(y * max_x) + x]++;
}

int main() {

  std::string line;

  std::ifstream stream("input.txt", std::ifstream::in);

  if (!stream.is_open()) {
    fprintf(stderr, "Failed to open file");
    exit(1);
  }

  // Unknown num of instructions
  std::vector<instruction> instructions;

  int biggest_x = 0;
  int biggest_y = 0;

  // Save instructions and calculate bounds for the memory allocation
  while (getline(stream, line)) {

    instruction temp;

    temp.x1 = parse_int_and_eat_characters_to_delim(line, ',');
    if (temp.x1 > biggest_x) biggest_x = temp.x1;

    temp.y1 = parse_int_and_eat_characters_to_delim(line, '>');
    if (temp.y1 > biggest_y) biggest_y = temp.y1;

    temp.x2 = parse_int_and_eat_characters_to_delim(line, ',');
    if (temp.x2 > biggest_x) biggest_x = temp.x2;

    temp.y2 = parse_int_and_eat_characters_to_delim(line, '\n');
    if (temp.y2 > biggest_y) biggest_y = temp.y2;

    instructions.push_back(temp);

  }

  // Allocate memory to save lines from instructions in coord-like system
  // Save 2D Array as 1D
  size_t num_of_elements = biggest_x * biggest_y;
  size_t coords_size = sizeof(int) * num_of_elements;
  int* coords_mem = (int*)malloc(coords_size);
  memset(coords_mem, 0, coords_size);

  for (instruction inst : instructions) {
    if (inst.x1 == inst.x2) {
      // vertical line
      int smaller_y, bigger_y;

      if (inst.y1 > inst.y2) {
	smaller_y = inst.y2;
	bigger_y = inst.y1;
      } else {
	smaller_y = inst.y1;
	bigger_y = inst.y2;
      }

      for (; smaller_y <= bigger_y; smaller_y++) {
	increment_value_in_2D_array(coords_mem, inst.x1, biggest_x, smaller_y);
      }
    } else if (inst.y1 == inst.y2) {
      // horizontal line
      int smaller_x, bigger_x;

      if (inst.x1 > inst.x2) {
	smaller_x = inst.x2;
	bigger_x = inst.x1;
      } else {
	smaller_x = inst.x1;
	bigger_x = inst.x2;
      }

      for (; smaller_x <= bigger_x; smaller_x++) {
	increment_value_in_2D_array(coords_mem, smaller_x, biggest_x, inst.y1);
      }

    } else {
      // diagonal
      // ignore for now
    }
  }


  int result = 0;

  for (size_t i = 0; i < num_of_elements; i++) {
    if (coords_mem[i] > 1) result++;
  }
  
  free(coords_mem);

  fprintf(stdout, "Success: %d", result);

  return 0;
}
  
