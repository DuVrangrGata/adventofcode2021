#include <cstdio>
#include <string>
#include <fstream>
#include <cstring>

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

  int result = 0;

  while(getline(stream, line)) {

    // Allocate enough memory to just copy the whole line
    // this can happen when there are just opening chars
    char* c_line = (char*)malloc(sizeof(char) * line.length() + 1) ;

    // Stack index
    size_t index = 0;

    for (size_t i = 0; i < line.length(); i++) {
      // Opening char
      if (line[i] == '{' || line[i] == '[' || line[i] == '(' || line[i] == '<') {
	// Push Stack
	c_line[index] = line[i];
	index++;
	continue;
      }

      // Incorrect closing char
      if (line[i] == '}' && c_line[index - 1] != '{') {
	result += 1197;
	break;
      }

      if (line[i] == ']' && c_line[index - 1] != '[') {
	result += 57;
	break;
      }
      
      if (line[i] == ')' && c_line[index - 1] != '(') {
	result += 3;
	break;
      }

      if (line[i] == '>' && c_line[index - 1] != '<') {
	result += 25137;
	break;
      }

      // Correct closing char
      // Pop stack
      index--;
    }

    free(c_line);
  }

  printf("Success: %d\n", result);

  return 0;
}
