# HeightFieldShape
HeightFieldShape extends [ConcaveShape](concave_shape.md)

This class represents a static height field that can be used to represent a terrain.

The height field is made of a grid with rows and columns with a height value at each grid point.

The height values can be of type integer, float or double.

When creating a HeightFieldShape, you need to specify the minimum and maximum height value of your height field. Note that the HeightFieldShape will be re-centered based on its AABB. It means that for instance, if the minimum height value is -200 and the maximum value is 400, the final minimum height of the field in the simulation will be -300 and the maximum height will be 300

<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/shapes/img/heightfield_shape_classes.png">

## Create
```lua
local columns = 3
local rows = 3
local min = -1
local max = 1
local data = {
	-1,0,-1,
	0,1,0,
	-1,0,-1,
}
local shape = rp3d.createHeightFieldShape(columns, rows, min, max, data, rp3d.HeightDataType.HEIGHT_FLOAT_TYPE)
```

## Methods

* HeightFieldShape:[getNbRows](#heightfieldshapegetnbrows)() number
* HeightFieldShape:[getNbColumns](#heightfieldshapegetnbcolumns)() number
* HeightFieldShape:[getVertexAt](#heightfieldshapegetvertexatxy)(x,y) vector3
* HeightFieldShape:[getHeightAt](#heightfieldshapegetheightatxy)(x,y) number
* HeightFieldShape:[getHeightDataType](#heightfieldshapegetheightdatatype)()  [rp3d.HeightDataType](../rp3d.md#rp3dheightdatatype)

---
### HeightFieldShape:getNbRows()
Return the number of rows in the height field. 

**RETURN**
* (number)

---
### HeightFieldShape:getNbColumns()
Return the number of columns in the height field.

**RETURN**
* (number)

---
### HeightFieldShape:getVertexAt(x,y)
Return the vertex (local-coordinates) of the height field at a given (x,y) position.

**PARAMETERS**
* `x` (number)
* `y` (number)

**RETURN**
* (vector3)

---
### HeightFieldShape:getHeightAt(x,y)
Return the height of a given (x,y) point in the height field. 

**PARAMETERS**
* `x` (number)
* `y` (number)

**RETURN**
* (number)

---
### HeightFieldShape:getHeightDataType()
Return the type of height value in the height field.

HEIGHT_FLOAT_TYPE, HEIGHT_DOUBLE_TYPE, HEIGHT_INT_TYPE
 
**RETURN**
* ([rp3d.HeightDataType](../rp3d.md#rp3dheightdatatype))
