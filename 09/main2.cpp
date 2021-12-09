#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

// Recursively mark every point in every direction
// until you hit 9 or an already marked point
// and count the number of times points get marked
int
size_of_basin(std::vector<std::string> & lines, int x, int y, int max_x, int max_y)
{
  if (lines[y][x] == '9' || lines[y][x] == 'm') return 0;

  lines[y][x] = 'm';

  int result = 1;

  if (x > 0)     result += size_of_basin(lines, x - 1, y, max_x, max_y);
  if (x < max_x) result += size_of_basin(lines, x + 1, y, max_x, max_y);
  if (y > 0)     result += size_of_basin(lines, x, y - 1, max_x, max_y);
  if (y < max_y) result += size_of_basin(lines, x, y + 1, max_x, max_y);

  return result;
}

// Update the array of the three highest values
void
update_top_three(int* top_three, int new_basin)
{
  if (new_basin < top_three[0]) return;

  top_three[0] = new_basin;

  if (new_basin > top_three[1]) {
    top_three[0] = top_three[1];
    top_three[1] = new_basin;
  }
  if (new_basin > top_three[2]) {
    top_three[1] = top_three[2];
    top_three[2] = new_basin;
  }

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

  // Unknown num of lines at start
  std::vector<std::string> lines;

  while(getline(stream, line)) {
    lines.push_back(line);
  }


  int *top_three_ptr;
  int top_three[3] = {0};

  top_three_ptr = top_three;

  // Start recursion for every point that is not marked or a 9
  // Recursion should be started one time for each basin
  for (size_t j = 0; j < lines.size(); j++) {
    for (size_t i = 0; i < lines[j].length(); i++) {

      if (lines[j][i] == 'm' || lines[j][i] == '9') continue;

      int basin = size_of_basin(lines, i, j, lines[j].length() - 1, lines.size() - 1);

      update_top_three(top_three_ptr, basin);
    }
  }

  int result = 1;
  for (int i : top_three) result *= i;

  printf("Success: %d\n", result);
  return 0;
}
