function getAge(dateString) {
    var today = new Date();
    var birthDate = new Date(dateString);
    var age = today.getFullYear() - birthDate.getFullYear();
    var m = today.getMonth() - birthDate.getMonth();
    if (m < 0 || (m === 0 && today.getDate() < birthDate.getDate())) {
        age--;
    }
    return age;
}

$("form").on("submit", (e) => handleform(e.target));

function handleform(form) {
    let ok = true;
    const redify = (form) => {
        form.css("border", "3px solid red");
        ok = false;
    };
    for (let o of form) o.style.border = "";
    if ($("#name").val().length < 3) redify($("#name"));
    if (!$("#date").val()) redify($("#date"));
    if (!$("#date").val() || $("#age").val() != getAge($("#date").val())) redify($("#age"));
    if ($("#email").val().length < 5) redify($("#email"));
    return ok;
}
