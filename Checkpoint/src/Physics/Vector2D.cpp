#include "Vector2D.hpp"
#include <math.h>

float Vector2D::magnitude()
{
    return sqrt(m_x*m_x + m_y*m_y);
}

void Vector2D::normalize()
{
    float m = magnitude();
    if (m > 0) {
        (*this) /= m;
    }
}
