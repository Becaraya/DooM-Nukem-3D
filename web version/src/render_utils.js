function dAtan2(d1, d2) {
    let angle = Math.atan2(d1, d2);
    return angle < 0 ? D_2PI + angle : angle * D_2PI / Math.PI;
}

function dAtan(a) {
    let angle = Math.atan(a);
    return angle < 0 ? D_2PI + angle : angle * D_2PI / Math.PI;
}

function swapd(d1, d2) {
    const tmp = d1.value;
    d1.value = d2.value;
    d2.value = tmp;
}

function wallLen(wall) {
    const dx = wall.x2 - wall.x1;
    const dy = wall.y2 - wall.y1;
    return Math.sqrt(dx * dx + dy * dy);
}

function findEntityTexture(al, entity) {
    let texture = {};
    if (entity.alive) {
        texture.sizeX = al.texgp[0].sizeX;
        texture.sizeY = al.texgp[0].sizeY;
        const orientationIndex = Math.floor((subAngle(entity.angleToPlayer + D_PI_4 / 2, entity.dir)) / D_PI_4);
        texture.pix = al.texgp[0].or[orientationIndex].pix[Math.floor(al.anim / 16384)];
    } else {
        let frame = Math.floor(entity.anim / 65000);
        frame = frame > 7 ? 7 : frame;
        texture = al.mobDeath[frame];
    }
    return texture;
}

function subAngle(angle1, angle2) {
    return (angle1 - angle2 + D_2PI) % D_2PI;
}