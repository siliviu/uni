$("button").on("click", (e) => init($(e.target).attr('class')));

var pos = "";
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
    for (let i = 1; i <= left - 1; ++i) {
        const [y, x] = squares.pop();
        m[y][x] = i;
    }
    let grid = new Array(n).fill(0).map(() => new Array(n));
    let table = $("<table></table>");
    const swap = (yy, xx) => {
        if (type == "text") {
            grid[y][x].html(grid[yy][xx].html());
            grid[yy][xx].html(" ");
        } else {
            grid[y][x].css("background", grid[yy][xx].css("background"));
            grid[yy][xx].css("background", "");
        }
        pos = [yy, xx];
    };
    for (let i = 0; i < n; ++i) {
        let tr = $("<tr></tr>");
        for (let j = 0; j < n; ++j) {
            let td = $("<td></td>");
            let s = $("<span></span>");
            if (type == "text") s.text(m[i][j]);
            else if (m[i][j]) {
                y = Math.floor((m[i][j] - 1) / n);
                x = (m[i][j] - 1) % n;
                td.css("background", `url(home.jpg) calc(-7vw * ${x}) calc(-7vw * ${y})`);
            }
            grid[i][j] = td;
            if (!m[i][j]) pos = [i, j];
            td.append(s);
            tr.append(td);
        }
        table.append(tr);
    }
    $("body").on("keydown", (e) => {
        [y, x] = pos;
        switch (e.which) {
            case 38:
                if (y == 0) return;
                swap(y - 1, x);
                break;
            case 37:
                if (x == 0) return;
                swap(y, x - 1);
                break;
            case 39:
                if (x == n - 1) return;
                swap(y, x + 1);
                break;
            case 40:
                if (y == n - 1) return;
                swap(y + 1, x);
                break;
        }
    });
    $("body").append(table);
    $("button").remove();
}
