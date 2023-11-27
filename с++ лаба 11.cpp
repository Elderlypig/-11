#include <iostream>
#include <cmath>
#include <algorithm>

class Vector {
private:
    int dim;
    double* coord;

public:
    // Конструктор по умолчанию
    Vector() : dim(0), coord(nullptr) {}

    // Конструктор с параметрами
    Vector(int dim) : dim(dim) {
        coord = new double[dim];
        for (int i = 0; i < dim; ++i) {
            coord[i] = 0.0;
        }
    }

    // Конструктор копирования
    Vector(const Vector& v) : dim(v.dim) {
        coord = new double[dim];
        for (int i = 0; i < dim; ++i) {
            coord[i] = v.coord[i];
        }
    }

    // Деструктор
    ~Vector() {
        delete[] coord;
    }

    // Метод для установки координат
    void set(int index, double value) {
        if (index >= 0 && index < dim) {
            coord[index] = value;
        }
    }

    // Метод для вывода данных на экран
    void show() const {
        for (int i = 0; i < dim; ++i) {
            std::cout << coord[i] << " ";
        }
        std::cout << std::endl;
    }

    // Методы для работы с векторами
    double Length() const {
        double sum = 0.0;
        for (int i = 0; i < dim; ++i) {
            sum += coord[i] * coord[i];
        }
        return std::sqrt(sum);
    }

    double Cosinus(const Vector& b) const {
        return (*this * b) / (this->Length() * b.Length());
    }

    int Ortos(const Vector& b) const {
        return std::abs(this->Cosinus(b)) < 1e-9;
    }

    int Parallel(const Vector& b) const {
        return (this->Ortos(b)) | (std::abs(this->Cosinus(b) - 1) < 1e-9);
    }

    // Операторы
    double operator*(const Vector& b) const {
        double sum = 0.0;
        for (int i = 0; i < dim; ++i) {
            sum += coord[i] * b.coord[i];
        }
        return sum;
    }

    Vector operator*(double num) const {
        Vector result(dim);
        for (int i = 0; i < dim; ++i) {
            result.coord[i] = coord[i] * num;
        }
        return result;
    }

    Vector operator+(const Vector& b) const {
        Vector result(dim);
        for (int i = 0; i < dim; ++i) {
            result.coord[i] = coord[i] + b.coord[i];
        }
        return result;
    }

    Vector operator-(const Vector& b) const {
        Vector result(dim);
        for (int i = 0; i < dim; ++i) {
            result.coord[i] = coord[i] - b.coord[i];
        }
        return result;
    }

    bool operator<(const Vector& b) const {
        return this->Length() < b.Length();
    }

    bool operator>(const Vector& b) const {
        return this->Length() > b.Length();
    }

    bool operator==(const Vector& b) const {
        return this->Length() == b.Length();
    }
};

int main() {
    // Создание векторов
    Vector v1(3);
    v1.set(0, 1.0);
    v1.set(1, 2.0);
    v1.set(2, 3.0);
    v1.show();

    Vector v2(3);
    v2.set(0, 4.0);
    v2.set(1, 5.0);
    v2.set(2, 6.0);
    v2.show();

    // Работа с векторами
    Vector v3 = v1 + v2;
    v3.show();

    Vector v4 = v1 - v2;
    v4.show();

    setlocale(LC_ALL, "Russian");

    double cos = v1.Cosinus(v2);
    std::cout << "Косинус: " << cos << std::endl;

    int ort = v1.Ortos(v2);
    std::cout << "Ортогональные: " << ort << std::endl;

    int par = v1.Parallel(v2);
    std::cout << "Паралель: " << par << std::endl;

    return 0;
}
