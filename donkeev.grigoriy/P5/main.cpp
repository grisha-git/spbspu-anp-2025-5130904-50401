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
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t&) = 0;
    virtual void move(const double, const double) = 0;
    virtual void scale(double) = 0;
  };
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t&);
    ~Rectangle() override = default;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(const double, const double) override;
    void scale(double) override;
  private:
    rectangle_t body;
  };
  Rectangle::Rectangle(const rectangle_t& rectangle):
    body(rectangle)
  {}
  double Rectangle::getArea() const
  {
    return body.height * body.width;
  }
  rectangle_t Rectangle::getFrameRect() const
  {
    return body;
  }
  void Rectangle::move(const point_t& target)
  {
    body.pos = target;
  }
  void Rectangle::move(const double dx, const double dy)
  {
    body.pos.x += dx;
    body.pos.y += dy;
  }
  void Rectangle::scale(double k)
  {
    body.height *= k;
    body.width *= k;
  }
  
}
int main()
{
  
}