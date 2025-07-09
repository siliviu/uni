const properties = ['name', 'producer', 'cpu', 'memory', 'storage']
const selectors = properties.slice(1);

const table = document.createElement('table');

const container = document.createElement('div');
container.classList.add('container');

const row = document.createElement('div');
row.classList.add('row');

let selects = []
for (const property of selectors) {
    const select = document.createElement('select');
    const placeholder = document.createElement('option');
    placeholder.innerText = property;
    selects[property] = select;

    select.append(placeholder);
    select.selectedIndex = 0;

    fetch(`options.php?attr=${property}`)
        .then(response => response.text())
        .then(data => {
            const items = JSON.parse(data);
            for (const item of items) {
                const option = document.createElement('option');
                option.innerText = item;
                select.append(option);
            }
        })
    row.append(select);
}
const button = document.createElement('button');
row.append(button);
button.innerText = 'Search';

container.append(row);
container.append(table);
document.body.append(container);

button.onclick = () => {
    let queryOptions = {}
    for (const property of selectors)
        if (selects[property].selectedIndex != 0)
            queryOptions[property] = selects[property].value;
    fetch('items.php?' + new URLSearchParams(queryOptions))
        .then(response => response.text())
        .then(data => {
            const items = JSON.parse(data);
            const table = document.getElementsByTagName('table')[0];
            table.replaceChildren();
            const thead = document.createElement('thead');
            for (const property of properties) {
                const td = document.createElement('td');
                td.innerHTML = property;
                thead.append(td);
            }
            table.append(thead);
            for (let item of items) {
                const trow = document.createElement('tr');
                item = JSON.parse(item);
                for (const property of properties) {
                    const td = document.createElement('td');
                    td.innerHTML = item[property];
                    trow.append(td);
                }
                table.append(trow);
            }
        })
}

button.click();