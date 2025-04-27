// Fonction pour créer une texture par défaut
function createDefaultTexture() {
	return {
	  size_x: 2,
	  size_y: 2,
	  pix: [
		0xffff00ff, // Magenta
		0xff000000, // Noir
		0xff000000, // Noir
		0xffff00ff, // Magenta
	  ],
	};
  }
  
  // Fonction pour charger une texture BMP
  function bmpToTex(tex, filePath, sizex, sizey) {
	return new Promise((resolve, reject) => {
	  const xhr = new XMLHttpRequest();
	  xhr.open("GET", filePath, true);
	  xhr.responseType = "arraybuffer";
  
	  xhr.onload = function () {
		if (xhr.status === 200) {
		  const buffer = xhr.response;
		  const dataView = new DataView(buffer);
  
		  // Lire l'offset des données de l'image
		  const offset = dataView.getUint32(10, true);
  
		  // Initialiser la texture
		  tex.size_x = sizex;
		  tex.size_y = sizey;
		  tex.pix = new Uint32Array(buffer, offset, sizex * sizey);
  
		  // Appliquer un masque alpha si nécessaire
		  for (let i = 0; i < tex.pix.length; i++) {
			if (tex.pix[i] !== 0xffff) {
			  tex.pix[i] |= 0xff000000; // Ajouter un canal alpha
			}
		  }
  
		  resolve(tex);
		} else {
		  // Charger une texture par défaut en cas d'erreur
		  resolve(createDefaultTexture());
		}
	  };
  
	  xhr.onerror = function () {
		// Charger une texture par défaut en cas d'erreur
		resolve(createDefaultTexture());
	  };
  
	  xhr.send();
	});
  }
  
  // Fonction pour charger des pixels BMP
  function bmpToPix(filePath, sizex, sizey) {
	return new Promise((resolve, reject) => {
	  const xhr = new XMLHttpRequest();
	  xhr.open("GET", filePath, true);
	  xhr.responseType = "arraybuffer";
  
	  xhr.onload = function () {
		if (xhr.status === 200) {
		  const buffer = xhr.response;
		  const dataView = new DataView(buffer);
  
		  // Lire l'offset des données de l'image
		  const offset = dataView.getUint32(10, true);
  
		  // Initialiser les pixels
		  const pix = new Uint32Array(buffer, offset, sizex * sizey);
  
		  // Appliquer un masque alpha si nécessaire
		  for (let i = 0; i < pix.length; i++) {
			if (pix[i] !== 0xffff) {
			  pix[i] |= 0xff000000; // Ajouter un canal alpha
			}
		  }
  
		  resolve(pix);
		} else {
		  // Charger des pixels par défaut en cas d'erreur
		  resolve(createDefaultTexture().pix);
		}
	  };
  
	  xhr.onerror = function () {
		// Charger des pixels par défaut en cas d'erreur
		resolve(createDefaultTexture().pix);
	  };
  
	  xhr.send();
	});
  }