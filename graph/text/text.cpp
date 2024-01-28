#include "text.hpp"

namespace ep {
// Constructor
Text::Text(const Epidemic& epidemic, sf::RenderWindow& window)
    : epidemic_(epidemic),
      window_(window),
      T_(epidemic_.getT()),
      N_(epidemic_.getN()),
      center_((window_.getSize().x - 2 * margin_) / 2 - 50.f),
      x_axis_title_x_(window_.getSize().x - 150.f),
      x_axis_title_y_(window_.getSize().y - margin_ / 2),
      x_number_y_(window_.getSize().y - 72.f),
      y_number_y_((window_.getSize().y - 90.f)),
      delta_y_(window_.getSize().y - 2 * margin_),
      delta_x_(window_.getSize().x - 2 * margin_),
      max_x_val_(nearest_multiple(x_partition_, T_)),
      max_y_val_(nearest_multiple(y_partition_, N_)) {
  font_.loadFromFile("../../Arialn.ttf");
}

// Private methods
sf::Text Text::createText(const std::string& content, const float x,
                          const float y, const int fontSize) const {
  sf::Text text(content, font_, fontSize);
  text.setFillColor(sf::Color::Black);
  text.setPosition(x, y);
  return text;
}

std::vector<sf::Text> Text::generateNumbers(int max, bool isVertical) const {
  std::vector<sf::Text> numbers;
  const int it = isVertical ? max_y_val_ : max_x_val_;
  for (int i = 0; i <= max; ++i) {
    std::string numberString = std::to_string(i * it / max);
    float x = isVertical ? y_number_x_ : margin_ + delta_x_* i/max;
    float y = isVertical ? y_number_y_ - delta_y_ * i / max : x_number_y_;
    sf::Text text = createText(numberString, x, y, axis_font_);
    numbers.push_back(text);
  }
  return numbers;
}

// Public methods
int Text::nearest_multiple(const int partition, const int real_val) const {
  int remainder = real_val % partition;
  if (remainder == 0) {
    return real_val;
  } else {
    return real_val + (partition - remainder);
  }
}

sf::Text Text::set_Title() const {
  sf::Text Title =
      createText("EPIDEMIC EVOLUTION", center_, title_y_, title_font_);
  return Title;
}

sf::Text Text::x_axis_name() const {
  sf::Text xAxisName =
      createText("Days", x_axis_title_x_, x_axis_title_y_, axis_font_);
  return xAxisName;
}

sf::Text Text::y_axis_name() const {
  sf::Text yAxisName = createText("Number of people", y_axis_title_x_,
                                  y_axis_title_y_, axis_font_);
  yAxisName.setRotation(-90.f);
  return yAxisName;
}

std::vector<sf::Text> Text::x_numbers() const {
  return generateNumbers(x_partition_, false);
}

std::vector<sf::Text> Text::y_numbers() const {
  return generateNumbers(y_partition_, true);
}
}  // namespace ep
