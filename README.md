# Editor Camera Position for Unreal Engine

This is a simple plugin for Unreal Engine that displays the camera position in the editor's viewport. It can also set and copy-paste the camera position.

https://github.com/zompi2/EditorCameraPositionUE4/assets/7863125/f9744a1c-215a-43fc-a26f-2b529380d420

It works on UE4.27, UE5.2, UE5.3 and UE5.4 (or at least I tested it on these versions)

## Why is it useful?

It is useful when a QA team reports you a bug in specific location. Finding this place in the editor on a huge map with only coordinates is tricky. With this tool you can simply copy-paste this location and go directly to a place where the problem occurs. 

It is also useful if you want to share a specific world coordinates to a teammate without getting coordinates of a specific object.

## Blueprint nodes

If you need a position of the editor viewport's camera in your Blueprint Utility Widget there are Blueprint nodes that can help you with it:

#### Get Editor Camera Position
![geteditorcameraposbp](https://github.com/user-attachments/assets/c94d94f3-14aa-4780-8ec3-5cf5c0594ae7)

#### Set Editor Camera Position
![seteditorcameraposition](https://github.com/user-attachments/assets/2ab1834e-f33c-4133-acc1-8db642d17110)

## FAQ

**But you can save your fav camera positions using Ctrl+Numer**  
This plugin is not for saving your favourite camera positions. It's for a situation when you have to quickly jump to a specific coordinates, given to you by someone else (usually the QA).

**But you can just spawn cube, set it's location to the desired location, press F and delete that cube**  
Yeah... I know... but for me it was annoying to do it every time I needed that simple functionality. It saves you that few seconds every time :)

**Does it work for camera position when piloting actors?**  
Yes it does!

## Marketplace!

This plugin can be downloaded from the Unreal Engine Marketplace! Here's **[the link to it](https://www.unrealengine.com/marketplace/en-US/product/9864b623739f4fbab30f4d877b137fc9).**  
The version of this plugin on a marketplace is **1.0.6**.  
Unreal Marketplace doesn't support plugins for UE4. For UE4.27 you can download the prebuilt plugin from **[here](https://github.com/zompi2/EditorCameraPositionUE4/raw/packs/Packs/EditorCameraPosition-4.27.zip).**

## Extra Links

* [Unreal Engine Forum](https://forums.unrealengine.com/t/plugin-editor-camera-position/764078)
* [Blog Entry](https://zompidev.blogspot.com/2023/03/editor-camera-position-plugin-for-ue4.html)
* [Reddit Post](https://www.reddit.com/r/unrealengine/comments/10u8rjx/nobody_asked_for_this_but_this_is_a_plugin_that)

## Anything else?

Just hoping you can find it useful.  
Cheers!  
<3  


