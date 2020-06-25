function createBlock(n){
    for (let i = 1; i < n; i++){
        document.write("<div class='blocks'><p>Block x</p></div>".replace("x",i));
    }
    
}
function changeDirection(ind){
    let myId = document.getElementById("direction");
    switch(ind){
        case 0:
            myId.style.flexDirection = "row";
            break;
        case 1:
            myId.style.flexDirection = "row-reverse";
            break;
        case 2:
            myId.style.flexDirection = "column";
            break;
        case 3:
            myId.style.flexDirection = "column-reverse";
            break;
    }
}

function changeJustify(str){
    let myId = document.getElementById("justify");
    myId.style.justifyContent = str;
}

function changeWrap(str){
    let myId = document.getElementById("wrap");
    myId.style.flexWrap = str;
}