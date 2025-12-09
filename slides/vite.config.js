import { defineConfig } from "vite";

export default defineConfig({
  base: "./",
  plugins: [
    {
      name: "reload",
      configureServer(server) {
        const { ws, watcher } = server;
        watcher.on("change", (file) => {
          if (file.endsWith(".md")) {
            server.ws.send({ type: "full-reload" });
          }
        });
      },
    },
  ],
});
