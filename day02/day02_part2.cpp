#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>

const int MIN_DIFF = 1;
const int MAX_DIFF = 3;

bool check_if_safe(std::vector<int> level)
{
  for (size_t i = 1; i < level.size(); ++i) {
    int diff_ab = std::abs(level[i] - level[i - 1]);
    if (diff_ab < MIN_DIFF || diff_ab > MAX_DIFF)
      return false;
  }
  return true;
}

bool check_if_sorted(std::vector<int> level)
{
  bool is_sorted_ascending = true;
  bool is_sorted_descending = true;

  for (size_t i = 1; i < level.size(); ++i) {
    if (level[i] < level[i - 1])
      is_sorted_ascending = false;
    if (level[i] > level[i - 1])
      is_sorted_descending = false;
  }
  return is_sorted_ascending || is_sorted_descending;
}

bool check_level_validity(std::vector<int> level)
{
  bool is_sorted = false;
  bool is_safe = false;

  is_sorted = check_if_sorted(level);
  is_safe = check_if_safe(level);
  return is_sorted && is_safe ? true : false;
}

bool test_bad_level(const std::vector<int> level)
{
  bool is_good_level = false;
  for (size_t i = 0; i < level.size(); ++i) {
      std::vector<int> shortened_level = level;
      shortened_level.erase(shortened_level.begin() + i);
      if (check_level_validity(shortened_level)) {
	is_good_level = true;
      }
  }
  return is_good_level;
}

int get_level(const std::string &line) {
    int value;
    std::vector<int> values_line;
    std::istringstream stream(line);

    while (stream >> value)
      values_line.push_back(value);
    if (values_line.size() < 2 ||
	(!check_level_validity(values_line) && !test_bad_level(values_line)))
      return 0;
    std::cout << "la validité de base est : " << check_level_validity(values_line) << std::endl;
    std::cout << "la validité avec tolerance  est : " << test_bad_level(values_line) << std::endl;
    return 1;
}

void read_file(const std::string& file) {
    std::string line;
    int safe_path = 0;
    std::ifstream input(file);
    if (!input.is_open()) {
        std::cerr << "Error: Failed to open file: " << file << std::endl;
        return;
    }
    while (std::getline(input, line)) {
      if (!line.empty()) 
	safe_path += get_level(line);
    }
    input.close();
    std::cout << safe_path << std::endl;
}

int main(int ac, const char *av[]) {
  if (ac != 2) {
    std::cerr << "Usage: ./day02_part1 <input_file>\n";
        return 1;
  }
  read_file(av[1]);
  return 0;
}
