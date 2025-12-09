#include <omdi.hpp>

auto main() -> int {
  auto state = omdi::State();
  auto app   = omdi::App(&state);

  app.Init(&state);
  app.Render(&state);

  return 0;
}
