#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

template <class T>
class Vector3 {
    public:
        static const int X = 0;
        static const int Y = 1;
        static const int Z = 2;
        Vector3() {}
        Vector3(T _x, T _y, T _z) {
            components[X] = _x;
            components[Y] = _y;
            components[Z] = _z;
        }
        virtual ~Vector3() {}

           T getX() { return components[X]; }
        void setX(T val) { components[X] = val; }
           T getY() { return components[Y]; }
        void setY(T val) { components[Y] = val; }
           T getZ() { return components[Z]; }
        void setZ(T val) { components[Z] = val; }
        void set(Vector3<T> v) {
            components[X] = v[X];
            components[Y] = v[Y];
            components[Z] = v[Z];
        }
           T dotProduct(Vector3<T> axis) { return (components[X] * axis[X]) + (components[Y] * axis[Y]) + (components[Z] * axis[Z]); }
           //T crossProduct(Vector3 v) { return (components[Y]*v[Z] + components[Z]*v[X] + components[X]*v[Y]) - (components[Y]*v[X] + components[Z]*v[Y] + components[X]*v[Z]); }
           //Vector3<T> tripleProduct(Vector3<T> v1, Vector3<T> v2) { return (v1*this->dotProduct(v2)) - (v2*this->dotProduct(v1)); }
           static Vector3<T> crossProduct(Vector3<T> v, Vector3<T> u) {
                return Vector3((v[Y]*u[Z]) - (v[Z]*u[Y]),
                               (v[Z]*u[X]) - (v[X]*u[Z]),
                               (v[X]*u[Y]) - (v[Y]*u[X])
                               );
           }

           T getNorm() {
                return sqrt(components[X] * components[X] +
                            components[Y] * components[Y] +
                            components[Z] * components[Z]);
           }

           static Vector3<T> normalized(Vector3<T> v) {
                return v / v.getNorm();
           }

           Vector3<T> tripleProduct(Vector3<T> v1, Vector3<T> v2) { return (v1*this->dotProduct(v2)) - (*this*v1.dotProduct(v2)); }
           T max();

        T& operator[] (int index);
        const T& operator[] (int index) const;
        Vector3<T>  operator+(const Vector3<T>& vector) const;
        Vector3<T>  operator-(const Vector3<T>& vector) const;
        Vector3<T>  operator-() const;
        Vector3<T>  operator*(T num) const;
        Vector3<T>  operator/(T num) const;

        Vector3<T>& operator+=(const Vector3<T>& vector);
        Vector3<T>& operator-=(const Vector3<T>& vector);
        Vector3<T>& operator*=(T num);
        Vector3<T>& operator*=(const Vector3<T>& vector);
        Vector3<T>& operator/=(T num);

        bool operator==(const Vector3<T>& vector) const;
        bool operator!=(const Vector3<T>& vector) const;
    protected:

    private:
        static const int DIMENSIONS = 3;
        T components[DIMENSIONS];
};

template <class T>
T& Vector3<T>::operator[] (int index) {
   if(index >= 0 && index < DIMENSIONS)
      return components[index];
}

template <class T>
const T& Vector3<T>::operator[] (int index) const {
   if(index >= 0 && index < DIMENSIONS)
      return components[index];
}

template <class T>
inline bool Vector3<T>::operator==(const Vector3<T>& vector) const {
    return components[X] == vector[X] && components[Y] == vector[Y] && components[Z] == vector[Z];
}

template <class T>
inline bool Vector3<T>::operator!=(const Vector3<T>& vector) const {
        return components[X] != vector[X] || components[Y] != vector[Y] || components[Z] != vector[Z];
}

template <class T>
inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& vector) const {
        return Vector3<T>(components[X] + vector[X], components[Y] + vector[Y], components[Z] + vector[Z]);
}

template <class T>
inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& vector) const {
        return Vector3<T>(components[X] - vector[X], components[Y] - vector[Y], components[Z] - vector[Z]);
}

template <class T>
inline Vector3<T> Vector3<T>::operator-() const {
        return Vector3<T>(-components[X], -components[Y], -components[Z]);
}

template <class T>
inline Vector3<T> Vector3<T>::operator*(T num) const {
        return Vector3<T>(components[X] * num, components[Y] * num, components[Z] * num);
}

template <class T>
inline Vector3<T> Vector3<T>::operator/(T num) const {
        return Vector3<T>(components[X] / num, components[Y] / num, components[Z] / num);
}

template <class T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& vector) {
        components[X] += vector[X];
        components[Y] += vector[Y];
        components[Z] += vector[Z];
        return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& vector) {
        components[X] -= vector[X];
        components[Y] -= vector[Y];
        components[Z] -= vector[Z];
        return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator*=(T num) {
        components[X] *= num;
        components[Y] *= num;
        components[Z] *= num;
        return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator/=(T num) {
        components[X] /= num;
        components[Y] /= num;
        components[Z] /= num;
        return *this;
}

template<class T>
Vector3<T> &Vector3<T>::operator*=(const Vector3<T> &vector) {
    components[X] *= vector[X];
    components[Y] *= vector[Y];
    components[Z] *= vector[Z];
    return *this;
}

typedef Vector3<int>    Vector3i;
typedef Vector3<float>  Vector3f;
typedef Vector3<double> Vector3d;

#endif // VECTOR3_H
