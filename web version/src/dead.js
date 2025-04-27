// Fonction pour appliquer une transparence (alpha) à une couleur
function alphaPix(pix, alpha) {
	const r = ((pix >> 16) & 0xff) * alpha;
	const g = ((pix >> 8) & 0xff) * alpha;
	const b = (pix & 0xff) * alpha;
	return ((r << 16) | (g << 8) | b) >>> 0; // Assure un entier non signé
  }
  
  // Fonction pour appliquer une transparence à tous les pixels d'une image source vers une destination
  function pixToPix(src, dst, alpha) {
	alpha = Math.max(0, Math.min(1, alpha)); // Clamp alpha entre 0 et 1
	for (let i = 0; i < WIN_SIZEX * WIN_SIZEY; i++) {
	  dst[i] = alphaPix(src[i], alpha);
	}
  }
  
  // Fonction pour afficher le texte "You Died" avec une échelle et une transparence
  function prontUrded(al, scale, alpha) {
	const yd = al.you_died;
	const winX = Math.floor(WIN_SIZEX / 2 - (yd.size_x * scale) / 2);
	const winY = Math.floor(WIN_SIZEY / 2 - (yd.size_y * scale) / 2);
  
	for (let y = 0; y < yd.size_y * scale; y++) {
	  for (let x = 0; x < yd.size_x * scale; x++) {
		const tmp = yd.pix[Math.floor(y / scale) * yd.size_x + Math.floor(x / scale)];
		if (tmp !== 0xffff) { // Ignore les pixels transparents
		  al.pix[(y + winY) * WIN_SIZEX + (x + winX)] = alphaPix(tmp, alpha);
		}
	  }
	}
  }
  
  // Fonction principale pour gérer l'état "mort" du joueur
  function dead(al) {
	if (!dead.stat) dead.stat = 0; // Variable statique simulée
	dead.stat += al.dtime;
  
	const scale = (dead.stat / 16000000.0) + 1.6;
	pixToPix(al.pix_dead, al.pix, (2000000 - dead.stat) / 2000000.0);
  
	if (dead.stat < 1000000) {
	  prontUrded(al, scale, dead.stat / 1000000.0);
	} else if (dead.stat < 3000000) {
	  prontUrded(al, scale, 1);
	} else if (dead.stat < 4000000) {
	  prontUrded(al, scale, (4000000 - dead.stat) / 1000000.0);
	}
  
	refresh(al); // Rafraîchit l'écran
  }