# HalfEdgeStructure
```lua
---@class Rp3dHalfEdgeStructureFace
---@field edgeIndex number
---@field faceVertices number[]
local Rp3dHalfEdgeStructureFace = {}

---@class Rp3dHalfEdgeStructureVertex
---@field edgeIndex number
---@field vertexPointIndex number
local Rp3dHalfEdgeStructureVertex = {}

---@class Rp3dHalfEdgeStructureEdge
---@field vertexIndex number
---@field twinEdgeIndex number
---@field faceIndex number
---@field nextEdgeIndex number
local Rp3dHalfEdgeStructureEdge = {}
```