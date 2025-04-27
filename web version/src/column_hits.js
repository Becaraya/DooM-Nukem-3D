// Fonction pour gérer les impacts au sol
function hitFloor(al, ray, hitnb) {
	const hit = ray.hits[hitnb];
	const tex = al.tex[hit.fl_tex];
	let y = hit.lim.sc_botwall;
  
	const f = {
	  posx: al.play.posx * 65535 * al.fov,
	  posy: al.play.posy * 65535 * al.fov,
	  hor: al.play.horizon + HORIZON_LIMIT,
	  indst:
		(65535 * (al.play.eyez - hit.fl_hei) * al.stretch) /
		al.cos[subAngle(ray.angle, al.play.dir)],
	};
  
	while (y < hit.lim.sc_botlim) {
	  let tmp = 2 * (y + f.hor) - al.stretch;
	  tmp = tmp ? f.indst / tmp : 65535;
  
	  f.dstx = (tmp * ray.xfact) / 65535 + f.posx * 1.04;
	  f.dsty = (tmp * ray.yfact) / 65535 + f.posy * 1.04;
  
	  f.dstx = ((f.dstx & TEX_REPEAT_F) * tex.size_x) >> TEX_REPEAT_F_DIV;
	  f.dsty = ((f.dsty & TEX_REPEAT_F) * tex.size_y) >> TEX_REPEAT_F_DIV;
  
	  const texIndex = f.dsty * tex.size_x + f.dstx;
	  al.pix[y * WIN_SIZEX + ray.x] =
		(tex.pix[texIndex] >> 24) ? tex.pix[texIndex] : skybox(al, y, 0);
  
	  y++;
	}
  }
  
  // Fonction pour gérer les impacts au plafond
  function hitCeiling(al, ray, hitnb) {
	const hit = ray.hits[hitnb];
	const tex = al.tex[hit.ce_tex];
	let y = hit.lim.sc_toplim;
  
	const f = {
	  posx: al.play.posx * 65535 * al.fov,
	  posy: al.play.posy * 65535 * al.fov,
	  hor: al.play.horizon + HORIZON_LIMIT,
	  indst:
		(65535 * (hit.ce_hei - al.play.eyez) * al.stretch) /
		al.cos[subAngle(ray.angle, al.play.dir)],
	};
  
	while (y < hit.lim.sc_topwall) {
	  let tmp = al.stretch - 2 * (y + f.hor);
	  tmp = tmp ? f.indst / tmp : 65535;
  
	  f.dstx = (tmp * ray.xfact) / 65535 + f.posx * 1.04;
	  f.dsty = (tmp * ray.yfact) / 65535 + f.posy * 1.04;
  
	  f.dstx = ((f.dstx & TEX_REPEAT_F) * tex.size_x) >> TEX_REPEAT_F_DIV;
	  f.dsty = ((f.dsty & TEX_REPEAT_F) * tex.size_y) >> TEX_REPEAT_F_DIV;
  
	  const texIndex = f.dsty * tex.size_x + f.dstx;
	  al.pix[y * WIN_SIZEX + ray.x] =
		(tex.pix[texIndex] >> 24) ? tex.pix[texIndex] : skybox(al, y, 0);
  
	  y++;
	}
  }
  
  // Fonction pour gérer les impacts sur les murs inférieurs
  function hitBotWall(al, ray, hitnb) {
	const hit = ray.hits[hitnb];
	const tex = hit.tex;
	const lim = hit.lim;
	const totLength = lim.botwall - lim.botmid;
	let y = lim.sc_botmid;
  
	while (y < lim.sc_botwall) {
	  texFind(
		al.pix,
		y * WIN_SIZEX + ray.x,
		(hit.hit_texx * tex.size_x) / 65535,
		(((y - lim.botmid) * hit.botwall_he) / totLength) % TEX_REPEAT_F,
		tex
	  );
	  y++;
	}
  }
  
  // Fonction pour gérer les impacts sur les murs supérieurs et inférieurs
  function hitTopBotWall(al, ray, hitnb) {
	const hit = ray.hits[hitnb];
	const tex = hit.tex;
	const lim = hit.lim;
	const totLength = lim.topmid - lim.topwall;
	let y = lim.sc_topwall;
  
	while (y < lim.sc_topmid) {
	  texFind(
		al.pix,
		y * WIN_SIZEX + ray.x,
		(hit.hit_texx * tex.size_x) / 65535,
		(((y - lim.topwall) * hit.topwall_he) / totLength) % TEX_REPEAT_F,
		tex
	  );
	  y++;
	}
  
	hitBotWall(al, ray, hitnb);
  }
  
  // Fonction pour gérer les impacts sur les murs
  function hitWall(al, ray, hitnb) {
	const hit = ray.hits[hitnb];
	if (hit.transparent) return;
  
	const tex = hit.tex;
	const lim = hit.lim;
	const totLength = lim.botmid - lim.topmid;
	let y = lim.sc_topmid;
  
	while (y < lim.sc_botmid) {
	  texFind(
		al.pix,
		y * WIN_SIZEX + ray.x,
		(hit.hit_texx * tex.size_x) / 65535,
		(((y - lim.topmid) * hit.wall_he) / totLength) % TEX_REPEAT_F,
		tex
	  );
	  y++;
	}
  }