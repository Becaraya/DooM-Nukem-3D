function freeBeforeRefresh(al) {
    if (al.edit.stat !== GRAVITY && al.text.gNum.str) {
        al.text.gNum.str = null;
    }
}

function refresh(al) {
    if (al.status === EDIT) {
        text(al);
    }
    if (al.k.t === 1 && al.status === GAME) {
        printText(al, al.text.t, al.sdlSurf);
    }
    if (!updateWindowSurface(al.sdlWin)) {
        yeet(al);
    }
    if (al.status === EDIT && !updateWindowSurface(al.winEd)) {
        yeet(al);
    }
}

function updateWindowSurface(window) {
    // Simulated window surface update
    return true;
}