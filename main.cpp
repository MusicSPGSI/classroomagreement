#include <iostream>
#include <vector>

#include "segment_tree.hpp"

int main() {
    std::vector<long long> arr = {1, 3, 5, 7, 9, 11};

    SumSegmentTree st = make_sum_segment_tree(arr);

    std::cout << "Sum of [1, 3]: " << st.query(1, 3) << '\n';  // 3 + 5 + 7 = 15
    std::cout << "Sum of [0, 5]: " << st.query(0, 5) << '\n';  // 36

    st.update(2, 10);  // arr[2]: 5 -> 10
    std::cout << "Sum of [1, 3] after update: " << st.query(1, 3) << '\n';  // 3 + 10 + 7 = 20

    return 0;
}
