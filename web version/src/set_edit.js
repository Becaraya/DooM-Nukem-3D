function printSpawnEnd(al) {
    const tmpy = al.play.posy * -10 + WIN_SIZEY / 2;
    const tmpx = al.play.posx * 10 + WIN_SIZEX / 2;

    putRectangle(al.sdlSurf, itop(tmpx - 1, tmpy - 1), itop(tmpx + 1, tmpy + 1), RED);

    if (!al.edit.sectEnd) {
        putRectangle(
            al.sdlSurf,
            itop(al.endSect.x - 1, al.endSect.y - 1),
            itop(al.endSect.x + 1, al.endSect.y + 1),
            BLUE
        );
    }
}

function setEdit(al) {
    let x = 0;
    let y = 0;

    al.pix.fill(0);

    while (x < WIN_SIZEX) {
        while (y < WIN_SIZEY) {
            if (x % al.edit.zoom === 0 && y % al.edit.zoom === 0 && y > 0 && x > 0) {
                al.pix[x + y * WIN_SIZEX] = WHITE;
            }
            y++;
        }
        y = 0;
        x++;
    }

    putRectangle(
        al.sdlSurf,
        itop(WIN_SIZEX / 2 - 2, WIN_SIZEY / 2 - 2),
        itop(WIN_SIZEX / 2 + 2, WIN_SIZEY / 2 + 2),
        GREEN
    );

    printSpawnEnd(al);
}

function getHei(al) {
    let tmp = al.sect;
    let t;
    let i = 0;

    freeTextHeiNum(al);

    while (al.edit.indexSect + i++ < al.nbSec) {
        tmp = tmp.next;
    }

    if (al.edit.stat === SET_FLO_HEI) {
        t = dtoaDoom(tmp.flHei);
        setText(
            al.text.flHeiNum,
            tmp.flHei ? t : "0",
            getRect(570, 410),
            addColor(TEXT_EDITOR)
        );
    } else {
        t = dtoaDoom(tmp.ceHei);
        setText(
            al.text.ceHeiNum,
            tmp.ceHei ? t : "0",
            getRect(570, 410),
            addColor(TEXT_EDITOR)
        );
    }

    free(t);
}

function getPlayerStat(al) {
    if (al.edit.stat >= LIFE && al.edit.stat <= MASS) {
        if (al.text.playerValue.str) al.text.playerValue.str = null;

        if (al.edit.stat === LIFE) al.text.playerValue.str = itoa(al.play.alive);
        if (al.edit.stat === POW) al.text.playerValue.str = dtoaDoom(al.play.powerMult);
        if (al.edit.stat === WEAPON) al.text.playerValue.str = itoa(0);
        if (al.edit.stat === SIZE) al.text.playerValue.str = dtoaDoom(al.play.size);
        if (al.edit.stat === MASS) al.text.playerValue.str = dtoaDoom(al.play.mass);
    }
}

function setEditMenu(al) {
    al.pixEd.fill(LIGHT_GREY);

    if (al.sect && al.sect.walls) {
        if (al.edit.stat === SET_FLO_HEI || al.edit.stat === SET_CEL_HEI) {
            getHei(al);
        }
        printCo(al);
    }

    getPlayerStat(al);
    globalMenuRectangle(al);

    if (
        al.edit.stat === EDIT_WALL ||
        al.edit.stat === EDIT_SECT ||
        al.edit.stat === SET_FLO_TEXT ||
        al.edit.stat === SET_FLO_HEI ||
        al.edit.stat === SET_CEL_TEXT ||
        al.edit.stat === SET_CEL_HEI ||
        al.edit.stat === SET_WALL_TEXT
    ) {
        sectWallMenuRectangle(al);

        if (
            (al.ev.motion.windowID === 2 &&
                inr(itop(45, 320), itop(220, 365), itop(al.ev.motion.x, al.ev.motion.y))) ||
            al.edit.stat === SET_FLO_TEXT ||
            al.edit.stat === SET_WALL_TEXT
        ) {
            putRectangle(al.surfEd, itop(45, 320), itop(220, 365), BLACK);
        }
    }

    setEditMenuNext(al);
}