#include <iostream>
#include <memory>
#include <unordered_map>

class A {
    public:
        void hello() {
            std::cout << "Hello" << std::endl;
        }
};

int main() {
    std::unordered_map< std::string, std::unique_ptr<A> > as;
    if (as["teste"] == nullptr) {
        as["teste"] = std::make_unique<A>();
    }
    as["teste"]->hello();
    as["teste"]->hello();
    as["teste"]->hello();
    as["teste"]->hello();
    return 0;
}
