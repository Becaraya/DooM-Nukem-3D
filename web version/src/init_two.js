function initStatus(al) {
    al.statFnc = [];
    al.statFnc[MENU] = menu;
    al.statFnc[GAME] = game;
    al.statFnc[DEAD] = dead;
    al.statFnc[PAUSE] = yeet;
    al.statFnc[EDIT] = editor;
}

function initPlayer(al, pl) {
    pl.mass = PLAYER_MASS;
    pl.power = PLAYER_AERO_POWER;
    pl.powerMult = 1;
    pl.size = PLAYER_SIZE;
    pl.eyez = PLAYER_SIZE - PLAYER_EYE_TOP;
    pl.onGround = true;
    pl.alive = 5;
    pl.dmg = 6;
    if (pl.csec) {
        pl.posz = al.sectors[pl.csec].flHei;
    }
}

function initTrigo(al) {
    al.sin = [];
    al.cos = [];
    for (let i = 0; i < D_2PI; i++) {
        al.sin[i] = Math.sin((Math.PI * 2 * i) / D_2PI);
        al.cos[i] = Math.cos((Math.PI * 2 * i) / D_2PI);
    }
}

function newMob(al, mouseEvent, index) {
    return {
        posx: (mouseEvent.x - WIN_SIZEX / 2) / 10.0,
        posy: (mouseEvent.y - WIN_SIZEY / 2) / -10.0,
        index: index,
        next: null,
    };
}

function initEdit(al) {
    al.winEd = createWindow(WIN_TITLE, WIN_POSX + WIN_SIZEX, WIN_POSY, WIN_EDIT_SIZEX, WIN_EDIT_SIZEY);
    al.surfEd = getWindowSurface(al.winEd);
    al.pixEd = al.surfEd.pixels;
    initTextEdit(al);
}

function createWindow(title, x, y, width, height) {
    return { title, x, y, width, height, shown: true };
}

function getWindowSurface(window) {
    return { pixels: new Uint32Array(window.width * window.height) };
}