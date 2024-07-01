# Object Syntax
- There is one object per line, values are separated by spaces and/or tabs
- All RGB colors are in integer values between 0 and 255
- Three dimensional Vectors (V3), consist of either integers or floats for x, y and z
- Lines starting with `#` are treated as comments and ignored during parsing
- optional fields will be filled with default values if not provided
- Paths and Names have a maximum length of 50 characters


## Camera & Lights
### Camera (only once per scene)
| **Identifier** | **View Point V3** | **Orientation V3 (Normalized)** | **FOV (1-180)** | **Samples for Anti Aliasing** (optional) | **Bounces (Reflection)** (optional) | **Threads (1-32)** (optional) |
|----------------|-------------------|---------------------------------|-----------------|------------------------------------------|-------------------------------------|-------------------------------|
| C              | -50.0,0,20        | 0,0,1                           | 70              | 100                                      | 4                                   | 8                             |

### Ambient Light (only once per scene)
| **Identifier** | **Ambient Lighting Ratio** | **RGB Colors** |
|----------------|----------------------------|----------------|
| C              | 0.2                        | 255,255,255    |

### Light
| **Identifier** | **Position V3** | **Intensity** | **RGB Colors** |
|----------------|-----------------|---------------|----------------|
| L              | -40.0,50.0,0.0  | 0.6           | 10,0,255       |

## Objects
> [!NOTE]
> Material and Texture Names are optional and can be used with any object. If a material or texture is provided, the RGB colors will be ignored.
> If you want to use a texture, you have to provide a material name as well.

### Sphere
| **Identifier** | **Center V3** | **Diameter** | **RGB Colors** | **Material Name** (optional) | **Texture Name** (optional) |
|----------------|---------------|--------------|----------------|------------------------------|-----------------------------|
| sp             | 0.0,0.0,20.60   | 12.6       | 10,0,255       | Advanced                     | Checkerboard                |

### Plane
| **Identifier** | **Point V3** | **Normal V3** | **RGB Colors** | **Material Name** (optional) | **Texture Name** (optional) |
|----------------|--------------|---------------|----------------|------------------------------|-----------------------------|
| pl             | 0.0,0.0,-10  | 0,1,0         | 0,0,255        | Default                      | UVCheckerboard              |

### Cylinder
| **Identifier** | **Center V3** | **Normal V3** | **Radius** | **Height** | **RGB Colors** | **Material Name** (optional) | **Texture Name** (optional) |
|----------------|---------------|---------------|------------|------------|----------------|------------------------------|-----------------------------|
| cy             | 50.0,0.0,20.6 | 0,0,1.0       | 14.2       | 21.42      | 10,0,255       |                              |                             |

### Cone
| **Identifier** | **Center V3** | **Normal V3** | Radius    | Height      | **RGB Colors** | **Material Name** (optional) | **Texture Name** (optional)|
|----------------|---------------|---------------|-----------|------------|----------------|------------------------------|-----------------------------|
| co             | 50.0,0.0,20.6 | 0,0,1.0       | 14.2      | 21.42      | 10,0,255       |                              |                             |

### Triangle
| **Identifier** | **Vertex 1 V3** | **Vertex 2 V3** | **Vertex 3 V3** | **RGB Colors** | **Material Name** (optional) | **Texture Name** (optional) |
|----------------|-----------------|-----------------|-----------------|----------------|------------------------------|-----------------------------|
| tr             | 50.0,0.0,20.6   | 50.0,0.0,20.6   | 50.0,0.0,20.6   | 10,0,255       |                              |                             |


## Materials
> [!IMPORTANT]
> Material Names are case sensitive and must be unique.

> [!NOTE]
> Materials are optional and can be used with any object. If a material is provided, the RGB colors will be ignored.

### Default Material
| **Identifier** | **Material Name** | **RGB Colors** | **Reflection Ratio** |
|----------------|-------------------|----------------|----------------------|
| M              | Default           | 255,255,255    | 0.0                  |

### Advanced Material
| **Identifier** | **Material Name** | **RGB Colors** | **Reflection Ratio** | **Diffuse Ratio** | **Specular Ratio** | **Shininess** |
|----------------|-------------------|----------------|----------------------|-------------------|--------------------|---------------|
| MA             | Advanced          | 255,255,255    | 0.0                  | 0.8               | 0.2                | 32            |

## Textures
> [!IMPORTANT]
> Texture Names are case sensitive and must be unique.

> [!NOTE]
> Textures are optional and can be used with any object. If a texture is provided, the RGB colors will be ignored.

### External Texture
| **Identifier** | **Texture Name** | **File Path**        |
|----------------|------------------|----------------------|
| TF             | Texture          | textures/texture.jpg |

### Checkerboard Texture 
| **Identifier** | **Texture Name** | **RGB Colors** | **RGB Colors** | **Scale** |
|----------------|------------------|----------------|----------------|-----------|
| TC             | Checkerboard     | 255,255,255    | 0,0,0          | 0.5       |

### UV Checkerboard Texture (looks better on spheres)
| **Identifier** | **Texture Name** | **RGB Colors** | **RGB Colors** | **Scale** |
|----------------|------------------|----------------|----------------|-----------|
| TUC            | UVCheckerboard   | 255,255,255    | 0,0,0          | 0.5       |

## Bump Maps
> [!IMPORTANT]
> Bump Maps are optional and can currently only be used with spheres. (They will be ignored for other objects)

| **Identifier** | **Texture Name** | **File Path**     |
|----------------|------------------|-------------------|
| B              | bump             | textures/bump.jpg |