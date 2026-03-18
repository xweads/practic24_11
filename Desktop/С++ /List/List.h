#pragma once
#include <cstddef>

template <class T>
struct List {
    T val;
    List<T>* next;
    List(const T& v): val(v), next(nullptr) {}
};

// Very small move-only dynamic array. Does not use std::vector.
template <class T>
struct Vec {
    T* data;
    size_t s, cap;
    Vec(): data(nullptr), s(0), cap(0) {}
    ~Vec() { delete [] data; }
    Vec(const Vec&) = delete;
    Vec& operator=(const Vec&) = delete;
    Vec(Vec&& o) noexcept : data(o.data), s(o.s), cap(o.cap) { o.data = nullptr; o.s = 0; o.cap = 0; }
    Vec& operator=(Vec&& o) noexcept { if (this != &o) { delete [] data; data = o.data; s = o.s; cap = o.cap; o.data = nullptr; o.s = 0; o.cap = 0; } return *this; }
#pragma once
#include <cstddef>

template <class T>
struct List {
    T val;
    List<T>* next;
    List(const T& v): val(v), next(nullptr) {}
};

template <class T>
struct Vec {
    T* data;
    size_t s, cap;
    Vec(): data(nullptr), s(0), cap(0) {}
    ~Vec() { delete [] data; }
    Vec(const Vec&) = delete;
    Vec& operator=(const Vec&) = delete;
    Vec(Vec&& o) noexcept : data(o.data), s(o.s), cap(o.cap) { o.data = nullptr; o.s = 0; o.cap = 0; }
    Vec& operator=(Vec&& o) noexcept { if (this != &o) { delete [] data; data = o.data; s = o.s; cap = o.cap; o.data = nullptr; o.s = 0; o.cap = 0; } return *this; }

    void reserve(size_t n) {
        if (n <= cap) return;
        T* nd = new T[n];
        for (size_t i = 0; i < s; ++i) nd[i] = data[i];
        delete [] data;
        data = nd;
        cap = n;
    }

    void push_back(const T& x) {
        if (s == cap) reserve(cap ? cap * 2 : 4);
        data[s++] = x;
    }
};

template <class T>
Vec< List<T>* > balanced_move(Vec< List<T>* >& src, size_t k) {
    Vec< List<T>* > res;
    if (k == 0) return res;

    size_t total = 0;
    for (size_t i = 0; i < src.s; ++i) {
        List<T>* p = src.data[i];
        while (p) { ++total; p = p->next; }
    }

    size_t needed = (total + k - 1) / k;
    res.reserve(needed);

    List<T>* cur_head = nullptr;
    List<T>* cur_tail = nullptr;
    size_t cur_count = 0;

    for (size_t i = 0; i < src.s; ++i) {
        List<T>* node = src.data[i];
        src.data[i] = nullptr;
        while (node) {
            List<T>* nxt = node->next;
            node->next = nullptr;

            if (!cur_head) cur_head = cur_tail = node;
            else { cur_tail->next = node; cur_tail = node; }

            ++cur_count;
            if (cur_count == k) {
                res.push_back(cur_head);
                cur_head = cur_tail = nullptr;
                cur_count = 0;
            }
            node = nxt;
        }
    }

    if (cur_head) res.push_back(cur_head);
    return res;
}
