# any_iterator

Ваша задача написать `any_iterator`, поддерживающий `std::forward_iterator_tag`, `std::bidirectional_iterator_tag` и `std::random_access_iterator_tag` в качестве параметра.

Это type-erasure обёртка над итератором.
Интерфейс, который нужно реализовать, находится в [any_iterator.h](./any_iterator.h).

При написании этого задания необходимо применить small-object оптимизацию (SOO).
