
谈一下Rust在并发编程中一定会碰到的`Send`以及`Sync`，他们一起保证了Rust的线程安全。可参考[Send and Sync](https://doc.rust-lang.org/nomicon/send-and-sync.html)。里面有如下两句，记住它：
- **A type is Send if it is safe to send it to another thread**
- **A type is Sync if it is safe to share between threads (T is Sync if and only if &T is Send).**

翻译过来的意思就是
- `Send`表示数据能安全地被`move`到另一个线程
- `Sync`表示数据能在多个线程中被同时安全地访问
>这里“安全”指不会发生数据的竞争 (race condition)。
### Send
当一个类型`T`实现了`Send`，表示这个类型的所有权可以在线程间安全的转移。例如，我们有一个连接两个线程的通道，我们想要能够向通道发送些数据到另一个线程。因此，我们要确保这个类型实现了`Send`。`Send`定义如下:
```rust
// Types that can be transferred across thread boundaries.
pub unsafe auto trait Send { }

#[stable(feature = "rust1", since = "1.0.0")]
impl<T: ?Sized> !Send for *const T {}
#[stable(feature = "rust1", since = "1.0.0")]
impl<T: ?Sized> !Send for *mut T {}
```
除了指针类型，基本上其他大多类型都自动实现了`Send`，比如`u8`、`usize`等等。另外如果一个类型内的所有类型都实现了`Send`，那么这个类型也实现了`Send`。比如我们后面自定义了一个结构体`Data<T>`， 如果`T`是`Send`，那么`Data`也是`Send`。 那有没有不是`Send`的类型呢？ 我们先举个没有实现`Send`的例子：
```rust
pub fn move_not_send() {
    let data = Rc::new(10);

    let t1 = thread::spawn( move || {
        println!("{:?}", data);
    });

    t1.join();
}
```
编译结果如下：
```rust
error[E0277]: `Rc<i32>` cannot be sent between threads safely
   --> src/send.rs:16:14
    |
16  |       let t1 = thread::spawn( move || {
    |  ______________^^^^^^^^^^^^^__-
    | |              |
    | |              `Rc<i32>` cannot be sent between threads safely
17  | |         println!("{:?}", data);
18  | |     });
    | |_____- within this `[closure@src/send.rs:16:29: 18:6]`
    | 
   ::: /home/sl/.rustup/toolchains/stable-x86_64-unknown-linux-gnu/lib/rustlib/src/rust/library/std/src/thread/mod.rs:617:8
    |
617 |       F: Send + 'static,
    |          ---- required by this bound in `spawn`
    |
    = help: within `[closure@src/send.rs:16:29: 18:6]`, the trait `Send` is not implemented for `Rc<i32>`
    = note: required because it appears within the type `[closure@src/send.rs:16:29: 18:6]`

error: aborting due to previous error; 1 warning emitted
```
因为`Rc`没有实现`Send`，所以它是不能在线程间安全转移。我们之前分析过`Rc`的实现，它并不是线程安全的，它的引用计数没有实现原子操作，多线程时是有问题的。 
```rust
#[stable(feature = "rust1", since = "1.0.0")]
impl<T: ?Sized> !marker::Send for Rc<T> {}
#[stable(feature = "rust1", since = "1.0.0")]
impl<T: ?Sized> !marker::Sync for Rc<T> {}
```
正是Rust进行了严格的检查，避免了不安全的实现，避免了潜在的Bug。上面的情况，可以用`Arc`，因为`Arc`实现了`Send`。
```rust
#[stable(feature = "rust1", since = "1.0.0")]
unsafe impl<T: ?Sized + Sync + Send> Send for Arc<T> {}
#[stable(feature = "rust1", since = "1.0.0")]
unsafe impl<T: ?Sized + Sync + Send> Sync for Arc<T> {}
```
改正后的代码如下：
```rust
#[derive(Debug)]
struct Data<T: Debug> {
  inner: T,
}

pub fn move_send() {
    let data1 = Data {inner: 10};
    let data2 = Arc::new(Data {inner: 100});
    // let data3 = Data {inner: Rc::new(1000)};
    let t1 = thread::spawn(move || {
        println!("{:?}, {:?}", data1, data2);
        // println!("{:?}", data3);
    });

    t1.join();
}
```
编译通过。




### Sync
当一个类型`T`实现了`Sync`，表示这个类型在多线程并发时没有导致内存不安全的可能性。

```rust
pub unsafe auto trait Sync {}

#[stable(feature = "rust1", since = "1.0.0")]
impl<T: ?Sized> !Sync for *const T {}
#[stable(feature = "rust1", since = "1.0.0")]
impl<T: ?Sized> !Sync for *mut T {}
```


---
参考文档：          
- [Rust 中 Send 与 Sync 有什么区别?](https://lotabout.me/2018/QQA-send-vs-sync-in-rust/)
- [线程安全](https://zhuanlan.zhihu.com/p/24142191)