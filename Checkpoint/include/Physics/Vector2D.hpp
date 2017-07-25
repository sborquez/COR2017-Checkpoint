#ifndef __Vector2D__
#define __Vector2D__

class Vector2D
{
public:
    Vector2D() : m_x(0), m_y(0) {};
    Vector2D(float x, float y) : m_x(x), m_y(y) {};
    ~Vector2D() {};

    inline float getX() { return m_x; }
    inline float getY() { return m_y; }

    inline void setX(float x) { m_x = x; }
    inline void setY(float y) { m_y = y; }

    Vector2D operator+ (const Vector2D& v2) const
    {
        return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
    }

    Vector2D operator+= (const Vector2D& v2)
    {
        m_x += v2.m_x;
        m_y += v2.m_y;
        return *this;
    }
    
    Vector2D operator- (const Vector2D& v2) const
    {
        return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
    }

    Vector2D operator-= (const Vector2D& v2)
    {
        m_x -= v2.m_x;
        m_y -= v2.m_y;
        return *this;
    }

    Vector2D operator* (float scalar) const
    {
        return Vector2D(m_x*scalar, m_y*scalar);
    }

    Vector2D operator*= (float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        return *this;
    }

    Vector2D operator/ (float scalar) const
    {
        return Vector2D(m_x/scalar, m_y/scalar);
    }

    Vector2D operator/= (float scalar)
    {
        m_x /= scalar;
        m_y /= scalar;

        return *this;
    }

    float magnitude();

    void normalize();

private:
    float m_x;
    float m_y;
};

#endif