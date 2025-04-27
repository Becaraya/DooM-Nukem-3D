// Fonction pour obtenir un mur spécifique
function getCoWal(al) {
	let tmpS = al.sect;
	let tmpW;
	let i = 0;
	let j = 0;
  
	while (al.nb_sec - i > al.edit.index_sect + 1) {
	  tmpS = tmpS.next;
	  i++;
	}
  
	tmpW = tmpS.walls;
	while (tmpS.nb_wal - j > al.edit.index_wall + 1) {
	  tmpW = tmpW.next;
	  j++;
	}
  
	return tmpW;
  }
  
  // Fonction pour afficher les coordonnées du secteur et du mur
  function printCo(al) {
	al.text.sect_index.str = `Sector ${al.edit.index_sect}`;
	al.text.wall_index.str = `Wall ${al.edit.index_wall + 1}`;
  }
  
  // Fonction pour dessiner les flèches interactives pour les secteurs
  function interactiveArrowSector(al, mev) {
	if (al.edit.index_sect > 1) {
	  drawTriangle(
		{ x: 160, y: 30 },
		-1,
		al.surf_ed,
		inr({ x: 145, y: 15 }, { x: 175, y: 47 }, { x: mev.x, y: mev.y })
		  ? BLACK
		  : WHITE
	  );
	}
	if (al.edit.index_sect < al.nb_sec) {
	  drawTriangle(
		{ x: 180, y: 30 },
		1,
		al.surf_ed,
		inr({ x: 176, y: 15 }, { x: 195, y: 47 }, { x: mev.x, y: mev.y })
		  ? BLACK
		  : WHITE
	  );
	}
	if (al.edit.index_wall > 0) {
	  drawTriangle(
		{ x: 160, y: 69 },
		-1,
		al.surf_ed,
		inr({ x: 145, y: 58 }, { x: 175, y: 88 }, { x: mev.x, y: mev.y })
		  ? BLACK
		  : WHITE
	  );
	}
	if (al.edit.index_wall < nbWall(al) - 1) {
	  drawTriangle(
		{ x: 180, y: 69 },
		1,
		al.surf_ed,
		inr({ x: 176, y: 58 }, { x: 195, y: 88 }, { x: mev.x, y: mev.y })
		  ? BLACK
		  : WHITE
	  );
	}
  }
  
  // Fonction pour dessiner les flèches interactives
  function interactiveArrow(al) {
	const mev = al.ev.motion;
  
	if (al.sect) {
	  interactiveArrowSector(al, mev);
	}
  
	if (
	  al.edit.stat === "SET_CEL_HEI" ||
	  al.edit.stat === "SET_FLO_HEI" ||
	  (al.edit.stat >= "LIFE" && al.edit.stat <= "MASS")
	) {
	  drawTriangle(
		{ x: 535, y: 420 },
		-1,
		al.surf_ed,
		inr({ x: 520, y: 410 }, { x: 545, y: 435 }, { x: mev.x, y: mev.y })
		  ? BLACK
		  : WHITE
	  );
	  drawTriangle(
		{ x: 640, y: 420 },
		1,
		al.surf_ed,
		inr({ x: 630, y: 410 }, { x: 660, y: 435 }, { x: mev.x, y: mev.y })
		  ? BLACK
		  : WHITE
	  );
	}
  
	if (al.edit.stat === "GRAVITY") {
	  drawTriangle(
		{ x: 535, y: 635 },
		-1,
		al.surf_ed,
		inr({ x: 520, y: 625 }, { x: 545, y: 660 }, { x: mev.x, y: mev.y })
		  ? BLACK
		  : WHITE
	  );
	  drawTriangle(
		{ x: 640, y: 635 },
		1,
		al.surf_ed,
		inr({ x: 630, y: 615 }, { x: 660, y: 660 }, { x: mev.x, y: mev.y })
		  ? BLACK
		  : WHITE
	  );
	}
  }
  
  // Fonction principale de l'éditeur
  function editor(al) {
	setEdit(al);
	al.pix_ed.fill(LIGHT_GREY);
  
	if (
	  al.edit.stat === "SET_WALL_TEXT" ||
	  al.edit.stat === "SET_CEL_TEXT" ||
	  al.edit.stat === "SET_FLO_TEXT"
	) {
	  texMenu(al);
	} else {
	  setEditMenu(al);
	}
  
	if (al.sect) {
	  drawSect(al, al.sect);
	  drawSectIndex(al, al.sect, al.nb_sec);
	}
  
	interactiveArrow(al);
	pigPos(al);
	refresh(al);
  }