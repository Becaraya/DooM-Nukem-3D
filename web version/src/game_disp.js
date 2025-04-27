// Fonction pour calculer l'angle en fonction des touches pressées
function calculateAngle(al) {
	const dir = al.play.dir;
  
	if (al.k.w && !al.k.a && !al.k.s && !al.k.d) return dir & D_2PIM;
	if (!al.k.w && al.k.a && !al.k.s && !al.k.d) return subAngle(dir, D_PI_2);
	if (!al.k.w && !al.k.a && al.k.s && !al.k.d) return addAngle(dir, D_PI);
	if (!al.k.w && !al.k.a && !al.k.s && al.k.d) return addAngle(dir, D_PI_2);
	if (al.k.w && al.k.a && !al.k.s && !al.k.d) return subAngle(dir, D_PI_4);
	if (!al.k.w && al.k.a && al.k.s && !al.k.d) return subAngle(dir, D_PI - D_PI_4);
	if (!al.k.w && !al.k.a && al.k.s && al.k.d) return addAngle(dir, D_PI - D_PI_4);
	if (al.k.w && !al.k.a && !al.k.s && al.k.d) return addAngle(dir, D_PI_4);
  
	return 69420; // Cas d'erreur
  }
  
  // Fonction pour gérer la décélération
  function deceleration(al) {
	let wack = 4.0 * al.dtime / 1000000.0;
	wack = wack > 0.9 ? 0.9 : wack;
  
	if (al.play.gd_vel < 1) wack = 0.25;
	if (al.play.gd_vel < 0.1) {
	  al.play.gd_vel = 0;
	  al.play.velx = 0;
	  al.play.vely = 0;
	}
  
	al.play.velx *= 1 - wack;
	al.play.vely *= 1 - wack;
	al.play.gd_vel = Math.sqrt(al.play.velx ** 2 + al.play.vely ** 2);
  }
  
  // Fonction pour gérer l'accélération
  function acceleration(al) {
	const netPower = al.play.power * (al.k.w ? 1 : 0.4) * al.play.power_mult - powerToRun(al);
	const dirForce = calculateAngle(al);
  
	if (dirForce === 69420 || netPower < 0) {
	  deceleration(al);
	  return;
	}
  
	const netForce = netPower / (al.play.gd_vel > 1 ? al.play.gd_vel : 1);
	const netAccel = netForce / (al.play.mass || 1);
  
	al.play.gd_vel += netAccel * al.dtime / 1000000;
	al.play.velx = al.sin[dirForce] * al.play.gd_vel;
	al.play.vely = al.cos[dirForce] * al.play.gd_vel;
  }
  
  // Fonction pour gérer les déplacements verticaux
  function verticalDisplacement(al) {
	if (al.play.posz < al.sec[al.play.csec].fl_hei) {
	  al.play.posz = al.sec[al.play.csec].fl_hei;
	  al.play.eyez = al.sec[al.play.csec].fl_hei + al.play.size - PLAYER_EYE_TOP;
	  al.play.velz = 0;
	  al.play.on_ground = 1;
	}
  
	if (al.play.posz + al.play.size > al.sec[al.play.csec].ce_hei) {
	  al.play.posz = al.sec[al.play.csec].ce_hei - al.play.size;
	  al.play.eyez = al.sec[al.play.csec].ce_hei - PLAYER_EYE_TOP;
	  al.play.velz = 0;
	}
  
	if (al.sec[al.play.csec].ce_hei - al.sec[al.play.csec].fl_hei < al.play.size) {
	  al.play.alive = 0;
	}
  }
  
  // Fonction pour gérer les déplacements globaux
  function displacement(al) {
	if (al.dtime > 1 && al.dtime < 1000000) {
	  ftNopPlayer(al, 0, al.play.velx * al.dtime / 1000000, al.play.vely * al.dtime / 1000000);
	}
  
	al.play.posz += al.play.velz * al.dtime / 1000000;
	al.play.eyez += al.play.velz * al.dtime / 1000000;
  
	for (let i = 0; i < al.nb_ent; i++) {
	  if (al.dtime > 1 && al.dtime < 1000000) {
		ftNop(al, al.ent[i], al.ent[i].velx * al.dtime / 1000000, al.ent[i].vely * al.dtime / 1000000);
	  }
	}
  
	verticalDisplacement(al);
  }