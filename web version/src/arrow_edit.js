// Fonction pour ajuster la hauteur du plafond ou du sol
function arrowStatHei(al, bev) {
	let tmp = al.sect;
	let i = 0;
  
	// Parcourt les secteurs jusqu'à atteindre l'index souhaité
	while (al.edit.index_sect + i++ < al.nb_sec) {
	  tmp = tmp.next;
	}
  
	if (al.edit.stat === "SET_CEL_HEI") {
	  if (
		bev.x > 520 &&
		bev.x < 545 &&
		bev.y > 410 &&
		bev.y < 435 &&
		tmp.ce_hei > tmp.fl_hei &&
		tmp.ce_hei
	  ) {
		tmp.ce_hei -= 0.25;
	  }
	  if (inr(itop(630, 410), itop(660, 435), itop(bev.x, bev.y))) {
		tmp.ce_hei += 0.25;
	  }
	}
  
	if (al.edit.stat === "SET_FLO_HEI") {
	  if (
		bev.x > 520 &&
		bev.x < 545 &&
		bev.y > 410 &&
		bev.y < 435 &&
		tmp.fl_hei > 0
	  ) {
		tmp.fl_hei -= 0.25;
	  }
	  if (
		inr(itop(630, 410), itop(660, 435), itop(bev.x, bev.y)) &&
		tmp.ce_hei > tmp.fl_hei
	  ) {
		tmp.fl_hei += 0.25;
	  }
	}
  }
  
  // Fonction pour ajuster les statistiques du joueur
  function arrowStatPlayer(al, bev) {
	if (bev.x > 520 && bev.x < 545 && bev.y > 410 && bev.y < 435) {
	  arrowStatPlayerMinus(al);
	}
	if (inr(itop(630, 410), itop(660, 435), bev)) {
	  arrowStatPlayerPlus(al);
	}
  }
  
  // Fonction pour ajuster la gravité
  function arrowGravity(al, bev) {
	if (inr(itop(520, 625), itop(545, 660), itop(bev.x, bev.y)) && al.g > 2) {
	  if (al.g === DEFAULT_G) {
		al.g = 9.0;
	  } else {
		al.g--;
	  }
	}
	if (inr(itop(630, 615), itop(660, 660), itop(bev.x, bev.y))) {
	  if (al.g === DEFAULT_G) {
		al.g = 10.0;
	  } else {
		al.g++;
	  }
	}
  
	// Met à jour la chaîne de gravité
	al.text.g_num.str = dtoaDoom(al.g);
  }
  
  // Fonction principale pour gérer les flèches
  function arrowStat(al, bev) {
	if (
	  al.edit.index_sect > 1 &&
	  bev.x > 145 &&
	  bev.x < 175 &&
	  bev.y > 15 &&
	  bev.y < 47
	) {
	  al.edit.index_wall = 0;
	  al.edit.index_sect--;
	  al.edit.stat = "SELECT";
	}
	if (
	  al.edit.index_sect < al.nb_sec &&
	  bev.x > 176 &&
	  bev.x < 195 &&
	  bev.y > 15 &&
	  bev.y < 47
	) {
	  al.edit.index_wall = 0;
	  al.edit.index_sect++;
	  al.edit.stat = "SELECT";
	}
	if (
	  al.edit.index_wall > 0 &&
	  bev.x > 145 &&
	  bev.x < 175 &&
	  bev.y > 59 &&
	  bev.y < 86
	) {
	  al.edit.index_wall--;
	}
	if (
	  al.edit.index_wall < nbWall(al) - 1 &&
	  bev.x > 176 &&
	  bev.x < 195 &&
	  bev.y > 59 &&
	  bev.y < 86
	) {
	  al.edit.index_wall++;
	}
	if (al.edit.stat === "SET_CEL_HEI" || al.edit.stat === "SET_FLO_HEI") {
	  arrowStatHei(al, bev);
	}
	if (al.edit.stat >= "LIFE" && al.edit.stat <= "MASS") {
	  arrowStatPlayer(al, itop(bev.x, bev.y));
	}
	if (al.edit.stat === "GRAVITY") {
	  arrowGravity(al, bev);
	}
  }
  
  // Fonctions utilitaires (à implémenter ou adapter selon vos besoins)
  function inr(p1, p2, p) {
	// Vérifie si un point est dans un rectangle défini par p1 et p2
	return (
	  p.x >= p1.x && p.x <= p2.x && p.y >= p1.y && p.y <= p2.y
	);
  }
  
  function itop(x, y) {
	// Convertit des coordonnées en un objet point
	return { x: x, y: y };
  }
  
  function dtoaDoom(value) {
	// Convertit un nombre en chaîne de caractères
	return value.toFixed(2);
  }
  
  function nbWall(al) {
	// Retourne le nombre de murs dans le secteur actuel
	return al.sect.nb_wal || 0;
  }
  
  function arrowStatPlayerMinus(al) {
	// Diminue une statistique du joueur (à implémenter)
  }
  
  function arrowStatPlayerPlus(al) {
	// Augmente une statistique du joueur (à implémenter)
  }