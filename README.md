# What is it?
Host-run is a tiny AmigaOS tool, which allows you to have Amiberry execute a command on the underlying Linux operating system. Think AmiKit's RabbitHole feature, only running on Amiberry and Linux (instead of WinUAE and Windows).

# How does it work?
* You can get the pre-compiled binary from the Releases page.
* Place it somewhere in your path (e.g. C: is a good idea)
* Use it from an AmigaOS Shell, script or icon (must be a Project type and use IconX), to execute a Linux command with any parameters.
* If Amiberry's option to allow host-run is enabled, it will execute that command along with any parameters for you.

# Examples
* Running Firefox from an AmigaOS shell: `host-run firefox`
* Running Chromium browser with a specific website `host-run chromium-browser https://github.com/midwan/amiberry`