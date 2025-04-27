function setDefaultPlayer(al) {
    al.g = DEFAULT_G;
    al.play.mass = PLAYER_MASS;
    al.play.powerMult = 1;
    al.play.size = PLAYER_SIZE;
    al.play.eyez = PLAYER_SIZE - PLAYER_EYE_TOP;
    al.play.alive = 10;
}

function mPressEdGlobNArr(al, bev) {
    arrowStat(al, bev);
    mousePressEditMiniMenu(al, bev);
    mousePressEditSettingSector(al, bev);
    mousePressEditPlayer(al, bev);
}

function resetMap(al) {
    freeSect(al.sect);
    al.sect = null;
    al.nbSec = 0;
    al.edit.indexSect = 0;
    al.edit.indexWall = 0;
}

function mousePressEditMenu(al, bev) {
    if (al.edit.stat === DRAWING) {
        if (bev.x > 590 && bev.x < 685 && bev.y > 15 && bev.y < 48) {
            al.edit.stat = SELECT;
            freeWall(al.sect.walls);
            al.nbSec--;
            delOneSect(al.sect);
        }
    } else {
        mPressEdGlobNArr(al, bev);
    }

    if (inr(itop(45, 125), itop(230, 170), itop(bev.x, bev.y))) {
        al.hard = !al.hard;
    }
    if (inr(itop(280, 125), itop(460, 170), itop(bev.x, bev.y)) && al.edit.stat !== DRAWING && al.sect) {
        resetMap(al);
    }
    if (inr(itop(495, 125), itop(645, 170), itop(bev.x, bev.y))) {
        setDefaultPlayer(al);
    }
    if (inr(itop(280, 655), itop(493, 698), itop(bev.x, bev.y))) {
        editToGame(al);
    }
}

function mousePressEdit(al) {
    const bev = al.ev.button;

    if (bev.type === "mouseup") return;

    if (bev.windowID === 1) {
        if (al.edit.stat === SET_SPAWN) {
            setSpawn(al, bev);
        }
        if (al.edit.stat === SET_END) {
            setEnd(al, bev);
        }
        if (al.edit.stat === SET_BAD_PIG) {
            badPig(al, bev);
        }
        if (al.edit.stat === SELECT) {
            al.edit.stat = DRAWING;
            al.nbSec++;
            al.edit.indexWall = 1;
            addSector(al, itop(bev.x, bev.y));
        } else if (al.edit.stat === DRAWING) {
            checkCanAdd(al, al.sect, itop(bev.x, bev.y));
        }
    }

    if (bev.windowID === 2) {
        mousePressEditMenu(al, bev);
    }
}