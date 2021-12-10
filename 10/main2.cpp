#include <cstdio>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>

typedef unsigned long long u64;

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

  // ints may overflow
  std::vector<u64> results;

  while(getline(stream, line)) {

    // Allocate enough memory to just copy the whole line
    // this can happen when there are just opening chars
    char* c_line = (char*)malloc(sizeof(char) * line.length() + 1) ;

    u64 result = 0;

    // Stack index
    int index = 0;

    for (size_t i = 0; i < line.length(); i++) {
      // Opening char
      if (line[i] == '{' || line[i] == '[' || line[i] == '(' || line[i] == '<') {
	// Push Stack
	c_line[index] = line[i];
	index++;
	continue;
      }

      // Incorrect closing char
      if ((line[i] == '}' && c_line[index - 1] != '{') ||
	  (line[i] == ']' && c_line[index - 1] != '[') ||
	  (line[i] == ')' && c_line[index - 1] != '(') ||
	  (line[i] == '>' && c_line[index - 1] != '<')) {
	c_line[0] = 'm';
	break;
      }

      // Correct closing char
      // Pop stack
      index--;
    }

    if (c_line[0] == 'm') continue;

    // Rest of stack
    c_line[index] = '\0';

    // Traverse rest of stack backwards
    for(; index >= 0; --index) {

      if (c_line[index] == '(') result = result * 5 + 1;
      if (c_line[index] == '[') result = result * 5 + 2;
      if (c_line[index] == '{') result = result * 5 + 3;
      if (c_line[index] == '<') result = result * 5 + 4;

    }

    results.push_back(result);

    free(c_line);
  }

  // odd size of results is guaranteed
  sort(results.begin(), results.end());
  int middle_index = results.size() / 2;

  printf("Success: %lld\n", results[middle_index]);

  return 0;
}
