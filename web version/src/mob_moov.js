function dWall(w, px, py) {
    let a = [];
    let b = [];
    let x, y;

    if (w.x2 - w.x1 === 0) w.x2 += 0.0000001;
    if (w.y2 - w.y1 === 0) w.x2 += 0.0001;

    a[0] = (w.y2 - w.y1) / (w.x2 - w.x1) + 0.001;
    b[0] = w.y2 - a[0] * w.x2 + 0.0001;

    a[1] = -1 / a[0] + 0.0001;
    b[1] = py - a[1] * px + 0.0001;

    x = (b[0] / a[1] - b[1] / a[1]) / (a[1] / a[1] - a[0] / a[1]);
    y = a[0] * x + b[0];

    return Math.sqrt((x - px) ** 2 + (y - py) ** 2);
}

function isCrossX(e, t, v, al) {
    const d = dWall(t, e.posx + v, e.posy);

    if (d < 0.5 && t.isCross) {
        if (
            e.posz + 0.5 < al.sec[t.secLnk].flHei ||
            e.posz + e.size > al.sec[t.secLnk].ceHei ||
            al.sec[t.secLnk].ceHei - al.sec[t.secLnk].flHei < e.size
        ) {
            return false;
        }
        return true;
    }

    return d >= 0.5;
}

function isCrossY(e, t, v, al) {
    const d = dWall(t, e.posx, e.posy + v);

    if (d < 0.5 && t.isCross) {
        if (
            e.posz + 0.5 < al.sec[t.secLnk].flHei ||
            e.posz + e.size > al.sec[t.secLnk].ceHei ||
            al.sec[t.secLnk].ceHei - al.sec[t.secLnk].flHei < e.size
        ) {
            return false;
        }
        return true;
    }

    return d >= 0.5;
}

function wallOk(al, e, t, o) {
    if (
        o.d.x > 0.0 &&
        (t.x1 >= e.posx || t.x2 >= e.posx) &&
        ((t.y1 <= e.posy && e.posy <= t.y2) || (t.y1 >= e.posy && e.posy >= t.y2))
    ) {
        if (!isCrossX(e, t, o.d.x, al)) o.p.x = 0;
    }

    if (
        o.d.x < 0.0 &&
        (t.x1 <= e.posx || t.x2 <= e.posx) &&
        ((t.y1 <= e.posy && e.posy <= t.y2) || (t.y1 >= e.posy && e.posy >= t.y2))
    ) {
        if (!isCrossX(e, t, o.d.x, al)) o.p.x = 0;
    }

    if (
        o.d.y > 0.0 &&
        (t.y1 >= e.posy || t.y2 >= e.posy) &&
        ((t.x1 <= e.posx && e.posx <= t.x2) || (t.x1 >= e.posx && e.posx >= t.x2))
    ) {
        if (!isCrossY(e, t, o.d.y, al)) o.p.y = 0;
    }

    if (
        o.d.y < 0.0 &&
        (t.y1 <= e.posy || t.y2 <= e.posy) &&
        ((t.x1 <= e.posx && e.posx <= t.x2) || (t.x1 >= e.posx && e.posx >= t.x2))
    ) {
        if (!isCrossY(e, t, o.d.y, al)) o.p.y = 0;
    }
}

function ftNop(al, e, x, y) {
    const o = { p: { x: 1, y: 1 }, d: { x, y } };

    accelerationEntities(al, e);

    for (let i = 0; i < al.sec[e.csec].nbWal; i++) {
        wallOk(al, e, al.sec[e.csec].walls[i], o);
    }

    if (o.p.y === 1 && e.vely !== 0 && e.alive) e.posy += y;
    if (o.p.x === 1 && e.velx !== 0 && e.alive) e.posx += x;

    mobOnZ(al, e);
    e.csec = isInSector(al, e.posx, e.posy);
}