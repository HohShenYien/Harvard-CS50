function changeBox(){
    let box = document.querySelector("#box");
    box.style.height = document.getElementById("heightTxt").value;
    box.style.width = document.getElementById("widthTxt").value;
    box.style.margin = document.getElementById("marginTxt").value;
    box.style.padding = document.getElementById("paddingTxt").value;
    box.style.borderWidth = document.getElementById("borderTxt").value;
    box.innerHTML=document.getElementById("text").value;
    return false;
}