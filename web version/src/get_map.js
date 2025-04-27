// Fonction pour libérer les données des secteurs
function freeTab(al) {
	if (al.sec) {
	  for (let i = 1; i < al.nb_sec; i++) {
		al.sec[i].walls = null; // Simule un "free" en supprimant la référence
		al.rotsec[i].walls = null;
	  }
	  al.sec = null; // Supprime la référence au tableau des secteurs
	}
  }
  
  // Fonction pour créer un point
  function getPoint(x, y) {
	return { x: x, y: y, color: WHITE };
  }
  
  // Fonction pour créer un élément de mur
  function createWallsElem(al, nb_sec, nb_wal) {
	const wall = {
	  wall_tex: al.sec[nb_sec].walls[nb_wal].wall_tex,
	  top_tex: al.sec[nb_sec].walls[nb_wal].top_tex,
	  bot_tex: al.sec[nb_sec].walls[nb_wal].bot_tex,
	  sec_lnk: al.sec[nb_sec].walls[nb_wal].sec_lnk,
	  is_cross: al.sec[nb_sec].walls[nb_wal].is_cross,
	  next: null,
	};
  
	return wall;
  }
  
  // Fonction pour récupérer les murs d'un secteur
  function getWalls(al, nb_sec) {
	let walls = null;
	let cur = null;
  
	for (let nb_wal = 0; nb_wal < al.sec[nb_sec].nb_wal; nb_wal++) {
	  const newWall = createWallsElem(al, nb_sec, nb_wal);
	  newWall.x1 = al.sec[nb_sec].walls[nb_wal].x1 * 10 + WIN_SIZEX / 2;
	  newWall.y1 = -al.sec[nb_sec].walls[nb_wal].y1 * 10 + WIN_SIZEY / 2;
	  newWall.x2 = al.sec[nb_sec].walls[nb_wal].x2 * 10 + WIN_SIZEX / 2;
	  newWall.y2 = -al.sec[nb_sec].walls[nb_wal].y2 * 10 + WIN_SIZEY / 2;
  
	  if (!walls) {
		walls = newWall;
		cur = walls;
	  } else {
		cur.next = newWall;
		cur = cur.next;
	  }
	}
  
	return walls;
  }
  
  // Fonction pour créer un élément de secteur
  function createSectorElem(al, nb_sec) {
	const sector = {
	  walls: getWalls(al, nb_sec),
	  next: null,
	  fl_hei: al.sec[nb_sec].fl_hei,
	  ce_hei: al.sec[nb_sec].ce_hei,
	  fl_tex: al.sec[nb_sec].fl_tex,
	  ce_tex: al.sec[nb_sec].ce_tex,
	  nb_wal: al.sec[nb_sec].nb_wal,
	};
  
	return sector;
  }