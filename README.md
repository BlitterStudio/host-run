# What is this

A small collection of tools to help Amiberry communicate with the underlying Linux OS.

## Host-Run

Host-run is a tiny AmigaOS tool, which allows you to have Amiberry execute a command on the underlying Linux operating system, with optional parameters. Think AmiKit's RabbitHole feature, only running on Amiberry and Linux (instead of WinUAE and Windows).
For example, you can have AmigaOS open Firefox (from the Linux side) and even pass a parameter of the website you want it to open.

## Host-MultiView

Host-Multiview is a tiny tool, similar to `host-run` mentioned above, but with a small change.
It calls `xdg-open` with the parameters you give it, which should make Linux open the file(s) you passed with the default filetype handler. For example, if you pass it an MKV file, it can open it with VLC, if you pass it an mp3 file, it may open it with Audacious, etc.

## How does it work

* You can get the pre-compiled binaries from the Releases page.
* Place them somewhere in your path (e.g. C: is a good idea)
* Use them from an AmigaOS Shell, script or icon (make sure it runs as Shell, not Workbench), to execute a Linux command with any parameters.
* If Amiberry's option to allow Native Code is enabled (in the Misc Panel), it will execute that command along with any parameters for you.
* Since Amiberry v3.4, AmigaOS device and volume names are automatically translated to the underlying host paths. This allows you to provide the full path to a file with host-run (or host-multiview), and as long as the location is accessible from the Linux side (i.e. it's not in a hardfile), it will find and access it.

## Examples

* Running Firefox from an AmigaOS shell: `host-run firefox`
* Running Chromium browser with a specific website (Amiberry in this case): `host-run chromium-browser https://github.com/BlitterStudio/amiberry`
* Launching VLC to play a video (assuming Work: is a directory on the Linux filesystem): `host-run vlc Work:videos/my_video.mkv`
* Using host-multivew to open the same video file (to demonstrae the simplicity): `host-multiview Work:videos/my_video.mkv`

* ### Create an icon to launch VLC

* Create a new text file, with these contents: `host-run vlc`
* Create a new icon or copy one you like, give it the same name as your text file above.
* Edit the icon's Information and make sure the Type is set to Project
* Set the icon's default tool to "C:IconX" and save the changes
* Double-clicking on the icon should now launch VLC on Linux.

### Create a DefIcons entry to handle MKV files

* Create a new entry to handle the .mkv extension
* Add a Project Type icon for the new entry
* Edit the icon's Information, and set the Default Tool to: `host-multiview`
* Save the changes
* Double clicking on an MKV file will now use `host-multiview` to open it, which will send it to Linux to be opened as if you double-clicked the file there. If you have a program that can handle such files installed (e.g. VLC) it should open up and play your file.
