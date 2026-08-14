#pragma once

#include <functional>
#include <vector>

template <typename T, typename Op>
class SegmentTree {
public:
    SegmentTree(const std::vector<T>& data, Op op, T identity)
        : n_(static_cast<int>(data.size())),
          op_(std::move(op)),
          identity_(identity),
          tree_(4 * n_, identity_) {
        if (n_ > 0) {
            build(data, 0, 0, n_ - 1);
        }
    }

    T query(int left, int right) const {
        return query(0, 0, n_ - 1, left, right);
    }

    void update(int index, T value) {
        update(0, 0, n_ - 1, index, value);
    }

private:
    int n_;
    Op op_;
    T identity_;
    std::vector<T> tree_;

    void build(const std::vector<T>& data, int node, int start, int end) {
        if (start == end) {
            tree_[node] = data[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(data, 2 * node + 1, start, mid);
        build(data, 2 * node + 2, mid + 1, end);
        tree_[node] = op_(tree_[2 * node + 1], tree_[2 * node + 2]);
    }

    T query(int node, int start, int end, int left, int right) const {
        if (right < start || end < left) {
            return identity_;
        }
        if (left <= start && end <= right) {
            return tree_[node];
        }
        int mid = start + (end - start) / 2;
        return op_(
            query(2 * node + 1, start, mid, left, right),
            query(2 * node + 2, mid + 1, end, left, right));
    }

    void update(int node, int start, int end, int index, T value) {
        if (start == end) {
            tree_[node] = value;
            return;
        }
        int mid = start + (end - start) / 2;
        if (index <= mid) {
            update(2 * node + 1, start, mid, index, value);
        } else {
            update(2 * node + 2, mid + 1, end, index, value);
        }
        tree_[node] = op_(tree_[2 * node + 1], tree_[2 * node + 2]);
    }
};

using SumSegmentTree = SegmentTree<long long, std::plus<long long>>;

inline SumSegmentTree make_sum_segment_tree(const std::vector<long long>& data) {
    return SumSegmentTree(data, std::plus<long long>{}, 0LL);
}
