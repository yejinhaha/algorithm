def coin_change(amount, coins):
    result = {}
    for coin in coins:
        count = amount // coin  # 각 동전으로 나눌 수 있는 개수
        result[coin] = count
        amount -= coin * count  # 남은 금액 계산

    return result

# 사용할 동전 종류
coins = [500, 100, 50, 10]
# 거스름돈 액수
amount = 2780

# 계산 수행
change = coin_change(amount, coins)

# 결과 출력
print(f"{amount} Won – ", end="")
print(", ".join([f"{coin} Won: {count}" for coin, count in change.items() if count > 0]))
