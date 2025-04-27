function initStatus(al) {
    al.statFnc = [];
    al.statFnc[MENU] = menu;
    al.statFnc[GAME] = game;
    al.statFnc[DEAD] = dead;
    al.statFnc[PAUSE] = yeet;
    al.statFnc[EDIT] = editor;
    al.statFnc[WON] = won;
}

function initPlayer(al, pl) {
    pl.dir = 0;
    pl.horizon = 0;
    pl.mass = PLAYER_MASS;
    pl.power = PLAYER_AERO_POWER;
    pl.powerMult = 1;
    pl.size = PLAYER_SIZE;
    pl.eyez = PLAYER_SIZE - PLAYER_EYE_TOP;
    pl.onGround = true;
    pl.alive = al.hard ? 6 : 10;
    pl.dmg = al.hard ? 4 : 6;
    if (pl.csec) {
        pl.posz = al.sectors[pl.csec].flHei;
    }
}

function launchInit(al, ed) {
    initTextures(al);
    initPlayer(al, al.play);
    initTrigo(al);
    initStatus(al);
    al.fps = 60;
    al.status = ed ? EDIT : GAME;
    al.g = DEFAULT_G;
    al.fov = DEFAULT_FOV;
    al.stretch = WIN_SIZEY + HORIZON_LIMIT * 2;
    al.nbTexGp = 1;
    al.fireAnim = 42000000;
    al.edit = {
        stat: SELECT,
        sectEnd: -1,
        zoom: 10,
        indexSect: al.nbSec,
    };
}

function init(al, str, ed) {
    if (str && hmsParser(al, str)) {
        throw new Error("Parsing failed");
    }
    launchInit(al, ed);
    if (!initSDL(al)) {
        throw new Error("SDL Initialization failed");
    }
    initTtf(al);
    al.texChoice = 0;
    if (al.status === EDIT) {
        if (str) {
            getMap(al);
        }
        initEdit(al);
    } else if (al.status === GAME) {
        setText(al.text.t, "TEXT", getRect(300, 330), addColor(TEXT_EDITOR));
        al.end = isInSector(al, al.endSect.x, al.endSect.y);
    }
    al.k = {};
    if (al.sect) {
        al.edit.indexWall = al.sect.nbWal - 1;
    }
}

function initSDL(al) {
    al.sdlWin = createWindow(WIN_TITLE, WIN_POSX, WIN_POSY, WIN_SIZEX, WIN_SIZEY);
    al.sdlSurf = getWindowSurface(al.sdlWin);
    al.pix = al.sdlSurf.pixels;
    return al.sdlWin && al.sdlSurf;
}

function createWindow(title, x, y, width, height) {
    return { title, x, y, width, height, shown: true };
}

function getWindowSurface(window) {
    return { pixels: new Uint32Array(window.width * window.height) };
}