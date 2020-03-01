#include <iostream>
#include <vector>
#include <random>
#include <iterator>
std::vector<std::vector<int>> circulant_generator(int num, int cirsize);
std::vector<std::vector<int>> column_generator(std::vector<int> column_vector, int cirsize);
void add_new_colum_circulant(std::vector<std::vector<int>> & parity_check, std::vector<std::vector<int>> &new_column_circulant);