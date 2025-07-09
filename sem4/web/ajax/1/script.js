if (!JQUERY) {
    const fromBox = document.createElement("select");
    const toBox = document.createElement("select");
    document.body.append(fromBox);
    document.body.append(toBox);
    const request = new XMLHttpRequest();
    request.onreadystatechange = function () {
        if (request.readyState == 4) {
            if (request.status == 200) {
                data = request.responseText;
                const cities = JSON.parse(data);
                for (const city of cities) {
                    console.log(city);
                    const option = document.createElement("option");
                    option.innerText = city;
                    fromBox.append(option);

                }
                fromBox.selectedIndex = -1;
            }
            else console.log('Error: ' + request.status);
        }
    };
    request.open('GET', 'start.php', true);
    request.send();
    fromBox.onchange = e => {
        const request = new XMLHttpRequest();
        request.onreadystatechange = function () {
            if (request.readyState == 4) {
                if (request.status == 200) {
                    data = request.responseText;
                    const cities = JSON.parse(data);
                    toBox.replaceChildren();
                    for (const city of cities) {
                        console.log(city);
                        const option = document.createElement("option");
                        option.innerText = city;
                        toBox.append(option);

                    }
                }
                else console.log('Error: ' + request.status);
            }
        };
        request.open('GET', `destination.php?from=${e.target.value}`, true);
        request.send();
    }
}
else {
    const fromBox = $("<select></select>");
    const toBox = $("<select></select>");
    $("body").append(fromBox);
    $("body").append(toBox);
    $.ajax({
        url: "start.php",
        success: data => {
            $(JSON.parse(data)).each((_, city) =>
                $(fromBox).append(`<option>${city}</option>`));
            $(fromBox).val(-1);
        }
    })
    fromBox.on('change', e => {
        $.ajax({
            url: 'destination.php',
            data: `from=${e.target.value}`,
            success: data => {
                $(toBox).empty();
                $(JSON.parse(data)).each((_, city) =>
                    $(toBox).append(`<option>${city}</option>`))
            }
        })
    });
}