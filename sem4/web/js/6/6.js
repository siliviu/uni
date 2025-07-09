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
    const styleEl = document.createElement("style");
    document.head.appendChild(styleEl);

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
    let table = document.createElement("table");
    const swap = (yy, xx) => {
        if (type == "text") {
            grid[y][x].innerHTML = grid[yy][xx].innerHTML;
            grid[yy][xx].innerHTML = " ";
        } else {
            grid[y][x].style.background = grid[yy][xx].style.background;
            grid[yy][xx].style.background = "";
        }
        pos = [yy, xx];
    };
    for (let i = 0; i < n; ++i) {
        let tr = document.createElement("tr");
        for (let j = 0; j < n; ++j) {
            let td = document.createElement("td");
            let s = document.createElement("span");
            if (type == "text") s.textContent = m[i][j];
            else if (m[i][j]) {
                y = Math.floor((m[i][j] - 1) / n);
                x = (m[i][j] - 1) % n;
                console.log(y, x);
                td.style.background = `url(home.jpg) calc(-7vw * ${x}) calc(-7vw * ${y})`;
            }
            grid[i][j] = td;
            if (!m[i][j]) pos = [i, j];
            td.appendChild(s);
            tr.appendChild(td);
        }
        table.appendChild(tr);
    }
    document.addEventListener(
        "keydown",
        (e) => {
            [y, x] = pos;
            switch (e.key) {
                case "ArrowUp":
                    if (y == 0) return;
                    swap(y - 1, x);
                    break;
                case "ArrowLeft":
                    if (x == 0) return;
                    swap(y, x - 1);
                    break;
                case "ArrowRight":
                    if (x == n - 1) return;
                    swap(y, x + 1);
                    break;
                case "ArrowDown":
                    if (y == n - 1) return;
                    swap(y + 1, x);
                    break;
            }
        },
        false
    );
    document.body.append(table);
    document.body.removeChild(document.getElementsByTagName("button")[0]);
    document.body.removeChild(document.getElementsByTagName("button")[0]);
}
