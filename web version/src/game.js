// Fonction pour gérer le vol
function flyyyy(al) {
	al.play.velz -= al.g * al.dtime / 1000000;
	if (al.play.fly) {
	  al.play.velz += (1000 / al.play.mass) * al.dtime / 1000000;
	}
  }
  
  // Fonction pour gérer les touches spéciales
  function spKey(al) {
	if (al.door !== 0) {
	  const tmp = 0.000001 * al.dtime;
	  if (al.k.lbrack) {
		if (al.sec[al.door].fl_hei + tmp < al.sec[al.door].ce_hei) {
		  al.sec[al.door].fl_hei += tmp;
		}
	  } else if (al.k.rbrack) {
		al.sec[al.door].fl_hei -= tmp;
	  }
	}
  }
  
  // Fonction principale du jeu
  function game(al) {
	rotate(al);
	spKey(al);
	if (al.k.space) {
	  jump(al);
	}
	if (al.play.on_ground) {
	  acceleration(al);
	} else {
	  flyyyy(al);
	}
	displacement(al);
	render(al);
  
	if (al.play.won) {
	  al.status = "WON";
	  pixToPix(al.pix, al.pix_dead, 1);
	  document.body.style.cursor = "default"; // Simule SDL_ShowCursor(SDL_ENABLE)
	} else if (al.play.alive) {
	  // Simule SDL_WarpMouseInWindow et SDL_ShowCursor(SDL_DISABLE)
	  document.body.style.cursor = "none";
	} else {
	  al.status = "DEAD";
	  pixToPix(al.pix, al.pix_dead, 1);
	  document.body.style.cursor = "default"; // Simule SDL_ShowCursor(SDL_ENABLE)
	}
  }