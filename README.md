# Editor Camera Position for Unreal Engine

This is a simple plugin for Unreal Engine that displays the camera position in the editor's viewport. It can also set and copy-paste the camera position.

https://github.com/zompi2/EditorCameraPositionUE4/assets/7863125/f9744a1c-215a-43fc-a26f-2b529380d420

It works on UE4.27, UE5.2, UE5.3, UE5.4 and UE5.5 (or at least I tested it on these versions)

## Why is it useful?

It is useful when a QA team reports you a bug in specific location. Finding this place in the editor on a huge map with only coordinates is tricky. With this tool you can simply copy-paste this location and go directly to a place where the problem occurs. 

It is also useful if you want to share a specific world coordinates to a teammate without getting coordinates of a specific object.

## Rotation

The plugin can also display and modify the camera rotation.

![camrot1](https://github.com/user-attachments/assets/ad91016f-5d2b-4e0c-81bb-8af2a901efc4)
![camrot2](https://github.com/user-attachments/assets/96603b3b-da49-4e28-b7c1-0c36293dd601)

## Blueprint nodes

If you need a position or rotation of the editor viewport's camera in your Blueprint Utility Widget there are Blueprint nodes that can help you with it:

#### Get Editor Camera Position
![geteditorcameraposbp](https://github.com/user-attachments/assets/c94d94f3-14aa-4780-8ec3-5cf5c0594ae7)

#### Set Editor Camera Position
![seteditorcameraposition](https://github.com/user-attachments/assets/2ab1834e-f33c-4133-acc1-8db642d17110)

#### Get Editor Camera Rotation
![camrot3](https://github.com/user-attachments/assets/0480b7db-88cd-4904-991b-b6c4429a9812)

#### Set Editor Camera Rotation
![camrot4](https://github.com/user-attachments/assets/089c591c-3c6b-4f98-abe4-f4a40a21dcb3)

## Settings

You can find few settings inside the `Edit -> Editor Preferences -> Plugins -> Editor Camera Position` section.

![camcam](https://github.com/user-attachments/assets/b6d7befa-1909-453f-ab99-ea956c175086)

* Enable Editor Camera Position/Rotation - should the option to show camera position or rotation in the editor be even possible?
* Camera Position/Rotation Trunc - describes how to truncate the values of camera position and rotation when moving the camera in the editor. Possible values:
    * `No Trunc` - the values will not be truncated
    * `Two Decimals` - the values will be truncated to two decimal places
    * `Zero Decimals` - the values will be truncated to the total integer values

## FAQ

**But you can save your fav camera positions using Ctrl+Numer**  
This plugin is not for saving your favourite camera positions. It's for a situation when you have to quickly jump to a specific coordinates, given to you by someone else (usually the QA).

**But you can just spawn cube, set it's location to the desired location, press F and delete that cube**  
Yeah... I know... but for me it was annoying to do it every time I needed that simple functionality. It saves you that few seconds every time :)

**Does it work for camera position and rotation when piloting actors?**  
Yes it does!

## Fab

This plugin can be downloaded from the Unreal Engine Fab! Here's **[the link to it](https://www.fab.com/listings/13d27c05-5c95-46f2-a123-06891956049e).**  
The version of this plugin on Fab is **1.1.1**.  
If you want to download it for UE4.27 you can download the prebuilt plugin from **[here](https://github.com/zompi2/EditorCameraPositionUE4/raw/packs/Packs/EditorCameraPosition-4.27.zip).**

## Anything else?

Just hoping you can find it useful.  
Cheers!  
<3  


