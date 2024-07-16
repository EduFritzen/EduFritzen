#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__


class Vector2
{
public:
   float x, y;

   Vector2()
   {
      x = y = 0;
   }

   Vector2(float _x, float _y)
   {
       x = _x;
       y = _y;
   }

   float getX(){
       return x;
   }
   float getY(){
       return y;
   }

   void set(float _x, float _y)
   {
       x = _x;
       y = _y;
   }

   void normalize()
   {
       float norm = (float)sqrt(x*x + y*y);

       if(norm==0.0)
       {
          x = 1;
          y = 1;
          return;
       }
       x /= norm;
       y /= norm;
   }

    float distance(const Vector2& p) const {
        return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
    }

    Vector2 operator - (const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2 operator + (const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

   //Adicionem os demais overloads de operadores aqui.
    Vector2 operator * (float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator / (float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    float dot(const Vector2& v) const {
        return x * v.x + y * v.y;
    }

    Vector2 reflect(const Vector2& normal) const {
        return *this - normal * (2 * this->dot(normal));
    }
};

#endif
