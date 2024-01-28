// per compilare: " cmake --build build "
// per eseguire i test: " cmake --build build --target test "
// per eseguire: " ./build/cellular_automaton "

#include "simulation/simulation.hpp"

int main() {
  ep::Population<int> initial_population;
  std::cout << "Please write initial population's group S (susceptible):\n";
  std::cin >> initial_population.S;
  std::cout << "Please write initial population's group I (infectious):\n";
  std::cin >> initial_population.I;
  std::cout << "Please write initial population's group R (removed):\n";
  std::cin >> initial_population.R;

  double beta;
  double gamma;
  std::cout << "Please write epidemic's parameter beta (probability of getting "
               "infected) where 0<=beta<=1 :\n";
  std::cin >> beta;
  std::cout << "Please write epidemic's parameter gamma (probability of "
               "healing) where 0<=gamma<=1 and gamma < bet :\n";
  std::cin >> gamma;

  int T;
  std::cout << "Please write the duration in days of the epidemic T:\n";
  std::cin >> T;

  ep::Epidemic epidemic{beta, gamma, initial_population, T};

  sf::RenderWindow window(sf::VideoMode(1250, 1000), "Cellular Automaton");
  ep::Simulation cellular_automaton{window, epidemic};
  cellular_automaton.cellular_automaton();
}