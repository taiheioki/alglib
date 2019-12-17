"use strict";

document.addEventListener("DOMContentLoaded", () => {
    // KaTeX from https://qiita.com/mametank/items/fa2b8a03598c9548e461
    renderMathInElement(document.body, {
        delimiters: [
            {left: "$$", right: "$$", display: true},
            {left: "$", right: "$", display: false}
        ],
        macros: {
            "\\sgn": "\\operatorname{sgn}"
        }
    });
    
    // clipboard.js
    const clipboard = new ClipboardJS(".copy-button");
    clipboard.on('success', (e) => {
        e.trigger.parentNode.classList.add('show-tooltip');
    });
    const tooltips = document.getElementsByClassName('tooltip');
    [].forEach.call(tooltips, (e) => {
        e.onanimationend = () => {
            e.parentNode.classList.remove('show-tooltip')
        }
    })
});
