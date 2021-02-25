/*
汉诺塔问题： 有n个盘子在A处， 盘子从大到小排列，最上面的盘子最小。现在要把这n个盘子从A处搬到C处，可以在B处暂存，但任何时候都不能出现
大盘子压在小盘子上面的情况。

解决思路： 当只有一个盘子时，直接从A移动到C即可。如果已知n-1个盘子的移动方案，那么n个盘子的方案如下： 先把前n-1个盘子从A借助C移动到B，
再把第n个盘子从A直接移动到C处，然后将B处的n-1个盘子从B借A移动到C处。
*/


use std::borrow::BorrowMut;

fn main() {
    let data = vec![5,4,3,2,1usize];
    let mut a = data.clone();
    let mut b = vec![];
    let mut c = vec![];
    hanoi(a.len(), a.borrow_mut(), b.borrow_mut(), c.borrow_mut());
    assert_eq!(data, c);
    println!("a: {:?}, b: {:?}, c: {:?}", a, b, c);
}

// 可将大盘子小盘子抽象为数字，塔抽象为栈。
// 如果n=1, 将盘子从a直接移到c
// 如果n>1, 1. 将n-1个盘子从a经c移动到b; 2. 将n从a移动到c; 3. 将n-1个盘子从b经a移动到c
fn hanoi(n: usize, a: &mut Vec<usize>, b: &mut Vec<usize>, c: &mut Vec<usize>) {
    assert!(n > 0);
    if n > 1 {
        hanoi(n-1, a, c, b);
        move_to(a, c);
        hanoi(n-1, b, a, c);
    } else {
        move_to(a, c);
    }
}


fn move_to(from: &mut Vec<usize>, to: &mut Vec<usize>) {
    assert!(from.len() > 0);
    let data = from.pop().unwrap();
    to.push(data);
}