#include "any-iterator.h"

#include <gtest/gtest.h>

#include <concepts>
#include <forward_list>
#include <iterator>
#include <vector>

template struct any_iterator<int, std::forward_iterator_tag>;
template struct any_iterator<int, std::bidirectional_iterator_tag>;
template struct any_iterator<int, std::random_access_iterator_tag>;

std::vector a = {4, 8, 15, 16, 23, 42};

template <typename T>
using random_iterator = any_iterator<T, std::random_access_iterator_tag>;

template <typename Iter>
concept decrementable = requires(Iter x) {
  x--;
  --x;
  { x-- } -> std::same_as<Iter>;
  { --x } -> std::same_as<Iter&>;
};

static_assert(std::random_access_iterator<random_iterator<int>>);

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

template <typename T>
using bi_iterator = any_iterator<T, std::bidirectional_iterator_tag>;

static_assert(std::bidirectional_iterator<bi_iterator<int>>);
static_assert(!std::random_access_iterator<bi_iterator<int>>);
static_assert(decrementable<bi_iterator<int>>);

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
  bi_iterator<const double> it2(++ ++b.begin());

  ASSERT_EQ(*it++, 1.1);
  ASSERT_EQ(*it++, 2.7);
  ASSERT_EQ(it, it2);
  ASSERT_EQ(*it--, 3.14);
  ASSERT_EQ(*it, 2.7);
}

template <typename T>
using fw_iterator = any_iterator<T, std::forward_iterator_tag>;

static_assert(std::forward_iterator<fw_iterator<int>>);
static_assert(!std::bidirectional_iterator<fw_iterator<int>>);
static_assert(!decrementable<fw_iterator<int>>);

std::forward_list<int> c = {1, 2, 3};

TEST(forward, simple) {
  fw_iterator<int> it(c.begin());

  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it, 2);
}

struct copy_move_counter {
  constexpr copy_move_counter() = default;

  copy_move_counter(const copy_move_counter&) {
    n_copies++;
  }

  copy_move_counter(copy_move_counter&&) noexcept {
    n_moves++;
  }

  copy_move_counter& operator=(const copy_move_counter&) {
    n_copies++;
    return *this;
  }

  copy_move_counter& operator=(copy_move_counter&&) noexcept {
    n_moves++;
    return *this;
  }

  bool operator==(const copy_move_counter&) const {
    return true;
  }

  copy_move_counter& operator++() {
    return *this;
  }

  copy_move_counter operator++(int) {
    return *this;
  }

  copy_move_counter& operator--() {
    return *this;
  }

  copy_move_counter operator--(int) {
    return *this;
  }

  int& operator*() const {
    return magic;
  }

  int* operator->() const {
    return &magic;
  }

  copy_move_counter& operator+=(ptrdiff_t) {
    return *this;
  }

  copy_move_counter& operator-=(ptrdiff_t) {
    return *this;
  }

  copy_move_counter operator+(ptrdiff_t) const {
    return {};
  }

  ptrdiff_t operator-(const copy_move_counter&) const {
    return 0;
  }

  bool operator<(const copy_move_counter&) const {
    return false;
  }

  bool operator<=(const copy_move_counter&) const {
    return false;
  }

  bool operator>(const copy_move_counter&) const {
    return false;
  }

  bool operator>=(const copy_move_counter&) const {
    return false;
  }

  bool operator!=(const copy_move_counter&) const {
    return true;
  }

  int& operator[](ptrdiff_t) {
    return magic;
  }

  int& operator[](ptrdiff_t) const {
    return magic;
  }

  static int magic;
  static thread_local size_t n_copies;
  static thread_local size_t n_moves;
};

int copy_move_counter::magic = 17;
thread_local size_t copy_move_counter::n_copies = 0;
thread_local size_t copy_move_counter::n_moves = 0;

template <typename T>
class FwTypeFixture : public testing::Test {};

using FwIteratorTestTags =
    ::testing::Types<std::forward_iterator_tag, std::bidirectional_iterator_tag, std::random_access_iterator_tag>;

TYPED_TEST_SUITE(FwTypeFixture, FwIteratorTestTags);

TYPED_TEST(FwTypeFixture, FwIterCopyChecks) {
  const auto initial_copies = copy_move_counter::n_copies;

  any_iterator<int, TypeParam> iter = copy_move_counter(), other;
  auto iter2 = iter;
  ASSERT_EQ(copy_move_counter::n_copies, initial_copies + 1);
  auto iter3(iter2);
  ASSERT_EQ(copy_move_counter::n_copies, initial_copies + 2);
  any_iterator<int, TypeParam> iter4;
  iter4 = iter3;
  ASSERT_EQ(copy_move_counter::n_copies, initial_copies + 3);
  iter4++;
  ASSERT_EQ(copy_move_counter::n_copies, initial_copies + 4);
  ++iter4;
  ASSERT_EQ(copy_move_counter::n_copies, initial_copies + 4);
  iter3 = iter3;
  ASSERT_EQ(copy_move_counter::n_copies, initial_copies + 5);
}

TYPED_TEST(FwTypeFixture, FwIterMoveChecks) {
  any_iterator<int, TypeParam> iter = copy_move_counter(), other;

  const auto initial_moves = copy_move_counter::n_moves;
  iter = std::move(iter);
  ASSERT_EQ(copy_move_counter::n_moves, initial_moves);
  other = std::move(iter);
  ASSERT_EQ(copy_move_counter::n_moves, initial_moves + 1);
}

template <typename T>
class BiTypeFixture : public testing::Test {};

using BiIteratorTestTags = ::testing::Types<std::bidirectional_iterator_tag, std::random_access_iterator_tag>;

TYPED_TEST_SUITE(BiTypeFixture, BiIteratorTestTags);

TYPED_TEST(BiTypeFixture, BiIterCopyChecks) {
  const auto initial_copies = copy_move_counter::n_copies;

  any_iterator<int, TypeParam> iter = copy_move_counter();
  ASSERT_EQ(copy_move_counter::n_copies, initial_copies);
  iter--;
  ASSERT_EQ(copy_move_counter::n_copies, initial_copies + 1);
  --iter;
  ASSERT_EQ(copy_move_counter::n_copies, initial_copies + 1);
}
