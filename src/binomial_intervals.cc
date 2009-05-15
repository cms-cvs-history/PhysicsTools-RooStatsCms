#include "Math/QuantFuncMathCore.h"

#include "PhysicsTools/RooStatsCms/interface/binomial_intervals.h"

using ROOT::Math::beta_quantile;
using ROOT::Math::beta_quantile_c;

// Language of Brown, Cai, DasGupta: p = binomial parameter, X = # successes, n = # trials.

void clopper_pearson::calculate(const double X, const double n) {
  set(0, 1);
  if (X > 0)
    lower_ = beta_quantile  (alpha_min_, X,     n - X + 1);
  if (n - X > 0)
    upper_ = beta_quantile_c(alpha_min_, X + 1, n - X);
}
