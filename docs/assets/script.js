"use strict";

document.addEventListener("DOMContentLoaded", () => {
    renderMathInElement(document.body, {
        delimiters: [
            { left: "$$", right: "$$", display: true },
            { left: "$", right: "$", display: false }
        ],
        macros: {
          "\\prn": "{\\left(#1\\right)}",
          "\\set": "{\\left\\{#1\\right\\}}",
          "\\defeq": "\\coloneqq",
          "\\funcdoms": "{#1}\\vcentcolon{#2}\\to{#3}",
          "\\join": "\\mathbin{\\vee}",
          "\\meet": "\\mathbin{\\wedge}",
          "\\Order": "\\mathrm{O}",
          "\\sgn": "\\operatorname{sgn}",
          "\\setR": "\\mathbb{R}",
          "\\iff": "\\Longleftrightarrow",
          "\\defiff": "\\overset{\\text{def}}{\\Longleftrightarrow}",
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
