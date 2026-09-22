#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double EPS = 1e-9;

// Сравнение чисел с плавающей точкой через эпсилон
bool isEqual(double x, double y) {
    return fabs(x - y) < EPS;
}

bool isZero(double x) {
    return fabs(x) < EPS;
}

// Функция вычисляет значение F(x) по кусочной формуле.
// Возвращает true, если значение вычислено успешно, false - при делении на ноль.
bool calculate(double a, double b, double c, double x, double &result) {
    bool aNegative = (a < -EPS);   // a < 0 через эпсилон
    bool aPositive = (a > EPS);    // a > 0 через эпсилон
    bool xIsZero = isZero(x);

    if (aNegative && !xIsZero) {
        // F = a*x^2 + b^2*x
        result = a * x * x + b * b * x;
        return true;
    } else if (aPositive && xIsZero) {
        // F = x - (x-a)/(x-c), проверка деления на ноль
        if (isZero(x - c)) {
            return false;
        }
        result = x - (x - a) / (x - c);
        return true;
    } else {
        // F = 1 + x/c, проверка деления на ноль
        if (isZero(c)) {
            return false;
        }
        result = 1 + x / c;
        return true;
    }
}

int main() {
    double a, b, c, Xnach, Xkon, dX;

    cout << "Vichislenie funktsii F na intervale [Xnach, Xkon] s shagom dX\n\n";

    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;
    cout << "Xnach = ";
    cin >> Xnach;
    cout << "Xkon = ";
    cin >> Xkon;
    cout << "dX = ";
    cin >> dX;

    if (isZero(dX)) {
        cout << "Oshibka: shag dX ne mozhet bit raven 0.\n";
        return 1;
    }

    int Ac = (int)a;
    int Bc = (int)b;
    int Cc = (int)c;

    // Поразрядное выражение: NOT(Ac OR Bc) AND (Bc OR Cc)
    int condition = (~(Ac | Bc)) & (Bc | Cc);
    bool isReal = (condition != 0);

    cout << "\n" << left << setw(14) << "x" << "F(x)" << endl;
    cout << "------------------------------------\n";

    for (double x = Xnach; x <= Xkon + EPS; x += dX) {
        double f;
        bool ok = calculate(a, b, c, x, f);

        cout << left << setw(14) << fixed << setprecision(4) << x;

        if (!ok) {
            cout << "delenie na 0 (propuscheno)" << endl;
            continue;
        }

        if (isReal) {
            cout << fixed << setprecision(6) << f << endl;
        } else {
            cout << (int)f << endl;
        }
    }

    return 0;
}
