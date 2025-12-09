#include <implot.h>
#include <omdi.hpp>

#include <array>

auto main() -> int {
  omdi::logger::Init();

  auto timer = omdi::utils::Timer();

  auto state = omdi::State();
  state.set("window_width", 1920);
  state.set("window_height", 1080);

  auto app = omdi::App(&state);

  // managers
  auto fontManager = omdi::FontManager();

  // components
  auto styleDialog = omdi::StyleDialog();
  auto menubar     = omdi::Menubar();

  menubar.AddLeft([&]() {
    // BAD (ok if logic is simple):
    // if (ImGui::BeginMenu("Help")) {
    //   ...
    //   ImGui::EndMenu();
    // }

    // GOOD:
    omdi::Component(
      []() { // opener
        return ImGui::BeginMenu("File");
      },
      [&]() { // logic (on button press)
        if (ImGui::MenuItem("Customize UI")) {
          state.set("show_style_dialog", true);
        }
      },
      []() { // closer
        ImGui::EndMenu();
      });
  });

  menubar.AddLeft([&]() {
    // BAD (ok if logic is simple):
    // if (ImGui::BeginMenu("Help")) {
    //   ...
    //   ImGui::EndMenu();
    // }

    // GOOD:
    omdi::Component(
      []() { // opener
        return ImGui::BeginMenu("Help");
      },
      [&]() { // logic (on button press)
        ImGui::Checkbox("Show ImGui demo", &state.get<bool>("show_imgui_demo"));
      },
      []() { // closer
        ImGui::EndMenu();
      });
  });

  auto managers = omdi::managers_t {
    { "font_manager", &fontManager },
  };

  auto components = omdi::components_t {
    {      "menubar",     &menubar },
    { "style_dialog", &styleDialog },
  };

  state.set("show_imgui_demo", false);

  // synthetic data
  const auto npts   = 1000u;
  auto       data_x = std::array<float, npts> {};
  auto       data_y = std::array<float, npts> {};
  for (auto i = 0u; i < npts; ++i) {
    data_x[i] = (float)i / (float)npts * 10.0f;
    data_y[i] = 0.5f + 0.5f * sinf(data_x[i] * 2.0f * M_PI / 5.0f) +
                (float)rand() / (float)RAND_MAX * 0.1f;
  }

  const auto nscat  = 10000u;
  auto       scat_x = std::array<float, nscat> {};
  auto       scat_y = std::array<float, nscat> {};
  for (auto i = 0u; i < nscat; ++i) {
    const float a = (int)((float)rand() / (float)RAND_MAX * 6.0f) * 0.3333 * M_PI +
                    (float)rand() / (float)RAND_MAX * 0.5f;
    const float t = (float)rand() / (float)RAND_MAX * 5.0f;
    scat_x[i]     = t * cosf(2.0 * t + a);
    scat_y[i]     = t * sinf(2.0 * t + a);
  }

  const auto nx = 512u;
  const auto ny = 512u;
  auto       xs = new float[nx];
  auto       ys = new float[ny];

  for (auto i = 0u; i < nx; ++i) {
    xs[i] = i * 0.01f - 2.56f;
  }
  for (auto j = 0u; j < ny; ++j) {
    ys[j] = j * 0.015f;
  }

  auto zfunc = [](float x, float y, float t) {
    return std::sinf(x * (2.0 * M_PI) + t) *
           std::cosf(y * (2.0 * M_PI) + 1.5 * t) * std::expf(-4.0 * (x * x));
  };

  auto zs = new float[nx * ny];
  for (auto j = 0u; j < ny; ++j) {
    for (auto i = 0u; i < nx; ++i) {
      auto x         = xs[i];
      auto y         = ys[j];
      zs[j * nx + i] = zfunc(x, y, 0.0f);
    }
  }

  app.Init(&state, managers);
  app.Render(
    &state,
    [&]() {
      if (state.get<bool>("show_imgui_demo")) {
        ImGui::ShowDemoWindow(&state.get<bool>("show_imgui_demo"));
      }
      if (ImGui::Begin("MyWindow")) {
        ImGui::Text("Pick a color:");
        static float color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
        ImGui::ColorEdit4("Color", color);

        ImGui::Text("You picked: %.2f, %.2f, %.2f, %.2f",
                    color[0],
                    color[1],
                    color[2],
                    color[3]);

        ImPlot::PushStyleColor(ImPlotCol_Line,
                               ImVec4(color[0], color[1], color[2], color[3]));

        // ALTERNATIVE: only for next item
        // ImPlot::SetNextLineStyle(ImVec4(color[0], color[1], color[2], color[3]));

        if (ImPlot::BeginPlot("lineplot")) {
          ImPlot::PlotLine("sine-ish", data_x.data(), data_y.data(), npts);
          ImPlot::EndPlot();
        }

        // ALTERNATIVE: using push style var
        // ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 4.0f);
        // ... also call ImPlot::PopStyleVar later

        ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 1.0f);

        if (ImPlot::BeginPlot("scatterplot", ImVec2(-1, -1), ImPlotFlags_Equal)) {
          ImPlot::PlotScatter("random scatter", scat_x.data(), scat_y.data(), nscat);
          ImPlot::EndPlot();
        }

        ImPlot::PopStyleColor();

        ImGui::End();
      }

      if (ImGui::Begin("Heatmap panel")) {
        ImPlot::PushColormap(ImPlotColormap_Viridis);

        if (ImPlot::BeginPlot("heatmap", ImVec2(-1, -1), ImPlotFlags_Equal)) {
          // ImPlot::PlotHeatmap("heatmap",
          //                     zs,
          //                     nx,
          //                     ny,
          //                     -1.0,
          //                     1.0,
          //                     nullptr,
          //                     ImPlotPoint(xs[0], ys[0]),
          //                     ImPlotPoint(xs[nx - 1], ys[ny - 1]));
          omdi::implot::PlotHeatmap("heatmap",
                                    zs,
                                    nx,
                                    ny,
                                    -1.0,
                                    1.0,
                                    ImPlotPoint(xs[0], ys[0]),
                                    ImPlotPoint(xs[nx - 1], ys[ny - 1]));
          ImPlot::EndPlot();
        }

        ImPlot::PopColormap();

        ImGui::End();
      }

      for (auto j = 0u; j < ny; ++j) {
        for (auto i = 0u; i < nx; ++i) {
          auto x         = xs[i];
          auto y         = ys[j];
          zs[j * nx + i] = zfunc(x, y, timer.elapsed());
        }
      }

      omdi::logger::Log("FPS: %.1f", 1.0 / timer.delta());
      timer.tick();
    },
    components,
    managers);

  return 0;
}
