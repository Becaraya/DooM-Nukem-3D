// Fonction pour afficher la position des "pigs" (mobs)
function pigPos(al) {
	let mob = al.ent;
  
	while (mob !== null) {
	  const pointA = {
		x: (mob.posx * 10) + (WIN_SIZEX / 2) + 2,
		y: -(mob.posy * 10) + (WIN_SIZEY / 2) + 2,
	  };
	  const pointB = {
		x: (mob.posx * 10) + (WIN_SIZEX / 2) - 2,
		y: -(mob.posy * 10) + (WIN_SIZEY / 2) - 2,
	  };
  
	  putRectangle(al.sdlsurf, pointA, pointB, RED); // Dessine un rectangle rouge
	  mob = mob.next;
	}
  }
  
  // Fonction pour initialiser les "pigs" (mobs)
  function initPig(al, mob, tmp, i) {
	while (tmp) {
	  mob[i] = {
		posx: tmp.posx,
		posy: tmp.posy,
		csec: isInSector(al, tmp.posx, tmp.posy),
		posz: al.sec[al.ent[0].csec].fl_hei,
		velx: 0,
		vely: 0,
		velz: 0,
		gd_vel: 0,
		on_ground: true,
		alive: 50,
		dir: 0,
		size: 2.5,
		width: 2.3,
		mass: 50,
		power: 200,
		hit: 1,
		index: i,
		fly: true,
	  };
	  tmp = tmp.next;
	  i++;
	}
	return mob;
  }
  
  // Fonction pour charger les "pigs" (mobs)
  function loadPig(al) {
	let tmp = al.ent;
	const mob = [];
  
	al.nb_ent = 0;
	if (al.ent === null) return;
  
	while (tmp) {
	  tmp = tmp.next;
	  al.nb_ent++;
	}
  
	tmp = al.ent;
	al.ent = initPig(al, mob, tmp, 0);
  }
  
  // Fonction pour créer un nouveau mob
  function newMob(al, bev, i) {
	return {
	  posx: (bev.x - WIN_SIZEX / 2) / 10,
	  posy: (bev.y - WIN_SIZEY / 2) / -10,
	  index: i,
	  next: null,
	};
  }
  
  // Fonction pour ajouter un "bad pig" (mob)
  function badPig(al, bev) {
	let cur = al.ent;
	let i = 0;
	let isNew = true;
  
	if (!al.ent) {
	  al.ent = newMob(al, bev, i);
	  return;
	}
  
	while (cur.next) {
	  if (
		cur.posx === (bev.x - WIN_SIZEX / 2) / 10 &&
		cur.posy === (bev.y - WIN_SIZEY / 2) / -10
	  ) {
		isNew = false;
	  }
	  cur = cur.next;
	  i++;
	}
  
	if (isNew && i < 21) {
	  cur.next = newMob(al, bev, i);
	}
  }