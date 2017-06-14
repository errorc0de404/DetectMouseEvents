# DetectMouseEvents
Detect if a mouse event was injected!

This code was initially written to show how easy it is to detect those AHK-Aimbots/Pixel Aimbots, 
that use functions like SendMessage/mouse_event/SendInput...

The reason why it is so easy to detect is, that the WinAPI sets a flag "LLMHF_INJECTED" whenever
a mouse/keyboard event was injected by a process (by calling one of the above functions for example).

The code will trigger a Messagebox with the accosiated event whenever the LLMHF_INJECTED flag is set.

In near future I will show you an example on how to bypass this flag using a self made mouse driver filter.
