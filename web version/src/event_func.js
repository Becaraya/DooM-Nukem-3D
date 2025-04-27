// Fonction pour gérer l'action de la touche "Z" (accroupissement)
function zFunc(al, isKeyDown) {
	if (isKeyDown) {
	  al.play.size = PLAYER_CROUCH;
	  al.play.eyez -= PLAYER_SIZE - PLAYER_CROUCH;
	  al.play.power_mult = 0.3;
	} else {
	  al.play.size = PLAYER_SIZE;
	  al.play.eyez += PLAYER_SIZE - PLAYER_CROUCH;
	  al.play.power_mult = 1;
	}
  }
  
  // Fonction pour gérer les touches relâchées
  function keyUpFunc(al, key) {
	switch (key) {
	  case "w": al.k.w = 0; break;
	  case "a": al.k.a = 0; break;
	  case "s": al.k.s = 0; break;
	  case "d": al.k.d = 0; break;
	  case "t": al.k.t = 0; break;
	  case "m": al.k.m = 0; break;
	  case "f": al.play.fly = 0; break;
	  case "[": al.k.lbrack = 0; break;
	  case "]": al.k.rbrack = 0; break;
	  case "ArrowLeft": al.k.left = 0; break;
	  case "ArrowRight": al.k.righ = 0; break;
	  case "Shift": al.play.power = PLAYER_AERO_POWER; break;
	  case "ArrowUp": al.k.up = 0; break;
	  case "ArrowDown": al.k.down = 0; break;
	  case " ": al.k.space = 0; break;
	}
  }
  
  // Fonction pour gérer les touches appuyées
  function keyDownFunc(al, key) {
	switch (key) {
	  case "Escape": prepareExit(al); break;
	  case "F1": al.status = (al.status === GAME) ? PAUSE : GAME; break;
	  case "w": al.k.w = 1; break;
	  case "a": al.k.a = 1; break;
	  case "s": al.k.s = 1; break;
	  case "d": al.k.d = 1; break;
	  case "t": al.k.t = 1; break;
	  case "m": al.k.m = 1; break;
	  case "f": al.play.fly = 1; break;
	  case "[": al.k.lbrack = 1; break;
	  case "]": al.k.rbrack = 1; break;
	  case "ArrowLeft": al.k.left = 1; break;
	  case "ArrowRight": al.k.righ = 1; break;
	  case "ArrowUp": al.k.up = 1; break;
	  case "ArrowDown": al.k.down = 1; break;
	  case "Shift": al.play.power = PLAYER_ANA_POWER; break;
	  case " ": al.k.space = 1; break;
	  case "-": al.fov *= 1.1; break;
	  case "+": al.fov /= 1.1; break;
	}
  }
  
  // Fonction principale pour gérer les événements clavier
  function keyFunc(al, event) {
	const key = event.key;
  
	if (key === "z") {
	  zFunc(al, event.type === "keydown");
	}
  
	if (event.type === "keydown") {
	  keyDownFunc(al, key);
	} else if (event.type === "keyup") {
	  keyUpFunc(al, key);
	}
  }