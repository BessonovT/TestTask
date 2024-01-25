#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-3;

// Точка
struct Point {
    double x, y;

    Point(double x, double y) : x(x), y(y) {}

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    double distance(const Point& other) const {
        return hypot(x - other.x, y - other.y);
    }
};

// Градиент f в точке p
vector<double> gradient(double f(const Point&), const Point& p) {
    double e = 1e-4;
    double dx = (f(Point(p.x + e, p.y)) - f(Point(p.x - e, p.y))) / (2 * e);
    double dy = (f(Point(p.x, p.y + e)) - f(Point(p.x, p.y - e))) / (2 * e);
    return vector<double> {dx, dy};
}

// Движение в сторону градиента с шагом s
Point move(const Point& p, const vector<double>& v, double s) {
    return Point(p.x + s * v[0], p.y + s * v[1]);
}

// Что дано
double tdoa(const Point& p) {
    // Расстояния от выбранной точки до остальных 
    double ad = p.distance(Point(1, 0));
    double bd = p.distance(Point(2, 0));
    double cd = p.distance(Point(3, 0));

    // Разности хода
    double t1 = ad - bd;
    double t2 = ad - cd;
    double t3 = bd - cd;

    // Возвращаем сумму квадратов
    return t1 * t1 + t2 * t2 + t3 * t3;
}

// Функция нахождения минимума
Point find_min(Point p) {
    // Размер шага
    double s = 0.1;

    // Повторять пока не будет достаточного сближения
    while (true) {
        vector<double> g = gradient(tdoa, p);
        // Проверка градиента на маленькость
        if (g[0] * g[0] + g[1] * g[1] < EPS) {
            return p;
        }
        // Движение в сторону минимума
        p = move(p, g, s);
    }
}

int main() {
    // Ищем и выводим минимум для трех точек (Пишем предполагаемые A, B и С)

    Point p1 = find_min(Point(-100, -100));
    Point p2 = find_min(Point(100, 100));
    Point p3 = find_min(Point(0, 15));

    cout << "The minimum is at (" << p1.x << ", " << p1.y << ") for point 1" << endl;
    cout << "The minimum is at (" << p2.x << ", " << p2.y << ") for point 2" << endl;
    cout << "The minimum is at (" << p3.x << ", " << p3.y << ") for point 3" << endl;

    return 0;
}