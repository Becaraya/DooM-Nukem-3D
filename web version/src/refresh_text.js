function printText(al, text, surf) {
    let tmp = null;
    let title = 0;

    if (al.status === EDIT && (title = titleCmp(al, text)) === 1) {
        al.font.style = "bold";
    }

    tmp = renderText(text.str, text.clr, al.font);
    if (!tmp) {
        yeet(al);
    }

    if (!blitSurface(tmp, surf, text.where)) {
        freeSurface(tmp);
    } else {
        yeet(al);
    }

    if (title) {
        al.font.style = "normal";
    }
}

function textSect(al) {
    if (
        al.edit.stat === EDIT_SECT ||
        al.edit.stat === SET_FLO_TEXT ||
        al.edit.stat === SET_FLO_HEI ||
        al.edit.stat === SET_CEL_TEXT ||
        al.edit.stat === SET_CEL_HEI
    ) {
        if (al.edit.stat === SET_CEL_HEI) {
            printText(al, al.text.ceHeiNum, al.surfEd);
        }
        if (al.edit.stat === SET_FLO_HEI) {
            printText(al, al.text.flHeiNum, al.surfEd);
        }
        printText(al, al.text.flTex, al.surfEd);
        printText(al, al.text.ceTex, al.surfEd);
        printText(al, al.text.flHei, al.surfEd);
        printText(al, al.text.ceHei, al.surfEd);
        printText(al, al.text.isDoor, al.surfEd);
    }
    printText(al, al.text.sectIndex, al.surfEd);
}

function setPlayerText(al) {
    if (al.edit.stat >= SET_PLAYER && al.edit.stat <= MASS) {
        printText(al, al.text.life, al.surfEd);
        printText(al, al.text.power, al.surfEd);
        printText(al, al.text.weapon, al.surfEd);
        printText(al, al.text.size, al.surfEd);
        printText(al, al.text.mass, al.surfEd);
        if (al.edit.stat !== SET_PLAYER) {
            printText(al, al.text.playerValue, al.surfEd);
        }
    }
}

function textDefaultEdit(al) {
    printText(al, al.text.genMap, al.surfEd);
    printText(al, al.text.draw, al.surfEd);
    printText(al, al.text.sector, al.surfEd);
    printText(al, al.text.wall, al.surfEd);
    printText(al, al.text.setPlayer, al.surfEd);
    printText(al, al.text.tools, al.surfEd);
    printText(al, al.text.settings, al.surfEd);
    printText(al, al.text.resetMap, al.surfEd);
    printText(al, al.text.resetPlayer, al.surfEd);
    setPlayerText(al);
}

function text(al) {
    textDefaultEdit(al);

    if (al.hard === 0) {
        printText(al, al.text.difEz, al.surfEd);
    } else {
        printText(al, al.text.difHa, al.surfEd);
    }

    if (al.edit.stat === DRAWING) {
        printText(al, al.text.cancel, al.surfEd);
    }

    if (al.sect) {
        textSect(al);

        if (al.sect.walls) {
            if (al.edit.stat === EDIT_WALL || al.edit.stat === SET_WALL_TEXT) {
                printText(al, al.text.wallTex, al.surfEd);
            }
            if (al.edit.stat === SET_END) {
                printText(al, al.text.setEnd, al.surfEd);
            } else {
                printText(al, al.text.setSpawn, al.surfEd);
            }
            printText(al, al.text.gravity, al.surfEd);
            if (al.edit.stat === GRAVITY) {
                printText(al, al.text.gNum, al.surfEd);
            }
            printText(al, al.text.setBadPig, al.surfEd);
            printText(al, al.text.link, al.surfEd);
            printText(al, al.text.wallIndex, al.surfEd);
        }
    }
}

function renderText(text, color, font) {
    // Simulated text rendering
    return { text, color, font };
}

function blitSurface(src, dest, where) {
    // Simulated blitting
    return true;
}

function freeSurface(surface) {
    // Simulated surface freeing
}