
template <typename T, typename Tag>
struct any_iterator {
  // replace void with needed type
  using value_type = void;
  using pointer = void*;
  using reference = void;
  using difference_type = void;
  using iterator_category = void;

  any_iterator();

  template <typename It>
  any_iterator(It);

  any_iterator(const any_iterator& other);
  any_iterator(any_iterator&& other);

  any_iterator& operator=(any_iterator&& other);
  any_iterator& operator=(const any_iterator& other);

  void swap(any_iterator& other) noexcept;

  template <typename It>
  any_iterator& operator=(It it);

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

  // note: next operators must compile ONLY for appropriate iterator tags

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

  ~any_iterator();
};
