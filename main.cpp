#include <omdi.hpp> // import the main omdi header

auto main() -> int {
  auto state = omdi::State();
  state.set("show_imgui_demo", false);

  state.set("my_color", new float[4] { 0.0f, 0.5f, 0.5f, 1.0f });

  auto app = omdi::App(&state);

  auto menubar     = omdi::menubar::Menubar();
  auto styleDialog = omdi::config::StyleDialog();
  auto fontManager = omdi::fonts::FontManager();

  menubar.AddLeft([&]() {
    omdi::safe::Component(
      []() {
        return ImGui::BeginMenu("Help");
      },
      [&]() {
        ImGui::Checkbox("Show ImGui demo", &state.get<bool>("show_imgui_demo"));
      },
      []() {
        ImGui::EndMenu();
      });
  });

  menubar.AddLeft([&]() {
    omdi::safe::Component(
      []() {
        return ImGui::BeginMenu("UI");
      },
      [&]() {
        if (ImGui::MenuItem("Style dialog")) {
          state.set("show_style_dialog", true);
        }
      },
      []() {
        ImGui::EndMenu();
      });
  });

  auto components = omdi::components_t {
    {      "menubar",     &menubar },
    { "style_dialog", &styleDialog }
  };

  auto managers = omdi::managers_t {
    { "font_manager", &fontManager }
  };

  app.Init(&state, managers);
  app.Render(
    &state,
    [&]() {
      if (state.get<bool>("show_imgui_demo")) {
        ImGui::ShowDemoWindow();
      }
      if (ImGui::Begin("Test Window")) {
        ImGui::Text("Pick a random color");
        ImGui::ColorEdit4("Color", state.get<float*>("my_color"));
        const auto color = state.get<float*>("my_color");
        ImGui::Text("You picked: %.2f, %.2f, %.2f, %.2f",
                    color[0],
                    color[1],
                    color[2],
                    color[3]);
        ImGui::End();
      }
    },
    components,
    managers);

  return 0;
}