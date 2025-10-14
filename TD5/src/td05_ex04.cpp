#include <iostream>
#include <windows.h>
#include <vector>

int average(std::vector<int> nums) {
    if (nums.empty()) return 0;
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }
    return sum / nums.size();
}

float average(std::vector<float> nums) {
    if (nums.empty()) return 0.0f;
    float sum = 0.0f;
    for (float num : nums) {
        sum += num;
    }
    return sum / nums.size();
}


int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD05 - EX04 -\n" << std::endl;

    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "La moyenne est : " << average(numbers) << std::endl;

    std::vector<float> float_numbers = {1.5, 2.5, 3.5, 4.5, 5.5};
    std::cout << "La moyenne est : " << average(float_numbers) << std::endl;

    return 0;
}