function testAlreadyHit(ray, owall) {
    for (let i = 0; i < ray.nbHits; i++) {
        if (!ray.hits[i].isEntity) {
            const hitWall = ray.hits[i].wall;
            if (
                (hitWall.x1 === owall.x1 && hitWall.y1 === owall.y1 && hitWall.x2 === owall.x2 && hitWall.y2 === owall.y2) ||
                (hitWall.x1 === owall.x2 && hitWall.y1 === owall.y2 && hitWall.x2 === owall.x1 && hitWall.y2 === owall.y1)
            ) {
                return true;
            }
        }
    }
    return false;
}

function wallHit(al, ray, wall, owall) {
    const hit = ray.hits[ray.nbHits];
    hit.isEntity = false;
    hit.wallLength = wallLen(owall);
    if (wall.x1 > wall.x2) swapd(wall, "x1", "x2");
    hit.hitTexX = Math.floor((wall.x1 / (wall.x1 - wall.x2)) * wallLen(owall) * UINT16_MAX) % Math.floor((TEX_REPEAT * UINT16_MAX) / TEX_REPEAT);
    hit.wall = { ...owall };
    hit.transparent = owall.wallTex ? false : true;
    hit.tex = al.tex[owall.wallTex];
}

function testHit(al, ray, wall, owall) {
    if ((wall.x1 >= 0 && wall.x2 <= 0) || (wall.x2 >= 0 && wall.x1 <= 0)) {
        const alpha = (wall.x2 - wall.x1) / (wall.y2 - wall.y1 || 1);
        const beta = wall.x1 - wall.y1 * alpha;
        const tmpDst = wall.y2 === wall.y1 ? 0 : -beta / alpha;

        if (tmpDst > 0 && tmpDst < ray.min && !testAlreadyHit(ray, owall)) {
            ray.min = tmpDst;
            ray.hits[ray.nbHits].hitDst = tmpDst * al.cos[subAngle(ray.angle, al.play.dir)];
            wallHit(al, ray, wall, owall);
            return true;
        }
    }
    return false;
}

function testEntityAlreadyHit(ray, oent) {
    for (let i = 0; i < ray.nbHits; i++) {
        if (ray.hits[i].isEntity) {
            const hitEnt = ray.hits[i].ent;
            if (hitEnt.posx === oent.posx && hitEnt.posy === oent.posy && hitEnt.posz === oent.posz) {
                return true;
            }
        }
    }
    return false;
}

function testEntityHit(al, ray, rotent, oent) {
    if (rotent.posx < oent.width / 2 && rotent.posx > -oent.width / 2) {
        if (rotent.posy > 0 && rotent.posy < ray.min && rotent.posy < ray.minEnt && !testEntityAlreadyHit(ray, oent)) {
            ray.minEnt = rotent.posy;
            ray.min = rotent.posy;
            const hit = ray.hits[ray.nbHits];
            hit.isEntity = true;
            hit.wallLength = oent.width;
            hit.hitDst = rotent.posy * al.cos[subAngle(rotent.angleToPlayer, al.play.dir)];
            hit.ent = { ...oent };
            hit.tex = findEntityTexture(al, oent);
            hit.hitTexX = ((oent.width / 2 - rotent.posx) * hit.tex.sizeX) / oent.width;
            return true;
        }
    }
    return false;
}

function wallLen(wall) {
    return Math.sqrt((wall.x2 - wall.x1) ** 2 + (wall.y2 - wall.y1) ** 2);
}

function swapd(obj, key1, key2) {
    const temp = obj[key1];
    obj[key1] = obj[key2];
    obj[key2] = temp;
}

function subAngle(angle1, angle2) {
    return (angle1 - angle2 + D_2PI) % D_2PI;
}

function findEntityTexture(al, entity) {
    // Simulated function to find the texture of an entity
    return al.tex[entity.texIndex];
}