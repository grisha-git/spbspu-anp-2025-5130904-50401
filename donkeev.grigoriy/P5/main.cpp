#include <iostream>
namespace donkeev
{
  struct point_t
  {
    double x, y;
  };
  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() = 0;
    virtual rectangle_t getFrameRect() = 0;
    virtual void move(const point_t&) = 0;
    virtual void move(const double, const double) = 0;
    virtual void isotropicScaling(double) = 0;
  };

}
int main()
{
  
}