#include "Vector3D.h"


namespace Vector3D
{
    int Vector3D::mvalue_id = 1;

    Vector3D::Vector3D() : m_id{mvalue_id ++}
    {
        std::cout << "Vector #" << m_id << " ";
        X = 0;
        Y = 0;
        Z = 0;
    }

    Vector3D::Vector3D(double x, double y, double z) : m_id{mvalue_id ++}
    {
        std::cout << "Vector #" << m_id << " ";
        X = x;
        Y = y;
        Z = z;
    }

    Vector3D::Vector3D(const Vector3D& copy)
    {
        std::cout << "Vector #" << m_id << " ";
        X = copy.X;
        Y = copy.Y;
        Z = copy.Z;
    }
    
    Vector3D::~Vector3D()
    {
        std::cout << "Vector #" << m_id << " ";
        X = 0;
        Y = 0;
        Z = 0;
    }

    double Vector3D::get_X() const { return X; }
    double Vector3D::get_Y() const { return Y; }
    double Vector3D::get_Z() const { return Z; }

    void Vector3D::set_X(double x) { this -> X = x; }
    void Vector3D::set_Y(double y) { this -> Y = y; }
    void Vector3D::set_Z(double z) { this -> Z = z; }
   
    std::ostream& operator<<(std::ostream& output, const Vector3D& vect)
    {
        output << "(" << vect.X << ", " << vect.Y << ", " << vect.Z << ")";

        return output;
    }

    double Vector3D::Lenght() const
    {
        return sqrt(X * X + Y * Y + Z * Z);
    }

    const Vector3D& Vector3D::CopyVector(const Vector3D& copy)
    {
        this -> X = copy.X;
        this -> Y = copy.Y;
        this -> Z = copy.Z;

        return *this;
    }

    const Vector3D& Vector3D::MultiplicatioScalar(const double scalar)
    {
        this -> X *= scalar;
        this -> Y *= scalar;
        this -> Z *= scalar;

        return *this;
    }

    const Vector3D& Vector3D::NormalizedVector()
    {
        this -> X /= Lenght();
        this -> Y /= Lenght();
        this -> Z /= Lenght();

        return *this;
    }

    const Vector3D& Vector3D::AddVector(const Vector3D& A, const Vector3D& B)
    {
        this -> X = A.X + B.X;
        this -> Y = A.Y + B.Y;
        this -> Z = A.Z + B.Z;

        return *this;
    }

    const Vector3D& Vector3D::SubVector(const Vector3D& A, const Vector3D& B)
    {
        this -> X = A.X - B.X;
        this -> Y = A.Y - B.Y;
        this -> Z = A.Z - B.Z;

        return *this;
    }

    const Vector3D& Vector3D::MultVector(const Vector3D& A, const Vector3D& B)
    {
        this -> X = (A.Y * B.Z) - (A.Z * B.Y);
        this -> Y = (A.Z * B.X) - (A.X * B.Z);
        this -> Z = (A.X * B.Y) - (A.Y * B.X);

        return *this;
    }

    Vector3D AdditionVector(const Vector3D& A, const Vector3D& B)
    {
        Vector3D C_add;

        C_add.set_X(A.get_X() + B.get_X());
        C_add.set_Y(A.get_Y() + B.get_Y());
        C_add.set_Z(A.get_Z() + B.get_Z());
        
        return C_add;
    }

    Vector3D SubstractionVector(const Vector3D& A, const Vector3D& B)
    {
        Vector3D C_sub;

        C_sub.set_X(A.get_X() - B.get_X());
        C_sub.set_Y(A.get_Y() - B.get_Y());
        C_sub.set_Z(A.get_Z() - B.get_Z());
        
        return C_sub;
    }

    Vector3D MultiplicationVector(const Vector3D& A, const Vector3D& B)
    {
        Vector3D C_mul;

        C_mul.set_X((A.get_Y() * B.get_Z()) - (A.get_Z() * B.get_Y()));
        C_mul.set_Y((A.get_Z() * B.get_X()) - (A.get_X() * B.get_Z()));
        C_mul.set_Z((A.get_X() * B.get_Y()) - (A.get_Y() * B.get_X()));

        return C_mul;
    }

    double ScalarProduct(const Vector3D& A, const Vector3D& B)
    {
        return (A.get_X() * B.get_X() + A.get_Y() * B.get_Y() + A.get_Z() * B.get_Z());
    }

    double Sin(const Vector3D& A, const Vector3D& B)
    {
        return (MultiplicationVector(A, B).Lenght() / (A.Lenght() * B.Lenght()));
    }

    double Cos(const Vector3D& A, const Vector3D& B)
    {
        return (ScalarProduct(A, B) / (A.Lenght() * B.Lenght()));
    }

    double Angle(const Vector3D& A, const Vector3D& B)
    {
        return (atan2(MultiplicationVector(A, B).Lenght(), ScalarProduct(A, B)) * 180 / M_PI);
    }
}
