#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

namespace ep {

template <typename type>
struct Population {
  type S;
  type I;
  type R;
};

class Epidemic {
 private:
  const double beta_;
  const double gamma_;
  const Population<int> initial_population_;
  const int T_;
  const int N_;
  std::vector<Population<double> > simulation_double_;
  const double critic_level_;
  const int lockdown_duration_;

  // Function that calculates the development of the emidemic expressing the
  // number of people in S, I and R in double
  Population<double> calculate(const Population<double> &) const;

  // Function that calculates the development of the emidemic douring a lockdown
  Population<double> lockdown(Population<double> const &) const;

  // Function that converts the number of people from double to int
  Population<int> round(Population<double> const &) const;

  // Function that keep the total number S + I + R = N
  Population<int> keep_total_constant(Population<int> const &) const;

 public:
  // Constructor
  Epidemic(const double, const double, Population<int> const &, const int);

  // Function that calculates the development of the epidemic expressing the
  // number of people in S, I and R in int
  std::vector<Population<int> > evolution() const;

  // Getter methods
  std::vector<Population<double> > get_simulation_double() const;
  Population<int> get_initial_population_() const;
  int getN() const;
  int getT() const;
  double get_beta() const;
  double get_gamma() const;

  // Saving resunts on file
  void print_results() const;
};
}  // namespace ep

#endif