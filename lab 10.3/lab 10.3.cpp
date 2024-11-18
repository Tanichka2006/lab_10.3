#include <iostream>
#include <iomanip> // Для форматування таблиці
#include <string>
#include <vector>
#include <algorithm> // Для сортування
#include <locale> // Для локалізації
#ifdef _WIN32
#include <windows.h> // Для SetConsoleCP і SetConsoleOutputCP
#endif

// Структура Price
struct Price {
    std::string productName; // Назва товару
    std::string shopName;    // Назва магазину
    double price;            // Вартість товару в гривнях
};

// Функція для виводу таблиці
void printTable(const std::vector<Price>& prices) {
    std::cout << "=============================================================\n";
    std::cout << std::left
        << std::setw(20) << "| Назва товару"
        << std::setw(20) << "| Назва магазину"
        << std::setw(10) << "| Ціна (грн)"
        << "|\n";
    std::cout << "=============================================================\n";

    for (const auto& item : prices) {
        std::cout << std::left
            << std::setw(20) << ("| " + item.productName)
            << std::setw(20) << ("| " + item.shopName)
            << std::setw(10) << ("| " + std::to_string(item.price))
            << "|\n";
    }
    std::cout << "=============================================================\n";
}

// Функція для пошуку товару за назвою
void searchProduct(const std::vector<Price>& prices, const std::string& productName) {
    bool found = false;

    std::cout << "Результат пошуку:\n";
    std::cout << "=============================================================\n";
    std::cout << std::left
        << std::setw(20) << "| Назва товару"
        << std::setw(20) << "| Назва магазину"
        << std::setw(10) << "| Ціна (грн)"
        << "|\n";
    std::cout << "=============================================================\n";

    for (const auto& item : prices) {
        if (item.productName == productName) {
            std::cout << std::left
                << std::setw(20) << ("| " + item.productName)
                << std::setw(20) << ("| " + item.shopName)
                << std::setw(10) << ("| " + std::to_string(item.price))
                << "|\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Товар з назвою \"" << productName << "\" не знайдено.\n";
    }
    std::cout << "=============================================================\n";
}

int main() {
#ifdef _WIN32
    // Для правильної роботи з українською мовою в консолі Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    setlocale(LC_ALL, "ukr"); // Встановлює українську локаль

    int n;
    std::cout << "Введіть кількість товарів: ";
    std::cin >> n;

    std::vector<Price> prices(n);

    // Введення даних
    for (int i = 0; i < n; ++i) {
        std::cout << "Введіть інформацію для товару " << i + 1 << ":\n";
        std::cin.ignore(); // Очищення буфера
        std::cout << "Назва товару: ";
        std::getline(std::cin, prices[i].productName);
        std::cout << "Назва магазину: ";
        std::getline(std::cin, prices[i].shopName);
        std::cout << "Ціна (грн): ";
        std::cin >> prices[i].price;
    }

    // Сортування за алфавітним порядком назв магазинів
    std::sort(prices.begin(), prices.end(), [](const Price& a, const Price& b) {
        return a.shopName < b.shopName;
        });

    // Вивід таблиці після сортування
    std::cout << "\nСписок товарів після сортування за назвами магазинів:\n";
    printTable(prices);

    // Пошук товару
    std::string searchName;
    std::cin.ignore(); // Очищення буфера
    std::cout << "\nВведіть назву товару для пошуку: ";
    std::getline(std::cin, searchName);

    searchProduct(prices, searchName);

    return 0;
}
