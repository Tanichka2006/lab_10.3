#include <iostream>
#include <iomanip> // ��� ������������ �������
#include <string>
#include <vector>
#include <algorithm> // ��� ����������
#include <locale> // ��� ����������
#ifdef _WIN32
#include <windows.h> // ��� SetConsoleCP � SetConsoleOutputCP
#endif

// ��������� Price
struct Price {
    std::string productName; // ����� ������
    std::string shopName;    // ����� ��������
    double price;            // ������� ������ � �������
};

// ������� ��� ������ �������
void printTable(const std::vector<Price>& prices) {
    std::cout << "=============================================================\n";
    std::cout << std::left
        << std::setw(20) << "| ����� ������"
        << std::setw(20) << "| ����� ��������"
        << std::setw(10) << "| ֳ�� (���)"
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

// ������� ��� ������ ������ �� ������
void searchProduct(const std::vector<Price>& prices, const std::string& productName) {
    bool found = false;

    std::cout << "��������� ������:\n";
    std::cout << "=============================================================\n";
    std::cout << std::left
        << std::setw(20) << "| ����� ������"
        << std::setw(20) << "| ����� ��������"
        << std::setw(10) << "| ֳ�� (���)"
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
        std::cout << "����� � ������ \"" << productName << "\" �� ��������.\n";
    }
    std::cout << "=============================================================\n";
}

int main() {
#ifdef _WIN32
    // ��� ��������� ������ � ���������� ����� � ������ Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    setlocale(LC_ALL, "ukr"); // ���������� ��������� ������

    int n;
    std::cout << "������ ������� ������: ";
    std::cin >> n;

    std::vector<Price> prices(n);

    // �������� �����
    for (int i = 0; i < n; ++i) {
        std::cout << "������ ���������� ��� ������ " << i + 1 << ":\n";
        std::cin.ignore(); // �������� ������
        std::cout << "����� ������: ";
        std::getline(std::cin, prices[i].productName);
        std::cout << "����� ��������: ";
        std::getline(std::cin, prices[i].shopName);
        std::cout << "ֳ�� (���): ";
        std::cin >> prices[i].price;
    }

    // ���������� �� ��������� �������� ���� ��������
    std::sort(prices.begin(), prices.end(), [](const Price& a, const Price& b) {
        return a.shopName < b.shopName;
        });

    // ���� ������� ���� ����������
    std::cout << "\n������ ������ ���� ���������� �� ������� ��������:\n";
    printTable(prices);

    // ����� ������
    std::string searchName;
    std::cin.ignore(); // �������� ������
    std::cout << "\n������ ����� ������ ��� ������: ";
    std::getline(std::cin, searchName);

    searchProduct(prices, searchName);

    return 0;
}
