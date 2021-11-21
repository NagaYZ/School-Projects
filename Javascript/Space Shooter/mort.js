"use strict";

function mort_alien(){	//mort d'alien par missile.

	var missile = world["MISSILE"];	
	var alien1 = world["ALIEN1"];
	var alien2 = world["ALIEN2"];
	var alien3 = world["ALIEN3"];
	var alien4 = world["ALIEN4"];
	var alien5 = world["ALIEN5"];
	var alien6 = world["ALIEN6"];
	var alien7 = world["ALIEN7"];
	var alien8 = world["ALIEN8"];
	

	if (missile.display == "lancé"){ //si il ya un missile de lancé.

		if (((missile.y<=alien8.y+15) &&(missile.y>=alien8.y-15)) &&(missile.x<=alien8.x+15)&&(missile.x>=alien8.x-15)){
			alien8.display='dead';	
			missile.toucher="touché";
		}
		if (((missile.y<=alien7.y+15) &&(missile.y>=alien7.y-15)) &&(missile.x<=alien7.x+15)&&(missile.x>=alien7.x-15)){
			alien7.display='dead';	
			missile.toucher="touché";	
		}
		if (((missile.y<=alien6.y+15) &&(missile.y>=alien6.y-15)) &&(missile.x<=alien6.x+15)&&(missile.x>=alien6.x-15)){
			alien6.display='dead';
			missile.toucher="touché";		
		}
		if (((missile.y<=alien5.y+15) &&(missile.y>=alien5.y-15)) &&(missile.x<=alien5.x+15)&&(missile.x>=alien5.x-15)){
			alien5.display='dead';		
			missile.toucher="touché";
		}
		if (((missile.y<=alien4.y+15) &&(missile.y>=alien4.y-15)) &&(missile.x<=alien4.x+15)&&(missile.x>=alien4.x-15)){
			alien4.display='dead';
			missile.toucher="touché";		
		}
		if (((missile.y<=alien3.y+15) &&(missile.y>=alien3.y-15)) &&(missile.x<=alien3.x+15)&&(missile.x>=alien3.x-15)){
			alien3.display='dead';	
			missile.toucher="touché";	
		}
		if (((missile.y<=alien2.y+15) &&(missile.y>=alien2.y-15)) &&(missile.x<=alien2.x+15)&&(missile.x>=alien2.x-15)){
			alien2.display='dead';	
			missile.toucher="touché";	
		}
		if (((missile.y<=alien1.y+15) &&(missile.y>=alien1.y-15)) &&(missile.x<=alien1.x+15)&&(missile.x>=alien1.x-15)){
			alien1.display='dead';	
			missile.toucher="touché";	
		}
	}
}

function mort_vaisseau(){// mort du vaisseau par colision avec missile ou alien.

	var player = world["PLAYER"];
	var missile = world["MISSILE"];	
	var alien1 = world["ALIEN1"];
	var alien2 = world["ALIEN2"];
	var alien3 = world["ALIEN3"];
	var alien4 = world["ALIEN4"];
	var alien5 = world["ALIEN5"];
	var alien6 = world["ALIEN6"];
	var alien7 = world["ALIEN7"];
	var alien8 = world["ALIEN8"];

	if (missile.display == 'lancé'){ // colision avec missile
		if ((((missile.x-25<=player.x)&&(player.x<= missile.x+25)) && ((missile.y-15<=player.y)&&( player.y<= missile.y +15))) && missile.display != 'none')  {
			missile.toucher="touché";
			game_over();
		}
	}

	//si alien en vie + colision.

	if(alien8.display =="alive"){ 
		if (((alien8.x-20<=player.x)&&(player.x<= alien8.x+20)) && ((alien8.y-20<=player.y)&&( player.y<= alien8.y +20)))  {
			game_over();
		}
	}
	if(alien7.display =="alive"){
		if (((alien7.x-20<=player.x)&&(player.x<= alien7.x+20)) && ((alien7.y-20<=player.y)&&( player.y<= alien7.y +20)))  {
			game_over();
		}
	}

	if(alien6.display =="alive"){
		if (((alien6.x-20<=player.x)&&(player.x<= alien6.x+20)) && ((alien6.y-20<=player.y)&&( player.y<= alien6.y +20)))  {
			game_over();
		}
	}
	if(alien5.display =="alive"){
		if (((alien5.x-20<=player.x)&&(player.x<= alien5.x+20)) && ((alien5.y-20<=player.y)&&( player.y<= alien5.y +20)))  {
			game_over();
		}
	}
	if(alien4.display =="alive"){
		if (((alien4.x-20<=player.x)&&(player.x<= alien4.x+20)) && ((alien4.y-20<=player.y)&&( player.y<= alien4.y +20)))  {
			game_over();
		}
	}
	if(alien3.display =="alive"){
		if (((alien3.x-20<=player.x)&&(player.x<= alien3.x+20)) && ((alien3.y-20<=player.y)&&( player.y<= alien3.y +20)))  {
			game_over();
		}
	}
	if(alien2.display =="alive"){
		if (((alien2.x-20<=player.x)&&(player.x<= alien2.x+20)) && ((alien2.y-20<=player.y)&&( player.y<= alien2.y +20)))  {
			game_over();
		}
	}
	if(alien1.display =="alive"){
		if (((alien1.x-20<=player.x)&&(player.x<= alien1.x+20)) && ((alien1.y-20<=player.y)&&( player.y<= alien1.y +20)))  {
			game_over();
		}
	}	

}

function game_over(){
	location.reload(); // on actualise la page.
}
