#include "simulation.hpp"

namespace ep {
// Constructor
Simulation::Simulation(sf::RenderWindow& window, const Epidemic& epidemic)
    : window_(window),
      epidemic_(epidemic),
      initial_population_(epidemic.get_initial_population_()),
      beta_(epidemic.get_beta()),
      gamma_(epidemic.get_gamma()),
      T_(epidemic.getT()),
      N_(epidemic.getN()),
      parts_(std::ceil((std::sqrt(N_)))),
      N_cells_(parts_ * parts_),
      cell_length_((window_.getSize().x - 258.f) / parts_),
      key_cells_width_((window_.getSize().x - 258.f) / 10),
      eng(rd()) {
  font.loadFromFile("../Arialn.ttf");
}

// Private methods
std::vector<sf::RectangleShape> Simulation::key_cells() const {
  std::vector<sf::RectangleShape> key_cells(4);
  std::vector<sf::Color> colors{sf::Color::Blue, sf::Color::Red,
                                sf::Color::Green, sf::Color::White};
  for (int i{}; i < 4; ++i) {
    key_cells[i].setPosition(window_.getSize().x - 240.f,
                             600.f + key_cells_width_ * i);
    key_cells[i].setSize(
        sf::Vector2f(key_cells_width_ - 10.f, key_cells_width_ - 10.f));
    key_cells[i].setOutlineThickness(2);
    key_cells[i].setOutlineColor(sf::Color::Black);
    key_cells[i].setFillColor(colors[i]);
  }
  return key_cells;
}

std::vector<sf::Text> Simulation::key_texts() const {
  std::vector<sf::Text> key_texts(4);
  std::vector<std::string> words{"Susceptible", "Infectious", "Removed",
                                 "Empty"};
  for (int i{}; i < 4; ++i) {
    key_texts[i].setString(words[i]);
    key_texts[i].setFillColor(sf::Color::Black);
    key_texts[i].setPosition(window_.getSize().x - 140.f,
                             620.f + key_cells_width_ * i);
    key_texts[i].setFont(font);
    key_texts[i].setCharacterSize(30);
  }
  return key_texts;
}

sf::Text Simulation::set_text() const {
  sf::Text text;
  text.setFillColor(sf::Color::Black);
  text.setPosition(window_.getSize().x - 230.f, 40.f);
  text.setFont(font);
  text.setCharacterSize(30);
  text.setString("Day = " + std::to_string(dayCounter) +
                 "\n\nSusceptible = " + std::to_string(SCounter) +
                 "\n\nInfectious = " + std::to_string(ICounter) +
                 "\n\nRemoved = " + std::to_string(RCounter));
  return text;
}

std::vector<int> Simulation::display_grid_values() {
  std::vector<int> grid(N_cells_);

  std::vector<int> CellNumber(N_cells_);
  std::iota(CellNumber.begin(), CellNumber.end(), 0);
  std::shuffle(CellNumber.begin(), CellNumber.end(), eng);
  for (int i{0}; i < N_cells_; ++i) {
    if (i < initial_population_.S) {
      grid[CellNumber[i]] = 0;
    } else if (i < initial_population_.S + initial_population_.I) {
      grid[CellNumber[i]] = 1;
    } else if (i < initial_population_.S + initial_population_.I +
                       initial_population_.R) {
      grid[CellNumber[i]] = 2;
    } else {
      grid[CellNumber[i]] = 3;
    }
  }
  return grid;
}

void Simulation::draw_grid(const std::vector<int>& grid,
                           const sf::Vector2f& cell_vector) const {
  for (int x = 0; x < parts_; ++x) {
    for (int y = 0; y < parts_; ++y) {
      sf::RectangleShape cell;
      cell.setPosition(x * cell_length_ + 5, y * cell_length_ + 5);
      cell.setSize(cell_vector);
      cell.setOutlineThickness(2);
      cell.setOutlineColor(sf::Color::Black);
      if (grid[x + y * parts_] == 0) {
        cell.setFillColor(sf::Color::Blue);
      } else if (grid[x + y * parts_] == 1) {
        cell.setFillColor(sf::Color::Red);
      } else if (grid[x + y * parts_] == 2) {
        cell.setFillColor(sf::Color::Green);
      } else if (grid[x + y * parts_] == 3) {
        cell.setFillColor(sf::Color::White);
      }
      window_.draw(cell);
    }
  }
}

void Simulation::calculate(const std::vector<int>& grid,
                           std::vector<int>& gridNext) {
  for (int y = 0; y < parts_; ++y) {
    for (int x = 0; x < parts_; ++x) {
      int neighborSum{};
      int current = x + y * parts_;
      gridNext[current] = grid[current];
      // Calculating the probability of an S individual of moving to I
      if (grid[current] == 0) {
        neighborSum = calculate_neighborSum(x, y, neighborSum, grid);
        std::uniform_real_distribution<double> probDistribution(0.0, 1.0);
        double probNumber = probDistribution(eng);
        double prob = probability(neighborSum);
        if (probNumber < prob) {
          gridNext[current] = 1;
        }
      }
      // Calculating the probability of an I individual of moving to R
      else if (grid[current] == 1) {
        std::uniform_real_distribution<double> probDistribution(0.0, 1.0);
        double probNumber = probDistribution(eng);
        if (probNumber <= gamma_) {
          gridNext[current] = 2;
        }
      }
    }
  }
}

int Simulation::counter(const std::vector<int>& grid, const int val) {
  int counter{};
  for (int i : grid) {
    if (i == val) {
      ++counter;
    }
  }
  return counter;
}

// Public methods
int Simulation::calculate_neighborSum(const int x, const int y, int neighborSum,
                                      const std::vector<int>& grid) {
  for (int i = -1; i < 2; ++i) {
    int xi = wrapValue(x + i, parts_);
    for (int j = -1; j < 2; ++j) {
      int yj = wrapValue(y + j, parts_);
      if (i != 0 || j != 0) {
        if (grid[xi + yj * parts_] == 1) {
          ++neighborSum;
        }
      }
    }
  }
  return neighborSum;
}

double Simulation::probability(const int n) const {
  double result = 1 - std::pow((1 - beta_), n);
  return result;
}

int Simulation::wrapValue(const int v, const int vMax) const {
  if (v == -1) {
    return vMax - 1;
  }
  if (v == vMax) {
    return 0;
  }
  return v;
}

int Simulation::get_parts_() const { return parts_; }

void Simulation::cellular_automaton() {
  std::vector<int> grid = display_grid_values();
  std::vector<int> gridNext(N_cells_);

  // Cell dimensions
  const sf::Vector2f cell_vector(cell_length_, cell_length_);

  // Writing the state of the population in the first day (T=0)
  sf::Text text = set_text();

  sf::Clock clock;

  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_.close();
    }

    window_.clear(sf::Color::White);

    draw_grid(grid, cell_vector);
    ICounter = counter(grid, 1);

    if (clock.getElapsedTime().asSeconds() > 1.0f) {
      clock.restart();

      calculate(grid, gridNext);

      // Change gridNext to grid
      for (int i = 0; i < N_cells_; ++i) {
        grid[i] = gridNext[i];
      }

      // Calculate the number of S, I and R for each iteration
      ++dayCounter;
      SCounter = counter(grid, 0);
      ICounter = counter(grid, 1);
      RCounter = counter(grid, 2);
      text = set_text();
    }

    // Drawing key and text on window
    window_.draw(text);

    std::vector<sf::RectangleShape> key_cells_result = key_cells();
    for (auto& element : key_cells_result) {
      window_.draw(element);
    }

    std::vector<sf::Text> key_texts_results = key_texts();
    for (auto& element : key_texts_results) {
      window_.draw(element);
    }

    // Closing window when T days are passed
    if (dayCounter == T_ + 1) {
      break;
    }

    window_.display();
  }
}
}  // namespace ep
