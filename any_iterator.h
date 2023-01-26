
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

  any_iterator(any_iterator const& other);
  any_iterator(any_iterator&& other);

  any_iterator& operator=(any_iterator&& other);
  any_iterator& operator=(any_iterator const& other);

  void swap(any_iterator& other) noexcept;

  template <typename It>
  any_iterator& operator=(It it);

  T const& operator*() const;
  T& operator*();

  T const* operator->() const;
  T* operator->();

  any_iterator& operator++() &;
  any_iterator operator++(int) &;

  template <typename TT, typename TTag>
  friend bool operator==(any_iterator<TT, TTag> const& a,
                         any_iterator<TT, TTag> const& b);

  template <typename TT, typename TTag>
  friend bool operator!=(any_iterator<TT, TTag> const& a,
                         any_iterator<TT, TTag> const& b);

  // note: next operators must compile ONLY for appropriate iterator tags

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag>& operator--(any_iterator<TT, TTag>&);

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag> operator--(any_iterator<TT, TTag>&, int);

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag>&
  operator+=(any_iterator<TT, TTag>&,
             typename any_iterator<TT, TTag>::difference_type);

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag>&
  operator-=(any_iterator<TT, TTag>&,
             typename any_iterator<TT, TTag>::difference_type);

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag>
  operator+(any_iterator<TT, TTag>,
            typename any_iterator<TT, TTag>::difference_type);

  template <typename TT, typename TTag>
  friend any_iterator<TT, TTag>
  operator-(any_iterator<TT, TTag>,
            typename any_iterator<TT, TTag>::difference_type);

  template <typename TT, typename TTag>
  friend bool operator<(any_iterator<TT, TTag> const& a,
                        any_iterator<TT, TTag> const& b);

  template <typename TT, typename TTag>
  friend typename any_iterator<TT, TTag>::difference_type
  operator-(any_iterator<TT, TTag> const& a, any_iterator<TT, TTag> const& b);

  ~any_iterator();
};
