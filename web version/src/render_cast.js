function rotateSector(al, secid, angle) {
    const rotsec = al.rotsec[secid];
    const sector = al.sec[secid];
    const play = al.play;

    rotsec.nbWal = sector.nbWal;

    for (let i = 0; i < rotsec.nbWal; i++) {
        const wall = sector.walls[i];
        rotsec.walls[i] = {
            x1: (wall.x1 - play.posx) * al.cos[angle] - (wall.y1 - play.posy) * al.sin[angle],
            y1: (wall.x1 - play.posx) * al.sin[angle] + (wall.y1 - play.posy) * al.cos[angle],
            x2: (wall.x2 - play.posx) * al.cos[angle] - (wall.y2 - play.posy) * al.sin[angle],
            y2: (wall.x2 - play.posx) * al.sin[angle] + (wall.y2 - play.posy) * al.cos[angle],
        };
    }
}

function rotateEntities(al, angle) {
    const play = al.play;

    for (let i = 0; i < al.nbEnt; i++) {
        const entity = al.ent[i];
        const rotent = al.rotent[i];

        rotent.angleToPlayer = Math.atan2(entity.posx - play.posx, entity.posy - play.posy) * D_2PI / Math.PI;
        entity.angleToPlayer = rotent.angleToPlayer;

        rotent.posx = (entity.posx - play.posx) * al.cos[angle] - (entity.posy - play.posy) * al.sin[angle];
        rotent.posy = (entity.posx - play.posx) * al.sin[angle] + (entity.posy - play.posy) * al.cos[angle];
    }
}

function setFloorHeight(hit, sector) {
    hit.flTex = sector.flTex;
    hit.flHei = sector.flHei;
    hit.ceTex = sector.ceTex;
    hit.ceHei = sector.ceHei;
}

function castSector(al, ray, secid, angle) {
    const sector = al.sec[secid];
    const rotsec = al.rotsec[secid];

    setFloorHeight(ray.hits[ray.nbHits], sector);
    rotateSector(al, secid, angle);
    rotateEntities(al, angle);

    ray.min = Infinity;
    ray.minEnt = Infinity;
    ray.hits[ray.nbHits].isEntity = false;

    let entityHits = 0;
    for (let i = 0; i < al.nbEnt; i++) {
        entityHits += testEntityHit(al, ray, al.rotent[i], al.ent[i]);
    }

    let wallHits = 0;
    for (let i = 0; i < rotsec.nbWal; i++) {
        wallHits += testWallHit(al, ray, rotsec.walls[i], sector.walls[i]);
    }

    ray.nbHits++;

    if (entityHits && !wallHits) {
        castSector(al, ray, secid, angle);
    } else if (ray.hits[ray.nbHits - 1].wall.secLnk) {
        castSector(al, ray, ray.hits[ray.nbHits - 1].wall.secLnk, angle);
    }
}

function castRay(al, angle, ray) {
    ray.angle = angle & D_2PIM;
    ray.xfact = al.sin[ray.angle] * UINT16_MAX;
    ray.yfact = al.cos[ray.angle] * UINT16_MAX;

    castSector(al, ray, al.play.csec, ray.angle);
}