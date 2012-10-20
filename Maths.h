#ifndef MATHS_H
#define MATHS_H

#include <math.h>


/**
 * By Daniel Soltyka
 * http://www.danielsoltyka.com/programming/2010/05/30/c-vector2d-rectangle-classes/
 */
class Vector2D
{
public:
    Vector2D(float x = 0, float y = 0);
    ~Vector2D() {};

    void Rotate( const float angle );
    float Magnitude() const;
    float Normalize();
    float DotProduct( const Vector2D& v2 ) const;
    float CrossProduct( const Vector2D& v2 ) const;

    static Vector2D Zero();
    static float Distance( const Vector2D& v1, const Vector2D& v2);

    Vector2D& operator= ( const Vector2D& v2 );

    Vector2D& operator+= ( const Vector2D& v2 );
    Vector2D& operator-= ( const Vector2D& v2 );
    Vector2D& operator*= ( const float scalar);
    Vector2D& operator/= ( const float scalar);

    const Vector2D operator+( const Vector2D &v2 ) const;
    const Vector2D operator-( const Vector2D &v2 ) const;
    const Vector2D operator*( const float scalar ) const;
    const Vector2D operator/( const float scalar ) const;

    bool operator== ( const Vector2D& v2 ) const;
    bool operator!= ( const Vector2D& v2 ) const;

public:
    float x, y;
};


class Rectangle
{
public:
    Rectangle( int x = 0, int y = 0, int w = 0, int h = 0 );
    ~Rectangle( void ) {};

    inline int Left( void ) const { return x; }
    inline int Right( void ) const { return x + w; }
    inline int Top( void ) const { return y; }
    inline int Bottom( void ) const { return y + h; }

    bool Contains( Vector2D& vVec ) const;
    bool Contains( int x, int y ) const;

    static Rectangle Empty();

    // Static methods below are derived from the RectangleExtensions class
    // written in C#, released under the MSPL
    static Vector2D GetIntersectionDepth( const Rectangle& rectA, const Rectangle& rectB );
    static Vector2D GetBottomCenter( const Rectangle& rect );
    static Vector2D GetCenter( const Rectangle& rect );
    static float GetDistance( const Rectangle& rectA, const Rectangle& rectB);
    static Vector2D GetDirection( const Rectangle& rectA, const Rectangle& rectB);

    Rectangle& operator= ( const Rectangle& r2 );

    bool operator== ( const Rectangle& r2 ) const;
    bool operator!= ( const Rectangle& r2 ) const;

public:
    int x, y, w, h;
};

#endif // MATHS_H
