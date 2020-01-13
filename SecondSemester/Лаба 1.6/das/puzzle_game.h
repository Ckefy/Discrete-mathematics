#pragma once

#include "board.h"
#include<unordered_map>
#include <unordered_set>
#include <queue>

struct solver {
    explicit solver(const board &b);

    solver(const solver &s);

    solver &operator=(const solver &other);

    struct iterator {
        explicit iterator(board *b);

        board &operator+(int x);

        board &operator-(int x);

        board &operator++();

        board &operator--();

        board &operator++(int);

        board &operator--(int);

        bool operator==(const iterator &other);

        bool operator!=(const iterator &other);

        board operator*();

    private:
        board *it;
    };

    ~solver();

    iterator begin();

    iterator end();

    size_t moves() const;

private:

    struct board_hasher {
        size_t operator()(const board &b) const;
    };

    struct equal_checker {
        bool operator()(const board &a, const board &b) const;
    };

    struct comparator {
        bool operator()(const std::pair<size_t, board> &a, const std::pair<size_t, board> &b) const;
    };

    std::vector<std::pair<char, char>> transition;
    board start_board;
    board _board_goal; //что должно получиться
    std::vector<board> boards; //последовательные изменения досок тут будут от начала и до конца
    std::unordered_map<board, board, board_hasher, equal_checker> parent; //ну родители прост

    void solve();

    void get_parents();

    bool check(size_t x, size_t y) const;
};

