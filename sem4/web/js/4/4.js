function sortRows(table, column) {
    let tbody = table.getElementsByTagName("tbody")[0];
    let rows = Array.from(tbody.getElementsByTagName("tr"));
    var th = table.getElementsByTagName("tr")[0].children[column];
    rows.sort((a, b) => ("" + a.children[column].innerHTML).localeCompare(b.children[column].innerHTML, undefined, { numeric: true }));
    if (th.classList.contains("inc")) {
        th.classList.remove("inc")
        rows.reverse();
        th.classList.add("dec");
    }
    else {
        th.classList.remove("dec")
        th.classList.add("inc");
        
    }
    tbody.innerHTML = "";
    for (let row of rows) tbody.append(row);
}

function init() {
    for (let table of document.getElementsByClassName("sort-row")) {
        let i = 0;
        let row = table.getElementsByTagName("tr")[0];
        for (let column of row.children) {
            let j = i;
            column.addEventListener("click", () => sortRows(table, j));
            i++;
        }
    }
}
