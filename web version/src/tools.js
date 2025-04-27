function rotate(al) {
    if (al.k.left) {
        al.play.dir = subAngle(al.play.dir, (LOOK_SENS * D_2PI / 2500) * al.dtime / 1000000);
    }
    if (al.k.righ) {
        al.play.dir = addAngle(al.play.dir, (LOOK_SENS * D_2PI / 2500) * al.dtime / 1000000);
    }
    if (al.k.up) {
        al.play.horizon -= LOOK_SENS * al.dtime / 1000000;
    }
    if (al.k.down) {
        al.play.horizon += LOOK_SENS * al.dtime / 1000000;
    }
    if (al.play.horizon < -HORIZON_LIMIT) {
        al.play.horizon = -HORIZON_LIMIT;
    }
    if (al.play.horizon > HORIZON_LIMIT) {
        al.play.horizon = HORIZON_LIMIT;
    }
}

function itop(x, y) {
    return { x, y };
}

function inr(srcA, srcB, cmp) {
    return srcA.x < cmp.x && srcA.y < cmp.y && srcB.x > cmp.x && srcB.y > cmp.y ? 1 : 0;
}

function nbWall(al) {
    let tmpS = al.sect;
    let i = 0;

    while (al.nbSec - i > al.edit.indexSect) {
        tmpS = tmpS.next;
        i++;
    }

    return tmpS ? tmpS.nbWal : 0;
}

function coCmp(p1, p2) {
    return p1.x === p2.x && p1.y === p2.y ? 1 : 0;
}

function subAngle(angle1, angle2) {
    return (angle1 - angle2 + D_2PI) % D_2PI;
}

function addAngle(angle1, angle2) {
    return (angle1 + angle2) % D_2PI;
}