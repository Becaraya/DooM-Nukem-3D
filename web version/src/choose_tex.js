// Fonction pour afficher le menu des textures
function displayTexMenu(ctx, tex, i, canvasWidth, canvasHeight) {
	let texX, texY;
	let x, y;
  
	y = i;
	texY = 0;
  
	while (y < canvasHeight && texY < tex.size_y && y < i + TEX_SIZE_MENU) {
	  x = canvasWidth - TEX_SIZE_MENU;
	  texX = Math.floor(x / tex.size_x);
  
	  while (x < canvasWidth && texX < tex.size_x) {
		const color = tex.pix[texX + texY * tex.size_x];
		ctx.fillStyle = `#${color.toString(16).padStart(8, '0')}`;
		ctx.fillRect(x, y, 1, 1); // Dessine un pixel
		texX++;
		x++;
	  }
	  texY++;
	  y++;
	}
  }
  
  // Fonction pour définir la texture d'un mur
  function setWallTex(al) {
	let tmpS = al.sect;
	let tmpW;
	let i = 0;
	let j = 0;
  
	while (al.edit.index_sect + i++ < al.nb_sec) {
	  tmpS = tmpS.next;
	}
	tmpW = tmpS.walls;
	while (j++ !== al.edit.index_wall) {
	  tmpW = tmpW.next;
	}
	tmpW.wall_tex = al.tex_choice;
  }
  
  // Fonction pour définir la texture du sol
  function setFloTex(al) {
	let tmpS = al.sect;
	let i = 0;
  
	while (al.edit.index_sect + i++ < al.nb_sec) {
	  tmpS = tmpS.next;
	}
	tmpS.fl_tex = al.tex_choice;
  }
  
  // Fonction pour gérer le clic sur le menu des textures
  function clickOnMenu(al, canvas, event) {
	const rect = canvas.getBoundingClientRect();
	const mouseX = event.clientX - rect.left;
	const mouseY = event.clientY - rect.top;
  
	if (
	  mouseX >= canvas.width - TEX_SIZE_MENU &&
	  mouseY <= (al.nb_tex + 1) * TEX_SIZE_MENU
	) {
	  al.tex_choice = Math.floor(mouseY / TEX_SIZE_MENU);
  
	  if (al.edit.stat === "SET_WALL_TEXT") {
		setWallTex(al);
	  }
	  if (al.edit.stat === "SET_FLO_TEXT") {
		setFloTex(al);
	  }
	  if (al.edit.stat === "SET_CEL_TEXT") {
		let tmpS = al.sect;
		let i = 0;
  
		while (al.edit.index_sect + i++ < al.nb_sec) {
		  tmpS = tmpS.next;
		}
		tmpS.ce_tex = al.tex_choice;
	  }
	  al.edit.stat = "SELECT";
	}
  }
  
  // Fonction pour afficher le menu des textures et gérer les clics
  function texMenu(al, canvas) {
	const ctx = canvas.getContext("2d");
  
	for (let i = 0; i <= al.nb_tex; i++) {
	  displayTexMenu(ctx, al.tex[i], i * TEX_SIZE_MENU, canvas.width, canvas.height);
	}
  
	canvas.addEventListener("mousedown", (event) => {
	  clickOnMenu(al, canvas, event);
	});
  }