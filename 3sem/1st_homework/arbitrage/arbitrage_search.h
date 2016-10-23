#ifndef INC_ARBITRAGE_ARBITRAGE_SEARCH_H_
#define INC_ARBITRAGE_ARBITRAGE_SEARCH_H_

#include <vector>

struct ExchangeRate {
    ExchangeRate(unsigned from, unsigned to, float rate) : from(from), to(to), rate(rate) {};
    unsigned from;
    unsigned to;
    float rate;
};

bool FindCycle(int currency, unsigned cur_quantity, std::vector<ExchangeRate> &trade_table);
void ScanTable(std::vector<ExchangeRate> &trade_table, int cur_quantity);

#endif //INC_ARBITRAGE_ARBITRAGE_SEARCH_H_
