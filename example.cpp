#include <iostream>
#include "include/setting.hpp"

using namespace so;
using namespace std;

int main() {
    auto a = json::parse(R"({"a":{"b":1,"c":2},"b":1})");
    auto b = json::parse(R"({"a":{"b":2,"d":4},"b":2})");
    std::cout << merge(a, b).stringify();

    return 0;
}
