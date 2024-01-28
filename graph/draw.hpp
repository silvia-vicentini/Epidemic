
#ifndef DRAW_HPP
#define DRAW_HPP

#include <variant>

#include "curve/curve.hpp"
#include "grid/grid.hpp"
#include "key/key.hpp"
#include "text/text.hpp"

namespace ep {

class Draw {
 private:
  const Epidemic epidemic_;

  // Window on which to draw the curves
  sf::RenderWindow& window_;

  ep::Text text_;
  ep::Grid grid_;
  ep::Curve curve_;
  ep::Key key_;

 public:
  // Constructor
  Draw(const Epidemic&, sf::RenderWindow&);

  void draw_graph() const;
};
}  // namespace ep
#endif
