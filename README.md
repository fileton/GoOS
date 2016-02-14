# GoOS
### Origin
Wouldn't it be nice to have an OS designed specifically for running applications written in Go? Well that is exactly the reason why I started this hobby OS project on the 26th of January 2016.

I was already fascinated with running Go compiled code on bare hardware which led to another project of mine called [libmigo] as a proof of concept. It's an ugly hack but it works.

So I had two options:

1) Redesign [libmigo] and turn it into something that can compile a single Go program to run on bare hardware.

2) Create a kernel tailor made for Go programs using a custom runtime enabling multiple programs written in Go to work together as one.

I chose the latter...

### Wishlist
These are a few things I want to implement of which two are the most defining features making this OS specifically designed for applications written in Go:
- Microkernel
- Preemptive multitasking
- Inter process communication via channels
- Kernel assisted garbage collection

### IPC via channels
One of the most defining features of Go is concurrency via the use of channels and the select statement and as such should be the defining feature of this OS. I want to take the concept beyond a single program and enable all programs running on GoOS to  exchange information the same way in a normal Go program they'd exchange information with goroutines.

The kernel will manage a global list of channels published to it by individual programs. A keyboard driver would publish a channel on which a program could register his channel that he wants keystrokes to be send thru.

### Kernel assisted garbage collection
Go wouldn't be Go if it didn't have a garbage collector so it must be implemented but having IPC thru channels demands a different approach. Each application will still have it's own garbage collector because of the overhead involved of having the kernel handle the creation of every new object and/or doing a garbage collection run on every program running.

By convention when a program sends objects thru a channel it gives up ownership of it and the receiver takes ownership. In normal Go programs this is merely a design principle, in GoOS it defines the behavior of a program's garbage collector for that object. The garbage collector only works on objects it has ownership of.

The (invisible) allocator in each application creates objects on memory pages it requests from the kernel. When an application crashes or ends then the kernel must know which dirty pages can be recycled. Dirty means that the page contains objects that another, still running, program has or had ownership of. You can imagine multiple programs owning different objects on a page that was originally given to another program because they were send via channels.

The way the kernel keeps track of dirty pages and how it detects when a dirty page can be recycled is what I call kernel assisted garbage collection. This is the key feature in enabling separate Go programs to work and communicate as one.

### Wish me luck
For now it's a personal project and until I have something to show that actually works as above it's going to stay that way. I've set myself a deadline of 1th of January 2018 to have a prototype microkernel and associated runtime ready.

So wish me luck! Feel free to contact me if you have questions, suggestions or just want to tell me that you can't wait for something tangible to play with.

[libmigo]: https://github.com/nutterts/libmigo
