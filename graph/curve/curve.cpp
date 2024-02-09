#include "curve.hpp"

#include <iostream>

namespace ep {

// Construictors
Curve::Curve(const Epidemic& epidemic, sf::RenderWindow& window)
    : epidemic_(epidemic),
      window_(window),
      population_state_(epidemic_.evolution()),
      T_(epidemic_.getT()),
      N_(epidemic_.getN()),
      margin_(80.f),
      dot_radius_(4.f),
      x_partition_(8),
      y_partition_(6),
      max_x_val_(nearest_multiple(x_partition_, T_)),
      max_y_val_(nearest_multiple(y_partition_, N_)),
      xscale_((window_.getSize().x - 2 * margin_) / max_x_val_) {}

const sf::Color SusceptibleColor(0, 0, 255);
const sf::Color InfectiousColor(230, 0, 0);
const sf::Color RemovedColor(20, 230, 0);

// Private methods
int Curve::nearest_multiple(const int partition, const int real_val) const {
  int remainder = real_val % partition;
  if (remainder == 0) {
    return real_val;
  } else {
    return real_val + (partition - remainder);
  }
}

std::vector<sf::VertexArray> Curve::generate_curve(
    const std::vector<int>& values, const sf::Color& color) const {
  std::vector<sf::VertexArray> curves;
  for (int i = 0; i < T_; ++i) {
    sf::VertexArray curve(sf::Lines, 2);
    curve[0].position = sf::Vector2f(
        margin_ + xscale_ * i,
        -margin_ + window_.getSize().y -
            (window_.getSize().y - 2 * margin_) / max_y_val_ * values[i]);
    curve[1].position = sf::Vector2f(
        margin_ + xscale_ * (i + 1),
        -margin_ + window_.getSize().y -
            (window_.getSize().y - 2 * margin_) / max_y_val_ * values[i + 1]);
    curve[0].color = curve[1].color = color;
    curves.push_back(curve);
  }
  return curves;
}

std::vector<sf::CircleShape> Curve::generate_dots(
    const std::vector<int>& values, const sf::Color& color) const {
  std::vector<sf::CircleShape> dots;
  for (int i = 0; i < T_; ++i) {
    sf::CircleShape dot(dot_radius_);
    dot.setFillColor(color);
    dot.setPosition(sf::Vector2f(
        margin_ + xscale_ * i,
        -margin_ + window_.getSize().y -
            (window_.getSize().y - 2 * margin_) / max_y_val_ * values[i] -
            dot_radius_ / 2));
    dots.push_back(dot);
  }
  return dots;
}

std::vector<int> Curve::S_values() const {
  std::vector<int> S_values;
  for (auto it=population_state_.begin(), last=population_state_.end();it!=last;++it) {
    S_values.push_back(it->S);
  }
  return S_values;
}

std::vector<int> Curve::I_values() const {
  std::vector<int> I_values;
  for (auto it=population_state_.begin(), last=population_state_.end();it!=last;++it) {
    I_values.push_back(it->.I);
  }
  return I_values;
}

std::vector<int> Curve::R_values() const {
  std::vector<int> R_values;
  for (auto it=population_state_.begin(), last=population_state_.end();it!=last;++it) {
    R_values.push_back(it->R);
  }
  return R_values;
}

// Public methods
std::vector<sf::VertexArray> Curve::S_curve() const {
  return generate_curve(S_values(), SusceptibleColor);
}

std::vector<sf::VertexArray> Curve::I_curve() const {
  return generate_curve(I_values(), InfectiousColor);
}

std::vector<sf::VertexArray> Curve::R_curve() const {
  return generate_curve(R_values(), RemovedColor);
}

std::vector<sf::CircleShape> Curve::S_dots() const {
  return generate_dots(S_values(), SusceptibleColor);
}

std::vector<sf::CircleShape> Curve::I_dots() const {
  return generate_dots(I_values(), InfectiousColor);
}

std::vector<sf::CircleShape> Curve::R_dots() const {
  return generate_dots(R_values(), RemovedColor);
}

}  // namespace ep
