function isLeft(p0, p1, p2) {
    const d = (p1.y - p0.y) * (p2.x - p1.x) - (p1.x - p0.x) * (p2.y - p1.y);
    if (d === 0) return 0;
    return d > 0 ? 1 : 2;
}

function intersectsCount(v1, v2, p1, p2) {
    const tab = [
        isLeft(v1, v2, p1),
        isLeft(v1, v2, p2),
        isLeft(p1, p2, v1),
        isLeft(p1, p2, v2),
    ];
    return tab[0] !== tab[1] && tab[2] !== tab[3] ? 1 : 0;
}

function inters(sec, point, extreme) {
    let intersections = 0;

    for (let i = 0; i < sec.nbWal; i++) {
        const a = { x: sec.walls[i].x1, y: sec.walls[i].y1 };
        const b = { x: sec.walls[i].x2, y: sec.walls[i].y2 };

        if (intersectsCount(a, b, point, extreme)) {
            intersections++;
        }
    }

    return intersections;
}

function isInSector(al, x, y) {
    const point = { x, y };
    const extreme = { x: MAX_X, y };

    for (let i = 1; i <= al.nbSec; i++) {
        if (inters(al.sec[i], point, extreme) % 2 === 1) {
            return i;
        }
    }

    return 0;
}