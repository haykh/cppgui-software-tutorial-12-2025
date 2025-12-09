import dearpygui.dearpygui as dpg

dpg.create_context()
dpg.create_viewport(title="Custom Title", width=1280, height=1024)

dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
