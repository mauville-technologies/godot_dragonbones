# Documentation

## Dragonbones Data Format

The dragonbones data format has a lot of components. In this section I'll attempt to explain the important pieces in relation to what is avaiable in Godot Dragonbones.

### Structure

The structure of a dragonbones file has 3 major components, in relation to what is displayed on the screen.

1. Armature

    This is the larger structure. The armature contains all the data for bones, IK, and slots. It also handles making calls to the animation engine.

2. Slot

    Meshes, Images and even other Armatures can be put into a slot and displayed in the slots position. A slot also controls its items' color modifiers. An armature has many slots.

### 