$("button").on("click", (e) => init($(e.target).attr('class')));

var selected = null;
var override = false;
const n = 4;

function shuffle(array) {
    let currentIndex = array.length;
    while (currentIndex != 0) {
        let randomIndex = Math.floor(Math.random() * currentIndex);
        currentIndex--;
        [array[currentIndex], array[randomIndex]] = [array[randomIndex], array[currentIndex]];
    }
}

function init(type) {
    let left = n * n;
    let squares = [];
    for (let i = 0; i < n; i++) for (let j = 0; j < n; j++) squares.push([i, j]);
    shuffle(squares);
    let m = new Array(n).fill(0).map(() => new Array(n));
    for (let i = 1; i <= left / 2; ++i) {
        const [y1, x1] = squares.pop();
        const [y2, x2] = squares.pop();
        m[y1][x1] = m[y2][x2] = i;
    }

    let table = $("<table></table>");
    $("body").append(table);
    const changeState = (e, first = false) => {
        e.find(">:first-child").toggle(first ? 0 : 100);
        if (type == "fruit") {
            e.css("background-size", e.css("background-size") == "cover" ? "0" : "cover");
        }
    };
    for (let i = 0; i < n; ++i) {
        let tr = $("<tr></tr>");
        for (let j = 0; j < n; ++j) {
            let td = $("<td></td>");
            let s = $("<span></span>");
            if (type == "text") s.text(m[i][j]);
            else td.css({ backgroundImage: `url(${m[i][j]}.png)`, backgroundSize: "cover" });
            td.append(s);
            td.attr("class", "_" + m[i][j]);
            changeState(td, true);
            td.on("click", () => {
                if (td.find(">:first-child").css("display") == "none" && override == false) {
                    if (selected == null) {
                        changeState(td);
                        selected = td;
                    } else {
                        changeState(td);
                        if (td.attr("class") == selected.attr("class")) {
                            selected = null;
                            left -= 2;
                            if (left == 0) alert("You won!");
                            return;
                        }
                        override = true;
                        setTimeout(() => {
                            changeState(td);
                            changeState(selected);
                            selected = null;
                            override = false;
                        }, 750);
                    }
                }
            });
            tr.append(td);
        }
        $("table").append(tr);
    }
    $("button").remove();
}
