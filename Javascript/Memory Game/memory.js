function MemoryGame(images, blank) {
	this.lego = images.slice();	
	this.dos = blank.slice();  
}

function comparer(array2,id){
	tab.push(array2);
	flip.unshift(id);
	
	if (tab.length == 2 ) {		
		if (tab[0] == tab[1] && flip[0]!= flip[1] ) {			
			complet.push(1);					
		}

		else if (tab[0] != tab[1] ||	flip[0]== flip[1] ){
			//delai
			setTimeout(function() {
				document.getElementById("num"+flip[0]+"").src="http://monge.univ-mlv.fr/ens/Licence/L1/2018-2019/progweb/src/td08/blank.png";
				document.getElementById("num"+flip[1]+"").src="http://monge.univ-mlv.fr/ens/Licence/L1/2018-2019/progweb/src/td08/blank.png";
				
			}, 500);	
		}	
		tab=[];
	}	
	
	if (complet.length=== 8){//partie fini
		setTimeout(function() {
				alert("Gagné");
				location.reload();
			}, 300);	
		
		flip=[];
		complet=[];
	}
}

function siclick(pos_carte,pos_div){

	var carte= pos_carte+1;
	document.getElementById("num"+pos_div+"").src="http://monge.univ-mlv.fr/ens/Licence/L1/2018-2019/progweb/src/td08/lego"+carte+".png";
	comparer(carte,pos_div);
}

MemoryGame.prototype.build = function build(div) {
	var pos = shuffleCards(this.lego.length);
	
	for (i in [...Array(this.lego.length*2)]){		
		var lien_dos = this.dos;			
		div.innerHTML +="<div><a onClick=siclick("+pos[i]+","+i+");><img id=num"+i+" src=http://monge.univ-mlv.fr/ens/Licence/L1/2018-2019/progweb/src/td08/"+ lien_dos + "></a></div>";
	}
}

function shuffleCards(length) {
	var cards = [];
	var liste=['0','1','2','3','4','5','6','7','0','1','2','3','4','5','6','7'];
	for(var i = 0; i < length; i++) {
		var random1 = Math.floor(liste.length*Math.random()); 
		cards.push(liste[random1]);
		liste.splice(random1,1);

		var random2 = Math.floor(liste.length*Math.random());
		cards.push(liste[random2]);		
		liste.splice(random2,1);
	}
	return cards;
}

