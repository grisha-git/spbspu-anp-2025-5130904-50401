#include <iostream>
#include <cmath>

namespace donkeev
{
  constexpr double PI = 3.14;
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
  class Polygon : public Shape
  {
  public:
    Polygon(const point_t*, size_t size, const point_t&);
    ~Polygon() override;
    Polygon(const Polygon&);
    Polygon& operator = (const Polygon&);
    Polygon(Polygon&&);
    Polygon& operator = (Polygon&&);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(const double, const double) override;
    void scale(double) override;
  private:
    point_t* points_;
    size_t size_;
    point_t pos_;
  };
  class Circle : public Shape
  {
  public:
    Circle(double, const point_t&);
    ~Circle() override = default;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(const double, const double) override;
    void scale(double) override;
  private:
    point_t center_;
    double radius_;
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
  void Rectangle::move(const point_t& d)
  {
    body.pos = d;
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
  Polygon::Polygon(const point_t* points, size_t size, const point_t& pos):
    points_(size ? new point_t[size] : nullptr),
    size_(size),
    pos_(pos)
  {
    if (points_ == nullptr)
    {
      throw std::bad_alloc();
    }
    else if (size_ < 3)
    {
      delete [] points_;
      throw std::logic_error("polygon contains more than 2 points");
    }
    for (size_t i = 0; i < size; ++i)
    {
      points_[i] = points[i];
    }
  }
  Polygon::~Polygon()
  {
    delete [] points_;
  }
  Polygon::Polygon(const Polygon& v):
    points_(new point_t[v.size_]),
    size_(v.size_),
    pos_(v.pos_)
  {
    for (size_t i = 0; i < size_; ++i)
    {
      points_[i] = v.points_[i];
    }
  }
  Polygon& Polygon::operator = (const Polygon& v)
  {
    point_t* temp = new point_t [v.size_];
    for (size_t i = 0; i < v.size_; ++i)
    {
      temp[i] = v.points_[i];
    }
    delete [] points_;
    points_ = temp;
    size_ = v.size_;
    pos_ = v.pos_;
    return *this;
  }
  Polygon::Polygon(Polygon&& v):
    points_(v.points_),
    size_(v.size_),
    pos_(v.pos_)
  {
    v.points_ = nullptr;
  }
  Polygon& Polygon::operator = (Polygon&& v)
  {
    if (this == &v)
    {
      return *this;
    }
    delete [] points_;
    points_ = v.points_;
    size_ = v.size_;
    pos_ = v.pos_;
    v.points_ = nullptr;
    return *this;
  }
  double Polygon::getArea() const
  {
    double area = 0.0;
    for (size_t i = 0; i < size_; ++i)
    {
      size_t j = (i + 1) % size_;
      area += points_[i].x * points_[j].y;
      area -= points_[j].x * points_[i].y;
    }
    return std::abs(area) / 2.0;
  }
  rectangle_t Polygon::getFrameRect() const
  {
    double minx = points_[0].x;
    double maxx = points_[0].x;
    double miny = points_[0].y;
    double maxy = points_[0].y;
    for (size_t i = 0; i < size_; ++i)
    {
      minx = points_[i].x < minx ? points_[i].x : minx;
      maxx = points_[i].x > maxx ? points_[i].x : maxx;
      miny = points_[i].y < miny ? points_[i].y : miny;
      maxy = points_[i].y > maxy ? points_[i].y : maxy;
    }
    rectangle_t frame;
    frame.height = maxy - miny;
    frame.width = maxx- minx;
    frame.pos = point_t{frame.width * 0.5, frame.height * 0.5};
    return frame;
  }
  void Polygon::move(const point_t& d)
  {
    pos_ = d;
    double dx = d.x - pos_.x;
    double dy = d.y - pos_.y;
    move(dx, dy);
  }
  void Polygon::move(const double dx, const double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
    for (size_t i = 0; i < size_; ++i)
    {
      points_[i].x += dx;
      points_[i].y += dy;
    }
  }
  void Polygon::scale(double k)
  {
    for (size_t i = 0; i < size_; ++i)
    {
      double dx = points_[i].x - pos_.x;
      double dy = points_[i].y - pos_.y;
      point_t newPoint = {pos_.x + dx * k, pos_.y + dy * k};
    }
  }
  Circle::Circle(double r, const point_t& c):
    center_(c),
    radius_(r)
  {}
  double Circle::getArea() const
  {
    return PI * radius_ * radius_;
  }
  rectangle_t Circle::getFrameRect() const
  {
    rectangle_t frame;
    frame.pos = center_;
    frame.height = radius_ * 2;
    frame.height = radius_ * 2;
    return frame;
  }
  void Circle::move(const point_t& d)
  {
    center_ = d;
  }
  void Circle::move(const double dx, const double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }
  void Circle::scale(double k)
  {
    radius_ *= k;
  }
}
int main()
{
  using namespace donkeev;
  Shape** shapes = new Shape* [3];
  shapes[0] = new Rectangle({7, 3, {2, 0}});
  try
  {
    const size_t size = 4;
    point_t* points = new point_t [size];
    points[0] = point_t {1.0, 1.0};
    points[1] = point_t {5.0, 1.0};
    points[2] = point_t {4.0, 4.0};
    points[3] = point_t {2.0, 4.0};
    shapes[1] = new Polygon(points, size, {3.0, 2.5});
  }
  catch(const std::bad_alloc& e)
  {
    std::cerr << "memory error\n";
  }
  catch(const std::logic_error& e)
  {
    std::cerr << e.what() << '\n';
  }
  shapes[2] = new Circle(13.5, {4, 7});
}
