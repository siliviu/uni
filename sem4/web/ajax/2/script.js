var page = 0, limit;
if (!JQUERY) {
    function changepage(inc) {
        page += inc;
        document.getElementsByClassName('prev')[0].disabled = (page == 0);
        document.getElementsByClassName('next')[0].disabled = (page == limit);
        document.getElementsByTagName('label')[0].innerText = `${page + 1}/${limit + 1}`;
        go();
    }
    function go() {
        fetch(`items.php?page=${page}`)
            .then(response => response.text())
            .then(data => {
                const items = JSON.parse(data);
                const table = document.getElementsByTagName("table")[0];
                while (table.rows.length > 1)
                    table.deleteRow(1);
                for (let item of items) {
                    item = JSON.parse(item);
                    const row = document.createElement("tr");
                    row.innerHTML = `   <td>${item.fname}</td>
                                        <td>${item.lname}</td>
                                        <td>${item.phone}</td>
                                        <td>${item.email}</td>`;
                    table.append(row);
                }
            })
    }
    fetch(`count.php`)
        .then(response => response.text())
        .then(data => {
            limit = Number(data);
            changepage(0);
        });
}
else {
    function changepage(inc) {
        page += inc;
        $('.prev')[0].disabled = (page == 0);
        $('.next')[0].disabled = (page == limit);
        $('label')[0].innerText = `${page + 1}/${limit + 1}`;
        go();
    }
    function go() {
        $.ajax({
            url: 'items.php',
            data: `page=${page}`,
            success: data => {
                const items = JSON.parse(data);
                const table = $("table")[0];
                while (table.rows.length > 1)
                    table.deleteRow(1);
                $(items).each((_, item) => {
                    item = JSON.parse(item);
                    const row = document.createElement("tr");
                    row.innerHTML = `   <td>${item.fname}</td>
                    <td>${item.lname}</td>
                    <td>${item.phone}</td>
                    <td>${item.email}</td>`;
                    table.append(row);
                });
            }
        })
    }
    $.ajax({
        url: "count.php",
        success: data => {
            limit = Number(data);
            changepage(0);
        }
    })
}