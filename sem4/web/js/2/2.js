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

function handleform(form) {
    let ok = true;
    const redify = (form) => {
        form.style.border = "3px solid red";
        ok = false;
    };
    for (let o of form) o.style.border = "";
    if (form["name"].value.length < 3) redify(form["name"]);
    if (!form["date"].value) redify(form["date"]);
    if (!form["age"].value || form["age"].value != getAge(form["date"].value)) redify(form["age"]);
    if (form["email"].value.length < 5) redify(form["email"]);
    return ok;
}
