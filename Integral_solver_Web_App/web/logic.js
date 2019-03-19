
function onMessage(jsonData) {
    var result = JSON.parse(jsonData);
    document.getElementById("solution").innerText = result.solution;
    document.getElementById("time").innerText = result.time;
}

function solve() {
    toggleProgress();
    var Http = new XMLHttpRequest();
    var url='http://localhost:8080/Integral_solver_Web_App_war_exploded/integral/solve';
    Http.open("POST", url, true);
    Http.setRequestHeader("Content-Type", "application/json");
    Http.onreadystatechange= function () {
        if (this.readyState===4 && this.status===200) {
            onMessage(Http.responseText);
        }
        toggleProgress();
    }
    var data = JSON.stringify({
        "function": document.getElementById("function").value,
        "args": [
            document.getElementById("x1").value,
            document.getElementById("x2").value,
            document.getElementById("y1").value,
            document.getElementById("y2").value,
            document.getElementById("z1").value,
            document.getElementById("z2").value
        ],
        "mpi": document.getElementById("mpi").value
    });
    Http.send(data);
}

function reset() {
    document.getElementById("function").value = "";

    document.getElementById("x1").value = "";
    document.getElementById("x2").value = "";
    document.getElementById("y1").value = "";
    document.getElementById("y2").value = "";
    document.getElementById("z1").value = "";
    document.getElementById("z2").value = "";

    document.getElementById("mpi").value = "";

    document.getElementById("solution").innerText = " ";
    document.getElementById("time").innerText = " ";
}

function toggleProgress() {
    var x = document.getElementById("progress");
    if (x.style.display === "none") {
        x.style.display = "block";
    } else {
        x.style.display = "none";
    }
}
