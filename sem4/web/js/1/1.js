function toggle(s) {
    nr = s.slice(-1) ^ 1;
    s = s.slice(0, -1) + nr;
    return s;
}

function move(list) {
    if (list.selectedIndex == -1) return;
    for (let sel of document.getElementsByClassName(toggle(list.className))) if (sel != list) sel.appendChild(list.selectedOptions[0]);
}
