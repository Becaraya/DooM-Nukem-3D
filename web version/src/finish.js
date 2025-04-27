// Fonction pour terminer l'écriture de la carte
function finishWrite(al, success) {
	if (success) {
	  console.log("Exiting...");
	  window.close(); // Simule un exit(0) en fermant la fenêtre
	} else {
	  console.log(`Map written as [${al.map_write_name}]!`);
	  window.close(); // Simule un exit(0)
	}
  }
  
  // Fonction pour afficher une erreur
  function prErr(str) {
	console.error(str);
	return 1;
  }
  
  // Fonction pour vérifier une texture et afficher un résultat
  function javoueJabuse1(tgp, i, or) {
	const tmp = tgp.or[or].pix[i];
  
	if (
	  tmp[0] === 0xffff00ff &&
	  tmp[1] === 0xff000000 &&
	  tmp[2] === 0xff000000 &&
	  tmp[3] === 0xffff00ff
	) {
	  tgp.size_x = 2;
	  tgp.size_y = 2;
	  console.log("X");
	} else {
	  console.log("O");
	}
  }
  
  // Fonction pour préparer la sortie (simulation d'une erreur)
  function prepareExit(al) {
	console.error("[1]    9654 segmentation fault  ./doom_nukem");
	window.close(); // Simule un exit(0)
  }