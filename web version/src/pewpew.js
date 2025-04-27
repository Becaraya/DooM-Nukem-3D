function piouPiou(al, i, ray) {
    const entity = al.ent[ray.hits[i].ent.index];

    if (entity.alive < 0) {
        entity.alive = 0;
        entity.anim = 0;
    }

    if (entity.alive) {
        entity.velx = 20 * al.sin[al.play.dir];
        entity.vely = 20 * al.cos[al.play.dir];
        if (entity.posz === al.sec[entity.csec].flHei) {
            entity.velz = 2;
        }
    }
}

function pewpew(al) {
    al.fireAnim = 0;

    const ray = { hits: [], nbHits: 0 };
    castRay(al, al.play.dir, ray);

    for (let i = 0; i < ray.nbHits; i++) {
        if (ray.hits[i].isEntity && ray.hits[i].ent.alive) {
            const entity = al.ent[ray.hits[i].ent.index];
            entity.alive -= al.play.dmg;
            piouPiou(al, i, ray);
            return;
        }
    }
}