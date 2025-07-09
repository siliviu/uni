$("select").on("click", (e) => $(e.target.parentNode).siblings().append(e.target.parentNode.selectedOptions[0]));
