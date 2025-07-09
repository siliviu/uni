const left = document.createElement('div');
left.classList.add('left');

const right = document.createElement('div');
right.classList.add('right');
document.body.append(left);
document.body.append(right);


const root = document.createElement('ul');
root.classList.add('tree-root')
left.append(root);
items = []

function load(id) {
    fetch(`load.php?id=${id}`)
        .then(response => response.text())
        .then(data => {
            const items = JSON.parse(data);
            for (let item of items)
                addItem(JSON.parse(item));
        })
}

function addItem(details) {
    const li = document.createElement('li');

    const span = document.createElement('span');
    span.innerText = details.name;
    li.append(span);

    if (details.type == 'Folder') {
        span.classList.add('caret');
        span.onclick = () => {
            span.parentElement.querySelector(".tree").classList.toggle("active");
            span.classList.toggle("caret-down");
            if (!span.nextSibling.classList.contains('loaded')) {
                load(details.id);
                span.nextSibling.classList.add('loaded');
            }
        }
        const ul = document.createElement('ul');
        ul.classList.add('tree');
        li.append(ul);
    }
    else
        span.onclick = () => right.innerText = `${details.name}\n\n${details.content}`;

    items[details.id] = li;
    if (details.id == 0)
        root.append(li);
    else
        items[details.parent].querySelector('ul').append(li);
}

load(-1);
