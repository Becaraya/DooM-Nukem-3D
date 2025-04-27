function mousePress(al) {
    if (al.status === GAME) {
        pewpew(al);
    } else if (al.status === EDIT) {
        mousePressEdit(al);
    } else if (al.status === DEAD || al.status === WON) {
        exitGame();
    }
}

function mouseMove(al) {
    const mev = al.ev.motion;

    if (al.status === GAME) {
        if (mev.x !== WIN_SIZEX / 2) {
            al.play.dir = (al.play.dir + mev.xrel * 10) & D_2PIM;
        }
        if (mev.y !== WIN_SIZEY / 2) {
            al.play.horizon += mev.yrel * 3;
        }
    }

    if (mev.windowID === 1 && al.edit.stat === DRAWING) {
        al.sect.walls.x2 = mev.x - (mev.x % al.edit.zoom);
        al.sect.walls.y2 = mev.y - (mev.y % al.edit.zoom);
    }
}

function mouseWheel(al) {
    // Placeholder for mouse wheel functionality
}