class Texture {
    constructor(sizeX, sizeY, pixels) {
        this.sizeX = sizeX; // Largeur de la texture
        this.sizeY = sizeY; // Hauteur de la texture
        this.pixels = pixels; // Tableau des pixels (tableau d'entiers)
    }

    writeToBuffer() {
        // Crée un tableau de bytes pour représenter la texture
        const buffer = new ArrayBuffer(16 + this.sizeX * this.sizeY * 4);
        const view = new DataView(buffer);

        // Écrit la largeur et la hauteur dans les 8 premiers octets
        view.setUint32(0, this.sizeX, true); // Little-endian
        view.setUint32(4, this.sizeY, true);

        // Écrit les pixels à partir du 16e octet
        const pixelOffset = 16;
        this.pixels.forEach((pixel, index) => {
            view.setUint32(pixelOffset + index * 4, pixel, true);
        });

        return buffer;
    }
}

class TextureManager {
    constructor() {
        this.textures = []; // Liste des textures
    }

    addTexture(texture) {
        this.textures.push(texture);
    }

    writeAllToBuffer() {
        // Crée un tableau de bytes pour représenter toutes les textures
        const headerSize = 16;
        const totalSize = this.textures.reduce((sum, tex) => sum + (16 + tex.sizeX * tex.sizeY * 4), headerSize);
        const buffer = new ArrayBuffer(totalSize);
        const view = new DataView(buffer);

        // Écrit le nombre de textures dans les 2 premiers octets
        view.setUint16(0, this.textures.length, true);

        let offset = headerSize;
        this.textures.forEach(texture => {
            const textureBuffer = texture.writeToBuffer();
            new Uint8Array(buffer).set(new Uint8Array(textureBuffer), offset);
            offset += textureBuffer.byteLength;
        });

        return buffer;
    }
}

// Exemple d'utilisation
const texture1 = new Texture(64, 64, new Array(64 * 64).fill(0xFF0000)); // Texture rouge
const texture2 = new Texture(32, 32, new Array(32 * 32).fill(0x00FF00)); // Texture verte

const manager = new TextureManager();
manager.addTexture(texture1);
manager.addTexture(texture2);

const buffer = manager.writeAllToBuffer();
console.log(buffer); // Vous pouvez utiliser ce buffer pour des opérations supplémentaires