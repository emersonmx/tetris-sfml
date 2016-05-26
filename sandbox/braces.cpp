#include <iostream>
#include <array>

struct Object {
    int x;
    int y;
};

class A {
    public:
        A() {
            std::cout << "A()" << std::endl;
        }

        int a;
};

int main() {
    using Block = std::array<char, 4>;
    float a;
    float b{};
    A oa;
    A ob{};
    std::array<Block, 4> blocks {{
        {
            {'.', '#', '.', '.'}
        },
        {
            {'.', '#', '.', '.'}
        },
        {
            {'.', '#', '.', '.'}
        },
        {
            {'.', '#', '.', '.'}
        }
    }};

    std::cout << "Block" << std::endl;
    for (auto& block : blocks) {
        for (auto& b : block) {
            std::cout << b;
        }
        std::cout << std::endl;
    }

    Block bl;
    std::cout << "Block" << std::endl;
    for (auto& i : bl) {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;

    Block bk{};
    std::cout << "Block" << std::endl;
    for (auto& i : bk) {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Init test" << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << oa.a << std::endl;
    std::cout << ob.a << std::endl;

    return 0;
}
