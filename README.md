# Scimulator

[Indev] Making a scientifically accurate simulator.

---

## Blocks

There will be some predefined blocks, but you can create more blocks using the DSLs.

## DSL 1: Propierties

For every block type, you can add and modify propierties like this:

```
name=_brick    -- the _ indicates it's a string
ignitable=?f   -- ? bool
density=.9.9   -- . float
               -- # int
arr=@a,b       -- @ list
```

You can change the propierties for every block at a future sidebar.

## DSL 2: Logic

Also, some blocks need logic or movement. You can use this:

```
when .voltage do -- power is a float, so when power > 0 this is triggered
    if .voltage > 50 then
        emit(heat 10) -- If too much voltage, emit heat
    /
/
```

## Example: Humanoid

### Propierties

```
name=_humanoid
alive=?t
conscious=?t
grounded=?t
male=?f            -- t = male, f = female
conductsElectricity=?t
conductsHeat=?t
heat=.310.15        -- Kelvin
weight=.55.5        -- kg
height=.1.60        -- meters
reach=.1.65         -- meters
volume=.0.055       -- m³
hydration=.0.60     -- 60% standard tissue water
```

### Logic

```
when .power do
    if .power / .resistance >= 0.1 then
        alive=?f
        power=.0
    /.
/.

-- Simple logic: if too electricity, die
```

## Progress:

- Place iron blocks on a grid