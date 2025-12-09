import dearpygui.dearpygui as dpg
import numpy as np

dpg.create_context()

with dpg.font_registry():
    default_font = dpg.add_font("fonts/MonaspiceKrNerdFont-Regular.otf", 16)
    dpg.bind_font(default_font)


with dpg.viewport_menu_bar():
    with dpg.menu(label="File"):
        dpg.add_menu_item(
            label="Style Editor", callback=lambda: dpg.show_item("style_dialog")
        )
        dpg.add_menu_item(label="Exit", callback=lambda: dpg.stop_dearpygui())

with dpg.window(label="Style dialog", show=False, tag="style_dialog"):
    dpg.add_color_edit(
        label="background color",
        no_alpha=True,
        callback=lambda s, a, u: dpg.set_viewport_clear_color([c * 255 for c in a]),
    )

npts = 1000
data_x = np.linspace(0, 10, npts)
data_y = 0.5 + 0.5 * np.sin(data_x * 2.0 * np.pi / 5.0) + np.random.rand(npts) * 0.1

nscat = 10000
avals = (np.random.randint(0, 6, nscat) * 0.3333 * np.pi) + (
    np.random.rand(nscat) * 0.5
)
tvals = np.random.rand(nscat) * 5.0
scat_x = tvals * np.cos(2.0 * tvals + avals)
scat_y = tvals * np.sin(2.0 * tvals + avals)
del avals, tvals


with dpg.window(label="Example Window"):
    with dpg.theme(tag="line_theme"):
        with dpg.theme_component(dpg.mvLineSeries):
            dpg.add_theme_color(
                dpg.mvPlotCol_Line,
                (255, 50, 50, 255),
                category=dpg.mvThemeCat_Plots,
                tag="line_color",
            )

    with dpg.theme(tag="scatter_theme"):
        with dpg.theme_component(dpg.mvScatterSeries):
            dpg.add_theme_style(
                dpg.mvPlotStyleVar_MarkerSize, 1.0, category=dpg.mvThemeCat_Plots
            )

    dpg.add_text("Pick a color:")

    def color_callback(_, app_data, user_data):
        dpg.set_value("color_display", user_data % tuple(app_data[:3]))
        dpg.configure_item(
            "line_color", value=[int(c * 255) for c in app_data[:3]] + [255]
        )

    dpg.add_color_edit(
        label="Color",
        callback=color_callback,
        user_data="You picked %.2f %.2f %.2f",
    )
    dpg.add_text("", tag="color_display")
    with dpg.plot(label="line plot", width=-1, height=0):
        dpg.add_plot_axis(dpg.mvXAxis, label="x")
        with dpg.plot_axis(dpg.mvYAxis, label="y"):
            dpg.add_line_series(
                data_x,  # pyright: ignore
                data_y,  # pyright: ignore
                label="sine-ish",
                tag="line_series",
            )
        dpg.bind_item_theme("line_series", "line_theme")

    with dpg.plot(label="scatter plot", width=-1, height=0, equal_aspects=True):
        dpg.add_plot_axis(dpg.mvXAxis, label="x")
        with dpg.plot_axis(dpg.mvYAxis, label="y"):
            dpg.add_scatter_series(
                scat_x,  # pyright: ignore
                scat_y,  # pyright: ignore
                label="spiral-ish",
                tag="scatter_series",
            )
        dpg.bind_item_theme("scatter_series", "scatter_theme")

dpg.create_viewport(title="dpg example", width=1280, height=1024)

dpg.set_viewport_clear_color([32, 32, 64, 255])


dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
