const n = 3;
var turn, finished = false;

const table = document.createElement("table");
const grid = new Array(n).fill(0).map(() => new Array(n));
const chars = ['0', 'X']

for (let i = 0; i < n; ++i) {
    const tr = document.createElement("tr");
    for (let j = 0; j < n; ++j) {
        const td = document.createElement("td");
        grid[i][j] = td;
        td.onclick = e => {
            if (grid[i][j].innerText)
                return;
            fetch(`move.php?y=${i}&x=${j}`)
                .then(response => response.text())
                .then(data => {
                    grid[i][j].innerText = chars[turn];
                    data = JSON.parse(data);
                    console.log(data);
                    if (data.end && typeof data.y == 'undefined') {
                        alert("Game over");
                        return;
                    }
                    grid[data.y][data.x].innerText = chars[turn ^ 1];
                    if (data.end)
                        alert("Game over");
                })
        }
        tr.append(td);
    }
    table.append(tr);
}
document.body.append(table);

fetch("start.php")
    .then(response => response.text())
    .then(data => {
        data = JSON.parse(data);
        console.log(data);
        turn = data.turn;
        if (turn)
            grid[data.y][data.x].innerText = 'X';
        turn ^= 1;
    })
