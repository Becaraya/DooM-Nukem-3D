class HMSParser {
    constructor() {
        this.sectors = [];
        this.entities = [];
        this.textures = [];
        this.textureGroups = [];
    }

    initSecTex() {
        this.sectors = [];
        this.textures = [];
    }

    checkLink(sector, wall) {
        for (const secWall of sector.walls) {
            if (
                (secWall.x1 === wall.x1 && secWall.y1 === wall.y1 && secWall.x2 === wall.x2 && secWall.y2 === wall.y2) ||
                (secWall.x1 === wall.x2 && secWall.y1 === wall.y2 && secWall.x2 === wall.x1 && secWall.y2 === wall.y1)
            ) {
                return secWall.secLnk ? false : true;
            }
        }
        return true;
    }

    checkLinks() {
        for (let i = 1; i < this.sectors.length; i++) {
            for (const wall of this.sectors[i].walls) {
                if (wall.secLnk) {
                    const linkedSector = this.sectors[wall.secLnk];
                    if (this.checkLink(linkedSector, wall) || wall.secLnk === i) {
                        throw new Error("Invalid link");
                    }
                }
            }
        }
    }

    parseEntities(buffer) {
        const view = new DataView(buffer);
        const nbEnt = view.getInt32(0, true);
        if (nbEnt === 0) return;

        let offset = 4;
        for (let i = 0; i < nbEnt; i++) {
            const posX = view.getInt32(offset, true) / 100.0;
            const posY = view.getInt32(offset + 4, true) / 100.0;
            this.entities.push({ posX, posY });
            offset += 8;
        }
    }

    parse(buffer) {
        this.initSecTex();

        const view = new DataView(buffer);
        const fileLength = buffer.byteLength;

        let offset = 0;

        // Parse sectors
        const sectorsBuffer = buffer.slice(offset, fileLength); // Simulated sector parsing
        this.sectors = []; // Populate with parsed sectors
        offset += sectorsBuffer.byteLength;

        // Parse entities
        const entitiesBuffer = buffer.slice(offset, fileLength); // Simulated entity parsing
        this.parseEntities(entitiesBuffer);
        offset += entitiesBuffer.byteLength;

        // Parse textures
        const texturesBuffer = buffer.slice(offset, fileLength); // Simulated texture parsing
        this.textures = []; // Populate with parsed textures
        offset += texturesBuffer.byteLength;

        // Parse texture groups
        const textureGroupsBuffer = buffer.slice(offset, fileLength); // Simulated texture group parsing
        this.textureGroups = []; // Populate with parsed texture groups
        offset += textureGroupsBuffer.byteLength;

        if (offset < fileLength) {
            throw new Error("Invalid File (too long)");
        }

        console.log("Parsing success!");
    }
}

// Exemple d'utilisation
const parser = new HMSParser();
const buffer = new ArrayBuffer(1024); // Simule un buffer contenant un fichier .hms
parser.parse(buffer);
console.log(parser);