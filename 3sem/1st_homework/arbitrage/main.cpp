#include <cfloat>
#include <iostream>
#include <vector>

#include "arbitrage_search.h"

int main() {
    unsigned cur_quantity = 0; // quantity of currencies
    std::cin >> cur_quantity;
    if (cur_quantity == 0 || cur_quantity == 1) {
        std::cout << "NO\n";
        return 0;
    }

    std::vector<ExchangeRate> trade_table;
    ScanTable(trade_table, cur_quantity);

    for (int currency = 0; currency < cur_quantity; ++currency) {
        if (FindCycle(currency, cur_quantity, trade_table)) {
            std::cout << "YES\n";
            return 0;
        }
    }
    std::cout << "NO\n";

    return 0;
}

