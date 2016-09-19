#include <cfloat>
#include <iostream>
#include <vector>

using namespace std;

struct ExchangeRate {
    ExchangeRate(unsigned from, unsigned to, float rate) : from(from), to(to), rate(rate) {};
    unsigned from;
    unsigned to;
    float rate;
};

bool findCycle(int currency, unsigned cur_quantity, vector<ExchangeRate> &trade_table);

int main() {
    unsigned cur_quantity = 0; // quantity of currencies
    //cout << "Enter quantity of currencies:\n";
    cin >> cur_quantity;
    if (cur_quantity == 0 || cur_quantity == 1) {
        cout << "NO\n";
        return 0;
    }

    vector<ExchangeRate> trade_table;
    //cout << "Enter trade table:\n";
    for (int line = 0; line < cur_quantity; ++line) {
        for (int column = 0; column < cur_quantity; ++column) {
            if (column == line) {
                trade_table.push_back(ExchangeRate(line, column, 1));
            } else {
                float weight;
                cin >> weight;
                if (weight == -1)
                    continue;
                trade_table.push_back(ExchangeRate(line, column, weight));
            }
        }
    }

    for (int currency = 0; currency < cur_quantity; ++currency) {
        if (findCycle(currency, cur_quantity, trade_table)) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";

    return 0;
}

bool findCycle(int currency, unsigned cur_quantity, vector<ExchangeRate> &trade_table) {
    vector<float> distance(cur_quantity);
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