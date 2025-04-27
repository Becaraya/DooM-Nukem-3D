function mobOnZ(al, e) {
    e.posz += e.velz * al.dtime / 1000000;

    if (e.velz || e.posz !== al.sec[e.csec].flHei) {
        e.onGround = false;
    } else {
        e.onGround = true;
    }

    if (!e.onGround) {
        e.velz -= al.g * al.dtime / 1000000;

        if (e.posz < al.sec[e.csec].flHei) {
            e.posz = al.sec[e.csec].flHei;
            e.velz = 0;
            e.onGround = true;
        }

        if (e.posz + e.size > al.sec[e.csec].ceHei) {
            e.posz = al.sec[e.csec].ceHei - e.size;
            e.velz = 0;
        }

        if (al.sec[e.csec].ceHei - al.sec[e.csec].flHei < e.size) {
            e.alive = false;
        }
    }
}