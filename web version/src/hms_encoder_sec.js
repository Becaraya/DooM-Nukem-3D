// Fonction pour écrire un mur dans un buffer
function writeWall(wall) {
	const buf = new ArrayBuffer(32);
	const view = new DataView(buf);
  
	view.setInt32(0, wall.x2 * 100, true);
	view.setInt32(4, wall.y2 * 100, true);
	view.setInt32(8, wall.x1 * 100, true);
	view.setInt32(12, wall.y1 * 100, true);
	view.setUint16(16, wall.wall_tex, true);
	view.setUint16(18, wall.bot_tex, true);
	view.setUint16(20, wall.top_tex, true);
	view.setUint16(22, wall.is_cross, true);
	view.setUint32(24, wall.sec_lnk, true);
  
	return buf;
  }
  
  // Fonction pour écrire tous les murs d'un secteur
  function writeWalls(sec) {
	const buffers = [];
	for (let i = 0; i < sec.nb_wal; i++) {
	  buffers.push(writeWall(sec.walls[i]));
	}
	return buffers;
  }
  
  // Fonction pour écrire un secteur dans un buffer
  function writeSector(sec) {
	const buf = new ArrayBuffer(16);
	const view = new DataView(buf);
  
	view.setUint32(0, Math.round((sec.fl_hei + 0.001) * 100), true);
	view.setUint32(4, Math.round((sec.ce_hei + 0.001) * 100), true);
	view.setUint16(8, sec.fl_tex, true);
	view.setUint16(10, sec.ce_tex, true);
	view.setUint32(12, sec.nb_wal, true);
  
	const wallsBuffers = writeWalls(sec);
	return [buf, ...wallsBuffers];
  }
  
  // Fonction pour écrire tous les secteurs
  function writeSectors(al) {
	const headerBuf = new ArrayBuffer(32);
	const headerView = new DataView(headerBuf);
  
	headerView.setInt32(0, al.nb_sec, true);
	headerView.setInt32(4, al.play.csec || 1, true);
	headerView.setInt32(8, al.play.posx * 100, true);
	headerView.setInt32(12, al.play.posy * 100, true);
	headerView.setInt32(16, al.door, true);
	headerView.setInt32(20, al.hard, true);
	headerView.setInt32(24, (al.end_sect.x - WIN_SIZEX / 2) / 10, true);
	headerView.setInt32(28, (al.end_sect.y - WIN_SIZEY / 2) / -10, true);
  
	const buffers = [headerBuf];
	for (let i = 1; i <= al.nb_sec; i++) {
	  buffers.push(...writeSector(al.sec[i]));
	}
  
	return buffers;
  }
  
  // Fonction pour écrire les données dans un fichier
  function writeToFile(buffers, filename) {
	const blob = new Blob(buffers, { type: "application/octet-stream" });
	const link = document.createElement("a");
	link.href = URL.createObjectURL(blob);
	link.download = filename;
	link.click();
  }