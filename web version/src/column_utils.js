// Adaptation JS des fonctions de column_utils.c

// skybox(al, y, tx): retourne la couleur du pixel de la skybox
function skybox(al, y, tx) {
    // al.tex[0] doit être un objet { size_x, size_y, pix (Array) }
    // al.play.horizon, al.stretch, HORIZON_LIMIT doivent exister
    const HORIZON_LIMIT = al.HORIZON_LIMIT || 0; // à adapter selon votre code
    const ty = Math.floor(al.tex[0].size_y * (y + al.play.horizon + HORIZON_LIMIT) / al.stretch);
    return al.tex[0].pix[ty * al.tex[0].size_x + tx];
}

// tex_find(pix, texx, texy, tex): met à jour pix[0] si la couleur est valide
function tex_find(pix, texx, texy, tex) {
    // tex doit être un objet { size_x, size_y, pix (Array) }
    const color = tex.pix[tex.size_x * texy + texx];
    if ((color >>> 24) !== 0) { // Vérifie si le canal alpha est non nul
        pix[0] = color;
        return 0;
    } else {
        return 1;
    }
}

// cap_int(varObj, lowcap, highcap): borne varObj.value entre lowcap et highcap
function cap_int(varObj, lowcap, highcap) {
    // varObj doit être un objet { value: Number }
    if (varObj.value < lowcap) varObj.value = lowcap;
    if (varObj.value > highcap) varObj.value = highcap;
}

// Export optionnel si besoin d'importer ailleurs
// window.skybox = skybox;
// window.tex_find = tex_find;
// window.cap_int = cap_int;
