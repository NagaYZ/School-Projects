"use strict";
function onclick(){
	let accueil = world["Accueil"];
	
	if (accueil.display === "play"){
		jouer();
		accueil.display="playing";
	}
	
}
window.addEventListener("click", onclick); //si on clique le jeu se lance.

window.onload=function () {
	world["Accueil"] = new Accueil(175, 150);			
	let accueil = world["Accueil"];
	accueil.display = "play";
	window.setInterval(gameLoop_accueil, 1000/60);
}
function draw_accueil(){
	var canvas = document.getElementById("game_area").getContext("2d");	
	let accueil = world["Accueil"];
	if (accueil.display === "play"){	world["Accueil"].draw(canvas);}
}

function gameLoop_accueil(){
	draw_accueil();
	
}



class Accueil{
	constructor(x,y){
		this.x=x;
		this.y=y;		
		this.img = new Image();
		this.img.src = "play.png";
	}
	draw(canvas) {
		canvas.drawImage(this.img, this.x, this.y, 300, 300);
	}
}