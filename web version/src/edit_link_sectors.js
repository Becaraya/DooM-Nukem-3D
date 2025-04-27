// Fonction pour lier un mur à un secteur
function linkWall(cur, set, id) {
	let wall = cur.walls;
  
	while (wall) {
	  if (
		(wall.x1 === set.x1 && wall.x2 === set.x2 && wall.y1 === set.y1 && wall.y2 === set.y2) ||
		(wall.x1 === set.x2 && wall.x2 === set.x1 && wall.y1 === set.y2 && wall.y2 === set.y1)
	  ) {
		set.sec_lnk = id + 1;
		set.is_cross = true;
		set.wall_tex = 0;
		return;
	  }
	  wall = wall.next;
	}
  }
  
  // Fonction pour lier un secteur à d'autres secteurs
  function linkSector(root, cur, id) {
	let wall;
	let i = 0;
  
	while (root) {
	  wall = i !== id ? cur.walls : null;
	  while (wall) {
		linkWall(root, wall, i);
		wall = wall.next;
	  }
	  root = root.next;
	  i++;
	}
  }
  
  // Fonction principale pour lier tous les secteurs
  function linkSectors(al) {
	let cur = al.sect;
	let id = 0;
  
	while (cur) {
	  linkSector(al.sect, cur, id);
	  cur = cur.next;
	  id++;
	}
  }