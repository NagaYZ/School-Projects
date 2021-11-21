"use strict";
function message_victoire(){	
	location.reload();
}

function victoire(){
	let compteur =0;
	for (var i=1;i<9;i++){
		if (world["ALIEN"+i+""].display === "dead"){// on verifie l"etat de chaque alien.			
			compteur +=1;
		}	
	}

	if (compteur===8){// si tous les aliens sont morts.
		message_victoire();
	}
}

