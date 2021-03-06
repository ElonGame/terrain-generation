#include "Kernel.hpp"

#include <algorithm>

namespace terrain{


std::vector<Point> Kernel::neighbours(Point point, int rows, int cols)
{
  int x = point.x;
  int y = point.y;
  std::vector<Point> points;

  switch(kernel_type)
  {
    case MOORE:
      points = {Point(x-1, y-1), Point(x, y-1), Point(x+1, y-1),
                Point(x-1, y),                  Point(x+1, y),
                Point(x-1, y+1), Point(x, y+1), Point(x+1, y+1)};
      break;

    case VON_NEUMANN:
      points = {               Point(x, y-1),
                Point(x-1, y),                 Point(x+1, y),
                               Point(x, y+1)};
      break;

    case VON_NEUMANN2:
       points = {Point(x-1, y-1),              Point(x+1, y-1),

                Point(x-1, y+1),               Point(x+1, y+1)};
        break;
  };

  // Cull outlier points (unnessesarily opaque code)
  points.erase(std::remove_if(points.begin(), points.end(),
    [&](Point p) { return !pointInRange(p.y, p.x, rows, cols);  }), points.end());
  /*
  for (auto it = points.begin(); it != points.end(); ) {
    if(!pointInRange(it->y, it->x, rows, cols))
      points.erase(it);
    else
      ++it;
  }
   */

  return points;        
}

std::vector<Point> Kernel::neighbours(Point point, int rows, int cols, KernelType kt)
{
  int x = point.x;
  int y = point.y;
  std::vector<Point> points;

  switch(kt)
  {
    case MOORE:
      points = {Point(x-1, y-1), Point(x, y-1), Point(x+1, y-1),
                Point(x-1, y),                  Point(x+1, y),
                Point(x-1, y+1), Point(x, y+1), Point(x+1, y+1)};
      break;

    case VON_NEUMANN:
      points = {               Point(x, y-1),
                Point(x-1, y),                 Point(x+1, y),
                               Point(x, y+1)};
      break;

    case VON_NEUMANN2:
       points = {Point(x-1, y-1),              Point(x+1, y-1),

                Point(x-1, y+1),               Point(x+1, y+1)};
        break;
  };

  // Cull outlier points
  for (auto it = points.begin(); it != points.end(); ) {
    if(!pointInRange(it->y, it->x, rows, cols))
      points.erase(it);
    else
      ++it;
  }

  return points;        
}

} // namespace terrain