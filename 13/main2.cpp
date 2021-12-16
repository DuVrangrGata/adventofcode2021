#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

struct point {
  int x;
  int y;
};

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

  // unknown num of points
  std::vector<point> points;
  std::vector<std::string> instructions;

  int high_x = -1;
  int high_y = -1;

  while(getline(stream, line)) {

    if (line.length() == 0) continue;

    // parse instructions
    if (line.starts_with("fold along")) {
      instructions.push_back(line.substr(11, 14));
      continue;
    }

    // parse points
    int pos = line.find(',');

    int x = std::stoi(line.substr(0, pos));
    int y = std::stoi(line.substr(pos + 1, std::string::npos));

    // keep track of outer bounds
    if (x > high_x) high_x = x;
    if (y > high_y) high_y = y;

    points.push_back(point{x, y});

  }

  // zero indexing
  high_x++;
  high_y++;

  // initialize paper mem struct and insert points
  const size_t MAX_X = high_x;
  const size_t PAPER_SIZE = high_x * high_y;

  bool* paper = (bool*)malloc(sizeof(bool) * PAPER_SIZE);
  memset(paper, 0, sizeof(bool) * PAPER_SIZE);

  for (point p : points) {
    paper[p.y * high_x + p.x] = 1;
  }

  //parse instruction
  for (std::string instruction : instructions) {
    char mode = instruction[0];
    int line_to_fold = std::stoi(instruction.substr(2, std::string::npos));

    if (mode == 'y') {
      for (int y = 0; y < line_to_fold; y++) {
  	for (int x = 0; x < high_x; x++) {
	  // calculate point mirrored by line_to_fold
	  // for each point above line_to_fold
  	  int new_y = line_to_fold + line_to_fold - y;
	  // if that mirrored point is 1, set it to 0
	  // and set the inital point to 1
  	  if (paper[new_y * MAX_X + x] == 1) {
  	    paper[y * MAX_X + x] = 1;
  	    paper[new_y * MAX_X + x] = 0;
  	  }

  	}
      }
      // update size of paper to consider
      high_y = line_to_fold;
    // mode x
    } else {
      for (int y = 0; y < high_y; y++) {
  	for (int x = 0; x < line_to_fold; x++) {
	  // calculate point mirrored by line_to_fold
	  // for each point to the right of line_to_fold
  	  int new_x = line_to_fold + line_to_fold - x;
	  // if that mirrored point is 1, set it to 0
	  // and set the inital point to 1
  	  if (paper[y * MAX_X + new_x] == 1) {
  	    paper[y * MAX_X + x] = 1;
  	    paper[y * MAX_X + new_x] = 0;
  	  }

  	}
      }
      // update size of paper to consider
      high_x = line_to_fold;
    }

  }

  // print remaining mem to stdout
  // read capital letters from stdout
  for (int j = 0; j < high_y; j++) {
    for (int i = 0; i < high_x; i++) {
      printf("%d ", paper[j * MAX_X + i]);
    }
    printf("\n");
  }

  return 0;
}
