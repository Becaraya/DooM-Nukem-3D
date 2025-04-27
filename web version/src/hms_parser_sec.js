class Wall {
    constructor(x1, y1, x2, y2, wallTex, botTex, topTex, secLnk, isCross = 0) {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
        this.wallTex = wallTex;
        this.botTex = botTex;
        this.topTex = topTex;
        this.secLnk = secLnk;
        this.isCross = isCross;
    }

    static parse(buffer) {
        const view = new DataView(buffer);
        const x1 = view.getInt32(0, true) / 100.0;
        const y1 = view.getInt32(4, true) / 100.0;
        const x2 = view.getInt32(8, true) / 100.0;
        const y2 = view.getInt32(12, true) / 100.0;
        const wallTex = view.getUint16(16, true);
        const botTex = view.getUint16(18, true);
        const topTex = view.getUint16(20, true);
        const secLnk = view.getUint32(24, true);
        const isCross = secLnk ? view.getUint16(22, true) : 0;
        return new Wall(x1, y1, x2, y2, wallTex, botTex, topTex, secLnk, isCross);
    }
}

class Sector {
    constructor(flHei, ceHei, flTex, ceTex, walls) {
        this.flHei = flHei;
        this.ceHei = ceHei;
        this.flTex = flTex;
        this.ceTex = ceTex;
        this.walls = walls;
    }

    static parse(buffer, wallBuffers) {
        const view = new DataView(buffer);
        const flHei = view.getUint32(0, true) / 100.0;
        const ceHei = view.getUint32(4, true) / 100.0;
        const flTex = view.getUint16(8, true);
        const ceTex = view.getUint16(10, true);
        const nbWal = view.getUint32(12, true);

        if (nbWal < 3) throw new Error("Not enough walls");

        const walls = wallBuffers.map(buf => Wall.parse(buf));
        return new Sector(flHei, ceHei, flTex, ceTex, walls);
    }
}

class HMSParser {
    constructor() {
        this.sectors = [];
    }

    parseSectors(buffer, sectorBuffers, wallBuffersPerSector) {
        const view = new DataView(buffer);
        const nbSec = view.getUint32(0, true);
        const csec = view.getUint32(4, true);
        const posx = view.getInt32(8, true) / 100.0;
        const posy = view.getInt32(12, true) / 100.0;
        const door = view.getUint32(16, true);
        const hard = view.getUint32(20, true);
        const endSectX = view.getInt32(24, true);
        const endSectY = view.getInt32(28, true);

        if (!csec || csec > nbSec) throw new Error("Invalid starting sector");

        this.sectors = sectorBuffers.map((sectorBuffer, i) =>
            Sector.parse(sectorBuffer, wallBuffersPerSector[i])
        );
    }
}

// Exemple d'utilisation
const parser = new HMSParser();
const sectorBuffer = new ArrayBuffer(16); // Simule un buffer de secteur
const wallBuffers = [new ArrayBuffer(32), new ArrayBuffer(32), new ArrayBuffer(32)]; // Simule des buffers de murs
const sectorBuffers = [sectorBuffer]; // Simule des buffers de secteurs
parser.parseSectors(new ArrayBuffer(32), sectorBuffers, [wallBuffers]);
console.log(parser.sectors);