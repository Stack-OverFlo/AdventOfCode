#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdbool.h>
#include <ios>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>

int get_level(std::string line)
{
  int value;
  int a = -1;
  int b = -1;
  int diff_ab;
  int count_diff_ok = 0;
  std::vector<int> values_line;
  std::istringstream stream(line);
  while (stream >> value) {
    if (stream.fail())
      break;
    values_line.push_back(value);
  }
  if (!(std::is_sorted(values_line.begin(), values_line.end())) &&
      !(std::is_sorted(values_line.rbegin(), values_line.rend())))
    return 0;
  for (auto it = values_line.begin() ; it != values_line.end() ; it++) {
    if (a == -1) {
      a = *it;
    } else {
      a = b;
    }
    b = *it;
    diff_ab = std::abs(a - b);
    if (diff_ab >= 1 && diff_ab <= 3)
      count_diff_ok++;
  }
  return (count_diff_ok == values_line.size() - 1) ? 1 : 0;
}

void read_file(std::string file)
{
  std::ifstream input;
  std::string line;
  std::stringstream stream(file);
  int safe_path = 0;
  input.open(file);
  while (input) {
    std::getline(input, line);
    safe_path += get_level(line);
  }
  input.close();
  std::cout << safe_path << std::endl;
}

int main(int ac, const char *av[])
{
  if (ac != 2) {
    std::cerr << "Usage: ./day02_part1 input/input.txt\n";
    return 1;
  }
  read_file(av[1]);
  return 0;
}
