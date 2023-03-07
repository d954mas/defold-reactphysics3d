# Material
This table contains the material properties of a collider that will be use for the dynamics simulation like the friction coefficient or the bounciness of the rigid body.
```lua
local material = {
    --Bounciness factor (between 0 and 1) where 1 is very bouncy 
    bounciness = 0,
    
    --The friction coefficient has to be a positive value.
    --The value zero is used for no friction at all.
    frictionCoefficient = 0,
    
    --The mass density
    massDensity = 0
}
```