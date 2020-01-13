#pragma once

#include <vector>
#include <string>

struct board {
    board();

    board(const board &other); //конструктор по умолчанию

    explicit board(const std::vector<std::vector<size_t>> &other);

    explicit board(int size);

    size_t size() const;//const значит, что нельзя менять члены класса того объекта, откуда вызван

    bool is_goal() const;

    size_t manhattan() const;

    size_t hamming() const;

    bool is_solvable() const;

    std::string to_string() const;

    std::vector<std::vector<size_t>> get_goal() const;

    friend bool operator!=(const board &a, const board &b);

    friend bool operator==(const board &a, const board &b);

    friend bool operator<(const board &a, const board &b);

    friend std::ostream &operator<<(std::ostream &out, const board &b);

    const std::vector<size_t> &operator[](size_t index) const;

    std::pair<size_t, size_t> get_zero() const;

    board &operator=(const board &other);

    std::vector<std::vector<size_t>> get_board() const;

    ~board();

private:
    std::vector<std::vector<size_t>> b;
    std::vector<std::vector<size_t>> goal; //нужное решение
    size_t _size; //размер доски
    std::pair<size_t, size_t> zero; //пустая клетка
    void init_goal(); //создает нужное решение - массив заполненый числами от 1 до n^2 и пустота в последней клетке
    void find_zero(); //находит где сейчас пустая клетка
};
