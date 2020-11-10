# What is it

Host-run is a tiny AmigaOS tool, which allows you to have Amiberry execute a command on the underlying Linux operating system. Think AmiKit's RabbitHole feature, only running on Amiberry and Linux (instead of WinUAE and Windows).

## How does it work

* You can get the pre-compiled binary from the Releases page.
* Place it somewhere in your path (e.g. C: is a good idea)
* Use it from an AmigaOS Shell, script or icon (must be a Project type and use IconX), to execute a Linux command with any parameters.
* If Amiberry's option to allow host-run is enabled, it will execute that command along with any parameters for you.
* Since Amiberry v3.4, AmigaOS device and volume names are automatically translated to the underlying host paths. This allows you to provide the full path to a file with host-run, and as long as the location is accessible from the Linux side (i.e. it's not in a hardfile), it will find and access it.

## Examples

* Running Firefox from an AmigaOS shell: `host-run firefox`
* Running Chromium browser with a specific website: `host-run chromium-browser https://github.com/midwan/amiberry`
* Launching VLC to play a video (assuming Work: is a directory on the Linux filesystem): `host-run vlc Work:videos/my_video.mkv`

* ### Create an icon to launch VLC

* Create a new text file, with these contents: `host-run vlc`
* Create a new icon or copy one you like, give it the same name as your text file above.
* Edit the icon's Information and make sure the Type is set to Project
* Set the icon's default tool to "C:IconX" and save the changes
* Double-clicking on the icon should now launch VLC on Linux.
