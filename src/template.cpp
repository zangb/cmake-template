#include "template/template.hpp"

namespace dummy {
auto greater_than(int a, int b) -> bool {
    if(a > b)
        return true;
    else
        return false;
}
}    // namespace dummy
