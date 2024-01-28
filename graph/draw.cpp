#include "draw.hpp"

namespace ep {
// Constructor
Draw::Draw(const Epidemic& epidemic, sf::RenderWindow& window)
    : epidemic_(epidemic),
      window_(window),
      text_(epidemic, window_),
      grid_(window_),
      curve_(epidemic, window_),
      key_(window_) {}

void Draw::draw_graph() const {
  bool captured = false;

  std::cout << "Press S to save screenshot.\n";

  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      // Setting the command to close the window
      if (event.type == sf::Event::Closed) {
        window_.close();
      }
      // Setting the command S to save on file the graph
      else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::S && !captured) {
          captured = true;

          sf::Texture texture;
          texture.create(window_.getSize().x, window_.getSize().y);
          texture.update(window_);

          sf::Image screenshot = texture.copyToImage();

          if (screenshot.saveToFile("screenshot.jpeg")) {
            std::cout << "Screenshot successfully saved to screenshot.jpeg.\n";
          } else {
            std::cout << "Error saving to screenshot.jpeg.\n";
          }

          captured = false;
        }
      }
    }

    window_.clear(sf::Color::White);

    // Writing curves, grid, texts and the key on window
    std::vector<std::variant<sf::VertexArray, sf::Text>> vec1{
        text_.set_Title(),  grid_.bottom_side(), grid_.top_side(),
        grid_.left_side(),  grid_.right_side(),  text_.x_axis_name(),
        text_.y_axis_name()};

    for (const auto& element : vec1) {
      std::visit([&](const auto& e) { window_.draw(e); }, element);
    }

    std::vector<std::vector<sf::VertexArray>> vec2{
        grid_.horizontal_lines(), grid_.vertical_lines(), curve_.S_curve(),
        curve_.I_curve(),         curve_.R_curve(),       key_.key_lines()};

    for (const auto& vect_element : vec2) {
      for (const auto& element : vect_element) {
        window_.draw(element);
      }
    }

    std::vector<std::vector<sf::Text>> vec3{
        text_.x_numbers(), text_.y_numbers(), key_.key_description()};

    for (const auto& vect_element : vec3) {
      for (const auto& element : vect_element) {
        window_.draw(element);
      }
    }

    std::vector<std::vector<sf::CircleShape>> vec4{
        curve_.S_dots(), curve_.I_dots(), curve_.R_dots(), key_.key_dots()};

    for (const auto& vect_element : vec4) {
      for (const auto& element : vect_element) {
        window_.draw(element);
      }
    }

    window_.display();
  }
}

}  // namespace ep