#pragma once
#ifndef MATH_HPP
#define MATH_HPP

namespace Math
{
    struct Vector
    {
        long double x;
        long double y;

        Vector()
        {
            x = 0;
            y = 0;
        }

        Vector( long double startx, long double starty)
        {
            x = startx;
            y = starty;
        }

        Vector operator= ( const Vector& b )
        {
            if( this != &b )
            {
                x = b.x;
                y = b.y;
            }

            return *this;
        }

        Vector& operator-= ( const Vector& b )
        {
            x -= b.x;
            y -= b.y;

            return *this;
        }

        Vector& operator+= ( const Vector& b )
        {
            x += b.x;
            y += b.y;

            return *this;
        }

        template< class DataType >
        Vector& operator/= ( const DataType& b )
        {
            x /= b;
            y /= b;

            return *this;
        }

        template< class DataType >
        Vector& operator*= ( const DataType& b )
        {
            x *= b;
            y *= b;

            return *this;
        }

        Vector operator+ ( const Vector& b )
        {
            Vector temp = *this;

            temp += b;

            return temp;
        }

        Vector operator- (const Vector& b )
        {
            Vector temp = *this;

            temp -= b;

            return temp;
        }

        template< class DataType >
        Vector operator/ (const DataType& b )
        {
            Vector temp = *this;

            temp /= b;

            return temp;
        }

        template< class DataType >
        Vector operator* ( const DataType& b )
        {
            Vector temp = *this;

            temp *= b;

            return temp;
        }

        bool operator== ( const Vector& b )
        {
            return ( x == b.x && y == b.y );
        }

        long double operator* ( const Vector& b ) //dot product
        {
            return (x * b.x + y * b.y );
        }

    };
}
#endif // MATH_HPP_INCLUDED
