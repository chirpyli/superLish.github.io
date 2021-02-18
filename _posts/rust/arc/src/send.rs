use std::thread;
use std::sync::mpsc::*;
use std::rc::Rc;
use std::sync::Arc;
use std::fmt::Debug;




pub fn move_not_send() {
    let data = Rc::new(10);

    // let t1 = thread::spawn( move || {
    //     println!("{:?}", data);
    // });
    //
    // t1.join();
}

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

pub fn sync() {
    let data1 = Data {inner: 10};
    let r1 = &data1;
    let data2 = Arc::new(Data {inner: 100});

    let t1 = thread::spawn(move || {
      println!("{:?}, {:?}", r1, data2);
    });

    t1.join();


    println!("end");
}
