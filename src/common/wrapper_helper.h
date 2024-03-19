#ifndef WRAPPER_HELPER_H
#define WRAPPER_HELPER_H

template <class T>
void *to_ptr(T &t) {
    return const_cast<T *>(reinterpret_cast<const T *>(&t));
}

#endif // WRAPPER_HELPER_H
