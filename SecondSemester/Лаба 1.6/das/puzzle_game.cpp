#include "puzzle_game.h"
#include <iostream>
#include <queue>
#include <algorithm>

solver::solver(const board &b) {
    start_board = b;
    transition = {{-1, 0},
                  {0,  1},
                  {1,  0},
                  {0,  -1}}; //сдвиги
    _board_goal = board(b.get_goal());
    solve();
}

solver::solver(const solver &s) = default;

solver &solver::operator=(const solver &other)  = default;

solver::~solver(){
    boards.clear();
    parent.clear();
}

size_t solver::board_hasher::operator()(const board &b) const {
    size_t hash = 0;
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            hash += b[i][j] * (i + b.size() * j);
        }
    }

    return hash;
}

bool solver::equal_checker::operator()(const board &a, const board &b) const {
    return a == b;
}

solver::iterator solver::begin() {
    return iterator(&boards[0]);
}

solver::iterator solver::end() {
    return iterator(&boards[boards.size()]);
}

solver::iterator::iterator(board *b) {
    it = b;
}

board &solver::iterator::operator++() {
    return *++it;
}

board &solver::iterator::operator+(int x) {
    return *(it + x);
}

board &solver::iterator::operator-(int x) {
    return *(it - x);
}

board &solver::iterator::operator--() {
    return *--it;
}

board &solver::iterator::operator++(int) {
    return *it++;
}

board &solver::iterator::operator--(int) {
    return *it--;
}

board solver::iterator::operator*() {
    return *it;
}

bool solver::iterator::operator==(const solver::iterator &other) {
    return it == other.it;
}

bool solver::iterator::operator!=(const solver::iterator &other) {
    return it != other.it;
}

void solver::solve() {
    if (!start_board.is_solvable()) {
        return;
    }

    std::priority_queue<std::pair<size_t, board>, std::vector<std::pair<size_t, board>>, comparator> q; //dist и доска
    std::unordered_set<board, board_hasher> used;
    std::unordered_map<board, size_t, board_hasher, equal_checker> distance; //2 и 3 параметр это хэш и проверка на эквивалент, ключ - доска, значение - дистанция

    q.push({0, start_board});
    distance[start_board] = 0;
    while (!q.empty()) {
        std::pair<size_t, board> current = q.top();
        if (current.second.is_goal()) {
            get_parents();
            return;
        }
        q.pop();
        used.insert(current.second);

        std::pair<size_t, size_t> zero = current.second.get_zero();
        for (auto dxdy : transition) {
            size_t dx = dxdy.first;
            size_t dy = dxdy.second;
            size_t new_x = zero.first + dx;
            size_t new_y = zero.second + dy;
            board changed_board = current.second;

            if (check(new_x, new_y)) {
                std::vector<std::vector<size_t>> tmp = changed_board.get_board();
                std::swap(tmp[zero.first][zero.second], tmp[new_x][new_y]);
                changed_board = board(tmp);


                size_t cur_dist = current.first + changed_board.hamming() + changed_board.manhattan(); //что было + стоимость + расстояние
                if (distance.find(changed_board) == distance.end()) {
                    distance[changed_board] = INT32_MAX;
                }
/////////////////////////////////////////////////////////////
                if (used.count(changed_board) && cur_dist >= distance[changed_board]) { //больше или равно вроде!!!!!
                    continue;
                }
////////////////////////////////////////////////////////////
                if (!used.count(changed_board) || cur_dist < distance[changed_board]) {
                    parent[changed_board] = current.second;
                    distance[changed_board] = cur_dist;
                    q.push({cur_dist, changed_board});
                }

            }
        }
    }
}

void solver::get_parents() {
    board v = _board_goal;
    while (v != start_board) {
        boards.emplace_back(v); //то же что и push_back
        v = parent[v];
    }
    boards.emplace_back(v);
    reverse(boards.begin(), boards.end());
}

bool solver::check(size_t x, size_t y) const {//проверка что не выходит за доску
    return x >= 0 && x < start_board.size() && y >= 0 && y < start_board.size();
}

size_t solver::moves() const {
    return boards.size() - 1; //добавлено -1
}

bool solver::comparator::operator()(const std::pair<size_t, board> &a, const std::pair<size_t, board> &b) const {
    return a.first > b.first;
};

