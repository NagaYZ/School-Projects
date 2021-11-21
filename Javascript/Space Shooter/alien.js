"use strict";

/* PARTIE COMPLIQUER:

-first_descente: correspond à la descente des aliens au début du jeu.
-autre_descente: correspond à la descente des aliens lorsque d'autre rebondisse en bas du canvas(ex: lorsque alien4 et alien8 vont rebondir sur le bas du canvas les autres aliens doivent continuer à descendre normalement sans changer leur vitesse).
- monte_X_Z: correspond au moment de rebond de deux aliens X et Z sur le BAS du canvas. 
- redescente_X_Z: correspond au moment de rebond de deux aliens X et Z sur le HAUT du canvas.
-rebondX: correspond à l'augmentation de la vitesse pour chaque paire d'alien (ex: rebond1 pour alien4 et alien8 qui sont les premiers à rebondir.)
- cran: correspond à la valeur des aliens qui descende vers le bas.

Fonction:( tout en bas de la page )
right_side() : rebond sur le cote droit donc diminution des abscisses
left_side() : rebond sur le cote gauche donc augmentation des abscisses.
up() : ....
down() : .... 

left_side_rebond_X_X (): pareil que left_side mais pour une paire d'alien spécifique (utilisé pour les rebonds).
right_side_rebond_X_X (): ...

*/
var rebond={"rebond1":0,"rebond2":0,"rebond3":0,"rebond4":0};
let first_descente =0;
let autre_descente=0;
let monte_8_4=0;
let monte_7_3=0;
let monte_6_2=0;
let monte_5_1=0;
let redescente_8_4=0;
let redescente_7_3=0;
let redescente_6_2=0;
let redescente_5_1=0;
const cran=20;


function spawn_alien(){
	draw_alien();
	direction_alien();
}

function draw_alien() {	
	var canvas = document.getElementById('game_area').getContext('2d');
	for (var i=1;i<9;i++){
		if (world["ALIEN"+i+""].display != 'dead'){// on dessine un alien qui si il est "en vie".
			world["ALIEN"+i+""].draw(canvas);
		}
	}		
}

function direction_alien(){
	var alien1 = world["ALIEN1"];
	var alien2 = world["ALIEN2"];
	var alien3 = world["ALIEN3"];
	var alien4 = world["ALIEN4"];
	var alien5 = world["ALIEN5"];
	var alien6 = world["ALIEN6"];
	var alien7 = world["ALIEN7"];
	var alien8 = world["ALIEN8"];
	
	//premiere descente
	if (first_descente===0){
		right_side(alien1);
		right_side(alien2);
		right_side(alien3);
		right_side(alien4);
		
		left_side(alien5);
		left_side(alien6);
		left_side(alien7);
		left_side(alien8);	
	}
	
	if ((alien1.x>=561)&& first_descente===0){
		down(alien1);
		down(alien2);
		down(alien3);
		down(alien4);
		down(alien5);
		down(alien6);
		down(alien7);
		down(alien8);	
		first_descente=1;
	}
	if (first_descente ===1){
		left_side(alien1);
		left_side(alien2);
		left_side(alien3);
		left_side(alien4);

		right_side(alien5);
		right_side(alien6);
		right_side(alien7);
		right_side(alien8);

	}
	
	if ((alien1.x<=0)&& first_descente===1 ){
		down(alien1);
		down(alien2);
		down(alien3);
		down(alien4);
		down(alien5);
		down(alien6);
		down(alien7);
		down(alien8);			
		first_descente=0;
	}
	

	////////////////////////////////////////// alien 8 et 4 rebondisse et  monte
	if (((alien8.y >= 560) && autre_descente !=undefined)&&alien8.x>=555){	
		
		rebond["rebond1"]+=10/100; //ajout de 10% de vitesse
		first_descente=undefined;
		monte_8_4=1;			
	}

	if (((alien8.y >= 560) && autre_descente !=undefined)&&alien8.x<=0){

		rebond["rebond1"]+=10/100; //ajout de 10% de vitesse
		first_descente=undefined;		
		monte_8_4=2;		
	}
	
	if (monte_8_4===1){
		
		left_side_rebond_8_4(alien4);
		right_side_rebond_8_4(alien8);					
	}
	
	if ((alien8.x >=560) && monte_8_4===1){	
		up(alien4);
		up(alien8);
		monte_8_4=2;	
	}

	if (monte_8_4===2){		

		right_side_rebond_8_4(alien4);
		left_side_rebond_8_4(alien8);
	}

	if ((alien8.x <=0) && monte_8_4===2){
		up(alien4);
		up(alien8);
		monte_8_4=1;
	}

	if (autre_descente===0 && monte_8_4>=1){	
		left_side(alien1);
		left_side(alien2);
		left_side(alien3);
		
		right_side(alien5);	
		right_side(alien6);
		right_side(alien7);
	}

	if (((alien1.x<=0 ) && autre_descente===0 )&& monte_8_4 >=1){
		down(alien1);
		down(alien2);
		down(alien3);		
		down(alien5);
		down(alien6);
		down(alien7);
		autre_descente=1;		
	}

	if (autre_descente===1){
		right_side(alien1);
		right_side(alien2);
		right_side(alien3);

		left_side(alien5);
		left_side(alien6);
		left_side(alien7);			
	}
	if ((alien1.x>=561) && autre_descente===1){
		down(alien1);
		down(alien2);
		down(alien3);		
		down(alien5);
		down(alien6);
		down(alien7);
		autre_descente=0;		
	}
	/////////////////////////////////// alien 7 et 3 rebondisse et  monte
	if (((alien7.y >= 560) && autre_descente !=undefined)&&alien7.x>=555){					
		monte_7_3=2;	
		rebond["rebond2"]+=10/100; //ajout de 10% de vitesse
		if (autre_descente != 'none'){
			autre_descente=2;
		}

	}
	if(((alien7.y >= 560) && autre_descente !=undefined)&&alien7.x<=0){				
		monte_7_3=1;	
		rebond["rebond2"]+=10/100; //ajout de 10% de vitesse
		if (autre_descente != 'none'){
			autre_descente=2;
		}
		
	}
	if (monte_7_3===1){				
		right_side_rebond_7_3(alien3);
		left_side_rebond_7_3(alien7);						
	}
	
	
	if ((alien3.x >=560 ) && monte_7_3===1){
		up(alien3);
		up(alien7);	
		monte_7_3=2;
		
	}
	if (monte_7_3===2){		
		left_side_rebond_7_3(alien3);	
		right_side_rebond_7_3(alien7);
	}
	if ((alien7.x >=560 ) && monte_7_3===2){
		up(alien3);
		up(alien7);
		monte_7_3=1;
	}

	if (autre_descente===2){	
		right_side(alien1);
		right_side(alien2);

		left_side(alien5);
		left_side(alien6);
	}

	if ((alien1.x>=561 ) && autre_descente===2 ){
		down(alien1);
		down(alien2);		
		down(alien5);
		down(alien6);		
		autre_descente=3;		
	}

	if (autre_descente===3){		
		left_side(alien1);
		left_side(alien2);

		right_side(alien5);
		right_side(alien6);

	}

	if ((alien1.x<=0) && autre_descente===3){
		down(alien1);
		down(alien2);		
		down(alien5);
		down(alien6);		
		autre_descente=2;		
	}

	//////////////////////////////////////////alien	6 et 2 rebondisse et monte
	if (((alien6.y >= 560) && autre_descente !=undefined)&&alien6.x <=0){
		monte_6_2=1;	
		rebond["rebond3"]+=10/100; //ajout de 10% de vitesse
		if (autre_descente != 'none'){
			autre_descente=4;
		}
				
	}
	if (((alien6.y >= 560) && autre_descente !=undefined)&&alien6.x >=555){		
		monte_6_2=2;	
		rebond["rebond3"]+=10/100; //ajout de 10% de vitesse
		if (autre_descente != 'none'){
			autre_descente=4;
		}		
	}	
	
	if  (monte_6_2===1){			
		right_side_rebond_6_2(alien2);
		left_side_rebond_6_2(alien6);			
	}
		
	if ((alien6.x <=0)&& monte_6_2===1){
		up(alien2);
		up(alien6);	
		monte_6_2=2;
		
	}
	if  (monte_6_2===2){		
		left_side_rebond_6_2(alien2);
		right_side_rebond_6_2(alien6);
	}
	if ( (alien6.x >=560)&& monte_6_2===2){		
		up(alien2);
		up(alien6);	
	 	monte_6_2=1;
	}

	if (autre_descente===4){		
		left_side(alien1);
		right_side(alien5);			
	}

	if ((alien1.x<=0 ) && autre_descente===4 ){		
		down(alien1);
		down(alien5);		
		autre_descente=5;		
	}

	if (autre_descente===5){	
		right_side(alien1);	
		left_side(alien5);			
	}
	if ((alien1.x>=560) && autre_descente===5){
		down(alien1);
		down(alien5);	
		autre_descente=4;		
	}
	////////////////////////////////////// alien 5 et 1 rebondisse et monte
	if (((alien5.y >= 560) && autre_descente!=undefined)&&alien5.x <=0){
		monte_5_1=2;	
		rebond["rebond4"]+=10/100;	 //ajout de 10% de vitesse
		autre_descente='none';	
	}	
	if (((alien5.y >= 560) && autre_descente!=undefined)&&alien5.x>=555){
		monte_5_1=1;		
		rebond["rebond4"]+=10/100; //ajout de 10% de vitesse
		autre_descente='none';	
	}	

	if  (monte_5_1===1){
		left_side_rebond_5_1(alien1);	
		right_side_rebond_5_1(alien5);	
	}
		
	if ((alien5.x >=555 ) && monte_5_1===1){
		up(alien1);
		up(alien5);	
		monte_5_1=2;
		
	}
	if  (monte_5_1===2){
		right_side_rebond_5_1(alien1);	
		left_side_rebond_5_1(alien5);
	}
	if ((alien5.x <=0) && monte_5_1===2){
		up(alien1);
		up(alien5);
	 	monte_5_1=1;
	}

	////////////////////////////////// alien 8 et 4 rebondisse et descende
	if(alien4.y <=0){			
		rebond["rebond1"]+=10/100; //ajout de 10% de vitesse
		monte_8_4=undefined;	
	}  	

	if ((redescente_8_4===0)&& monte_8_4===undefined){
		left_side_rebond_8_4(alien4);		
		right_side_rebond_8_4(alien8);						
	}

	if (((alien8.x >=560) && monte_8_4===undefined)&& redescente_8_4===0){
		down(alien4);
		down(alien8);		
		redescente_8_4=1;		
	}

	if (redescente_8_4===1){		
		
		right_side_rebond_8_4(alien4);		
		left_side_rebond_8_4(alien8);			
	}

	if (((alien8.x <=0 )&& monte_8_4===undefined)&& redescente_8_4===1){		
		down(alien4);
		down(alien8);
		redescente_8_4=0;		
	}
	if ((alien8.y >=561)&& monte_8_4 ===undefined){
		
		redescente_8_4=0;		
		autre_descente='none';	
	}
		
	///////////////////////////// alien 7 et 3 rebondisse et descende
	if(alien3.y <=0){		
		rebond["rebond2"]+=10/100; //ajout de 10% de vitesse
		monte_7_3=undefined;	
	}  	
	if ((redescente_7_3===0)&& monte_7_3===undefined){	
		left_side_rebond_7_3(alien3);		
		right_side_rebond_7_3(alien7);						
	}

	if (((alien7.x >=560) && monte_7_3===undefined)&& redescente_7_3===0){
		down(alien3);
		down(alien7);
		redescente_7_3=1;		
	}

	if (redescente_7_3===1){			
		right_side_rebond_7_3(alien3);		
		left_side_rebond_7_3(alien7);			
	}

	if (((alien7.x <=0 )&& monte_7_3===undefined)&& redescente_7_3===1){		
		down(alien3);
		down(alien7);	
		redescente_7_3=0;		
	}
	if ((alien7.y >=561)&& monte_7_3 === undefined){
		redescente_7_3=0;
	}

	///////////////////////////////// alien 6 et 2 rebondisse et descende
	if(alien2.y <0){	
		rebond["rebond3"]+=10/100;	 //ajout de 10% de vitesse
		monte_6_2=undefined;	
	}  	
	if ((redescente_6_2===0)&& monte_6_2===undefined){					
		left_side_rebond_6_2(alien2);		
		right_side_rebond_6_2(alien6);				
	}
	
	if (((alien6.x >=560) && monte_6_2===undefined)&& redescente_6_2===0){
		down(alien2);
		down(alien6);	
		redescente_6_2=1;		
	}

	if (redescente_6_2===1){	
		right_side_rebond_6_2(alien2);		
		left_side_rebond_6_2(alien6);			
	}

	if (((alien6.x <=0 )&& monte_6_2===undefined)&& redescente_6_2===1){		
		down(alien2);
		down(alien6);	
		redescente_6_2=0;		
	}
	if ((alien6.y >=561)&& monte_6_2===undefined){
		redescente_6_2=0;
	}
	
	/////////////////////////////////// alien 5 et 1 rebondisse et descende
	if(alien1.y <=0){	
		rebond["rebond4"]+=10/100; //ajout de 10% de vitesse
		monte_5_1=undefined;
	}  	
	if ((redescente_5_1===0)&& monte_5_1===undefined){	
		right_side_rebond_5_1(alien1);		
		left_side_rebond_5_1(alien5);		
							
	}

	if (((alien5.x <=0 ) && monte_5_1===undefined)&& redescente_5_1===0){

		down(alien1);
		down(alien5);	
		redescente_5_1=1;		
	}

	if (redescente_5_1===1){			
		left_side_rebond_5_1(alien1);		
		right_side_rebond_5_1(alien5);		
	}

	if (((alien5.x >=560)&& monte_5_1===undefined)&& redescente_5_1===1){		
		down(alien1);
		down(alien5);		
		redescente_5_1=0;		
	}
	if ((alien5.y >=561)&& monte_5_1===undefined){
		redescente_5_1=0;
	}

	function left_side(alien){alien.x -= vitesse;}

	function right_side(alien){alien.x += vitesse;}

	function up(alien){alien.y -= cran;}

	function down(alien){alien.y += cran;}

	function left_side_rebond_8_4(alien){
		alien.x -= vitesse * rebond["rebond1"] + vitesse;		
	}

	function right_side_rebond_8_4(alien){
		alien.x += vitesse * rebond["rebond1"] + vitesse;
	}

	function left_side_rebond_7_3(alien){
		alien.x -= vitesse * rebond["rebond2"] + vitesse;		
	}

	function right_side_rebond_7_3(alien){
		alien.x += vitesse * rebond["rebond2"] + vitesse;
	}

	function left_side_rebond_6_2(alien){
		alien.x -= vitesse * rebond["rebond3"] + vitesse;		
	}

	function right_side_rebond_6_2(alien){
		alien.x += vitesse * rebond["rebond3"] + vitesse;
	}

	function left_side_rebond_5_1(alien){
		alien.x -= vitesse * rebond["rebond4"] + vitesse;		
	}

	function right_side_rebond_5_1(alien){
		alien.x += vitesse * rebond["rebond4"] + vitesse;
	}
}