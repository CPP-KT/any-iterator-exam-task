#pragma once

template <typename T, typename Tag>
class any_iterator {
public:
  using value_type = void;
  using pointer = void;
  using reference = void;
  using difference_type = void;
  using iterator_category = void;

public:
  any_iterator();

  ~any_iterator();

  template <typename It>
  any_iterator(It);

  any_iterator(const any_iterator& other);
  any_iterator(any_iterator&& other);

  template <typename It>
  any_iterator& operator=(It it);

  any_iterator& operator=(any_iterator&& other);
  any_iterator& operator=(const any_iterator& other);

  void swap(any_iterator& other) noexcept;

  const T& operator*() const;
  T& operator*();

  const T* operator->() const;
  T* operator->();

  any_iterator& operator++() &;
  any_iterator operator++(int) &;

  template <typename TT, typename TTag>
  friend bool operator==(const any_iterator<TT, TTag>& a, const any_iterator<TT, TTag>& b);

  template <typename TT, typename TTag>
  friend bool operator!=(const any_iterator<TT, TTag>& a, const any_iterator<TT, TTag>& b);

  // note: following operators must compile ONLY for appropriate iterator tags

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag>& operator--(any_iterator<TT, TTag>&);

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag> operator--(any_iterator<TT, TTag>&, int);

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag>& operator+=(any_iterator<TT, TTag>&, typename any_iterator<TT, TTag>::difference_type);

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag>& operator-=(any_iterator<TT, TTag>&, typename any_iterator<TT, TTag>::difference_type);

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag> operator+(any_iterator<TT, TTag>, typename any_iterator<TT, TTag>::difference_type);

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag> operator-(any_iterator<TT, TTag>, typename any_iterator<TT, TTag>::difference_type);

  template <typename TT, typename TTag>
  friend bool operator<(const any_iterator<TT, TTag>& a, const any_iterator<TT, TTag>& b);

  template <typename TT, typename TTag>
  friend typename any_iterator<TT, TTag>::difference_type operator-(const any_iterator<TT, TTag>& a,
                                                                    const any_iterator<TT, TTag>& b);
};
