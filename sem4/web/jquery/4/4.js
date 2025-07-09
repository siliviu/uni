function sortRows(table, column) {
    let tbody = $(table).find("tbody")[0];
    let rows = Array.from($(tbody).find("tr"));
    var th = $(table).find("tr")[0].children[column];
    rows.sort((a, b) => ("" + a.children[column].innerHTML).localeCompare(b.children[column].innerHTML, undefined, { numeric: true }));
    if ($(th).hasClass("inc")) {
        $(th).removeClass("inc").addClass("dec");
        rows.reverse();
    } else $(th).removeClass("dec").addClass("inc");
    tbody.innerHTML = "";
    for (let row of rows) $(tbody).append(row);
}

$(".sort-row").each((_, obj) => {
    $(obj)
        .find(">:first-child")
        .find(">:first-child")
        .children()
        .each((i, column) => $(column).on("click", () => sortRows(obj, i)));
});
