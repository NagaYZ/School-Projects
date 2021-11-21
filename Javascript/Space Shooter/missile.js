"use strict";
let duree_vie=0;
let bullet_speed=3;

function draw_missile() {	
	var canvas = document.getElementById('game_area').getContext('2d');
	world["MISSILE"].draw(canvas);	

}
function direction_missile(){
	var missile = world["MISSILE"];	
	
	missile.y-=bullet_speed;
	bullet_speed=bullet_speed*99/100; // garde 99% de sa vitesse a chaque tour.
	duree_vie+=3;
}


function tirer(){	
	var player = world["PLAYER"];
	world["MISSILE"] = new Missile(player.x+20, player.y-20);	
	var missile = world["MISSILE"];	
	missile.toucher="pas touché";
	
	var loop = setInterval(gameLoop_missile, 500/60);

	function gameLoop_missile() {					 
		missile.display="lancé"; //missile lancé
		draw_missile();
		direction_missile();		

		if((duree_vie>=300) || (missile.toucher =="touché")){	//missile disparait si il a touché un vaisseau ou s'il a parcourut la moitie du canvas.
			duree_vie=0;	
			bullet_speed=3;						
			missile.display="ready"; //pret a tirer un aure missile
			missile.x=this.x+20; // réinitialise sa position pour qu'il n'y est pas de "reste" invisible du missile. 
			missile.y=this.y-20;
			clearInterval(loop);
		}			
	}
}

