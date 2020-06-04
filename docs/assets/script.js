"use strict";

document.addEventListener("DOMContentLoaded", () => {
    renderMathInElement(document.body, {
        delimiters: [
            { left: "$$", right: "$$", display: true },
            { left: "$", right: "$", display: false }
        ],
        macros: {
            "\\order": "\\mathrm{O}",
            "\\sgn": "\\operatorname{sgn}"
        }
    });

    // clipboard.js
    const clipboard = new ClipboardJS(".copy-button");
    clipboard.on("success", e => {
        e.trigger.parentNode.classList.add("show-tooltip");
    });
    const tooltips = document.getElementsByClassName("tooltip");
    [].forEach.call(tooltips, e => {
        e.onanimationend = () => {
            e.parentNode.classList.remove("show-tooltip");
        };
    });
});
