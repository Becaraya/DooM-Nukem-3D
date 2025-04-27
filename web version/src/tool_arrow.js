function setSizeArrow(al, i) {
    if (i === 1 && al.play.size === 1.78) {
        al.play.size = 1.80;
        al.play.eyez = 1.65;
    } else if (i === 1) {
        al.play.size += 0.05;
        al.play.eyez += 0.05;
    } else if (i === -1 && al.play.size === 1.78) {
        al.play.size = 1.75;
        al.play.eyez = 1.60;
    } else {
        al.play.size -= 0.05;
        al.play.eyez -= 0.05;
    }
}

function arrowStatPlayerMinus(al) {
    if (al.edit.stat === LIFE && al.play.alive > 2) {
        al.play.alive--;
    }
    if (al.edit.stat === POW && al.play.powerMult > 0.2) {
        al.play.powerMult -= 0.1;
    }
    if (al.edit.stat === SIZE && al.play.size > 0.3) {
        setSizeArrow(al, -1);
    }
    if (al.edit.stat === MASS && al.play.mass > 20 && al.play.mass !== 67) {
        al.play.mass -= 10;
    }
    if (al.edit.stat === MASS && al.play.mass === 67) {
        al.play.mass = 60;
    }
}

function arrowStatPlayerPlus(al) {
    if (al.edit.stat === LIFE && al.play.alive < 25) {
        al.play.alive++;
    }
    if (al.edit.stat === POW) {
        al.play.powerMult += 0.1;
    }
    if (al.edit.stat === SIZE) {
        setSizeArrow(al, 1);
    }
    if (al.edit.stat === MASS && al.play.mass !== 67) {
        al.play.mass += 10;
    }
    if (al.edit.stat === MASS && al.play.mass === 67) {
        al.play.mass = 70;
    }
}