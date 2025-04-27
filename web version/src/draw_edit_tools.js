// Fonction pour dessiner un mur
function drawWall(al, wall, clr) {
	if (!wall) return;
  
	const a = { x: wall.x1, y: wall.y1 };
	const b = { x: wall.x2, y: wall.y2 };
	const clrTmp = clr === WHITE && wall.sec_lnk ? LIGHT_GREY : clr;
  
	if (wall.x1 !== -1) {
	  putLine(al.sdlsurf, a, b, clrTmp); // Dessine une ligne entre deux points
	}
  
	if (wall.next) {
	  drawWall(al, wall.next, clr); // Appelle récursivement pour le mur suivant
	}
  }
  
  // Fonction pour dessiner un mur avec un index spécifique
  function drawWallIndex(al, wall, index) {
	if (!wall) return;
  
	const a = { x: wall.x1, y: wall.y1 };
	const b = { x: wall.x2, y: wall.y2 };
	let clr = wall.sec_lnk ? DARK_RED : RED;
  
	if (index === 0) {
	  clr = wall.sec_lnk ? DARK_YELLOW : YELLOW;
	}
  
	if (wall.x1 !== -1) {
	  putLine(al.sdlsurf, a, b, clr); // Dessine une ligne entre deux points
	}
  
	if (wall.next) {
	  drawWallIndex(al, wall.next, index - 1); // Appelle récursivement pour le mur suivant
	}
  }
  
  // Fonction pour dessiner un secteur avec un index spécifique
  function drawSectIndex(al, sect, i_s) {
	if (!sect) return;
  
	if (i_s === al.edit.index_sect) {
	  drawWallIndex(al, sect.walls, al.edit.index_wall);
	} else if (sect.next) {
	  drawSectIndex(al, sect.next, i_s - 1); // Appelle récursivement pour le secteur suivant
	}
  }
  
  // Fonction pour dessiner un secteur
  function drawSect(al, sect) {
	if (!sect) return;
  
	drawWall(al, sect.walls, WHITE); // Dessine les murs du secteur
	if (sect.next) {
	  drawSect(al, sect.next); // Appelle récursivement pour le secteur suivant
	}
  }