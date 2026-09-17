#include <iostream>
#include <vector>

int main()
{
    int N = 2;
    int C = 3;
    int H = 2;
    int W = 2;

    std::vector<float> tensor = {
        // 第 0 张图片
        1,  2,  3,  4,
        5,  6,  7,  8,
        9, 10, 11, 12,

        // 第 1 张图片
        13, 14, 15, 16,
        17, 18, 19, 20,
        21, 22, 23, 24
    };

    int n = 1;
    
    int c = 0;
    int h = 1;
    int w = 1;

    int index = ((n * C + c) * H + h) * W + w;

    std::cout << "index = " << index << std::endl;
    std::cout << "value = " << tensor[index] << std::endl;

    return 0;
}