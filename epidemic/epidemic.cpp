#include "epidemic.hpp"

#include <stdexcept>

namespace ep {

// Constructor

Epidemic::Epidemic(const double beta, const double gamma,
                   const Population<int>& initial_population, const int T)
    : beta_(beta),
      gamma_(gamma),
      initial_population_(initial_population),
      T_(T),
      N_(initial_population_.S + initial_population_.I + initial_population_.R),
      critic_level_(0.6),
      lockdown_duration_(14) {
  // Throws
  if (beta_ < 0. || beta_ > 1.) {
    throw std::runtime_error{"Error: \u03B2 must be between 0 and 1"};
  }
  if (gamma_ < 0. || gamma_ > 1.) {
    throw std::runtime_error{"Error: \u03B3 must be between 0 and 1"};
  }
  if (beta_ / gamma_ <= 1) {
    throw std::runtime_error{"Error: \u03B2/\u03B3 must be greater than 1"};
  }
  if (initial_population_.S < 0) {
    throw std::runtime_error{
        "Error: initial number of susceptible people must be greater than "
        "or equal to 0"};
  }
  if (initial_population_.I < 0) {
    throw std::runtime_error{
        "Error: initial number of infectious people must be greater than "
        "or equal to 0"};
  }
  if (initial_population_.R < 0) {
    throw std::runtime_error{
        "Error: initial number of recovered people must be greater than "
        "or equal to 0"};
  }
  if (T_ < 0) {
    throw std::runtime_error{
        "Error: the epidemic can't last a negative number of days"};
  }

  // Setting simulation_double_ with calculate of lockdown functions
  Population<double> initial_population_double = {
      static_cast<double>(initial_population.S),
      static_cast<double>(initial_population.I),
      static_cast<double>(initial_population.R)};
  simulation_double_.push_back(initial_population_double);
  int i = 0;
  while (i < T_) {
    if (simulation_double_[i].I < critic_level_ * N_) {
      Population<double> next_state = calculate(simulation_double_[i]);
      simulation_double_.push_back(next_state);
      ++i;
    } else {
      int lockdownDays = std::min(T_ - i, lockdown_duration_);
      for (int a = 0; a < lockdownDays; ++a) {
        Population<double> next_state = lockdown(simulation_double_[i]);
        simulation_double_.push_back(next_state);
        ++i;
      }
    }
  }
}

// Private methods

Population<double> Epidemic::calculate(
    const Population<double>& prev_state) const {
  Population<double> next_state;
  next_state.S = prev_state.S - beta_ * prev_state.S * prev_state.I / N_;
  next_state.I = prev_state.I + beta_ * prev_state.S * prev_state.I / N_ -
                 gamma_ * prev_state.I;
  next_state.R = prev_state.R + gamma_ * prev_state.I;
  return next_state;
}

Population<double> Epidemic::lockdown(
    const Population<double>& prev_state) const {
  Population<double> next_state;
  next_state.S = prev_state.S;
  next_state.R = prev_state.R + gamma_ * prev_state.I;
  next_state.I = N_ - prev_state.S - next_state.R;
  return next_state;
}

Population<int> Epidemic::round(const Population<double>& double_state) const {
  Population<int> int_state;
  int_state.S = std::round(double_state.S);
  int_state.I = std::round(double_state.I);
  int_state.R = std::round(double_state.R);
  return int_state;
}

Population<int> Epidemic::keep_total_constant(
    const Population<int>& population_state) const {
  Population<int> modified_state = population_state;
  int tot = modified_state.S + modified_state.I + modified_state.R;
  if (tot != N_) {
    int diff = tot - N_;
    if (diff > 0) {
      modified_state.R -= diff;
    } else {
      modified_state.S -= diff;
    }
  }
  return modified_state;
}

// Public methods

std::vector<Population<int> > Epidemic::evolution() const {
  std::vector<Population<int> > simulation_int_;
  for (const auto& population_state_double : simulation_double_) {
    simulation_int_.push_back(
        keep_total_constant(round(population_state_double)));
  }
  return simulation_int_;
}

std::vector<Population<double> > Epidemic::get_simulation_double() const {
  return simulation_double_;
}

Population<int> Epidemic::get_initial_population_() const {
  return initial_population_;
}

int Epidemic::getN() const { return N_; }

int Epidemic::getT() const { return T_; }

double Epidemic::get_beta() const { return beta_; }

double Epidemic::get_gamma() const { return gamma_; }

void Epidemic::print_results() const {
  std::ofstream outputFile("results.txt");

  if (outputFile.is_open()) {
    outputFile << "Report of each of the stored states of population:\n";
    std::vector<Population<int>> population_state_ = evolution();
    outputFile << std::setw(12) << std::left << "Day " << std::setw(12)
               << std::left << "S " << std::setw(12) << std::left << "I "
               << std::setw(6) << std::left << "R " << '\n'
               << "----------------------------------------\n";
    ;

    int i{};
    for (auto& state : population_state_) {
      outputFile << std::setw(12) << std::left << i << std::setw(12)
                 << std::left << state.S << std::setw(12) << std::left
                 << state.I << std::setw(6) << std::left << state.R << '\n';
      ++i;
    }

    outputFile.close();

    std::cout << "Results succesfully saved to results.txt.\n";
  } else {
    std::cerr << "Error opening results.txt.\n";
  }
}
}  // namespace ep