// Fonction pour convertir les murs d'un secteur en format de jeu
function wallsToGame(walls, sec) {
	let i = sec.nb_wal - 1;
  
	while (walls) {
	  sec.walls[i] = { ...walls };
	  sec.walls[i].x1 = (sec.walls[i].x1 - WIN_SIZEX / 2) / 10.0;
	  sec.walls[i].x2 = (sec.walls[i].x2 - WIN_SIZEX / 2) / 10.0;
	  sec.walls[i].y1 = (sec.walls[i].y1 - WIN_SIZEY / 2) / -10.0;
	  sec.walls[i].y2 = (sec.walls[i].y2 - WIN_SIZEY / 2) / -10.0;
	  walls = walls.next;
	  i--;
	}
  }
  
  // Fonction pour compter le nombre de murs dans un secteur
  function howManyWalls(sec) {
	let cur = sec.walls;
	let count = 0;
  
	while (cur) {
	  cur = cur.next;
	  count++;
	}
	return count;
  }
  
  // Fonction pour convertir un secteur en format de jeu
  function sectorToGame(al, cur, id) {
	const sec = al.sec[id] = {};
	sec.fl_hei = cur.fl_hei;
	sec.ce_hei = cur.ce_hei;
	sec.fl_tex = cur.fl_tex;
	sec.ce_tex = cur.ce_tex;
	sec.nb_wal = howManyWalls(cur);
	sec.walls = new Array(sec.nb_wal);
	wallsToGame(cur.walls, sec);
  }
  
  // Fonction pour compter le nombre de secteurs
  function howManySectors(al) {
	let cur = al.sect;
	let count = 0;
  
	while (cur) {
	  cur = cur.next;
	  count++;
	}
	return count;
  }
  
  // Fonction principale pour convertir l'éditeur en format de jeu
  function editToGame(al) {
	linkSectors(al);
  
	if (!al.sect) {
	  console.log("Empty map");
	  return;
	}
  
	al.nb_sec = howManySectors(al);
	al.tmp_sec = al.sec;
	al.sec = new Array(al.nb_sec + 1);
  
	let cur = al.sect;
	let id = 0;
  
	while (cur) {
	  sectorToGame(al, cur, id);
	  cur = cur.next;
	  id++;
	}
  
	if (!al.edit.sect_end) {
	  convertEnd(al);
	}
  
	loadPig(al);
  
	if (!al.map_write_name) {
	  al.map_write_name = "poi.hms";
	}
  
	if (hmsEncoder(al, al.map_write_name)) {
	  finishWrite(al, 1);
	} else {
	  finishWrite(al, 0);
	}
  }