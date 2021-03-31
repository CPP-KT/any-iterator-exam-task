#include "gtest/gtest.h"

#include "any_iterator.h"
#include <iterator>

#include <vector>
#include <map>
#include <forward_list>

template struct any_iterator<int, std::input_iterator_tag>;
template struct any_iterator<int, std::output_iterator_tag>;
template struct any_iterator<int, std::forward_iterator_tag>;
template struct any_iterator<int, std::bidirectional_iterator_tag>;
template struct any_iterator<int, std::random_access_iterator_tag>;

std::vector<int> a = {4, 8, 15, 16, 23, 42};

template<typename T>
using random_iterator = any_iterator<T, std::random_access_iterator_tag>;

TEST(random, simple) {
    random_iterator<int> it(a.begin() + 1);
    ASSERT_EQ(*it, 8);
}

TEST(random, comparison) {
    random_iterator<int> it1(a.begin() + 1);
    random_iterator<int> it2(a.begin());

    ASSERT_NE(it1, it2);
    ASSERT_GT(it1, it2);

    random_iterator<int> it3(a.begin());
    random_iterator<int> it4(it2);

    ASSERT_EQ(it2, it3);
    ASSERT_EQ(it3, it4);

    random_iterator<int> it5(a.end() - 1);

    ASSERT_LT(it1, it5);
}

TEST(random, operations) {
    random_iterator<int> it1(a.begin());

    ASSERT_EQ(*it1, 4);

    random_iterator<int> it2(a.begin() + 2);

    ASSERT_EQ(*it2, 15);
    ASSERT_EQ(it1 + 2, it2);
    ASSERT_EQ(it2 - 2, it1);

    ASSERT_EQ(--it2, ++it1);
    ASSERT_EQ(it2, it1);

    random_iterator<int> it3(a.end());
    it3 -= a.size() - 1;

    ASSERT_EQ(it3, it1);

    it2++;
    it3.swap(it2);
    ASSERT_EQ(it3, ++it1);
}

TEST(random, moves) {
    random_iterator<int> it1(a.begin());
    it1 += 3;
    random_iterator<int> it2(std::move(it1));

    ASSERT_EQ(it2, random_iterator<int>(a.begin() + 3));
}

struct bad_element {
    void huligan() {
        throw std::exception();
    }

    double pi() {
        return 3;
    }
};

TEST(random, bad_and_arrow) {
    std::vector<bad_element> bad_vector = {bad_element(), bad_element()};
    random_iterator<bad_element> it1(bad_vector.begin());

    ASSERT_THROW(it1->huligan(), std::exception);
    ASSERT_EQ((it1 + 1)->pi(), 3.);
}

template<typename T>
using bi_iterator = any_iterator<T, std::bidirectional_iterator_tag>;

std::set<double> b = {1.1, 3.14, 2.7, 5.782};

TEST(bidirectional, simple) {
    bi_iterator<const double> it(b.begin());

    ASSERT_EQ(*it, 1.1);
    ASSERT_EQ(*(++it), 2.7);
}

TEST(bidirectional, comparison) {
    bi_iterator<const double> it1(++b.begin());
    bi_iterator<const double> it2(b.begin());

    ASSERT_NE(it1, it2);

    bi_iterator<const double> it3(b.begin());
    bi_iterator<const double> it4(it2);

    ASSERT_EQ(it2, it3);
    ASSERT_EQ(it3, it4);
}

TEST(bidirectional, operations) {
    bi_iterator<const double> it(b.begin());
    bi_iterator<const double> it2(++++b.begin());

    ASSERT_EQ(*it++, 1.1);
    ASSERT_EQ(*it++, 2.7);
    ASSERT_EQ(it, it2);
    ASSERT_EQ(*it--, 3.14);
    ASSERT_EQ(*it, 2.7);
}

template <typename T>
using fw_iterator = any_iterator<T, std::forward_iterator_tag>;

std::forward_list<int> c = {1, 2, 3};

TEST(forward, simple) {
    fw_iterator<int> it(c.begin());

    ASSERT_EQ(*it++, 1);
    ASSERT_EQ(*it, 2);
}

