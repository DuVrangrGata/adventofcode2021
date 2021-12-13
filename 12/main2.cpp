#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

enum cave_type {
  SMALL,
  BIG,
  START,
  END,
};

struct cave {
  std::string name;
  cave_type type = SMALL;
  std::vector<int> connections;
};

// parse the string name to initilize cave struct
bool
initialize_cave(cave& c, const std::string & name)
{
  c.name = name;

  if(name.compare("start") == 0) {
    c.type = START;
    return true;
  } else if(name.compare("end") == 0) {
    c.type = END;
    return false;
  }

  if(name[0] >= 'A' && name[0] <= 'Z') c.type = BIG;
  return false;
}

// recursivly check every option, mark already visited small caves
// keep track if we already visited a small cave twice
int
traverse(int pos, const std::vector<cave>& caves, std::vector<int> marked, bool visited_twice)
{

  // return 1 valid path when pos is end
  if (caves[pos].type == END) return 1;

  int result = 0;

  for(int option : caves[pos].connections) {

    // dont consider start point as an option ever
    if (caves[option].type == START) continue;

    // Check if option is a marked cave
    bool already_marked = false;

    for (int m : marked) {
      if (m == option) already_marked = true;
    }

    // mark small caves
    if (caves[pos].type != BIG) {
      marked.push_back(pos);
    }

    if (already_marked) {
      // if we have not yet visited a small cave twice
      // do it within another recursive call
      if (!visited_twice) 
	result += traverse(option, caves, marked, true);
      continue;
    }

    // go through every option counting num of pathes reaching end
    result += traverse(option, caves, marked, visited_twice);
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

  // Parse input into cave structs
  std::vector<cave> caves;
  // index of "start" cave
  int startPointIndex = -1;

  while(getline(stream, line)) {

    size_t pos = line.find('-');

    std::string cave1 = line.substr(0, pos);
    std::string cave2 = line.substr(pos + 1, std::string::npos);

    int cave1Index = -1;
    int cave2Index = -1;

    // Check if caves already exist
    for(size_t i = 0; i < caves.size(); i++) {
      if(caves[i].name.compare(cave1) == 0) cave1Index = i;
      if(caves[i].name.compare(cave2) == 0) cave2Index = i;
    }

    // Create Cave 1
    if (cave1Index == -1) {
      cave new_cave1;

      bool is_start_point = initialize_cave(new_cave1, cave1);

      caves.push_back(new_cave1);
      cave1Index = caves.size() - 1;

      if (is_start_point) startPointIndex = cave1Index;
    }

    // Create Cave2
    if (cave2Index == -1) {
      cave new_cave2;

      bool is_start_point = initialize_cave(new_cave2, cave2);

      caves.push_back(new_cave2);
      cave2Index = caves.size() - 1;

      if (is_start_point) startPointIndex = cave2Index;
    }

    // Add connections to caves
    caves[cave1Index].connections.push_back(cave2Index);
    caves[cave2Index].connections.push_back(cave1Index);
  }

  int result = 0;

  std::vector<int> marked;

  // Have we already visited a small cave twice
  bool visited_twice = false;

  // Take every traversal option from the start point recursivly
  result += traverse(startPointIndex, caves, marked, visited_twice);

  printf("Success: %d\n", result);

  return 0;
}
