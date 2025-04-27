function heeeet(al) {
    const tmp = al.hard ? 3 : 2;
    al.play.alive -= (al.play.alive - tmp < 0) ? al.play.alive : tmp;
}

function accelerationEntities(al, mob) {
    mob.velx = (mob.posx < al.play.posx) ? 0.8 : -0.8;
    mob.vely = (mob.posy < al.play.posy) ? 0.8 : -0.8;

    const d = ((mob.posx - al.play.posx) ** 2 + (mob.posy - al.play.posy) ** 2);

    if (d < 2.8 && mob.alive !== 0 &&
        mob.posz + mob.size >= al.play.posz &&
        mob.posz <= al.play.posz + al.play.size) {
        
        al.play.velz = (d <= 2) ? 0 : 2.5;
        al.play.velx = (mob.posx < al.play.posx) ? 2.5 : -2.5;
        al.play.vely = (mob.posy < al.play.posy) ? 2.5 : -2.5;

        mob.velx = (mob.posx < al.play.posx) ? -2.5 : 2.5;
        mob.vely = (mob.posy < al.play.posy) ? -2.5 : 2.5;

        mob.velx = (d < 2.5) ? 0 : mob.velx;
        mob.vely = (d < 2.5) ? 0 : mob.vely;

        if (mob.hit) {
            heeeet(al);
        }
        mob.hit = 0;
    } else {
        mob.hit = 1;
    }
}