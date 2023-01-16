local LUME = require "libs.lume"

local M = {}

M.dirty = false -- if dirty update gui. Scene reload/changed

M.scene_config = {
	name = "",
	---@type Rp3dPhysicsWorld
	world = nil
}
M.rendering = {
	debug_draw = true,
	contact_points = false,
	contact_normals = false,
	broad_phase = false,
	colliders_aabb = false,
	shapes = true,
}
M.simulation = {
	play = true,
	step = false,
	sleep = true,
	gravity = true,
	velocity_iterations = 6,
	position_iterations = 3,
	step = 1 / 60
}
M.profiling = {
	fps_delay = 1,
	dt_max = 0,
	fps = 0,
	frames = 0,
	dt = 0,
	phys_step = 0,
	phys_total = 0,
}

function M.set_allow_sleep(enable)
	M.simulation.sleep = enable
	if (M.scene_config.world) then

	end
end

function M.set_enable_gravity(enable)
	M.simulation.gravity = enable
	if (M.scene_config.world) then

	end
end

function M.scene_new(cfg)
	M.dirty = true
	M.scene_config.name = assert(cfg.name)
	M.scene_config.world = assert(cfg.world)
	M.profiling.fps = 0
	M.profiling.dt = 0
	M.profiling.phys_step = 0
	M.profiling.phys_total = 0
	M.profiling.dt_max = 0
	M.profiling.dt_total = 0
	M.profiling.fps_delay = 0
end

function M.scene_final()
	M.scene_config.world = nil
end

function M.update(dt)
	local cfg = M.scene_config
	if (cfg.world) then
		if (M.simulation.play or M.simulation.step) then
			M.simulation.step = false
			local time = socket.gettime()
			-- cfg.world:Step(cfg.dt * cfg.time_scale, cfg.velocityIterations, cfg.positionIterations)
			-- M.world_step_time = socket.gettime() - time
			--cfg.world:DebugDraw()
		end

	end

	M.profiling.dt_max = math.max(dt, M.profiling.dt_max)
	M.profiling.fps_delay = M.profiling.fps_delay - dt
	M.profiling.frames = M.profiling.frames + 1
	if (M.profiling.fps_delay < 0) then
		M.profiling.fps_delay = 1
		M.profiling.dt = M.profiling.dt_max
		M.profiling.fps = M.profiling.frames
		M.profiling.dt_max = 0
		M.profiling.frames = 0
	end


end

function M.updatePhysics(dt,objects)
	if (not M.scene_config.world) then return end
	local w = M.scene_config.world
	w:getDebugRenderer():setIsDebugItemDisplayed(rp3d.DebugRenderer.DebugItem.CONTACT_POINT,
			M.rendering.contact_points)
	w:getDebugRenderer():setIsDebugItemDisplayed(rp3d.DebugRenderer.DebugItem.CONTACT_NORMAL,
			M.rendering.contact_normals)
	w:getDebugRenderer():setIsDebugItemDisplayed(rp3d.DebugRenderer.DebugItem.COLLIDER_BROADPHASE_AABB,
			M.rendering.broad_phase)
	w:getDebugRenderer():setIsDebugItemDisplayed(rp3d.DebugRenderer.DebugItem.COLLIDER_AABB,
			M.rendering.colliders_aabb)
	w:getDebugRenderer():setIsDebugItemDisplayed(rp3d.DebugRenderer.DebugItem.COLLISION_SHAPE,
			M.rendering.shapes)

	for _,object in ipairs(objects)do
		object:update_transform()
	end

	w:getDebugRenderer():draw()
end

function M.reset()
	local cfg = M.scene_config
	M.dirty = true
	cfg.velocityIterations = 8
	cfg.positionIterations = 3
	--  M.debug_draw.flags =  bit.bor(box2d.b2Draw.e_shapeBit, box2d.b2Draw.e_jointBit)
	-- M.debug_draw.draw:SetFlags(M.debug_draw.flags)
end

function M.debug_draw_add_flag(flag)
	--  M.debug_draw.flags = bit.bor(M.debug_draw.flags, flag)
	--  M.debug_draw.draw:SetFlags(M.debug_draw.flags)
end

function M.debug_draw_remove_flag(flag)
	--   M.debug_draw.flags = bit.band(M.debug_draw.flags, bit.bnot(flag))
	--  M.debug_draw.draw:SetFlags(M.debug_draw.flags)
end

M.reset()

return M