// Fonction pour créer la carte
function getMap(al) {
	let sect = null;
	let cur = null;
  
	for (let nb_sec = 1; nb_sec <= al.nb_sec; nb_sec++) {
	  if (!sect) {
		sect = createSectorElem(al, nb_sec);
		cur = sect;
	  } else {
		cur.next = createSectorElem(al, nb_sec);
		cur = cur.next;
	  }
	}
  
	al.sect = sect;
  }
  
  // Fonction pour compter le nombre de murs
  function countWall(wall) {
	let count = 0;
  
	while (wall) {
	  count++;
	  wall = wall.next;
	}
  
	return count;
  }
  
  // Fonction pour compter le nombre de secteurs
  function countSect(sect) {
	let count = 0;
  
	while (sect) {
	  count++;
	  sect = sect.next;
	}
  
	return count;
  }
  
  // Fonction pour remplir les données des murs dans un tableau
  function getWallTab(al, nb_sec, walls) {
	let nb_wal = 0;
  
	while (walls) {
	  al.sec[nb_sec].walls[nb_wal] = {
		x1: (walls.x1 - WIN_SIZEX / 2) / 10,
		y1: (walls.y1 - WIN_SIZEY / 2) / -10,
		x2: (walls.x2 - WIN_SIZEX / 2) / 10,
		y2: (walls.y2 - WIN_SIZEY / 2) / -10,
		wall_tex: walls.wall_tex,
		top_tex: walls.top_tex,
		bot_tex: walls.bot_tex,
		sec_lnk: walls.sec_lnk,
		is_cross: walls.is_cross,
	  };
	  nb_wal++;
	  walls = walls.next;
	}
  
	al.sec[nb_sec].nb_wal = nb_wal;
  }
  
  // Fonction pour remplir les données des secteurs dans un tableau
  function getSecTab(al) {
	const sectCount = countSect(al.sect);
	al.sec = new Array(sectCount + 2).fill(null).map(() => ({ walls: [] }));
  
	let sect = al.sect;
	let nb_sec = 1;
  
	while (sect) {
	  getWallTab(al, nb_sec, sect.walls);
	  al.sec[nb_sec].fl_hei = sect.fl_hei;
	  al.sec[nb_sec].ce_hei = sect.ce_hei;
	  al.sec[nb_sec].fl_tex = sect.fl_tex;
	  al.sec[nb_sec].ce_tex = sect.ce_tex;
	  sect = sect.next;
	  nb_sec++;
	}
  
	al.nb_sec = nb_sec - 1;
	al.sect = null; // Libère la référence pour simuler un "free"
  }