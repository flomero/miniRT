# Object Syntax
- There is one object per line, values are separated by spaces and/or tabs
- All RGB colors are in integer values between 0 and 255
- Three dimensional Vectors (V3), consist of either integers or floats for x, y and z
- Lines starting with `#` are treated as comments and ignored during parsing
- optional fields will be filled with default values if not provided

## Camera (only once per scene)
| **Identifier** | **View Point V3** | **Orientation V3 (Normalized)** | **FOV (1-180)** | **Samples for Anti Aliasing** (optional) | **Bounces (Reflection)** (optional) | **Threads (1-32)** (optional) |
|----------------|-------------------|---------------------------------|-----------------|-------------------------------|--------------------------|---------------------|
| C              | -50.0,0,20        | 0,0,1                           | 70              | 100                           | 4                        | 8                   |

## Ambient Light (only once per scene)
| **Identifier** | **Ambient Lighting Ratio** | **RGB Colors** |
|----------------|----------------------------|----------------|
| C              | 0.2                        | 255,255,255    |

## Light
| **Identifier** | **Position V3** | **Intensity** | **RGB Colors** |
|----------------|-----------------|---------------|----------------|
| L              | -40.0,50.0,0.0  | 0.6           | 10,0,255       |

## Sphere
| **Identifier** | **Center V3** | **Diameter** | **RGB Colors** | **Reflection Ratio** |
|----------------|---------------|------------|----------------|----------------------|
| sp             | 0.0,0.0,20.60   | 12.6       | 10,0,255        | 0.5                  |

## Plane
| **Identifier** | **Point V3** | **Normal V3** | **RGB Colors** (optional) | **Reflection Ratio** (optional) |
|----------------|--------------|---------------|----------------|----------------------|
| pl             | 0.0,0.0,-10  | 0,1,0         | 0,0,255        | 0.0                  |

## Cylinder
| **Identifier** | **Center V3** | **Normal V3** | **Radius** | **Height** | **RGB Colors** | **Reflection Ratio** |
|----------------|---------------|---------------|------------|------------|----------------|----------------------|
| cy             | 50.0,0.0,20.6 | 0,0,1.0         | 14.2        | 21.42       | 10,0,255        | 0.0                  |