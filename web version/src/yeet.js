function freeWall(walls) {
    if (walls.next) {
        freeWall(walls.next);
    }
    walls = null;
}

function freeSect(sect) {
    if (sect.next) {
        freeSect(sect.next);
    }
    freeWall(sect.walls);
    sect = null;
}

function yeet(al) {
    if (al.sect) {
        freeSect(al.sect);
    }
    if (al.font) {
        closeFont(al.font);
    }
    if (al.ttfSt) {
        quitTtf();
    }
    if (al.sdlSurf) {
        freeSurface(al.sdlSurf);
    }
    if (al.surfEd) {
        freeSurface(al.surfEd);
    }
    if (al.winEd) {
        destroyWindow(al.winEd);
    }
    al.ent = null;
    al.rotent = null;
    al = null;
    exit();
}

function closeFont(font) {
    // Simulated font closing
}

function quitTtf() {
    // Simulated TTF quit
}

function freeSurface(surface) {
    // Simulated surface freeing
}

function destroyWindow(window) {
    // Simulated window destruction
}

function exit() {
    // Simulated program exit
}