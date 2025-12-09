import { defineConfig } from "vite";

export default defineConfig({
  plugins: [
    {
      name: "reload",
      configureServer(server) {
        const { ws, watcher } = server;
        watcher.on("change", (file) => {
          if (file.endsWith(".md")) {
            ws.send({
              type: "full-reload",
            });
          }
        });
      },
    },
  ],
});
