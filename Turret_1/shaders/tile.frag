precision mediump float;

uniform sampler2D tileset;       // Атлас тайлов
uniform vec2 tile_size;          // Размер одного тайла (например, 32x32)
uniform vec2 atlas_size;         // Размер всего атласа (например, 256x256)

// Передаём тип тайла через атрибут вершины (в SFML это можно сделать через color.r)

void main() {
    float tileIndex = gl_Color.r * 255.0; // Восстанавливаем тип тайла (0-255)
    vec2 tile_uv = vec2(tileIndex * tile_size.x, 0) / atlas_size;
    gl_FragColor = texture2D(tileset, tile_uv + gl_TexCoord[0].xy);
}