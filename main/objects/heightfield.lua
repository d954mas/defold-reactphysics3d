local CLASS = require "libs.middleclass"
local PERLIN = require "libs.perlin"

local PhysObject = require "main.objects.physics_object"

local NB_POINTS_WIDTH = 100;
local NB_POINTS_LENGTH = 100;

---@class GameHeightField:GamePhysObject
local HeightField = CLASS.class("HeightField", PhysObject)

---@param world Rp3dPhysicsWorld
function HeightField:initialize(rigid_body, world)
	PhysObject.initialize(self, world)
	self.rigid_body = rigid_body

	self:generateHeightField()
	self:generateGraphicsMesh()

	local transform_identity = {
		position = vmath.vector3(),
		quat = vmath.quat()
	}
	if (rigid_body) then
		self.body = world:createRigidBody(transform_identity);
		self.collider = self.body:addCollider(self.shape, transform_identity);
		self.body:updateMassPropertiesFromColliders();
	else
		self.body = world:createCollisionBody(transform_identity);
		self.collider = self.body:addCollider(self.shape, transform_identity);
	end
	self.body:setUserData(self)
end

function HeightField:generateHeightField()
	self.heightfield = {}
	local min = 0
	local max = 0
	local width = (NB_POINTS_WIDTH - 1);
	local length = (NB_POINTS_LENGTH - 1);
	local persistence = 9;
	local frequency = 0.28;
	local amplitude = 12;
	local octaves = 1;
	local randomseed = 23;
	local perlinNoise = PERLIN(persistence, frequency, amplitude, octaves, randomseed);

	for i = 0, NB_POINTS_WIDTH - 1 do
		for j = 0, NB_POINTS_LENGTH - 1 do
			local arrayIndex = j * NB_POINTS_WIDTH + i;
			local h = perlinNoise:GetHeight(-width * 0.5 + i, -length * 0.5 + j)

			if (i == 0 and j == 0) then
				min = h
				max = h
			end

			min = math.min(min, h)
			max = math.max(max, h)
			self.heightfield[arrayIndex + 1] = h
		end
	end
	self.mMaxHeight = max
	self.mMinHeight = min
	self.shape = rp3d.createHeightFieldShape(NB_POINTS_WIDTH, NB_POINTS_LENGTH, min, max, self.heightfield, rp3d.HeightDataType.HEIGHT_FLOAT_TYPE)
end

function HeightField:generateGraphicsMesh()
	local vertexId = 0;
	self.mVertices = {}
	local mIndicesId = 0
	self.mIndices = {}

	for i = 0, NB_POINTS_WIDTH - 1 do
		for j = 0, NB_POINTS_LENGTH - 1 do
			local originHeight = -(self.mMaxHeight - self.mMinHeight) * 0.5 - self.mMinHeight;
			local height = originHeight + self.heightfield[j * NB_POINTS_WIDTH + i + 1];
			local vertex = vmath.vector3(-(NB_POINTS_WIDTH - 1) * 0.5 + i, height, -(NB_POINTS_LENGTH - 1) * 0.5 + j)
			self.mVertices[vertexId] = vertex
			if ((i < NB_POINTS_WIDTH - 1) and (j < NB_POINTS_LENGTH - 1)) then
				local v1 = vertexId;
				local v2 = vertexId + 1;
				local v3 = vertexId + NB_POINTS_LENGTH;
				local v4 = vertexId + NB_POINTS_LENGTH + 1;

				-- First triangle
				self.mIndices[mIndicesId]= v1
				mIndicesId = mIndicesId + 1
				self.mIndices[mIndicesId]= v2
				mIndicesId = mIndicesId + 1
				self.mIndices[mIndicesId]= v3
				mIndicesId = mIndicesId + 1
				-- Second triangle
				self.mIndices[mIndicesId]= v2
				mIndicesId = mIndicesId + 1
				self.mIndices[mIndicesId]= v4
				mIndicesId = mIndicesId + 1
				self.mIndices[mIndicesId]= v3
				mIndicesId = mIndicesId + 1
			end
			vertexId = vertexId + 1
		end
	end

	self:calculateNormals()
end

function HeightField:calculateNormals()
	self.mNormals = {}
	for i=0,#self.mVertices do
		self.mNormals[i] = vmath.vector3(0)
	end


	local getVertexIndexInFace = function(faceIndex, i)
		return self.mIndices[faceIndex*3 + i]
	end
	for i=0,(#self.mIndices+1)/3-1 do
		-- Get the three vertices index of the current face
		local v1 = getVertexIndexInFace(i, 0);
		local v2 = getVertexIndexInFace(i, 1);
		local v3 = getVertexIndexInFace(i, 2);
		assert(v1 < #self.mVertices+1);
		assert(v2 < #self.mVertices+1);
		assert(v3 < #self.mVertices+1);
		-- Compute the normal of the face
		local p = assert(self.mVertices[v1])
		local q = assert(self.mVertices[v2])
		local r = assert(self.mVertices[v3])
		local normal = vmath.normalize(vmath.cross(q-p,r-p))

		self.mNormals[v1] = self.mNormals[v1]+normal;
		self.mNormals[v2] = self.mNormals[v1]+normal;
		self.mNormals[v3] = self.mNormals[v1]+normal;
	end

	for i=0,#self.mNormals do
		self.mNormals[i] = vmath.normalize(self.mNormals[i])
	end



end



--[[openglframework::Vector3 vertex(-(NB_POINTS_WIDTH - 1) * 0.5f + i, height, -(NB_POINTS_LENGTH - 1) * 0.5f + j);

mVertices.push_back(vertex);

// Triangle indices
if ((i < NB_POINTS_WIDTH - 1) && (j < NB_POINTS_LENGTH - 1)) {

unsigned int v1 = vertexId;
unsigned int v2 = vertexId + 1;
unsigned int v3 = vertexId + NB_POINTS_LENGTH;
unsigned int v4 = vertexId + NB_POINTS_LENGTH + 1;

// First triangle
indices.push_back(v1);
indices.push_back(v2);
indices.push_back(v3);

// Second triangle
indices.push_back(v2);
indices.push_back(v4);
indices.push_back(v3);
}

vertexId++;
}
}

mIndices.push_back(indices);

calculateNormals();
end--]]

function HeightField:dispose()
	PhysObject.dispose(self)
	rp3d.destroyHeightFieldShape(self.shape)
end

return HeightField