#include "arbitrage_search.h"

#include <cfloat>
#include <iostream>
#include <vector>

bool FindCycle(int currency, unsigned cur_quantity, std::vector<ExchangeRate> &trade_table) {
    std::vector<float> distance(cur_quantity);
    for (int v = 0; v < cur_quantity; ++v)
        distance[v] = FLT_MIN;
    distance[currency] = 1;

    for (int i = 0; i <= cur_quantity; ++i) {
        for (auto &ex_rate : trade_table) {
            if (distance[ex_rate.to] < distance[ex_rate.from] * ex_rate.rate) {
                if (i == cur_quantity)
                    return true;
                distance[ex_rate.to] = distance[ex_rate.from] * ex_rate.rate;
            }
        }
    }
    return false;
}
void ScanTable(std::vector<ExchangeRate> &trade_table, int cur_quantity) {
    for (int line = 0; line < cur_quantity; ++line) {
        for (int column = 0; column < cur_quantity; ++column) {
            if (column == line) {
                trade_table.push_back(ExchangeRate(line, column, 1));
            } else {
                float weight;
                std::cin >> weight;
                if (weight == -1)
                    continue;
                trade_table.push_back(ExchangeRate(line, column, weight));
            }
        }
    }
}