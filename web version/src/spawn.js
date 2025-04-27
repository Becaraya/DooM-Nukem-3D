function setSpawn(al, spw) {
    const tmp = {
        x: spw.x - (spw.x % al.edit.zoom),
        y: spw.y - (spw.y % al.edit.zoom),
    };

    al.play.posx = (tmp.x - WIN_SIZEX / 2) / 10;
    al.play.posy = (tmp.y - WIN_SIZEY / 2) / -10;
}

function convertEnd(al) {
    const tmp = {
        x: (al.endSect.x - WIN_SIZEX / 2) / 10,
        y: (al.endSect.y - WIN_SIZEY / 2) / -10,
    };

    al.edit.sectEnd = isInSector(al, tmp.x, tmp.y);
    if (!al.edit.sectEnd) {
        al.edit.sectEnd = -1;
    }
}

function setEnd(al, bev) {
    al.endSect = {
        x: bev.x - (bev.x % al.edit.zoom),
        y: bev.y - (bev.y % al.edit.zoom),
    };

    al.edit.spawnz = 0;
    al.edit.sectEnd = 0;
}