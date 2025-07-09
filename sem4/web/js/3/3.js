var selected = null;
var override = false;
const n = 4;

// stolen
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
    // const styleSheet = styleEl.sheet;

    let left = n * n;
    let squares = [];
    for (let i = 0; i < n; i++) for (let j = 0; j < n; j++) squares.push([i, j]);
    shuffle(squares);
    let m = new Array(n).fill(0).map(() => new Array(n));
    for (let i = 1; i <= left / 2; ++i) {
        // if (type == "fruit")
        //     styleSheet.insertRule(
        //         `._${i} {
        //     background-image: url("${i}.png"); 
        //     background-size: cover;
        // }`,
        //         styleSheet.cssRules.length
        //     );
        const [y1, x1] = squares.pop();
        const [y2, x2] = squares.pop();
        m[y1][x1] = m[y2][x2] = i;
    }

    let table = document.createElement("table");
    const changeState = (e) => {
        e.firstChild.style.visibility = e.firstChild.style.visibility == "hidden" ? "visible" : "hidden";
        if(type=='fruit') {
            console.log(e.style.backgroundSize);
            e.style.backgroundSize = e.style.backgroundSize == "cover" ? "0" : "cover";
        }
    };
    for (let i = 0; i < n; ++i) {
        let tr = document.createElement("tr");
        for (let j = 0; j < n; ++j) {
            let td = document.createElement("td");
            let s = document.createElement("span");
            if (type == "text") 
                s.textContent = m[i][j];
            else {
                td.style.backgroundImage = `url(${m[i][j]}.png)`;
                td.style.backgroundSize = "cover";
            }
            td.appendChild(s);
            td.className = "_" + m[i][j];
            changeState(td);
            td.addEventListener("click", (e) => {
                if (td.firstChild.style.visibility == "hidden" && override == false) {
                    if (selected == null) {
                        changeState(td);
                        selected = td;
                    } else {
                        changeState(td);
                        if (td.className == selected.className) {
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
            tr.appendChild(td);
        }
        table.appendChild(tr);
    }
    document.body.append(table);
    document.body.removeChild(document.getElementsByTagName("button")[0])
    document.body.removeChild(document.getElementsByTagName("button")[0])
}
