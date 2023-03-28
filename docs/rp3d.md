# RP3D

This object is used by the user as a factory to create the physics world and other objects.

## Methods

* rp3d.[createPhysicsWorld](#rp3dcreatephysicsworldsettings)(settings) [PhysicsWorld](world.md)
* rp3d.[destroyPhysicsWorld](#rp3ddestroyphysicsworldworld)(world) 
* rp3d.[createBoxShape](#rp3dcreateboxshapeextent)(extent)  [BoxShape](shapes/box_shape.md)
* rp3d.[destroyBoxShape](#rp3ddestroyboxshapeboxshape)(boxShape) 
* rp3d.[createSphereShape](#rp3dcreatesphereshaperadius)(radius) [SphereShape](shapes/sphere_shape.md)
* rp3d.[destroySphereShape](#rp3ddestroysphereshapesphereshape)(sphereShape)
* rp3d.[createCapsuleShape](#rp3dcreatecapsuleshaperadius-height)(radius, height) [CapsuleShape](shapes/capsule_shape.md)
* rp3d.[destroyCapsuleShape](#rp3dcreatecapsuleshaperadius-height)(capsuleShape)
* rp3d.[createPolyhedronMesh](#rp3dcreatepolyhedronmeshvertices-indices-polygonfaces)(vertices, indices, polygonFaces) [PolyhedronMesh](polyhedron_mesh.md)
* rp3d.[createPolyhedronMeshFromMeshVerticesCopy](#rp3dcreatepolyhedronmeshfrommeshverticescopybuffer)(buffer) [PolyhedronMesh](polyhedron_mesh.md)
* rp3d.[destroyPolyhedronMesh](#rp3ddestroypolyhedronmeshpolyhedronmesh)(polyhedronMesh) 
* rp3d.[createConvexMeshShape](#rp3dcreateconvexmeshshapepolyhedronmesh-scaling)(polyhedronMesh, scaling) [ConvexMeshShape](shapes/convex_mesh_shape.md)
* rp3d.[destroyConvexMeshShape](#rp3ddestroyconvexmeshshapeconvexmeshshape)(convexMeshShape)
* rp3d.[createTriangleVertexArray](#rp3dcreatetrianglevertexarrayvertices-indices)(vertices, indices) [TriangleVertexArray](triangle_vertex_array.md)
* rp3d.[createTriangleVertexArrayFromMeshVerticesCopy](#rp3dcreatetrianglevertexarrayfrommeshverticescopybuffer)(buffer) [TriangleVertexArray](triangle_vertex_array.md)
* rp3d.[destroyTriangleVertexArray](#rp3ddestroytrianglevertexarraytrianglearray)(triangleArray) 
* rp3d.[createTriangleMesh](#rp3dcreatetrianglemesh)() [TriangleMesh](triangle_mesh.md)
* rp3d.[destroyTriangleMesh](#rp3ddestroytrianglemeshtrianglemesh)(triangleMesh)
* rp3d.[createConcaveMeshShape](#rp3dcreateconcavemeshshapetrianglemesh-scaling)(triangleMesh, scaling) [ConcaveMeshShape](shapes/concave_mesh_shape.md)
* rp3d.[destroyConcaveMeshShape](#rp3ddestroyconcavemeshshapeconcavemeshshape)(concaveMeshShape)
* rp3d.[createHeightFieldShape](#rp3dcreateheightfieldshapenbgridcolumns-nbgridrows-minheight-maxheight-heightfielddata-datatype-upaxis-integerheightscale-scaling)(nbGridColumns, nbGridRows, minHeight, maxHeight, heightFieldData, dataType, upAxis, integerHeightScale, scaling) [HeightFieldShape](shapes/heightfield_shape.md)
* rp3d.[destroyHeightFieldShape](#rp3ddestroyheightfieldshapeheightfieldshape)(heightFieldShape)
* rp3d.[createAABB](#rp3dcreateaabbmincoordinates-maxcoordinates)(minCoordinates, maxCoordinates) [AABB](aabb.md)
* rp3d.[createBallAndSocketJointInfoLocalSpace](#rp3dcreateballandsocketjointinfolocalspacebody1-body2-anchorpointbody1localspace-anchorpointbody2localspace)(body1, body2, anchorPointBody1LocalSpace, anchorPointBody2LocalSpace) [BallAndSocketJointInfo](joints/ball_and_socket_joint_info.md)
* rp3d.[createBallAndSocketJointInfoWorldSpace](#rp3dcreateballandsocketjointinfoworldspacebody1-body2-initanchorpointworldspace)(body1, body2, initAnchorPointWorldSpace) [BallAndSocketJointInfo](joints/ball_and_socket_joint_info.md)
* rp3d.[createHingeJointInfoLocalSpace](#rp3dcreatehingejointinfolocalspaceb)(body1, body2, anchorPointBody1Local, anchorPointBody2Local, rotationBody1AxisLocal, rotationBody2AxisLocal) [HingeJointInfo](joints/hinge_joint_info.md)
* rp3d.[createHingeJointInfoWorldSpace](#rp3dcreateheigejointinfoworldspacebody1)(body1, body2, initAnchorPointWorldSpace, initRotationAxisWorld) [HingeJointInfo](joints/hinge_joint_info.md)
---
### rp3d.createPhysicsWorld(settings)
Create and return an instance of PhysicsWorld.

**PARAMETERS**
* `settings` ([WorldSetting](world.md#worldsettings))

**RETURN**
* ([PhysicsWorld](world.md))

---
### rp3d.destroyPhysicsWorld(world)
Destroy an instance of PhysicsWorld.

**PARAMETERS**
* `world` ([PhysicsWorld](world.md))

---
### rp3d.createBoxShape(extent)
Create and return a box collision shape.

**PARAMETERS**
* `extent` (vector3)

**RETURN**
* ([BoxShape](shapes/box_shape.md))

---
### rp3d.destroyBoxShape(boxShape)
Destroy a box collision shape.

**PARAMETERS**
* `boxShape` ([BoxShape](shapes/box_shape.md))

---
### rp3d.createSphereShape(radius)
Create and return a sphere collision shape.

**PARAMETERS**
* `radius` (number)

**RETURN**
* ([SphereShape](shapes/sphere_shape.md))

---
### rp3d.destroySphereShape(sphereShape)
Destroy a sphere collision shape.

**PARAMETERS**
* `sphereShape` ([SphereShape](shapes/sphere_shape.md))

---
### rp3d.createCapsuleShape(radius, height)
Create and return a capsule shape.

**PARAMETERS**
* `radius` (number)
* `height` (number)

**RETURN**
* ([CapsuleShape](shapes/capsule_shape.md))

---
### rp3d.destroyCapsuleShape(capsuleShape)
Destroy a capsule collision shape.

**PARAMETERS**
* `capsuleShape` ([CapsuleShape](shapes/capsule_shape.md))

---
### rp3d.createPolyhedronMesh(vertices, indices, polygonFaces)
Create a polyhedron mesh.

**PARAMETERS**
* `vertices` (number[])
* `indices` (number[])
* `polygonFaces` ([PolygonFace](polyhedron_mesh.md#polygonface)[])

**RETURN**
* ([PolyhedronMesh](polyhedron_mesh.md))

---
### rp3d.createPolyhedronMeshFromMeshVerticesCopy(buffer)
Create a polyhedron mesh from mesh vertices

**PARAMETERS**
* `buffer` (buffer)

**RETURN**
* ([PolyhedronMesh](polyhedron_mesh.md))

---
### rp3d.destroyPolyhedronMesh(polyhedronMesh)
Destroy a polyhedron mesh.

**PARAMETERS**
* `polyhedronMesh` ([PolyhedronMesh](polyhedron_mesh.md))

---
### rp3d.createConvexMeshShape(polyhedronMesh, scaling)
Create and return a convex mesh shape.

**PARAMETERS**
* `polyhedronMesh` ([PolyhedronMesh](polyhedron_mesh.md))
* `scaling` (vector|nil) 

**RETURN**
* ([ConvexMeshShape](shapes/convex_mesh_shape.md))

---
### rp3d.destroyConvexMeshShape(convexMeshShape)
Destroy a convex mesh shape.

**PARAMETERS**
* `convexMeshShape` ([ConvexMeshShape](shapes/convex_mesh_shape.md))

---
### rp3d.createTriangleVertexArray(vertices, indices, normals)
Create and return a triangle vertex array.

**PARAMETERS**
* `vertices` (number[])
* `indices` (number[])
* `normals` (number[]|nil)

**RETURN**
* ([TriangleVertexArray](triangle_vertex_array.md))

---
### rp3d.createTriangleVertexArrayFromMeshVerticesCopy(buffer)
Create and return a triangle vertex array from mesh vertices.

**PARAMETERS**
* `buffer` (buffer)

**RETURN**
* ([TriangleVertexArray](triangle_vertex_array.md))

---
### rp3d.destroyTriangleVertexArray(triangleArray)
Destroy a triangle vertex array.

**PARAMETERS**
* `triangleArray` ([TriangleVertexArray](triangle_vertex_array.md))

---
### rp3d.createTriangleMesh() 
Create a triangle mesh.

**RETURN**
* ([TriangleMesh](triangle_mesh.md))

---
### rp3d.destroyTriangleMesh(triangleMesh)
Destroy a triangle mesh. 

**PARAMETERS**
* `triangleMesh` ([TriangleMesh](triangle_mesh.md))

---
### rp3d.createConcaveMeshShape(triangleMesh, scaling)
Create and return a concave mesh shape.

**PARAMETERS**
* `triangleMesh` ([TriangleMesh](triangle_mesh.md))
* `scaling` (vector3|nil)

**RETURN**
* ([ConcaveMeshShape](shapes/concave_mesh_shape.md))

---
### rp3d.destroyConcaveMeshShape(concaveMeshShape)
Destroy a concave mesh shape.

**PARAMETERS**
* `concaveMeshShape` ([ConcaveMeshShape](shapes/concave_mesh_shape.md))

---
### rp3d.createHeightFieldShape(nbGridColumns, nbGridRows, minHeight, maxHeight, heightFieldData, dataType, upAxis, integerHeightScale, scaling)
Create and return a height-field shape.

**PARAMETERS**
* `nbGridColumns` (number)
* `nbGridRows` (number)
* `minHeight` (number)
* `maxHeight` (number)
* `heightFieldData` (number[])
* `dataType` ([HeightDataType](#rp3dheightdatatype))
* `upAxis` (number|nil) representing the up axis direction (0 for x, 1 for y and 2 for z)
* `integerHeightScale` (number|nil)
* `scaling ` (vector3)

**RETURN**
* ([HeightFieldShape](shapes/heightfield_shape.md))

---
### rp3d.destroyHeightFieldShape(heightFieldShape)
Destroy a height-field shape. 

**PARAMETERS**
* `heightFieldShape` ([HeightFieldShape](shapes/heightfield_shape.md))

---
### rp3d.createAABB(minCoordinates, maxCoordinates)
Create and return a AABB

**PARAMETERS**
* `minCoordinates` (vector3)
* `maxCoordinates` (vector3)

**RETURN**
* ([AABB](aabb.md))

---
### rp3d.createBallAndSocketJointInfoLocalSpace(body1, body2, anchorPointBody1LocalSpace, anchorPointBody2LocalSpace)
Create BallAndSocketJointInfo

**PARAMETERS**
* `body1` ([RigidBody](rigid_body.md))
* `body2` ([RigidBody](rigid_body.md))
* `anchorPointBody1LocalSpace` (vector3)
* `anchorPointBody2LocalSpace` (vector3)

**RETURN**
* ([BallAndSocketJointInfo](joints/ball_and_socket_joint_info.md))

---
### rp3d.createBallAndSocketJointInfoWorldSpace(body1, body2, initAnchorPointWorldSpace)
Create BallAndSocketJointInfo

**PARAMETERS**
* `body1` ([RigidBody](rigid_body.md))
* `body2` ([RigidBody](rigid_body.md))
* `initAnchorPointWorldSpace` (vector3)

**RETURN**
* ([BallAndSocketJointInfo](joints/ball_and_socket_joint_info.md))

---
### rp3d.createHingeJointInfoLocalSpace(body1, body2, anchorPointBody1Local, anchorPointBody2Local, rotationBody1AxisLocal, rotationBody2AxisLocal)
Create HingeJointInfo

**PARAMETERS**
* `body1` ([RigidBody](rigid_body.md))
* `body2` ([RigidBody](rigid_body.md))
* `anchorPointBody1Local` (vector3)
* `anchorPointBody2Local` (vector3)
* `rotationBody1AxisLocal` (vector3)
* `rotationBody2AxisLocal` (vector3)

**RETURN**
* ([HingeJointInfo](joints/hinge_joint_info.md))

---
### rp3d.createHingeJointInfoWorldSpace(body1, body2, initAnchorPointWorldSpace, initRotationAxisWorld)
Create HingeJointInfo

**PARAMETERS**
* `body1` ([RigidBody](rigid_body.md))
* `body2` ([RigidBody](rigid_body.md))
* `initAnchorPointWorldSpace` (vector3)
* `initRotationAxisWorld` (vector3)

**RETURN**
* ([HingeJointInfo](joints/hinge_joint_info.md))

## Enums

### rp3d.CollisionShapeName

```lua
rp3d.CollisionShapeName = {
	TRIANGLE = "TRIANGLE",
	SPHERE = "SPHERE",
	CAPSULE = "CAPSULE",
	BOX = "BOX",
	CONVEX_MESH = "CONVEX_MESH",
	TRIANGLE_MESH = "TRIANGLE_MESH",
	HEIGHTFIELD = "HEIGHTFIELD"
}
```

### rp3d.CollisionShapeType

```lua
rp3d.CollisionShapeType = {
	SPHERE = "SPHERE",
	CAPSULE = "CAPSULE",
	CONVEX_POLYHEDRON = "CONVEX_POLYHEDRON",
	CONCAVE_SHAPE = "CONCAVE_SHAPE"
}
```

### rp3d.BodyType

```lua
rp3d.BodyType = {
	STATIC = "STATIC",
	KINEMATIC = "KINEMATIC",
	DYNAMIC = "DYNAMIC"
}
```

### rp3d.DebugRenderer

```lua
rp3d.DebugRenderer = {
	DebugItem = {
		COLLIDER_AABB = "COLLIDER_AABB",
		COLLIDER_BROADPHASE_AABB = "COLLIDER_BROADPHASE_AABB",
		COLLISION_SHAPE = "COLLISION_SHAPE",
		CONTACT_POINT = "CONTACT_POINT",
		CONTACT_NORMAL = "CONTACT_NORMAL"
	},
}
```

### rp3d.OverlapPair

```lua
rp3d.OverlapPair = {
	EventType = {
		OverlapStart = "OverlapStart",
		OverlapStay = "OverlapStay",
		OverlapExit = "OverlapExit"
	},
}

```

### rp3d.ContactPair

```lua
rp3d.ContactPair = {
	EventType = {
		ContactStart = "ContactStart",
		ContactStay = "ContactStay",
		ContactExit = "ContactExit"
	},
}
```

### rp3d.ContactsPositionCorrectionTechnique

```lua
rp3d.ContactsPositionCorrectionTechnique = {
	BAUMGARTE_CONTACTS = "BAUMGARTE_CONTACTS",
	SPLIT_IMPULSES = "SPLIT_IMPULSES",
}
```

### rp3d.TriangleRaycastSide

```lua
rp3d.TriangleRaycastSide = {
	FRONT = "FRONT",
	BACK = "BACK",
	FRONT_AND_BACK = "FRONT_AND_BACK"
}
```

### rp3d.HeightDataType

```lua
rp3d.HeightDataType = {
	HEIGHT_FLOAT_TYPE = "HEIGHT_FLOAT_TYPE",
	HEIGHT_DOUBLE_TYPE = "HEIGHT_DOUBLE_TYPE",
	HEIGHT_INT_TYPE = "HEIGHT_INT_TYPE"
}
```

### rp3d.JointType

```lua
rp3d.JointType = {
    BALLSOCKETJOINT  = "BALLSOCKETJOINT",
	SLIDERJOINT  = "SLIDERJOINT",
	HINGEJOINT  = "HINGEJOINT",
	FIXEDJOINT   = "FIXEDJOINT"
}
```

### rp3d.JointsPositionCorrectionTechnique

```lua
rp3d.JointsPositionCorrectionTechnique = {
	BAUMGARTE_JOINTS  = "BAUMGARTE_JOINTS",
	NON_LINEAR_GAUSS_SEIDEL  = "NON_LINEAR_GAUSS_SEIDEL",
}
```