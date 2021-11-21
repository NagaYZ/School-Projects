"use strict";

var world = {};
var keys=[];
const vitesse=3;

window.addEventListener("keydown", function (e) {keys[e.keyCode] = true;}); //quand on appuie sur une touche.
window.addEventListener("keyup", function (e) {	 keys[e.keyCode] = false;});//quand on relache sur une touche.

function jouer() {
	world["PLAYER"] = new Player(275, 550);	
	world["ALIEN1"]= new Alien(0,60);
	world["ALIEN2"]= new Alien(0,125);
	world["ALIEN3"]= new Alien(0,190);
	world["ALIEN4"]= new Alien(0,255);
	world["ALIEN5"]= new Alien(560,60);
	world["ALIEN6"]= new Alien(560,125);
	world["ALIEN7"]= new Alien(560,190);
	world["ALIEN8"]= new Alien(560,255);
	var player = world["PLAYER"];
	world["MISSILE"] = new Missile(player.x, player.y);	
	var missile = world["MISSILE"];
	missile.display='ready';
	for (var i=1;i<9;i++){world["ALIEN"+i+""].display="alive";} //tous les aliens sont "en vie".(voir mort.js)
	window.setInterval(gameLoop, 500/60);
}

	
function gameLoop() {
	draw();
	mort_alien();
	mort_vaisseau();
	deplacement_vaisseau();
	spawn_alien();	
	victoire();
}

function draw() {
	var canvas = document.getElementById('game_area').getContext('2d');
	var context = document.getElementById('game_area');
	canvas.clearRect(0,0,context.height,context.width);
	world["PLAYER"].draw(canvas);	
}

function deplacement_vaisseau(){	
	var player = world["PLAYER"];
	var missile = world["MISSILE"];

	    if (keys[38] && player.y >=10) { //haut	    	
	    	player.y -= vitesse;
	    }
	    else if (keys[40] && player.y <=530) { //bas	    	
	        player.y += vitesse;
	    }
	    else if (keys[37] && player.x >=15) { //gauche	    	
	      	player.x -=	vitesse;
	    }	   
	    else if (keys[39] && player.x <= 535) { // droite	    	
	    	player.x += vitesse;
	    }
	    else if (keys[32]) { //BARRE ESPACE	    	
	    	if( missile.display=='ready'){//si pas d'autre missile lancé en cours de deplacement.(1 missile a la fois)	    		
				tirer();//missile.js
			}      	
	    }
	}

class Player{
	constructor(x,y){
		this.x=x;
		this.y=y;
		this.img = new Image();
		this.img.src = 'spaceshooter/PNG/playerShip3_red.png';
	}
	draw(canvas) {
		canvas.drawImage(this.img, this.x, this.y, 50, 50);
	}
}

class Missile{
	constructor(x,y){
		this.x=x;
		this.y=y;		
		this.img = new Image();
		this.img.src = 'spaceshooter/PNG/Lasers/laserRed01.png';
	}
	draw(canvas) {
		canvas.drawImage(this.img, this.x, this.y, 10, 40);
	}
}

class Alien{
	constructor(x,y){
		this.x=x;
		this.y=y;		
		this.img = new Image();
		this.img.src = 'spaceshooter/PNG/Enemies/enemyGreen1.png';
	}
	draw(canvas) {
		canvas.drawImage(this.img, this.x, this.y, 40, 40);
	}
}
