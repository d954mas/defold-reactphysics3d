local LUME = require "libs.lume"
local RENDER_3D = require("scene3d.render.render3d")

local M = {}

M.dirty = false -- if dirty update gui. Scene reload/changed

M.scene_config = {
	name = "",
	---@type Rp3dPhysicsWorld
	world = nil
}
M.rendering = {
	debug_draw = false,
	contact_points = false,
	contact_normals = false,
	broad_phase = false,
	colliders_aabb = false,
	shapes = true,
}
M.simulation = {
	play = true,
	make_step = false,
	sleep = true,
	gravity = true,
	velocity_iterations = 6,
	position_iterations = 3,
	step = 1 / 60,
	body_selected = nil,
	raycast_from = nil,
	raycast_to = nil
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

M.camera = {
	input = false,
	orbit_y = false,
	orbit_x = false,
	euler_y = 0,
	euler_x = 0
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
	M.simulation.raycast_from = nil
	M.simulation.raycast_to = nil
	M.simulation.body_selected = nil
end

function M.update(dt)
	local cfg = M.scene_config
	if (cfg.world) then
		cfg.world:setNbIterationsPositionSolver(M.simulation.position_iterations)
		cfg.world:setNbIterationsVelocitySolver(M.simulation.velocity_iterations)
		if (M.simulation.play or M.simulation.make_step) then
			M.simulation.make_step = false
			local time = socket.gettime()
			cfg.world:update(M.simulation.step)
			cfg.world:getDebugRenderer():draw()
			-- cfg.world:Step(cfg.dt * cfg.time_scale, cfg.velocityIterations, cfg.positionIterations)
			M.profiling.phys_step = socket.gettime() - time
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

	if (M.camera.orbit_y) then
		M.camera.euler_y = M.camera.euler_y + 25 * dt
	end

	if (M.camera.orbit_x) then
		M.camera.euler_x = M.camera.euler_x - 25 * dt
	end

	if (M.simulation.raycast_from) then
	--	msg.post("@render:", "draw_line",
			--	{ start_point = M.simulation.raycast_from, end_point = M.simulation.raycast_to, color = vmath.vector4(1, 0, 0, 0.5) })
	end
end

function M.updatePhysics(dt, objects)
	if (dt == 0) then return end
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

	w:setIsDebugRenderingEnabled(M.rendering.debug_draw)

	for _, object in ipairs(objects) do
		object:updateTransform()
		object:updateColor()
	end
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

-- Vectors used in calculations for public transform functions
local nv = vmath.vector4(0, 0, -1, 1)
local fv = vmath.vector4(0, 0, 1, 1)
local pv = vmath.vector4(0, 0, 0, 1)

local function world_to_screen(pos, raw)
	local mat_view = RENDER_3D.camera_view()
	local mat_proj = RENDER_3D.camera_perspective(math.rad(50))
	local m = mat_proj * mat_view
	pv.x, pv.y, pv.z, pv.w = pos.x, pos.y, pos.z, 1

	pv = m * pv
	pv = pv * (1 / pv.w)
	pv.x = (pv.x / 2 + 0.5) * RENDER_3D.window_width
	pv.y = (pv.y / 2 + 0.5) * RENDER_3D.window_height

	if raw then return pv.x, pv.y, 0 end
end
-- Returns start and end points for a ray from the camera through the supplied screen coordinates
-- Start point is on the camera near plane, end point is on the far plane.
local QUAT_Z = vmath.quat_rotation_x(math.rad(0))
local function screen_to_world_ray(x, y, raw)
	local mat_view = RENDER_3D.camera_view()
	local mat_proj = RENDER_3D.camera_perspective()

	local window_x = RENDER_3D.window_width
	local window_y = RENDER_3D.window_height
	local m = vmath.inv(mat_proj * mat_view)

	-- Remap coordinates to range -1 to 1
	local x1 = (x - window_x * 0.5) / window_x * 2
	local y1 = (y - window_y * 0.5) / window_y * 2

	nv.x, nv.y = x1, y1
	fv.x, fv.y = x1, y1
	local np = m * nv
	local fp = m * fv
	np = np * (1 / np.w)
	fp = fp * (1 / fp.w)

	if raw then return np.x, np.y, np.z, fp.x, fp.y, fp.z
	else return vmath.vector3(np.x, np.y, np.z), vmath.vector3(fp.x, fp.y, fp.z) end
end

function M.on_input(action_id, action)
	if (M.camera.input) then
		if (action_id == hash("touch")) then
			M.camera.euler_y = M.camera.euler_y + action.dx * 0.05
			M.camera.euler_x = M.camera.euler_x + action.dy * 0.05
			--M.camera.euler_x = M.camera.euler_x + action.dx * 0.1
		end
	else
		if (action_id == hash("touch")) then
			if action.pressed then
				--try raycast
				local ray_start, ray_end = screen_to_world_ray(action.screen_x, action.screen_y)
				M.simulation.raycast_from = vmath.vector3(ray_start)
				M.simulation.raycast_to = vmath.vector3(ray_end)

				if (M.scene_config.world) then
					---@type Rp3dCollisionBody
					local result = nil
					local result_world_pos = nil
					local ray_1 = { point1 = ray_start, point2 = ray_end, maxFraction = 1 }
					M.scene_config.world:raycast(ray_1, function(info)
						result = info.body
						result_world_pos = info.worldPoint
						return info.hitFraction
					end)
					if (M.simulation.body_selected) then
						local phys_body = M.simulation.body_selected:getUserData()
						phys_body:setSelected(false)
						M.simulation.body_selected = nil
					end
					if (result) then
						local phys_body = result:getUserData()
						phys_body:setSelected(true)
						M.simulation.body_selected = result
						M.simulation.body_selected_pos =result:getLocalPoint(result_world_pos)
					end
				end
			end

			if (action.released) then
				if (M.simulation.body_selected) then
					local phys_body = M.simulation.body_selected:getUserData()
					phys_body:setSelected(false)
					M.simulation.body_selected = nil
				end
			end

			if(not action.pressed and M.simulation.body_selected)then
				local v3 = vmath.vector3(action.dx/960,action.dy/540,0)
				local MOUSE_MOVE_BODY_FORCE = 200000.0
				local quat = vmath.quat_from_to(vmath.vector3(0,0,-1),RENDER_3D.view_front)
				v3 = vmath.rotate(quat,v3)


				local force = v3 * MOUSE_MOVE_BODY_FORCE

				M.simulation.body_selected:applyWorldForceAtLocalPosition(force, M.simulation.body_selected_pos);
			end


		end
	end

end

M.reset()

return M