function setEditMenuNextNext(al) {
    const m = itop(al.ev.motion.x, al.ev.motion.y);

    if (
        (al.edit.stat >= SET_PLAYER && al.edit.stat <= MASS) ||
        (al.ev.motion.windowID === 2 && inr(itop(495, 240), itop(645, 285), m))
    ) {
        putRectangle(al.surfEd, itop(495, 240), itop(645, 285), BLACK);
        if (al.edit.stat === LIFE || inr(itop(45, 320), itop(220, 365), m)) {
            putRectangle(al.surfEd, itop(45, 320), itop(220, 365), BLACK);
        }
        if (al.edit.stat === POW || inr(itop(280, 320), itop(460, 365), m)) {
            putRectangle(al.surfEd, itop(280, 320), itop(460, 365), BLACK);
        }
        if (al.edit.stat === WEAPON || inr(itop(495, 320), itop(645, 365), m)) {
            putRectangle(al.surfEd, itop(495, 320), itop(645, 365), BLACK);
        }
        if (al.edit.stat === SIZE || inr(itop(45, 400), itop(220, 445), m)) {
            putRectangle(al.surfEd, itop(45, 400), itop(220, 445), BLACK);
        }
        if (al.edit.stat === MASS || inr(itop(280, 400), itop(460, 445), m)) {
            putRectangle(al.surfEd, itop(280, 400), itop(460, 445), BLACK);
        }
    }
}

function setEditMenuNext(al) {
    const m = itop(al.ev.motion.x, al.ev.motion.y);

    if (
        (al.ev.motion.windowID === 2 && inr(itop(45, 540), itop(220, 585), m)) ||
        al.edit.stat === SET_SPAWN ||
        al.edit.stat === SET_END
    ) {
        putRectangle(al.surfEd, itop(45, 540), itop(220, 585), BLACK);
    }
    if (
        (al.ev.motion.windowID === 2 && inr(itop(280, 540), itop(460, 585), m)) ||
        al.edit.stat === SET_BAD_PIG
    ) {
        putRectangle(al.surfEd, itop(280, 540), itop(460, 585), BLACK);
    }
    if (
        (al.ev.motion.windowID === 2 && inr(itop(495, 540), itop(645, 585), m)) ||
        al.edit.stat === SELECT ||
        al.edit.stat === DRAWING
    ) {
        putRectangle(al.surfEd, itop(495, 540), itop(645, 585), BLACK);
    }
    if (
        (al.ev.motion.windowID === 2 && inr(itop(45, 605), itop(220, 650), m)) ||
        al.edit.stat === LINK_MOD
    ) {
        putRectangle(al.surfEd, itop(45, 605), itop(220, 650), BLACK);
    }
    if (
        (al.ev.motion.windowID === 2 && inr(itop(280, 605), itop(460, 650), m)) ||
        al.edit.stat === GRAVITY
    ) {
        putRectangle(al.surfEd, itop(280, 605), itop(460, 650), BLACK);
    }
    if (
        al.ev.motion.windowID === 2 &&
        inr(itop(280, 655), itop(493, 698), m)
    ) {
        putRectangle(al.surfEd, itop(280, 655), itop(490, 695), BLACK);
    }

    setEditMenuNextNext(al);
}

function globalMenuRectangle(al) {
    const m = itop(al.ev.motion.x, al.ev.motion.y);

    if (al.edit.stat === DRAWING) {
        putRectangle(al.surfEd, itop(590, 15), itop(699, 48), BLACK);
    }
    if (al.ev.motion.windowID === 2) {
        if (inr(itop(45, 125), itop(230, 170), m)) {
            putRectangle(al.surfEd, itop(45, 125), itop(230, 170), BLACK);
        }
        if (inr(itop(280, 125), itop(460, 170), m)) {
            putRectangle(al.surfEd, itop(280, 125), itop(460, 170), BLACK);
        }
        if (inr(itop(495, 125), itop(645, 170), m)) {
            putRectangle(al.surfEd, itop(495, 125), itop(645, 170), BLACK);
        }
    }
    if (
        (al.ev.motion.windowID === 2 && inr(itop(45, 240), itop(220, 285), m)) ||
        al.edit.stat === EDIT_SECT ||
        al.edit.stat === SET_FLO_TEXT ||
        al.edit.stat === SET_FLO_HEI ||
        al.edit.stat === SET_CEL_TEXT ||
        al.edit.stat === SET_CEL_HEI
    ) {
        putRectangle(al.surfEd, itop(45, 240), itop(220, 285), BLACK);
    }
    if (
        (al.ev.motion.windowID === 2 && inr(itop(280, 240), itop(460, 285), m)) ||
        al.edit.stat === EDIT_WALL ||
        al.edit.stat === SET_WALL_TEXT
    ) {
        putRectangle(al.surfEd, itop(280, 240), itop(460, 285), BLACK);
    }
}

function sectWallMenuRectangle(al) {
    const m = itop(al.ev.motion.x, al.ev.motion.y);

    if (al.edit.stat !== SET_WALL_TEXT) {
        if (
            al.edit.stat !== EDIT_WALL &&
            ((al.ev.motion.windowID === 2 && inr(itop(280, 400), itop(460, 445), m)) ||
                al.edit.stat === SET_CEL_HEI)
        ) {
            putRectangle(al.surfEd, itop(280, 400), itop(460, 445), BLACK);
        }
        if (
            al.edit.stat !== EDIT_WALL &&
            ((al.ev.motion.windowID === 2 && inr(itop(280, 320), itop(460, 365), m)) ||
                al.edit.stat === SET_CEL_TEXT)
        ) {
            putRectangle(al.surfEd, itop(280, 320), itop(460, 365), BLACK);
        }
        if (
            al.edit.stat !== EDIT_WALL &&
            ((al.ev.motion.windowID === 2 && inr(itop(45, 400), itop(220, 445), m)) ||
                al.edit.stat === SET_FLO_HEI)
        ) {
            putRectangle(al.surfEd, itop(45, 400), itop(220, 445), BLACK);
        }
        if (inr(itop(495, 320), itop(645, 365), m)) {
            putRectangle(al.surfEd, itop(495, 320), itop(645, 365), BLACK);
        }
    }
}