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

function isCrossX(player, wall, v, al) {
    const d = dWall(wall, player.posx + v, player.posy);

    if (wall.isCross && d < GRO) {
        if (
            player.posz + 0.5 < al.sec[wall.secLnk].flHei ||
            player.posz + player.size > al.sec[wall.secLnk].ceHei ||
            al.sec[wall.secLnk].ceHei - al.sec[wall.secLnk].flHei < player.size
        ) {
            return false;
        }
        return true;
    }

    return d >= GRO;
}

function isCrossY(player, wall, v, al) {
    const d = dWall(wall, player.posx, player.posy + v);

    if (wall.isCross && d < GRO) {
        if (
            player.posz + 0.5 < al.sec[wall.secLnk].flHei ||
            player.posz + player.size > al.sec[wall.secLnk].ceHei ||
            al.sec[wall.secLnk].ceHei - al.sec[wall.secLnk].flHei < player.size
        ) {
            return false;
        }
        return true;
    }

    return d >= GRO;
}

function wallOk(al, wall, p, m) {
    const player = al.play;

    if (
        p.x > 0.0 &&
        (wall.x1 >= player.posx + p.x || wall.x2 >= player.posx + p.x) &&
        ((wall.y1 <= player.posy && player.posy <= wall.y2) ||
            (wall.y1 >= player.posy && player.posy >= wall.y2))
    ) {
        if (!isCrossX(player, wall, p.x, al)) m.x = 0;
    }

    if (
        p.x < 0.0 &&
        (wall.x1 <= player.posx + p.x || wall.x2 <= player.posx + p.x) &&
        ((wall.y1 <= player.posy && player.posy <= wall.y2) ||
            (wall.y1 >= player.posy && player.posy >= wall.y2))
    ) {
        if (!isCrossX(player, wall, p.x, al)) m.x = 0;
    }

    if (
        p.y > 0.0 &&
        (wall.y1 >= player.posy + p.y || wall.y2 >= player.posy + p.y) &&
        ((wall.x1 <= player.posx + p.x && player.posx + p.x <= wall.x2) ||
            (wall.x1 >= player.posx + p.x && player.posx + p.x >= wall.x2))
    ) {
        if (!isCrossY(player, wall, p.y, al)) m.y = 0;
    }

    if (
        p.y < 0.0 &&
        (wall.y1 <= player.posy + p.y || wall.y2 <= player.posy + p.y) &&
        ((wall.x1 <= player.posx + p.x && player.posx + p.x <= wall.x2) ||
            (wall.x1 >= player.posx + p.x && player.posx + p.x >= wall.x2))
    ) {
        if (!isCrossY(player, wall, p.y, al)) m.y = 0;
    }
}

function ftNopPlayer(al, i, x, y) {
    const m = { x: 1, y: 1 };
    const p = { x, y };

    while (i < al.sec[al.play.csec].nbWal) {
        const wall = al.sec[al.play.csec].walls[i];
        wallOk(al, wall, p, m);
        i++;
    }

    if (m.y === 1) al.play.posy += y;
    if (m.x === 1) al.play.posx += x;

    al.play.csec = isInSector(al, al.play.posx, al.play.posy);

    if (!al.play.csec || (al.end && al.play.csec === al.end)) {
        al.play.won = 1;
    }

    al.play.onGround = 0;
}