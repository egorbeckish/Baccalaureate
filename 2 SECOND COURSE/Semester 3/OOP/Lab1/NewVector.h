#pragma once
#include <iostream>
#include <math.h>

namespace Vector3D
{
    class Vector3D
    {
        private:
            double X, Y, Z;
            int m_id;
            static int mvalue_id;
        
        public:
            
            // Конструктор нуль-вектора
            Vector3D();

            // Конструктор с пользовательскими значениями
            Vector3D(double x, double y, double z);

            // Конструктор копирования
            Vector3D(const Vector3D& copy);

            // Деструктор
            ~Vector3D();

            // чтение координат
            double get_X() const;
            double get_Y() const;
            double get_Z() const;

            // запись координа
            void set_X(double x);
            void set_Y(double y);
            void set_Z(double z);

            friend std::ostream& operator<<(std::ostream& output, const Vector3D& vect);

            // модуль
            double Lenght() const;

            // копирование вектора
            const Vector3D& CopyVector(const Vector3D& copy);

            // умножение вектора на скаляр
            const Vector3D& MultiplicatioScalar(const double scalar);

            // Нормированный вектор
            const Vector3D& NormalizedVector();

            // сложение векторов
            const Vector3D& AddVector(const Vector3D& A, const Vector3D& B);
            // Vector3D AdditionVector(const Vector3D& A, const Vector3D& B);

            // вычитание векторов
            const Vector3D& SubVector(const Vector3D& A, const Vector3D& B);
            // Vector3D SubstractionVector(const Vector3D& A, const Vector3D& B);

            // векторное произведение
            const Vector3D& MultVector(const Vector3D& A, const Vector3D& B);
            // Vector3D MultiplicationVector(const Vector3D& A, const Vector3D& B);

    };

    Vector3D AdditionVector(const Vector3D& A, const Vector3D& B);

    Vector3D SubstractionVector(const Vector3D& A, const Vector3D& B);

    Vector3D MultiplicationVector(const Vector3D& A, const Vector3D& B);

    double ScalarProduct(const Vector3D& A, const Vector3D& B);

    double Sin(const Vector3D& A, const Vector3D& B);

    double Cos(const Vector3D& A, const Vector3D& B);

    double Angle(const Vector3D& A, const Vector3D& B);
}
