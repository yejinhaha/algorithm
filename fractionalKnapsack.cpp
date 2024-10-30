#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <tuple>

struct Item {
    char name;
    double weight;
    double value;
    double valuePerWeight;
};

// 비교 함수: 단위 무게 당 가치가 높은 순으로 정렬
bool compare(Item a, Item b) {
    return a.valuePerWeight > b.valuePerWeight;
}

void fractionalKnapsack(std::vector<Item> items, double capacity) {
    // 단위 무게 당 가치를 계산
    for (auto& item : items) {
        item.valuePerWeight = item.value / item.weight;
    }

    // 단위 무게 당 가치 기준으로 정렬
    std::sort(items.begin(), items.end(), compare);

    double totalWeight = 0.0;
    double totalValue = 0.0;
    std::vector<std::tuple<char, double, double>> selectedItems;

    // 물건을 배낭에 담기
    for (auto& item : items) {
        if (totalWeight + item.weight <= capacity) {
            // 물건 전체를 배낭에 담을 수 있는 경우
            selectedItems.push_back(std::make_tuple(item.name, item.weight, item.value));
            totalWeight += item.weight;
            totalValue += item.value;
        }
        else {
            // 물건 일부만 배낭에 담아야 하는 경우
            double remainWeight = capacity - totalWeight;
            double value = item.valuePerWeight * remainWeight;
            selectedItems.push_back(std::make_tuple(item.name, remainWeight, value));
            totalWeight += remainWeight;
            totalValue += value;
            break; // 배낭이 가득 찼으므로 종료
        }
    }

    // 결과 출력
    std::cout << "Goods\tWeight of goods in knapsack\tValue of goods in knapsack\n";
    for (auto& item : selectedItems) {
        std::cout << std::get<0>(item) << "\t\t" << std::get<1>(item) << "\t\t\t"
            << std::fixed << std::setprecision(2) << std::get<2>(item) << "\n";
    }
    std::cout << "Sum\t\t" << totalWeight << "\t\t\t" << totalValue << "\n";
}

int main() {
    // 입력 데이터 설정 (각 물건의 무게와 가치)
    std::vector<Item> items = {
        {'A', 10, 60},   // 백금
        {'B', 15, 75},   // 금
        {'C', 25, 10},   // 은
        {'D', 50, 5}     // 주석
    };
    double capacity = 40; // 배낭의 최대 용량

    // Fractional Knapsack 알고리즘 실행
    fractionalKnapsack(items, capacity);

    return 0;
}
