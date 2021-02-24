## A description of how Rust's channel implementation works

Channels are supposed to be the basic building block for all other concurrent primitives that are used in Rust. As a result, the channel type needs to be highly optimized, flexible, and broad enough for use everywhere.

The choice of implementation of all channels is to be built on lock-free data structures. The channels themselves are then consequently also lock-free data structures. As always with lock-free code, this is a very "here be dragons" territory, especially because I'm unaware of any academic papers that have gone into great length about channels of these flavors.

## Flavors of channels

From the perspective of a consumer of this library, there is only one flavor of channel. This channel can be used as a stream and cloned to allow multiple senders. Under the hood, however, there are actually three flavors of channels in play.

* Flavor::Oneshots - these channels are highly optimized for the one-send use case. They contain as few atomics as possible and involve one and exactly one allocation.
* Streams - these channels are optimized for the non-shared use case. They use a different concurrent queue that is more tailored for this use case. The initial allocation of this flavor of channel is not  optimized.
* Shared - this is the most general form of channel that this module offers, a channel with multiple senders. This type is as optimized as it can be, but the previous two types mentioned are much faster for their use-cases.

## Concurrent queues

The basic idea of Rust's Sender/Receiver types is that send() never blocks, but recv() obviously blocks. This means that under the hood there must be some shared and concurrent queue holding all of the actual data.

With two flavors of channels, two flavors of queues are also used. We have chosen to use queues from a well-known author that are abbreviated as SPSC and MPSC (single producer, single consumer and multiple producer, single consumer). SPSC queues are used for streams while MPSC queues are used for shared channels.

### SPSC optimizations

The SPSC queue found online is essentially a linked list of nodes where one half of the nodes are the "queue of data" and the other half of nodes are a cache of unused nodes. The unused nodes are used such that an allocation is not required on every push() and a free doesn't need to happen on every pop().

As found online, however, the cache of nodes is of an infinite size. This means that if a channel at one point in its life had 50k items in the queue, then the queue will always have the capacity for 50k items. I believed that this was an unnecessary limitation of the implementation, so I have altered the queue to optionally have a bound on the cache size.

By default, streams will have an unbounded SPSC queue with a small-ish cache size. The hope is that the cache is still large enough to have very fast send() operations while not too large such that millions of channels can coexist at once.

### MPSC optimizations

Right now the MPSC queue has not been optimized. Like the SPSC queue, it uses a linked list under the hood to earn its unboundedness, but I have not put forth much effort into having a cache of nodes similar to the SPSC queue.

For now, I believe that this is "ok" because shared channels are not the most common type, but soon we may wish to revisit this queue choice and determine another candidate for backend storage of shared channels.

## Overview of the Implementation

Now that there's a little background on the concurrent queues used, it's worth going into much more detail about the channels themselves. The basic pseudocode for a send/recv are:


     send(t)                             recv()
       queue.push(t)                       return if queue.pop()
       if increment() == -1                deschedule {
         wakeup()                            if decrement() > 0
                                               cancel_deschedule()
                                           }
                                           queue.pop()

As mentioned before, there are no locks in this implementation, only atomic instructions are used.

### The internal atomic counter

Every channel has a shared counter with each half to keep track of the size of the queue. This counter is used to abort descheduling by the receiver and to know when to wake up on the sending side.

As seen in the pseudocode, senders will increment this count and receivers will decrement the count. The theory behind this is that if a sender sees a -1 count, it will wake up the receiver, and if the receiver sees a 1+ count, then it doesn't need to block.

The recv() method has a beginning call to pop(), and if successful, it needs to decrement the count. It is a crucial implementation detail that this decrement does *not* happen to the shared counter. If this were the case, then it would be possible for the counter to be very negative when there were no receivers waiting, in which case the senders would have to determine when it was actually appropriate to wake up a receiver.

Instead, the "steal count" is kept track of separately (not atomically because it's only used by receivers), and then the decrement() call when descheduling will lump in all of the recent steals into one large decrement.

The implication of this is that if a sender sees a -1 count, then there's guaranteed to be a waiter waiting!

## Native Implementation

A major goal of these channels is to work seamlessly on and off the runtime. All of the previous race conditions have been worded in terms of scheduler-isms (which is obviously not available without the runtime).

For now, native usage of channels (off the runtime) will fall back onto mutexes/cond vars for descheduling/atomic decisions. The no-contention path is still entirely lock-free, the "deschedule" blocks above are surrounded by a mutex and the "wakeup" blocks involve grabbing a mutex and signaling on a condition variable.

## Select

Being able to support selection over channels has greatly influenced this design, and not only does selection need to work inside the runtime, but also outside the runtime.

The implementation is fairly straightforward. The goal of select() is not to return some data, but only to return which channel can receive data without blocking. The implementation is essentially the entire blocking procedure followed by an increment as soon as its woken up. The cancellation procedure involves an increment and swapping out of to_wake to acquire ownership of the thread to unblock.

Sadly this current implementation requires multiple allocations, so I have seen the throughput of select() be much worse than it should be. I do not believe that there is anything fundamental that needs to change about these channels, however, in order to support a more efficient select().

FIXME: Select is now removed, so these factors are ready to be cleaned up!

# Conclusion

And now that you've seen all the races that I found and attempted to fix, here's the code for you to find some more!