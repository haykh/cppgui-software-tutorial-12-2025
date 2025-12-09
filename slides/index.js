import "reveal.js/dist/reveal.css";
import "reveal.js/dist/theme/night.css";
import Markdown from "reveal.js/plugin/markdown/markdown.esm.js";
import Reveal from "reveal.js";
import "./style.css";

const deck = new Reveal();
deck.initialize({ hash: true, slideNumber: true, plugins: [Markdown] });
