Name:Joseph Bentley
pNum : p10011026

TMX Tile Engine Assessment

Framework : XDL v0.1 ;)


Hey Phil, 
Controls : 
1 : pokemon Town, its size is exactly the screens size, but the small trees in the center are a different layer
2 : Desert Map : Loads a single layer TMX, with margins and spacing. 
3 : Swamp : Loads a single layer isometric TMX

WASD to move player, the camera should follow.

O and P to zoom the camera, although its not focused on the player just yet
R to reset camera

Bare in mind that i wrote alot of this with a focus towards using it as a foundation for my 4yp. Because of this, i wrote
alot of helper classes that made my experience with SDL alot easier over all. 

Alot of things are going to be changed from this, such as the tile engine loading from XMl, i aim to move all the XML code away
from that and putting it in ContentManager. I also intend to expand on sprite, to player etc, with helper functions for the end user.
At the moment its just a sprite, but the end intension is to be like coco's, where you can expand Sprite, and suddenly, you 
are a fully fledged sprite, with draw, update and helper functions and collisions.

Thanks
-Joe