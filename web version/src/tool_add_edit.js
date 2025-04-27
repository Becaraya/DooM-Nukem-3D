function wallsToGame(walls, sec) {
    let i = sec.nbWal - 1;

    while (walls) {
        sec.walls[i] = { ...walls };
        sec.walls[i].x1 = (sec.walls[i].x1 - WIN_SIZEX / 2) / 10.0;
        sec.walls[i].x2 = (sec.walls[i].x2 - WIN_SIZEX / 2) / 10.0;
        sec.walls[i].y1 = (sec.walls[i].y1 - WIN_SIZEY / 2) / -10.0;
        sec.walls[i].y2 = (sec.walls[i].y2 - WIN_SIZEY / 2) / -10.0;
        walls = walls.next;
        i--;
    }
}

function addSector(al, coo) {
    initSect(al, al.sect);
    setCoo(al, coo, 1, al.sect.walls);
    setCoo(al, coo, 2, al.sect.walls);
}

function checkEndSector(wall, x, y) {
    let tmp = wall;

    while (tmp.next) {
        tmp = tmp.next;
    }

    return tmp.x1 === x && tmp.y1 === y;
}

function checkCanAdd(al, sect, coo) {
    const tmp = {
        x: coo.x - (coo.x % al.edit.zoom),
        y: coo.y - (coo.y % al.edit.zoom),
    };

    if (sect.walls.next && sect.walls.next.x1 === tmp.x && sect.walls.next.y1 === tmp.y) {
        return;
    }

    addWall(al, al.sect, coo);
}

function delOneSect(sect) {
    if (!sect.next) {
        sect = null;
    } else {
        const tmp = sect.next;
        sect = tmp;
    }
}