#include <fstream>
#include <cstring>
#include <algorithm>
#include <iostream>

constexpr int num_size = 13107200;
int nums[num_size];

int main(int argc, char const* argv[]) {
    std::memset(nums, 0, sizeof(nums));
    for (int i = -num_size/2,j=0; j<num_size; i++,j++){
        nums[j] = i;
    }
    std::cout << "Init ends;"<< std::endl;

    std::ofstream std_file;
    std_file.open("std_file.in");
    for (int i : nums){
        std_file << i << "\n";
    }
    std_file << std::endl;
    std_file.close();
    std::cout << "Std_file ends;" << std::endl;

    std::random_shuffle(nums, nums + num_size);
    std::cout << "Has shuffle the nums;"<< std::endl;

    std::ofstream out_file;
    out_file.open("rand_int.in");
    for (int i : nums){
        out_file << i << "\n";
    }
    out_file << std::endl;
    out_file.close();
    std::cout << "Ends."<< std::endl;


    return 0;
}
