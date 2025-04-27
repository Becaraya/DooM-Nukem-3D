class RaycastRay {
    constructor() {
        this.x = 0;
        this.angle = 0;
        this.xfact = 0;
        this.yfact = 0;
        this.nb_hits = 0;
        this.hits = Array(MAX_HITS).fill(null).map(() => new RaycastHit());
        this.min = 0.0;
        this.minent = 0.0;
    }
}

class TextList {
    constructor() {
        this.t = new Text();
        this.gen_map = new Text();
        this.sect_index = new Text();
        this.wall_index = new Text();
        this.settings = new Text();
        this.wall_para = new Text();
        this.sect_para = new Text();
        this.wall = new Text();
        this.sector = new Text();
        this.tools = new Text();
        this.cancel = new Text();
        this.wall_tex = new Text();
        this.fl_hei = new Text();
        this.ce_hei = new Text();
        this.fl_hei_num = new Text();
        this.ce_hei_num = new Text();
        this.fl_tex = new Text();
        this.ce_tex = new Text();
        this.set_player = new Text();
        this.life = new Text();
        this.power = new Text();
        this.weapon = new Text();
        this.size = new Text();
        this.mass = new Text();
        this.set_spawn = new Text();
        this.set_end = new Text();
        this.set_bad_pig = new Text();
        this.draw = new Text();
        this.del_sect = new Text();
        this.player_value = new Text();
        this.dif_ez = new Text();
        this.dif_ha = new Text();
        this.gravity = new Text();
        this.g_num = new Text();
        this.reset_map = new Text();
        this.reset_player = new Text();
        this.is_door = new Text();
        this.link = new Text();
    }
}