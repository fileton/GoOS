# GoOS

#####26 jan 2016
While working on libmigo it dawned on me that if something is worth doing, it's worth doing well. The library was limited to x86 protected mode and was envisioned as a toolset for somebody who wants to write an operating system using Go, not an operating system by itself.

After much concideration and understanding the longterm commitment it would take I decided to use what I learned from libmigo and design an OS using Go. It should from a user and driver perspective be as idiomatic as possible which should lead to an interesting design. 

The first steps will concist of writing a clean 32bit codebase for the loader that creates a sane environment for our 64bit kernel. This part will be exclusivly assembler & C.
