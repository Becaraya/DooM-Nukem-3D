class Texture {
    constructor(sizeX, sizeY, pixels) {
        this.sizeX = sizeX;
        this.sizeY = sizeY;
        this.pixels = pixels;
    }

    static parse(buffer) {
        const view = new DataView(buffer);
        const sizeX = view.getUint32(0, true);
        const sizeY = view.getUint32(4, true);

        if (!sizeX || !sizeY) {
            throw new Error("Null sized texture");
        }

        const pixelBuffer = buffer.slice(16);
        const pixels = new Int32Array(pixelBuffer);
        return new Texture(sizeX, sizeY, pixels);
    }
}

class TextureParser {
    constructor() {
        this.textures = [];
    }

    parseTextures(buffer) {
        const view = new DataView(buffer);
        const nbTex = view.getUint16(0, true);

        let offset = 16;
        for (let i = 0; i <= nbTex; i++) {
            const textureSize = 16 + view.getUint32(offset, true) * view.getUint32(offset + 4, true) * 4;
            const textureBuffer = buffer.slice(offset, offset + textureSize);
            this.textures.push(Texture.parse(textureBuffer));
            offset += textureSize;
        }
    }
}

// Exemple d'utilisation
const parser = new TextureParser();
const buffer = new ArrayBuffer(1024); // Simule un buffer contenant des textures
parser.parseTextures(buffer);
console.log(parser.textures);