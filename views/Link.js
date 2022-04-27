var hiddenElement = document.getElementById("box");
var btn = document.getElementById('btn');

function handleButtonClick() {
   hiddenElement.scrollIntoView({block: "center", behavior: "smooth"});
}


console.log(btn)

btn.addEventListener('click', handleButtonClick);