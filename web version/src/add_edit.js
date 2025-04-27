// Fonction pour définir les coordonnées d'un mur
function setCoo(al, bev, who, wall) {
    if (who === 1) {
      wall.x1 = bev.x - (bev.x % al.edit.zoom);
      wall.y1 = bev.y - (bev.y % al.edit.zoom);
    } else {
      wall.x2 = bev.x - (bev.x % al.edit.zoom);
      wall.y2 = bev.y - (bev.y % al.edit.zoom);
    }
  }
  
  // Fonction pour initialiser un secteur
  function initSec(al) {
    al.sect = {
      walls: {
        x1: 0,
        y1: 0,
        x2: 0,
        y2: 0,
        next: null,
      },
      next: null,
      nb_wal: 1,
    };
  
    setCoo(al, { x: -1, y: -1 }, 1, al.sect.walls);
    setCoo(al, { x: -1, y: -1 }, 2, al.sect.walls);
  }
  
  // Fonction pour initialiser un secteur ou en ajouter un nouveau
  function initSect(al, sect) {
    if (!sect) {
      initSec(al);
    } else {
      const newSect = {
        walls: {
          x1: 0,
          y1: 0,
          x2: 0,
          y2: 0,
          next: null,
        },
        next: al.sect,
        nb_wal: 1,
      };
  
      setCoo(al, { x: -1, y: -1 }, 1, newSect.walls);
      setCoo(al, { x: -1, y: -1 }, 2, newSect.walls);
      al.sect = newSect;
    }
  }
  
  // Fonction pour corriger les murs d'un secteur
  function correctAllShit(sect) {
    let wall = sect.walls;
  
    sect.ce_hei = 2.5;
    sect.fl_tex = 2;
    sect.ce_tex = 3;
  
    while (wall) {
      const tmpx1 = wall.x1;
      const tmpy1 = wall.y1;
      wall.x1 = wall.x2;
      wall.y1 = wall.y2;
      wall.x2 = tmpx1;
      wall.y2 = tmpy1;
  
      if (!wall.sec_lnk && !wall.wall_tex) {
        wall.wall_tex = 1;
      }
  
      wall = wall.next;
    }
  }
  
  // Fonction pour ajouter un mur à un secteur
  function addWall(al, sect, coo) {
    if (
      sect.walls.x1 === sect.walls.x2 &&
      sect.walls.y1 === sect.walls.y2
    ) {
      return;
    }
  
    if (
      sect.walls.next &&
      checkEndSector(
        sect.walls.next,
        coo.x - (coo.x % al.edit.zoom),
        coo.y - (coo.y % al.edit.zoom)
      ) === 1
    ) {
      al.edit.stat = "SELECT";
      al.edit.index_sect++;
      correctAllShit(al.sect);
      return;
    }
  
    const newWall = {
      x1: sect.walls.x2,
      y1: sect.walls.y2,
      x2: sect.walls.x2,
      y2: sect.walls.y2,
      next: sect.walls,
    };
  
    sect.nb_wal++;
    sect.walls = newWall;
  }
  
  // Fonction fictive pour vérifier la fin d'un secteur (à implémenter selon vos besoins)
  function checkEndSector(wall, x, y) {
    // Implémentez la logique de vérification ici
    return 0; // Exemple : retourne 0 par défaut
  }