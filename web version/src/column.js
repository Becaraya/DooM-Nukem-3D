// Fonction pour limiter les valeurs d'un intervalle
function capInt(value, min, max) {
	return Math.max(min, Math.min(max, value));
}

// Fonction pour ajuster les limites d'un rayon
function scLims(lim, prlim) {
	lim.sc_toplim = capInt(lim.toplim, prlim.mb_toplim, prlim.mb_botlim);
	lim.sc_topwall = capInt(lim.topwall, prlim.mb_toplim, prlim.mb_botlim);
	lim.sc_topmid = capInt(lim.topmid, prlim.mb_toplim, prlim.mb_botlim);
	lim.sc_botlim = capInt(lim.botlim, prlim.mb_toplim, prlim.mb_botlim);
	lim.sc_botwall = capInt(lim.botwall, prlim.mb_toplim, prlim.mb_botlim);
	lim.sc_botmid = capInt(lim.botmid, prlim.mb_toplim, prlim.mb_botlim);
	lim.mb_toplim = lim.sc_topmid;
	lim.mb_botlim = lim.sc_botmid;
}

// Fonction pour gérer les entités dans un rayon
function hitEnt(al, ray, hitnb) {
	const tex = ray.hits[hitnb].tex;
	const lim = ray.hits[hitnb].lim;
	const totLength = lim.botmid - lim.topmid;
	let y = lim.sc_topmid;

	while (y < lim.sc_botmid) {
		texFind(
			al.pix,
			y * WIN_SIZEX + ray.x,
			ray.hits[hitnb].hit_texx,
			((y - lim.topmid) * tex.size_y) / totLength,
			tex
		);
		y++;
	}
}

// Fonction pour calculer la hauteur d'un nouveau mur
function newWallHe(hit, nhit) {
	const ceil = Math.min(hit.ce_hei, nhit.ce_hei);
	const floor = Math.max(hit.fl_hei, nhit.fl_hei);
	return (ceil - floor) * 65535; // Équivalent de UINT16_MAX
}

// Fonction pour traiter un impact
function hitPrint(al, ray, hitnb, prlim) {
	const hit = ray.hits[hitnb];
	const lim = hit.lim;
	const hor = WIN_SIZEY / 2 - al.play.horizon;

	if (!hit.is_entity) {
		lim.toplim = prlim.mb_toplim;
		lim.botlim = prlim.mb_botlim;
		hitWallHeights(al, hit, lim, hor);
		if (hitnb < ray.nb_hits - 1) {
			hitNextWalls(al, hit, lim, hor);
		}
		scLims(lim, prlim);
		hitCeiling(al, ray, hitnb);
		hitFloor(al, ray, hitnb);
		if (hitnb < ray.nb_hits - 1) {
			hitTopBotWall(al, ray, hitnb);
		}
	}

	if (hit.is_entity) {
		hitLineSaveEnt(al, hit, lim, hor);
		scLims(lim, prlim);
	}

	if (hitnb < ray.nb_hits - 1) {
		hitPrint(al, ray, hitnb + 1, hit.is_entity ? prlim : lim);
	}

	if (hit.is_entity) {
		hitEnt(al, ray, hitnb);
	} else {
		hitWall(al, ray, hitnb);
	}
}

// Fonction principale pour traiter une colonne
function column(al, ray) {
	const lim = {
		mb_toplim: 0,
		mb_botlim: WIN_SIZEY - 1,
	};

	hitPrint(al, ray, 0, lim);
}