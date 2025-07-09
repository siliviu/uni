var saved = true;
var selected;
if (!JQUERY) {
    const select = document.getElementsByTagName("select")[0];
    const form = document.getElementsByTagName("form")[0];
    fetch("ids.php")
        .then(response => response.text())
        .then(data => {
            const ids = JSON.parse(data);
            for (const id of ids) {
                const option = document.createElement("option");
                option.innerText = id;
                select.append(option);
            }
            select.selectedIndex = -1;
        })

    select.onchange = e => {
        if (!saved) {
            alert("Unsaved changes!");
            return;
        }
        selected = e.target.value;
        fetch(`person.php?id=${selected}`)
            .then(response => response.text())
            .then(data => {
                const person = JSON.parse(data);
                form["name"].value = person.name;
                form["email"].value = person.email;
                form["phone"].value = person.phone;
            })
    }
    form["name"].onchange = form["email"].onchange = form["phone"].onchange = () => {
        saved = false
        document.getElementsByTagName("button")[0].disabled = false;
    }
    function update() {
        const person = {
            id: selected,
            name: form["name"].value,
            email: form["email"].value,
            phone: form["phone"].value
        };
        fetch("update.php", {
            method: 'PUT',
            body: JSON.stringify(person)
        })
            .then(response => response.text())
            .then(data => {
                console.log(data);
                saved = true;
                document.getElementsByTagName("button")[0].disabled = true;
            })
            .catch(error => {
                alert(error);
            });
    }
}
else {
    $.ajax({
        url: "ids.php",
        success: ids => {
            $(JSON.parse(ids)).each((_, id) =>
                $("select").append(`<option>${id}</option>`));
        }
    })
    $("select").on('change', e => {
        if (!saved) {
            alert("Unsaved changes!");
            return;
        }
        selected = e.target.value;
        $.ajax({
            url: 'person.php',
            data: `id=${e.target.value}`,
            success: data => {
                const person = JSON.parse(data);
                $("#name").val(person.name);
                $("#email").val(person.email);
                $("#phone").val(person.phone);
            }
        })
    });
    $("input").on('change', e => {
        saved = false;
        $("button")[0].disabled = false;
    })
    function update() {
        const person = {
            id: selected,
            name: $("#name").val(),
            email: $("#email").val(),
            phone: $("#phone").val()
        };
        $.ajax({
            url: 'update.php',
            type: 'PUT',
            data: JSON.stringify(person),
            success: data => {
                console.log(data);
                saved = true;
                document.getElementsByTagName("button")[0].disabled = true
            },
            fail: err => alert(err)
        })
    }
}