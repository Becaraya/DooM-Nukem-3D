function powerToRun(al) {
    return (al.play.mass * al.g * al.play.gdVel) / 6;
}

function jump(al) {
    if (al.play.onGround) {
        al.play.onGround = false;
        al.play.velz += Math.sqrt(al.play.power * al.play.powerMult * 1.5) / 
                        (1.41 * Math.sqrt(al.play.mass));
    }
}