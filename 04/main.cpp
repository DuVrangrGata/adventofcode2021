#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

int main() {

  std::string line, str_instructions;

  std::ifstream stream("input.txt", std::ifstream::in);

  if (!stream.is_open()) {
    fprintf(stderr, "Failed to open file");
    exit(1);
  }

  // get size of file
  stream.seekg(0, stream.end);
  int length = stream.tellg();
  stream.seekg(0, stream.beg);

  // The first line contains the instructions
  getline(stream, str_instructions);

  // unknown num of instructions
  std::vector<int> instructions;

  // Read in instructions
  size_t pos;
  while((pos = str_instructions.find(',')) != std::string::npos) {
    int instruction = std::stoi(str_instructions.substr(0, pos));
    str_instructions.erase(0, pos + 1);
    instructions.push_back(instruction);
  }

  // One Last Instruction, it is not found because it does not end with ','
  int instruction = std::stoi(str_instructions);
  instructions.push_back(instruction);

  // Eat first newline
  stream.ignore(1, '\n');

  // Reserve enough space for the string to contain the whole file
  length -= str_instructions.length();

  std::string string_boards = "";
  string_boards.reserve(length);

  int num_of_lines = 0;

  // Save all lines in one big string and count the number of lines
  while (getline(stream, line)) {

    if (line.length() == 0) {
      continue;
    }

    string_boards += line + ' ';

    num_of_lines++;

  }

  int num_to_parse = 5 * num_of_lines;
  //int num_of_boards = num_of_lines / 5;

  // This will contain all boards ->  5 Numbers * num of lines
  int* int_boards = (int*)malloc(sizeof(int) * num_to_parse);

  // Read in all integers with stringstream
  // There might be a more efficient way of doing this
  std::stringstream ss(string_boards);

  int* ptr = int_boards;
  int temp;

  while (ss >> temp) {
    *ptr = temp;
    ptr++;
  }


  int result = 0;
  for (int inst : instructions) {
    for(int i = 0; i < num_to_parse; i++) {
      if (int_boards[i] == inst) {

	// Mark number
	int_boards[i] = -1;

	// Check for bingo

	// Get Index of Row
	int index_line = (i % 25) / 5;

	// Get Index in Line
	int index_in_line = i % 5;

	// Check for horizontal BINGO
	bool horizontal_bingo = true;

	if (int_boards[i - index_in_line] != -1)     horizontal_bingo = false;
	if (int_boards[i - index_in_line + 1] != -1) horizontal_bingo = false;
	if (int_boards[i - index_in_line + 2] != -1) horizontal_bingo = false;
	if (int_boards[i - index_in_line + 3] != -1) horizontal_bingo = false;
	if (int_boards[i - index_in_line + 4] != -1) horizontal_bingo = false;

	// Check for vertical BINGO
	bool vertical_bingo = true;

	if (int_boards[i - (index_line * 5)] != -1)          vertical_bingo = false;
	if (int_boards[i - (index_line * 5) + 5] != -1)      vertical_bingo = false;
	if (int_boards[i - (index_line * 5) + 10] != -1)     vertical_bingo = false;
	if (int_boards[i - (index_line * 5) + 15] != -1)     vertical_bingo = false;
	if (int_boards[i - (index_line * 5) + 20] != -1)     vertical_bingo = false;

	// When no bingo no party
	if (!(vertical_bingo || horizontal_bingo)) continue;

	// Iterate over the 25 board indicies
	int start_board_index = i - (index_line * 5) - index_in_line;

	for (int j = 0; j < 25; j++) {
	  int value = int_boards[start_board_index + j];
	  if (value == -1) continue;
	  result += value;
	}

	break;
      }
    }
    
    if (result != 0) {
      result *= inst;
      break;
    }
  }

  free(int_boards);

  fprintf(stdout, "Success: %d", result);

  return 0;
}
